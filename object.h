//**************************************************
// 
// object.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CObject
{
	/* ����`�� */
private:
	static const int MAX_OBJECT = 30000;	// �I�u�W�F�N�g�̍ő吔

	/* ���ÓI�����o�֐��� */
public:
	static void ReleaseAll();	// �S�Ẳ��
	static void UpdateAll();	// �S�Ă̍X�V
	static void DrawAll();		// �S�Ă̕`��
	static int GetNumAll();		// �����̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numAll;					// ����
	static CObject* m_pObject[MAX_OBJECT];	// �I�u�W�F�N�g�̏��

	/* �������o�֐��� */
public:
	CObject();			// �f�t�H���g�R���X�g���N�^
	virtual ~CObject();	// �f�X�g���N�^

public:
	virtual HRESULT Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��
	virtual void SetPos(const D3DXVECTOR3& pos) = 0;	// �ʒu�̐ݒ�
	virtual const D3DXVECTOR3& GetPos() const = 0;		// �ʒu�̎擾

protected:
	void Release();	// ���

	/* �������o�ϐ��� */
private:
	int m_index;	// �i�[��̔ԍ�
};

#endif // !_OBJECT_H_
