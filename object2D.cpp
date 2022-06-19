//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "object.h"
#include "object2D.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
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
	{// NULL�`�F�b�N
		// ������
		pObject2D->Init();
	}

	return pObject2D;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CObject2D::CObject2D() :
	m_pVtxBuff(nullptr),
	m_pTexture(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_time(0),
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
	m_time = 0;
	m_rot = 0.0f;
	m_size = POLYGON_SIZE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/Inui Toko 000.jpg",
		&m_pTexture);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(CRenderer::VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		CRenderer::FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	CRenderer::VERTEX_2D *pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

	if (m_pTexture != nullptr)
	{// �e�N�X�`���̔j��
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	// ���
	CObject::Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CObject2D::Update()
{
	m_time++;

	m_rot += ROTATION_SPEED;

	if (m_rot >= D3DX_PI)
	{// 3.14���傫��
		m_rot -= D3DX_PI * 2.0f;
	}
	else if (m_rot <= -D3DX_PI)
	{// -3.14��菬����
		m_rot += D3DX_PI * 2.0f;
	}

	m_size = POLYGON_SIZE * (((sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f) + 1.0f);

	// ��]
	Rotation(m_pos, m_rot, m_size);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CRenderer::VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(CRenderer::FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

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
}

//--------------------------------------------------
// ��]
//--------------------------------------------------
void CObject2D::Rotation(const D3DXVECTOR3& pos, float rot, float size)
{
	D3DXMATRIX mtx, mtxTrans;

	// ��]�̔��f
	D3DXMatrixRotationZ(&mtx, -rot);

	// �ʒu�̔��f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);
	
	D3DXVECTOR3 pVtxPos[NUM_VERTEX];

	float halfSize = size * 0.5f;

	pVtxPos[0] = D3DXVECTOR3(-halfSize, -halfSize, 0.0f);
	pVtxPos[1] = D3DXVECTOR3(+halfSize, -halfSize, 0.0f);
	pVtxPos[2] = D3DXVECTOR3(-halfSize, +halfSize, 0.0f);
	pVtxPos[3] = D3DXVECTOR3(+halfSize, +halfSize, 0.0f);

	CRenderer::VERTEX_2D* pVtx = nullptr;	// ���_���ւ̃|�C���^

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{// ���_���̐ݒ�
		D3DXVec3TransformCoord(&pVtx[i].pos, &pVtxPos[i], &mtx);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
