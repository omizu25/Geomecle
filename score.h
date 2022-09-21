//**************************************************
// 
// score.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _SCORE_H_	//このマクロ定義がされてなかったら
#define _SCORE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 前方宣言
//==================================================
class CNumberManager;

//==================================================
// 定義
//==================================================
class CScore
{
	/* ↓定義↓ */
public:
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値

	/* ↓静的メンバ関数↓ */
public:
	static CScore* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// 生成

	/* ↓メンバ関数↓ */
public:
	CScore();	// デフォルトコンストラクタ
	~CScore();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// 初期化
	void Uninit();			// 終了
	void Add(int score);	// 加算
	void Set(int score);	// 設定
	int Get();				// 取得

	/* ↓メンバ変数↓ */
private:
	CNumberManager* m_pNumber;	// 数字
	int m_score;				// スコア
};

#endif // !_SCORE_H_
