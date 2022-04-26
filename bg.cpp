//**************************************************
//
// Hackathon ( bg.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "rectangle3D.h"
#include "bg.h"
#include "texture.h"
#include "color.h"
#include "input.h"
#include "utility.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const float	BG_SIZE = 30.0f;		// 背景のサイズ
const float	BG_LENGTH = 1200.0f;	// 背景の長さ
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_idxTop;		// 上辺の3D矩形のインデックス
int	s_idxBottom;	// 下辺の3D矩形のインデックス
int	s_idxLeft;		// 左辺の3D矩形のインデックス
int	s_idxRight;		// 右辺の3D矩形のインデックス
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitBG(void)
{
	{// 上辺
		// 矩形の設定
		s_idxTop = SetRectangle3D(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(BG_LENGTH, BG_SIZE, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, BG_LENGTH * 0.5f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle3D(s_idxTop, pos);

		// 矩形のサイズの設定
		SetSizeRectangle3D(s_idxTop, size);
	}

	{// 下辺
		// 矩形の設定
		s_idxTop = SetRectangle3D(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(BG_LENGTH, BG_SIZE, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, -BG_LENGTH * 0.5f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle3D(s_idxTop, pos);

		// 矩形のサイズの設定
		SetSizeRectangle3D(s_idxTop, size);
	}

	{// 左辺
		// 矩形の設定
		s_idxTop = SetRectangle3D(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(BG_SIZE, BG_LENGTH, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(-BG_LENGTH * 0.5f, 0.0f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle3D(s_idxTop, pos);

		// 矩形のサイズの設定
		SetSizeRectangle3D(s_idxTop, size);
	}

	{// 右辺
		// 矩形の設定
		s_idxTop = SetRectangle3D(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(BG_SIZE, BG_LENGTH, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(BG_LENGTH * 0.5f, 0.0f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle3D(s_idxTop, pos);

		// 矩形のサイズの設定
		SetSizeRectangle3D(s_idxTop, size);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitBG(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateBG(void)
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawBG(void)
{
}
