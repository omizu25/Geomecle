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
	/* �������o�֐��� */
public:
	CEnemyHoming();				// �f�t�H���g�R���X�g���N�^
	~CEnemyHoming() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
	void Set(const D3DXVECTOR3& pos) override;	// �ݒ�
};

#endif // !_ENEMY_HOMING_H_