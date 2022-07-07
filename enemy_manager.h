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
#include "enemy.h"

//==================================================
// ��`
//==================================================
class CEnemyManager
{
	/* ����`�� */
private:
	static const int SPAWN_INTERVAL;	// �X�|�[���̃C���^�[�o��

	struct SLoad
	{
		D3DXVECTOR3 pos;
		int timing;
		CEnemy::EType type;
	};

	/* �������o�֐��� */
public:
	CEnemyManager();	// �f�t�H���g�R���X�g���N�^
	~CEnemyManager();	// �f�X�g���N�^

public:
	void Load();	// �ǂݍ���
	void Spawn();	// �X�|�[��
	void Release();	// ���

	/* �������o�ϐ��� */
private:
	SLoad* m_pEnemyLoad;	// �ǂݍ��ݗp�̃G�l�~�[
	int m_time;				// ����
	int m_timing;			// �^�C�~���O
	int m_max;				// �ő�l
	int m_spawn;			// �X�|�[��
};

#endif // !_APPLICATION_H_
