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
#include "number_manager.h"
#include "utility.h"
#include "application.h"
#include "mode.h"
#include <assert.h>

//--------------------------------------------------
// 生成
//--------------------------------------------------
CTime* CTime::Create(const D3DXVECTOR3& pos, int start, int end)
{
	CTime* pTime = nullptr;

	pTime = new CTime;

	if (pTime != nullptr)
	{// nullチェック
		// 初期化
		pTime->Init(pos);
		pTime->SetStart(start);
		pTime->SetEnd(end);
	}

	return pTime;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTime::CTime() :
	m_pNumber(nullptr),
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
	assert(m_pNumber == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTime::Init(const D3DXVECTOR3& pos)
{
	m_start = 0;
	m_elapsed = 0;
	m_end = 0;

	// 数の生成
	m_pNumber = CNumberManager::Create(pos, 0);
	m_pNumber->SetZero(true);
	m_pNumber->SetZeroDigit(4);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTime::Uninit()
{
	// 解放
	m_pNumber->Release();

	m_pNumber = nullptr;
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
	m_pNumber->ChangeNumber(number);

	if (number <= 0)
	{// 時間切れ
		// モードの変更
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);
	}
}

//--------------------------------------------------
// 開始時間の設定
//--------------------------------------------------
void CTime::SetStart(int start)
{
	m_start = start;
}

//--------------------------------------------------
// 終了時間の設定
//--------------------------------------------------
void CTime::SetEnd(int end)
{
	m_end = end;
}
