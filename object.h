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
		TYPE_NONE = -1,
		TYPE_PLAYER,	// プレイヤー
		TYPE_BULLET,	// 弾
		TYPE_ENEMY,		// 敵
		TYPE_BODY,		// 体
		TYPE_MAX,
	};

	enum ECategory
	{
		CATEGORY_NONE = -1,
		CATEGORY_3D,		// 3D
		CATEGORY_EFFECT,	// エフェクト
		CATEGORY_2D,		// 2D
		CATEGORY_MAX
	};

private:
	static const int MAX_2D;		// 2Dの最大数
	static const int MAX_3D;		// 3Dの最大数
	static const int MAX_EFFECT = 30000;	// エフェクトの最大数
	static const int MAX_OBJECT[CATEGORY_MAX];	// 最大数の配列

	/* ↓静的メンバ関数↓ */
public:
	static void ReleaseAll(bool releaseKeep);	// 全ての解放
	static void UpdateAll();	// 全ての更新
	static void DrawAll();		// 全ての描画
	static int GetNumAll();		// 総数の取得
	static int GetMax(ECategory cat);	// 最大数の取得
	static CObject** GetMyObject(ECategory cat);	// オブジェクトの取得
	static bool Exist(EType type);	// 存在するかどうか

	/* ↓静的メンバ変数↓ */
private:
	static int m_numAll;	// 総数
	static CObject* m_pObject[CATEGORY_MAX][MAX_EFFECT];	// オブジェクトの情報

	/* ↓メンバ関数↓ */
public:
	CObject();				// デフォルトコンストラクタ
	CObject(ECategory cat);	// コンストラクタ
	virtual ~CObject();		// デストラクタ

public:
	virtual void Init() = 0;	// 初期化
	virtual void Uninit() = 0;	// 終了
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画

public:
	void SetType(EType type);		// 種類の設定
	const EType GetType() const;	// 種類の取得
	void SetKeep(bool keep);		// ずっと持っているかの設定
	void Release();	// 解放

	/* ↓メンバ変数↓ */
private:
	EType m_type;		// タイプ
	ECategory m_cat;	// カテゴリー
	int m_index;		// 格納先の番号
	bool m_keep;		// ずっと持っているかどうか
};

#endif // !_OBJECT_H_
