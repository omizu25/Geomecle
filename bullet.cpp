//**************************************************
// 
// bullet.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "bullet.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include "effect_manager.h"
#include "exp.h"
#include "score.h"
#include "mode.h"
#include "game.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CBullet::SHOT_INTERVAL = 8;
const float CBullet::STD_SIZE = 25.0f;
const float CBullet::STD_MOVE = 15.0f;
const float CBullet::STD_INERTIA = 0.3f;

//==================================================
// 静的メンバ変数
//==================================================
int CBullet::m_time = 0;
float CBullet::m_dest = 0.0f;
float CBullet::m_now = 0.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CBullet* CBullet::Create(float rot)
{
	CBullet* pBullet = nullptr;

	pBullet = new CBullet;

	if (pBullet != nullptr)
	{// nullチェック
		pBullet->Init();
		pBullet->SetMove(rot);
	}

	return pBullet;
}

//--------------------------------------------------
// 発射
//--------------------------------------------------
void CBullet::Shot()
{
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (!CInput::GetKey()->Shot(&rot))
	{// 弾の発射していない
		m_dest = 0.0f;
		m_now = 0.0f;
		m_time = 0;
		return;
	}

	if ((m_time % SHOT_INTERVAL) != 0)
	{// インターバル中
		m_time++;
		return;
	}

	if (m_time == 0)
	{// １発目
		// 目的の向き
		m_dest = atan2f(rot.x, rot.y);

		// 角度の正規化
		NormalizeAngle(&m_dest);

		m_now = m_dest;

		// 弾発射
		CBullet::Create(m_now);

		m_time++;
		return;
	}

	m_time++;

	// 目的の向き
	m_dest = atan2f(rot.x, rot.y);

	// 角度の正規化
	NormalizeAngle(&m_dest);

	float angle = m_dest - m_now;

	// 角度の正規化
	NormalizeAngle(&angle);

	// 慣性・向きを更新 (減衰させる)
	m_now += angle * STD_INERTIA;

	// 角度の正規化
	NormalizeAngle(&m_now);

	// 弾発射
	CBullet::Create(m_now);
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CBullet::CBullet() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CBullet::~CBullet()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CBullet::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject3D::TYPE_BULLET);

	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	// 位置の設定
	CObject3D::SetPos(pos);

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Bullet);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CBullet::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CBullet::Update()
{
	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;

	// 位置の設定
	CObject3D::SetPos(pos);

	// 更新
	CObject3D::Update();

	{
		float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
		float width = (CWall::STD_WIDTH * 0.5f) - size;
		float height = (CWall::STD_HEIGHT * 0.5f) - size;

		if (InRange(&pos, D3DXVECTOR3(width, height, 0.0f)))
		{// 範囲外
			// 爆発
			CEffectManager::GetInstanse()->Bullet(pos);

			// 解放
			CObject::Release();
			return;
		}
	}

	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D::EType type = CObject3D::TYPE_NONE;
	D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float targetSize = 0.0f;
	float size = STD_SIZE * 0.5f;

	for (int i = 0; i < CObject::GetMax(CObject::CATEGORY_3D); i++)
	{
		if (pObject[i] == nullptr)
		{// nullチェック
			continue;
		}

		type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_ENEMY && type != CObject3D::TYPE_BODY)
		{// 指定のタイプではない
			continue;
		}

		switch (type)
		{
		case CObject3D::TYPE_BODY:
		{
			targetPos = pObject[i]->GetPos();
			targetSize = pObject[i]->GetSize().x * 0.5f;

			if (CollisionCircle(pos, size, targetPos, targetSize))
			{// 当たり判定
				// 解放
				CObject::Release();
				return;
			}
		}
			break;

		case CObject3D::TYPE_ENEMY:
		{
			CEnemy* pEnemy = (CEnemy*)pObject[i];
			targetPos = pEnemy->GetPos();
			targetSize = pEnemy->GetSize().x * 0.5f;

			if (CollisionCircle(pos, size, targetPos, targetSize))
			{// 当たり判定
				// 経験値の生成
				CExp::CreateAll(targetPos);

				CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

				// スコアの加算
				pGame->GetScore()->Add(CEnemy::STD_SCORE);

				// 敵の解放
				pObject[i]->Release();
				return;
			}
		}
			break;

		default:
			assert(false);
			break;
		}
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CBullet::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CBullet::SetMove(float rot)
{
	// 向きの設定
	CObject3D::SetRot(rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;
}