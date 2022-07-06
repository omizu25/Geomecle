//**************************************************
// 
// enemy_round_trip.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _ENEMY_ROUND_TRIP_H_	//���̃}�N����`������ĂȂ�������
#define _ENEMY_ROUND_TRIP_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "enemy.h"

//==================================================
// ��`
//==================================================
class CEnemyRoundTrip : public CEnemy
{
	/* �������o�֐��� */
public:
	CEnemyRoundTrip();				// �f�t�H���g�R���X�g���N�^
	~CEnemyRoundTrip() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
	void Set(const D3DXVECTOR3& pos) override;	// �ݒ�
};

#endif // !_ENEMY_ROUND_TRIP_H_