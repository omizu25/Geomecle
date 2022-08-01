//**************************************************
// 
// effect.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_H_	//このマクロ定義がされてなかったら
#define _EFFECT_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object.h"

//==================================================
// 定義
//==================================================
class CEffect : public CObject
{
	/* 定義 */
public:
	static const float STD_SIZE;	// サイズの標準値

private:
	static const float STD_MOVE;	// 移動量の標準値

	/* ↓静的メンバ関数↓ */
public:
	static CEffect* Create(const D3DXVECTOR3& pos, float rot);	// 生成
	static int GetNumAll();	// 総数の取得

	/* ↓静的メンバ変数↓ */
private:
	static int m_numAll;	// 総数

	/* ↓メンバ関数↓ */
public:
	CEffect();				// デフォルトコンストラクタ
	~CEffect() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	const D3DXVECTOR3& GetPos() const;	// 位置の取得
	const D3DXCOLOR& GetCol() const;	// 色の取得

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_pos;	// 位置
	D3DXVECTOR3 m_move;	// 移動量
	D3DXCOLOR m_col;	// 色
};

#endif // !_EFFECT_H_
