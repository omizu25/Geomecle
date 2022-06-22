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
class CInput;
class CTexture;
class CPlayer;

//==================================================
// 定義
//==================================================
class CApplication
{
public: /* 定義 */
	static const int SCREEN_WIDTH = 1280;	// スクリーンの幅
	static const int SCREEN_HEIGHT = 720;	// スクリーンの高さ
	static const bool FULL_SCREEN;			// フルスクリーンにするかどうか

public:
	static CApplication* GetInstanse();	// インスタンスの取得

private: /* 静的メンバ変数 */
	static CApplication* m_pApplication;	// 自分のクラス

private:
	CApplication();		// デフォルトコンストラクタ

public:
	~CApplication();	// デストラクタ

public: /* メンバ関数 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画
	LPDIRECT3DDEVICE9 GetDevice();	// デバイスの取得
	CTexture* GetTexture();			// テクスチャの情報の取得
	CPlayer* GetPlayer();			// プレイヤーの情報の取得

private: /* メンバ変数 */
	CRenderer* m_pRenderer;	// レンダラーの情報
	CInput* m_pInput;		// 入力の情報
	CTexture* m_pTexture;	// テクスチャの情報
	CPlayer* m_pPlayer;		// プレイヤーの情報
};

#endif // !_APPLICATION_H_
