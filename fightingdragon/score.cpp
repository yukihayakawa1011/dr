//============================
//
//スコア処理(score.cpp)
//Author:早川 友貴
//
//============================
#include "score.h"  
//#include "bullet.h"
#include "enemy.h"
#include "manager.h"
#include "object2D.h"
#include "renderer.h"
#include "debugproc.h"
//#include "sound.h"

LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;  //テクスチャのポインタ

//=============================
//コンストラクタ
//=============================
CScore::CScore()
{
	m_nScore = 0;								//スコアの値
	m_nWindth = 0.0f;							//幅の値
	m_nHeight = 0.0f;							//高さの値
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_pNumber[nCnt] = NULL;
	}
}

//=============================
//デストラクタ
//=============================
CScore::~CScore()
{

}

//============================
//テクスチャの生成(読み込み)
//============================
HRESULT CScore::Load(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&m_pTexture);

	return S_OK;
}

//============================
//テクスチャの破棄
//============================
void CScore::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	
}

//============================
//生成処理
//============================
CScore *CScore::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CScore *pScore;

	nTex = 0;

	//オブジェクト2Dの生成
	pScore = NEW_DBG CScore;

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//初期化処理
		pScore->Init(D3DXVECTOR3(100.0f * nCnt, pos.y, pos.z), fRot, nCnt);
	}

	return pScore;
}

//=============================
//  スコアの初期化
//=============================
HRESULT CScore::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	if (m_pNumber[nTex] == NULL)
	{
		m_pNumber[nTex] = NEW_DBG CNumber;

		m_pNumber[nTex]->Init(pos, fRot, nTex);

		//種類を設定
		SetType(CObject::TYPE_SCORE);

		//テクスチャ割当て
		m_pNumber[nTex]->BindTexture(m_pTexture);

		m_nScore = 0;

		//VERTEX_2D *pVtx;    //頂点情報へのポインタ

		///*頂点バッファをロックし、頂点情報へのポインタを取得*/
		//m_pNumber[nTex]->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		////頂点座標の設定
		//pVtx[0].pos = D3DXVECTOR3(pos.x - 60.0f, pos.y - 60.0f, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(pos.x + 60.0f, pos.y - 60.0f, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(pos.x - 60.0f, pos.y + 60.0f, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(pos.x + 60.0f, pos.y + 60.0f, 0.0f);

		////rhw(法線)の設定
		//pVtx[0].rhw = 1.0f;
		//pVtx[1].rhw = 1.0f;
		//pVtx[2].rhw = 1.0f;
		//pVtx[3].rhw = 1.0f;

		////頂点カラーの設定
		//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		////テクスチャ座標の設定
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//m_pNumber[nTex]->SetPosition(pos);

		////頂点バッファをアンロックする
		//m_pNumber[nTex]->GetBuff()->Unlock();
	}

	return S_OK;
}

//=====================
//スコアの終了処理
//=====================
void CScore::Uninit(void)
{
	CNumber::Release();
}

//スコアの更新処理
void  CScore::Update(void)
{
	//デバッグ表示の情報を渡す
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProck();

	SetPos(D3DXVECTOR3(1000.0f, 50.0f, 0.0f), 50.0f, 50.0f);

	int aTexU[NUM_PLACE];

	//スコアの上限
	if (m_nScore >= 9999)
	{
		m_nScore = 9999;
	}

	aTexU[0] = m_nScore % 10000 / 1000;
	aTexU[1] = m_nScore % 1000 / 100;
	aTexU[2] = m_nScore % 100 / 10;
	aTexU[3] = m_nScore % 10 / 1;

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	for (int nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pNumber[nCntScore]->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);

		//頂点バッファをアンロックする
		m_pNumber[nCntScore]->GetBuff()->Unlock();
	}

#ifdef _DEBUG
	pDebug->Print("スコアの数値 : %d\n", m_nScore);
#endif
}

//スコアの描画処理
void  CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_pNumber[nCnt]->Draw();
	}
}

//===============================
//スコアの加算
//===============================
void CScore::Add(int nScore)
{
	int aTexU[NUM_PLACE];  //各桁の数字を格納
	//int nCntScore;

 	m_nScore += nScore;

	//スコアの上限
	if (m_nScore >= 9999)
	{
		m_nScore = 9999;
	}

	aTexU[0] = m_nScore % 10000 / 1000;
	aTexU[1] = m_nScore % 1000 / 100;
	aTexU[2] = m_nScore % 100 / 10;
	aTexU[3] = m_nScore % 10 / 1;

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	for (int nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pNumber[nCntScore]->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);

		//頂点バッファをアンロックする
		m_pNumber[nCntScore]->GetBuff()->Unlock();
	}
}

//================================
//スコアを受け取る
//===============================
int  CScore::Get(void)
{
	return m_nScore;
}

//==================================
//スコアの設定
//==================================
void  CScore::SetPos(D3DXVECTOR3 pos, float nWINDTH, float nHeight)
{
	SetPosition(pos);
	
	m_nWindth = nWINDTH;
	
	m_nHeight = nHeight;

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	for (int nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pNumber[nCntScore]->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(pos.x - 50.0f + (nCntScore * POS_SCORE), pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + 50.0f + (nCntScore * POS_SCORE), pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - 50.0f + (nCntScore * POS_SCORE), pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + 50.0f + (nCntScore * POS_SCORE), pos.y + 50.0f, 0.0f);

		//頂点バッファをアンロックする
		m_pNumber[nCntScore]->GetBuff()->Unlock();
	}
}

