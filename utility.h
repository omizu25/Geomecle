//**************************************************
//
// Hackathon ( utility.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _UTILITY_H_	// ���̃}�N����`������ĂȂ�������
#define _UTILITY_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "renderer.h"
#include <crtdbg.h>

//--------------------------------------------------
// �o�͂Ƀe�L�X�g���o�͂���B
// ����  : pAngle / �p�x
//--------------------------------------------------
#ifdef _DEBUG
#define DEBUG_PRINT(...) _RPT_BASE(_CRT_WARN, __FILE__, __LINE__, NULL, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) ((void)0)
#endif

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// �p�x�̐��K��
// ����  : float* pAngle / �p�x
//--------------------------------------------------
void NormalizeAngle(float* pAngle);

//--------------------------------------------------
// �z�[�~���O
// ����1  : D3DXVECTOR3* pPosOut / �ʒu
// ����2  : D3DXVECTOR3& inPosNow / ���݂̈ʒu
// ����3  : D3DXVECTOR3& inPosDest / �ړI�̈ʒu
// ����4  : float inSpeed / ����
// �Ԓl  : bool / �ړI�̈ʒu�ɒ��������ǂ���
//--------------------------------------------------
bool Homing(D3DXVECTOR3* pPosOut, const D3DXVECTOR3& inPosNow, const D3DXVECTOR3& inPosDest, float inSpeed);

//--------------------------------------------------
// �����_�̃����_��
// ����1  : float inMax / �ő�l
// ����2  : float inMin / �ŏ��l
// �Ԓl  : float / �����_���l
//--------------------------------------------------
float FloatRandam(float inMax, float inMin);

//--------------------------------------------------
// �����̃����_��
// ����1  : int inMax / �ő�l
// ����2  : int inMin / �ŏ��l
// �Ԓl  : int / �����_���l
//--------------------------------------------------
int IntRandam(int inMax, int inMin);

//--------------------------------------------------
// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
// ����1  : int inTime / �^�C��
// ����2  : float inCycle / ����
// �Ԓl  : float / 1.0f�`0.0f��sin�J�[�u
//--------------------------------------------------
float SinCurve(int inTime, float inCycle);

//--------------------------------------------------
// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
// ����1  : int inTime / �^�C��
// ����2  : float inCycle / ����
// �Ԓl  : float / 1.0f�`0.0f��cos�J�[�u
//--------------------------------------------------
float CosCurve(int inTime, float inCycle);

//--------------------------------------------------
// �J�[�u�̒l���A���Ă���
// ����1  : float inCurve / �J�[�u
// ����2  : float inMax / �ő�l
// ����3  : float inMin / �ŏ��l
// �Ԓl  : float / �J�[�u
//--------------------------------------------------
float Curve(float inCurve, float inMax, float inMin);

#endif // !_UTILITY_H_
