//============================
//
//モード処理(mode.h)
//Author:早川 友貴
//
//============================
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
#include "pause.h"

CPlayer *CGame::m_pPlayer = NULL;					//プレイヤー情報を初期化
CPlayer *CGame::m_pPlayerMirror = NULL;					//プレイヤー情報を初期化
CExplosion *CGame::m_pExplosion = NULL;				//爆発情報を初期化
CEnemy *CGame::m_pEnemy = NULL;						//敵情報を初期化
CAbg *CGame::m_pAbg = NULL;							//多重背景を初期化
CEffect *CGame::m_pEffect = NULL;					//エフェクト情報を初期化
CScore *CGame::m_pScore = NULL;						//スコア情報を初期化
CTime *CGame::m_pTime = NULL;						//タイム情報を初期化
CBlock *CGame::m_pBlock = NULL;						//ブロック情報を初期化
CCamera *CGame::m_pCamera = NULL;					//カメラ情報を初期化
CLight *CGame::m_pLight = NULL;						//ライト情報を初期化
CObjectx *CGame::m_pObjectx[USE_OBJECTX] = {};		//オブジェクトX情報を初期化
CModel *CGame::m_pModel = NULL;						//モデル情報を初期化
CInfection *CGame::m_pInfection = NULL;				//感染情報情報を初期化
CObject3d *CGame::m_pObject3d = NULL;				//感染情報情報を初期化
CPause *CGame::m_pPause = NULL;				//感染情報情報を初期化

//============================
//タイトルコンストラクタ
//============================
CTitle::CTitle()
{
	m_pTexture = NULL;				//テクスチャのポインタ
	m_pVtxBuff = NULL;				//頂点バッファへのポインタ
}

//============================
//タイトルデストラクタ
//============================
CTitle::~CTitle()
{

}

//===========================
//生成
//===========================
CTitle *CTitle::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CTitle *pTitle;

	//オブジェクト2Dの生成
	pTitle = NEW_DBG CTitle;

	//初期化処理
	pTitle->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pTitle;
}

//===========================
//タイトル初期化
//===========================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\infection_title.png",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファがNULLだったら
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//テクスチャのポインタがNULLだったら
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////角度を決める
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////長さを算出する
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////頂点座標の設定
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(法線)の設定
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
//タイトル終了
//===========================
void CTitle::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点情報の破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	
	CScene::Uninit();

	ReleaseAll();
}

//===========================
//タイトル更新
//===========================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//キーボードの取得
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		
		CManager::GetInstance()->SetMode(MODE_STORY);
			
		CSound::PlaySound(CSound::SOUND_LABEL_SE_TITLEENTER);

	}
	

//#ifdef _DEBUG
//
//	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
//	{
//		CManager::SetMode(MODE_GAME);
//	}
//
//#endif // DEBUG

}

//===========================
//タイトル描画
//===========================
void CTitle::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類
}

//============================
//ストーリーコンストラクタ
//============================
CStory::CStory()
{
	m_pTexture = NULL;				//テクスチャのポインタ
	m_pVtxBuff = NULL;				//頂点バッファへのポインタ
}

//============================
//ストーリーデストラクタ
//============================
CStory::~CStory()
{

}

//===========================
//ストーリー生成
//===========================
CStory *CStory::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CStory *pStory;

	//オブジェクト2Dの生成
	pStory = NEW_DBG CStory;

	//初期化処理
	pStory->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pStory;
}

//===========================
//ストーリー初期化
//===========================
HRESULT CStory::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\story.png",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファがNULLだったら
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//テクスチャのポインタがNULLだったら
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////角度を決める
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////長さを算出する
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////頂点座標の設定
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(法線)の設定
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
//ストーリー終了
//===========================
void CStory::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点情報の破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//ストーリー更新
//===========================
void CStory::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//キーボードの取得
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_TUTORIAL);

		CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTORIALENTER);
	}


	//#ifdef _DEBUG
	//
	//	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//	{
	//		CManager::SetMode(MODE_GAME);
	//	}
	//
	//#endif // DEBUG

}

//===========================
//ストーリー描画
//===========================
void CStory::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類
}

//============================
//チュートリアルコンストラクタ
//============================
CTutorial::CTutorial()
{
	m_pTexture = NULL;				//テクスチャのポインタ
	m_pVtxBuff = NULL;				//頂点バッファへのポインタ
}

//============================
//チュートリアルデストラクタ
//============================
CTutorial::~CTutorial()
{

}

//===========================
//チュートリアル生成
//===========================
CTutorial *CTutorial::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CTutorial *pTutorial;

	//オブジェクト2Dの生成
	pTutorial = NEW_DBG CTutorial;

	//初期化処理
	pTutorial->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pTutorial;
}

//===========================
//チュートリアル初期化
//===========================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\tutorial0.png",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファがNULLだったら
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//テクスチャのポインタがNULLだったら
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////角度を決める
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////長さを算出する
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////頂点座標の設定
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(法線)の設定
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
//チュートリアル終了
//===========================
void CTutorial::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点情報の破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//チュートリアル更新
//===========================
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//キーボードの取得
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_GAME);

		CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTORIALENTER);
	}


	//#ifdef _DEBUG
	//
	//	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//	{
	//		CManager::SetMode(MODE_GAME);
	//	}
	//
	//#endif // DEBUG

}

