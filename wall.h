//**************************************************
// 
// wall.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _WALL_H_	//���̃}�N����`������ĂȂ�������
#define _WALL_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CWall : public CObject3D
{
	/* ��` */
private:
	static const float MAX_WIDTH;	//	���̍ő�l
	static const float MAX_LENGTH;	//	�����̍ő�l

	/* ���ÓI�����o�֐��� */
public:
	static void AllCreate();	// �S�Ă̐���
	static float GetWidth();	// ���̎擾
	static float GetLength();	// �����̎擾

private:
	static CWall* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// ����

	/* �������o�֐��� */
public:
	CWall();			// �f�t�H���g�R���X�g���N�^
	~CWall() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
};

#endif // !_BG_H_
