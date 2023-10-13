//============================
//
//プレイヤー処理(player.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include "bg.h"
#include "input.h"
#include "player.h"
//#include "bullet.h"
#include "sound.h"
#include "score.h"
#include "block.h"
#include "renderer.h"
#include "bilboard.h"
#include "debugproc.h"
#include "enemy.h"
#include "particle.h"
#include "time.h"
#include "mode.h"

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9  CPlayer::m_pTexture;
//============================
//コンストラクタ
//============================
CPlayer::CPlayer()
{
	m_fLength = 0.0f;
	m_movefLength = 0.0f;
	m_fAngle = 0.0f;
	m_posold = D3DXVECTOR3(0.0f,0.0f,0.0f);						//古い位置
	m_bJump = false;											//ジャンプ中かどうか
	m_fWidth = 0.0f;											//プレイヤー幅をクリア
	m_fHeight = 0.0f;											//プレイヤー高さをクリア
	m_nNumModel = 0;											//モデルの最大数をクリア
	m_bDeath = false;											//プレイヤーの生死判定をクリア
	m_ShotRot = 0.0f;											//弾の方向をクリア
	m_bRot = false;												//プレイヤーの向きをクリア
	m_bAim = false;												//プレイヤーがエイムしてるかどうかをクリア
	m_nLife = 0;												//プレイヤーの体力をクリア
	m_PlayerState = PLAYER_NONE;								//プレイヤーの状態をクリア
	m_stateCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);				//色をクリア
	m_nCntState = 0;											//プレイヤー状態カウントをクリア

	m_nNumAll = 0;				//数の最大数
	m_nType = 0;			//種類
	bLoop = false;							//終了するかどうか
	m_nKey = 0;								//キーの数
	m_nCounter = 0;						//モーションカウンター
	m_bFinish = false;						//終了するかどうか
	m_bAttack = false;						//攻撃状態に入っているかどうかをクリア

	m_nNumModel = 0;						//モーションの総数

	nPunchSpeed = 0;						//パンチ間隔

	/*for (int nCnt = 0; nCnt < MOTIONTYPE_MAX; nCnt++)
	{
		m_aInfo[nCnt].nNumKey = 0;
		m_aInfo[nCnt].aKeyinfo[nCnt + 1].nFrame = 0;
	}

	m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame;*/

	memset(&m_InitPartPos[0], NULL, sizeof(D3DXVECTOR3));

	memset(&m_aInfo[0], NULL, sizeof(m_aInfo));

	m_nFrameCnt = 0;

	/*プレイヤー通常変数のクリア
	m_NoneMat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_NoneMat.MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_NoneMat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	プレイヤーを赤くさせる変数のクリア
	m_RedMat.MatD3D.Ambient = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_RedMat.MatD3D.Diffuse = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_RedMat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	プレイヤーを薄くさせる変数のクリア
	m_InvincibleMat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_InvincibleMat.MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_InvincibleMat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);*/
	/*m_nldxShadow = 0;*/
}

//============================
//デストラクタ
//============================
CPlayer::~CPlayer()
{

}

////============================
////テクスチャの生成(読み込み)
////============================
//HRESULT CPlayer::Load(void)
//{
//	//デバイスの取得
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	//テクスチャの読み込み
//			D3DXCreateTextureFromFile(pDevice,
//				"data\\TEXTURE\\raginee.png",
//				&m_pTexture);
//
//	return S_OK;
//}
//
////============================
////テクスチャの破棄
////============================
//void CPlayer::Unload(void)
//{
//	//テクスチャの破棄
//	if (m_pTexture != NULL)
//	{
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//}

//============================
//生成処理
//============================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CPlayer *pPlayer;

	//オブジェクト2Dの生成
	pPlayer = NEW_DBG CPlayer;

	//初期化処理
	pPlayer->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex,fWidth,fHeight);

	////テクスチャの割り当て
	//pPlayer->BindTexture(m_pTexture);

	return pPlayer;
}

