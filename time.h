//**************************************************
// 
// time.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TIME_H_	//このマクロ定義がされてなかったら
#define _TIME_H_	//２重インクルード防止のマクロ定義

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
class CTime
{
	/* ↓定義↓ */
public:
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値

	/* ↓静的メンバ関数↓ */
public:
	static CTime* Create(const D3DXVECTOR3& pos, int start, int end);	// 生成

	/* ↓メンバ関数↓ */
public:
	CTime();	// デフォルトコンストラクタ
	~CTime();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos);	// 初期化
	void Uninit();						// 終了
	void Update();						// 更新
	void SetStart(int start);			// 開始時間の設定
	void SetEnd(int end);				// 終了時間の設定

	/* ↓メンバ変数↓ */
private:
	CNumberManager* m_pNumber;	// 数字
	int m_start;				// 開始
	int m_elapsed;				// 経過
	int m_end;					// 終了
};

#endif // !_TIME_H_
