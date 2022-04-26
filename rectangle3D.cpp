//**************************************************
// 
// Hackathon ( rectangle3D.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "rectangle3D.h"
#include "color.h"
#include "texture.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_RECTANGLE3D = 1024;	// ��`�̍ő吔
const int	NUM_VERTEX = 4;			// ���_�̐�
const int	NUM_POLYGON = 2;		// �|���S���̐�

typedef struct
{
	LPDIRECT3DTEXTURE9		pTexture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9	pVtxBuff;	// ���_�o�b�t�@
	D3DXMATRIX				mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3				pos;		// �ʒu
	D3DXVECTOR3				rot;		// ����
	bool					use;		// �g�p���Ă��邩�ǂ���
	bool					draw;		// �`�悷�邩�ǂ���
	bool					add;		// ���Z�������邩�ǂ���
}MyRectangle3D;
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
MyRectangle3D	s_rectangle3D[MAX_RECTANGLE3D];	// ��`�̏��
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitRectangle3D(void)
{
	// �������̃N���A
	memset(s_rectangle3D, 0, sizeof(s_rectangle3D));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitRectangle3D(void)
{
	for (int i = 0; i < MAX_RECTANGLE3D; i++)
	{
		MyRectangle3D *pRectangle3D = &s_rectangle3D[i];

		if (pRectangle3D->pVtxBuff != NULL)
		{// ���_�o�b�t�@�̉��
			pRectangle3D->pVtxBuff->Release();
			pRectangle3D->pVtxBuff = NULL;
		}
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawRectangle3D(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;	// �v�Z�p�}�g���b�N�X

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int i = 0; i < MAX_RECTANGLE3D; i++)
	{
		MyRectangle3D *pRectangle3D = &s_rectangle3D[i];

		if (!pRectangle3D->use || !pRectangle3D->draw)
		{// �g�p���Ă��Ȃ��A�`�悷�邵�Ȃ�
			continue;
		}

		/*�� �g�p���Ă���A�`�悷�� ��*/

		if (pRectangle3D->add)
		{// ���Z��������
			// �����_�[�X�e�[�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, pRectangle3D->pVtxBuff, 0, sizeof(VERTEX_3D));

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&pRectangle3D->mtxWorld);

		// Z�̌����𔽉f
		D3DXMatrixRotationZ(&mtxRot, pRectangle3D->rot.z);
		D3DXMatrixMultiply(&pRectangle3D->mtxWorld, &pRectangle3D->mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pRectangle3D->pos.x, pRectangle3D->pos.y, pRectangle3D->pos.z);
		D3DXMatrixMultiply(&pRectangle3D->mtxWorld, &pRectangle3D->mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &pRectangle3D->mtxWorld);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pRectangle3D->pTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			0,						// �`�悷��ŏ��̒��_�C���f�b�N�X
			NUM_POLYGON);			// �v���~�e�B�u(�|���S��)��

		if (pRectangle3D->add)
		{// ���Z��������
			// �����_�[�X�e�[�g�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}

	// �e�N�X�`���̉���
	pDevice->SetTexture(0, NULL);

	// ���C�g��L���ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
int SetRectangle3D(TEXTURE inTexture)
{
	// �ݒ� [ �e�N�X�`������ ]
	return SetRectangle3DWithTex(GetTexture(inTexture));
}

//--------------------------------------------------
// �ݒ� [ �e�N�X�`������ ]
//--------------------------------------------------
int SetRectangle3DWithTex(LPDIRECT3DTEXTURE9 pTexture)
{
	for (int i = 0; i < MAX_RECTANGLE3D; i++)
	{
		MyRectangle3D *pRectangle3D = &s_rectangle3D[i];

		if (pRectangle3D->use)
		{// �g�p���Ă���
			continue;
		}

		/*�� �g�p���Ă��Ȃ� ��*/

		pRectangle3D->pTexture = pTexture;
		pRectangle3D->use = true;
		pRectangle3D->draw = true;
		pRectangle3D->add = false;
		pRectangle3D->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pRectangle3D->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ���_�o�b�t�@�̐���
		GetDevice()->CreateVertexBuffer(
			sizeof(VERTEX_3D) * NUM_VERTEX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&pRectangle3D->pVtxBuff,
			NULL);

		VERTEX_3D *pVtx = NULL;	// ���_���ւ̃|�C���^

		// ���_�������b�N���A���_���ւ̃|�C���^���擾
		pRectangle3D->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�o�b�t�@���A�����b�N����
		pRectangle3D->pVtxBuff->Unlock();

		D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �ʒu�̐ݒ�
		SetSizeRectangle3D(i, size);

		//�F�̐ݒ�
		SetColorRectangle3D(i, GetColor(COLOR_WHITE));

		D3DXVECTOR2 texU = D3DXVECTOR2(0.0f, 1.0f);
		D3DXVECTOR2 texV = D3DXVECTOR2(0.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		SetTexRectangle3D(i, texU, texV);

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// �g�p����߂�
//--------------------------------------------------
void StopUseRectangle3D(int inIdx)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	pRectangle3D->use = false;

	if (pRectangle3D->pVtxBuff != NULL)
	{// ���_�o�b�t�@�̉��
		pRectangle3D->pVtxBuff->Release();
		pRectangle3D->pVtxBuff = NULL;
	}
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void SetPosRectangle3D(int inIdx, const D3DXVECTOR3& inPos)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	if (!pRectangle3D->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pRectangle3D->pos = inPos;
}

//--------------------------------------------------
// �����̐ݒ�
//--------------------------------------------------
void SetRotRectangle3D(int inIdx, const D3DXVECTOR3& inRot)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	if (!pRectangle3D->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pRectangle3D->rot = inRot;
}

//--------------------------------------------------
// �T�C�Y�̐ݒ�
//--------------------------------------------------
void SetSizeRectangle3D(int inIdx, const D3DXVECTOR3& inSize)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	if (!pRectangle3D->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_3D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle3D(inIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	float fWidth = inSize.x * 0.5f;
	float fHeight = inSize.y * 0.5f;
	float fDepth = inSize.z * 0.5f;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-fWidth, +fHeight, +fDepth);
	pVtx[1].pos = D3DXVECTOR3(+fWidth, +fHeight, +fDepth);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, -fHeight, -fDepth);
	pVtx[3].pos = D3DXVECTOR3(+fWidth, -fHeight, -fDepth);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void SetColorRectangle3D(int inIdx, const D3DXCOLOR& inColor)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	if (!pRectangle3D->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_3D *pVtx = NULL;	// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle3D(inIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = inColor;
	pVtx[1].col = inColor;
	pVtx[2].col = inColor;
	pVtx[3].col = inColor;

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
//--------------------------------------------------
void SetTexRectangle3D(int inIdx, const D3DXVECTOR2& inTexU, const D3DXVECTOR2& inTexV)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	if (!pRectangle3D->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_3D *pVtx = NULL;	// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle3D(inIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(inTexU.x, inTexV.x);
	pVtx[1].tex = D3DXVECTOR2(inTexU.y, inTexV.x);
	pVtx[2].tex = D3DXVECTOR2(inTexU.x, inTexV.y);
	pVtx[3].tex = D3DXVECTOR2(inTexU.y, inTexV.y);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawRectangle3D(int inIdx, bool inDraw)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	if (!pRectangle3D->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pRectangle3D->draw = inDraw;
}

//--------------------------------------------------
// ���Z�������邩�ǂ���
//--------------------------------------------------
void SetAddRectangle3D(int inIdx, bool inAdd)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	if (!pRectangle3D->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pRectangle3D->add = inAdd;
}

//--------------------------------------------------
// �e�N�X�`���̕ύX
//--------------------------------------------------
void ChangeTextureRectangle3D(int inIdx, TEXTURE inTexture)
{
	// �e�N�X�`���̕ύX [ �e�N�X�`������ ]
	ChangeTextureRectangle3DWithTex(inIdx, GetTexture(inTexture));
}

//--------------------------------------------------
// �e�N�X�`���̕ύX [ �e�N�X�`������ ]
//--------------------------------------------------
void ChangeTextureRectangle3DWithTex(int inIdx, LPDIRECT3DTEXTURE9 pTexture)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	if (!pRectangle3D->use)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pRectangle3D->pTexture = pTexture;
}

//--------------------------------------------------
// ���_�o�b�t�@���擾
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffRectangle3D(int inIdx)
{
	assert(inIdx >= 0 && inIdx < MAX_RECTANGLE3D);

	MyRectangle3D *pRectangle3D = &s_rectangle3D[inIdx];

	if (!pRectangle3D->use)
	{// �g�p���Ă��Ȃ�
		return NULL;
	}

	/*�� �g�p���Ă��� ��*/

	return s_rectangle3D[inIdx].pVtxBuff;
}
