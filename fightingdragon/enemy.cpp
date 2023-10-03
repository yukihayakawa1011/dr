//============================
//
//敵処理(enemy.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include "bg.h"
//#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "renderer.h"
#include "debugproc.h"
#include "sound.h"
#include "particle.h"
#include "mode.h"
#include "player.h"

//静的メンバ変数宣言
int CEnemy::m_nLife[MAX_ENEMY] = {};

//============================
//コンストラクタ
//============================
CEnemy::CEnemy()
{
	m_Enemystate = ENEMYSTATE_STANBY;
	nCntEnemy = 0;										//何番目の敵か知る

	m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_nCntState = 0;
}

CEnemy::CEnemy(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//デストラクタ
//============================
CEnemy::~CEnemy()
{
}

//============================
//テクスチャの生成(読み込み)
//============================
HRESULT CEnemy::Load(void)
{
	////デバイスの取得
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\g0OntK3S.jpg",
	//	&m_pTexture[0]);

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\lostwarm.png",
	//	&m_pTexture[1]);

	////テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\raginee.png",
	//	&m_pTexture[2]);

	return S_OK;
}

//============================
//テクスチャの破棄
//============================
void CEnemy::Unload(void)
{
	//for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	//{
	//	//テクスチャの破棄
	//	if (m_pTexture[nCnt] != NULL)
	//	{
	//		m_pTexture[nCnt]->Release();
	//		m_pTexture[nCnt] = NULL;
	//	}
	//}
}


//============================
//生成処理
//============================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CEnemy *pEnemy;

	//オブジェクト2Dの生成
	pEnemy = NEW_DBG CEnemy(pos);

	//初期化処理
	pEnemy->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex,fWidth,fHeight);

	////テクスチャの割り当て
	//pEnemy->BindTexture(m_pTexture[nTex]);

	return pEnemy;
}

