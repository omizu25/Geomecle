//**************************************************
// 
// bullet.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _BULLET_H_	//このマクロ定義がされてなかったら
#define _BULLET_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CBullet : public CObject3D
{
	/* 定義 */
private:
	static const int SHOT_INTERVAL;	// 発射の間隔
	static const float MAX_SIZE;	// サイズの最大値
	static const float MAX_MOVE;	// 移動量の最大値
	static const float MAX_INERTIA;	// 慣性の最大値

	/* ↓静的メンバ関数↓ */
public:
	static CBullet* Create(float rot);	// 生成
	static void Shot();	// 発射

	/* ↓静的メンバ変数↓ */
private:
	static int m_time;	// 時間
	static float m_dest;
	static float m_now;

	/* ↓メンバ関数↓ */
public:
	CBullet();				// デフォルトコンストラクタ
	~CBullet() override;	// デストラクタ

public:
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画

private:
	void SetMove(float rot);	// 移動量の設定

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
};

#endif // !_BULLET_H_
