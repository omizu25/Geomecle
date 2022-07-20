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
		TYPE_WALL,			// ��
		TYPE_BG,			// �w�i
		TYPE_UI,			// UI
		TYPE_MAX,
		TYPE_NONE
	};

private:
	static const int MAX_OBJECT = 30000;	// �I�u�W�F�N�g�̍ő吔

	/* ���ÓI�����o�֐��� */
public:
	static void ReleaseAll();		// �S�Ẳ��
	static void UpdateAll();		// �S�Ă̍X�V
	static void DrawAll();			// �S�Ă̕`��
	static int GetMax();			// �ő�l�̎擾
	static int GetNumAll();			// �����̎擾
	static CObject** GetMyObject();	// �I�u�W�F�N�g�̎擾
	static bool Exist(EType type);	// ���݂��邩�ǂ���

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numAll;					// ����
	static CObject* m_pObject[MAX_OBJECT];	// �I�u�W�F�N�g�̏��

	/* �������o�֐��� */
public:
	CObject();			// �f�t�H���g�R���X�g���N�^
	virtual ~CObject();	// �f�X�g���N�^

public:
	virtual void Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��
	void SetType(EType type);		// ��ނ̐ݒ�
	const EType GetType() const;	// ��ނ̎擾
	void Release();	// ���

	/* �������o�ϐ��� */
private:
	EType m_type;	// �^�C�v
	int m_index;	// �i�[��̔ԍ�
};

#endif // !_OBJECT_H_
