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
public:
	enum EType
	{
		TYPE_PLAYER = 0,	// �v���C���[
		TYPE_BULLET,		// �e
		TYPE_ENEMY,			// �G
		TYPE_MAX,
		TYPE_NONE
	};

	static const int MAX_OBJECT = 30000;	// �I�u�W�F�N�g�̍ő吔

	/* ���ÓI�����o�֐��� */
public:
	static void ReleaseAll();		// �S�Ẳ��
	static void UpdateAll();		// �S�Ă̍X�V
	static void DrawAll();			// �S�Ă̕`��
	static int GetNumAll();			// �����̎擾
	static CObject** GetMyObject();	// �I�u�W�F�N�g�̎擾

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
	virtual void SetSize(float size) = 0;	// �T�C�Y�̐ݒ�
	virtual float GetSize() = 0;			// �T�C�Y�̎擾
	void SetType(CObject::EType type);	// ��ނ̐ݒ�
	CObject::EType GetType();			// ��ނ̎擾
	void Release();	// ���

	/* �������o�ϐ��� */
private:
	CObject::EType m_type;	// �^�C�v
	int m_index;			// �i�[��̔ԍ�
};

#endif // !_OBJECT_H_
