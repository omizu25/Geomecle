//**************************************************
// 
// circle_manager.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _CIRCLE_MANAGER_H_	//���̃}�N����`������ĂȂ�������
#define _CIRCLE_MANAGER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CCircle;

//==================================================
// ��`
//==================================================
class CCircleManager
{
	/* ��` */
public:
	static const int MAX_CIRCLE = 4;	// �~�̍ő吔

private:
	static const int MAX_INTERVAL;	// �C���^�[�o���̍ő�l
	static const int MIN_INTERVAL;	// �C���^�[�o���̍ŏ��l

	/* ���ÓI�����o�֐��� */
public:
	static CCircleManager* Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);	// ����

	/* �������o�֐��� */
public:
	CCircleManager();	// �f�t�H���g�R���X�g���N�^
	~CCircleManager();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);	// ������
	void Uninit();	// �I��
	void Release();	// ���
	void Update();	// �X�V

	/* �������o�ϐ��� */
private:
	CCircle* m_pCircle;	// �~
	int m_time;			// �^�C��
	int m_interval;		// �C���^�[�o��
	float m_areaTop;	// �G���A�̏�
	float m_areaBottom;	// �G���A�̉�
	float m_areaRight;	// �G���A�̉E
	float m_areaLeft;	// �G���A�̍�
};

#endif // !_CIRCLE_MANAGER_H_
