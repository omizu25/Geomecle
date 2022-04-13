//**************************************************
// 
// Hackathon ( rectangle.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RECTANGLE_H_	//���̃}�N����`������ĂȂ�������
#define _RECTANGLE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "texture.h"

//==================================================
// ��`
//==================================================
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g[2D]

/*�� ���_���[2D] ��*/

struct VERTEX_2D
{
	D3DXVECTOR3	pos;	// ���_���W
	float		rhw;	// ���W�ϊ��p�W�� (1.0f�ŌŒ�)
	D3DCOLOR	col;	// ���_�J���[
	D3DXVECTOR2	tex;	// �e�N�X�`�����W
};

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// ������
//--------------------------------------------------
void InitRectangle(void);

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitRectangle(void);

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawRectangle(void);

//--------------------------------------------------
// �ݒ�
// ����  : TEXTURE inTexture / �񋓌^ ���
//--------------------------------------------------
int SetRectangle(TEXTURE inTexture);

//--------------------------------------------------
// �ݒ� [ �e�N�X�`������ ]
// ����  : LPDIRECT3DTEXTURE9 pTexture / �e�N�X�`��
//--------------------------------------------------
int SetRectangleWithTex(LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// �g���̂��~�߂�
// ����  : int inIdx / �C���f�b�N�X
//--------------------------------------------------
void StopUseRectangle(int inIdx);

//--------------------------------------------------
// �ʒu�̐ݒ�
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR3& inPos / ���S�̈ʒu
// ����3  : D3DXVECTOR3& inSize / �T�C�Y
//--------------------------------------------------
void SetPosRectangle(int inIdx, const D3DXVECTOR3& inPos, const D3DXVECTOR3& inSize);

//--------------------------------------------------
// ��]����ʒu�̐ݒ�
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR3& inPos / ���S�̈ʒu
// ����3  : float inRot / ����
// ����4  : float inWidth / ��
// ����5  : float inHeight / ����
//--------------------------------------------------
void SetRotationPosRectangle(int inIdx, const D3DXVECTOR3& inPos, float inRot, float inWidth, float inHeight);

//--------------------------------------------------
// �F�̐ݒ�
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : D3DXCOLOR& inColor / �F
//--------------------------------------------------
void SetColorRectangle(int inIdx, const D3DXCOLOR& inColor);

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR2& inTexU / x = ���[, y = �E�[
// ����3  : D3DXVECTOR2& inTexV / x = ��[, y = ���[
//--------------------------------------------------
void SetTexRectangle(int inIdx, const D3DXVECTOR2& inTexU, const D3DXVECTOR2& inTexV);

//--------------------------------------------------
// �`�悷�邩�ǂ���
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : bool inDraw / �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawRectangle(int inIdx, bool inDraw);

//--------------------------------------------------
// ���Z�������邩�ǂ���
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : bool inAdd / ���Z�������邩�ǂ���
//--------------------------------------------------
void SetAddRectangle(int inIdx, bool inAdd);

//--------------------------------------------------
// �e�N�X�`���̕ύX
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : TEXTURE inTexture / �񋓌^ ���
//--------------------------------------------------
void ChangeTextureRectangle(int inIdx, TEXTURE inTexture);

//--------------------------------------------------
// �e�N�X�`���̕ύX [ �e�N�X�`������ ]
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : TEXTURE pTexture / �񋓌^ ���
//--------------------------------------------------
void ChangeTextureRectangleWithTex(int inIdx, LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// ���_�o�b�t�@�̎擾
// ����  : int inIdx / �C���f�b�N�X
// �Ԓl  : LPDIRECT3DVERTEXBUFFER9 / ���_�o�b�t�@
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffRectangle(int inIdx);

#endif // !_RECTANGLE_H_
