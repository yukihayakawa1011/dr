//============================
//
//オブジェクトX処理(objectx.cpp)
//Author:早川 友貴
//
//============================
#include "main.h"
#include "objectx.h"
#include "input.h"
#include "renderer.h"
#include "objectx.h"

//静的メンバ変数宣言
CObjectx::SET_OBJECTX CObjectx::Objectx[MAX_OBJECTX] = {};

//============================
//コンストラクタ
//============================
CObjectx::CObjectx()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置をクリア
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//移動量をクリア
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//傾きをクリア

	//m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);				//色をクリア
	m_nLife = 0;

	m_nTexCnt = 0;		//テクスチャ情報の番号をクリア

}

//============================
//デストラクタ
//============================
CObjectx::~CObjectx()
{

}

//============================
//生成処理
//============================
CObjectx *CObjectx::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CObjectx *pObjectx;

	//オブジェクト2Dの生成
	pObjectx = NEW_DBG CObjectx;

	//初期化処理
	pObjectx->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex, fWidth, fHeight);

	return pObjectx;
}

//====================
//モデルの初期化
//====================
HRESULT CObjectx::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	int nNumVtx;  //頂点数

	DWORD dwSizeFVF;  //頂点フォーマットのサイズ

	BYTE *pVtxBUff;  //頂点バッファのポインタ

	if (nTex == 0)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\wall.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[0].m_pBuffMat,
			NULL,
			&Objectx[0].m_dwNumMat,
			&Objectx[0].m_pMesh);
	}

	if (nTex == 1)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\floor.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[1].m_pBuffMat,
			NULL,
			&Objectx[1].m_dwNumMat,
			&Objectx[1].m_pMesh);
	}

	if (nTex == 2)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\long_Floor.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[2].m_pBuffMat,
			NULL,	 
			&Objectx[2].m_dwNumMat,
			&Objectx[2].m_pMesh);
	}

	if (nTex == 3)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\escape_door.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[3].m_pBuffMat,
			NULL,
			&Objectx[3].m_dwNumMat,
			&Objectx[3].m_pMesh);
	}

	if (nTex == 4)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX("data\\MODEL\\window.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&Objectx[4].m_pBuffMat,
			NULL,
			&Objectx[4].m_dwNumMat,
			&Objectx[4].m_pMesh);
	}

	D3DXMATERIAL *pMat; //マテリアルへのポインタ

	if (Objectx[nTex].m_pBuffMat != NULL)
	{
		//マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)Objectx[nTex].m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)Objectx[nTex].m_dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{//テクスチャファイルネームが存在する
			 //テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&Objectx[nTex].m_apTexture[nCntMat]);
			}
		}
	}

	SetPosition(pos);

	if (Objectx[nTex].m_pMesh != NULL)
	{

		//頂点数の取得
		nNumVtx = Objectx[nTex].m_pMesh->GetNumVertices();

		//頂点フォーマットのサイズを取得
		dwSizeFVF = D3DXGetFVFVertexSize(Objectx[nTex].m_pMesh->GetFVF());

		//頂点バッファをロック
		Objectx[nTex].m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

			if (vtx.x > Objectx[nTex].m_VtxMax.x)
			{
				Objectx[nTex].m_VtxMax.x = vtx.x;
			}

			if (vtx.x < Objectx[nTex].m_VtxMin.x)
			{
				Objectx[nTex].m_VtxMin.x = vtx.x;
			}

			if (vtx.y > Objectx[nTex].m_VtxMax.y)
			{
				Objectx[nTex].m_VtxMax.y = vtx.y;
			}

			if (vtx.y < Objectx[nTex].m_VtxMin.y)
			{
				Objectx[nTex].m_VtxMin.y = vtx.y;
			}

			if (vtx.z > Objectx[nTex].m_VtxMax.z)
			{
				Objectx[nTex].m_VtxMax.z = vtx.z;
			}

			if (vtx.z < Objectx[nTex].m_VtxMin.z)
			{
				Objectx[nTex].m_VtxMin.z = vtx.z;
			}

			pVtxBUff += dwSizeFVF;	//頂点フォーマットのサイズ分ぼいんを進める
		}

		//頂点バッファをアンロック
		Objectx[nTex].m_pMesh->UnlockVertexBuffer();
	}

	//モデルの幅・高さをセット
	SetVtxMax(Objectx[nTex].m_VtxMax);
	SetVtxMin(Objectx[nTex].m_VtxMin);

	//何番目かのオブジェクト化を知らせる
	m_Objectx = Objectx[nTex];

	m_nTexCnt = nTex;

	return S_OK;
}

