//**************************************************
// 
// circle_safety.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_SAFETY_H_	//���̃}�N����`������ĂȂ�������
#define _CIRCLE_SAFETY_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "circle.h"

//==================================================
// ��`
//==================================================
class CCircleSafety : public CCircle
{
	/* ��` */
public:
	static const int COUNTDOWN_TIME;	// �J�E���g�_�E���̎���

private:
	static const int MAX_LIFE;			// �����̍ő�l
	static const D3DXCOLOR STD_COLOR;	// �W���̐F
	static const D3DXCOLOR START_COLOR;	// �n�܂�̐F
	static const D3DXCOLOR END_COLOR;	// �I���̐F
	static const D3DXCOLOR DIFF_COLOR;	// �F�̍���

	/* �������o�֐��� */
public:
	CCircleSafety();			// �f�t�H���g�R���X�g���N�^
	~CCircleSafety() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	bool Appear() override;						// �o��������
	void SetAppear(ECircle appear) override;	// �o�������ł̐ݒ�

	/* �������o�ϐ��� */
private:
	int m_time;	// �^�C��
	D3DXCOLOR m_changeCol;	// �F�̕ω���
};

#endif // !_CIRCLE_SAFETY_H_
