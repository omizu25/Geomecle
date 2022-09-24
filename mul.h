//**************************************************
// 
// mul.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MUL_H_	//���̃}�N����`������ĂȂ�������
#define _MUL_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "score.h"

//==================================================
// �O���錾
//==================================================
class CObject2D;

//==================================================
// ��`
//==================================================
class CMul : public CScore
{
	/* ����`�� */
public:
	static const float STD_WIDTH;	// ���̕W���l
	static const float STD_HEIGHT;	// �����̕W���l
	static const float MUL_SIZE;	// �|����̃T�C�Y

	/* ���ÓI�����o�֐��� */
public:
	static CMul* Create(const D3DXVECTOR3& pos);	// ����

	/* �������o�֐��� */
public:
	CMul();	// �f�t�H���g�R���X�g���N�^
	~CMul();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size) override;	// ������
	void Uninit() override;		// �I��
	void Release() override;	// ���

public:
	void Add();				// ���Z
	void Set(int value);	// �ݒ�

	/* �������o�ϐ��� */
private:
	CObject2D* m_pMul;	// �|����
	D3DXVECTOR3 m_pos;	// �ʒu
};

#endif // !_MUL_H_