//===========================
//チュートリアル描画
//===========================
void CTutorial::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類
}

//============================
//ゲームコンストラクタ
//============================
CGame::CGame()
{
	m_pBlock = NULL;

	m_pEnemy = NULL;

	m_pTime = NULL;

	m_pInfection = NULL;

	m_pPlayer = NULL;

	m_pCamera = NULL;

	m_pLight = NULL;

	m_pObject3d = NULL;

	m_pPause = NULL;

	m_bPause = false;
}

//============================
//ゲームデストラクタ
//============================
CGame::~CGame()
{

}

//===========================
//生成
//===========================
CGame *CGame::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CGame *pGame;

	//オブジェクト2Dの生成
	pGame = NEW_DBG CGame;

	//初期化処理
	pGame->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pGame;
}

//===========================
//ゲーム初期化
//===========================
HRESULT CGame::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	nTex = 0;

	fRot = 0.0f;

	m_bPause = false;

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//CAbg::Load();			//多重背景テクスチャロード

	CScore::Load();			//スコアテクスチャロード

	//CEffect::Load(0);		//エフェクトテクスチャロード

							//CExplosion::Load();		//爆発テクスチャロード

							CBlock::Load();			//ブロックテクスチャロード

							//CEnemy::Load();			//敵テクスチャロード

							//CPlayer::Load();		//プレイヤーテクスチャロード

	CObject3d::Load();		//オブジェクト3dテクスチャロード

							//CBilboard::Load();		//ビルボードテクスチャロード

							////オブジェクトの生成(初期化も)
							//CBg::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 50.0f, 0);

							////多重背景の生成
							//CAbg::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);

							////アニメーションの生成
							//CAnim::Create(D3DXVECTOR3(800.0f, 500.0f, 0.0f), 50.0f, 0);

							/*InitShadow();*/


	if (m_pObject3d == NULL)
	{
		////オブジェクト3Dの生成
		m_pObject3d = CObject3d::Create(D3DXVECTOR3(-250.0f, 0.0f, 0.0f), 50.0f, 0, 50.0f, 50.0);
	}
	else
	{
		return -1;
	}

	if (m_pEnemy == NULL)
	{//敵の生成
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(-250.0f, 0.0f, 0.0f), D3DX_PI * -0.5f, 0, 50.0f, 50.0f);
	}
	else
	{
		return -1;
	}


	//NULLチェック
	if (m_pPlayer == NULL)
	{
		//プレイヤーの生成
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(300.0f, 2.0f, -10.0f), D3DX_PI * 0.5f, 1, 20.0f, 20.0f);
	}
	else
	{
		return -1;
	}

	//if (m_pScore == NULL)
	//{
	//	//スコアの生成
	//	m_pScore = CScore::Create(D3DXVECTOR3(300.0f, 700.0f, 0.0f), 0.0f, 0);
	//}
	////CBilboard::Create(D3DXVECTOR3(-400.0f, 0.0f, 0.0f), 0.0f, 0, 200.0f, 200.0f);

	//カメラの生成
	if (m_pCamera == NULL)
	{
		m_pCamera = NEW_DBG CCamera;
		m_pCamera->Init();
	}

	//ライトの生成
	if (m_pLight == NULL)
	{
		m_pLight = NEW_DBG CLight;
		m_pLight->Init();
	}

	////ポーズの生成
	//if (m_pPause == NULL);
	//{
	//	m_pPause = NEW_DBG CPause;
	//}

	return S_OK;
}

//===========================
//ゲーム終了
//===========================
void CGame::Uninit(void)
{
	//カメラの破棄
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	//ライトの破棄
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();

		delete  m_pLight;
		m_pLight = NULL;
	}

	////多重背景のテクスチャ破棄
	//CAbg::Unload();

	//スコアテクスチャのテクスチャ破棄
	CScore::Unload();

	////タイムテクスチャのテクスチャ破棄
	//CTime::Unload();

	////弾のテクスチャ破棄
	//CBullet::Unload();

	//エフェクトのテクスチャ破棄
	CEffect::Unload();

	//敵のテクスチャ破棄
	CEnemy::Unload();

	////爆発のテクスチャ破棄
	//CExplosion::Unload();

	////プレイヤーのテクスチャ破棄
	//CPlayer::Unload();

	//ブロックのテクスチャ破棄
	CBlock::Unload();

	//オブジェクト3dテクスチャ破棄
	CObject3d::Unload();

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//ゲーム更新
//===========================
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//キーボードの取得
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	/*if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_START, 0) == true)
	{
		m_bPause = m_bPause ? false : true;
	}*/

	if (m_bPause == true)
	{//Pキーが押されていない時
	 //ポーズ画面の更新処理

		/*m_pPause->Update();*/
	}

	if (m_bPause == false)
	{
		//カメラの更新
		m_pCamera->Update();

		m_pLight->Update();

		CInputKeyboard *pInputKeyboard;

		//キーボードの取得
		pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

		D3DXVECTOR3 pos = m_pPlayer->GetPosition();

		if (pos.x <= -300.0f)
		{
			CManager::GetInstance()->SetMode(MODE_RESULT);
		}

		bool bDeath = m_pPlayer->GetDeath();

		if (bDeath == true)
		{
			CManager::GetInstance()->SetMode(MODE_GAMEOVER);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_RESULT);

		CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTORIALENTER);
	}
}

