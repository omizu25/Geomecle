//**************************************************
// 
// bom.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _BOM_H_	//���̃}�N����`������ĂȂ�������
#define _BOM_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

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
class CBom
{
	/* ����`�� */
private:
	static const int MAX_BOM = 3;	// �{���̍ő吔
	static const float STD_SIZE;	// �T�C�Y�̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CBom* Create(const D3DXVECTOR3& pos);	// ����

	/* �������o�֐��� */
public:
	CBom();	// �f�t�H���g�R���X�g���N�^
	~CBom();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos);	// ������
	void Uninit();	// �I��
	void Release();	// ���
	void Update();	// �X�V
	int Get();		// �擾
	void Reset();	// ���Z�b�g

private:
	void Sub();	// ���Z

	/* �������o�ϐ��� */
private:
	CObject2D* m_pObj[MAX_BOM];	// �{��
	int m_bom;					// �{���̐�
};

#endif // !_BOM_H_
