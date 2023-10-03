//============================
//
//ポーズ処理(pause.cpp)
//Author:早川 友貴
//
//============================
#include "mode.h"
#include "pause.h"
#include "input.h"
#include "time.h"
#include "manager.h"
#include "renderer.h"

//========================
//ポーズ画面のコンストラクタ
//========================
CPause::CPause()
{
	for (int nCnt = 0; nCnt < NUM_PAUSE; nCnt++)
	{
		m_apTexturePause[nCnt] = NULL;		//テクスチャ(3枚分)へのポインタ
		acol[nCnt] = nCnt;
	}

	 m_pVtxBuffPause = NULL;		 //頂点バッファへのポインタ
	 m_PauseMenu;		//ポーズメニュー
	 m_Kecheck; //キーが押されたか確認する

	 m_bPause = false;
}

//========================
//ポーズ画面のデストラクタ
//========================
CPause::~CPause()
{
	
}

//============================
//モードの生成
//============================
CPause *CPause::Create(void)
{
	CPause *pPause;

	pPause = new CPause;


	if (pPause == NULL)
	{
		return NULL;
	}

	pPause->InitPause();

	return pPause;
}

//========================
//ポーズ画面の初期化処理
//========================
void CPause::InitPause(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	int nCntPause;

	m_bPause = false;

	//カラーを初期化
	 acol[0] = D3DXCOLOR(1.0f,1.0f,1.0f, 1.0f);
	 acol[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	 acol[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	 acol[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	 acol[4] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//キーチェックを初期化
	m_Kecheck = false;

	//ポーズメニューを初期化
	m_PauseMenu = PAUSE_MENU_CONTINUE;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\continue.png",
		&m_apTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\retry.png",
	&m_apTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\exitgame.png",
		&m_apTexturePause[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enter.png",
		&m_apTexturePause[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pausecon.png",
		&m_apTexturePause[4]);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPause,
		NULL);

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(150.0f , 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(500.0f , 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(150.0f , 300.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(500.0f , 300.0f, 0.0f);

		if(nCntPause == 3)
		{
			pVtx[0].pos = D3DXVECTOR3(600.0f, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(800.0f, 400.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(600.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, 600.0f, 0.0f);
		}

		if (nCntPause == 4)
		{
			pVtx[0].pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(700.0f, 400.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(500.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(700.0f, 600.0f, 0.0f);
		}

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + 1.0f);

		pVtx += 4;   //頂点データのポインタを4つ分進める

	}

	//頂点バッファをアンロックする
	m_pVtxBuffPause->Unlock();

}

//======================
//ポーズの終了処理
//======================
void CPause::UninitPause(void)
{
	int nCntPause;

	//3枚目のテクスチャの破棄
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (m_apTexturePause[nCntPause] != NULL)
		{
			m_apTexturePause[nCntPause]->Release();
			m_apTexturePause[nCntPause] = NULL;
		}
	}

	//頂点バッファの破棄
	if (m_pVtxBuffPause != NULL)
	{
		m_pVtxBuffPause->Release();
		m_pVtxBuffPause = NULL;
	}
}

//=========================
//ポーズの更新処理
//=========================
void CPause::UpdatePause(void)
{
	int nCntPause;
	bool bPause;
	bPause = GetPause();

	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//キーボードの取得
	pInputKeyboard = CManager::GetInputKeyboard();

	//ゲームパッドの取得
	pInputGamepad = CManager::GetGamePad();

	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	for (nCntPause = 0; nCntPause < 3; nCntPause++)
	{
		if (m_PauseMenu == nCntPause)
		{
			acol[nCntPause] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		}

		else if (nCntPause != m_PauseMenu)
		{
			acol[nCntPause] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_UP, 0) == true)
	{//上操作が行われた場合


	 //サウンドの再生
		//PlaySound(SOUND_LABEL_TUTORIAL);

		switch (m_PauseMenu)
		{
		case PAUSE_MENU_CONTINUE:

			m_PauseMenu = PAUSE_MENU_QUIT;

			break;

		case PAUSE_MENU_QUIT:

			m_PauseMenu = PAUSE_MENU_RETRY;

			break;

		case PAUSE_MENU_RETRY:

			m_PauseMenu = PAUSE_MENU_CONTINUE;

			break;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_DOWN, 0) == true)
	{//下操作が行われた場合


	 //サウンドの再生
		//PlaySound(SOUND_LABEL_TUTORIAL);

		switch (m_PauseMenu)
		{
		case PAUSE_MENU_CONTINUE:

			m_PauseMenu = PAUSE_MENU_RETRY;

			break;

		case PAUSE_MENU_RETRY:

			m_PauseMenu = PAUSE_MENU_QUIT;

			break;

		case PAUSE_MENU_QUIT:

			m_PauseMenu = PAUSE_MENU_CONTINUE;

			break;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{//決定キー(ENTER)が押された

		//PlaySound(SOUND_LABEL_ENTER);

		if (m_Kecheck == false)
		{

			switch (m_PauseMenu)
			{
			case PAUSE_MENU_CONTINUE:

				SetEnablePause(bPause = false);

				break;

			case PAUSE_MENU_RETRY:

				m_Kecheck = true;

				/*SetFade(MODE_GAME);*/

				

				break;

			case PAUSE_MENU_QUIT:

				m_Kecheck = true;

				/*SetFade(MODE_TITLE);*/

				/*ResetTime();*/

				break;
			}
		}
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (bPause == true)
	{
		for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(500.0f, 100.0f + (nCntPause * SPACE_DATA), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(800.0f, 100.0f + (nCntPause * SPACE_DATA), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(500.0f, 200.0f + (nCntPause * SPACE_DATA), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, 200.0f + (nCntPause * SPACE_DATA), 0.0f);

			if (nCntPause == 3)
			{
				pVtx[0].pos = D3DXVECTOR3(1050.0f, 620.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(1250.0f, 620.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(1050.0f, 720.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(1250.0f, 720.0f, 0.0f);
			}

			if (nCntPause == 4)
			{
				pVtx[0].pos = D3DXVECTOR3(800.0f, 620.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(1000.0f,620.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(800.0f, 720.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(1000.0f,720.0f, 0.0f);
			}

			pVtx[0].col = acol[nCntPause];
			pVtx[1].col = acol[nCntPause];
			pVtx[2].col = acol[nCntPause];
			pVtx[3].col = acol[nCntPause];

			//テクスチャ座標の更新
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;   //頂点データのポインタを4つ分進める
		}

		//頂点バッファをアンロックする
		m_pVtxBuffPause->Unlock();
	}
}

//======================
//ポーズの描画処理
//======================
void CPause::DrawPause(void)
{
	int nCntPause;

	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		pDevice->SetTexture(0, m_apTexturePause[nCntPause]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2); //プリミティブの種類

	}
}

//=======================
//ポーズメニューのリセット
//=======================
void CPause::ResetPause(void)
{
	//ポーズメニューを初期化
	m_PauseMenu = PAUSE_MENU_CONTINUE;
}

//===================================
//ポーズ状態の取得
//===================================
void CPause::SetEnablePause(bool bPause)
{
	m_bPause = bPause;
}

//========================
//ポーズ状態の取得
//========================
bool CPause::GetPause(void)
{
	return m_bPause;
}