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
CScore::CScore()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CScore::~CScore()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CScore::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// 初期化
	CNumberManager::Init(pos, size);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CScore::Uninit()
{
	// 終了
	CNumberManager::Uninit();
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

		// 加算
		CNumberManager::Add(score + (score * pGame->GetMul()->Get()));
	}
	else
	{
		// 加算
		CNumberManager::Add(score);
	}
}
