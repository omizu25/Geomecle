//**************************************************
// 
// enemy_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_MANAGER_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_MANAGER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CEnemyWave;

//==================================================
// ��`
//==================================================
class CEnemyManager
{
	/* ��` */
private:
	static const int MAX_WAVE = 7;	// �E�F�[�u�̍ő吔
	static const char* FILE_NAME[];	// �t�@�C���p�X

	/* ���ÓI�����o�֐��� */
public:
	static CEnemyManager* GetInstanse();	// �C���X�^���X�̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static CEnemyManager* m_pEnemyManager;	// �����̃N���X

	/* �������o�֐��� */
private:
	CEnemyManager();	// �f�t�H���g�R���X�g���N�^

public:
	~CEnemyManager();	// �f�X�g���N�^

public:
	void Init();	// ������
	void Uninit();	// �I��
	void Release();	// ���
	void Update();	// �X�V

	/* �������o�ϐ��� */
private:
	CEnemyWave* m_pWave[MAX_WAVE];	// �E�F�[�u���
	int m_nowWave;					// ���݂̃E�F�[�u
};

#endif // !_ENEMY_MANAGER_H_
