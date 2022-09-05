//**************************************************
// 
// game.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _GAME_H_	//このマクロ定義がされてなかったら
#define _GAME_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "mode.h"

//==================================================
// 前方宣言
//==================================================
class CTime;
class CScore;
class CMul;

//==================================================
// 定義
//==================================================
class CGame : public CMode
{
	/* ↓メンバ関数↓ */
public:
	CGame();			// デフォルトコンストラクタ
	~CGame() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

public:
	CScore* GetScore();	// スコアの取得
	CMul* GetMul();		// 倍率の取得

private:
	CTime* m_pTime;		// タイム
	CScore* m_pScore;	// スコア
	CMul* m_pMul;		// 倍率
};

#endif // !_GAME_H_
