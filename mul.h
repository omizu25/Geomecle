//**************************************************
// 
// mul.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MUL_H_	//このマクロ定義がされてなかったら
#define _MUL_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 前方宣言
//==================================================
class CNumberManager;
class CObject2D;

//==================================================
// 定義
//==================================================
class CMul
{
	/* ↓定義↓ */
public:
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値
	static const float MUL_SIZE;	// 掛けるのサイズ

	/* ↓静的メンバ関数↓ */
public:
	static CMul* Create(const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CMul();	// デフォルトコンストラクタ
	~CMul();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos);	// 初期化
	void Uninit();	// 終了
	void Add();		// 加算
	int Get();		// 取得

	/* ↓メンバ変数↓ */
private:
	CNumberManager* m_pNumber;	// 数字
	CObject2D* m_pMul;			// 掛ける
	D3DXVECTOR3 m_pos;			// 位置
	int m_mul;					// 倍率
};

#endif // !_MUL_H_
