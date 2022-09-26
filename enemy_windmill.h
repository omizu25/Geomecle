//**************************************************
// 
// enemy_windmill.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_WINDMILL_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_WINDMILL_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// ��`
//==================================================
class CEnemyWindmill : public CEnemy
{
	/* ��` */
private:
	static const float STD_MOVE;		// �ړ��ʂ̕W���l
	static const float STD_ROTATION;	// ��]�̕W���l

	/* �������o�֐��� */
public:
	CEnemyWindmill();			// �f�t�H���g�R���X�g���N�^
	~CEnemyWindmill() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
	void Kill() override;	// �L�����ꂽ

private:
	void Set(const D3DXVECTOR3& pos) override;	// �ݒ�
	void SetMove();	// �ړ��ʂ̐ݒ�

	/* �����o�ϐ� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
};

#endif // !_ENEMY_WINDMILL_H_
