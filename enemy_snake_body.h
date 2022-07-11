//**************************************************
// 
// enemy_snake_body.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_SNAKE_BODY_H_	//このマクロ定義がされてなかったら
#define _ENEMY_SNAKE_BODY_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CEnemySnakeHead : public CObject3D
{
	/* 定義 */
private:
	static const float MAX_SIZE;		// サイズの最大値
	static const float MAX_MOVE;		// 移動量の最大値
	static const float MAX_AMPLITUDE;	// 振幅の最大値

	/* ↓メンバ関数↓ */
public:
	CEnemySnakeHead();				// デフォルトコンストラクタ
	~CEnemySnakeHead() override;	// デストラクタ

public:
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画

	/* メンバ変数 */
private:
	int m_time;			// タイム
	D3DXVECTOR3 m_move;	// 移動量
};

#endif // !_ENEMY_SNAKE_BODY_H_
