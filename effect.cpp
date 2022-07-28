//**************************************************
// 
// effect.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "effect.h"
#include "application.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEffect::STD_SIZE = 25.0f;
const float CEffect::STD_MOVE = 10.0f;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CEffect::m_numAll = 0;
IDirect3DVertexBuffer9* CEffect::vtxBuf = nullptr;
IDirect3DVertexBuffer9* CEffect::uvBuf = nullptr;
IDirect3DVertexBuffer9* CEffect::worldPosBuf = nullptr;
IDirect3DVertexDeclaration9* CEffect::decl = nullptr;
IDirect3DIndexBuffer9* CEffect::indexBuf = nullptr;
ID3DXEffect* CEffect::effect = nullptr;

//--------------------------------------------------
// ����
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, float rot)
{
	CEffect* pEffect = nullptr;

	pEffect = new CEffect;

	if (pEffect != nullptr)
	{// null�`�F�b�N
		pEffect->Init();
		pEffect->SetPos(pos);
		pEffect->SetRot(rot);
		pEffect->m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;
	}

	return pEffect;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
int CEffect::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// �C���X�^���V���O�̏�����
//--------------------------------------------------
void CEffect::InitInstancing()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	Vtx vtx[4] = {	// �P�ʔ|���o�b�t�@
		{ -STD_SIZE, -STD_SIZE, 0.0f, 0.0f},
		{ +STD_SIZE, -STD_SIZE, 1.0f, 0.0f},
		{ -STD_SIZE, +STD_SIZE, 0.0f, 1.0f},
		{ +STD_SIZE, +STD_SIZE, 1.0f, 1.0f}
	};

	// ���_�o�b�t�@�쐬
	pDevice->CreateVertexBuffer(sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &vtxBuf, 0);

	{
		void *p = 0;
		vtxBuf->Lock(0, 0, &p, 0);
		memcpy(p, vtx, sizeof(vtx));
		vtxBuf->Unlock();
	}

	// �C���f�b�N�X�o�b�t�@
	WORD index[4] = { 0, 1, 2, 3 };
	pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuf, 0);
	void *p = 0;
	indexBuf->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuf->Unlock();

	// ���_�錾�쐬
	D3DVERTEXELEMENT9 declElems[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// Local coord
		{ 0, 8, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// UV
		{ 1, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },	// ���[���h�ʒu
		{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },	// �`�b�v��UV
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(declElems, &decl);

	// �V�F�[�_�쐬
	ID3DXBuffer *errBuf = 0;
	D3DXCreateEffectFromFileA(pDevice, "data/TEXT/Effect.fx", 0, 0, 0, 0, &effect, &errBuf);
	if (errBuf) {
		const char *errMsg = (const char*)errBuf->GetBufferPointer();
		OutputDebugStringA(errMsg);
		return;
	}
}

//--------------------------------------------------
// �C���X�^���V���O�̏I��
//--------------------------------------------------
void CEffect::UninitInstancing()
{
	vtxBuf->Release();
	decl->Release();
	indexBuf->Release();
	effect->Release();
}

//--------------------------------------------------
// �C���X�^���V���O�̕`��
//--------------------------------------------------
void CEffect::DrawInstancing()
{
	if (m_numAll == 0)
	{
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(WorldPos) * m_numAll, 0, 0, D3DPOOL_MANAGED, &worldPosBuf, 0);
	pDevice->CreateVertexBuffer(sizeof(UV) * m_numAll, 0, 0, D3DPOOL_MANAGED, &uvBuf, 0);

	{// �G�t�F�N�g�̏��擾
		WorldPos *worldPos = new WorldPos[m_numAll];	// ���[���h���W�ʒu�o�b�t�@

		CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_EFFECT);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		for (int i = 0; i < CObject::GetMax(CObject::CATEGORY_EFFECT); i++)
		{
			if (pObject[i] == nullptr)
			{
				continue;
			}
			pos = pObject[i]->GetPos();

			worldPos[i].x = pos.x;
			worldPos[i].y = pos.y;
		}

		{
			void *p = 0;
			worldPosBuf->Lock(0, 0, &p, 0);
			memcpy(p, worldPos, sizeof(WorldPos) * m_numAll);
			worldPosBuf->Unlock();
		}

		delete[] worldPos;
	}

	{
		UV *p = 0;
		uvBuf->Lock(0, 0, (void**)&p, 0);

		for (int i = 0; i < m_numAll; i++)
		{
			p[i].u = 0.0f;
			p[i].v = 1.0f;
		}

		uvBuf->Unlock();
	}

	// �C���X�^���X�錾
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | m_numAll);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | (unsigned)1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | (unsigned)1);

	// ���_�ƃC���f�b�N�X��ݒ肵�ĕ`��
	pDevice->SetVertexDeclaration(decl);
	pDevice->SetStreamSource(0, vtxBuf, 0, sizeof(Vtx));
	pDevice->SetStreamSource(1, worldPosBuf, 0, sizeof(WorldPos));
	pDevice->SetStreamSource(2, uvBuf, 0, sizeof(UV));
	pDevice->SetIndices(indexBuf);

	effect->SetTechnique("tech");
	UINT passNum = 0;
	effect->Begin(&passNum, 0);
	effect->BeginPass(0);

	effect->SetTexture("tex", CApplication::GetInstanse()->GetTexture()->Get(CTexture::LABEL_bright));
	effect->SetFloat("screenW", CApplication::SCREEN_WIDTH * 0.5f);
	effect->SetFloat("screenH", CApplication::SCREEN_HEIGHT * 0.5f);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

	effect->EndPass();
	effect->End();

	// ��n��
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);

	worldPosBuf->Release();
	uvBuf->Release();
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEffect::CEffect() : CObject3D(CObject::CATEGORY_EFFECT),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	m_numAll++;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEffect::~CEffect()
{
	m_numAll--;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEffect::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject3D::TYPE_BULLET);

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_icon_122540_256);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEffect::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEffect::Update()
{
	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEffect::Draw()
{
	/* �C���X�^���V���O�ŕ`�� */
}
