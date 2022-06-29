//**************************************************
// 
// object.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT_H_	//このマクロ定義がされてなかったら
#define _OBJECT_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CObject
{
	/* ↓定義↓ */
public:
	enum EType
	{
		TYPE_PLAYER = 0,	// プレイヤー
		TYPE_BULLET,		// 弾
		TYPE_ENEMY,			// 敵
		TYPE_MAX,
		TYPE_NONE
	};

	static const int MAX_OBJECT = 30000;	// オブジェクトの最大数

	/* ↓静的メンバ関数↓ */
public:
	static void ReleaseAll();		// 全ての解放
	static void UpdateAll();		// 全ての更新
	static void DrawAll();			// 全ての描画
	static int GetNumAll();			// 総数の取得
	static CObject** GetMyObject();	// オブジェクトの取得

	/* ↓静的メンバ変数↓ */
private:
	static int m_numAll;					// 総数
	static CObject* m_pObject[MAX_OBJECT];	// オブジェクトの情報

	/* ↓メンバ関数↓ */
public:
	CObject();			// デフォルトコンストラクタ
	virtual ~CObject();	// デストラクタ

public:
	virtual HRESULT Init() = 0;	// 初期化
	virtual void Uninit() = 0;	// 終了
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画
	virtual void SetPos(const D3DXVECTOR3& pos) = 0;	// 位置の設定
	virtual const D3DXVECTOR3& GetPos() const = 0;		// 位置の取得
	virtual void SetSize(float size) = 0;	// サイズの設定
	virtual float GetSize() = 0;			// サイズの取得
	void SetType(CObject::EType type);	// 種類の設定
	CObject::EType GetType();			// 種類の取得
	void Release();	// 解放

	/* ↓メンバ変数↓ */
private:
	CObject::EType m_type;	// タイプ
	int m_index;			// 格納先の番号
};

#endif // !_OBJECT_H_
