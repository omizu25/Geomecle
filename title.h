//**************************************************
// 
// title.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TITLE_H_	//���̃}�N����`������ĂȂ�������
#define _TITLE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// ��`
//==================================================
class CTitle : public CMode
{
	/* �������o�֐��� */
public:
	CTitle();			// �f�t�H���g�R���X�g���N�^
	CTitle(EMode mode);	// �R���X�g���N�^
	~CTitle() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
};

#endif // !_TITLE_H_
