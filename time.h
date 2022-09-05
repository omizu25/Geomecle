//**************************************************
// 
// time.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TIME_H_	//���̃}�N����`������ĂȂ�������
#define _TIME_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

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
class CTime
{
	/* ���ÓI�����o�֐��� */
public:
	static CTime* Create(const D3DXVECTOR3& pos, int start, int end);	// ����

	/* �������o�֐��� */
public:
	CTime();	// �f�t�H���g�R���X�g���N�^
	~CTime();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos);	// ������
	void Uninit();						// �I��
	void Update();						// �X�V
	void SetStart(int start);			// �J�n���Ԃ̐ݒ�
	void SetEnd(int end);				// �I�����Ԃ̐ݒ�

	/* �������o�ϐ��� */
private:
	CNumberManager* m_pNumber;	// ����
	int m_start;				// �J�n
	int m_elapsed;				// �o��
	int m_end;					// �I��
};

#endif // !_TIME_H_