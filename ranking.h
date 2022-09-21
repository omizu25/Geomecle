//**************************************************
// 
// ranking.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RANKING_H_	//���̃}�N����`������ĂȂ�������
#define _RANKING_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CScore;

//==================================================
// ��`
//==================================================
class CRanking
{
	/* ���ÓI�����o�֐��� */
public:
	static const float STD_WIDTH;	// ���̕W���l
	static const float STD_HEIGHT;	// �����̕W���l

private:
	static const int MAX_RANKING = 5;	// �����L���O�̍ő吔
	static const char* FILE_NAME;		// �t�@�C���p�X

	/* ���ÓI�����o�֐��� */
public:
	static CRanking* Create(const D3DXVECTOR3& pos, float length);	// ����
	static void Load();			// �ǂݍ���
	static void Save();			// �ۑ�
	static void Set(int score);	// �ݒ�
	static int Get(int rank);	// �擾

private:
	static void Change();	// �ύX

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_score;	// ����̃X�R�A
	static int m_ranking[MAX_RANKING];	// �����L���O

	/* �������o�֐��� */
public:
	CRanking();		// �f�t�H���g�R���X�g���N�^
	~CRanking();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos, float length);	// ������
	void Uninit();	// �I��

	/* �������o�ϐ��� */
private:
	CScore* m_pRanking[MAX_RANKING];	// �����L���O
};

#endif // !_RANKING_H_