//============================
//ポリゴンの初期化
//============================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	/*m_nldxShadow = SetShadow();

	m_pMotion = NEW_DBG CMotion;

	m_pMotion->Init(pos, fRot, nTex, fWidth, fHeight);*/

	//fHeight = 0.0f;
	//fWidth = 0.0f;
	//nTex = 0;
	//fRot = 0.0f;
	//pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	nPunchSpeed = PLAYER_PUNCH_SPEED;

	m_nKey = 0;								//キーの数

	m_nFrameCnt = 0;

	m_stateCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	SetPosition(pos);

	nTex = 0;

	m_bDeath = false;	//プレイヤーが死んだかどうか初期化

	m_bRot = false;		//プレイヤーの向き情報を初期化

	m_bJump = false;	//プレイヤーのジャンプ情報を初期化

	SetJump(m_bJump);

	m_ShotRot = 50.0f;   //弾の方向を初期化

	m_nLife = 3;		 //ライフを初期化

	m_PlayerState = PLAYER_NONE;	//プレイヤーの状態を初期化

	m_nCntState = 120;				//プレイヤー状態カウントを初期化

	m_bAttack = false;				//攻撃状態かどうかを初期化

	for (int nCntInfo = 0; nCntInfo < MAX_PART; nCntInfo++)
	{
		m_aInfo[nCntInfo].nNumKey = 0;

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			m_aInfo[nCntInfo].aKeyinfo[nCnt].nFrame = 60;
		}
	}

	/*SetRot(D3DXVECTOR3(0.0f,0.0f,0.0f));*/

	//全てのパーツ数を初期化
	m_nNumModel = MAX_PART;

	/*if (m_player_mode[nTex] == PLAYER_PLAYER)
	{*/
		//モデル生成
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 32.0f, 0.0f), fRot, 0, fWidth, fHeight,0);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), fRot, 1, fWidth, fHeight, 0);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 18.0f, 0.0f), fRot, 2, fWidth, fHeight, 0);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(2.0f, -9.0f, -0.9f), fRot, 3, fWidth, fHeight, 0);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(0.3f, -12.0f, 0.0f), fRot, 4, fWidth, fHeight, 0);
		m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 5, fWidth, fHeight, 0);
		m_apModel[6] = CModel::Create(D3DXVECTOR3(-2.0f, -9.0f, -0.9f), fRot, 6, fWidth, fHeight, 0);
		m_apModel[7] = CModel::Create(D3DXVECTOR3(0.3f, -12.0f, 0.0f), fRot, 7, fWidth, fHeight,0);
		m_apModel[8] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 8, fWidth, fHeight,0);
		m_apModel[9] = CModel::Create(D3DXVECTOR3(5.0f, 15.0f, -1.0f), fRot, 9, fWidth, fHeight,0);
		m_apModel[10] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), fRot, 10, fWidth, fHeight,0);
		m_apModel[11] = CModel::Create(D3DXVECTOR3(5.7f, 0.0f, 0.0f), fRot, 11, fWidth, fHeight,0);
		m_apModel[12] = CModel::Create(D3DXVECTOR3(6.0f, 0.0f, 0.0f), fRot, 12, fWidth, fHeight,0);
		m_apModel[13] = CModel::Create(D3DXVECTOR3(-5.0f, 15.0f, -1.0f), fRot, 13, fWidth, fHeight, 0);
		m_apModel[14] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.5f), fRot, 14, fWidth, fHeight, 0);
		m_apModel[15] = CModel::Create(D3DXVECTOR3(-5.7f, 0.0f, -0.5f), fRot, 15, fWidth, fHeight, 0);
		m_apModel[16] = CModel::Create(D3DXVECTOR3(-6.0f, 0.0f, 0.0f), fRot, 16, fWidth, fHeight, 0);
		/*m_apModel[17] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), fRot, 17, fWidth, fHeight);*/
	//}

	//if (m_player_mode[nTex] == PLAYER_MIRROR)
	//{
	//	//モデル生成
	//	m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 38.0f, 0.0f), fRot, 0, fWidth, fHeight);
	//	m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, -1.0f, 0.0f), fRot, 1, fWidth, fHeight);
	//	m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 18.0f, 0.0f), fRot, 2, fWidth, fHeight);
	//	m_apModel[3] = CModel::Create(D3DXVECTOR3(4.0f, -10.0f, 0.0f), fRot, 3, fWidth, fHeight);
	//	m_apModel[4] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 0.0f), fRot, 4, fWidth, fHeight);
	//	m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 5, fWidth, fHeight);
	//	m_apModel[6] = CModel::Create(D3DXVECTOR3(-4.0f, -10.0f, 0.0f), fRot, 6, fWidth, fHeight);
	//	m_apModel[7] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 1.0f), fRot, 7, fWidth, fHeight);
	//	m_apModel[8] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 8, fWidth, fHeight);
	//	m_apModel[9] = CModel::Create(D3DXVECTOR3(5.0f, 15.0f, -1.0f), fRot, 9, fWidth, fHeight);
	//	m_apModel[10] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), fRot, 10, fWidth, fHeight);
	//	m_apModel[11] = CModel::Create(D3DXVECTOR3(5.7f, 0.0f, 0.0f), fRot, 11, fWidth, fHeight);
	//	m_apModel[12] = CModel::Create(D3DXVECTOR3(6.0f, 0.0f, 0.0f), fRot, 12, fWidth, fHeight);
	//	m_apModel[13] = CModel::Create(D3DXVECTOR3(-5.0f, 15.0f, -1.0f), fRot, 13, fWidth, fHeight);
	//	m_apModel[14] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.5f), fRot, 14, fWidth, fHeight);
	//	m_apModel[15] = CModel::Create(D3DXVECTOR3(-5.7f, 0.0f, -0.5f), fRot, 15, fWidth, fHeight);
	//	m_apModel[16] = CModel::Create(D3DXVECTOR3(-6.0f, 0.0f, 0.0f), fRot, 16, fWidth, fHeight);
	//	m_apModel[17] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), fRot, 17, fWidth, fHeight);
	//}

		for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
		{
			m_InitPartPos[nCnt] = m_apModel[nCnt]->GetPos();
		}

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
	//m_apModel[17]->SetParent(m_apModel[16]);

	/*CObjectx::Init(pos, fRot, nTex, fWidth, fHeight);*/

	//種類の設定
	SetType(CObject::TYPE_PLAYER);

	////対角線の長さを算出する
	//m_fLength = sqrtf(fWidth * fWidth + fHeight * fHeight) * 0.5f;

	////対角線の角度を算出する
	//m_fAngle = atan2f(fWidth, fHeight);

	////頂点バッファの生成
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&m_pVtxBuff,
	//	NULL);

	////頂点バッファがNULLだったら
	//if (m_pVtxBuff == NULL)
	//{
	//	return E_FAIL;
	//}

	////テクスチャのポインタがNULLだったら
	//if (m_pTexture == NULL)
	//{
	//	return E_FAIL;
	//}

	//VERTEX_3D *pVtx;    //頂点情報へのポインタ

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y, 0.0f);


	////////角度を決める
	//////m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////////長さを算出する
	//////m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////////頂点座標の設定
	//////pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//////pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//////pVtx[0].pos.z = 0.0f;			   

	//////pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//////pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//////pVtx[1].pos.z = 0.0f;			    

	//////pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//////pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//////pVtx[2].pos.z = 0.0f;			    

	//////pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//////pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//////pVtx[3].pos.z = 0.0f;

	//// 法線ベクトルの設定
	//pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

	SetPosition(pos);

	SetRot(D3DXVECTOR3(0.0f,fRot,0.0f));

	SetDeath(m_bDeath);

	m_fWidth = fWidth;

	m_fHeight = fHeight;

	SetLife(m_nLife);

	SetState(m_PlayerState);

	SetMotionPlayer(MOTIONTYPE_NEUTRAL);

	return S_OK;
}
//============================
//ポリゴンの終了
//============================
void CPlayer::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			delete m_apModel[nCnt];

			m_apModel[nCnt] = NULL;
		}
	}

	/*if (m_pMotion != NULL)
	{
		delete m_pMotion;

		m_pMotion = NULL;
	}*/

	this->Release();
}
//============================
//ポリゴンの更新
//============================
void CPlayer::Update(void)
{
	if (m_bDeath == false)
	{
		//////高さを取得
		////m_fHeight = CObject3d::get

		//デバッグ表示の情報を渡す
		CDebugProc *pDebug = CManager::GetDebugProck();

		D3DXVECTOR3 pos = GetPosition();

		m_posold = pos; //前回の位置を記録

		D3DXVECTOR3 rot = GetRot();

		CInputKeyboard *pInputKeyboard;
		CInputGamePad *pInputGamepad;

		CScore *pScore;

		//スコアの取得
		pScore = CGame::GetScore();

		//キーボードの取得
		pInputKeyboard = CManager::GetInputKeyboard();

		pInputGamepad = CManager::GetGamePad();

		D3DXVECTOR3 move = GetMove();

		////基本ニュートラルに設定
		//m_pMotion->Set(0);

		////モーションの更新
		//m_pMotion->Update();

		int nState = 0;
		m_PlayerState = GetState();
		if (m_bDeath == false)
		{
			if(m_PlayerState == PLAYER_NONE || m_PlayerState == PLAYER_GURD)
			{ 
				if (m_PlayerState != PLAYER_GURD)
				{
					if (pInputKeyboard->GetPless(DIK_A) == true || pInputGamepad->GetGameStickL_X_Press(pInputGamepad->BUTTON_STICK_LX, 0) <= -1)
					{//Aキーが押された

						move.x = -1.0f;

						m_bRot = false;

						if (m_nType != MOTIONTYPE_MOVE)
						{
							SetMotionPlayer(MOTIONTYPE_MOVE);
						}
					}

					else if (pInputKeyboard->GetPless(DIK_D) == true || pInputGamepad->GetGameStickL_X_Press(pInputGamepad->BUTTON_STICK_LX, 0) >= 1)
					{//Dキーが押された
						move.x = 1.0f;

						m_bRot = true;

						if (m_nType != MOTIONTYPE_MOVE)
						{
							SetMotionPlayer(MOTIONTYPE_MOVE);
						}
					}

					//プレイヤーのパンチをしたかどうか
					else if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
					{
						/*for (int nCnt = 0; nCnt <= PLAYER_PUNCH_SPEED; nCnt++)
						{
							nPunchSpeed--;*/

						if (m_nType != MOTIONTYPE_PUNCH0)
						{
							HitEnemyPunch0(m_bDeath);
							SetMotionPlayer(MOTIONTYPE_PUNCH0);

							m_bAttack = true;
						}

						/*if (nPunchSpeed <= 0)
						{
							nPunchSpeed = PLAYER_PUNCH_SPEED;
						}*/
						/*}*/
					}
					else
					{
						m_bAttack = false;
					}
				}

				else if (m_bAttack == false)
				{
					if (m_nType != MOTIONTYPE_NEUTRAL)
					{
						SetMotionPlayer(MOTIONTYPE_NEUTRAL);
					}
				}
		
			//ガード処理
			if (pInputKeyboard->GetPless(DIK_G) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_X, 0) == true)
			{
				m_PlayerState = PLAYER_GURD;
			}
			else
			{
				m_PlayerState = PLAYER_NONE;
			}

			if (pos.y > 2000.0f)
			{
				pos.y = 2000.0f;
				move.y = 0;
			}

			else if (pos.y < 1.0f)
			{
				pos.y = 0.0f;
				move.y = 1.0f;
			}


		//壁の当たり判定
		if (pos.x + 50.0f > 620)
		{
			pos.x = 620.0f - 50.0f;
			move.x = 0;
		}

		else if (pos.x - 50.0f < -3000.0f)
		{
			pos.x = -3000.0f + 50.0f;
			move.x = 0;
		}

		////頂点情報の受け取り
		//LPDIRECT3DVERTEXBUFFER9 Buff = CBilboard::GetBuff();

		//VERTEX_3D *pVtx;    //頂点情報へのポインタ

		///*頂点バッファをロックし、頂点情報へのポインタを取得*/
		//Buff->Lock(0, 0, (void**)&pVtx, 0);

		//重力処理
		move.y -= 1.0f;

		if (move.y >= -1.0f)
		{
			m_bJump = true;

			SetJump(m_bJump);
		}

		////位置を更新
		//m_fLength += m_movefLength;

		//移動量を更新
		move.x += (0.0f - move.x) * 0.2f;

		//移動量を位置に代入
		pos += move;

		//情報をセット
		SetPosition(pos);
		SetMove(move);
		SetRot(rot);

		//ブロックの当たり判定
		HitBlock(m_bJump);

		SetJump(m_bJump);

		if (m_PlayerState != PLAYER_GURD)
		{
			//敵との当たり判定
			m_bDeath = HitPlayer(m_bDeath);
		}

		//床の判定
		if (pos.y <= 1.0f)
		{
			m_bJump = false;
			move.y = 0.0f;
			pos.y = 1.0f;

			SetJump(m_bJump);
		}

		//////影の設定
		////SetPositionShadow(m_nldxShadow, D3DXVECTOR3(pos.x, 0.0f, pos.z));

		//////頂点座標の設定
		////pVtx[0].pos = D3DXVECTOR3(- m_fWidth,+ m_fHeight, 0.0f);
		////pVtx[1].pos = D3DXVECTOR3(+ m_fWidth,+ m_fHeight, 0.0f);
		////pVtx[2].pos = D3DXVECTOR3(- m_fWidth, pos.y, 0.0f);
		////pVtx[3].pos = D3DXVECTOR3(+ m_fWidth, pos.y, 0.0f);

		////// 法線ベクトルの設定
		////pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		////pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		////pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		////pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//////頂点カラーの設定
		////pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		////pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		////pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		////pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//////テクスチャ座標の設定
		////pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		////pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		////pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		////pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//////頂点バッファをアンロックする
		////Buff->Unlock();

		///*SetBuff(Buff);*/


		////感染度が100になると死ぬ処理
		//if (pTime->Get() == 100)
		//{
		//	//パーティクルの生成
		//	CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 1, 1.0f, 1.0f);

		//	m_bDeath = true;

		//	SetDeath(m_bDeath);
		//}

#ifdef _DEBUG
		int nAttack = 0;
		if (m_bAttack == true)
		{
			nAttack = 1;
		}
		else
		{
			nAttack = 0;
		}

		int nState = 0;
		if (m_nType == MOTIONTYPE_MOVE)
		{
			nState = 1;
		}
		if (m_nType == MOTIONTYPE_PUNCH0)
		{
			nState = 2;
		}
		else
		{
			nState = 0;
		}

		pDebug->Print("プレイヤーのモーション状態 : %d\n", nState);

//プレイヤーの場所デバック情報
		pDebug->Print("プレイヤーの場所 X : %f Y : %f Z : %f\n", pos.x, pos.y, pos.z);

		//プレイヤーの場所デバック情報
		pDebug->Print("プレイヤーの移動量 X : %f Y : %f Z : %f\n", move.x, move.y, move.z);

		//プレイヤーの場所デバック情報
		pDebug->Print("プレイヤーの向き X : %f Y : %f Z : %f\n", rot.x, rot.y, rot.z);

		//プレイヤーの状態デバック情報
		pDebug->Print("プレイヤー状態 : %d\n", nState);

		//プレイヤーの攻撃してるかどうかチェック
		pDebug->Print("プレイヤーが攻撃しているかどうか : %d\n", nAttack);

		//デバッグ表示用
		int nJump;

		if (m_bJump == false)
		{
			nJump = 0;
		}
		else
		{
			nJump = 1;
		}


		//プレイヤーのジャンプデバック情報
		pDebug->Print("プレイヤーのジャンプ : %d\n", nJump);

		pDebug->Print("プレイヤーの体力 :: %d\n", m_nLife);
#endif

		SetPlayerRot(m_bRot);

		////感染度が100になると死ぬ処理
		//if (pTime->Get() == 100)
		//{
		//	//パーティクルの生成
		//	CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 1, 1.0f, 1.0f);

		//	m_bDeath = true;

		//	SetDeath(m_bDeath);
		//}

#ifdef _DEBUG
//プレイヤーの場所デバック情報
		pDebug->Print("プレイヤーミラーの移動量 X : %f Y : %f Z : %f\n", move.x, move.y, move.z);
#endif

		/*return;*/
	}
		SetState(m_PlayerState);

		D3DXVECTOR3 PosDiff; //モーションの差分を求める
		D3DXVECTOR3 RotDiff; //モーションの差分を求める

		//モーション情報挿入用
		D3DXVECTOR3 MotionPos;
		D3DXVECTOR3 MotionRot;

		//フレームカウントを加算
		m_nFrameCnt++;

		//現在のキーの数を調べる
		pDebug->Print("\n何番めのキーか : %d\n", m_nKey);

		//全モデルの更新(パーツ)の更新
		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{

			int nNextKey = m_nKey + 1;

			if (nNextKey > m_aInfo[m_nType].nNumKey)
			{
				nNextKey = 0;
			}

			//位置
			//キーの差分を求めるx
			PosDiff.x = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosX;

			//キーの差分を求めるy
			PosDiff.y = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosY;

			//キーの差分を求めるz
			PosDiff.z = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosZ;

			//向き
			//キーの差分を求めるx
			RotDiff.x = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotX;

			//キーの差分を求めるy
			RotDiff.y = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotY;

			//キーの差分を求めるz
			RotDiff.z = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotZ;

			//向きの正規化
			//目標の向きXが３.１４を超えたら
			if (RotDiff.x > D3DX_PI)
			{
				RotDiff.x -= D3DX_PI * 2;
			}
			else if (RotDiff.x < -D3DX_PI)
			{//目標の向きXが-３.１４を超えたら
				RotDiff.x += D3DX_PI * 2;
			}

			//目標の向きYが３.１４を超えたら
			if (RotDiff.y > D3DX_PI)
			{
				RotDiff.y -= D3DX_PI * 2;
			}
			else if (RotDiff.y < -D3DX_PI)
			{//目標の向きYが-３.１４を超えたら
				RotDiff.y += D3DX_PI * 2;
			}

			//目標の向きZが３.１４を超えたら
			if (RotDiff.z > D3DX_PI)
			{
				RotDiff.z -= D3DX_PI * 2;
			}
			else if (RotDiff.z < -D3DX_PI)
			{//目標の向きZが-３.１４を超えたら
				RotDiff.z += D3DX_PI * 2;
			}

			////パーツの位置や差分を計算する
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = (float)m_nKey + PosDiff.x * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = (float)m_nKey + PosDiff.y * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = (float)m_nKey + PosDiff.z * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = (float)m_nKey + RotDiff.x * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = (float)m_nKey + RotDiff.y * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = (float)m_nKey + RotDiff.z * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);

			m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame = 60;

			//パーツの位置や差分を計算する
			MotionPos.x = m_InitPartPos[nCntModel].x;/* + m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosX + PosDiff.x * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);*/
			MotionPos.y = m_InitPartPos[nCntModel].y;/* + m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosY + PosDiff.y * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);*/
			MotionPos.z = m_InitPartPos[nCntModel].z; /*+ m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosZ + PosDiff.z * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);*/
			MotionRot.x = m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotX + RotDiff.x * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			MotionRot.y = m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotY + RotDiff.y * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			MotionRot.z = m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotZ + RotDiff.z * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);

			//向きの正規化
			//目標の向きXが３.１４を超えたら
			if (MotionRot.x > D3DX_PI)
			{
				MotionRot.x -= D3DX_PI * 2;
			}
			else if (MotionRot.x < -D3DX_PI)
			{//目標の向きXが-３.１４を超えたら
				MotionRot.x += D3DX_PI * 2;
			}

			//目標の向きYが３.１４を超えたら
			if (MotionRot.y > D3DX_PI)
			{
				MotionRot.y -= D3DX_PI * 2;
			}
			else if (MotionRot.y < -D3DX_PI)
			{//目標の向きYが-３.１４を超えたら
				MotionRot.y += D3DX_PI * 2;
			}

			//目標の向きZが３.１４を超えたら
			if (MotionRot.z > D3DX_PI)
			{
				MotionRot.z -= D3DX_PI * 2;
			}
			else if (MotionRot.z < -D3DX_PI)
			{//目標の向きZが-３.１４を超えたら
				MotionRot.z += D3DX_PI * 2;
			}

			////パーツの位置・向きを設定
			//m_apModel[nCntModel]->SetPos(D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX,
			//	m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY, m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ));

			//m_apModel[nCntModel]->SetRot(D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX,
			//	m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY, m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ));

			//パーツの位置・向きを設定
			m_apModel[nCntModel]->SetPos(MotionPos);

			m_apModel[nCntModel]->SetRot(MotionRot);

			switch (m_nType)
			{
			case MOTIONTYPE_NEUTRAL:

				if (m_nKey == 0)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

					//ふたつ目のパーツ(体)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//みっつ目のパーツ(頭)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//よっつ目のパーツ(左肩)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//いつつ目のパーツ(左腕)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//むっつ目のパーツ(左手)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
				}

				else if (m_nKey == 1)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

					//ふたつ目のパーツ(体)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//みっつ目のパーツ(頭)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//よっつ目のパーツ(左肩)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//いつつ目のパーツ(左腕)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//むっつ目のパーツ(左手)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -1.5f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;

				}

				else if (m_nKey == 2)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

					//ふたつ目のパーツ(体)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//みっつ目のパーツ(頭)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//よっつ目のパーツ(左肩)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//いつつ目のパーツ(左腕)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//むっつ目のパーツ(左手)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.5f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = -0.5f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.6f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -7.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
				}

				else if (m_nKey == 3)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.0f;

					//ふたつ目のパーツ(体)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//みっつ目のパーツ(頭)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//よっつ目のパーツ(左肩)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//いつつ目のパーツ(左腕)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//むっつ目のパーツ(左手)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
				}

				if (m_nKey == 4)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

					//ふたつ目のパーツ(体)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//みっつ目のパーツ(頭)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//よっつ目のパーツ(左肩)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//いつつ目のパーツ(左腕)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//むっつ目のパーツ(左手)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
				}

				break;

		

