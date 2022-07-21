//**************************************************
// 
// title.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TITLE_H_	//このマクロ定義がされてなかったら
#define _TITLE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 定義
//==================================================
class CTitle : public CMode
{
	/* ↓メンバ関数↓ */
public:
	CTitle();			// デフォルトコンストラクタ
	CTitle(EMode mode);	// コンストラクタ
	~CTitle() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
};

#endif // !_TITLE_H_
