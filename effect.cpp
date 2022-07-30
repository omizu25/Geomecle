//**************************************************
// 
// effect.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "effect.h"
#include "application.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEffect::STD_SIZE = 25.0f;
const float CEffect::STD_MOVE = 10.0f;

//==================================================
// 静的メンバ変数
//==================================================
int CEffect::m_numAll = 0;
IDirect3DVertexBuffer9* CEffect::vtxBuf = nullptr;
IDirect3DVertexBuffer9* CEffect::worldPosBuf = nullptr;
IDirect3DVertexBuffer9* CEffect::colBuf = nullptr;
IDirect3DVertexDeclaration9* CEffect::decl = nullptr;
IDirect3DIndexBuffer9* CEffect::indexBuf = nullptr;
ID3DXEffect* CEffect::effect = nullptr;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, float rot)
{
	if (m_numAll >= CObject::GetMax(CObject::CATEGORY_EFFECT))
	{// 最大数を越した
		return nullptr;
	}

	CEffect* pEffect = nullptr;

	pEffect = new CEffect;

	if (pEffect != nullptr)
	{// nullチェック
		pEffect->Init();
		pEffect->m_pos = pos;
		pEffect->m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;
		pEffect->m_col = D3DXCOLOR(FloatRandam(1.0f, 0.0f), FloatRandam(1.0f, 0.0f), FloatRandam(1.0f, 0.0f), 1.0f);
	}

	return pEffect;
}

//--------------------------------------------------
// 総数の取得
//--------------------------------------------------
int CEffect::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// インスタンシングの初期化
//--------------------------------------------------
void CEffect::InitInstancing()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	Vtx vtx[4] = {	// 単位板ポリバッファ
		{ -STD_SIZE, -STD_SIZE, 0.0f, 0.0f},
		{ +STD_SIZE, -STD_SIZE, 1.0f, 0.0f},
		{ -STD_SIZE, +STD_SIZE, 0.0f, 1.0f},
		{ +STD_SIZE, +STD_SIZE, 1.0f, 1.0f}
	};

	// 頂点バッファ作成
	pDevice->CreateVertexBuffer(sizeof(vtx), 0, 0, D3DPOOL_MANAGED, &vtxBuf, 0);

	{
		void *p = 0;
		vtxBuf->Lock(0, 0, &p, 0);
		memcpy(p, vtx, sizeof(vtx));
		vtxBuf->Unlock();
	}

	// インデックスバッファ
	WORD index[4] = { 0, 1, 2, 3 };
	pDevice->CreateIndexBuffer(sizeof(index), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &indexBuf, 0);
	void *p = 0;
	indexBuf->Lock(0, 0, &p, 0);
	memcpy(p, index, sizeof(index));
	indexBuf->Unlock();

	// 頂点宣言作成
	D3DVERTEXELEMENT9 declElems[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },	// Local coord
		{ 0, 8, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },	// UV
		{ 1, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },	// ワールド位置
		{ 2, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },	// 色
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(declElems, &decl);

	// シェーダ作成
	ID3DXBuffer *errBuf = 0;
	D3DXCreateEffectFromFileA(pDevice, "data/TEXT/Effect.fx", 0, 0, 0, 0, &effect, &errBuf);
	if (errBuf) {
		const char *errMsg = (const char*)errBuf->GetBufferPointer();
		OutputDebugStringA(errMsg);
		return;
	}
}

//--------------------------------------------------
// インスタンシングの終了
//--------------------------------------------------
void CEffect::UninitInstancing()
{
	vtxBuf->Release();
	decl->Release();
	indexBuf->Release();
	effect->Release();
}

