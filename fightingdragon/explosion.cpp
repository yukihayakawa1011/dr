//============================
//
//爆発処理(bullet.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include"explosion.h"
//#include "bullet.h"
#include "renderer.h"

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9  CExplosion::m_pTexture;
//============================
//コンストラクタ
//============================
CExplosion::CExplosion()
{
	m_nCounterAnim = 0;			//アニメーションカウンタークリア
	m_nPatternAnim = 0;			//アニメーションパターンクリア

	m_pTexture = 0;								//テクスチャ初期化

	m_nLife = 0;								//体力クリア
}

CExplosion::CExplosion(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//デストラクタ
//============================
CExplosion::~CExplosion()
{

}

//============================
//テクスチャの生成(読み込み)
//============================
HRESULT CExplosion::Load(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\explosion.png",
		&m_pTexture);

	return S_OK;
}

//============================
//テクスチャの破棄
//============================
void CExplosion::Unload(void)
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
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CExplosion *pExplosion;

	//オブジェクト2Dの生成
	pExplosion = NEW_DBG CExplosion(pos);

	//初期化処理
	pExplosion->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	//テクスチャの割り当て
	pExplosion->BindTexture(m_pTexture);

	return pExplosion;
}

//============================
//ポリゴンの初期化
//============================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CBilboard::Init(pos, fRot, nTex,50.0f,50.0f);

	m_nLife = 80;

	//頂点情報の受け取り
	LPDIRECT3DVERTEXBUFFER9 Buff = CBilboard::GetBuff();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	/*頂点バッファをロックし、頂点情報へのポインタを取得*/
	Buff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y + 50.0f, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

	//頂点バッファをアンロックする
	Buff->Unlock();

	return S_OK;
}
//============================
//ポリゴンの終了
//============================
void CExplosion::Uninit(void)
{
	Release();
}
//============================
//ポリゴンの更新
//============================
void CExplosion::Update(void)
{
	m_nLife--;

	DrawAnim();

	if (m_nLife < 0)
	{
		Release();
	}

}
//============================
//ポリゴンの描画
//============================
void CExplosion::Draw(void)
{
	CBilboard::Draw();
}

//アニメーション
void CExplosion::DrawAnim(void)
{
	//頂点情報の受け取り
	LPDIRECT3DVERTEXBUFFER9 Buff = CBilboard::GetBuff();

	VERTEX_2D *pVtx;    //頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	Buff->Lock(0, 0, (void**)&pVtx, 0);

	//位置情報を更新
	/*g_posPlayer.x += g_movePlayer.x;*/

	////頂点座標の設定
	//pVtx[0].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[0].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[0].pos.z = 0.0f;

	//pVtx[1].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[1].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[1].pos.z = 0.0f;

	//pVtx[2].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[2].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[2].pos.z = 0.0f;

	//pVtx[3].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[3].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	//pVtx[3].pos.z = 0.0f;

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(g_posPlayer.x - 100.0f, g_posPlayer.y - 100.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_posPlayer.x + 100.0f, g_posPlayer.y - 100.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_posPlayer.x - 100.0f, g_posPlayer.y + 100.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_posPlayer.x + 100.0f, g_posPlayer.y + 100.0f, 0.0f);

	m_nCounterAnim++;			//カウンターを加算

	if (m_nCounterAnim == 8)
	{
		m_nCounterAnim = 0;	//カウンターを初期値に戻す

							/*g_nPatternAnimPlayer++;	*/	//　パターンNO.を更新する
		m_nPatternAnim = (m_nPatternAnim + 1) % 8;

		//テクスチャ座標の設定

		pVtx[0].tex = D3DXVECTOR2(0.0f + (m_nPatternAnim % 5) * 0.125f, (m_nPatternAnim / 5) * 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f + (m_nPatternAnim % 5) * 0.125f, (m_nPatternAnim / 5) * 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (m_nPatternAnim % 5) * 0.125f, 1.0f + (m_nPatternAnim / 5) * 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f + (m_nPatternAnim % 5) * 0.125f, 1.0f + (m_nPatternAnim / 5) * 0.0f);

		//頂点バッファをアンロックする
		Buff->Unlock();
	}
}

