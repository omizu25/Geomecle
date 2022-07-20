//**************************************************
// 
// bullet.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _BULLET_H_	//���̃}�N����`������ĂȂ�������
#define _BULLET_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CBullet : public CObject3D
{
	/* ��` */
private:
	static const int SHOT_INTERVAL;	// ���˂̊Ԋu
	static const float STD_SIZE;	// �T�C�Y�̕W���l
	static const float STD_MOVE;	// �ړ��ʂ̕W���l
	static const float STD_INERTIA;	// �����̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CBullet* Create(float rot);	// ����
	static void Shot();	// ����

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_time;	// ����
	static float m_dest;
	static float m_now;

	/* �������o�֐��� */
public:
	CBullet();				// �f�t�H���g�R���X�g���N�^
	~CBullet() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void SetMove(float rot);	// �ړ��ʂ̐ݒ�

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
};

#endif // !_BULLET_H_
