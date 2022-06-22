//**************************************************
// 
// bullet.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _BULLET_H_	//���̃}�N����`������ĂȂ�������
#define _BULLET_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object2D.h"

//==================================================
// ��`
//==================================================
class CBullet : public CObject2D
{
public: /* �ÓI�����o�֐� */
	static CBullet* Create();	// ����

public:
	CBullet();			// �f�t�H���g�R���X�g���N�^
	virtual ~CBullet();	// �f�X�g���N�^

public: /* �����o�֐� */
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

protected:
	void Release();	// ���

private: /* �����o�ϐ� */
	D3DXVECTOR3 m_move;	// �ړ���
	int m_life;			// ����
	int m_index;		// �i�[��̔ԍ�
};

#endif // !_BULLET_H_
