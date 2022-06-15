//**************************************************
//
// Hackathon ( snake.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "rectangle3D.h"
#include "snake.h"
#include "texture.h"
#include "color.h"
#include "input.h"
#include "utility.h"
#include "bg.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
/* 蛇 */
struct SSnake
{
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3	move;		// 移動量
	float		rot;		// 向き
	float		rotDest;	// 目的の向き
	float		size;		// サイズ
	int			idx;		// 3D矩形のインデックス
};
}// namespaceはここまで

 //==================================================
 // スタティック変数
 //==================================================
namespace
{
SSnake	s_snake;	// 蛇の情報
}// namespaceはここまで

 //==================================================
 // スタティック関数プロトタイプ宣言
 //==================================================
namespace
{
void Load(void);
void Move(void);
void Rot(void);
void MovingLimit(void);
}// namespaceはここまで

 //--------------------------------------------------
 // 初期化
 //--------------------------------------------------
void InitSnake(void)
{
	//メモリのクリア
	memset(&s_snake, 0, sizeof(s_snake));

	// 3D矩形の設定
	s_snake.idx = SetRectangle3D(TEXTURE_icon_122380_256);

	D3DXVECTOR3 size = D3DXVECTOR3(s_snake.size, s_snake.size, 0.0f);

	// 3D矩形の位置の設定
	SetSizeRectangle3D(s_snake.idx, size);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitSnake(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateSnake(void)
{
	// 移動
	Move();

	// 回転
	Rot();

	// 移動制限
	MovingLimit();

	// 矩形の位置の設定
	SetPosRectangle3D(s_snake.idx, s_snake.pos);

	// 矩形の向きの設定
	SetRotRectangle3D(s_snake.idx, s_snake.rot);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawSnake(void)
{
}

namespace
{
//--------------------------------------------------
// 移動
//--------------------------------------------------
void Move(void)
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_LEFT))
	{// 左キーが押された
		vec.x -= 1.0f;
	}
	if (pInput->Press(CInput::KEY_RIGHT))
	{// 右キーが押された
		vec.x += 1.0f;
	}
	if (pInput->Press(CInput::KEY_UP))
	{// 上キーが押された
		vec.y += 1.0f;
	}
	if (pInput->Press(CInput::KEY_DOWN))
	{// 下キーが押された
		vec.y -= 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// 移動してない
		return;
	}

	// ベクトルの正規化
	D3DXVec3Normalize(&vec, &vec);

	s_snake.rotDest = atan2f(vec.y, vec.x) - (D3DX_PI * 0.5f);
	s_snake.move += vec * 7.0f;

	// 移動
	s_snake.pos.x += s_snake.move.x;
	s_snake.pos.y += s_snake.move.y;

	// 慣性・移動量を更新 (減衰させる)
	s_snake.move.x += (0.0f - s_snake.move.x) * 1.0f;
	s_snake.move.y += (0.0f - s_snake.move.y) * 1.0f;
}

//--------------------------------------------------
// 回転
//--------------------------------------------------
void Rot(void)
{
	if (s_snake.rot == s_snake.rotDest)
	{// 回転してない
		return;
	}

	// 角度の正規化
	NormalizeAngle(&s_snake.rotDest);

	float rot = s_snake.rotDest - s_snake.rot;

	// 角度の正規化
	NormalizeAngle(&rot);

	//慣性・向きを更新 (減衰させる)
	s_snake.rot += rot * 0.25f;

	// 角度の正規化
	NormalizeAngle(&s_snake.rot);
}

//--------------------------------------------------
// 移動制限
//--------------------------------------------------
void MovingLimit(void)
{
	// 背景のサイズの取得
	float sizeBG = GetSizeBG();

	float plus = sizeBG - s_snake.size;
	float minus = (sizeBG * -1.0f) + s_snake.size;

	if (s_snake.pos.y >= plus)
	{// 上
		s_snake.pos.y = plus;
	}
	else if (s_snake.pos.y <= minus)
	{// 下
		s_snake.pos.y = minus;
	}

	if (s_snake.pos.x >= plus)
	{// 右
		s_snake.pos.x = plus;
	}
	else if (s_snake.pos.x <= minus)
	{// 左
		s_snake.pos.x = minus;
	}
}
}// namespaceはここまで
