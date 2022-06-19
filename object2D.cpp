//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "object.h"
#include "object2D.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
const int NUM_VERTEX = 4;			// 頂点の数
const int NUM_POLYGON = 2;			// ポリゴンの数
const float POLYGON_SIZE = 100.0f;	// ポリゴンのサイズ
const float ROTATION_SPEED = 0.1f;	// 回転速度
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CObject2D* CObject2D::Create()
{
	CObject2D* pObject2D = nullptr;

	pObject2D = new CObject2D;

	if (pObject2D != nullptr)
	{// NULLチェック
		// 初期化
		pObject2D->Init();
	}

	return pObject2D;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CObject2D::CObject2D() :
	m_pVtxBuff(nullptr),
	m_pTexture(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_time(0),
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
	m_time = 0;
	m_rot = 0.0f;
	m_size = POLYGON_SIZE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/Inui Toko 000.jpg",
		&m_pTexture);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(CRenderer::VERTEX_2D) * NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		CRenderer::FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	CRenderer::VERTEX_2D *pVtx = nullptr;	// 頂点情報へのポインタ

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

	// 解放
	CObject::Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CObject2D::Update()
{
	m_time++;

	m_rot += ROTATION_SPEED;

	if (m_rot >= D3DX_PI)
	{// 3.14より大きい
		m_rot -= D3DX_PI * 2.0f;
	}
	else if (m_rot <= -D3DX_PI)
	{// -3.14より小さい
		m_rot += D3DX_PI * 2.0f;
	}

	m_size = POLYGON_SIZE * (((sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f) + 1.0f);

	// 回転
	Rotation(m_pos, m_rot, m_size);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CRenderer::VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(CRenderer::FVF_VERTEX_2D);

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
}

//--------------------------------------------------
// 回転
//--------------------------------------------------
void CObject2D::Rotation(const D3DXVECTOR3& pos, float rot, float size)
{
	D3DXMATRIX mtx, mtxTrans;

	// 回転の反映
	D3DXMatrixRotationZ(&mtx, -rot);

	// 位置の反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);
	
	D3DXVECTOR3 pVtxPos[NUM_VERTEX];

	float halfSize = size * 0.5f;

	pVtxPos[0] = D3DXVECTOR3(-halfSize, -halfSize, 0.0f);
	pVtxPos[1] = D3DXVECTOR3(+halfSize, -halfSize, 0.0f);
	pVtxPos[2] = D3DXVECTOR3(-halfSize, +halfSize, 0.0f);
	pVtxPos[3] = D3DXVECTOR3(+halfSize, +halfSize, 0.0f);

	CRenderer::VERTEX_2D* pVtx = nullptr;	// 頂点情報へのポインタ

	// 頂点情報をロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{// 頂点情報の設定
		D3DXVec3TransformCoord(&pVtx[i].pos, &pVtxPos[i], &mtx);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
