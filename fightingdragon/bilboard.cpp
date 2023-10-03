//============================
//
//ビルボード処理(bilboard.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include "renderer.h"
#include "bilboard.h"
//#include "bullet.h"
#include "debugproc.h"

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CBilboard::m_pTexture0 = NULL;


//========================
//コンストラクタ
//========================
CBilboard::CBilboard()
{
	//m_mtxWorld = NULL;						//ワールドマトリックス

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pTexture1 = 0;

	m_pVtxBuff = NULL;
}

//========================
//デストラクタ
//========================
CBilboard::~CBilboard()
{

}

//============================
//テクスチャの生成(読み込み)
//============================
HRESULT CBilboard::Load(void)
{
	////デバイスの取得
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//
	//	//テクスチャの読み込み
	//	D3DXCreateTextureFromFile(pDevice,
	//		"data\\TEXTURE\\raginee.png",
	//		&m_pTexture0);
	//
	return S_OK;
}

//============================
//テクスチャの破棄
//============================
void CBilboard::Unload(void)
{
		//テクスチャの破棄
		if (m_pTexture0 != NULL)
		{
			m_pTexture0->Release();
			m_pTexture0 = NULL;
		}
}

//========================
//クリエイト
//========================
CBilboard *CBilboard::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CBilboard *pBilboard;

	//オブジェクト2Dの生成
	pBilboard = NEW_DBG CBilboard;

	//初期化処理
	pBilboard->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 0,fWidth,fHeight);

	/*for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{*/
		pBilboard->BindTexture(m_pTexture0);
	/*}*/

	return pBilboard;
}

//ポリゴンの初期化処理
HRESULT CBilboard::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//種類を設定
	SetType(CObject::TYPE_BILBOARD);

	//各種変数の初期化
	m_pos = pos; //位置を初期化

	m_rot.x = fRot; //向きを初期化
	m_rot.y = fRot; //向きを初期化
	m_rot.z = fRot; //向きを初期化

					//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx; //頂点座標へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-fWidth, + fHeight, 20.0f);
	pVtx[1].pos = D3DXVECTOR3(+fWidth, + fHeight, 20.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, - fHeight, 20.0f);
	pVtx[3].pos = D3DXVECTOR3(+fWidth, - fHeight, 20.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	pVtx[1].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	pVtx[2].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	pVtx[3].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//ポリゴンの終了処理
void CBilboard::Uninit(void)
{
	//テクスチャの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//テクスチャの破棄
	if (m_pTexture1 != NULL)
	{
		m_pTexture1->Release();
		m_pTexture1 = NULL;
	}

	Release();
}

//ポリゴンの更新処理
void CBilboard::Update(void)
{
	//デバッグ表示の情報を渡す
	CDebugProc *pDebug = CManager::GetDebugProck();

	//int nCnt = CBullet::GetNumAllBullet();

#ifdef _DEBUG
	//弾の総数をデバッグ表示
	//pDebug->Print("弾の総数 : %d\n", nCnt);
#endif
}

//ポリゴンの描画処理
void CBilboard::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxTrans; 

	//ビューマトリックス取得用
	D3DXMATRIX mtxView;

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView); //逆行列を求める

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	
		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		pDevice->SetTexture(0, m_pTexture1);

		//ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//αテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//============================
//位置をセットする
//============================
void CBilboard::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================
//移動量をセットする
//============================
void CBilboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//===========================
//頂点情報をセット
//===========================
void CBilboard::SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
{
	m_pVtxBuff = Buff;
}

//============================
//傾きをセットする
//============================
void CBilboard::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================
//色をセットする
//============================
void CBilboard::SetCol(D3DXCOLOR col)
{
	m_col = col;

	//VERTEX_2D *pVtx;    //頂点情報へのポインタ

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	//pVtx[1].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	//pVtx[2].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
	//pVtx[3].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);

	////頂点バッファをアンロックする
	//m_pVtxBuff->Unlock();
}

//============================
//位置の取得
//============================
D3DXVECTOR3 CBilboard::GetPosition(void)
{
	return m_pos;
}

//============================
//移動量の取得
//============================
D3DXVECTOR3 CBilboard::GetMove(void)
{
	return m_move;
}

//============================
//頂点情報の取得
//============================
LPDIRECT3DVERTEXBUFFER9 CBilboard::GetBuff(void)
{
	return m_pVtxBuff;
}

//============================
//傾きの取得
//============================
D3DXVECTOR3 CBilboard::GetRot(void)
{
	return m_rot;
}

//============================
//色の取得
//============================
D3DXCOLOR CBilboard::GetCol(void)
{
	return m_col;
}

//===================================
//テクスチャの割り当て
//===================================
void CBilboard::BindTexture(LPDIRECT3DTEXTURE9 pTextur)
{
		m_pTexture1 = pTextur;
}
