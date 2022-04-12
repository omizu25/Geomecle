//**************************************************
// 
// Hackathon ( rectangle3D.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RECTANGLE3D_H_	//このマクロ定義がされてなかったら
#define _RECTANGLE3D_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "texture.h"

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitRectangle3D(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitRectangle3D(void);

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawRectangle3D(void);

//--------------------------------------------------
// 設定
// 引数  : TEXTURE texture / 列挙型 種類
//--------------------------------------------------
int SetRectangle3D(TEXTURE texture);

//--------------------------------------------------
// 設定 [ テクスチャあり ]
// 引数  : LPDIRECT3DTEXTURE9 pTexture / テクスチャ
//--------------------------------------------------
int SetRectangle3DWithTex(LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// 使うのを止める
// 引数  : int nIdx / インデックス
//--------------------------------------------------
void StopUseRectangle3D(int nIdx);

//--------------------------------------------------
// 位置の設定
// 引数1  : int nIdx / インデックス
// 引数2  : D3DXVECTOR3 &pos / 中心の位置
//--------------------------------------------------
void SetPosRectangle3D(int nIdx, const D3DXVECTOR3 &pos);

//--------------------------------------------------
// 向きの設定
// 引数1  : int nIdx / インデックス
// 引数2  : D3DXVECTOR3 &rot / 向き
//--------------------------------------------------
void SetRotRectangle3D(int nIdx, const D3DXVECTOR3 &rot);

//--------------------------------------------------
// サイズの設定
// 引数1  : int nIdx / インデックス
// 引数2  : D3DXVECTOR3 &size / サイズ
//--------------------------------------------------
void SetSizeRectangle3D(int nIdx, const D3DXVECTOR3 &size);

//--------------------------------------------------
// 色の設定
// 引数1  : int nIdx / インデックス
// 引数2  : D3DXCOLOR &color / 色
//--------------------------------------------------
void SetColorRectangle3D(int nIdx, const D3DXCOLOR &color);

//--------------------------------------------------
// テクスチャ座標の設定
// 引数1  : int nIdx / インデックス
// 引数2  : D3DXVECTOR2 &texU / x = 左端, y = 右端
// 引数3  : D3DXVECTOR2 &texV / x = 上端, y = 下端
//--------------------------------------------------
void SetTexRectangle3D(int nIdx, const D3DXVECTOR2 &texU, const D3DXVECTOR2 &texV);

//--------------------------------------------------
// 描画するかどうか
// 引数1  : int nIdx / インデックス
// 引数2  : bool bDraw / 描画するかどうか
//--------------------------------------------------
void SetDrawRectangle3D(int nIdx, bool bDraw);

//--------------------------------------------------
// 加算合成するかどうか
// 引数1  : int nIdx / インデックス
// 引数2  : bool bDraw / 加算合成するかどうか
//--------------------------------------------------
void SetAddRectangle3D(int nIdx, bool bAdd);

//--------------------------------------------------
// テクスチャの変更
// 引数1  : int nIdx / インデックス
// 引数2  : TEXTURE texture / 列挙型 種類
//--------------------------------------------------
void ChangeTextureRectangle3D(int nIdx, TEXTURE texture);

//--------------------------------------------------
// テクスチャの変更 [ テクスチャあり ]
// 引数1  : int nIdx / インデックス
// 引数2  : TEXTURE texture / 列挙型 種類
//--------------------------------------------------
void ChangeTextureRectangle3DWithTex(int nIdx, LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// 頂点バッファの取得
// 引数  : int nIdx / インデックス
// 返値  : LPDIRECT3DVERTEXBUFFER9 / 頂点バッファ
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffRectangle3D(int nIdx);

#endif // !_RECTANGLE3D_H_
