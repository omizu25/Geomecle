//**************************************************
// 
// enemy_wave.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_WAVE_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_WAVE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// ��`
//==================================================
class CEnemyWave
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

	/* ���ÓI�����o�֐��� */
public:
	static CEnemyWave* Create(const char* pPath);	// ����
	
	/* �������o�֐��� */
public:
	CEnemyWave();	// �f�t�H���g�R���X�g���N�^
	~CEnemyWave();	// �f�X�g���N�^

public:
	void Load(const char* pPath);	// �ǂݍ���
	bool Spawn();	// �X�|�[��
	void Release();	// ���
	void Reset();	// ���Z�b�g

	/* �������o�ϐ��� */
private:
	SLoad* m_pLoad;	// �ǂݍ���
	int m_time;		// ����
	int m_timing;	// �^�C�~���O
	int m_max;		// �ő吔
	int m_spawn;	// �X�|�[��
};

#endif // !_ENEMY_WAVE_H_
