//============================
//
//エフェクト処理(effect.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include"explosion.h"
#include "effect.h"
#include "particle.h"
#include "renderer.h"

//静的メンバ変数宣言
CEffect *CParticle::pEffect = NULL;

//============================
//コンストラクタ
//============================
CParticle::CParticle()
{

	m_nLife = 0;								//体力クリア
}

//オーバーロードコンストラクタ
CParticle::CParticle(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//デストラクタ
//============================
CParticle::~CParticle()
{

}


//============================
//生成処理
//============================
void *CParticle::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	switch (nTex)
	{
	case TYPE_DAMAGE:

		//パーティクル(赤色)
		ParticleRed(pos, D3DXVECTOR3(0.0f,300.0f,0.0f), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), 10.0f,200);

		////パーティクル(黄色)
		//ParticleYellow();

		break;

	case TYPE_WINDOW:

		//パーティクル(ガラス)
		ParticleWindow(pos, D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 200);

		break;
	}

	return S_OK;
}

//============================
//ポリゴンの初期化
//============================
HRESULT CParticle::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CBilboard::Init(pos, fRot, nTex, fWidth,fHeight);

	//種類を設定
	SetType(CObject::TYPE_PARTICLE);

	////頂点情報の受け取り
	//LPDIRECT3DVERTEXBUFFER9 Buff = CBilboard::GetBuff();

	//VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//					/*頂点バッファをロックし、頂点情報へのポインタを取得*/
	//Buff->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y - 50.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y - 50.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - 50.0f, pos.y + 50.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + 50.0f, pos.y + 50.0f, 0.0f);

	////rhw(法線)の設定
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////頂点カラーの設定
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	////テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////頂点バッファをアンロックする
	//Buff->Unlock();

	return S_OK;
}
//============================
//ポリゴンの終了
//============================
void CParticle::Uninit(void)
{
	CBilboard::Release();
}
//============================
//ポリゴンの更新
//============================
void CParticle::Update(void)
{

}

//============================
//ポリゴンの描画
//============================
void CParticle::Draw(void)
{
	/*CObject2D::Draw();*/
}

//=============================
//パーティクル(赤色)
//=============================
void CParticle::ParticleRed(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float m_fRadius, int nLife)
{
	int nCntParticle = 0, nCntParticle1 = 0;

	//パーティクルの生成
	for (nCntParticle1 = 0; nCntParticle1 < USE_PARTICLE; nCntParticle1++)
	{
		//移動量の設定
		move.x = sinf(((float)(rand() % 629 - 400.0f)) / 200) * ((float)(rand() % 300) / 50.0f + 1.0f);
		move.y = cosf(((float)(rand() % 629 - 200)) / 200) * ((float)(rand() % 400) / 50.0f + 1.0f);

		//頂点カラーの設定
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//半径の設定
		m_fRadius = USE_RADIUS;

		pEffect->Create(pos, 0.0f, 0,10.0f,10.0f,move * 10,col,nLife);
	}
}

//=============================
//パーティクル(ガラス)
//=============================
void CParticle::ParticleWindow(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float m_fRadius, int nLife)
{
	int nCntParticle = 0, nCntParticle1 = 0;

	//パーティクルの生成
	for (nCntParticle1 = 0; nCntParticle1 < 4; nCntParticle1++)
	{
		//移動量の設定
		move.x = sinf(((float)(rand() % 629 - 250.0f)) / 200) * ((float)(rand() % 400) / 50.0f + 1.0f);
		move.y = cosf(((float)(rand() % 629 - 100.0f)) / 200) * ((float)(rand() % 400) / 50.0f + 1.0f);

		//頂点カラーの設定
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//半径の設定
		m_fRadius = m_fRadius;

		pEffect->Create(D3DXVECTOR3(pos.x - 10.0f,pos.y + 40.0f,pos.z), 0.0f, 1, 30.0f, 30.0f, move * 2, col, nLife);
	}
}