//============================
//ポリゴンの初期化
//============================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	////デバイスの取得
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
		m_Enemystate = ENEMYSTATE_STANBY;

		SetState(m_Enemystate);

		m_nCntState = 60;

	//全てのパーツ数を初期化
	m_nNumModel = MAX_MODEL;

	//モデル生成
	m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), fRot, 0, fWidth, fHeight);
	m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, -1.0f, 0.0f), fRot, 1, fWidth, fHeight);
	m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 18.0f, 0.0f), fRot, 2, fWidth, fHeight);
	m_apModel[3] = CModel::Create(D3DXVECTOR3(4.0f, -10.0f, 0.0f), fRot, 3, fWidth, fHeight);
	m_apModel[4] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 0.0f), fRot, 4, fWidth, fHeight);
	m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 5, fWidth, fHeight);
	m_apModel[6] = CModel::Create(D3DXVECTOR3(-4.0f, -10.0f, 0.0f), fRot, 6, fWidth, fHeight);
	m_apModel[7] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 1.0f), fRot, 7, fWidth, fHeight);
	m_apModel[8] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 8, fWidth, fHeight);
	m_apModel[9] = CModel::Create(D3DXVECTOR3(5.0f, 15.0f, -1.0f), fRot, 9, fWidth, fHeight);
	m_apModel[10] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), fRot, 10, fWidth, fHeight);
	m_apModel[11] = CModel::Create(D3DXVECTOR3(5.7f, 0.0f, 0.0f), fRot, 11, fWidth, fHeight);
	m_apModel[12] = CModel::Create(D3DXVECTOR3(6.0f, 0.0f, 0.0f), fRot, 12, fWidth, fHeight);
	m_apModel[13] = CModel::Create(D3DXVECTOR3(-5.0f, 15.0f, -1.0f), fRot, 13, fWidth, fHeight);
	m_apModel[14] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.5f), fRot, 14, fWidth, fHeight);
	m_apModel[15] = CModel::Create(D3DXVECTOR3(-5.7f, 0.0f, -0.5f), fRot, 15, fWidth, fHeight);
	m_apModel[16] = CModel::Create(D3DXVECTOR3(-6.0f, 0.0f, 0.0f), fRot, 16, fWidth, fHeight);

	//親モデルの設定(全パーツ分)
	m_apModel[0]->SetParent(NULL);
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[2]->SetParent(m_apModel[1]);
	m_apModel[3]->SetParent(m_apModel[0]);
	m_apModel[4]->SetParent(m_apModel[3]);
	m_apModel[5]->SetParent(m_apModel[4]);
	m_apModel[6]->SetParent(m_apModel[0]);
	m_apModel[7]->SetParent(m_apModel[6]);
	m_apModel[8]->SetParent(m_apModel[7]);
	m_apModel[9]->SetParent(m_apModel[1]);
	m_apModel[10]->SetParent(m_apModel[9]);
	m_apModel[11]->SetParent(m_apModel[10]);
	m_apModel[12]->SetParent(m_apModel[11]);
	m_apModel[13]->SetParent(m_apModel[1]);
	m_apModel[14]->SetParent(m_apModel[13]);
	m_apModel[15]->SetParent(m_apModel[14]);
	m_apModel[16]->SetParent(m_apModel[15]);
	
	//種類を設定
	SetType(CObject::TYPE_ENEMY);

	if (nTex == 0)
	{
		m_nLife[0] = 5;

		SetLife(m_nLife[nTex], nTex);
	}

	if (nTex == 1)
	{
		m_nLife[1] = 5;

		SetLife(m_nLife[nTex], nTex);
	}

	if (nTex == 2)
	{
		m_nLife[2] = 5;

		SetLife(m_nLife[nTex], nTex);
	}

	m_ColEnemy = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	SetCol(m_ColEnemy);
	
	D3DXVECTOR3 move = GetMove();

	//移動量の初期化
	move.x = 3.0f;

	//移動量のセット
	SetMove(move);

	return S_OK;
}
//============================
//ポリゴンの終了
//============================
void CEnemy::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			delete m_apModel[nCnt];

			m_apModel[nCnt] = NULL;
		}
	}

	CObjectx::Release();
}
//============================
//ポリゴンの更新
//============================
void CEnemy::Update(void)
{
	//if()

	//オブジェクト3dのデータをもらう
	CObject3d *pobject3d = CGame::GetObject3d();
	bool bShowenemy = pobject3d->GetShowEnemy();

	D3DXVECTOR3 pos = GetPosition();

	m_posold = pos; //前回の位置を記録

	D3DXVECTOR3 move = GetMove();

	D3DXVECTOR3 rot = GetRot();

	CPlayer *m_pPlayer = CGame::GetPlayer();

	if (pos.z <= 0.0f)
	{//敵の位置(Z)が0だったら
		bShowenemy = true;

		pobject3d->SetShowEnemy(bShowenemy);

		m_Enemystate = ENEMYSTATE_ATTACK;

		SetState(m_Enemystate);

		if (move.x <= 0.0f)
		{
			rot.y = D3DX_PI * 0.5f;
		}
		else
		{
			rot.y = D3DX_PI * -0.5f;
		}

		//重力処理
		move.y -= 0.5f;

		if (move.y >= -1.0f)
		{
			m_bJump = true;

			SetJump(m_bJump);
		}

		//床の判定
		if (pos.y <= 1.0f)
		{
			m_bJump = false;
			move.y = 0.0f;
			pos.y = 1.0f;

			SetJump(m_bJump);
		}

		pos += move;

		SetPosition(pos);

		//物に当たったら移動量を反転
		if (HitBlock() == true)
		{
			move.x *= -1;
		}

		SetMove(move);


	}

	else
	{//敵の位置(Z)が0以外だったら
		if (m_pPlayer->GetPosition().x - 100.0f <= pos.x + 200.0f
			&&m_pPlayer->GetPosition().x + 10.0f >= pos.x
			&& m_pPlayer->GetPosition().y + 5.0f >= pos.y)
		{
			bShowenemy = false;

			pobject3d->SetShowEnemy(bShowenemy);

			move.z = -8.0f;

			pos.z += move.z;

			if (pos.z <= 0.0f)
			{
				pos.z = 0.0f;
			}

			if (pos.z >= 8.0f && pos.z <= 11.0f)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_WINDOW);
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SCREAM);

				CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 2, 20.0f, 20.0f);

				/*SetState(ENEMYSTATE_NONE);*/
			}

			SetPosition(pos);

		}

		if (m_pPlayer->GetPosition().x + 50.0f <= pos.x
			&&m_pPlayer->GetPosition().x - 10.0f >= pos.x - 200.0f
			&& m_pPlayer->GetPosition().y + 5.0f >= pos.y)
		{
			bShowenemy = false;

			pobject3d->SetShowEnemy(bShowenemy);

			move.z = -8.0f;

			pos.z += move.z;

			if (pos.z <= 0.0f)
			{
				pos.z = 0.0f;
			}

			if (pos.z >= 8.0f && pos.z <= 11.0f)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_WINDOW);
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SCREAM);

				CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 2, 20.0f, 20.0f);

				/*SetState(ENEMYSTATE_NONE);*/

				SetMove(D3DXVECTOR3(-3.0f, move.y, 0.0f));
			}

			SetPosition(pos);
		}
	}

	if (bShowenemy == false)
	{
		m_Enemystate = ENEMYSTATE_NONE;

		SetState(m_Enemystate);
	}

	if (bShowenemy == true && pos.z > 0.0f)
	{
		m_Enemystate = ENEMYSTATE_STANBY;

		SetState(m_Enemystate);
	}

	SetRot(rot);

	//デバッグ表示の情報を渡す
	CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("敵の総数 : %d\n", m_nEnemy);

	//敵の場所デバック情報
	pDebug->Print("敵の場所 X : %f Y : %f Z : %f\n", pos.x, pos.y, pos.z);

	pDebug->Print("敵の移動量 X : %f Y : %f Z : %f\n", move.x, move.y, move.z);

	pDebug->Print("敵0の体力 : %d\n", m_nLife[0]);
	pDebug->Print("敵1の体力 : %d\n", m_nLife[1]);
	pDebug->Print("敵2の体力 : %d\n", m_nLife[2]);
