//**************************************************
// 
// object2D.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _OBJECT2D_H_	//���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �O���錾
//==================================================
class CObject;

//==================================================
// ��`
//==================================================
class CObject2D : public CObject
{
public: /* �ÓI�����o�֐� */
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

private:
	void Rotation(const D3DXVECTOR3& pos, float rot, float size);	// ��]

private: /* �����o�ϐ� */
	int m_time;			// ����
	float m_rot;		// ����
	float m_size;		// �T�C�Y
	D3DXVECTOR3 m_pos;	// �ʒu
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
};

#endif // !_OBJECT2D_H_
