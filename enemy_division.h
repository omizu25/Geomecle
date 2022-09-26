//**************************************************
// 
// enemy_division.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_DIVISION_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_DIVISION_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// ��`
//==================================================
class CEnemyDivision : public CEnemy
{
	/* ����`�� */
private:
	static const float STD_MOVE;	// �ړ��ʂ̕W���l
	static const float ROT_CHANGE;	// �����̕ύX�l

	/* �������o�֐��� */
public:
	CEnemyDivision();			// �f�t�H���g�R���X�g���N�^
	~CEnemyDivision() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
	void Kill() override;	// �L�����ꂽ

private:
	void Set(const D3DXVECTOR3& pos) override;	// �ݒ�

	/* �������o�ϐ��� */
private:
	int m_time;	// �^�C��
};

#endif // !_ENEMY_DIVISION_H_
