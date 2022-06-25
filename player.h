//**************************************************
// 
// player.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PLAYER_H_	//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object2D.h"

//==================================================
// ��`
//==================================================
class CPlayer : public CObject2D
{
	/* ���ÓI�����o�֐��� */
public:
	static CPlayer* Create();		// ����
	static void ChangeNumShot();	// �����̕ύX
	static int GetNumShot();		// �����̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numShot;	// ����

	/* �������o�֐��� */
public:
	CPlayer();				// �f�t�H���g�R���X�g���N�^
	 ~CPlayer() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
	const D3DXVECTOR3& GetPos() const override;	// �ʒu�̎擾

private:
	void Move();	// �ړ�
};

#endif // !_OBJECT_H_
