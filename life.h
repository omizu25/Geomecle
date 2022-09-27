//**************************************************
// 
// life.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _LIFE_H_	//���̃}�N����`������ĂȂ�������
#define _LIFE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CObject2D;

//==================================================
// ��`
//==================================================
class CLife
{
	/* ����`�� */
private:
	static const int MAX_LIFE = 5;	// ���C�t�̍ő吔
	static const float STD_SIZE;	// �T�C�Y�̕W���l
	 
	/* ���ÓI�����o�֐��� */
public:
	static CLife* Create(const D3DXVECTOR3& pos);	// ����

	/* �������o�֐��� */
public:
	CLife();	// �f�t�H���g�R���X�g���N�^
	~CLife();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos);	// ������
	void Uninit();	// �I��
	void Release();	// ���
	void Sub();		// ���Z
	int Get();		// �擾

	/* �������o�ϐ��� */
private:
	CObject2D* m_pObj[MAX_LIFE];	// ���C�t
	int m_life;						// �c�@
};

#endif // !_LIFE_H_
