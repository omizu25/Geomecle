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
	enum EType
	{
		TYPE_NONE = -1,
		TYPE_HOMING = 0,	// ホーミング
		TYPE_ROUNDTRIP,		// 往復
		TYPE_WINDMILL,		// 風車
		TYPE_SNAKE,			// 蛇
		TYPE_DIVISION,		// 分裂
		TYPE_ROLLING,		// 回転
		TYPE_MAX
	};
	
private:
	static const float STD_SIZE;	// サイズの最大値

	/* ↓静的メンバ関数↓ */
public:
	static CEnemy* Create(CEnemy::EType type, const D3DXVECTOR3& pos);	// 生成

	/* ↓メンバ関数↓ */
public:
	CEnemy();				// デフォルトコンストラクタ
	 ~CEnemy() override;	// デストラクタ

public:
	void Init() override;	// 初期化
	void Uninit() override;	// 終了
	void Update() override;	// 更新
	void Draw() override;	// 描画

private:
	virtual void Set(const D3DXVECTOR3& pos) = 0;	// 設定
};

#endif // !_ENEMT_H_