//モデルの終了処理
void CObjectx::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_OBJECTX; nCnt++)
	{
		for (int nCntMat = 0; nCntMat < (int)Objectx[m_nTexCnt].m_dwNumMat; nCntMat++)
		{
			//テクスチャの破棄
			if (Objectx[nCnt].m_apTexture[nCntMat] != NULL)
			{
				Objectx[nCnt].m_apTexture[nCntMat]->Release();
				Objectx[nCnt].m_apTexture[nCntMat] = NULL;
			}
		}

		//メッシュの破棄
		if (Objectx[nCnt].m_pMesh != NULL)
		{	  		
			Objectx[nCnt].m_pMesh->Release();
			Objectx[nCnt].m_pMesh = NULL;
		}

		//マテリアルの破棄
		if (Objectx[nCnt].m_pBuffMat != NULL)
		{			
			Objectx[nCnt].m_pBuffMat->Release();
			Objectx[nCnt].m_pBuffMat = NULL;
		}
	}
	CObject::Release();
}

//モデルの更新処理
void CObjectx::Update(void)
{

}

//モデルの描画処理
void CObjectx::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	D3DMATERIAL9 matDef;  //現在のマテリアル保存用

	D3DXMATERIAL *pMat;	  //マテリアルデータへのポインタ

	 //ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_Objectx.m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_Objectx.m_mtxWorld,
		&m_Objectx.m_mtxWorld,
		&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_Objectx.m_mtxWorld, &m_Objectx.m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Objectx.m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_Objectx.m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_Objectx.m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_Objectx.m_apTexture[nCntMat]);

		//モデル(パーツ)の描画
		m_Objectx.m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//============================
//位置をセットする
//============================
void CObjectx::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================
//移動量をセットする
//============================
void CObjectx::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================
//傾きをセットする
//============================
void CObjectx::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================
//色をセットする
//============================
void CObjectx::SetCol(D3DXCOLOR col)
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

////============================
////頂点情報をセットする
////============================
//void CObjectx::SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
//{
//	
//}

//============================
//体力をセットする
//============================
void CObjectx::SetLife(int nLife)
{
	m_nLife = nLife;
}

//============================
//モデル最大値をセットする
//============================
void CObjectx::SetVtxMax(D3DXVECTOR3 VtxMax)
{
	m_Objectx.m_VtxMax = VtxMax;
}

//============================
//モデル最小値をセットする
//============================
void CObjectx::SetVtxMin(D3DXVECTOR3 VtxMin)
{
	m_Objectx.m_VtxMin = VtxMin;
}


//============================
//位置の取得
//============================
D3DXVECTOR3 CObjectx::GetPosition(void)
{
	return m_pos;
}

//============================
//移動量の取得
//============================
D3DXVECTOR3 CObjectx::GetMove(void)
{
	return m_move;
}

//============================
//傾きの取得
//============================
D3DXVECTOR3 CObjectx::GetRot(void)
{
	return m_rot;
}

//============================
//色の取得
//============================
D3DXCOLOR CObjectx::GetCol(void)
{
	return m_col;
}

////============================
////頂点の取得
////============================
//LPDIRECT3DVERTEXBUFFER9 CObjectx::GetBuff(void)
//{
//	
//}

//============================
//体力取得
//============================
int CObjectx::GetLife(void)
{
	return m_nLife;
}

//============================
//最大値の取得
//============================
D3DXVECTOR3 CObjectx::GetVtxMax(void)
{
	return m_Objectx.m_VtxMax;
}

//============================
//最小値の取得
//============================
D3DXVECTOR3 CObjectx::GetVtxMin(void)
{
	return m_Objectx.m_VtxMin;
}


