//**************************************************
// 
// enemy.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_H_	//このマクロ定義がされてなかったら
#define _ENEMY_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// 定義
//==================================================
class CEnemy : public CObject3D
{
	/* 定義 */
public:
	static const float MAX_SIZE;	// サイズの最大値

	enum EType
	{
		TYPE_HOMING = 0,	// ホーミング
		TYPE_ROUNDTRIP,		// 往復
		TYPE_MAX,
		TYPE_NONE
	};

	/* ↓静的メンバ関数↓ */
public:
	static CEnemy* Create(CEnemy::EType type, const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CEnemy();				// デフォルトコンストラクタ
	 ~CEnemy() override;	// デストラクタ

public:
	HRESULT Init() override;	// 初期化
	void Uninit() override;		// 終了
	void Update() override;		// 更新
	void Draw() override;		// 描画
	virtual void Set(const D3DXVECTOR3& pos) = 0;	// 設定
};

#endif // !_ENEMT_H_
