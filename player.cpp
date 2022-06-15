//**************************************************
//
// Hackathon ( player.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "rectangle3D.h"
#include "player.h"
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
const float	PLAYER_SIZE = 30.0f;	// プレイヤーのサイズ

/* プレイヤー */
struct SPlayer
{
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3	move;		// 移動量
	float		rot;		// 向き
	float		rotDest;	// 目的の向き
	int			idx;		// 3D矩形のインデックス
};
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
SPlayer	s_player;	// プレイヤーの情報
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
void Move(void);
void Rot(void);
void MovingLimit(void);
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitPlayer(void)
{
	//メモリのクリア
	memset(&s_player, 0, sizeof(s_player));

	// 3D矩形の設定
	s_player.idx = SetRectangle3D(TEXTURE_icon_122380_256);

	D3DXVECTOR3 size = D3DXVECTOR3(PLAYER_SIZE, PLAYER_SIZE, 0.0f);

	// 3D矩形の位置の設定
	SetSizeRectangle3D(s_player.idx, size);

	// 3D矩形の色の設定
	SetColorRectangle3D(s_player.idx, GetColor(COLOR_LIGHTBLUE));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitPlayer(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdatePlayer(void)
{
	// 移動
	Move();

	// 回転
	Rot();

	// 移動制限
	MovingLimit();

	// 矩形の位置の設定
	SetPosRectangle3D(s_player.idx, s_player.pos);

	// 矩形の向きの設定
	SetRotRectangle3D(s_player.idx, s_player.rot);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawPlayer(void)
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

	s_player.rotDest = atan2f(vec.y, vec.x) - (D3DX_PI * 0.5f);
	s_player.move += vec * 7.0f;

	// 移動
	s_player.pos.x += s_player.move.x;
	s_player.pos.y += s_player.move.y;

	// 慣性・移動量を更新 (減衰させる)
	s_player.move.x += (0.0f - s_player.move.x) * 1.0f;
	s_player.move.y += (0.0f - s_player.move.y) * 1.0f;
}

//--------------------------------------------------
// 回転
//--------------------------------------------------
void Rot(void)
{
	if (s_player.rot == s_player.rotDest)
	{// 回転してない
		return;
	}

	// 角度の正規化
	NormalizeAngle(&s_player.rotDest);

	float rot = s_player.rotDest - s_player.rot;

	// 角度の正規化
	NormalizeAngle(&rot);

	//慣性・向きを更新 (減衰させる)
	s_player.rot += rot * 0.25f;

	// 角度の正規化
	NormalizeAngle(&s_player.rot);
}

//--------------------------------------------------
// 移動制限
//--------------------------------------------------
void MovingLimit(void)
{
	// 背景のサイズの取得
	float sizeBG = GetSizeBG();

	float plus = sizeBG - PLAYER_SIZE;
	float minus = (sizeBG * -1.0f) + PLAYER_SIZE;

	if (s_player.pos.y >= plus)
	{// 上
		s_player.pos.y = plus;
	}
	else if (s_player.pos.y <= minus)
	{// 下
		s_player.pos.y = minus;
	}

	if (s_player.pos.x >= plus)
	{// 右
		s_player.pos.x = plus;
	}
	else if (s_player.pos.x <= minus)
	{// 左
		s_player.pos.x = minus;
	}
}
}// namespaceはここまで