#endif

	//VERTEX_2D *pVtx;    //頂点情報へのポインタ

	//					/*頂点バッファをロックし、頂点情報へのポインタを取得*/
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y - 10.0f + move.y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y - 10.0f + move.y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y + 10.0f + move.y, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y + 10.0f + move.y, 0.0f);

	////rhw(法線)の設定
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////頂点カラーの設定
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	////テクスチャ座標の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////頂点バッファをアンロックする
	//m_pVtxBuff->Unlock();

	/*if (m_nLife < 0)
	{
		CExplosion::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 0);

		Release();
	}*/

	

}
//============================
//ポリゴンの描画
//============================
void CEnemy::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRot();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//D3DMATERIAL9 matDef;  //現在のマテリアル保存用

	//D3DXMATERIAL *pMat;	  //マテリアルデータへのポインタ
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			rot.y, rot.x, rot.z);

		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			&mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans,
			pos.x, pos.y, pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		for (int nCntMat = 0; nCntMat < m_nNumModel; nCntMat++)
		{
			if (m_Enemystate == ENEMYSTATE_STANBY)
			{
				m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

				//モデル(パーツ)の描画
				m_apModel[nCntMat]->DrawCol(m_ColEnemy);
			}
			if (m_Enemystate == ENEMYSTATE_ATTACK)
			{
				//モデル(パーツ)の描画
				m_apModel[nCntMat]->Draw();
			}
			if (m_Enemystate == ENEMYSTATE_DAMAGE)
			{
				m_ColEnemy = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				//モデル(パーツ)の描画
				m_apModel[nCntMat]->DrawCol(m_ColEnemy);
			}

			if (m_Enemystate == ENEMYSTATE_NONE)
			{
				m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

				//モデル(パーツ)の描画
				m_apModel[nCntMat]->DrawCol(m_ColEnemy);
			}

			////現在のマテリアルを取得
			//pDevice->GetMaterial(&matDef);

			////マテリアルデータへのポインタを取得
			//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		}
		/*保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);*/
}

