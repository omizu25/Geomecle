//**************************************************
// 
// object3D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT3D_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT3D_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include "texture.h"
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CObject3D : public CObject
{
	/* ����`�� */
private:
	struct VERTEX_3D
	{// ���_�f�[�^
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	};

	static const DWORD FVF_VERTEX_3D;	// ���_�t�H�[�}�b�g
	static const int NUM_VERTEX;		// ���_�̐�
	static const int NUM_POLYGON;		// �|���S���̐�

	/* ���ÓI�����o�֐��� */
public:
	static CObject3D* Create();	// ����

	/* �������o�֐��� */
public:
	CObject3D();			// �f�t�H���g�R���X�g���N�^
	~CObject3D() override;	// �f�X�g���N�^

public: 
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
	void SetPos(const D3DXVECTOR3& pos) override;	// �ʒu�̐ݒ�
	const D3DXVECTOR3& GetPos() const override;		// �ʒu�̎擾
	void SetSize(const D3DXVECTOR3& size) override;	// �T�C�Y�̐ݒ�
	const D3DXVECTOR3& GetSize() const override;	// �T�C�Y�̎擾
	void SetRot(float rot) override;		// �����̐ݒ�
	const float GetRot() const override;	// �����̎擾
	void SetTexture(CTexture::ELabel texture);					// �e�N�X�`���̐ݒ�
	void SetVtxTex(const D3DXVECTOR2& u, const D3DXVECTOR2 v);	// �e�N�X�`�����W�̐ݒ�

	/* �������o�ϐ��� */
private:
	CTexture::ELabel m_texture;	// �e�N�X�`���̗񋓌^
	float m_rot;		// ����
	D3DXVECTOR3 m_size;	// �T�C�Y
	D3DXVECTOR3 m_pos;	// �ʒu
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
};

#endif // !_OBJECT3D_H_