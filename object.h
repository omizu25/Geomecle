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
#include "renderer.h"

//==================================================
// 定義
//==================================================
class CObject
{
public: /* 定義 */
	static const int MAX_POLYGON = 5;	// ポリゴンの最大数

public: /* 静的メンバ関数 */
	static void CreateAll();	// 全ての生成
	static void ReleaseAll();	// 全ての解放
	static void UpdateAll();	// 全ての更新
	static void DrawAll();		// 全ての描画

private: /* 静的メンバ変数 */
	static int m_numAll;	// 総数

protected:
	static CObject* m_pObject[MAX_POLYGON];	// オブジェクトの情報

public:
	CObject();			// デフォルトコンストラクタ
	virtual ~CObject();	// デストラクタ

public: /* メンバ関数 */
	virtual HRESULT Init() = 0;	// 初期化
	virtual void Uninit() = 0;	// 終了
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画
	virtual void SetPos(const D3DXVECTOR3& pos) = 0;	// 位置の設定

protected:
	void Release();	// 解放

private: /* メンバ変数 */
	int m_index;	// 格納先の番号
};

#endif // !_OBJECT_H_
