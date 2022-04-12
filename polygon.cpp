//**************************************************
//
// Hackathon ( polygon.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "rectangle.h"
#include "rectangle3D.h"
#include "polygon.h"
#include "texture.h"
#include "color.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	idxPolygon2D;	// 2D矩形のインデックス
int	idxPolygon3D;	// 3D矩形のインデックス
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitPolygon(void)
{
	// 3D矩形の設定
	idxPolygon3D = SetRectangle3D(TEXTURE_NONE);

	D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	// 3D矩形の位置の設定
	SetSizeRectangle3D(idxPolygon3D, size);

	// 矩形の設定
	idxPolygon2D = SetRectangle(TEXTURE_NONE);

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	
	// 矩形の位置の設定
	SetPosRectangle(idxPolygon2D, pos, size);

	// 矩形の色の設定
	SetColorRectangle(idxPolygon2D, GetColor(COLOR_RED));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitPolygon(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdatePolygon(void)
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawPolygon(void)
{
}
