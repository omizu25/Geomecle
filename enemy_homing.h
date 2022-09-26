//**************************************************
// 
// enemy_homing.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_HOMING_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_HOMING_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// ��`
//==================================================
class CEnemyHoming : public CEnemy
{
	/* ����`�� */
private:
	static const float STD_MOVE;	// �ړ��ʂ̕W���l
	static const float SIZE_CHANGE;	// �T�C�Y�̕ύX�l

	/* �������o�֐��� */
public:
	CEnemyHoming();				// �f�t�H���g�R���X�g���N�^
	~CEnemyHoming() override;	// �f�X�g���N�^

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
	int m_time;				// �^�C��
	D3DXVECTOR3 m_saveSize;	// �T�C�Y�̕ۑ�
};

#endif // !_ENEMY_HOMING_H_