//========================
//敵のダメージ
//========================
void CEnemy::AddDamage(int nDamage,int nEnemy)
{
	m_nLife[nEnemy] = m_nLife[nEnemy] - nDamage;

	SetLife(m_nLife[nEnemy],nEnemy);

	m_Enemystate = ENEMYSTATE_DAMAGE;

	SetState(m_Enemystate);

	//デバッグ表示の情報を渡す
	CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("敵%dの体力 : %d\n",nEnemy, m_nLife[0]);
	pDebug->Print("敵%dの体力 : %d\n",nEnemy + 1, m_nLife[1]);
	pDebug->Print("敵%dの体力 : %d\n",nEnemy + 2, m_nLife[2]);
#endif
}

//==============================
//ブロックとの当たり判定(3D)
//==============================
bool CEnemy::HitBlock(void)
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		CObject *pObj = NULL;

		CObjectx *pObjectx = NULL;

		//オブジェクトを取得
		pObj = GetObject(nCnt);

		//NULLチェック
		if (pObj != NULL)
		{
			TYPE type;

			//種類を取得
			type = pObj->GetType();

			D3DXVECTOR3 move = GetMove();

			////位置取得
			//D3DXVECTOR3 posBlock = pObj->GetPosition();

			if (type == TYPE_BLOCK || type == TYPE_FLOOR || type == TYPE_LONGFLOOR)
			{
				pObjectx = dynamic_cast<CObjectx*>(pObj);

				if (pObjectx != NULL)
				{
					if (GetPosition().z + ENEMY_MIN_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z
						&& GetPosition().z + ENEMY_MIN_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z)
					{
						if (GetPosition().y + ENEMY_MIN_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y
							&& GetPosition().y + ENEMY_MIN_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y)
						{
							//左からの当たり判定
							if (GetPosition().x + ENEMY_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x
								&& m_posold.x + ENEMY_MAX_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
							{//プレイヤーとブロックが当たった 

							 //位置を左側に固定
								SetPosition(D3DXVECTOR3(pObjectx->GetPosition().x + pObjectx->GetVtxMin().x - ENEMY_MAX_X, GetPosition().y, GetPosition().z));

								/*move.x = 0.0f;*/

								//ジャンプができるように
								SetJump(false);

								return true;
							}

							//右からの当たり判定
							if (GetPosition().x + ENEMY_MIN_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
								&& m_posold.x + ENEMY_MIN_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x)
							{//プレイヤーとブロックが当たった 

							 //プレイヤーを右側に固定
								SetPosition(D3DXVECTOR3(pObjectx->GetPosition().x + pObjectx->GetVtxMax().x - ENEMY_MIN_X, GetPosition().y, GetPosition().z));

								move.x = 0.0f;

								//ジャンプができるように
								SetJump(false);

								return true;

								////ジャンプができるように
								//SetJump(false);

							}
						}
					}

					if (GetPosition().x + ENEMY_MAX_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
						&& GetPosition().x + ENEMY_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
					{
						//手前からの当たり判定
						if (GetPosition().z + ENEMY_MAX_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z
							&& m_posold.z + ENEMY_MAX_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z)
						{//プレイヤーとブロックが当たった 

						 //プレイヤーを奥側に固定
							SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, pObjectx->GetPosition().z + pObjectx->GetVtxMin().z - ENEMY_MAX_Z));

							/*move.x = 0.0f;*/

							////ジャンプができるように
							//SetJump(false);

						}

						//奥からの当たり判定
						if (GetPosition().z + ENEMY_MIN_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z
							&& m_posold.z + ENEMY_MIN_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z)
						{//プレイヤーとブロックが当たった 

						 //プレイヤーを手前側に固定
							SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, pObjectx->GetPosition().z + pObjectx->GetVtxMax().z - ENEMY_MIN_Z));

							move.x = 0.0f;

							////ジャンプができるように
							//SetJump(false);

						}
					}

					if (GetPosition().x + ENEMY_MIN_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
						&& GetPosition().x + ENEMY_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
					{
						//手前からの当たり判定
						if (GetPosition().y + ENEMY_MAX_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y
							&& m_posold.y + ENEMY_MAX_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y)
						{//プレイヤーとブロックが当たった 

						 //プレイヤーを奥側に固定
							SetPosition(D3DXVECTOR3(GetPosition().x, pObjectx->GetPosition().y - pObjectx->GetVtxMin().y - ENEMY_MAX_Y, GetPosition().z));

							move.y = 0.0f;

							//ジャンプができるように
							SetJump(false);

							////ジャンプができるように
							//SetJump(false);

						}

						//奥からの当たり判定
						if (GetPosition().y + ENEMY_MIN_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y
							&& m_posold.y + ENEMY_MIN_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y)
						{//プレイヤーとブロックが当たった 

						 //プレイヤーを奥側に固定
							SetPosition(D3DXVECTOR3(GetPosition().x, pObjectx->GetPosition().y + pObjectx->GetVtxMax().y + ENEMY_MIN_Y, GetPosition().z));

							move.y = 0.0f;

							//ジャンプができるように
							SetJump(false);

							////ジャンプができるように
							//SetJump(false);

						}
					}

				}
			}

			//位置と移動情報をセット
			SetPosition(GetPosition());
			SetMove(move);
		}
	}
	return false;
}

