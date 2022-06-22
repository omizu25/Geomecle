//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "object.h"
#include "object2D.h"
#include "texture.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
static const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);	// ���_�t�H�[�}�b�g

struct VERTEX_2D
{// ���_�f�[�^
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

const int NUM_VERTEX = 4;			// ���_�̐�
const int NUM_POLYGON = 2;			// �|���S���̐�
const float POLYGON_SIZE = 100.0f;	// �|���S���̃T�C�Y
const float ROTATION_SPEED = 0.1f;	// ��]���x
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CObject2D* CObject2D::Create()
{
	CObject2D* pObject2D = nullptr;

	pObject2D = new CObject2D;

	if (pObject2D != nullptr)
	{// null�`�F�b�N
		pObject2D->Init();
	}

	return pObject2D;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CObject2D::CObject2D() :
	m_pVtxBuff(nullptr),
	m_texture(CTexture::TEXTURE_NONE),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(0.0f),
	m_size(0.0f)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObject2D::~CObject2D()
{
	assert(m_pVtxBuff == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CObject2D::Init()
{
	m_rot = 0.0f;
	m_size = POLYGON_SIZE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_texture = CTexture::TEXTURE_NONE;
	
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float size = m_size * 0.5f;

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size, -size, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+size, -size, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size, +size, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+size, +size, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CObject2D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CObject2D::Update()
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CObject2D::Draw()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	CTexture* pTexture = CApplication::GetInstanse()->GetTexture();
	 
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`�悷��ŏ��̒��_�C���f�b�N�X
		NUM_POLYGON);			// �v���~�e�B�u(�|���S��)��
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void CObject2D::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;

	// ���_���̐ݒ�
	CObject2D::SetVtx();
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CObject2D::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CObject2D::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//--------------------------------------------------
// ���_���̐ݒ�
//--------------------------------------------------
void CObject2D::SetVtx()
{
	D3DXMATRIX mtx, mtxTrans;

	// ��]�̔��f
	D3DXMatrixRotationZ(&mtx, -m_rot);

	// �ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);
	
	D3DXVECTOR3 pVtxPos[NUM_VERTEX];

	float halfSize = m_size * 0.5f;

	pVtxPos[0] = D3DXVECTOR3(-halfSize, -halfSize, 0.0f);
	pVtxPos[1] = D3DXVECTOR3(+halfSize, -halfSize, 0.0f);
	pVtxPos[2] = D3DXVECTOR3(-halfSize, +halfSize, 0.0f);
	pVtxPos[3] = D3DXVECTOR3(+halfSize, +halfSize, 0.0f);

	VERTEX_2D* pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{// ���_���̐ݒ�
		D3DXVec3TransformCoord(&pVtx[i].pos, &pVtxPos[i], &mtx);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
