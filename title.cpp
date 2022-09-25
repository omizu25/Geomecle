//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "title.h"
#include "application.h"
#include "camera.h"
#include "object.h"
#include "object2D.h"
#include "effect_manager.h"
#include "wall.h"
#include "utility.h"
#include "menu.h"
#include "sound.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTitle::CTitle() : CMode(CMode::MODE_TITLE),
	m_pMenu(nullptr),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_time(0),
	m_partCnt(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTitle::Init()
{
	m_time = 0;
	m_partCnt = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	CObject2D* pTitle = CObject2D::Create();
	pTitle->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.3f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pTitle->SetSize(D3DXVECTOR3(750.0f, 250.0f, 0.0f));
	pTitle->SetTexture(CTexture::LABEL_Title);
	pTitle->SetFade(0.0f);

	D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.85f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(300.0f, 100.0f, 0.0f);
	m_pMenu = CMenu::Create(pos, size, 3, 100.0f, true, true);
	m_pMenu->SetTexture(0 ,CTexture::LABEL_Title);
	m_pMenu->SetFrame(D3DXVECTOR3(600.0f, (float)CApplication::SCREEN_HEIGHT, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

	// BGM
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_BGM_Title);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTitle::Uninit()
{
	if (m_pMenu != nullptr)
	{// null�`�F�b�N
		m_pMenu->Uninit();
		delete m_pMenu;
		m_pMenu = nullptr;
	}

	// �S�Ẳ��
	CObject::ReleaseAll(false);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTitle::Update()
{
	// �X�V
	CObject::UpdateAll();

	// �G�t�F�N�g
	Effect();

	// �I��
	int select = m_pMenu->Select();

	if (m_time >= CMode::FADE_TIME)
	{// �t�F�[�h����
		if (select != -1)
		{
			Change(MODE_TUTORIAL);
		}
		
		return;
	}

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CTitle::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}

//--------------------------------------------------
// �G�t�F�N�g
//--------------------------------------------------
void CTitle::Effect()
{
	m_time++;

	if ((m_time % 13) != 0)
	{// ���Ԋu�҂�
		return;
	}

	if (m_partCnt % 15 == 0)
	{// ���Ԋu
		m_col.r = FloatRandom(1.0f, 0.0f);
		m_col.g = FloatRandom(1.0f, 0.0f);
		m_col.b = FloatRandom(1.0f, 0.0f);
	}

	m_partCnt++;

	float width = CWall::STD_WIDTH * 0.4f;
	float height = CWall::STD_HEIGHT * 0.4f;

	D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandom(width, -width), FloatRandom(height, -height), 0.0f);

	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Particle(pos, m_col);
}
