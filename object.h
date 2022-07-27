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
		TYPE_NONE = -1,
		TYPE_PLAYER,	// �v���C���[
		TYPE_BULLET,	// �e
		TYPE_ENEMY,		// �G
		TYPE_BODY,		// ��
		TYPE_MAX,
	};

	enum ECategory
	{
		CATEGORY_NONE = -1,
		CATEGORY_3D,		// 3D
		CATEGORY_EFFECT,	// �G�t�F�N�g
		CATEGORY_2D,		// 2D
		CATEGORY_MAX
	};

private:
	static const int MAX_2D;		// 2D�̍ő吔
	static const int MAX_3D;		// 3D�̍ő吔
	static const int MAX_EFFECT = 30000;	// �G�t�F�N�g�̍ő吔
	static const int MAX_OBJECT[CATEGORY_MAX];	// �ő吔�̔z��

	/* ���ÓI�����o�֐��� */
public:
	static void ReleaseAll(bool releaseKeep);	// �S�Ẳ��
	static void UpdateAll();	// �S�Ă̍X�V
	static void DrawAll();		// �S�Ă̕`��
	static int GetNumAll();		// �����̎擾
	static int GetMax(ECategory cat);	// �ő吔�̎擾
	static CObject** GetMyObject(ECategory cat);	// �I�u�W�F�N�g�̎擾
	static bool Exist(EType type);	// ���݂��邩�ǂ���

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numAll;	// ����
	static CObject* m_pObject[CATEGORY_MAX][MAX_EFFECT];	// �I�u�W�F�N�g�̏��

	/* �������o�֐��� */
public:
	CObject();				// �f�t�H���g�R���X�g���N�^
	CObject(ECategory cat);	// �R���X�g���N�^
	virtual ~CObject();		// �f�X�g���N�^

public:
	virtual void Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��

public:
	void SetType(EType type);		// ��ނ̐ݒ�
	const EType GetType() const;	// ��ނ̎擾
	void SetKeep(bool keep);		// �����Ǝ����Ă��邩�̐ݒ�
	void Release();	// ���

	/* �������o�ϐ��� */
private:
	EType m_type;		// �^�C�v
	ECategory m_cat;	// �J�e�S���[
	int m_index;		// �i�[��̔ԍ�
	bool m_keep;		// �����Ǝ����Ă��邩�ǂ���
};

#endif // !_OBJECT_H_
