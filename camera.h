//**************************************************
// 
// camera.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CAMERA_H_	// ���̃}�N����`������ĂȂ�������
#define _CAMERA_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CCamera
{
	/* ����`�� */
private:
	static const float MAX_NEAR;	// �j�A�̍ő�l
	static const float MAX_FAR;		// �t�@�[�̍ő�l

	/* �������o�֐��� */
public:
	CCamera();	// �f�t�H���g�R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

public:
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Set();		// �ݒ�

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_posV;		// ���݂̎��_
	D3DXVECTOR3 m_posR;		// ���݂̒����_
	D3DXVECTOR3 m_posVDest;	// �ړI�̎��_
	D3DXVECTOR3 m_posRDest;	// �ړI�̒����_
	D3DXVECTOR3 m_vecU;		// ������x�N�g��
	D3DXVECTOR3 m_rot;		// ���݂̌���
	D3DXVECTOR3 m_rotDest;	// �ړI�̌���
	D3DXMATRIX m_mtxProj;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;	// �r���[�}�g���b�N�X
};

#endif // !_CAMERA_H_
