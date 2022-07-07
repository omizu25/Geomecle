//**************************************************
// 
// enemy_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_MANAGER_H_	//このマクロ定義がされてなかったら
#define _ENEMY_MANAGER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// 定義
//==================================================
class CEnemyManager
{
	/* ↓定義↓ */
private:
	static const int SPAWN_INTERVAL;	// スポーンのインターバル

	struct SLoad
	{
		D3DXVECTOR3 pos;
		int timing;
		CEnemy::EType type;
	};

	/* ↓メンバ関数↓ */
public:
	CEnemyManager();	// デフォルトコンストラクタ
	~CEnemyManager();	// デストラクタ

public:
	void Load();	// 読み込み
	void Spawn();	// スポーン
	void Release();	// 解放

	/* ↓メンバ変数↓ */
private:
	SLoad* m_pEnemyLoad;	// 読み込み用のエネミー
	int m_time;				// 時間
	int m_timing;			// タイミング
	int m_max;				// 最大値
	int m_spawn;			// スポーン
};

#endif // !_APPLICATION_H_
