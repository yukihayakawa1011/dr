//============================
//
//オブジェクト2D処理(object2D.cpp)
//Author:早川 友貴
//
//============================
#include "object2D.h"
#include "manager.h"
#include "anim.h"
#include "bg.h"
#include "renderer.h"

//静的メンバ変数宣言
CObject2D *CObject2D::m_apObject[320];

//============================
//コンストラクタ
//============================
CObject2D::CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置をクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//移動量をクリア
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//傾きをクリア
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);				//色をクリア
	m_nLife = 0;
}

//============================
//デストラクタ
//============================
CObject2D::~CObject2D()
{

}

//============================
//生成処理
//============================
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CObject2D *pObject2D;

	//オブジェクト2Dの生成
	pObject2D = NEW_DBG CObject2D;

	//初期化処理
	pObject2D->Init(D3DXVECTOR3(pos.x,pos.y,pos.z),fRot,nTex,fWidth,fHeight);

	return pObject2D;
}

//============================
//ポリゴンの初期化
//============================
HRESULT CObject2D::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

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
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	//rhw(法線)の設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//============================
//ポリゴンの終了
//============================
void CObject2D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}
//============================
//ポリゴンの更新
//============================
void CObject2D::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - m_pos.x, pos.y - m_pos.y, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + m_pos.x, pos.y - m_pos.y, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - m_pos.x, pos.y + m_pos.y, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + m_pos.x, pos.y + m_pos.y, m_pos.z);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	SetPosition(pos);
}
//============================
//ポリゴンの描画
//============================
void CObject2D::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();

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
//位置をセットする
//============================
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================
//移動量をセットする
//============================
void CObject2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================
//傾きをセットする
//============================
void CObject2D::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================
//色をセットする
//============================
void CObject2D::SetCol(D3DXCOLOR col)
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
//頂点情報をセットする
//============================
void CObject2D::SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
{
	m_pVtxBuff = Buff;
}

//============================
//体力をセットする
//============================
void CObject2D::SetLife(int nLife)
{
	m_nLife = nLife;
}

//============================
//位置の取得
//============================
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}

//============================
//移動量の取得
//============================
D3DXVECTOR3 CObject2D::GetMove(void)
{
	return m_move;
}

//============================
//傾きの取得
//============================
D3DXVECTOR3 CObject2D::GetRot(void)
{
	return m_rot;
}

//============================
//色の取得
//============================
D3DXCOLOR CObject2D::GetCol(void)
{
	return m_col;
}

//============================
//頂点の取得
//============================
LPDIRECT3DVERTEXBUFFER9 CObject2D::GetBuff(void)
{
	return m_pVtxBuff;
}

//============================
//体力取得
//============================
int CObject2D::GetLife(void)
{
	return m_nLife;
}

//===================================
//テクスチャの割り当て
//===================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTextur)
{
	m_pTexture = pTextur;
}