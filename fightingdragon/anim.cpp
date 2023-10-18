//============================
//
//オブジェクト2D処理(object2D.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include "anim.h"
#include "renderer.h"

//============================
//コンストラクタ
//============================
CAnim::CAnim()
{
	m_nCounterAnim = 0;			//アニメーションカウンタークリア
	m_nPatternAnim = 0;			//アニメーションパターンクリア

	m_pos = 0.0f;
	m_move = 0.0f;
}

//============================
//デストラクタ
//============================
CAnim::~CAnim()
{

}

//============================
//生成処理
//============================
CAnim *CAnim::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CAnim *pAnim;

	//オブジェクト2Dの生成
	pAnim = NEW_DBG CAnim;

	//初期化処理
	pAnim->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pAnim;
}

//============================
//ポリゴンの初期化
//============================
HRESULT CAnim::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (nTex == 0)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\runningman100.png",
			&m_pTexture);
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
	pVtx[0].pos = D3DXVECTOR3(pos.x - 100.0f, pos.y - 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 100.0f, pos.y - 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 100.0f, pos.y + 100.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 100.0f, pos.y + 100.0f, 0.0f);
	

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
	pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//============================
//ポリゴンの終了
//============================
void CAnim::Uninit(void)
{
	Release();
}
//============================
//ポリゴンの更新
//============================
void CAnim::Update(void)
{
	VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	CAnim::DrawAnim();

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//============================
//ポリゴンの描画
//============================
void CAnim::Draw(void)
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

//アニメーション
void CAnim::DrawAnim(void)
{
		VERTEX_2D *pVtx;    //頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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

		if (m_nCounterAnim == 5)
		{
			m_nCounterAnim = 0;	//カウンターを初期値に戻す

								/*g_nPatternAnimPlayer++;	*/	//　パターンNO.を更新する
			m_nPatternAnim = (m_nPatternAnim + 1) % 10;

			//テクスチャ座標の設定

			pVtx[0].tex = D3DXVECTOR2(0.0f + (m_nPatternAnim % 5) * 0.2f, (m_nPatternAnim / 5) * 0.5f);
			pVtx[1].tex = D3DXVECTOR2(0.2f + (m_nPatternAnim % 5) * 0.2f, (m_nPatternAnim / 5) * 0.5f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (m_nPatternAnim % 5) * 0.2f, 0.5f + (m_nPatternAnim / 5) * 0.5f);
			pVtx[3].tex = D3DXVECTOR2(0.2f + (m_nPatternAnim % 5) * 0.2f, 0.5f + (m_nPatternAnim / 5) * 0.5f);

			//頂点バッファをアンロックする
			m_pVtxBuff->Unlock();
		}
}

