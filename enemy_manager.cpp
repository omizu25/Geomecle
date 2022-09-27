//**************************************************
// 
// enemy_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_manager.h"
#include "enemy_wave.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CEnemyManager::FILE_NAME[] =
{// �e�N�X�`���̃p�X
	"data/TEXT/EnemySpawn000.json",
	"data/TEXT/EnemySpawn001.json",
	"data/TEXT/EnemySpawn002.json",
	"data/TEXT/EnemySpawn003.json",
	"data/TEXT/EnemySpawn004.json",
	"data/TEXT/EnemySpawn005.json",
	"data/TEXT/EnemySpawn006.json",
};

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
	m_nowWave(0)
{
	static_assert(sizeof(FILE_NAME) / sizeof(FILE_NAME[0]) == MAX_WAVE, "aho");

	for (int i = 0; i < MAX_WAVE; i++)
	{
		m_pWave[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyManager::~CEnemyManager()
{
	for (int i = 0; i < MAX_WAVE; i++)
	{
		assert(m_pWave[i] == nullptr);
	}
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemyManager::Init()
{
	for (int i = 0; i < MAX_WAVE; i++)
	{
		m_pWave[i] = CEnemyWave::Create(FILE_NAME[i]);
	}

	m_nowWave = 0;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyManager::Uninit()
{
	for (int i = 0; i < MAX_WAVE; i++)
	{
		if (m_pWave[i] != nullptr)
		{// null�`�F�b�N
			m_pWave[i]->Release();
			m_pWave[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CEnemyManager::Release()
{
	for (int i = 0; i < MAX_WAVE; i++)
	{
		if (m_pWave[i] != nullptr)
		{// null�`�F�b�N
			m_pWave[i]->Release();
			m_pWave[i] = nullptr;
		}
	}

	if (m_pEnemyManager != nullptr)
	{// null�`�F�b�N
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyManager::Update()
{
	if (m_pWave[m_nowWave] == nullptr)
	{// null�`�F�b�N
		assert(false);
	}

	if (!m_pWave[m_nowWave]->Spawn())
	{// �S�ẴX�|�[��������
		return;
	}

	m_nowWave++;

	if (m_nowWave >= MAX_WAVE)
	{
 		m_nowWave = 2;
	}

	if (m_pWave[m_nowWave] == nullptr)
	{// null�`�F�b�N
		assert(false);
	}

	// ���Z�b�g
	m_pWave[m_nowWave]->Reset();
}
