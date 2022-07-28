//**************************************************
// 
// effect.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_H_	//このマクロ定義がされてなかったら
#define _EFFECT_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CEffect : public CObject3D
{
	/* 定義 */
private:
	// 頂点バッファ
	struct Vtx {
		float x, y;	// pos
		float u, v;	// tex
	};

	// チップのUVバッファ
	struct UV {
		float u, v;	// 
	};

	// 板ポリのワールド座標位置バッファ
	struct WorldPos {
		float x, y;	// メンバ変数のpos
	};

	static const float STD_SIZE;	// サイズの標準値
	static const float STD_MOVE;	// 移動量の標準値

	/* ↓静的メンバ関数↓ */
public:
	static CEffect* Create(const D3DXVECTOR3& pos, float rot);	// 生成
	static int GetNumAll();			// 総数の取得
	static void InitInstancing();	// インスタンシングの初期化
	static void UninitInstancing();	// インスタンシングの終了
	static void DrawInstancing();	// インスタンシングの描画

	/* ↓静的メンバ変数↓ */
private:
	static int m_numAll;	// 総数
	static IDirect3DVertexBuffer9 *vtxBuf;
	static IDirect3DVertexBuffer9 *uvBuf;
	static IDirect3DVertexBuffer9 *worldPosBuf;
	static IDirect3DVertexDeclaration9 *decl;
	static IDirect3DIndexBuffer9 *indexBuf;
	static ID3DXEffect *effect;

	/* ↓メンバ関数↓ */
public:
	CEffect();				// デフォルトコンストラクタ
	~CEffect() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

	/* ↓メンバ変数↓ */
private:
	D3DXVECTOR3 m_move;	// 移動量
	int m_life;			// 寿命
};

#endif // !_EFFECT_H_
