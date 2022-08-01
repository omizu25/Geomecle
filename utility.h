//**************************************************
//
// utility.h
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _UTILITY_H_	// このマクロ定義がされてなかったら
#define _UTILITY_H_	// ２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

#ifdef _DEBUG
//==================================================
// デバッグ用
//==================================================
#include <crtdbg.h>

//--------------------------------------------------
// 出力にテキストを出力する。
// 引数  : pAngle / 角度
//--------------------------------------------------
#define DEBUG_PRINT(...) _RPT_BASE(_CRT_WARN, __FILE__, __LINE__, NULL, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) ((void)0)
#endif

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 角度の正規化
// 引数  : pAngle / 角度
//--------------------------------------------------
void NormalizeAngle(float *pAngle);

//--------------------------------------------------
// ホーミング
// 引数1  : D3DXVECTOR3 *pPosOut / 位置
// 引数2  : D3DXVECTOR3 &posNow / 現在の位置
// 引数3  : D3DXVECTOR3 &posDest / 目的の位置
// 引数4  : float fSpeed / 速さ
// 返値  : bool / 目的の位置に着いたかどうか
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed);

//--------------------------------------------------
// 小数点のランダム
// 引数1  : float fMax / 最大値
// 引数2  : float fMin / 最小値
// 返値  : float / ランダム値
//--------------------------------------------------
float FloatRandam(float fMax, float fMin);

//--------------------------------------------------
// 整数のランダム
// 引数1  : int nMax / 最大値
// 引数2  : int nMin / 最小値
// 返値  : int / ランダム値
//--------------------------------------------------
int IntRandam(int nMax, int nMin);

//--------------------------------------------------
// sinカーブの値が1.0f〜0.0fで帰ってくる
// 引数1  : int nTime / タイム
// 引数2  : float fCycle / 周期
// 返値  : float / 1.0f〜0.0fのsinカーブ
//--------------------------------------------------
float SinCurve(int nTime, float fCycle);

//--------------------------------------------------
// cosカーブの値が1.0f〜0.0fで帰ってくる
// 引数1  : int nTime / タイム
// 引数2  : float fCycle / 周期
// 返値  : float / 1.0f〜0.0fのcosカーブ
//--------------------------------------------------
float CosCurve(int nTime, float fCycle);

//--------------------------------------------------
// カーブの値が帰ってくる
// 引数1  : float fCurve / カーブ
// 引数2  : float fMax / 最大値
// 引数3  : float fMin / 最小値
// 返値  : float / カーブ
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin);

//--------------------------------------------------
// 範囲内
// 引数1  : D3DXVECTOR3* pPos / 位置
// 引数2  : D3DXVECTOR3 range / 範囲
// 返値  : bool / 範囲外に出たかどうか
//--------------------------------------------------
bool InRange(D3DXVECTOR3* pPos, const D3DXVECTOR3& range);

//--------------------------------------------------
// 範囲内で反射
// 引数1  : D3DXVECTOR3* pPos / 位置
// 引数2  : D3DXVECTOR3* pMove / 移動量
// 引数3  : D3DXVECTOR3 range / 範囲
// 返値  : bool / 範囲外に出たかどうか
//--------------------------------------------------
bool InRangeReflect(D3DXVECTOR3* pPos, D3DXVECTOR3* pMove, const D3DXVECTOR3& range);

//--------------------------------------------------
// 円の当たり判定
// 引数1  : D3DXVECTOR3& pos1 / １つ目の位置
// 引数2  : float radius1 / １つ目の半径
// 引数3  : D3DXVECTOR3& pos2 / ２つ目の位置
// 引数4  : float radius2 / ２つ目の半径
// 返値  : bool / 範囲外に出たかどうか
//--------------------------------------------------
bool CollisionCircle(const D3DXVECTOR3& pos1, float radius1, const D3DXVECTOR3& pos2, float radius2);

//--------------------------------------------------
// バッファのコピー
// 引数1  : IDirect3DVertexBuffer9* pBuf / バッファ
// 引数2  : void* pSrc / ソース
// 引数3  : unsigned size / ソースのサイズ
//--------------------------------------------------
void CopyBuf(IDirect3DVertexBuffer9* pBuf, void* pSrc, unsigned size);

#endif // !_UTILITY_H_
