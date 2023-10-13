//============================
//
//モデル処理(model.cpp)
//Author:早川 友貴
//
//============================
#include "main.h"
#include "model.h"
#include "renderer.h"
#include "objectx.h"

//静的メンバ変数宣言
CModel::SET_MODEL CModel::pModels[MAX_PART] = {};

//============================
//コンストラクタ
//============================
CModel::CModel()
{
	//m_pMesh = NULL;								//メッシュ
	//m_pBuffMat = NULL;						//頂点情報のマテリアル
	//m_dwNumMat = 0;								//マテリアル
												//D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	for (int nCntIndx = 0; nCntIndx < MAX_PART; nCntIndx++)
	{
		m_nIdx = nCntIndx;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置をクリア
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//傾きをクリア

	m_Type = MODELTYPE_PLAYER;							//モデルのタイプをクリア
}

//============================
//デストラクタ
//============================
CModel::~CModel()
{

}

//============================
//生成処理
//============================
CModel *CModel::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, int nType)
{
	CModel *pModel;

	//オブジェクト2Dの生成
	pModel = NEW_DBG CModel;

	//初期化処理
	pModel->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex, fWidth, fHeight,nType);

	return pModel;
}

//====================
//モデルの初期化
//====================
HRESULT CModel::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, int nType)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	DWORD dwSizeFVF;  //頂点フォーマットのサイズ

	BYTE *pVtxBUff;  //頂点バッファのポインタ

	int nNumVtx;  //頂点数

	if (nType == 0)
	{
		m_Type = MODELTYPE_PLAYER;
	}
	if (nType == 1)
	{
		m_Type = MODELTYPE_ENEMY0;
	}
	if (nType == 2)
	{
		m_Type = MODELTYPE_ENEMY1;
	}
	if (nType == 3)
	{
		m_Type = MODELTYPE_ENEMY2;
	}

	if (m_Type == MODELTYPE_PLAYER)
	{
		if (nTex == 0)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\hip.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[0].m_pBuffMat,
				NULL,
				&pModels[0].m_dwNumMat,
				&pModels[0].m_pMesh);
		}

		if (nTex == 1)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\body.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[1].m_pBuffMat,
				NULL,
				&pModels[1].m_dwNumMat,
				&pModels[1].m_pMesh);
		}

		if (nTex == 2)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\head.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[2].m_pBuffMat,
				NULL,
				&pModels[2].m_dwNumMat,
				&pModels[2].m_pMesh);
		}

		if (nTex == 3)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\tigh_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[3].m_pBuffMat,
				NULL,
				&pModels[3].m_dwNumMat,
				&pModels[3].m_pMesh);
		}

		if (nTex == 4)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\leg_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[4].m_pBuffMat,
				NULL,
				&pModels[4].m_dwNumMat,
				&pModels[4].m_pMesh);
		}

		if (nTex == 5)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\shuuze_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[5].m_pBuffMat,
				NULL,
				&pModels[5].m_dwNumMat,
				&pModels[5].m_pMesh);
		}

		if (nTex == 6)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\tigh_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[6].m_pBuffMat,
				NULL,
				&pModels[6].m_dwNumMat,
				&pModels[6].m_pMesh);
		}

		if (nTex == 7)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\leg_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[7].m_pBuffMat,
				NULL,
				&pModels[7].m_dwNumMat,
				&pModels[7].m_pMesh);
		}

		if (nTex == 8)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\shuuze_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[8].m_pBuffMat,
				NULL,
				&pModels[8].m_dwNumMat,
				&pModels[8].m_pMesh);
		}

		if (nTex == 9)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\shoulder_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[9].m_pBuffMat,
				NULL,
				&pModels[9].m_dwNumMat,
				&pModels[9].m_pMesh);
		}

		if (nTex == 10)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\arm_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[10].m_pBuffMat,
				NULL,
				&pModels[10].m_dwNumMat,
				&pModels[10].m_pMesh);
		}

		if (nTex == 11)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\arm2_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[11].m_pBuffMat,
				NULL,
				&pModels[11].m_dwNumMat,
				&pModels[11].m_pMesh);
		}

		if (nTex == 12)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\hand_l.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[12].m_pBuffMat,
				NULL,
				&pModels[12].m_dwNumMat,
				&pModels[12].m_pMesh);
		}

		if (nTex == 13)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\shoulder_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[13].m_pBuffMat,
				NULL,
				&pModels[13].m_dwNumMat,
				&pModels[13].m_pMesh);
		}

		if (nTex == 14)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\arm_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[14].m_pBuffMat,
				NULL,
				&pModels[14].m_dwNumMat,
				&pModels[14].m_pMesh);
		}

		if (nTex == 15)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\arm2_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[15].m_pBuffMat,
				NULL,
				&pModels[15].m_dwNumMat,
				&pModels[15].m_pMesh);
		}

		if (nTex == 16)
		{
			//Xファイルの読み込み
			D3DXLoadMeshFromX("data\\MODEL\\hand_r.x",
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&pModels[16].m_pBuffMat,
				NULL,
				&pModels[16].m_dwNumMat,
				&pModels[16].m_pMesh);
		}
	}

	D3DXMATERIAL *pMat; //マテリアルへのポインタ

	
		if (pModels[nTex].m_pBuffMat != NULL)
		{
			//マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)pModels[nTex].m_pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)pModels[nTex].m_dwNumMat; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//テクスチャファイルネームが存在する
				 //テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&pModels[nTex].m_apTexture[nCntMat]);
				}
			}
		}

	SetPos(pos);

		if (pModels[nTex].m_pMesh != NULL)
		{
			//頂点数の取得
			nNumVtx = pModels[nTex].m_pMesh->GetNumVertices();

			//頂点フォーマットのサイズを取得
			dwSizeFVF = D3DXGetFVFVertexSize(pModels[nTex].m_pMesh->GetFVF());

			//頂点バッファをロック
			pModels[nTex].m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBUff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				//頂点座標の代入
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBUff;

				if (vtx.x > pModels[nTex].m_VtxMax.x)
				{
					pModels[nTex].m_VtxMax.x = vtx.x;
				}

				if (vtx.x < pModels[nTex].m_VtxMin.x)
				{
					pModels[nTex].m_VtxMin.x = vtx.x;
				}

				if (vtx.y > pModels[nTex].m_VtxMax.y)
				{
					pModels[nTex].m_VtxMax.y = vtx.y;
				}

				if (vtx.y < pModels[nTex].m_VtxMin.y)
				{
					pModels[nTex].m_VtxMin.y = vtx.y;
				}

				if (vtx.z > pModels[nTex].m_VtxMax.z)
				{
					pModels[nTex].m_VtxMax.z = vtx.z;
				}

				if (vtx.z < pModels[nTex].m_VtxMin.z)
				{
					pModels[nTex].m_VtxMin.z = vtx.z;
				}

				pVtxBUff += dwSizeFVF;	//頂点フォーマットのサイズ分ぼいんを進める
			}

			//頂点バッファをアンロック
			pModels[nTex].m_pMesh->UnlockVertexBuffer();
		}

		//モデルの情報を渡す
		nModel = nTex;

		//モデルの幅・高さをセット
		SetVtxMax(pModels[nModel].m_VtxMax);
		SetVtxMin(pModels[nModel].m_VtxMin);

		SetBuffMat(pModels[nModel].m_pBuffMat);

		//共有のデータを引き継ぎ
		Model = pModels[nTex];

	return S_OK;
}

