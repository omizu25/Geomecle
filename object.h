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
		TYPE_WALL,			// 壁
		TYPE_BG,			// 背景
		TYPE_UI,			// UI
		TYPE_MAX,
		TYPE_NONE
	};

private:
	static const int MAX_OBJECT = 30000;	// オブジェクトの最大数

	/* ↓静的メンバ関数↓ */
public:
	static void ReleaseAll();		// 全ての解放
	static void UpdateAll();		// 全ての更新
	static void DrawAll();			// 全ての描画
	static int GetMax();			// 最大値の取得
	static int GetNumAll();			// 総数の取得
	static CObject** GetMyObject();	// オブジェクトの取得
	static bool Exist(EType type);	// 存在するかどうか

	/* ↓静的メンバ変数↓ */
private:
	static int m_numAll;					// 総数
	static CObject* m_pObject[MAX_OBJECT];	// オブジェクトの情報

	/* ↓メンバ関数↓ */
public:
	CObject();			// デフォルトコンストラクタ
	virtual ~CObject();	// デストラクタ

public:
	virtual void Init() = 0;	// 初期化
	virtual void Uninit() = 0;	// 終了
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画
	void SetType(EType type);		// 種類の設定
	const EType GetType() const;	// 種類の取得
	void Release();	// 解放

	/* ↓メンバ変数↓ */
private:
	EType m_type;	// タイプ
	int m_index;	// 格納先の番号
};

#endif // !_OBJECT_H_
