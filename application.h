//**************************************************
// 
// application.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _APPLICATION_H_	//このマクロ定義がされてなかったら
#define _APPLICATION_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 前方宣言
//==================================================
class CRenderer;
class CPlayer;
class CInput;

//==================================================
// 定義
//==================================================
class CApplication
{
public: /* 定義 */
	static const int SCREEN_WIDTH = 1280;	// スクリーンの幅
	static const int SCREEN_HEIGHT = 720;	// スクリーンの高さ

public: /* 静的メンバ関数 */
	static LPDIRECT3DDEVICE9 GetDevice();	// デバイスの取得
	static CPlayer* GetPlayer();			// プレイヤーの取得

private: /* 静的メンバ変数 */
	static CRenderer* m_pRenderer;	// レンダラーの情報
	static CInput* m_pInput;		// 入力の情報

public:
	CApplication();				// デフォルトコンストラクタ
	virtual ~CApplication();	// デストラクタ

public: /* メンバ関数 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画
};

#endif // !_APPLICATION_H_
