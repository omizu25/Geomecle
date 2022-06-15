//**************************************************
// 
// renderer.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RENDERER_H_	//このマクロ定義がされてなかったら
#define _RENDERER_H_	//２重インクルード防止のマクロ定義

//==================================================
// ライブラリーリンク
//==================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CRenderer
{
public: /* 定義 */
	static const int SCREEN_WIDTH = 1280;	// スクリーンの幅
	static const int SCREEN_HEIGHT = 720;	// スクリーンの高さ

	static const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);	// 頂点フォーマット

	struct VERTEX_2D
	{// 頂点データ
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	};

public:
	CRenderer();			// デフォルトコンストラクタ
	virtual ~CRenderer();	// デストラクタ

public: /* メンバ関数 */
	HRESULT Init(HWND hWnd, bool bWindow);	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画
	LPDIRECT3DDEVICE9 GetDevice();	// デバイスの取得

private:
#ifdef _DEBUG
	void DrawFPS();	// FPS表示
#endif // _DEBUG

private: /* メンバ変数 */
	LPDIRECT3D9 m_pD3D;	// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Deviceオブジェクト

#ifdef _DEBUG
	LPD3DXFONT m_pFont;	// フォント
#endif // _DEBUG
};

#endif // !_RENDERER_H_
