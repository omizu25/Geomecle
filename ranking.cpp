//**************************************************
// 
// ranking.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "ranking.h"
#include "number_manager.h"
#include "number.h"
#include "utility.h"

#include <assert.h>
#include <stdio.h>

//==================================================
// ��`
//==================================================
const float CRanking::STD_WIDTH = 40.0f;
const float CRanking::STD_HEIGHT = 50.0f;
const char* CRanking::FILE_NAME = "data/TEXT/Ranking.txt";

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CRanking::m_score = 0;
int CRanking::m_ranking[MAX_RANKING] = {};

//--------------------------------------------------
// ����
//--------------------------------------------------
CRanking* CRanking::Create(const D3DXVECTOR3& pos, float length)
{
	CRanking* pRanking = nullptr;

	pRanking = new CRanking;

	if (pRanking != nullptr)
	{// null�`�F�b�N
		// ������
		pRanking->Init(pos, length);
	}

	return pRanking;
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CRanking::Load()
{
	FILE *pFile = nullptr;

	// �t�@�C�����J��
	pFile = fopen(FILE_NAME, "r");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fscanf(pFile, "%d", &m_ranking[i]);
		}
		
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		assert(false);
	}
}

//--------------------------------------------------
// �ۑ�
//--------------------------------------------------
void CRanking::Save()
{
	FILE *pFile = nullptr;

	// �t�@�C�����J��
	pFile = fopen(FILE_NAME, "w");

	if (pFile != nullptr)
	{// �t�@�C�����J�����ꍇ

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fprintf(pFile, "%d\n\n", m_ranking[i]);
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{// �t�@�C�����J���Ȃ��ꍇ
		assert(false);
	}
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CRanking::Set(int score)
{
	m_score = score;

	// �ǂݍ���
	Load();

	// �ύX
	Change();

	// �ۑ�
	Save();
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int CRanking::Get(int rank)
{
	if (rank == -1)
	{// �w��̒l
		return m_score;
	}

	assert(rank >= 0 && rank < MAX_RANKING);

	return m_ranking[rank];
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
void CRanking::Change()
{
	int ranking[MAX_RANKING + 1] = {};

	for (int i = 0; i < MAX_RANKING; i++)
	{
		ranking[i] = m_ranking[i];
	}

	ranking[MAX_RANKING] = m_score;

	int save = 0;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		save = ranking[i];

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (save < ranking[j])
			{// ���肪�傫����������
				save = ranking[j];
			}
		}

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (save == ranking[j])
			{// �ő�l��T���Č��
				ranking[j] = ranking[i];
				ranking[i] = save;
				break;
			}
		}
	}

	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_ranking[i] = ranking[i];
	}
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CRanking::CRanking() :
	m_newRank(0),
	m_time(0)
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_pRanking[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CRanking::~CRanking()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		assert(m_pRanking[i] == nullptr);
	}
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CRanking::Init(const D3DXVECTOR3& pos, float length)
{
	m_time = 0;

	D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

	float PosX = 0.0f;
	float PosY = 0.0f;
	float height = STD_HEIGHT;

	if (length <= 0.0f)
	{// �l���}�C�i�X
		height *= -1.0f;
	}

	float maxWidth = CNumberManager::MAX_DIGIT * size.x;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		PosX = pos.x - (maxWidth - (Digit(m_ranking[i]) * size.x));
		PosY = pos.y + (i * (length + height));

		// �X�R�A�̐���
		m_pRanking[i] = CNumberManager::Create(D3DXVECTOR3(PosX, PosY, 0.0f), size, m_ranking[i]);

		// ���ʂ̐���
		CNumber* pNumber = CNumber::Create(D3DXVECTOR3(pos.x - maxWidth - size.x, PosY, 0.0f), size);
		pNumber->Change(i + 1);
	}

	m_newRank = -1;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_ranking[i] != m_score)
		{// �w��̒l�ł͂Ȃ�
			continue;
		}

		m_newRank = i;

		break;
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CRanking::Uninit()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		// ���
		m_pRanking[i]->Uninit();

		m_pRanking[i] = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CRanking::Update()
{
	if (m_newRank == -1)
	{// �w��̒l
		return;
	}

	m_time++;

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = SinCurve(m_time, 0.01f) + 0.1f;

	// �F�̐ݒ�
	m_pRanking[m_newRank]->SetCol(col);
}
