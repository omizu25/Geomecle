//**************************************************
// 
// rankingUI.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "rankingUI.h"
#include "score.h"
#include "number.h"
#include "object2D.h"
#include "utility.h"

#include <assert.h>
#include <stdio.h>

//==================================================
// ��`
//==================================================
const float CRankingUI::STD_WIDTH = 40.0f;
const float CRankingUI::STD_HEIGHT = 50.0f;
const char* CRankingUI::FILE_NAME[] =
{// �����L���O�̃e�L�X�g�̃p�X
	"data/TEXT/Ranking_Normal.txt",		// �ʏ�
	"data/TEXT/Ranking_SafetyArea.txt",	// ���S�G���A
	"data/TEXT/Ranking_DangerArea.txt",	// �댯�G���A
};

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CRankingUI::m_score = 0;
int CRankingUI::m_ranking[MAX_RANKING] = {};

//--------------------------------------------------
// ����
//--------------------------------------------------
CRankingUI* CRankingUI::Create(const D3DXVECTOR3& pos, float length)
{
	CRankingUI* pRanking = nullptr;

	pRanking = new CRankingUI;

	if (pRanking != nullptr)
	{// null�`�F�b�N
		// ������
		pRanking->Init(pos, length);
	}

	return pRanking;
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CRankingUI::Set(int score)
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
int CRankingUI::Get(int rank)
{
	if (rank == -1)
	{// �w��̒l
		return m_score;
	}

	assert(rank >= 0 && rank < MAX_RANKING);

	// �ǂݍ���
	Load();

	return m_ranking[rank];
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CRankingUI::Load()
{
	FILE *pFile = nullptr;

	// �t�@�C�����J��
	pFile = fopen(FILE_NAME[CGame::GetMode()], "r");

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
void CRankingUI::Save()
{
	FILE *pFile = nullptr;

	// �t�@�C�����J��
	pFile = fopen(FILE_NAME[CGame::GetMode()], "w");

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
// �ύX
//--------------------------------------------------
void CRankingUI::Change()
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
CRankingUI::CRankingUI() :
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
CRankingUI::~CRankingUI()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		assert(m_pRanking[i] == nullptr);
	}
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CRankingUI::Init(const D3DXVECTOR3& pos, float length)
{
	m_time = 0;

	D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

	float height = STD_HEIGHT;

	if (length <= 0.0f)
	{// �l���}�C�i�X
		height *= -1.0f;
	}

	float posX = 0.0f;
	float posY = 0.0f;
	float maxWidth = CNumberManager::MAX_DIGIT * size.x;
	float interval = 3 * (size.x * 0.5f);
	float rankPosX = 0.0f;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		posX = pos.x - (maxWidth - (Digit(m_ranking[i]) * size.x));
		posY = pos.y + (i * (length + height));

		// �X�R�A�̐���
		m_pRanking[i] = CScore::Create(D3DXVECTOR3(posX, posY, 0.0f), size);

		// �X�R�A�̐ݒ�
		m_pRanking[i]->Set(m_ranking[i]);

		rankPosX = pos.x - maxWidth - interval - (STD_HEIGHT * 0.5f);

		// �ʂ̐���
		CObject2D* pRank = CObject2D::Create();
		pRank->SetPos(D3DXVECTOR3(rankPosX - 20.0f, posY, 0.0f));
		pRank->SetSize(D3DXVECTOR3(STD_HEIGHT, STD_HEIGHT, 0.0f));
		pRank->SetTexture(CTexture::LABEL_Rank);
		pRank->SetFade(0.0f);

		// ���ʂ̐���
		CNumber* pNumber = CNumber::Create(D3DXVECTOR3(rankPosX - 65.0f, posY, 0.0f), size * 1.2f);
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
void CRankingUI::Uninit()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_pRanking[i] != nullptr)
		{// null�`�F�b�N
			// �I��
			m_pRanking[i]->Uninit();
			delete m_pRanking[i];
			m_pRanking[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CRankingUI::Release()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		if (m_pRanking[i] != nullptr)
		{// null�`�F�b�N
			// ���
			m_pRanking[i]->Release();
			delete m_pRanking[i];
			m_pRanking[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CRankingUI::Update()
{
	if (m_newRank == -1)
	{// �w��̒l
		return;
	}

	m_time++;

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, 0.01f) * 0.9f);

	// �F�̐ݒ�
	m_pRanking[m_newRank]->SetCol(col);
}

//--------------------------------------------------
// ���Z�b�g
//--------------------------------------------------
void CRankingUI::Reset(const D3DXVECTOR3& pos, float length)
{
	// �ǂݍ���
	Load();

	D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

	float height = STD_HEIGHT;

	if (length <= 0.0f)
	{// �l���}�C�i�X
		height *= -1.0f;
	}

	float posX = 0.0f;
	float posY = 0.0f;
	float maxWidth = CNumberManager::MAX_DIGIT * size.x;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		posX = pos.x - (maxWidth - (Digit(m_ranking[i]) * size.x));
		posY = pos.y + (i * (length + height));

		// �X�R�A�̃��Z�b�g
		m_pRanking[i]->Reset(D3DXVECTOR3(posX, posY, 0.0f), size);

		// �X�R�A�̐ݒ�
		m_pRanking[i]->Set(m_ranking[i]);
	}
}
