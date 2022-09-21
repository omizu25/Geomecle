//**************************************************
// 
// enemy_wave.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_wave.h"
#include "application.h"
#include "mode.h"
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
const int CEnemyWave::SPAWN_INTERVAL = 30;

//--------------------------------------------------
// ����
//--------------------------------------------------
CEnemyWave* CEnemyWave::Create(const char* pPath)
{
	CEnemyWave* pWave = nullptr;

	pWave = new CEnemyWave;

	if (pWave != nullptr)
	{// null�`�F�b�N
		pWave->Load(pPath);
	}

	return pWave;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
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
// �f�X�g���N�^
//--------------------------------------------------
CEnemyWave::~CEnemyWave()
{
	assert(m_pLoad == nullptr);
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CEnemyWave::Load(const char* pPath)
{
	std::ifstream ifs(pPath);

	if (!ifs)
	{// �e�L�X�g���J���Ȃ�
		assert(false);
		return;
	}

	ifs >> enemy;

	m_max = enemy["MAX"];

	if (m_pLoad == nullptr)
	{// null�`�F�b�N
		m_pLoad = new SLoad[m_max];
	}

	if (m_pLoad == nullptr)
	{// null�`�F�b�N
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
// �X�|�[��
//--------------------------------------------------
bool CEnemyWave::Spawn()
{
	if (m_max == m_spawn)
	{// �S���X�|�[������
		return true;
	}

	m_time++;

	if (CObject3D::Exist(CObject3D::TYPE_ENEMY))
	{// �G������
		if ((m_time % SPAWN_INTERVAL) != 0)
		{// �C���^�[�o����
			return false;
		}
	}
	else
	{
		m_time = 0;
	}

	for (int i = 0; i < m_max; i++)
	{
		if (m_pLoad[i].timing != m_timing)
		{// �^�C�~���O���Ⴄ
			continue;
		}

		// �G�̐���
		CEnemy::Create(m_pLoad[i].type, m_pLoad[i].pos);
		
		m_spawn++;
	}

	m_timing++;

	return false;
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CEnemyWave::Release()
{
	if (m_pLoad != nullptr)
	{// null�`�F�b�N
		delete[] m_pLoad;
		m_pLoad = nullptr;
	}
}

//--------------------------------------------------
// ���Z�b�g
//--------------------------------------------------
void CEnemyWave::Reset()
{
	m_time = 0;
	m_timing = 0;
	m_spawn = 0;
}
