//**************************************************
// 
// result.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RESULT_H_	//���̃}�N����`������ĂȂ�������
#define _RESULT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

//==================================================
// ��`
//==================================================
class CResult : public CMode
{
	/* �������o�֐��� */
public:
	CResult();				// �f�t�H���g�R���X�g���N�^
	CResult(EMode mode);	// �R���X�g���N�^
	~CResult() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��
};

#endif // !_RESULT_H_