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
#include "application.h"
#include "mode.h"
#include <assert.h>

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
	m_pWave(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyManager::~CEnemyManager()
{
	assert(m_pWave == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemyManager::Init()
{
	m_pWave = new CEnemyWave;

	if (m_pWave != nullptr)
	{// null�`�F�b�N
		m_pWave->Load();
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyManager::Uninit()
{
	if (m_pWave != nullptr)
	{// null�`�F�b�N
		m_pWave->Release();

	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyManager::Update()
{
	
}
