//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_manager.h"
#include <assert.h>

// �W�F�C�\���p
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>

namespace nl = nlohmann;

static nl::json enemy;	// ���X�g�̐���

//==================================================
// ��`
//==================================================
const int CEnemyManager::SPAWN_INTERVAL = 60;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CEnemyManager* CEnemyManager::m_pEnemyManager = nullptr;

//--------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------
CEnemyManager* CEnemyManager::GetInstanse()
{
	if (m_pEnemyManager == nullptr)
	{// null�`�F�b�N
		m_pEnemyManager = new CEnemyManager;
	}

	return m_pEnemyManager;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyManager::CEnemyManager() :
	m_pEnemyLoad(nullptr),
	m_time(0),
	m_timing(0),
	m_max(0),
	m_spawn(0)
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyManager::~CEnemyManager()
{
	assert(m_pEnemyLoad == nullptr);
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CEnemyManager::Load()
{
	m_time = 0;
	m_timing = 0;
	m_spawn = 0;

	std::ifstream ifs("data/TEXT/EnemySpawn.json");

	if (!ifs)
	{// �e�L�X�g���J���Ȃ�
		assert(false);
		return;
	}

	ifs >> enemy;

	m_max = enemy["MAX"];

	if (m_pEnemyLoad == nullptr)
	{// null�`�F�b�N
		m_pEnemyLoad = new SLoad[m_max];
	}

	if (m_pEnemyLoad == nullptr)
	{// null�`�F�b�N
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
}

//--------------------------------------------------
// �X�|�[��
//--------------------------------------------------
void CEnemyManager::Spawn()
{
	if (m_max == m_spawn)
	{// �S���X�|�[������
		return;
	}

	m_time++;

	if (CObject::Exist(CObject::TYPE_ENEMY))
	{// �G������
		if ((m_time % CEnemyManager::SPAWN_INTERVAL) != 0)
		{// �C���^�[�o����
			return;
		}
	}
	else
	{
		m_time = 0;
	}

	for (int i = 0; i < m_max; i++)
	{
		if (m_pEnemyLoad[i].timing != m_timing)
		{// �^�C�~���O���Ⴄ
			continue;
		}

		// �G�̐���
		CEnemy::Create(m_pEnemyLoad[i].type, m_pEnemyLoad[i].pos);
		
		m_spawn++;
	}

	m_timing++;
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CEnemyManager::Release()
{
	if (m_pEnemyLoad != nullptr)
	{// null�`�F�b�N
		delete[] m_pEnemyLoad;
		m_pEnemyLoad = nullptr;
	}
}