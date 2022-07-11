//**************************************************
// 
// enemy_snake_head.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy_snake_head.h"
#include "object3D.h"
#include "bullet.h"
#include "player.h"
#include "texture.h"
#include "utility.h"
#include "wall.h"
#include "enemy_snake_body.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEnemySnakeHead::MAX_BODY = 15;
const int CEnemySnakeHead::IDX_PARENT = 0;
const float CEnemySnakeHead::MAX_SIZE = 20.0f;
const float CEnemySnakeHead::MAX_MOVE = 1.5f;
const float CEnemySnakeHead::AMPLITUDE_WIDTH = 3.0f;
const float CEnemySnakeHead::AMPLITUDE_SPEED = 2.0f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemySnakeHead::CEnemySnakeHead() :
	m_time(0),
	m_rotOld(0.0f),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemySnakeHead::~CEnemySnakeHead()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CEnemySnakeHead::Init()
{
	m_time = 0;

	// 初期化
	CEnemy::Init();

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemySnakeHead::Uninit()
{
	for (int i = 0; i < MAX_BODY; i++)
	{
		if (m_pBody[i] == nullptr)
		{// nullチェック
			continue;
		}

		// 解放
		m_pBody[i]->Release();
		m_pBody[i] = nullptr;
	}

	if (m_pBody != nullptr)
	{// nullチェック
		delete[] m_pBody;
		m_pBody = nullptr;
	}

	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemySnakeHead::Update()
{
	m_time++;

	// 移動量の設定
	SetMove();

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// 前回の位置の保存
	m_posOld = pos;

	pos.x += m_move.x;
	pos.y += m_move.y;

	float size = (MAX_SIZE * 0.5f) + (CWall::GetWidth() * 0.5f);
	float wall = (CWall::GetLength() * 0.5f) - size;

	//	範囲内
	InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f));

	// 位置の設定
	CObject3D::SetPos(pos);

	// 前回の向きの保存
	m_rotOld = CObject3D::GetRot();

	float rot = atan2f(m_move.x, m_move.y);

	// 角度の正規化
	NormalizeAngle(&rot);

	// 向きの設定
	CObject3D::SetRot(rot);

	if (m_pBody[IDX_PARENT] != nullptr)
	{// nullチェック
		// 目的の位置の設定
		m_pBody[IDX_PARENT]->SetPosDest(m_posOld);

		//	前回の向きの設定
		m_pBody[IDX_PARENT]->SetRotOld(m_rotOld);
	}

	for (int i = 0; i < MAX_BODY; i++)
	{
		if (m_pBody[i] == nullptr || i == IDX_PARENT)
		{// nullチェック
			continue;
		}

		int parent = i - 1;
		D3DXVECTOR3 posOld = m_pBody[parent]->GetPosOld();

		// 目的の位置の設定
		m_pBody[i]->SetPosDest(posOld);

		float rotOld = m_pBody[parent]->GetRotOld();

		//	前回の向きの設定
		m_pBody[i]->SetRotOld(rotOld);
	}

	// 更新
	CEnemy::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemySnakeHead::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// 前回の位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CEnemySnakeHead::GetPosOld() const
{
	return m_posOld;
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemySnakeHead::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	m_posOld = pos;

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_icon_122380_256);

	// 移動量の設定
	SetMove();

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	m_pBody = new CEnemySnakeBody*[MAX_BODY];

	for (int i = 0; i < MAX_BODY; i++)
	{
		if (m_pBody[i] == nullptr)
		{
			continue;
		}

		// 生成
		m_pBody[i] = CEnemySnakeBody::Create();
		m_pBody[i]->SetPos(pos);
		m_pBody[i]->SetPosDest(pos);
	}
}

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CEnemySnakeHead::SetMove()
{
	float fRotMove, fRotDest, fRotDiff;

	// 現在の移動方向(角度)
	fRotMove = atan2f(m_move.x, m_move.y);

	CPlayer* pPlayer = CApplication::GetInstanse()->GetPlayer();

	// 目的の移動方向(角度)
	fRotDest = atan2f(pPlayer->GetPos().x - GetPos().x, pPlayer->GetPos().y - GetPos().y);

	fRotDiff = fRotDest - fRotMove;	// 目的の移動方向までの差分

	// 角度の正規化
	NormalizeAngle(&fRotDiff);

	fRotMove += fRotDiff;	// 移動方向(角度)の補正

	// 角度の正規化
	NormalizeAngle(&fRotMove);

	float sinCurve = sinf(D3DXToRadian(m_time * AMPLITUDE_SPEED)) * AMPLITUDE_WIDTH;

	m_move.x = (sinf(fRotMove) * MAX_MOVE) + (sinCurve * sinf(fRotMove + D3DX_PI * 0.5f));
	m_move.y = (cosf(fRotMove) * MAX_MOVE) + (sinCurve * cosf(fRotMove + D3DX_PI * 0.5f));
	//m_move *= 2.0f;
}
