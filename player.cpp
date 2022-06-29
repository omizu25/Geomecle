//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "player.h"
#include "object2D.h"
#include "bullet.h"
#include "texture.h"
#include <assert.h>

//--------------------------------------------------
// 生成
//--------------------------------------------------
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{// nullチェック
		pPlayer->Init();
	}

	return pPlayer;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CPlayer::CPlayer()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CPlayer::Init()
{
	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject::TYPE_PLAYER);

	//D3DXVECTOR3 pos = D3DXVECTOR3(CApplication::SCREEN_WIDTH * 0.5f, CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_icon_122380_256);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CPlayer::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CPlayer::Update()
{
	CInput* pInput = CInput::GetKey();

	if (pInput->Trigger(CInput::KEY_SHOT))
	{// スペースキーが押された
		CBullet::Create();
		CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_ENTER);
	}

	// 移動
	Move();

	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CPlayer::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 移動
//--------------------------------------------------
void CPlayer::Move()
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_LEFT))
	{// 左キーが押された
		vec.x -= 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_RIGHT))
	{// 右キーが押された
		vec.x += 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_UP))
	{// 上キーが押された
		vec.y += 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_DOWN))
	{// 下キーが押された
		vec.y -= 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// 移動してない
		return;
	}

	// ベクトルの正規化
	D3DXVec3Normalize(&vec, &vec);

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// 移動
	pos.x += vec.x * 7.0f;
	pos.y += vec.y * 7.0f;

	// 位置の設定
	CObject3D::SetPos(pos);
}