//モデルの終了処理
void CModel::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		//メッシュの破棄
		if (pModels[nCnt].m_pMesh != NULL)
		{
			pModels[nCnt].m_pMesh->Release();
			pModels[nCnt].m_pMesh = NULL;
		}

		//マテリアルの破棄
		if (pModels[nCnt].m_pBuffMat != NULL)
		{
			pModels[nCnt].m_pBuffMat->Release();
			pModels[nCnt].m_pBuffMat = NULL;
		}
	}
}

//モデルの更新処理
void CModel::Update(void)
{
	SetPos(m_pos);

	////奥移動
	//if (GetKeyboardPress(DIK_W) == true)
	//{
	//	if (GetKeyboardPress(DIK_D) == true)
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.25f * D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.25f * D3DX_PI) * 1.0f;
	//	}

	//	else if (GetKeyboardPress(DIK_A) == true)
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.25f * -D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.25f * -D3DX_PI) * 1.0f;
	//	}

	//	else
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.0f * D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.0f * D3DX_PI) * 1.0f;
	//	}
	//}

	////手前移動
	//else if (GetKeyboardPress(DIK_S) == true)
	//{
	//	if (GetKeyboardPress(DIK_D) == true)
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.75f * D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.75f * D3DX_PI) * 1.0f;
	//	}

	//	else if (GetKeyboardPress(DIK_A) == true)
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 0.75f * -D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 0.75f * -D3DX_PI) * 1.0f;
	//	}

	//	else
	//	{
	//		g_posModel.x += sinf(g_rotModel.x + 1.0f * D3DX_PI) * 1.0f;
	//		g_posModel.z += cosf(g_rotModel.z + 1.0f * D3DX_PI) * 1.0f;
	//	}
	//}

	////左移動
	//else if (GetKeyboardPress(DIK_A) == true)
	//{
	//	g_posModel.x -= sinf(g_rotModel.x + 0.5f * D3DX_PI) * 1.0f;
	//	g_posModel.z -= cosf(g_rotModel.z + 0.5f * D3DX_PI) * 1.0f;
	//}

	////右移動
	//else if (GetKeyboardPress(DIK_D) == true)
	//{
	//	g_posModel.x += sinf(g_rotModel.x + 0.5f * D3DX_PI) * 1.0f;
	//	g_posModel.z += cosf(g_rotModel.z + 0.5f * D3DX_PI) * 1.0f;
	//}

	////上移動
	//if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_posModel.y += 0.4f;
	//}

	////下移動
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	g_posModel.y -= 0.4f;
	//}
}

