//**************************************************
// 
// time.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "time.h"
#include "utility.h"
#include "application.h"
#include "mode.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CTime::STD_WIDTH = 50.0f;
const float CTime::STD_HEIGHT = 60.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CTime* CTime::Create(const D3DXVECTOR3& pos, int start, int end)
{
	CTime* pTime = nullptr;

	pTime = new CTime;

	if (pTime != nullptr)
	{// nullチェック
		D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

		// 初期化
		pTime->Init(pos, size);
		pTime->m_start = start;
		pTime->m_end = end;
	}

	return pTime;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTime::CTime() :
	m_start(0),
	m_elapsed(0),
	m_end(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTime::~CTime()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTime::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_start = 0;
	m_elapsed = 0;
	m_end = 0;

	// 初期化
	CNumberManager::Init(pos, size);
	CNumberManager::SetZero(true);
	CNumberManager::SetZeroDigit(4);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTime::Uninit()
{
	// 終了
	CNumberManager::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTime::Update()
{
	int time = timeGetTime();

	m_elapsed = (time - m_start) / 10;

	int number = m_end - m_elapsed;

	// 数の変更
	CNumberManager::Set(number);

	if (number <= 0)
	{// 時間切れ
		// モードの変更
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);
	}
}
