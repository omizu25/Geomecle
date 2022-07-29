//**************************************************
// 
// effect.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_H_	//���̃}�N����`������ĂȂ�������
#define _EFFECT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CEffect : public CObject3D
{
	/* ��` */
private:
	// ���_�o�b�t�@
	struct Vtx {
		float x, y;	// pos
		float u, v;	// tex
	};
	
	static const float STD_SIZE;	// �T�C�Y�̕W���l
	static const float STD_MOVE;	// �ړ��ʂ̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CEffect* Create(const D3DXVECTOR3& pos, float rot);	// ����
	static int GetNumAll();			// �����̎擾
	static void InitInstancing();	// �C���X�^���V���O�̏�����
	static void UninitInstancing();	// �C���X�^���V���O�̏I��
	static void DrawInstancing();	// �C���X�^���V���O�̕`��

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numAll;	// ����
	static IDirect3DVertexBuffer9 *vtxBuf;
	static IDirect3DVertexBuffer9 *worldPosBuf;
	static IDirect3DVertexBuffer9 *colBuf;
	static IDirect3DVertexDeclaration9 *decl;
	static IDirect3DIndexBuffer9 *indexBuf;
	static ID3DXEffect *effect;

	/* �������o�֐��� */
public:
	CEffect();				// �f�t�H���g�R���X�g���N�^
	~CEffect() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

	/* �������o�ϐ��� */
private:
	D3DXCOLOR m_col;	// �F
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_saveMove;	// �ۑ������ړ���
	float m_time;	// ����
};

#endif // !_EFFECT_H_
