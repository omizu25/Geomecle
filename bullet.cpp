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
#include "game.h"
#include "utility.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CBullet::SHOT_INTERVAL = 10;
const float CBullet::STD_SIZE = 25.0f;
const float CBullet::STD_MOVE = 10.0f;
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
	CObject3D::SetType(CObject::TYPE_BULLET);

	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	// 位置の設定
	CObject3D::SetPos(pos);

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_icon_122540_256);
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
		float size = (STD_SIZE * 0.5f) + (CWall::GetWidth() * 0.5f);
		float wall = (CWall::GetLength() * 0.5f) - size;

		if (InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f)))
		{// 範囲外
			// 解放
			CObject::Release();
			return;
		}
	}

	CObject** pObject = GetMyObject();

	for (int i = 0; i < CObject::GetMax(); i++)
	{
		if (pObject[i] == nullptr ||
			pObject[i]->GetType() != CObject::TYPE_ENEMY)
		{
			continue;
		}

		CEnemy* pEnemy = (CEnemy*)pObject[i];
		D3DXVECTOR3 enemyPos = pEnemy->GetPos();
		D3DXVECTOR3 enemySize = pEnemy->GetSize();
		float size = (STD_SIZE * 0.5f);

		if (((pos.y - size) <= (enemyPos.y + enemySize.y)) &&
			((pos.y + size) >= (enemyPos.y - enemySize.y)) &&
			((pos.x - size) <= (enemyPos.x + enemySize.x)) &&
			((pos.x + size) >= (enemyPos.x - enemySize.x)))
		{// 当たり判定
			// 敵の解放
			pObject[i]->Release();

			// 解放
			CObject::Release();
			return;
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