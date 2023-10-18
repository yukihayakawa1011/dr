//============================
//
//ポリゴン処理(porygon.cpp)
//Author:早川 友貴
//
//============================
#include "object3d.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "sound.h"

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CObject3d::m_pTexture = NULL;
LPDIRECT3DVERTEXBUFFER9 CObject3d::m_pVtxBuff = NULL;
CObject3d *CObject3d::m_pObject[320] = {};

//========================
//コンストラクタ
//========================
CObject3d::CObject3d()
{
	 //m_mtxWorld = NULL;						//ワールドマトリックス

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_objectcol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_TimeBlinking = 0;

	//m_bShowEnemy = true;
}

//========================
//デストラクタ
//========================
CObject3d::~CObject3d()
{

}

//============================
//テクスチャの生成(読み込み)
//============================
HRESULT CObject3d::Load(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	return S_OK;
}

//============================
//テクスチャの破棄
//============================
void CObject3d::Unload(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//========================
//クリエイト
//========================
CObject3d *CObject3d::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CObject3d *pObject3D;

	//オブジェクト2Dの生成
	pObject3D = NEW_DBG CObject3d;

	//初期化処理
	pObject3D->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f,0, fWidth, fHeight);

	return pObject3D;
}

 //ポリゴンの初期化処理
HRESULT CObject3d::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (nTex == 0)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\black.jpg",
			&m_pTexture);
	}

	//各種変数の初期化
	m_pos = pos; //位置を初期化
	
	m_rot.x = fRot; //向きを初期化
	m_rot.y = fRot; //向きを初期化
	m_rot.z = fRot; //向きを初期化

	/*m_bShowEnemy = true;*/

	m_objectcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_TimeBlinking = 600;

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
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, + pos.z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, + pos.z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, - pos.z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, - pos.z);

	D3DXVECTOR3 vec0 = D3DXVECTOR3(0, 0.0, 0.0f) - D3DXVECTOR3(0.0f, 0.0f,0.0f);
	D3DXVECTOR3 vec1 = D3DXVECTOR3(200, 0.0, + 100.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec2 = D3DXVECTOR3(- 200, 0.0,+ 100.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 nor;
	//float fheight;		//求める高さ

	//ふたつのベクトルから法線を求める
	D3DXVec3Cross(&nor,
		&vec1,
		&vec2);

	//法線を正規化する
	D3DXVec3Normalize(&nor, &nor);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	pVtx[1].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	pVtx[2].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);
	pVtx[3].nor = D3DXVECTOR3(nor.x, nor.y, nor.z);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
	pVtx[1].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
	pVtx[2].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
	pVtx[3].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//色をセットする
	SetColor(m_objectcol);

	//SetShowEnemy(m_bShowEnemy);

	return S_OK;
}

//ポリゴンの終了処理
void CObject3d::Uninit(void)
{
	Release();
}

//ポリゴンの更新処理
void CObject3d::Update(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_3D *pVtx; //頂点座標へのポインタ

	//頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//色を明け渡す
	m_objectcol = GetColor();

	/*if (m_objectcol.a < 1.0f || m_objectcol.a > 0.0f)
	{*/
		
			m_TimeBlinking--;

			/*m_bShowEnemy = false;

			SetShowEnemy(m_bShowEnemy);*/

			//一定時間で発光する
			if (m_TimeBlinking == 50)
			{
				//発光させる
				m_objectcol.a = 1.1f;

				CSound::PlaySound(CSound::SOUND_LABEL_SE_THUNDER);
			}

			if (m_TimeBlinking < 0)
			{//時間がたったらリセット
				m_TimeBlinking = 600;
			}
			else if (m_TimeBlinking <= 50)
			{//光ってからリセットまでの間

				//徐々に薄くする
				m_objectcol.a -= 0.02f;

			/*	m_bShowEnemy = true;

				SetShowEnemy(m_bShowEnemy);*/
			}
			else
			{//それ以外は見えなくする
				m_objectcol.a = 0.0f;
			}
		
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
		pVtx[1].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
		pVtx[2].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);
		pVtx[3].col = D3DXCOLOR(m_objectcol.r, m_objectcol.g, m_objectcol.b, m_objectcol.a);

		SetColor(m_objectcol);
	/*}*/
}

//ポリゴンの描画処理
void CObject3d::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

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

	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //プリミティブの種類
}

//============================
//位置をセットする
//============================
void CObject3d::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//============================
//位置の取得
//============================
D3DXVECTOR3 CObject3d::GetPosition(void)
{
	return m_pos;
}

//============================
//移動量の取得
//============================
D3DXVECTOR3 CObject3d::GetMove(void)
{
	return m_move;
}

//===================================
//プレイヤーの高さを知るための処理
//===================================
float CObject3d::GetHeight(D3DXVECTOR3 pos)
{

	D3DXVECTOR3 vec0 = D3DXVECTOR3(0, 0.0, 0.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec1 = D3DXVECTOR3(200, 0.0, +100.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vec2 = D3DXVECTOR3(-200, 0.0, +100.0f) - D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 nor;
	float fheight = 0.0f;		//求める高さ

	//内積の処理
	fheight = (pos.x - vec0.x *  nor.x) + (fheight - vec0.y  * nor.y) + (pos.z - vec0.z  * nor.z);

	if (fheight != 0.0f)
	{
		fheight = pos.y;
	}
	return fheight;
}

//===================================
//色を渡す処理
//===================================
D3DXCOLOR CObject3d::GetColor(void)
{
	return m_objectcol;
}

//===================================
//色をセットする処理
//===================================
void CObject3d::SetColor(D3DXCOLOR col)
{
	m_objectcol = col;
}

////===================================
////敵の姿を映すかを渡す処理
////===================================
//bool CObject3d::GetShowEnemy(void)
//{
//	return m_bShowEnemy;
//}
//
////===================================
////色をセットする処理
////===================================
//void CObject3d::SetShowEnemy(bool ShowEnemy)
//{
//	m_bShowEnemy = ShowEnemy;
//}
//
//
//
//
