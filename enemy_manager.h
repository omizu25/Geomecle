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

//==================================================
// インクルード
//==================================================
class CEnemyWave;

//==================================================
// 定義
//==================================================
class CEnemyManager
{
	/* ↓静的メンバ関数↓ */
public:
	static CEnemyManager* GetInstanse();	// インスタンスの取得

	/* ↓静的メンバ変数↓ */
private:
	static CEnemyManager* m_pEnemyManager;	// 自分のクラス

	/* ↓メンバ関数↓ */
private:
	CEnemyManager();	// デフォルトコンストラクタ

public:
	~CEnemyManager();	// デストラクタ

public:
	void Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新

	/* ↓メンバ変数↓ */
private:
	CEnemyWave* m_pWave;	// ウェーブ情報
};

#endif // !_APPLICATION_H_