//===========================
//ゲーム描画
//===========================
void CGame::Draw(void)
{
	//カメラ情報取得
	CCamera *pCamera = CGame::GetCamera();

	//カメラの設定
	pCamera->SetCamera();
}

//============================
//リザルトコンストラクタ
//============================
CResult::CResult()
{
	m_pTexture = NULL;				//テクスチャのポインタ
	m_pVtxBuff = NULL;				//頂点バッファへのポインタ
}

//============================
//リザルトデストラクタ
//============================
CResult::~CResult()
{

}

//===========================
//生成
//===========================
CResult *CResult::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CResult *pResult;

	//オブジェクト2Dの生成
	pResult = NEW_DBG CResult;

	//初期化処理
	pResult->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pResult;
}

//===========================
//リザルト初期化
//===========================
HRESULT CResult::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\clear.jpg",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファがNULLだったら
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//テクスチャのポインタがNULLだったら
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////角度を決める
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////長さを算出する
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////頂点座標の設定
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(法線)の設定
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
//リザルト終了
//===========================
void CResult::Uninit(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点情報の破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//リザルト更新
//===========================
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//キーボードの取得
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_TITLE);

		CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTORIALENTER);
	}
}

//===========================
//リザルト描画
//===========================
void CResult::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類
}

//============================
//ゲームオーバーコンストラクタ
//============================
CGameOver::CGameOver()
{
	m_pTexture = NULL;				//テクスチャのポインタ
	m_pVtxBuff = NULL;				//頂点バッファへのポインタ
}

//============================
//ゲームオーバーデストラクタ
//============================
CGameOver::~CGameOver()
{

}

//===========================
//ゲームオーバー生成
//===========================
CGameOver *CGameOver::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CGameOver *pGameOver;

	//オブジェクト2Dの生成
	pGameOver = NEW_DBG CGameOver;

	//初期化処理
	pGameOver->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pGameOver;
}

//===========================
//ゲームオーバー初期化
//===========================
HRESULT CGameOver::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gameover.png",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファがNULLだったら
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//テクスチャのポインタがNULLだったら
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////角度を決める
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////長さを算出する
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////頂点座標の設定
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(法線)の設定
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	CSound::PlaySound(CSound::SOUND_LABEL_SE_DEATH);

	return S_OK;
}

//===========================
//ゲームオーバー終了
//===========================
void CGameOver::Uninit(void)
{
	CSound::StopSound();

	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//頂点情報の破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//ゲームオーバー更新
//===========================
void CGameOver::Update(void)
{
	CInputKeyboard *pInputKeyboard;

	CInputGamePad *pInputGamepad;

	//キーボードの取得
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_TITLE);
	}
}

//===========================
//ゲームオーバー描画
//===========================
void CGameOver::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類
}

//============================
//プレイヤー情報取得
//============================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//============================
//プレイヤーミラー情報取得
//============================
CPlayer *CGame::GetPlayerMirror(void)
{
	return m_pPlayerMirror;
}

//============================
//爆発の情報取得
//============================
CExplosion *CGame::GetExplosion(void)
{
	return m_pExplosion;
}

//============================
//敵の情報取得
//============================
CEnemy *CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//============================
//敵の情報取得
//============================
CAbg *CGame::GetAbg(void)
{
	return m_pAbg;
}

//============================
//エフェクトの情報取得
//============================
CEffect *CGame::GetEffect(void)
{
	return m_pEffect;
}

//============================
//スコアの情報取得
//============================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//============================
//タイムの情報取得
//============================
CTime *CGame::GetTime(void)
{
	return m_pTime;
}

//============================
//ブロックの情報取得
//============================
CBlock *CGame::GetBlock(void)
{
	return m_pBlock;
}

//============================
//カメラの情報取得
//============================
CCamera *CGame::GetCamera(void)
{
	return m_pCamera;
}

//============================
//ライトの情報取得
//============================
CLight *CGame::GetLight(void)
{
	return m_pLight;
}



//============================
//オブジェクトXの情報取得
//============================
CObjectx *CGame::GetObjectx(void)
{
	return m_pObjectx[0];
}

//============================
//モデルの情報取得
//============================
CModel *CGame::GetModel(void)
{
	return m_pModel;
}

//============================
//感染情報の情報取得
//============================
CInfection *CGame::GetInfection(void)
{
	return m_pInfection;
}

//============================
//オブジェクト3D情報の情報取得
//============================
CObject3d *CGame::GetObject3d(void)
{
	return m_pObject3d;
}



