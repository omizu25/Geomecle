//**************************************************
// 
// object3D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT3D_H_	//このマクロ定義がされてなかったら
#define _OBJECT3D_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "texture.h"
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CObject3D : public CObject
{
	/* ↓定義↓ */
private:
	struct VERTEX_3D
	{// 頂点データ
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	};

	static const DWORD FVF_VERTEX_3D;	// 頂点フォーマット
	static const int NUM_VERTEX;		// 頂点の数
	static const int NUM_POLYGON;		// ポリゴンの数
	static const float POLYGON_SIZE;	// ポリゴンのサイズ

	/* ↓静的メンバ関数↓ */
public:
	static CObject3D* Create();	// 生成

	/* ↓メンバ関数↓ */
public:
	CObject3D();			// デフォルトコンストラクタ
	~CObject3D() override;	// デストラクタ

public: 
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画
	void SetPos(const D3DXVECTOR3& pos) override;	// 位置の設定
	const D3DXVECTOR3& GetPos() const override;		// 位置の取得
	void SetSize(float size) override;	// サイズの設定
	float GetSize() override;			// サイズの取得
	void SetTexture(CTexture::ELabel texture);					// テクスチャの設定
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v);	// テクスチャ座標の設定

	/* ↓メンバ変数↓ */
private:
	float m_rot;		// 向き
	float m_size;		// サイズ
	D3DXVECTOR3 m_pos;	// 位置
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	CTexture::ELabel m_texture;			// テクスチャの列挙型
};

#endif // !_OBJECT3D_H_
