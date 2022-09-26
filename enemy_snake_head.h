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
// �O���錾
//==================================================
class CEnemySnakeBody;

//==================================================
// ��`
//==================================================
class CEnemySnakeHead : public CEnemy
{
	/* ��` */
private:
	static const int MAX_BODY;			// �̂̍ő吔
	static const int IDX_PARENT;		// �e�̔ԍ�
	static const float STD_SIZE;		// �T�C�Y�̕W���l
	static const float STD_MOVE;		// �ړ��ʂ̕W���l
	static const float AMPLITUDE_WIDTH;	// �U���̕�
	static const float AMPLITUDE_SPEED;	// �U���̑��x

	/* �������o�֐��� */
public:
	CEnemySnakeHead();				// �f�t�H���g�R���X�g���N�^
	~CEnemySnakeHead() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
	void Kill() override;	// �L�����ꂽ

public:
	const D3DXVECTOR3& GetPosOld() const;	// �O��̈ʒu�̎擾

private:
	void Set(const D3DXVECTOR3& pos) override;	// �ݒ�
	void SetMove();	// �ړ��ʂ̐ݒ�

	/* �����o�ϐ� */
private:
	int m_time;					// �^�C��
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 m_posOld;		// �O��̈ʒu
	CEnemySnakeBody** m_pBody;	// �̂̏��

};

#endif // !_ENEMY_SNAKE_HEAD_H_
