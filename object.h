//**************************************************
// 
// object.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CObject
{
public:
	CObject();			// �f�t�H���g�R���X�g���N�^
	virtual ~CObject();	// �f�X�g���N�^

public: /* �����o�֐� */
	virtual HRESULT Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��
	virtual void SetPos(const D3DXVECTOR3& pos) = 0;	// �ʒu�̐ݒ�
};

#endif // !_OBJECT_H_