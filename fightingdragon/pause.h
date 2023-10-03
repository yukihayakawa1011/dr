//============================
//
//ポーズ処理(pause.h)
//Author:早川 友貴
//
//============================
#ifndef _PAUSE_H_   //このマクロ定義がされていなかったら
#define _PAUSE_H_   //2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define NUM_PAUSE  (5)		//ポーズメニューの数
#define SPACE_DATA (200.0f) //ポーズメニューの間隔のデータ

class CPause
{
public:
	//ポーズメニュー
	typedef enum
	{
		PAUSE_MENU_CONTINUE = 0,	//ゲームに戻る
		PAUSE_MENU_RETRY,			//ゲームをやり直す
		PAUSE_MENU_QUIT,			//タイトル画面に戻る
		PAUSE_MENU_MAX
	}PAUSE_MENU;

	CPause();
	~CPause();

	static CPause *Create(void);

	//プロトタイプ宣言
	void InitPause(void);
	void UninitPause(void);
	void UpdatePause(void);
	void DrawPause(void);
	void ResetPause(void);

	void SetEnablePause(bool bPause);
	bool GetPause(void);

private:
	LPDIRECT3DTEXTURE9 m_apTexturePause[NUM_PAUSE] = {};		//テクスチャ(3枚分)へのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPause = NULL;		 //頂点バッファへのポインタ
	PAUSE_MENU m_PauseMenu;		//ポーズメニュー
	bool m_Kecheck; //キーが押されたか確認する
	D3DXCOLOR acol[NUM_PAUSE];
	bool m_bPause;			//ポーズ状態のON/OFF
	//VERTEX_2D g_aVertex[4];  //頂点数を格納
};
#endif
