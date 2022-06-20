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
public:
	CObject();			// デフォルトコンストラクタ
	virtual ~CObject();	// デストラクタ

public: /* メンバ関数 */
	virtual HRESULT Init() = 0;	// 初期化
	virtual void Uninit() = 0;	// 終了
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画
	virtual void SetPos(const D3DXVECTOR3& pos) = 0;	// 位置の設定
};

#endif // !_OBJECT_H_
