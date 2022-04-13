//**************************************************
// 
// Hackathon ( utility.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "utility.h"

//--------------------------------------------------
// �p�x�̐��K��
//--------------------------------------------------
void NormalizeAngle(float* pAngle)
{
	if (*pAngle >= D3DX_PI)
	{// 3.14���傫��
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{// -3.14��菬����
		*pAngle += D3DX_PI * 2.0f;
	}
}

//--------------------------------------------------
// �z�[�~���O
//--------------------------------------------------
bool Homing(D3DXVECTOR3* pPosOut, const D3DXVECTOR3& inPosNow, const D3DXVECTOR3& inPosDest, float inSpeed)
{
	D3DXVECTOR3 vecDiff = inPosDest - inPosNow;

	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength <= inSpeed)
	{// ������蒷������������
		*pPosOut = inPosDest;
		return true;
	}
	else
	{// ������蒷�����傫����
		*pPosOut = inPosNow + ((vecDiff / fLength) * inSpeed);
		return false;
	}
}

//--------------------------------------------------
// �����_�̃����_��
//--------------------------------------------------
float FloatRandam(float inMax, float inMin)
{
	return ((rand() / (float)RAND_MAX) * (inMax - inMin)) + inMin;
}

//--------------------------------------------------
// �����̃����_��
//--------------------------------------------------
int IntRandam(int inMax, int inMin)
{
	return (int)((rand() / (float)RAND_MAX) * (inMax - inMin)) + inMin;
}

//--------------------------------------------------
// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float SinCurve(int inTime, float inCycle)
{
	return  (sinf((inTime * inCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float CosCurve(int inTime, float inCycle)
{
	return  (cosf((inTime * inCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// �J�[�u�̒l���A���Ă���
//--------------------------------------------------
float Curve(float inCurve, float inMax, float inMin)
{
	return (inCurve * (inMax - inMin)) + inMin;
}
