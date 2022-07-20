//**************************************************
// 
// mode.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "mode.h"

#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CMode::CMode() :
	m_mode(MODE_NONE),
	m_modeNext(MODE_NONE)
{

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CMode::~CMode()
{
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CMode::Set()
{
	if (m_modeNext == MODE_NONE)
	{// 次のモードが決まってない
		return;
	}

	switch (m_mode)
	{// 現在のモードの終了
	case MODE_TITLE:	// タイトル
		break;

	case MODE_GAME:		// ゲーム
		break;

	case MODE_RESULT:	// リザルト
		break;

	case MODE_NONE:
		/* 処理なし */
		break;

	default:
		assert(false);
		break;
	}

	m_mode = m_modeNext;	// 現在の画面(モード)を切り替える

	switch (m_modeNext)
	{// 次のモードの初期化
	case MODE_TITLE:	// タイトル
		break;

	case MODE_GAME:		// ゲーム
		break;

	case MODE_RESULT:	// リザルト
		break;

	case MODE_NONE:
	default:
		assert(false);
		break;
	}

	m_modeNext = MODE_NONE;
}

//--------------------------------------------------
// 変更
//--------------------------------------------------
void CMode::Change(EMode mode)
{
	assert(mode > MODE_NONE && mode < MODE_MAX);

	m_modeNext = mode;
}
