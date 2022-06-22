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
#include "object2D.h"
#include <d3dx9.h>

//==================================================
// 定義
//==================================================
class CBullet : public CObject2D
{
public: /* 静的メンバ関数 */
	static CBullet* Create();	// 生成

public:
	CBullet();				// デフォルトコンストラクタ
	~CBullet() override;	// デストラクタ

public: /* メンバ関数 */
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画

private: /* メンバ変数 */
	D3DXVECTOR3 m_move;	// 移動量
	int m_life;			// 寿命
	int m_index;		// 格納先の番号
};

#endif // !_BULLET_H_
