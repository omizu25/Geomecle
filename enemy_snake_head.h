//**************************************************
// 
// enemy_snake_head.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_SNAKE_HEAD_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_SNAKE_HEAD_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// ��`
//==================================================
class CEnemySnakeHead : public CEnemy
{
	/* ��` */
private:
	static const float MAX_SIZE;		// �T�C�Y�̍ő�l
	static const float MAX_MOVE;		// �ړ��ʂ̍ő�l
	static const float MAX_AMPLITUDE;	// �U���̍ő�l

	/* �������o�֐��� */
public:
	CEnemySnakeHead();				// �f�t�H���g�R���X�g���N�^
	~CEnemySnakeHead() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��

private:
	void Set(const D3DXVECTOR3& pos) override;	// �ݒ�
	void SetMove();	// �ړ��ʂ̐ݒ�

	/* �����o�ϐ� */
private:
	int m_time;				// �^�C��
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
};

#endif // !_ENEMY_SNAKE_HEAD_H_
