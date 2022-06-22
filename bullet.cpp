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
#include "object2D.h"
#include "application.h"
#include "player.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
}

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
	m_life(0),
	m_index(0)
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
	CObject2D::Init();

	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	// 位置の設定
	CObject2D::SetPos(pos);

	// テクスチャの設定
	CObject2D::SetTexture(CTexture::TEXTURE_icon_122540_256);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CBullet::Uninit()
{
	// 終了
	CObject2D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CBullet::Update()
{
	m_life--;

	D3DXVECTOR3 pos = CObject2D::GetPos() + m_move;

	// 位置の設定
	CObject2D::SetPos(pos);

	// 更新
	CObject2D::Update();

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
	CObject2D::Draw();
}
