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

//--------------------------------------------------
// 生成
//--------------------------------------------------
CScore* CScore::Create(const D3DXVECTOR3& pos)
{
	CScore* pScore = nullptr;

	pScore = new CScore;

	if (pScore != nullptr)
	{// nullチェック
		// 初期化
		pScore->Init(pos);
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
void CScore::Init(const D3DXVECTOR3& pos)
{
	m_score = 0;

	// 数の生成
	m_pNumber = CNumberManager::Create(pos, 0);
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
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

	// 倍率の加算
	int mul = pGame->GetMul()->Get();

	m_score += score + (score * mul);

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
