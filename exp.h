//**************************************************
// 
// exp.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EXP_H_	//���̃}�N����`������ĂȂ�������
#define _EXP_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CExp : public CObject3D
{
	/* ��` */
private:
	static const int MAX_EXP;			// �o���l�̍ő吔
	static const int STD_LIFE;			// �����̕W���l
	static const int BLINK_START;		// �_�ł̎n�܂�
	static const float BLINK_SPEED;		// �_�ł̑��x
	static const float HOMING_START;	// �z�[�~���O�̎n�܂�
	static const float HOMING_SPEED;	// �z�[�~���O�̑��x
	static const float STD_SIZE;		// �T�C�Y�̕W���l
	static const float STD_ROTATION;	// ��]�̕W���l
	static const float MAX_MOVE;		// �ړ��ʂ̍ő�l
	static const float MAX_RADIUS;		// ���a�̍ő�l

	/* ���ÓI�����o�֐��� */
public:
	static void CreateAll(const D3DXVECTOR3& pos);	// �S�Ă̐���

private:
	static CExp* Create(const D3DXVECTOR3& pos, float rot);	// ����

	/* �������o�֐��� */
public:
	CExp();				// �f�t�H���g�R���X�g���N�^
	~CExp() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

private:
	void SetMove(float rot);	// ���ʂ̐ݒ�
	void Collision();			// �����蔻��
	void Absorption();			// �z��
	void Wall();				// ��

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
	int m_life;	// ����
};

#endif // !_EXP_H_
