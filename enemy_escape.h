//**************************************************
// 
// enemy_escape.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_ESCAPE_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_ESCAPE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// ��`
//==================================================
class CEnemyEscape : public CEnemy
{
	/* ����`�� */
private:
	static const float HOMING_SPEED;	// �z�[�~���O�̑��x
	static const float ESCAPE_SPEED;	// �����鎞�̑��x
	static const float ROT_CHANGE;		// �����̕ύX�l
	static const float STD_INERTIA;		// �����̕W���l
	static const float FIND_AREA;		// �T���G���A

	/* �������o�֐��� */
public:
	CEnemyEscape();				// �f�t�H���g�R���X�g���N�^
	~CEnemyEscape() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
	void Kill() override;	// �L�����ꂽ

private:
	void Escape();	// �e���瓦����
	void Set(const D3DXVECTOR3& pos) override;	// �ݒ�

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
	float m_rot;		
	bool m_rotDir;		// ��]���� [ true / �E��� / false : ����� ]
};

#endif // !_ENEMY_ESCAPE_H_
