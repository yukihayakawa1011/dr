//============================
//
//エフェクト処理(effect.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include"explosion.h"
#include "effect.h"
#include "renderer.h"

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9  CEffect::m_pTexture = NULL;
//============================
//コンストラクタ
//============================
CEffect::CEffect()
{
	m_nLife = 0;								//体力クリア

	m_fRadius = 0;								//半径をクリア
}

//オーバーロードコンストラクタ
CEffect::CEffect(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//デストラクタ
//============================
CEffect::~CEffect()
{

}

////============================
////テクスチャの生成(読み込み)
////============================
//HRESULT CEffect::Load(int nTex)
//{
//	//デバイスの取得
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//	
//	
//
//	return S_OK;
//}

//============================
//テクスチャの破棄
//============================
void CEffect::Unload(void)
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
CEffect *CEffect::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	CEffect *pEffect;

	//オブジェクト2Dの生成
	pEffect = NEW_DBG CEffect(pos);

	//初期化処理
	pEffect->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex,fWidth,fHeight,move,col,nLife);

	//テクスチャの割り当て
	pEffect->BindTexture(m_pTexture);

	return pEffect;
}

//============================
//ポリゴンの初期化
//============================
HRESULT CEffect::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (nTex == 0)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\effect000.jpg",
			&m_pTexture);
	}

	if (nTex == 1)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\brake_Window.png",
			&m_pTexture);
	}

	SetCol(col);

	CBilboard::Init(pos, fRot, nTex, fWidth,fHeight);

	//種類を設定
	SetType(CObject::TYPE_EFFECT);

	m_nLife = nLife;

	m_fRadius = 6.0f;

	//VERTEX_2D *pVtx;    //頂点情報へのポインタ

	///*頂点バッファをロックし、頂点情報へのポインタを取得*/
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y - m_fRadius, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y - m_fRadius, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y + m_fRadius, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y + m_fRadius, 0.0f);

	////rhw(法線)の設定
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	////テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////頂点バッファをアンロックする
	//m_pVtxBuff->Unlock();

	m_move = move;

	SetCol(col);

	return S_OK;
}
//============================
//ポリゴンの終了
//============================
void CEffect::Uninit(void)
{
	CBilboard::Release();
}
//============================
//ポリゴンの更新
//============================
void CEffect::Update(void)
{
	//VERTEX_2D *pVtx;    //頂点情報へのポインタ

	D3DXCOLOR col = GetCol();

	D3DXVECTOR3 pos = GetPosition();

	///*頂点バッファをロックし、頂点情報へのポインタを取得*/
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y - m_fRadius, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y - m_fRadius, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - m_fRadius, pos.y + m_fRadius, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + m_fRadius, pos.y + m_fRadius, 0.0f);

	////rhw(法線)の設定
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	////頂点カラーの設定
 // 	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a);
	//pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	////頂点バッファをアンロックする
	//m_pVtxBuff->Unlock();

	pos += m_move;

	SetPosition(pos);

	//エフェクトの体力を減らす
	m_nLife--;

	//エフェクトのα値を減らす
	col.a -= 0.1f;

	//半径を小さくしていく
	m_fRadius -= 2.0f;

	SetCol(col);

	//体力がなくなったら消す
	if (m_nLife < 0 || m_fRadius < 0)
	{
		Release();
	}

}
//============================
//ポリゴンの描画
//============================
void CEffect::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//オブジェクトの描画
	CBilboard::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

