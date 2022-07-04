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
#include "object3D.h"
#include "application.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CBullet::MAX_SIZE = 30.0f;
const float CBullet::MAX_MOVE = 10.0f;

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
HRESULT CBullet::Init()
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
	CObject3D::SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_icon_122540_256);

	return S_OK;
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
		float size = (MAX_SIZE * 0.5f) + (CWall::MAX_WIDTH * 0.5f);
		float wall = (CWall::MAX_LENGTH * 0.5f) - size;

		if (InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f)))
		{// 範囲外
			// 解放
			CObject::Release();
			return;
		}
	}

	CObject** pObject = GetMyObject();

	for (int i = 0; i < CObject::MAX_OBJECT; i++)
	{
		if (pObject[i] == nullptr ||
			pObject[i]->GetType() != CObject::TYPE_ENEMY)
		{
			continue;
		}

		D3DXVECTOR3 enemyPos = pObject[i]->GetPos();
		float size = (MAX_SIZE * 0.5f);

		if (((pos.y - size) <= (enemyPos.y + CEnemy::MAX_SIZE)) &&
			((pos.y + size) >= (enemyPos.y - CEnemy::MAX_SIZE)) &&
			((pos.x - size) <= (enemyPos.x + CEnemy::MAX_SIZE)) &&
			((pos.x + size) >= (enemyPos.x - CEnemy::MAX_SIZE)))
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

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * MAX_MOVE;
}