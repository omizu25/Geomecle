//**************************************************
// 
// player.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PLAYER_H_	//このマクロ定義がされてなかったら
#define _PLAYER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object2D.h"

//==================================================
// 定義
//==================================================
class CPlayer : public CObject2D
{
	/* ↓静的メンバ関数↓ */
public:
	static CPlayer* Create();		// 生成
	static void ChangeNumShot();	// 放つ数の変更
	static int GetNumShot();		// 放つ数の取得

	/* ↓静的メンバ変数↓ */
private:
	static int m_numShot;	// 放つ数

	/* ↓メンバ関数↓ */
public:
	CPlayer();				// デフォルトコンストラクタ
	 ~CPlayer() override;	// デストラクタ

public:
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画
	const D3DXVECTOR3& GetPos() const override;	// 位置の取得

private:
	void Move();	// 移動
};

#endif // !_OBJECT_H_
