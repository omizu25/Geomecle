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
IDirect3DVertexBuffer9* CEffect::uvBuf = nullptr;
IDirect3DVertexBuffer9* CEffect::worldPosBuf = nullptr;
IDirect3DVertexDeclaration9* CEffect::decl = nullptr;
IDirect3DIndexBuffer9* CEffect::indexBuf = nullptr;
ID3DXEffect* CEffect::effect = nullptr;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, float rot)
{
	CEffect* pEffect = nullptr;

	pEffect = new CEffect;

	if (pEffect != nullptr)
	{// nullチェック
		pEffect->Init();
		pEffect->SetPos(pos);
		pEffect->SetRot(rot);
		pEffect->m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;
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
		{ 2, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },	// チップのUV
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
	{
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	pDevice->CreateVertexBuffer(sizeof(WorldPos) * m_numAll, 0, 0, D3DPOOL_MANAGED, &worldPosBuf, 0);
	pDevice->CreateVertexBuffer(sizeof(UV) * m_numAll, 0, 0, D3DPOOL_MANAGED, &uvBuf, 0);

	{// エフェクトの情報取得
		WorldPos *worldPos = new WorldPos[m_numAll];	// ワールド座標位置バッファ

		CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_EFFECT);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		for (int i = 0; i < CObject::GetMax(CObject::CATEGORY_EFFECT); i++)
		{
			if (pObject[i] == nullptr)
			{
				continue;
			}
			pos = pObject[i]->GetPos();

			worldPos[i].x = pos.x;
			worldPos[i].y = pos.y;
		}

		{
			void *p = 0;
			worldPosBuf->Lock(0, 0, &p, 0);
			memcpy(p, worldPos, sizeof(WorldPos) * m_numAll);
			worldPosBuf->Unlock();
		}

		delete[] worldPos;
	}

	{
		UV *p = 0;
		uvBuf->Lock(0, 0, (void**)&p, 0);

		for (int i = 0; i < m_numAll; i++)
		{
			p[i].u = 0.0f;
			p[i].v = 1.0f;
		}

		uvBuf->Unlock();
	}

	// インスタンス宣言
	pDevice->SetStreamSourceFreq(0, D3DSTREAMSOURCE_INDEXEDDATA | m_numAll);
	pDevice->SetStreamSourceFreq(1, D3DSTREAMSOURCE_INSTANCEDATA | (unsigned)1);
	pDevice->SetStreamSourceFreq(2, D3DSTREAMSOURCE_INSTANCEDATA | (unsigned)1);

	// 頂点とインデックスを設定して描画
	pDevice->SetVertexDeclaration(decl);
	pDevice->SetStreamSource(0, vtxBuf, 0, sizeof(Vtx));
	pDevice->SetStreamSource(1, worldPosBuf, 0, sizeof(WorldPos));
	pDevice->SetStreamSource(2, uvBuf, 0, sizeof(UV));
	pDevice->SetIndices(indexBuf);

	effect->SetTechnique("tech");
	UINT passNum = 0;
	effect->Begin(&passNum, 0);
	effect->BeginPass(0);

	effect->SetTexture("tex", CApplication::GetInstanse()->GetTexture()->Get(CTexture::LABEL_bright));
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
	uvBuf->Release();
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEffect::CEffect() : CObject3D(CObject::CATEGORY_EFFECT),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
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
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject3D::TYPE_BULLET);

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_icon_122540_256);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEffect::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEffect::Update()
{
	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;

	// 位置の設定
	CObject3D::SetPos(pos);

	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEffect::Draw()
{
	/* インスタンシングで描画 */
}
