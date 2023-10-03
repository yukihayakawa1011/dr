//============================
//
//マネージャー処理(manager.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include "xaudio2.h"					 //サウンド処理に必要
#include "object2D.h"
#include "anim.h"
#include "bg.h"
//#include "bullet.h"
#include "object3d.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "abg.h"
#include "effect.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "block.h"
#include "camera.h"
#include "light.h"
#include "bilboard.h"
#include "objectx.h"
//#include "shadow.h"
#include "debugproc.h"
//#include "infection.h"
#include "mode.h"

//静的メンバ変数
CRenderer *CManager::m_pRenderer = NULL;				//レンダラーを初期化
CInputKeyboard *CManager::m_pInputKeyboard = NULL;		//キーボード情報を初期化
CDebugProc *CManager::m_pDebugProc = NULL;				//デバッグ情報を初期化
CSound *CManager::m_pSound = NULL;						//サウンド情報を初期化
CScene *CManager::m_pScene = NULL;						//シーン情報を初期化
CScene *CScene::m_pScene = NULL;						//シーン情報を初期化
CInputGamePad *CManager::m_pInputGamePad = NULL;		//ゲームパッド情報を初期化

//============================
//コンストラクタ
//============================
CScene::CScene()
{
	m_Mode = MODE_TITLE;

	m_nMode = 0;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


//============================
//デストラクタ
//============================
CScene::~CScene()
{

}

//============================
//モードの生成
//============================
CScene *CScene::Create(MODE mode)
{
	switch (mode)
	{
	case CScene::MODE_TITLE:
		m_pScene = CTitle::Create(D3DXVECTOR3(640.0f,360.0f,0.0f),0.0f,0);
		break;

	case CScene::MODE_STORY:
		m_pScene = CStory::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);
		break;

	case CScene::MODE_TUTORIAL:
		m_pScene = CTutorial::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);
		break;

	case CScene::MODE_GAME:
		m_pScene = CGame::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0);

		break;

	case CScene::MODE_RESULT:
		m_pScene = CResult::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);
		break;

	case CScene::MODE_GAMEOVER:
		m_pScene = CGameOver::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);
		break;

	case CScene::MODE_MAX:
		break;
	}
	
	if (m_pScene == NULL)
	{
		return NULL;
	}

	return m_pScene;
}

//============================
//シーンの初期化
//============================
HRESULT CScene::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	m_Mode = MODE_TITLE;

	CManager::SetMode(m_Mode);

	return S_OK;
}

//============================
//シーンの終了
//============================
void CScene::Uninit(void)
{
	Release();

	/*if (m_pScene != NULL)
	{
		delete m_pScene;
		m_pScene = NULL;
	}*/
	
}

//============================
//シーンの更新
//============================
void CScene::Update(void)
{
	
}

//============================
//シーンの描画
//============================
void CScene::Draw(void)
{
	
}

//============================
//位置をセットする
//============================
void CScene::SetPosition(D3DXVECTOR3 pos)
{
	
}

//============================
//位置の取得
//============================
D3DXVECTOR3 CScene::GetPosition(void)
{
	return m_pos;
}

//============================
//移動量の取得
//============================
D3DXVECTOR3 CScene::GetMove(void)
{
	return m_pos;
}

//============================
//シーン情報ゲット
//============================
CScene::MODE CScene::GetMode(void)
{
	return m_Mode;
}

//以下マネージャーの処理

//============================
//コンストラクタ
//============================
CManager::CManager()
{

}


//============================
//デストラクタ
//============================
CManager::~CManager()
{

}

