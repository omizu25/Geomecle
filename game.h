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
#include "circle_manager.h"

//==================================================
// �O���錾
//==================================================
class CObject2D;
class CPause;
class CTime;
class CScore;
class CMul;
class CLife;
class CPlayer;
class CBom;

//==================================================
// ��`
//==================================================
class CGame : public CMode
{
	/* ��` */
public:
	enum EGame
	{
		GAME_NONE = -1,
		GAME_NORMAL = 0,	// �ʏ�
		GAME_SAFETY_AREA,	// ���S�G���A
		GAME_DANGER_AREA,	// �댯�G���A
		GAME_MAX
	};

private:
	static const int MAX_TIME;		// ���Ԃ̍ő�l
	static const int PAUSE_TIME;	// �|�[�Y���o����l�ɂȂ�܂ł̎���
	
	/* ���ÓI�����o�֐��� */
public:
	static void SetMode(EGame mode);	// �Q�[�����[�h�̐ݒ�
	static EGame GetMode();				// �Q�[�����[�h�̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static EGame m_mode;	// �Q�[�����[�h

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
	void Reset();	// ���Z�b�g

public:
	CPlayer* GetPlayer();	// �v���C���[�̎擾
	CScore* GetScore();		// �X�R�A�̎擾
	CMul* GetMul();			// �{���̎擾
	CTime* GetTime();		// �^�C���̎擾
	CLife* GetLife();		// ���C�t�̎擾

private:
	void Effect();	// �G�t�F�N�g

	/* �������o�ϐ��� */
private:
	CCircleManager* m_pCircle[CCircleManager::MAX_CIRCLE];	// �~
	CObject2D* m_pPauseBG;	// �|�[�Y�̔w�i
	CPlayer* m_pPlayer;		// �v���C���[
	CPause* m_pPause;		// �|�[�Y
	CTime* m_pTime;			// �^�C��
	CMul* m_pMul;			// �{��
	CLife* m_pLife;			// ���C�t
	CBom* m_pBom;			// �{��
	CScore* m_pScore;		// �X�R�A
	CScore* m_pBestScore;	// �x�X�g�X�R�A
	int m_time;	//�^�C��
};

#endif // !_GAME_H_
