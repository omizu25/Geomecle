//**************************************************
// 
// main.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MAIN_H_	//このマクロ定義がされてなかったら
#define _MAIN_H_	//２重インクルード防止のマクロ定義

//==================================================
// 前方宣言
//==================================================
class CRenderer;

//==================================================
// プロトタイプ宣言
//==================================================
#ifdef _DEBUG
//--------------------------------------------------
// FPS取得
// 返値 : int / FPS
//--------------------------------------------------
int GetFPS();
#endif // _DEBUG

//--------------------------------------------------
// レンダラーの取得
//--------------------------------------------------
CRenderer* GetRenderer();

#endif // !_MAIN_H_
