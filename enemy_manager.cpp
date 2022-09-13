//**************************************************
// 
// enemy_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_manager.h"
#include "enemy_wave.h"
#include "application.h"
#include "mode.h"
#include <assert.h>

//==================================================
// 静的メンバ変数
//==================================================
CEnemyManager* CEnemyManager::m_pEnemyManager = nullptr;

//--------------------------------------------------
// インスタンスの取得
//--------------------------------------------------
CEnemyManager* CEnemyManager::GetInstanse()
{
	if (m_pEnemyManager == nullptr)
	{// nullチェック
		m_pEnemyManager = new CEnemyManager;
	}

	return m_pEnemyManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyManager::CEnemyManager() :
	m_pWave(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyManager::~CEnemyManager()
{
	assert(m_pWave == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemyManager::Init()
{
	m_pWave = new CEnemyWave;

	if (m_pWave != nullptr)
	{// nullチェック
		m_pWave->Load();
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyManager::Uninit()
{
	if (m_pWave != nullptr)
	{// nullチェック
		m_pWave->Release();

	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyManager::Update()
{
	
}
