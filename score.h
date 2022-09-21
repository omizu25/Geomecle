//**************************************************
// 
// score.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _SCORE_H_	//���̃}�N����`������ĂȂ�������
#define _SCORE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CNumberManager;

//==================================================
// ��`
//==================================================
class CScore
{
	/* ����`�� */
public:
	static const float STD_WIDTH;	// ���̕W���l
	static const float STD_HEIGHT;	// �����̕W���l

	/* ���ÓI�����o�֐��� */
public:
	static CScore* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// ����

	/* �������o�֐��� */
public:
	CScore();	// �f�t�H���g�R���X�g���N�^
	~CScore();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// ������
	void Uninit();			// �I��
	void Add(int score);	// ���Z
	void Set(int score);	// �ݒ�
	int Get();				// �擾

	/* �������o�ϐ��� */
private:
	CNumberManager* m_pNumber;	// ����
	int m_score;				// �X�R�A
};

#endif // !_SCORE_H_
