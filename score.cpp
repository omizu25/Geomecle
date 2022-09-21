//**************************************************
// 
// score.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "score.h"
#include "number_manager.h"
#include "application.h"
#include "mode.h"
#include "game.h"
#include "mul.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CScore::STD_WIDTH = 40.0f;
const float CScore::STD_HEIGHT = 50.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CScore* CScore::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	CScore* pScore = nullptr;

	pScore = new CScore;

	if (pScore != nullptr)
	{// nullチェック
		// 初期化
		pScore->Init(pos, size);
	}

	return pScore;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CScore::CScore() :
	m_pNumber(nullptr),
	m_score(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CScore::~CScore()
{
	assert(m_pNumber == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CScore::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_score = 0;

	// 数の生成
	m_pNumber = CNumberManager::Create(pos, size, 0);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CScore::Uninit()
{
	// 解放
	m_pNumber->Release();

	m_pNumber = nullptr;
}

//--------------------------------------------------
// 加算
//--------------------------------------------------
void CScore::Add(int score)
{
	CMode* pMode = CApplication::GetInstanse()->GetMode();

	if (CMode::MODE_GAME == pMode->Get())
	{// ゲーム中
		CGame* pGame = (CGame*)pMode;

		// 倍率の加算
		int mul = pGame->GetMul()->Get();

		m_score += score + (score * mul);

		// 数の変更
		m_pNumber->ChangeNumber(m_score);
	}
	else
	{
		m_score += score;
	}
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CScore::Set(int score)
{
	m_score = score;

	// 数の変更
	m_pNumber->ChangeNumber(m_score);
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CScore::Get()
{
	return m_score;
}
