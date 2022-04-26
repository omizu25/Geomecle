//**************************************************
//
// FPD制作 ( game.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "rectangle.h"
#include "rectangle3D.h"
#include "color.h"
#include "time.h"
#include "utility.h"
#include "player.h"
#include "camera.h"
#include "bg.h"

#include <assert.h>

//==================================================
// スタティック変数
//==================================================
namespace
{
EGameState	s_gameState = GAMESTATE_NONE;	// ゲームの状態
int			s_counterState;					// 状態管理カウンター
bool		s_pause = false;				// ポーズ中かどうか [してる  : true してない  : false]
}// namesapceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitGame(void)
{
	// 背景の初期化
	InitBG();

	// プレイヤーの初期化
	InitPlayer();

	// カメラの初期化
	InitCamera();

	s_gameState = GAMESTATE_SAMPLE;	// サンプル状態に設定

	s_counterState = 0;	// カウンターの初期化

	s_pause = false;	// ポーズ解除
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitGame(void)
{
	// 背景の終了
	UninitBG();

	// カメラの終了
	UninitCamera();

	// プレイヤーの終了
	UninitPlayer();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateGame(void)
{
	// プレイヤーの更新
	UpdatePlayer();

	// カメラの更新
	UpdateCamera();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	// 3D矩形の描画
	DrawRectangle3D();

	// 矩形の描画
	DrawRectangle();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetGameState(EGameState inState)
{
	assert(inState >= 0 && inState < GAMESTATE_MAX);

	s_gameState = inState;
	s_counterState = 0;
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
EGameState GetGameState(void)
{
	return s_gameState;
}

//--------------------------------------------------
// ポーズの有効無効設定
//--------------------------------------------------
void SetEnablePause(bool inPause)
{
	s_pause = inPause;
}

//--------------------------------------------------
// ポーズの有効無効取得
//--------------------------------------------------
bool GetEnablePause(void)
{
	return s_pause;
}
