//**************************************************
// 
// enemy.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy.h"
#include "object3D.h"
#include "bullet.h"
#include "player.h"
#include "texture.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEnemy* CEnemy::Create()
{
	CEnemy* pEnemy = nullptr;

	pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{// nullチェック
		pEnemy->Init();
	}

	return pEnemy;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemy::CEnemy()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemy::~CEnemy()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CEnemy::Init()
{
	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject::TYPE_ENEMY);

	D3DXVECTOR3 pos = D3DXVECTOR3(300.0f, 0.0f, 0.0f);

	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_InuiToko000);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemy::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemy::Update()
{
	D3DXVECTOR3 posDest = CApplication::GetInstanse()->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// ホーミング
	Homing(&pos, pos, posDest, 3.0f);

	// 位置の設定
	CObject3D::SetPos(pos);

	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemy::Draw()
{
	// 描画
	CObject3D::Draw();
}
