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
	/* 定義 */
private:
	static const int MAX_WAVE = 5;	// ウェーブの最大数
	static const char* FILE_NAME[];	// ファイルパス

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
	CEnemyWave* m_pWave[MAX_WAVE];	// ウェーブ情報
	int m_nowWave;					// 現在のウェーブ
};

#endif // !_APPLICATION_H_
