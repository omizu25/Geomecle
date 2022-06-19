//**************************************************
// 
// object2D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT2D_H_	//このマクロ定義がされてなかったら
#define _OBJECT2D_H_	//２重インクルード防止のマクロ定義

//==================================================
// 前方宣言
//==================================================
class CObject;

//==================================================
// 定義
//==================================================
class CObject2D : public CObject
{
public: /* 静的メンバ関数 */
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

private:
	void Rotation(const D3DXVECTOR3& pos, float rot, float size);	// 回転

private: /* メンバ変数 */
	int m_time;			// 時間
	float m_rot;		// 向き
	float m_size;		// サイズ
	D3DXVECTOR3 m_pos;	// 位置
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
};

#endif // !_OBJECT2D_H_
