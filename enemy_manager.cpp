//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "renderer.h"
#include "enemy_manager.h"
#include <assert.h>

// ジェイソン用
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>

namespace nl = nlohmann;

static nl::json enemy;//リストの生成

//==================================================
// 定義
//==================================================
const int CEnemyManager::SPAWN_INTERVAL = 60;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyManager::CEnemyManager() :
	m_pEnemyLoad(nullptr)
{

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyManager::~CEnemyManager()
{
	assert(m_pEnemyLoad == nullptr);
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CEnemyManager::Load()
{
	std::ifstream ifs("data/TEXT/EnemySpawn.json");

	if (!ifs)
	{// テキストが開けない
		assert(false);
		return;
	}

	ifs >> enemy;

	m_max = enemy["MAX"];

	if (m_pEnemyLoad == nullptr)
	{// nullチェック
		m_pEnemyLoad = new SLoad[m_max];
	}

	if (m_pEnemyLoad == nullptr)
	{// nullチェック
		assert(false);
		return;
	}
		
	memset(m_pEnemyLoad, 0, sizeof(m_pEnemyLoad));

	for (int i = 0; i < m_max; i++)
	{
		std::string name = "ENEMY";
		std::string Number = std::to_string(i);
		name += Number;
	
		m_pEnemyLoad[i].pos = D3DXVECTOR3(enemy[name]["POS"]["X"], enemy[name]["POS"]["Y"], 0.0f);
		m_pEnemyLoad[i].type = (CEnemy::EType)enemy[name]["TYPE"];
		m_pEnemyLoad[i].timing = enemy[name]["TIMING"];
	}

	int i = 0;
}

//--------------------------------------------------
// スポーン
//--------------------------------------------------
void CEnemyManager::Spawn()
{
	m_time++;

	

	if ((m_time % CEnemyManager::SPAWN_INTERVAL) != 0)
	{// インターバル中
		return;
	}

	for (int i = 0; i < m_max; i++)
	{
		if (m_pEnemyLoad[i].timing != m_timing)
		{// タイミングが違う
			continue;
		}

		CEnemy::Create(m_pEnemyLoad[i].type, m_pEnemyLoad[i].pos);
	}

	m_timing++;
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CEnemyManager::Release()
{
	if (m_pEnemyLoad != nullptr)
	{// nullチェック
		delete[] m_pEnemyLoad;
		m_pEnemyLoad = nullptr;
	}
}