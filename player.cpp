//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "player.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "wall.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CPlayer::STD_SIZE = 30.0f;
const float CPlayer::STD_MOVE = 5.0f;
const float CPlayer::STD_ROT = 0.1f;

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

	// 位置の設定
	CObject3D::SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

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
	// 移動
	Move();

	// 向き
	Rot();

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

	// 目的の向き
	m_rotDest = atan2f(vec.x, vec.y);

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// 移動
	pos.x += vec.x * STD_MOVE;
	pos.y += vec.y * STD_MOVE;

	float size = (STD_SIZE * 0.5f) + (CWall::GetWidth() * 0.5f);
	float wall = (CWall::GetLength() * 0.5f) - size;

	// 範囲内
	InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f));

	// 位置の設定
	CObject3D::SetPos(pos);
}

//--------------------------------------------------
// 向き
//--------------------------------------------------
void CPlayer::Rot()
{
	float angle = 0.0f;

	// 角度の正規化
	NormalizeAngle(&m_rotDest);

	float rot = CObject3D::GetRot();

	angle = m_rotDest - rot;

	// 角度の正規化
	NormalizeAngle(&angle);

	//慣性・向きを更新 (減衰させる)
	rot += angle * STD_ROT;

	// 角度の正規化
	NormalizeAngle(&rot);

	// 向きの設定
	CObject3D::SetRot(rot);
}