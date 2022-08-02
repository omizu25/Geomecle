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
	CTitle() = delete;	// デフォルトコンストラクタ
	CTitle(EMode mode);	// コンストラクタ
	~CTitle() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	void Effect();	// エフェクト

	/* メンバ変数 */
private:
	D3DXCOLOR m_col;	// 色
	int m_time;			// 時間
	int m_partCnt;		// パーティクルカウンター
};

#endif // !_TITLE_H_
