//**************************************************
// 
// enemy_snake_head.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_snake_body.h"
#include "utility.h"
#include "wall.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemySnakeBody::STD_SIZE = 15.0f;
const int CEnemySnakeBody::MOVE_INTERVAL = 2;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEnemySnakeBody* CEnemySnakeBody::Create()
{
	CEnemySnakeBody* pBody = nullptr;

	pBody = new CEnemySnakeBody;

	if (pBody != nullptr)
	{// nullチェック
		pBody->Init();
	}

	return pBody;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemySnakeBody::CEnemySnakeBody() :
	m_time(0),
	m_rotOld(0.0f),
	m_posDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemySnakeBody::~CEnemySnakeBody()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CEnemySnakeBody::Init()
{
	m_time = 0;

	// 初期化
	CObject3D::Init();

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_icon_122540_256);

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemySnakeBody::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemySnakeBody::Update()
{
	m_time++;

	if ((m_time % MOVE_INTERVAL) != 0)
	{// 一定間隔のタイミングではない
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// 前回の位置の保存
	m_posOld = pos;

	// ホーミング
	Homing(&pos, pos, m_posDest, 10.0f);

	float size = (STD_SIZE * 0.5f) + (CWall::GetWidth() * 0.5f);
	float wall = (CWall::GetLength() * 0.5f) - size;

	//	範囲内
	InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f));

	// 位置の設定
	CObject3D::SetPos(pos);

	// 向きの設定
	CObject3D::SetRot(m_rotOld);

	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemySnakeBody::Draw()
{
	// 描画
	CObject3D::Draw();
}

//--------------------------------------------------
// 目的の位置の設定
//--------------------------------------------------
void CEnemySnakeBody::SetPosDest(const D3DXVECTOR3& posDest)
{
	m_posDest = posDest;
}

//--------------------------------------------------
// 前回の位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CEnemySnakeBody::GetPosOld() const
{
	return m_posOld;
}

//--------------------------------------------------
// 前回の向きの設定
//--------------------------------------------------
void CEnemySnakeBody::SetRotOld(float rotOld)
{
	m_rotOld = rotOld;
}

//--------------------------------------------------
// 前回の向きの取得
//--------------------------------------------------
float CEnemySnakeBody::GetRotOld()
{
	return m_rotOld;
}
