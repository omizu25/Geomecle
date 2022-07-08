//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CTexture
{
	/* ↓定義↓ */
public:
	enum ELabel
	{
		LABEL_icon_122380_256 = 0,	// 仮画像1
		LABEL_icon_122540_256,		// 仮画像2
		LABEL_Homing,				// ホーミング
		LABEL_PaperAirplane,		// 紙飛行機
		LABEL_MAX,
		LABEL_NONE,	// 使用しない
	};

	static const char* FILE_NAME[];	// ファイルパス

	/* ↓メンバ関数↓ */
public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public:
	void LoadAll();				// 全ての読み込み
	void Load(ELabel label);	// 指定の読み込み
	void ReleaseAll();			// 全ての破棄
	void Release(ELabel label);	// 指定の破棄
	LPDIRECT3DTEXTURE9 GetTexture(ELabel label);	// 情報の取得

	/* ↓メンバ変数↓ */
private:
	LPDIRECT3DTEXTURE9 s_pTexture[LABEL_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_