//--------------------------------------------------
// インスタンシングの描画
//--------------------------------------------------
void CEffect::DrawInstancing()
{
	if (m_numAll == 0)
	{// 表示されていない
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(D3DXVECTOR2) * m_numAll, 0, 0, D3DPOOL_MANAGED, &worldPosBuf, 0);
	pDevice->CreateVertexBuffer(sizeof(D3DXCOLOR) * m_numAll, 0, 0, D3DPOOL_MANAGED, &colBuf, 0);

	{// エフェクトの情報取得
		D3DXVECTOR2* worldPos = new D3DXVECTOR2[m_numAll];	// ワールド座標位置バッファ
		D3DXCOLOR* col = new D3DXCOLOR[m_numAll];

		CEffect** pObject = (CEffect**)CObject::GetMyObject(CObject::CATEGORY_EFFECT);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		int num = 0;

		for (int i = 0; i < CObject::GetMax(CObject::CATEGORY_EFFECT); i++)
		{
			if (pObject[i] == nullptr)
			{
				continue;
			}
			pos = pObject[i]->m_pos;

			worldPos[num].x = pos.x;
			worldPos[num].y = pos.y;

			col[num] = pObject[i]->m_col;

			num++;
		}

		assert(num == m_numAll);

		{
			void *p = 0;
			worldPosBuf->Lock(0, 0, &p, 0);
			memcpy(p, worldPos, sizeof(D3DXVECTOR2) * m_numAll);
			worldPosBuf->Unlock();

			colBuf->Lock(0, 0, &p, 0);
			memcpy(p, col, sizeof(D3DXCOLOR) * m_numAll);
			colBuf->Unlock();
		}

		delete[] worldPos;
		delete[] col;
	}

	// インスタンス宣言
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | m_numAll);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | (unsigned)1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | (unsigned)1);

	// 頂点とインデックスを設定して描画
	pDevice->SetVertexDeclaration(decl);
	pDevice->SetStreamSource(0, vtxBuf, 0, sizeof(Vtx));
	pDevice->SetStreamSource(1, worldPosBuf, 0, sizeof(D3DXVECTOR2));
	pDevice->SetStreamSource(2, colBuf, 0, sizeof(D3DXCOLOR));
	pDevice->SetIndices(indexBuf);

	effect->SetTechnique("tech");
	UINT passNum = 0;
	effect->Begin(&passNum, 0);
	effect->BeginPass(0);

	effect->SetTexture("tex", CApplication::GetInstanse()->GetTexture()->Get(CTexture::LABEL_Effect));
	effect->SetFloat("screenW", CApplication::SCREEN_WIDTH * 0.5f);
	effect->SetFloat("screenH", CApplication::SCREEN_HEIGHT * 0.5f);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 4, 0, 2);

	effect->EndPass();
	effect->End();

	// 後始末
	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
	pDevice->SetStreamSourceFreq(2, 1);
	
	worldPosBuf->Release();
	colBuf->Release();
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEffect::CEffect() : CObject(CObject::CATEGORY_EFFECT),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
{
	m_numAll++;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEffect::~CEffect()
{
	m_numAll--;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEffect::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEffect::Uninit()
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEffect::Update()
{
	m_pos += m_move;

	//慣性・移動量を更新 (減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.01f;
	m_move.y += (0.0f - m_move.y) * 0.01f;

	float move = D3DXVec3Length(&m_move);

	if (move <= 1.0f)
	{
		CObject::Release();
		return;
	}

	float size = (STD_SIZE * 0.5f) + (CWall::GetWidth() * 0.5f);
	float wall = (CWall::GetLength() * 0.5f) - size;

	if (m_pos.x >= 1280)
	{// 右の壁
		m_pos.x = 1280;
		m_move.x *= -1.0f;
	}
	else if (m_pos.x <= -0)
	{// 左の壁
		m_pos.x = -0;
		m_move.x *= -1.0f;
	}

	if (m_pos.y >= 720)
	{// 上の壁
		m_pos.y = 720;
		m_move.y *= -1.0f;
	}
	else if (m_pos.y <= -0)
	{// 下の壁
		m_pos.y = -0;
		m_move.y *= -1.0f;
	}

	m_col.a += (0.0f - m_col.a) * 0.01f;
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEffect::Draw()
{
	/* インスタンシングで描画 */
}
