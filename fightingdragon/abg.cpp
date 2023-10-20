////============================
////
////オブジェクト2D多重背景(abg.cpp)
////Author:早川 友貴
////
////============================
//#include "abg.h"
//#include "manager.h"
//#include "renderer.h"
//
////静的メンバ変数宣言
//LPDIRECT3DTEXTURE9  CAbg::m_pTexture[MAX_TEX] = {};  //テクスチャのポインタをクリア
////============================
////コンストラクタ
////============================
//CAbg::CAbg()
//{
//	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	{
//		m_apObject[nCnt].pObject2d = NULL;
//		m_apObject[nCnt].m_fMove = D3DXVECTOR2(0.0f, 0.0f);
//		m_apObject[nCnt].m_fTex = D3DXVECTOR2(0.0f,0.0f);
//	}
//}
//
////============================
////デストラクタ
////============================
//CAbg::~CAbg()
//{
//
//}
//
////============================
////テクスチャの生成(読み込み)
////============================
//HRESULT CAbg::Load(void)
//{
//	//デバイスの取得
//	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	//テクスチャの読み込み
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\TEXTURE\\bg.jpg",
//		&m_pTexture[0]);
//	
//	//テクスチャの読み込み
//	//D3DXCreateTextureFromFile(pDevice,
//	//	"data\\TEXTURE\\bg2.png",
//	//	&m_pTexture[1]);
//	//
//	////テクスチャの読み込み
//	//D3DXCreateTextureFromFile(pDevice,
//	//	"data\\TEXTURE\\bg102.png",
//	//	&m_pTexture[2]);
//	//
//		
//	return S_OK;
//}
//
////============================
////テクスチャの破棄
////============================
//void CAbg::Unload(void)
//{
//	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	{
//		//テクスチャの破棄
//		if (m_pTexture[nCnt] != NULL)
//		{
//			m_pTexture[nCnt]->Release();
//			m_pTexture[nCnt] = NULL;
//		}
//	}
//}
//
////============================
////生成処理
////============================
//CAbg *CAbg::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
//{
//	CAbg *pAbg = NULL;
//
//	if (pAbg == NULL)
//	{
//		//オブジェクト2Dの生成
//		pAbg = NEW_DBG CAbg;
//
//		for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//		{
//			//初期化処理
//			pAbg->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nCnt,fWidth,fHeight);
//
//		/*	pAbg->m_apObject[0].m_fMove = D3DXVECTOR2(0.001f, 0.0f);
//			pAbg->m_apObject[1].m_fMove = D3DXVECTOR2(0.0005f, 0.0f);
//			pAbg->m_apObject[2].m_fMove = D3DXVECTOR2(0.0001f, 0.0f);*/
//		}
//	}
//
//	return pAbg;
//}
//
////============================
////ポリゴンの初期化
////============================
//HRESULT CAbg::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
//{
//	if (m_apObject[nTex].pObject2d == NULL)
//	{
//
//		m_apObject[nTex].pObject2d = CObject2D::Create(pos, fRot, nTex, fWidth, fHeight);
//
//		m_apObject[nTex].pObject2d->Init(pos, fRot, nTex,fWidth,fHeight);
//
//		//テクスチャ割当て
//		m_apObject[nTex].pObject2d->BindTexture(m_pTexture[nTex]);
//
//			VERTEX_2D *pVtx;    //頂点情報へのポインタ
//
//			/*頂点バッファをロックし、頂点情報へのポインタを取得*/
//			m_apObject[nTex].pObject2d->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
//
//			//頂点座標の設定
//			pVtx[0].pos = D3DXVECTOR3(pos.x - SCREEN_WIDTH, pos.y - SCREEN_HEIGHT, pos.z);
//			pVtx[1].pos = D3DXVECTOR3(pos.x + SCREEN_WIDTH, pos.y - SCREEN_HEIGHT, pos.z);
//			pVtx[2].pos = D3DXVECTOR3(pos.x - SCREEN_WIDTH, pos.y + SCREEN_HEIGHT, pos.z);
//			pVtx[3].pos = D3DXVECTOR3(pos.x + SCREEN_WIDTH, pos.y + SCREEN_HEIGHT, pos.z);
//
//			//rhw(法線)の設定
//			pVtx[0].rhw = 1.0f;
//			pVtx[1].rhw = 1.0f;
//			pVtx[2].rhw = 1.0f;
//			pVtx[3].rhw = 1.0f;
//
//			//頂点カラーの設定
//			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//			//テクスチャ座標の設定
//			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//			m_apObject[nTex].pObject2d->SetPosition(pos);
//
//			//頂点バッファをアンロックする
//			m_apObject[nTex].pObject2d->GetBuff()->Unlock();
//		}
//
//	return S_OK;
//}
////============================
////ポリゴンの終了
////============================
//void CAbg::Uninit(void)
//{
//	//for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	//{
//	//	//終了処理
//	//	m_apObject[nCnt].pObject2d->Uninit();
//	//}
//
//	//終了処理
//	CObject::Release();
//}
////============================
////ポリゴンの更新
////============================
//void CAbg::Update(void)
//{
//	//for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	//{
//	//	m_apObject[nCnt].m_fTex.x -= m_apObject[nCnt].m_fMove.x;
//	//	m_apObject[nCnt].m_fTex.y -= m_apObject[nCnt].m_fMove.y;
//
//	//	VERTEX_2D *pVtx;    //頂点情報へのポインタ
//
//	//	//頂点バッファをロックし、頂点情報へのポインタを取得
//	//	m_apObject[nCnt].pObject2d->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
//
//	//	//テクスチャ座標の更新
//	//	pVtx[0].tex = D3DXVECTOR2(m_apObject[nCnt].m_fTex.x, m_apObject[nCnt].m_fTex.y);
//	//	pVtx[1].tex = D3DXVECTOR2(m_apObject[nCnt].m_fTex.x + 1.0f, m_apObject[nCnt].m_fTex.y);
//	//	pVtx[2].tex = D3DXVECTOR2(m_apObject[nCnt].m_fTex.x, m_apObject[nCnt].m_fTex.y + 1.0f);
//	//	pVtx[3].tex = D3DXVECTOR2(m_apObject[nCnt].m_fTex.x + 1.0f, m_apObject[nCnt].m_fTex.y + 1.0f);
//	//	
//	//	//頂点バッファをアンロックする
//	//	m_apObject[nCnt].pObject2d->GetBuff()->Unlock();
//	//}
//}
////============================
////ポリゴンの描画
////============================
//void CAbg::Draw(void)
//{
//	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	{
//		m_apObject[nCnt].pObject2d->Draw();
//	}
//}
//
////============================
////位置をセットする
////============================
//void CAbg::SetPosition(D3DXVECTOR3 pos)
//{
//	
//}
//
////============================
////位置をセットする
////============================
//void CAbg::SetRot(D3DXVECTOR3 rot)
//{
//	
//}
//
////============================
//D3DXVECTOR3 CAbg::GetPosition(void)
//{
//	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//}
//
////============================
//D3DXVECTOR3 CAbg::GetMove(void)
//{
//	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//}
//
////============================
//D3DXVECTOR3 CAbg::GetRot(void)
//{
//	return D3DXVECTOR3(0.0f,0.0f,0.0f);
//}