//**************************************************
// 
// game.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _GAME_H_	//���̃}�N����`������ĂȂ�������
#define _GAME_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// �O���錾
//==================================================
class CTime;
class CScore;
class CMul;

//==================================================
// ��`
//==================================================
class CGame : public CMode
{
	/* �������o�֐��� */
public:
	CGame();			// �f�t�H���g�R���X�g���N�^
	~CGame() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	CScore* GetScore();	// �X�R�A�̎擾
	CMul* GetMul();		// �{���̎擾

private:
	CTime* m_pTime;		// �^�C��
	CScore* m_pScore;	// �X�R�A
	CMul* m_pMul;		// �{��
};

#endif // !_GAME_H_
