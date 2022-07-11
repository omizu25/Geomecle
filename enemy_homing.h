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
	/* ↓定義↓ */
private:
	static const int MAX_U;				// Uの最大数
	static const int ANIMATION_TIME;	// アニメーションの時間

	/* ↓メンバ関数↓ */
public:
	CEnemyHoming();				// デフォルトコンストラクタ
	~CEnemyHoming() override;	// デストラクタ

public:
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画

private:
	void Set(const D3DXVECTOR3& pos) override;	// 設定
	void SetTex();	// テクスチャ座標の設定

	/* ↓メンバ変数↓ */
private:
	int m_time;			// タイム
	int m_idxPattern;	// パターン番号
};

#endif // !_ENEMY_HOMING_H_
