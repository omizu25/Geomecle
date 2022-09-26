//**************************************************
// 
// enemy_snake_body.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_SNAKE_BODY_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_SNAKE_BODY_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CEnemySnakeBody : public CObject3D
{
	/* ��` */
private:
	static const float STD_SIZE;	// �T�C�Y�̕W���l
	static const int MOVE_INTERVAL;	// �ړ��̃C���^�[�o��

		/* ���ÓI�����o�֐��� */
public:
	static CEnemySnakeBody* Create();	// ����

	/* �������o�֐��� */
public:
	CEnemySnakeBody();				// �f�t�H���g�R���X�g���N�^
	~CEnemySnakeBody() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
	void SetPosDest(const D3DXVECTOR3& posDest);	// �ړI�̈ʒu�̐ݒ�
	const D3DXVECTOR3& GetPosOld() const;			// �O��̈ʒu�̎擾

	/* �����o�ϐ� */
private:
	int m_time;				// �^�C��
	D3DXVECTOR3 m_posDest;	// �ړI�̈ʒu
	D3DXVECTOR3 m_posOld;	// �O��̈ʒu
};

#endif // !_ENEMY_SNAKE_BODY_H_