case MOTIONTYPE_MOVE:

	if (m_nKey == 0)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

		//ふたつ目のパーツ(体)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//みっつ目のパーツ(頭)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//よっつ目のパーツ(左肩)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//いつつ目のパーツ(左腕)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//むっつ目のパーツ(左手)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
	}

	else if (m_nKey == 1)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

		//ふたつ目のパーツ(体)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//みっつ目のパーツ(頭)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//よっつ目のパーツ(左肩)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//いつつ目のパーツ(左腕)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//むっつ目のパーツ(左手)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;

	}

	else if (m_nKey == 2)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

		//ふたつ目のパーツ(体)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//みっつ目のパーツ(頭)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//よっつ目のパーツ(左肩)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//いつつ目のパーツ(左腕)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//むっつ目のパーツ(左手)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -7.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
	}

	else if (m_nKey == 3)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.0f;

		//ふたつ目のパーツ(体)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//みっつ目のパーツ(頭)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//よっつ目のパーツ(左肩)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//いつつ目のパーツ(左腕)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//むっつ目のパーツ(左手)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
	}

	if (m_nKey == 4)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

		//ふたつ目のパーツ(体)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//みっつ目のパーツ(頭)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//よっつ目のパーツ(左肩)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//いつつ目のパーツ(左腕)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//むっつ目のパーツ(左手)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
	}

	break;

	case MOTIONTYPE_PUNCH0:

		if (m_nKey == 0)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//ふたつ目のパーツ(体)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//みっつ目のパーツ(頭)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//よっつ目のパーツ(左肩)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//いつつ目のパーツ(左腕)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//むっつ目のパーツ(左手)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
		}

		else if (m_nKey == 1)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//ふたつ目のパーツ(体)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//みっつ目のパーツ(頭)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//よっつ目のパーツ(左肩)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//いつつ目のパーツ(左腕)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//むっつ目のパーツ(左手)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
		}

		else if (m_nKey == 2)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//ふたつ目のパーツ(体)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//みっつ目のパーツ(頭)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//よっつ目のパーツ(左肩)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//いつつ目のパーツ(左腕)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//むっつ目のパーツ(左手)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
		}

		else if (m_nKey == 3)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//ふたつ目のパーツ(体)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//みっつ目のパーツ(頭)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//よっつ目のパーツ(左肩)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//いつつ目のパーツ(左腕)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//むっつ目のパーツ(左手)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
		}

		else if (m_nKey == 4)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//ふたつ目のパーツ(体)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//みっつ目のパーツ(頭)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//よっつ目のパーツ(左肩)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//いつつ目のパーツ(左腕)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//むっつ目のパーツ(左手)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;

			m_bAttack = false;

		}
				break;
			}
		}

		//再生フレーム数に達したら現在のキーを1つ進める
		m_nCounter++;

		m_aInfo[m_nKey].nNumKey = 5;

		switch (m_nType)
		{
		case MOTIONTYPE_NEUTRAL:
			if (m_nFrameCnt > 60)
			{
				m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
				m_nCounter = 0;
				m_nFrameCnt = 0;
			}

			break;

		case MOTIONTYPE_MOVE:
			if (m_nFrameCnt > 50)
			{
				m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
				m_nCounter = 0;
				m_nFrameCnt = 0;
			}

			break;

		case MOTIONTYPE_PUNCH0:
			if (m_nFrameCnt > 20)
			{
				m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
				m_nCounter = 0;
				m_nFrameCnt = 0;

				if (m_nKey == 4)
				{
					SetMotionPlayer(MOTIONTYPE_NEUTRAL);
				}
			}

			break;
		}

		//m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;

		/*m_nKey = (m_nKey + 1) % m_nKey;*/
		}

	}
}
	


