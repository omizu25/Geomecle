//**************************************************
// 
// circle_danger.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_DANGER_H_	//���̃}�N����`������ĂȂ�������
#define _CIRCLE_DANGER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "circle.h"

//==================================================
// ��`
//==================================================
class CCircleDanger : public CCircle
{
	/* ��` */
public:
	static const int COUNTDOWN_TIME;	// �J�E���g�_�E���̎���

private:
	static const int MAX_LIFE;			// �����̍ő�l
	static const int MIN_LIFE;			// �����̍ŏ��l
	static const D3DXCOLOR STD_COLOR;	// �W���̐F

	/* �������o�֐��� */
public:
	CCircleDanger();			// �f�t�H���g�R���X�g���N�^
	~CCircleDanger() override;	// �f�X�g���N�^

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
};

#endif // !_CIRCLE_DANGER_H_
