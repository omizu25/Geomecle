//**************************************************
// 
// number.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _NUMBER_H_	//���̃}�N����`������ĂȂ�������
#define _NUMBER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object2D.h"

//==================================================
// ��`
//==================================================
class CNumber : public CObject2D
{
	/* ���ÓI�����o�֐��� */
public:
	static CNumber* Create(const D3DXVECTOR3& pos, int number);	// ����

	/* �������o�֐��� */
public:
	CNumber();				// �f�t�H���g�R���X�g���N�^
	~CNumber() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_move;	// �ړ���
};

#endif // !_NUMBER_H_
