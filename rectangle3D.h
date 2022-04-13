//**************************************************
// 
// Hackathon ( rectangle3D.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _RECTANGLE3D_H_	//���̃}�N����`������ĂȂ�������
#define _RECTANGLE3D_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "texture.h"

//==================================================
// ��`
//==================================================
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g[3D] �ʒu�E�@���E�J���[�E�e�N�X�`��

/*�� ���_���[3D] ��*/

struct VERTEX_3D
{
	D3DXVECTOR3	pos;	// ���_���W
	D3DXVECTOR3	nor;	// �@���x�N�g��
	D3DCOLOR	col;	// ���_�J���[
	D3DXVECTOR2	tex;	// �e�N�X�`�����W
};

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// ������
//--------------------------------------------------
void InitRectangle3D(void);

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitRectangle3D(void);

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawRectangle3D(void);

//--------------------------------------------------
// �ݒ�
// ����  : TEXTURE inTexture / �񋓌^ ���
//--------------------------------------------------
int SetRectangle3D(TEXTURE inTexture);

//--------------------------------------------------
// �ݒ� [ �e�N�X�`������ ]
// ����  : LPDIRECT3DTEXTURE9 pTexture / �e�N�X�`��
//--------------------------------------------------
int SetRectangle3DWithTex(LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// �g���̂��~�߂�
// ����  : int inIdx / �C���f�b�N�X
//--------------------------------------------------
void StopUseRectangle3D(int inIdx);

//--------------------------------------------------
// �ʒu�̐ݒ�
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR3& inPos / ���S�̈ʒu
//--------------------------------------------------
void SetPosRectangle3D(int inIdx, const D3DXVECTOR3& inPos);

//--------------------------------------------------
// �����̐ݒ�
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR3& inRot / ����
//--------------------------------------------------
void SetRotRectangle3D(int inIdx, const D3DXVECTOR3& inRot);

//--------------------------------------------------
// �T�C�Y�̐ݒ�
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR3& inSize / �T�C�Y
//--------------------------------------------------
void SetSizeRectangle3D(int inIdx, const D3DXVECTOR3& inSize);

//--------------------------------------------------
// �F�̐ݒ�
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : D3DXCOLOR& inColor / �F
//--------------------------------------------------
void SetColorRectangle3D(int inIdx, const D3DXCOLOR& inColor);

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : D3DXVECTOR2& inTexU / x = ���[, y = �E�[
// ����3  : D3DXVECTOR2& inTexV / x = ��[, y = ���[
//--------------------------------------------------
void SetTexRectangle3D(int inIdx, const D3DXVECTOR2& inTexU, const D3DXVECTOR2& inTexV);

//--------------------------------------------------
// �`�悷�邩�ǂ���
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : bool inDraw / �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawRectangle3D(int inIdx, bool inDraw);

//--------------------------------------------------
// ���Z�������邩�ǂ���
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : bool inAdd / ���Z�������邩�ǂ���
//--------------------------------------------------
void SetAddRectangle3D(int inIdx, bool inAdd);

//--------------------------------------------------
// �e�N�X�`���̕ύX
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : TEXTURE inTexture / �񋓌^ ���
//--------------------------------------------------
void ChangeTextureRectangle3D(int inIdx, TEXTURE inTexture);

//--------------------------------------------------
// �e�N�X�`���̕ύX [ �e�N�X�`������ ]
// ����1  : int inIdx / �C���f�b�N�X
// ����2  : TEXTURE pTexture / �񋓌^ ���
//--------------------------------------------------
void ChangeTextureRectangle3DWithTex(int inIdx, LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// ���_�o�b�t�@�̎擾
// ����  : int inIdx / �C���f�b�N�X
// �Ԓl  : LPDIRECT3DVERTEXBUFFER9 / ���_�o�b�t�@
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffRectangle3D(int inIdx);

#endif // !_RECTANGLE3D_H_
