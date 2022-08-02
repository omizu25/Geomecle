//**************************************************
// 
// effect.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _EFFECT_H_	//���̃}�N����`������ĂȂ�������
#define _EFFECT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object.h"

//==================================================
// ��`
//==================================================
class CEffect : public CObject
{
	/* ��` */
public:
	static const float STD_WIDTH;	// ���̕W���l
	static const float STD_HEIGHT;	// �����̕W���l

private:
	static const int MAX_LIFE;		// �����̍ő�l

	/* ���ÓI�����o�֐��� */
public:
	static CEffect* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col);	// ����
	static int GetNumAll();	// �����̎擾

	/* ���ÓI�����o�ϐ��� */
private:
	static int m_numAll;	// ����

	/* �������o�֐��� */
public:
	CEffect();				// �f�t�H���g�R���X�g���N�^
	~CEffect() override;	// �f�X�g���N�^

public:
	void Init() override;	// ������
	void Uninit() override;	// �I��
	void Update() override;	// �X�V
	void Draw() override;	// �`��

public:
	const D3DXVECTOR3& GetPos() const;	// �ʒu�̎擾
	const D3DXCOLOR& GetCol() const;	// �F�̎擾
	const D3DXVECTOR3& GetMove() const;	// �ړ���

	/* �������o�ϐ��� */
private:
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXCOLOR m_col;	// �F
	int m_life;			// ����
};

#endif // !_EFFECT_H_
