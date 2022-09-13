//**************************************************
// 
// enemy_wave.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_wave.h"
#include "application.h"
#include "mode.h"
#include <assert.h>

// ジェイソン用
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>

namespace nl = nlohmann;

static nl::json enemy;	// リストの生成


//==================================================
// 定義
//==================================================
const int CEnemyWave::SPAWN_INTERVAL = 60;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyWave::CEnemyWave() :
	m_pLoad(nullptr),
	m_time(0),
	m_timing(0),
	m_max(0),
	m_spawn(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyWave::~CEnemyWave()
{
	assert(m_pLoad == nullptr);
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CEnemyWave::Load()
{
	std::ifstream ifs("data/TEXT/EnemySpawn.json");

	if (!ifs)
	{// テキストが開けない
		assert(false);
		return;
	}

	ifs >> enemy;

	m_max = enemy["MAX"];

	if (m_pLoad == nullptr)
	{// nullチェック
		m_pLoad = new SLoad[m_max];
	}

	if (m_pLoad == nullptr)
	{// nullチェック
		assert(false);
		return;
	}
		
	memset(m_pLoad, 0, sizeof(m_pLoad));

	for (int i = 0; i < m_max; i++)
	{
		std::string name = "ENEMY";
		std::string Number = std::to_string(i);
		name += Number;
	
		m_pLoad[i].pos = D3DXVECTOR3(enemy[name]["POS"]["X"], enemy[name]["POS"]["Y"], 0.0f);
		m_pLoad[i].type = (CEnemy::EType)enemy[name]["TYPE"];
		m_pLoad[i].timing = enemy[name]["TIMING"];
	}
}

//--------------------------------------------------
// スポーン
//--------------------------------------------------
void CEnemyWave::Spawn()
{
	if (m_max == m_spawn)
	{// 全部スポーンした
		
		if (CObject3D::Exist(CObject3D::TYPE_ENEMY))
		{// 敵がいる
			return;
		}

		// モードの変更
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);

		return;
	}

	m_time++;

	if (CObject3D::Exist(CObject3D::TYPE_ENEMY))
	{// 敵がいる
		if ((m_time % SPAWN_INTERVAL) != 0)
		{// インターバル中
			return;
		}
	}
	else
	{
		m_time = 0;
	}

	for (int i = 0; i < m_max; i++)
	{
		if (m_pLoad[i].timing != m_timing)
		{// タイミングが違う
			continue;
		}

		// 敵の生成
		CEnemy::Create(m_pLoad[i].type, m_pLoad[i].pos);
		
		m_spawn++;
	}

	m_timing++;
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CEnemyWave::Release()
{
	if (m_pLoad != nullptr)
	{// nullチェック
		delete[] m_pLoad;
		m_pLoad = nullptr;
	}
}
