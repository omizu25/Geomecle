//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "texture.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CTexture::s_FileName[] =
{// テクスチャのパス
	"data/TEXTURE/icon_122380_256.png",	// 仮画像1
	"data/TEXTURE/icon_122540_256.png",	// 仮画像2
};

CTexture* CTexture::m_pTexture = nullptr;

static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "aho");

//--------------------------------------------------
// 生成
//--------------------------------------------------
CTexture* CTexture::Instanse()
{
	if (m_pTexture == nullptr)
	{// nullチェック
		m_pTexture = new CTexture;
	}

	return m_pTexture;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CTexture::LoadAll()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetDevice();
	
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// テクスチャの読み込みがされている
			continue;
		}

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::UnloadAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Unload(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// テクスチャの解放
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// 取得
// 引数  : char* inFileName / 文字列 ファイル名
// 返値  : TEXTURE / テクスチャの種類
//--------------------------------------------------
CTexture::TEXTURE CTexture::GetFileName(char* inFileName)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (strcmp(inFileName, s_FileName[i]) == 0)
		{// 文字列が同じ
			// 読み込み
			Load((TEXTURE)i);

			return (TEXTURE)i;
		}
	}

	assert(false);
	return TEXTURE_NONE;
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// テクスチャを使用しない
		return NULL;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// 読み込み
	Load(inTexture);

	return s_pTexture[inTexture];
}
