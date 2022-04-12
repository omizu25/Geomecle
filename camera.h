//**************************************************
//
// 3Dゲーム制作 ( camera.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _CAMERA_H_		// このマクロ定義がされてなかったら
#define _CAMERA_H_		// ２重インクルード防止のマクロ定義

//==================================================
// 構造体
//==================================================
struct Camera
{
	D3DXVECTOR3		posV;			// 現在の視点
	D3DXVECTOR3		posR;			// 現在の注視点
	D3DXVECTOR3		posVDest;		// 目的の視点
	D3DXVECTOR3		posRDest;		// 目的の注視点
	D3DXVECTOR3		vecU;			// 上方向ベクトル
	D3DXVECTOR3		rot;			// 現在の向き
	D3DXVECTOR3		rotDest;		// 目的の向き
	D3DXMATRIX		mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX		mtxView;		// ビューマトリックス
	float			fDistance;		// 視点から注視点の距離
};

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitCamera(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitCamera(void);

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateCamera(void);

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetCamera(void);

//--------------------------------------------------
// 取得
// 返値  : Camera / カメラの情報
//--------------------------------------------------
Camera *GetCamera(void);

#endif // !_CAMERA_H_