//============================
//初期化
//============================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	//NULLチェック
	if (m_pSound == NULL)
	{
		//サウンドの生成
		m_pSound = NEW_DBG CSound;
	}
	else
	{
		return -1;
	}

	if (m_pSound != NULL)
	{
		m_pSound->InitSound(hWnd);
	}

	//NULLチェック
	if (m_pRenderer == NULL)
	{
		//レンダラーの生成
		m_pRenderer = NEW_DBG CRenderer;

	}
	else
	{
		return -1;
	}

	//NULLチェック
	if (m_pRenderer != NULL)
	{
		//初期化処理
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//初期化処理が失敗した場合

			return -1;
		}
	}
	else
	{
		return -1;
	}

	//NULLチェック
	if (m_pScene == NULL)
	{
		m_pScene = CScene::Create(CScene::MODE_TITLE);
	}
	else
	{
		return -1;
	}

	//NULLチェック
	if (m_pDebugProc == NULL)
	{
		m_pDebugProc = NEW_DBG CDebugProc;

		m_pDebugProc->Init();
	}
	else
	{
		return -1;
	}

	//NULLチェック
	if (m_pInputKeyboard == NULL)
	{
		//キーボード入力の生成
		m_pInputKeyboard = NEW_DBG CInputKeyboard;
	}
	else
	{
		return -1;
	}

	
	//NULLチェック
	if (m_pInputKeyboard != NULL)
	{
		//初期化処理
		if (FAILED(m_pInputKeyboard->Init(hinstance, hWnd)))
		{//初期化処理が失敗した場合

			return -1;
		}
	}
	else
	{
		return -1;
	}

	//NULLチェック
	if (m_pInputGamePad == NULL)
	{
		//ゲームパッド入力の生成
		m_pInputGamePad = NEW_DBG CInputGamePad;
	}
	else
	{
		return -1;
	}


	//NULLチェック
	if (m_pInputGamePad != NULL)
	{
		//初期化処理
		if (FAILED(m_pInputGamePad->Init(hWnd)))
		{//初期化処理が失敗した場合

			return -1;
		}
	}
	else
	{
		return -1;
	}

	return S_OK;
}
//============================
//終了
//============================
void CManager::Uninit(void)
{
	////オブジェクト全ての破棄
	//CObject::ReleaseAll();

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		
		m_pScene = NULL;
	}

	//キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		//終了処理
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;

		m_pInputKeyboard = NULL;
	}

	//ゲームパッド破棄
	if (m_pInputGamePad != NULL)
	{
		//終了処理
		m_pInputGamePad->Uninit();

		delete m_pInputGamePad;

		m_pInputGamePad = NULL;
	}

	//デバッグの破棄
	if (m_pDebugProc != NULL)
	{
		//終了処理
		m_pDebugProc->Uninit();

		delete m_pDebugProc;

		m_pDebugProc = NULL;
	}

	//レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		//終了処理
		m_pRenderer->Uninit();

		delete m_pRenderer;

		m_pRenderer = NULL;
	}

	if (m_pSound != NULL)
	{
		//サウンドの停止
		m_pSound->StopSound();

		//サウンドの終了処理
		m_pSound->UninitSound();

		delete m_pSound;

		m_pSound = NULL;
	}
}
//============================
//更新
//============================
void CManager::Update(void)
{
	/*UpdateShadow();*/

	//キーボードの更新
	m_pInputKeyboard->Update();

	//ゲームパッドの更新
	m_pInputGamePad->Update();

	//デバッグの更新
	m_pDebugProc->Update();

	//レンダラーの更新
	m_pRenderer->Update();
}
//============================
//描画
//============================
void CManager::Draw(void)
{//画面クリア(バックバッファとZバッファのクリア)

	//DrawShadow();

	//レンダラーの描画
	m_pRenderer->Draw();
}

//============================
//サウンドの情報取得
//============================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//============================
//レンダラーの情報取得
//============================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//============================
//キーボード情報取得
//============================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//============================
//デバッグの情報取得
//============================
CDebugProc *CManager::GetDebugProck(void)
{
	return m_pDebugProc;
}

//============================
//シーンの情報セット
//============================
void CManager::SetMode(CScene::MODE mode)
{
	//サウンドの停止
	m_pSound->StopSound();

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		
		m_pScene = NULL;
	}

	m_pScene = CScene::Create(mode);
}

//============================
//ゲームパッド情報取得
//============================
CInputGamePad *CManager::GetGamePad(void)
{
	return m_pInputGamePad;
}