//============================
//ポリゴンの描画
//============================
void CPlayer::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRot();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス

	//D3DMATERIAL9 matDef;  //現在のマテリアル保存用

	//D3DXMATERIAL *pMat;	  //マテリアルデータへのポインタ

	/*CModel *pModel;

	CModel::SET_MODEL *pModelMat;

	pModel = pModel->GetModel();*/

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

	////現在のマテリアルを取得
	//pDevice->GetMaterial(&matDef);

	////マテリアルデータへのポインタを取得
	//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	/*pModelMat = pModelMat->m_pBuffMat*/

	/*pMat = (D3DXMATERIAL*)pModelMat->m_pBuffMat->GetBufferPointer();*/

	if (m_bDeath == false)
	{
		for (int nCntMat = 0; nCntMat < m_nNumModel; nCntMat++)
		{
			switch (m_PlayerState)
			{
			case PLAYER_NONE:

				//マテリアルの設定
				m_stateCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;

			case PLAYER_DAMAGE:

				//マテリアルの設定
				m_stateCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				break;

			case PLAYER_INVINCIBLE:
				m_stateCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				break;

			case PLAYER_GURD:
				m_stateCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}

			if (m_PlayerState == PLAYER_NONE || m_PlayerState == PLAYER_GURD)
			{
				//モデル(パーツ)の描画
				m_apModel[nCntMat]->Draw();
			}
			else
			{
				//モデル(パーツ)の描画
				m_apModel[nCntMat]->DrawCol(m_stateCol);
			}
		}
	}

	/*保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);*/
}

