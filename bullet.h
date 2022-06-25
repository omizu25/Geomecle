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
#include "object2D.h"
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CBullet : public CObject2D
{
	/* ↓静的メンバ関数↓ */
public:
	static CBullet* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CBullet();				// デフォルトコンストラクタ
	~CBullet() override;	// デストラクタ

public:
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
	int m_life;			// 寿命
};

#endif // !_BULLET_H_
