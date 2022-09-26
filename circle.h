//**************************************************
// 
// circle.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_H_	//���̃}�N����`������ĂȂ�������
#define _CIRCLE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CCircle : public CObject3D
{
	/* ��` */
public:
	enum ECircle
	{
		CIRCLE_NONE = -1,
		CIRCLE_APPEAR = 0,	// �o��
		CIRCLE_DISAPPEAR,	// ����
		CIRCLE_MAX
	};

	static const float DISAPPEAR_SPEED;	// ���ł̑��x

private:
	static const float STD_SIZE;	// �T�C�Y�̕W���l
	static const float APPEAR_SPEED;	// �o���̑��x

	/* ���ÓI�����o�֐��� */
public:
	static CCircle* Create(const D3DXVECTOR3& pos);	// ����
	static void Collision();	// �����蔻��
	static bool GetCollision();	// �������Ă��邩�ǂ����̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static bool m_collision;	// �����蔻��

	/* �������o�֐��� */
public:
	CCircle();				// �f�t�H���g�R���X�g���N�^
	~CCircle() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	virtual bool Appear();					// �o��������
	virtual void SetAppear(ECircle appear);	// �o�������ł̐ݒ�
	
public:
	bool GetCountDown();	// �J�E���g�_�E�������Ă��邩�ǂ���
	void SetTime(int time);	// �J�E���g�_�E���̃^�C���̐ݒ�
	void SetLife(int life);	// �����̐ݒ�
	int GetLife();			// �����̎擾
	ECircle GetAppear();	// �o�������ł̎擾

	/* �������o�ϐ��� */
private:
	int m_time;				// �^�C��
	int m_countDownTime;	// �J�E���g�_�E���̃^�C��
	int m_life;				// ����
	ECircle m_appear;		// �o��������
	bool m_countDown;		// �J�E���g�_�E�������邩�ǂ���
};

#endif // !_CIRCLE_H_
