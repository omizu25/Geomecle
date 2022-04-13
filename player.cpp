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

#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const float	PLAYER_SIZE = 30.0f;	// プレイヤーのサイズ

/* プレイヤー */
struct Player
{
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3	rot;		// 向き
	D3DXVECTOR3	rotDest;	// 目的の向き
	D3DXVECTOR3	move;		// 移動量
};
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int		s_idx3DPlayer;	// 3D矩形のインデックス
Player	s_player;		// プレイヤーの情報
}// namespaceはここまで

//==================================================
// スタティック関数プロトタイプ宣言
//==================================================
namespace
{
void Rot(void);
}// namespaceはここまで


//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitPlayer(void)
{
	//メモリのクリア
	ZeroMemory(&s_player, sizeof(s_player));

	// 3D矩形の設定
	s_idx3DPlayer = SetRectangle3D(TEXTURE_NONE);

	D3DXVECTOR3 size = D3DXVECTOR3(PLAYER_SIZE, PLAYER_SIZE, 0.0f);

	// 3D矩形の位置の設定
	SetSizeRectangle3D(s_idx3DPlayer, size);
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
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (GetMoveKeyPress(MOVE_KEY_LEFT))
	{// 左キーが押された
		vec.x -= 1.0f;
	}
	if (GetMoveKeyPress(MOVE_KEY_RIGHT))
	{// 右キーが押された
		vec.x += 1.0f;
	}
	if (GetMoveKeyPress(MOVE_KEY_UP))
	{// 上キーが押された
		vec.y += 1.0f;
	}
	if (GetMoveKeyPress(MOVE_KEY_DOWN))
	{// 下キーが押された
		vec.y -= 1.0f;
	}

	// ベクトルの正規化
	D3DXVec3Normalize(&vec, &vec);

	s_player.rotDest.y = atan2f(vec.x, vec.y) + D3DX_PI;
	s_player.move += vec * 5.0f;

	// 移動
	s_player.pos.x += s_player.move.x;
	s_player.pos.y += s_player.move.y;

	// 慣性・移動量を更新 (減衰させる)
	s_player.move.x += (0.0f - s_player.move.x) * 1.0f;
	s_player.move.y += (0.0f - s_player.move.y) * 1.0f;
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
// 回転
//--------------------------------------------------
void Rot(void)
{
	D3DXVECTOR3 angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 角度の正規化
	NormalizeAngle(&s_player.rotDest.z);

	angle.z = s_player.rotDest.z - s_player.rot.z;

	// 角度の正規化
	NormalizeAngle(&angle.z);

	//慣性・向きを更新 (減衰させる)
	s_player.rot.z += angle.z * 1.0f;

	// 角度の正規化
	NormalizeAngle(&s_player.rot.z);
}
}// namespaceはここまで
