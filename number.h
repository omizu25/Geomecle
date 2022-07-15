//**************************************************
// 
// number.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _NUMBER_H_	//このマクロ定義がされてなかったら
#define _NUMBER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object2D.h"

//==================================================
// 定義
//==================================================
class CNumber : public CObject2D
{
	/* ↓静的メンバ関数↓ */
public:
	static CNumber* Create(const D3DXVECTOR3& pos, int number);	// 生成

	/* ↓メンバ関数↓ */
public:
	CNumber();				// デフォルトコンストラクタ
	~CNumber() override;	// デストラクタ

public:
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
};

#endif // !_NUMBER_H_
