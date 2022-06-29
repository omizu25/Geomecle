//**************************************************
// 
// enemy.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_H_	//このマクロ定義がされてなかったら
#define _ENEMY_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CEnemy : public CObject3D
{
	/* ↓静的メンバ関数↓ */
public:
	static CEnemy* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CEnemy();				// デフォルトコンストラクタ
	 ~CEnemy() override;	// デストラクタ

public:
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画
};

#endif // !_ENEMT_H_
