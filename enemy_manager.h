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
// �C���N���[�h
//==================================================
class CEnemyWave;

//==================================================
// ��`
//==================================================
class CEnemyManager
{
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
	void Update();	// �X�V

	/* �������o�ϐ��� */
private:
	CEnemyWave* m_pWave;	// �E�F�[�u���
};

#endif // !_APPLICATION_H_