//============================
//ジャンプしてるかどうかをセットする
//============================
void CPlayer::SetJump(bool jump)
{
	m_bJump = jump;
}

//============================
//ジャンプしてるかどうかの取得
//============================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//==============================
//ブロックとの当たり判定(3D)
//==============================
void CPlayer::HitBlock(bool bJump)
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
					if (GetPosition().z + PLAYER_MIN_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z
						&& GetPosition().z + PLAYER_MIN_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z)
					{
						if (GetPosition().y + PLAYER_MIN_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y
							&& GetPosition().y + PLAYER_MIN_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y)
						{
							//左からの当たり判定
							if (GetPosition().x + PLAYER_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x
								&& m_posold.x + PLAYER_MAX_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
							{//プレイヤーとブロックが当たった 

								//位置を左側に固定
								SetPosition(D3DXVECTOR3(pObjectx->GetPosition().x + pObjectx->GetVtxMin().x - PLAYER_MAX_X, GetPosition().y, GetPosition().z));

								move.x = 0.0f;

								//ジャンプができるように
								bJump = false;
								SetJump(bJump);

							}
							
							//右からの当たり判定
							if (GetPosition().x + PLAYER_MIN_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
								&& m_posold.x + PLAYER_MIN_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x)
							{//プレイヤーとブロックが当たった 

								//プレイヤーを右側に固定
								SetPosition(D3DXVECTOR3(pObjectx->GetPosition().x + pObjectx->GetVtxMax().x - PLAYER_MIN_X, GetPosition().y, GetPosition().z));

								move.x = 0.0f;

								//ジャンプができるように
								SetJump(false);

							}
						}
					}

					if (GetPosition().x + PLAYER_MAX_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
						&& GetPosition().x + PLAYER_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
					{
						//手前からの当たり判定
						if (GetPosition().z + PLAYER_MAX_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z
							&& m_posold.z + PLAYER_MAX_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z)
						{//プレイヤーとブロックが当たった 

							//プレイヤーを奥側に固定
							SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, pObjectx->GetPosition().z + pObjectx->GetVtxMin().z - PLAYER_MAX_Z));

							move.x = 0.0f;

							//ジャンプができるように
							SetJump(false);

						}

						//奥からの当たり判定
						if (GetPosition().z + PLAYER_MIN_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z
							&& m_posold.z + PLAYER_MIN_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z)
						{//プレイヤーとブロックが当たった 

							//プレイヤーを手前側に固定
							SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, pObjectx->GetPosition().z + pObjectx->GetVtxMax().z - PLAYER_MIN_Z));

							move.x = 0.0f;

							//ジャンプができるように
							SetJump(false);

						}
					}

					if (GetPosition().x + PLAYER_MIN_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
						&& GetPosition().x + PLAYER_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
					{
						//手前からの当たり判定
						if (GetPosition().y + PLAYER_MAX_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y
							&& m_posold.y + PLAYER_MAX_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y)
						{//プレイヤーとブロックが当たった 

							//プレイヤーを奥側に固定
							SetPosition(D3DXVECTOR3(GetPosition().x, pObjectx->GetPosition().y - pObjectx->GetVtxMin().y - PLAYER_MAX_Y - 10.0f, GetPosition().z));

							move.y = 0.0f;

							//ジャンプができるように
							SetJump(false);

						}

						//奥からの当たり判定
						if (GetPosition().y + PLAYER_MIN_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y
							&& m_posold.y + PLAYER_MIN_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y)
						{//プレイヤーとブロックが当たった 

							//プレイヤーを奥側に固定
							SetPosition(D3DXVECTOR3(GetPosition().x, pObjectx->GetPosition().y + pObjectx->GetVtxMax().y + PLAYER_MIN_Y, GetPosition().z));

							move.y = 0.0f;

							//ジャンプができるように
							SetJump(false);
						}
					}
				}
			}

			//位置と移動情報をセット
			SetPosition(GetPosition());
			SetMove(move);
		}
	}
}

