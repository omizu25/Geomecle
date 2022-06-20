//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "object.h"
#include "object2D.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
static const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);	// 頂点フォーマット

struct VERTEX_2D
{// 頂点データ
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
};

const int NUM_VERTEX = 4;			// 頂点の数
const int NUM_POLYGON = 2;			// ポリゴンの数
const float POLYGON_SIZE = 100.0f;	// ポリゴンのサイズ
const float ROTATION_SPEED = 0.1f;	// 回転速度
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CObject2D::CObject2D() :
	m_pVtxBuff(nullptr),
	m_pTexture(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(0.0f),
	m_size(0.0f)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObject2D::~CObject2D()
{
	assert(m_pVtxBuff == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CObject2D::Init()
{
	m_rot = 0.0f;
	m_size = POLYGON_SIZE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/icon_122380_256.png",
		&m_pTexture);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CObject2D::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{// 頂点バッファの破棄
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexture != nullptr)
	{// テクスチャの破棄
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CObject2D::Update()
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// プリミティブの種類
		0,						// 描画する最初の頂点インデックス
		NUM_POLYGON);			// プリミティブ(ポリゴン)数
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void CObject2D::SetPos(const D3DXVECTOR3& pos)
{
	m_pos = pos;

	D3DXMATRIX mtx, mtxTrans;

	// 回転の反映
	D3DXMatrixRotationZ(&mtx, -m_rot);

	// 位置の反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);
	
	D3DXVECTOR3 pVtxPos[NUM_VERTEX];

	float halfSize = m_size * 0.5f;

	pVtxPos[0] = D3DXVECTOR3(-halfSize, -halfSize, 0.0f);
	pVtxPos[1] = D3DXVECTOR3(+halfSize, -halfSize, 0.0f);
	pVtxPos[2] = D3DXVECTOR3(-halfSize, +halfSize, 0.0f);
	pVtxPos[3] = D3DXVECTOR3(+halfSize, +halfSize, 0.0f);

	VERTEX_2D* pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{// 頂点情報の設定
		D3DXVec3TransformCoord(&pVtx[i].pos, &pVtxPos[i], &mtx);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
