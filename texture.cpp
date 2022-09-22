//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "texture.h"
#include "application.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CTexture::FILE_NAME[] =
{// テクスチャのパス
	"data/TEXTURE/icon_122380_256.png",	// プレイヤー
	"data/TEXTURE/icon_122540_256.png",	// 弾
	"data/TEXTURE/Homing.png",			// ホーミング
	"data/TEXTURE/HomingAI.png",		// AIホーミング
	"data/TEXTURE/HomingDivision.png",	// 分裂ホーミング
	"data/TEXTURE/PaperAirplane.png",	// 紙飛行機
	"data/TEXTURE/Windmill.png",		// 風車
	"data/TEXTURE/snake_body.png",		// 蛇の体
	"data/TEXTURE/Number.png",			// 数
	"data/TEXTURE/result.png",			// リザルト
	"data/TEXTURE/title.png",			// タイトル
	"data/TEXTURE/effect.jpg",			// エフェクト
	"data/TEXTURE/bg.png",				// 背景
	"data/TEXTURE/mul.png",				// 掛ける
	"data/TEXTURE/rank.png",			// 位
	"data/TEXTURE/ranking.png",			// ランキング
	"data/TEXTURE/NewScore.png",		// 新しいスコア
	"data/TEXTURE/Tutorial.png",		// チュートリアル
	"data/TEXTURE/Comma.png",			// カンマ
};

static_assert(sizeof(CTexture::FILE_NAME) / sizeof(CTexture::FILE_NAME[0]) == CTexture::LABEL_MAX, "aho");

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
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
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの読み込みがされている
			continue;
		}

		// 読み込み
		Load((ELabel)i);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(ELabel label)
{
	assert(label >= 0 && label < LABEL_MAX);

	if (s_pTexture[label] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		FILE_NAME[label],
		&s_pTexture[label]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::ReleaseAll()
{
	for (int i = 0; i < LABEL_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Release(ELabel label)
{
	assert(label >= 0 && label < LABEL_MAX);

	if (s_pTexture[label] != nullptr)
	{// テクスチャの解放
		s_pTexture[label]->Release();
		s_pTexture[label] = nullptr;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::Get(ELabel label)
{
	if (label == LABEL_NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(label >= 0 && label < LABEL_MAX);

	// 読み込み
	Load(label);

	return s_pTexture[label];
}
