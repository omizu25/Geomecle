//**************************************************
// 
// circle_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "circle_manager.h"
#include "circle.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CCircleManager::MAX_INTERVAL = 180;
const int CCircleManager::MIN_INTERVAL = 60;

//--------------------------------------------------
// ����
//--------------------------------------------------
CCircleManager* CCircleManager::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size)
{
	CCircleManager* pManager = nullptr;

	pManager = new CCircleManager;

	if (pManager != nullptr)
	{// null�`�F�b�N
		pManager->Init(pos, size);
	}

	return pManager;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CCircleManager::CCircleManager() :
	m_pCircle(nullptr),
	m_time(0),
	m_interval(0),
	m_areaTop(0.0f),
	m_areaBottom(0.0f),
	m_areaRight(0.0f),
	m_areaLeft(0.0f)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CCircleManager::~CCircleManager()
{
	assert(m_pCircle == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CCircleManager::Init(const D3DXVECTOR3& pos, const D3DXVECTOR2& size)
{
	m_time = 0;
	m_interval = IntRandom(MAX_INTERVAL, MIN_INTERVAL);

	m_pCircle = nullptr;

	m_areaTop = pos.y + size.y;
	m_areaBottom = pos.y - size.y;
	m_areaRight = pos.x + size.x;
	m_areaLeft = pos.x - size.x;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CCircleManager::Uninit()
{
	if (m_pCircle != nullptr)
	{// null�`�F�b�N
		m_pCircle->Uninit();
		m_pCircle = nullptr;
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CCircleManager::Release()
{
	if (m_pCircle != nullptr)
	{// null�`�F�b�N
		m_pCircle->Release();
		m_pCircle = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CCircleManager::Update()
{
	if (m_pCircle == nullptr)
	{// �~���Ȃ�
		m_time++;

		if (m_time <= m_interval)
		{// �C���^�[�o����
			return;
		}

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pos.x = FloatRandom(m_areaRight, m_areaLeft);
		pos.y = FloatRandom(m_areaTop, m_areaBottom);

		pos.x = FloatRandom(m_areaRight, m_areaLeft);
		pos.y = FloatRandom(m_areaTop, m_areaBottom);

		// ����
		m_pCircle = CCircle::Create(pos);

		return;
	}

	if (m_pCircle->Appear())
	{// ���ł���
		m_time = 0;
		m_interval = IntRandom(MAX_INTERVAL, MIN_INTERVAL);

		// ���
		m_pCircle->Release();
		m_pCircle = nullptr;
		return;
	}

	/* ���ł��ĂȂ� */

	if (m_pCircle->GetAppear() == CCircle::CIRCLE_DISAPPEAR)
	{// ���Œ�
		return;
	}

	m_time++;

	int life = m_pCircle->GetLife();

	if (m_time >= life)
	{// �����𒴂���
		// ����
		m_pCircle->SetAppear(CCircle::CIRCLE_DISAPPEAR);
	}
}
