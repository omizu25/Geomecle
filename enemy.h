//**************************************************
// 
// enemy.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CEnemy : public CObject3D
{
	/* ���ÓI�����o�֐��� */
public:
	static CEnemy* Create();	// ����

	/* �������o�֐��� */
public:
	CEnemy();				// �f�t�H���g�R���X�g���N�^
	 ~CEnemy() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
};

#endif // !_ENEMT_H_