//==============================
//敵の当たり判定(3D)
//==============================
bool CPlayer::HitEnemyPunch0(bool bDeath)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//キーボードの取得
	pInputKeyboard = CManager::GetInputKeyboard();

	pInputGamepad = CManager::GetGamePad();

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

			////位置取得
			//D3DXVECTOR3 posBlock = pObj->GetPosition();

			if (type == TYPE_ENEMY)
			{

				pObjectx = dynamic_cast<CObjectx*>(pObj);

				if (GetPosition().x + 12.0f >= pObjectx->GetPosition().x - 15.0f
					&& GetPosition().x - 12.0f <= pObjectx->GetPosition().x + 15.0f
					&& GetPosition().y + 10.0f >= pObjectx->GetPosition().y - 20.0f
					&& GetPosition().y - 10.0f <= pObjectx->GetPosition().y + 40.0f
					&& GetPosition().z + 5.0f >= pObjectx->GetPosition().z - 5.0f
					&& GetPosition().z - 5.0f <= pObjectx->GetPosition().z + 5.0f)
				{
					CEnemy *pEnemy = CGame::GetEnemy();

					//パーティクルの生成
					CParticle::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y + 20.0f, GetPosition().z), GetRot().y, 1, 10.0f, 10.0f);

					/*CSound::PlaySound(CSound::SOUND_LABEL_SE_BLOOD);
					CSound::PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);*/

					int nEnemyLife = pEnemy->GetLife(0);

					if (nEnemyLife <= 0)
					{
						//死んだことにする
						bDeath = true;

						

						pEnemy->SetDeath(bDeath,0);

						return true;
					}
					else
					{
						pEnemy->AddDamage(1, 0);

						D3DXVECTOR3 move = GetMove();

						/*move = D3DXVECTOR3(20.0f, 10.0f, 0.0f);

						SetMove(move);*/
					}
				}
			}
		}
	}
	return false;
}

