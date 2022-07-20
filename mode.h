//**************************************************
// 
// mode.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODE_H_	//���̃}�N����`������ĂȂ�������
#define _MODE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CMode
{
	/* �������o�֐��� */
public:
	CMode();	// �f�t�H���g�R���X�g���N�^
	~CMode();	// �f�X�g���N�^

public:
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��
	LPDIRECT3DDEVICE9 GetDevice();	// �f�o�C�X�̎擾

private:
#ifdef _DEBUG
	void DrawFPS();	// FPS�\��
#endif // _DEBUG

	 /* �������o�ϐ��� */
private:
	LPDIRECT3D9 m_pD3D;				// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;	// Device�I�u�W�F�N�g

#ifdef _DEBUG
	LPD3DXFONT m_pFont;	// �t�H���g
#endif // _DEBUG
};

#endif // !_RENDERER_H_
