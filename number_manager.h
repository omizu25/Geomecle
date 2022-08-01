//**************************************************
// 
// number_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _NUMBER_MANAGER_H_	//���̃}�N����`������ĂȂ�������
#define _NUMBER_MANAGER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CNumber;

//==================================================
// ��`
//==================================================
class CNumberManager
{
	/* ����`�� */
private:
	static const int MAX_DIGIT = 8;	// ���̍ő吔
	static const float STD_WIDTH;	// ���̕W���l
	static const float STD_HEIGHT;	// �����̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CNumberManager* Create(const D3DXVECTOR3& pos, int value);	// ����

	/* �������o�֐��� */
public:
	CNumberManager();	// �f�t�H���g�R���X�g���N�^
	~CNumberManager();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos);	// ������
	void Uninit();	// �I��
	void Release();	// ���
	void ChangeNumber(int value);	// ���̕ύX

private:
	int GetDigit(int value);	// ���̎擾

	/* �������o�ϐ��� */
private:
	CNumber* m_number[MAX_DIGIT];	// ��
	int m_value;	// �l
};

#endif // !_NUMBER_MANAGER_H_