//==============================
//敵の当たり判定(3D)
//==============================
bool CPlayer::HitPlayer(bool bDeath)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//キーボードの取得
	pInputKeyboard = CManager::GetInputKeyboard();

	pInputGamepad = CManager::GetGamePad();

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

			////位置取得
			//D3DXVECTOR3 posBlock = pObj->GetPosition();

			if (type == TYPE_ENEMY)
			{

				pObjectx = dynamic_cast<CObjectx*>(pObj);

				if (GetPosition().x + 10.0f >= pObjectx->GetPosition().x - 0.0f
					&& GetPosition().x - 10.0f <= pObjectx->GetPosition().x + 0.0f
					&& GetPosition().y + 10.0f >= pObjectx->GetPosition().y - 20.0f
					&& GetPosition().y - 10.0f <= pObjectx->GetPosition().y + 40.0f
					&& GetPosition().z + 5.0f >= pObjectx->GetPosition().z - 5.0f
					&& GetPosition().z - 5.0f <= pObjectx->GetPosition().z + 5.0f)
				{
						//パーティクルの生成
						CParticle::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y + 20.0f, GetPosition().z), GetRot().y, 1, 10.0f, 10.0f);

						CSound::PlaySound(CSound::SOUND_LABEL_SE_BLOOD);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

						if (m_nLife <= 0)
						{
							//死んだことにする
							bDeath = true;

							SetDeath(bDeath);

							return true;
						}
						else
						{
							AddDamage(1);

							D3DXVECTOR3 move = GetMove();

							move = D3DXVECTOR3(20.0f, 10.0f, 0.0f);

							SetMove(move);

							if (m_nType != MOTIONTYPE_NEUTRAL)
							{
								SetMotionPlayer(MOTIONTYPE_NEUTRAL);
							}
						}
				}
			}
		}
	}
	return false;
}

////============================
//プレイヤーの死亡情報セット
////============================
void CPlayer::SetDeath(bool bDeath)
{
	m_bDeath = bDeath;
}

////============================
//プレイヤーの死亡情報を受け渡す
////============================
bool CPlayer::GetDeath(void)
{
	return m_bDeath;
}

////============================
//プレイヤーの向き情報セット
////============================
void CPlayer::SetPlayerRot(bool bRot)
{
	m_bRot = bRot;
}

////============================
//プレイヤーの向き情報受け渡す
////============================
bool CPlayer::GetPlayerRot(void)
{
	return m_bRot;
}

////============================
//プレイヤーの向き情報セット
////============================
void CPlayer::SetPlayerAim(bool bAim)
{
	m_bAim = bAim;
}

////============================
//プレイヤーの状態セット
////============================
void CPlayer::SetState(PLAYER_STATE state)
{
	m_PlayerState = state;

	switch (m_PlayerState)
	{
	case PLAYER_NONE:
		
		m_nCntState = 120;

		break;

	case PLAYER_DAMAGE:

		m_nCntState--;
	
		if (m_nCntState == 60)
		{
			m_PlayerState = PLAYER_INVINCIBLE;
		}
			
		break;

	case PLAYER_INVINCIBLE:

		m_nCntState--;

		if (m_nCntState == 0)
		{
			m_PlayerState = PLAYER_NONE;
		}
			
		break;
	}
}

