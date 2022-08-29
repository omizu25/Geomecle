//**************************************************
// 
// number_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _NUMBER_MANAGER_H_	//このマクロ定義がされてなかったら
#define _NUMBER_MANAGER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 前方宣言
//==================================================
class CNumber;

//==================================================
// 定義
//==================================================
class CNumberManager
{
	/* ↓定義↓ */
public:
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値

private:
	static const int MAX_DIGIT = 8;	// 桁の最大数

	/* ↓静的メンバ関数↓ */
public:
	static CNumberManager* Create(const D3DXVECTOR3& pos, int value, bool zero);	// 生成

	/* ↓メンバ関数↓ */
public:
	CNumberManager();	// デフォルトコンストラクタ
	~CNumberManager();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos);	// 初期化
	void Uninit();	// 終了
	void Release();	// 解放
	void ChangeNumber(int value);	// 数の変更

private:
	void ZeroDraw();	// ゼロの描画

	/* ↓メンバ変数↓ */
private:
	CNumber* m_number[MAX_DIGIT];	// 数
	int m_value;	// 値
	bool m_zero;	// ゼロを描画するかどうか
};

#endif // !_NUMBER_MANAGER_H_