//============================
//体力をセットする
//============================
void CEnemy::SetLife(int nLife,int nEnemy)
{
	if (nEnemy == 0)
	{
		nEnemy = 0;
	}

	if (nEnemy == 1)
	{
		nEnemy = 1;
	}

	if (nEnemy == 2)
	{
		nEnemy = 2;
	}

	m_nLife[nEnemy] = nLife;
}

//============================
//体力取得
//============================
int CEnemy::GetLife(int nEnemy)
{
	return m_nLife[nEnemy];
}

//============================
//状態をセットする
//============================
void CEnemy::SetState(EnemyState state)
{
	/*if (nEnemy == 0)
	{
		nEnemy = 0;
	}

	if (nEnemy == 1)
	{
		nEnemy = 1;
	}

	if (nEnemy == 2)
	{
		nEnemy = 2;
	}
*/
	m_Enemystate = state;

	switch (m_Enemystate)
	{
	case ENEMYSTATE_STANBY:

		

		break;

	case ENEMYSTATE_ATTACK:

		m_nCntState = 60;

		break;

	case ENEMYSTATE_DAMAGE:

		m_nCntState--;

		if (m_nCntState == 0)
		{
			m_Enemystate = ENEMYSTATE_ATTACK;
		}

		break;

	case ENEMYSTATE_NONE:

		break;
	}
}

//============================
//状態を取得
//============================
CEnemy::EnemyState CEnemy::GetState(int nEnemy)
{
	return m_Enemystate;
}

//============================
//ジャンプしてるかどうかをセットする
//============================
void CEnemy::SetJump(bool jump)
{
	m_bJump = jump;
}

//============================
//ジャンプしてるかどうかの取得
//============================
bool CEnemy::GetJump(void)
{
	return m_bJump;
}

////======================
////敵の位置取得
////======================
//CEnemy CEnemy::GetPos(void)
//{
//	return m_pos;
//}
//
////======================
////敵の位置設定
////======================
//void CEnemy::SetPos(D3DXVECTOR3 pos)
//{
//	m_pos = pos;
//}
