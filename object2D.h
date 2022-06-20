//**************************************************
// 
// object2D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT2D_H_	//このマクロ定義がされてなかったら
#define _OBJECT2D_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CObject2D : public CObject
{
public: /* 定義 */
	static const int MAX_POLYGON = 5;	// ポリゴンの最大数

public:
	static CObject2D* Create();	// 生成

public:
	CObject2D();			// デフォルトコンストラクタ
	~CObject2D() override;	// デストラクタ

public: /* メンバ関数 */
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画
	void SetPos(const D3DXVECTOR3& pos) override;	// 位置の設定
	D3DXVECTOR3 GetPos() override;					// 位置の取得
	void SetVtx();	// 頂点情報の設定

private: /* メンバ変数 */
	float m_rot;		// 向き
	float m_size;		// サイズ
	D3DXVECTOR3 m_pos;	// 位置
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
};

#endif // !_OBJECT2D_H_
