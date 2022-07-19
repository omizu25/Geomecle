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
#include <vector>

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
private:
	static const int MAX_DIGIT = 8;	// 桁の最大数
	static const float STD_WIDTH;	// 幅の標準値
	static const float STD_HEIGHT;	// 高さの標準値

	/* ↓メンバ関数↓ */
public:
	CNumberManager();	// デフォルトコンストラクタ
	~CNumberManager();	// デストラクタ

public:
	void Init(const D3DXVECTOR3& pos, int value);	// 初期化
	void Uninit();	// 終了
	void ChangeNumber(int value);	// 数の変更

private:
	int GetDigit(int value);	// 桁の取得

	/* ↓メンバ変数↓ */
private:
	CNumber* m_number[MAX_DIGIT];	// 数
	int m_value;	// 値
};

#endif // !_NUMBER_MANAGER_H_
