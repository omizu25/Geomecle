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
	/* ��` */
public:
	static const float MAX_SIZE;	// �T�C�Y�̍ő�l

	enum EType
	{
		TYPE_HOMING = 0,	// �z�[�~���O
		TYPE_ROUNDTRIP,		// ����
		TYPE_MAX,
		TYPE_NONE
	};

	/* ���ÓI�����o�֐��� */
public:
	static CEnemy* Create(CEnemy::EType type, const D3DXVECTOR3& pos);	// ����

	/* �������o�֐��� */
public:
	CEnemy();				// �f�t�H���g�R���X�g���N�^
	 ~CEnemy() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
	virtual void Set(const D3DXVECTOR3& pos) = 0;	// �ݒ�
};

#endif // !_ENEMT_H_
