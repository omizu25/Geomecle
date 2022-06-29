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
#include <assert.h>

//--------------------------------------------------
// 生成
//--------------------------------------------------
CBullet* CBullet::Create()
{
	CBullet* pBullet = nullptr;

	pBullet = new CBullet;

	if (pBullet != nullptr)
	{// nullチェック
		pBullet->Init();
	}

	return pBullet;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CBullet::CBullet() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_life(0)
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
	m_life = 60;
	m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject::TYPE_BULLET);

	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	// 位置の設定
	CObject3D::SetPos(pos);

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
	m_life--;

	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;

	// 位置の設定
	CObject3D::SetPos(pos);

	// 更新
	CObject3D::Update();

	CObject** pObject = GetMyObject();

	for (int i = 0; i < CObject::MAX_OBJECT; i++)
	{
		if (pObject[i] == nullptr)
		{// nullチェック
			continue;
		}

		if (pObject[i]->GetType() != CObject::TYPE_ENEMY)
		{// 種類が違う
			continue;
		}

		D3DXVECTOR3 enemyPos = pObject[i]->GetPos();
		float enemySize = pObject[i]->GetSize() * 0.5f;
		float size = CObject3D::GetSize() * 0.5f;

		if ((pos.y - size <= (enemyPos.y + enemySize)) &&
			(pos.y + size >= (enemyPos.y - enemySize)) &&
			(pos.x - size <= (enemyPos.x + enemySize)) &&
			(pos.x + size >= (enemyPos.x - enemySize)))
		{// 当たり判定
			pObject[i]->Release();

			// 解放
			CObject::Release();
			return;
		}
	}

	if (m_life <= 0)
	{// 体力が亡くなった
		// 解放
		CObject::Release();
		return;
	}

	if (pos.x >= CApplication::SCREEN_WIDTH)
	{// 画面の左端を越した
		// 解放
		CObject::Release();
		return;
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
