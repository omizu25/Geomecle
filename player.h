//**************************************************
// 
// player.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PLAYER_H_	//このマクロ定義がされてなかったら
#define _PLAYER_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include <d3dx9.h>
#include "object2D.h"

//==================================================
// 定義
//==================================================
class CPlayer : public CObject2D
{
public:
	static CPlayer* CPlayer::Create();	// 生成

public:
	CPlayer();		// デフォルトコンストラクタ
	 ~CPlayer();	// デストラクタ

public: /* メンバ関数 */
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

private:
	void Move();	// 移動

private: /* メンバ変数 */
};

#endif // !_OBJECT_H_
