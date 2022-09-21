//**************************************************
// 
// ranking.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "ranking.h"
#include "score.h"
#include "number_manager.h"
#include "number.h"
#include "utility.h"

#include <assert.h>
#include <stdio.h>

//==================================================
// 定義
//==================================================
const float CRanking::STD_WIDTH = 40.0f;
const float CRanking::STD_HEIGHT = 50.0f;
const char* CRanking::FILE_NAME = "data/TEXT/Ranking.txt";

//==================================================
// 静的メンバ変数
//==================================================
int CRanking::m_score = 0;
int CRanking::m_ranking[MAX_RANKING] = {};

//--------------------------------------------------
// 生成
//--------------------------------------------------
CRanking* CRanking::Create(const D3DXVECTOR3& pos, float length)
{
	CRanking* pRanking = nullptr;

	pRanking = new CRanking;

	if (pRanking != nullptr)
	{// nullチェック
		// 初期化
		pRanking->Init(pos, length);
	}

	return pRanking;
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CRanking::Load()
{
	FILE *pFile = nullptr;

	// ファイルを開く
	pFile = fopen(FILE_NAME, "r");

	if (pFile != nullptr)
	{// ファイルが開いた場合

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fscanf(pFile, "%d", &m_ranking[i]);
		}
		
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);
	}
}

//--------------------------------------------------
// 保存
//--------------------------------------------------
void CRanking::Save()
{
	FILE *pFile = nullptr;

	// ファイルを開く
	pFile = fopen(FILE_NAME, "w");

	if (pFile != nullptr)
	{// ファイルが開いた場合

		for (int i = 0; i < MAX_RANKING; i++)
		{
			fprintf(pFile, "%d\n\n", m_ranking[i]);
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開かない場合
		assert(false);
	}
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CRanking::Set(int score)
{
	m_score = score;

	// 読み込み
	Load();

	// 変更
	Change();

	// 保存
	Save();
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CRanking::Get(int rank)
{
	if (rank == -1)
	{// 指定の値
		return m_score;
	}

	assert(rank >= 0 && rank < MAX_RANKING);

	return m_ranking[rank];
}

//--------------------------------------------------
// 変更
//--------------------------------------------------
void CRanking::Change()
{
	int ranking[MAX_RANKING + 1] = {};

	for (int i = 0; i < MAX_RANKING; i++)
	{
		ranking[i] = m_ranking[i];
	}

	ranking[MAX_RANKING] = m_score;

	int save = 0;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		save = ranking[i];

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (save < ranking[j])
			{// 相手が大きかったら交代
				save = ranking[j];
			}
		}

		for (int j = i + 1; j < MAX_RANKING + 1; j++)
		{
			if (save == ranking[j])
			{// 最大値を探して交代
				ranking[j] = ranking[i];
				ranking[i] = save;
				break;
			}
		}
	}

	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_ranking[i] = ranking[i];
	}
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CRanking::CRanking()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		m_pRanking[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRanking::~CRanking()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		assert(m_pRanking[i] == nullptr);
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CRanking::Init(const D3DXVECTOR3& pos, float length)
{
	D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

	float PosX = 0.0f;
	float PosY = 0.0f;
	float height = STD_HEIGHT;

	if (length <= 0.0f)
	{// 値がマイナス
		height *= -1.0f;
	}

	float maxWidth = CNumberManager::MAX_DIGIT * size.x;

	for (int i = 0; i < MAX_RANKING; i++)
	{
		PosX = pos.x - (maxWidth - (Digit(m_ranking[i]) * size.x));
		PosY = pos.y + (i * (length + height));

		// スコアの生成
		m_pRanking[i] = CScore::Create(D3DXVECTOR3(PosX, PosY, 0.0f), size);

		// スコアの設定
		m_pRanking[i]->Set(m_ranking[i]);

		// 順位の生成
		CNumber* pNumber = CNumber::Create(D3DXVECTOR3(pos.x - maxWidth - size.x, PosY, 0.0f), size);
		pNumber->Change(i + 1);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CRanking::Uninit()
{
	for (int i = 0; i < MAX_RANKING; i++)
	{
		// 解放
		m_pRanking[i]->Uninit();

		m_pRanking[i] = nullptr;
	}
}
