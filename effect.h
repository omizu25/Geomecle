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
	static const float STD_SIZE;	// �T�C�Y�̕W���l
	static const float STD_MOVE;	// �ړ��ʂ̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CEffect* Create();	// ����
	static int GetNumAll();		// �����̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numAll;	// ����

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
	D3DXVECTOR3 m_move;	// �ړ���
	int m_life;			// ����
};

#endif // !_EFFECT_H_
