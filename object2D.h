//**************************************************
// 
// object2D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT2D_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CObject2D : public CObject
{
public: /* ��` */
	static const int MAX_POLYGON = 5;	// �|���S���̍ő吔

public:
	static CObject2D* Create();	// ����

public:
	CObject2D();			// �f�t�H���g�R���X�g���N�^
	~CObject2D() override;	// �f�X�g���N�^

public: /* �����o�֐� */
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
	void SetPos(const D3DXVECTOR3& pos) override;	// �ʒu�̐ݒ�
	D3DXVECTOR3 GetPos() override;					// �ʒu�̎擾
	void SetVtx();	// ���_���̐ݒ�

private: /* �����o�ϐ� */
	float m_rot;		// ����
	float m_size;		// �T�C�Y
	D3DXVECTOR3 m_pos;	// �ʒu
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
};

#endif // !_OBJECT2D_H_
