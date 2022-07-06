//**************************************************
// 
// enemy_homing.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_HOMING_H_	//このマクロ定義がされてなかったら
#define _ENEMY_HOMING_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// 定義
//==================================================
class CEnemyHoming : public CEnemy
{
	/* ↓メンバ関数↓ */
public:
	CEnemyHoming();				// デフォルトコンストラクタ
	~CEnemyHoming() override;	// デストラクタ

public:
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画
	void Set(const D3DXVECTOR3& pos) override;	// 設定
};

#endif // !_ENEMY_HOMING_H_