////============================
//プレイヤーの向き情報受け渡す
////============================
bool CPlayer::GetPlayerAim(void)
{
	return m_bAim;
}

////============================
//プレイヤーのライフセット
////============================
void CPlayer::SetLife(int nLife)
{
	m_nLife = nLife;
}

////============================
//プレイヤーのライフ受け渡す
////============================
int CPlayer::GetLife(void)
{
	return m_nLife;
}

////============================
//プレイヤーの状態受け渡す
////============================
CPlayer::PLAYER_STATE CPlayer::GetState(void)
{
	return m_PlayerState;
}

//============================
//モーションの設定
//============================
void CPlayer::SetMotionPlayer(MOTIONTYPE nType)
{
	m_nType = nType;		 //モーションのタイプ
	m_nKey = 0;				 //現在のキーNO
	m_nCounter = 0;	 //モーションカウンター

	switch (m_nType)
	{
	case MOTIONTYPE_NEUTRAL:

		if (m_nKey == 0)
		{
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotY = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotZ = 0.0f;

			//ふたつ目のパーツ(体)
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotY = 0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotZ = 0.0f;

			//みっつ目のパーツ(頭)	 m_nKey
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotY = 0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotZ = 0.0f;

			//よっつ目のパーツ(左肩)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotZ = 0.5f;

			//いつつ目のパーツ(左腕)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotZ = -0.2f;

			//むっつ目のパーツ(左手)	m_nKey
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotX = 1.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotZ = -0.2f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotX = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotZ = 0.9f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotZ = 0.2f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotY = -0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotZ = 0.0f;
		}

		break;

	case MOTIONTYPE_MOVE:

		if (m_nKey == 0)
		{
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotY = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotZ = 0.0f;

			//ふたつ目のパーツ(体)
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotY = 0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotZ = 0.0f;
			
			//みっつ目のパーツ(頭)	 
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotY = 0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotZ = 0.0f;
			
			//よっつ目のパーツ(左肩)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotZ = 0.5f;
			
			//いつつ目のパーツ(左腕)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotZ = -0.2f;
			
			//むっつ目のパーツ(左手)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotX = 1.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotZ = -0.2f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotX = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotZ = 0.1f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotZ = -0.7f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotZ = 0.0f;
			
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotZ = 0.9f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotZ = 0.2f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotY = -0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotZ = 0.0f;
		}
		break;

	case MOTIONTYPE_PUNCH0:

		if (m_nKey == 0)
		{
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotZ = 0.0f;
		
			//ふたつ目のパーツ(体)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotZ = 0.0f;
			
			//みっつ目のパーツ(頭)	 
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotZ = 0.0f;
			
			//よっつ目のパーツ(左肩)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotZ = 0.3f;
			
			//いつつ目のパーツ(左腕)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotZ = -0.2f;
			
			//むっつ目のパーツ(左手)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotZ = 0.1f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotZ = -0.7f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotZ = 0.0f;
		
				
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotZ = 0.0f;
			
				
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosZ = 0.0f;
		
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotZ = -0.1f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotZ = 0.0f;
		}
		break;
	}
				
}

//========================
//プレイヤーのダメージ
//========================
void CPlayer::AddDamage(int nDamage)
{
	m_nLife = m_nLife - nDamage;

	m_PlayerState = PLAYER_DAMAGE;

	SetLife(m_nLife);

	SetState(m_PlayerState);
}

////============================
////位置をセットする
////============================
//void CPlayer::SetPosition(D3DXVECTOR3 pos)
//{
//	m_pos = pos;
//}
//
////============================
////移動量をセットする
////============================
//void CPlayer::SetMove(D3DXVECTOR3 move)
//{
//	m_move = move;
//}
//
////============================
////傾きをセットする
////============================
//void CPlayer::SetRot(D3DXVECTOR3 rot)
//{
//	m_rot = rot;
//}
//
////============================
////色をセットする
////============================
//void CPlayer::SetCol(D3DXCOLOR col)
//{
//	m_col = col;
//
//	//VERTEX_2D *pVtx;    //頂点情報へのポインタ
//
//	////頂点バッファをロックし、頂点情報へのポインタを取得
//	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	////頂点カラーの設定
//	//pVtx[0].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
//	//pVtx[1].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
//	//pVtx[2].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
//	//pVtx[3].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
//
//	////頂点バッファをアンロックする
//	//m_pVtxBuff->Unlock();
//}
//
////============================
////頂点情報をセットする
////============================
//void CPlayer::SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
//{
//	m_pVtxBuff = Buff;
//}
//
////============================
////体力をセットする
////============================
//void CPlayer::SetLife(int nLife)
//{
//	m_nLife = nLife;
//}
//
////============================
////位置の取得
////============================
//D3DXVECTOR3 CPlayer::GetPosition(void)
//{
//	return m_pos;
//}
//
////============================
////移動量の取得
////============================
//D3DXVECTOR3 CPlayer::GetMove(void)
//{
//	return m_move;
//}
//
////============================
////傾きの取得
////============================
//D3DXVECTOR3 CPlayer::GetRot(void)
//{
//	return m_rot;
//}
//
////============================
////色の取得
////============================
//D3DXCOLOR CPlayer::GetCol(void)
//{
//	return m_col;
//}
//
////============================
////頂点の取得
////============================
//LPDIRECT3DVERTEXBUFFER9 CPlayer::GetBuff(void)
//{
//	return m_pVtxBuff;
//}
//
////============================
////体力取得
////============================
//int CPlayer::GetLife(void)
//{
//	return m_nLife;
//}
