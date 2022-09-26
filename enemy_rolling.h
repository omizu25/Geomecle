//**************************************************
// 
// enemy_rolling.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_ROLLING_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_ROLLING_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// ��`
//==================================================
class CEnemyRolling : public CEnemy
{
	/* ����`�� */
private:
	static const float STD_SIZE;	// �T�C�Y�̕W���l
	static const float STD_MOVE;	// �ړ��ʂ̕W���l
	static const float ROT_CHANGE;	// �����̕ύX�l

	/* ���ÓI�����o�֐��� */
public:
	static void Create(const D3DXVECTOR3& pos);	// ����

	/* �������o�֐��� */
public:
	CEnemyRolling();			// �f�t�H���g�R���X�g���N�^
	~CEnemyRolling() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
	void Kill() override;	// �L�����ꂽ

private:
	void Set(const D3DXVECTOR3& pos) override;	// �ݒ�
	void SetRotDir(bool rotDir);				// ��]�����̐ݒ�

	/* �������o�ϐ��� */
private:
	int m_time;		// �^�C��
	bool m_rotDir;	// ��]���� [ true / �E��� / false : ����� ]
};

#endif // !_ENEMY_ROLLING_H_
