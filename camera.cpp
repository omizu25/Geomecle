//**************************************************
// 
// camera.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "camera.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CCamera::MAX_NEAR = 10.0f;
const float CCamera::MAX_FAR = 2500.0f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CCamera::CCamera() :
	m_posV(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posR(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posVDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posRDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_vecU(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	memset(m_mtxProj, 0, sizeof(m_mtxProj));
	memset(m_mtxView, 0, sizeof(m_mtxView));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CCamera::~CCamera()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = m_posV;
	m_posRDest = m_posR;
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 固定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = m_rot;

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CCamera::Uninit()
{
	
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CCamera::Update()
{
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CCamera::Set()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProj);

	// プロジェクションマトリックスの作成(平行投影)
	D3DXMatrixOrthoLH(&m_mtxProj,			// プロジェクションマトリックス
		(float)CApplication::SCREEN_WIDTH,	// 幅
		(float)CApplication::SCREEN_HEIGHT,	// 高さ
		CCamera::MAX_NEAR,					// ニア
		CCamera::MAX_FAR);					// ファー
	
	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProj);
}
