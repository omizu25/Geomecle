//**************************************************
// 
// bullet.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _BULLET_H_	//このマクロ定義がされてなかったら
#define _BULLET_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object2D.h"

//==================================================
// 定義
//==================================================
class CBullet : public CObject2D
{
private: /* 定義 */
	static const int MAX_BULLET = 124;	// 弾の最大数

public: /* 静的メンバ関数 */
	static CBullet* Create();	// 生成

public:
	CBullet();			// デフォルトコンストラクタ
	virtual ~CBullet();	// デストラクタ

public: /* メンバ関数 */
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

protected:
	void Release();	// 解放

private: /* メンバ変数 */
	int m_life;		// 寿命
	int m_index;	// 格納先の番号
};

#endif // !_BULLET_H_