//モデルの描画処理
void CModel::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//全モデル[パーツ]の描画
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	D3DMATERIAL9 matDef;  //現在のマテリアル保存用

	D3DXMATERIAL *pMat;	  //マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&Model.m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&Model.m_mtxWorld,
		&Model.m_mtxWorld,
		&mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&Model.m_mtxWorld, &Model.m_mtxWorld, &mtxTrans);

	//パーツの親のマトリックスを設定
	if (m_pParent != NULL)
	{//親モデルがある場合
		Model.m_mtxParent = m_pParent->GetMtxWorld();  //親インデックスを取得
	}

	else
	{//親モデルがない場合
	 //現在のマトリックスを取得する
		pDevice->GetTransform(D3DTS_WORLD, &Model.m_mtxParent); //プレイヤーのマトリックスを設定
	}

	//貸し出したパーツのワールドマトリックスと親のマトリックスを掛け合わせる
	D3DXMatrixMultiply(&Model.m_mtxWorld,
		&Model.m_mtxWorld,
		&Model.m_mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &Model.m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)Model.m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)Model.m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, Model.m_apTexture[nCntMat]);

		//モデル(パーツ)の描画
		Model.m_pMesh->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//モデルの描画処理
void CModel::DrawCol(D3DXCOLOR col)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//全モデル[パーツ]の描画
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	D3DMATERIAL9 matDef;  //現在のマテリアル保存用

	D3DXMATERIAL *pMat;	  //マテリアルデータへのポインタ

	D3DXMATERIAL mat;

	ZeroMemory(&mat, sizeof(D3DXMATERIAL));
		
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&Model.m_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&Model.m_mtxWorld,
			&Model.m_mtxWorld,
			&mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&Model.m_mtxWorld, &Model.m_mtxWorld, &mtxTrans);

		//パーツの親のマトリックスを設定
		if (m_pParent != NULL)
		{//親モデルがある場合
			Model.m_mtxParent = m_pParent->GetMtxWorld();  //親インデックスを取得
		}

		else
		{//親モデルがない場合
			//現在のマトリックスを取得する
			pDevice->GetTransform(D3DTS_WORLD, &Model.m_mtxParent); //プレイヤーのマトリックスを設定
		}

		//貸し出したパーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&Model.m_mtxWorld,
			&Model.m_mtxWorld,
			&Model.m_mtxParent);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &Model.m_mtxWorld);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)Model.m_pBuffMat->GetBufferPointer();

		mat.MatD3D.Ambient = col;
		mat.MatD3D.Diffuse = col;
		//mat.MatD3D.Emissive = col;

		for (int nCntMat = 0; nCntMat < (int)Model.m_dwNumMat; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&mat.MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, Model.m_apTexture[nCntMat]);

			//モデル(パーツ)の描画
			Model.m_pMesh->DrawSubset(nCntMat);
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
}

//========================
//親モデルの設定
//========================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//========================
//マトリックス情報を渡す
//========================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return Model.m_mtxWorld;
}


//============================
//位置をセットする
//============================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//============================
//移動量をセットする
//============================
void CModel::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//============================
//傾きをセットする
//============================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//============================
//モデル最大値をセットする
//============================
void CModel::SetVtxMax(D3DXVECTOR3 VtxMax)
{
	Model.m_VtxMax = VtxMax;
}

//============================
//モデル最小値をセットする
//============================
void CModel::SetVtxMin(D3DXVECTOR3 VtxMin)
{
	Model.m_VtxMin = VtxMin;
}

//============================
//モデルマテリアル情報セットする
//============================
void CModel::SetBuffMat(LPD3DXBUFFER Mat)
{
	Model.m_pBuffMat = Mat;
}

//============================
//モデルタイプ情報セットする
//============================
void CModel::SetModelType(MODELTYPE type)
{
	m_Type = type;
}

//============================
//位置の取得
//============================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//============================
//移動量の取得
//============================
D3DXVECTOR3 CModel::GetMove(void)
{
	return m_move;
}

//============================
//傾きの取得
//============================
D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//============================
//最大値の取得
//============================
D3DXVECTOR3 CModel::GetVtxMax(void)
{
	return Model.m_VtxMax;
}

//============================
//最小値の取得
//============================
D3DXVECTOR3 CModel::GetVtxMin(void)
{
	return Model.m_VtxMin;
}

//============================
//マテリアル情報の取得
//============================
LPD3DXBUFFER CModel::GetBuffMat(void)
{
	return Model.m_pBuffMat;
}

//============================
//モデル情報の取得
//============================
CModel::SET_MODEL *CModel::GetModel(void)
{
	return &Model;
}


