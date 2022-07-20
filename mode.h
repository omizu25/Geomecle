//**************************************************
// 
// mode.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODE_H_	//このマクロ定義がされてなかったら
#define _MODE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CMode
{
	/* ↓メンバ関数↓ */
public:
	CMode();	// デフォルトコンストラクタ
	~CMode();	// デストラクタ

public:
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画
	LPDIRECT3DDEVICE9 GetDevice();	// デバイスの取得

private:
#ifdef _DEBUG
	void DrawFPS();	// FPS表示
#endif // _DEBUG

	 /* ↓メンバ変数↓ */
private:
	LPDIRECT3D9 m_pD3D;				// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Deviceオブジェクト

#ifdef _DEBUG
	LPD3DXFONT m_pFont;	// フォント
#endif // _DEBUG
};

#endif // !_RENDERER_H_
