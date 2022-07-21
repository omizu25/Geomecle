//**************************************************
// 
// result.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RESULT_H_	//このマクロ定義がされてなかったら
#define _RESULT_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 定義
//==================================================
class CResult : public CMode
{
	/* ↓メンバ関数↓ */
public:
	CResult();				// デフォルトコンストラクタ
	CResult(EMode mode);	// コンストラクタ
	~CResult() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画
};

#endif // !_RESULT_H_
