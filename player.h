//**************************************************
// 
// player.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PLAYER_H_	//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CPlayer : public CObject3D
{
	/* ��` */
public:
	static const float MAX_MOVE;	// �ړ��ʂ̍ő�l

private:
	static const float MAX_SIZE;	// �T�C�Y�̍ő�l
	static const float MAX_ROT;		// �����̍ő�l

	/* ���ÓI�����o�֐��� */
public:
	static CPlayer* Create();	// ����

	/* �������o�֐��� */
public:
	CPlayer();				// �f�t�H���g�R���X�g���N�^
	 ~CPlayer() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��

private:
	void Move();	// �ړ�
	void Rot();		// ����

private:
	float m_rotDest;	// �ړI�̌���
};

#endif // !_OBJECT_H_
