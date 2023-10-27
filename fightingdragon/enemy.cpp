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

//============================
//コンストラクタ
//============================
CEnemy::CEnemy()
{
	m_Enemystate = ENEMYSTATE_NONE;					//敵のステートをクリアする

	m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//敵の色をクリアする

	m_nCntState = 0;									//敵の数をクリアする

	
	m_bDeath = false;									//敵が死亡したかどうかをクリアする


	m_nCnt = 0;

	m_nLife[0] = 0;

	memset(&m_InitPartPos[0], NULL, sizeof(D3DXVECTOR3));

	memset(&m_aInfo[0], NULL, sizeof(m_aInfo));

	m_nFrameCnt = 0;

	m_bFinish = false;						//終了するかどうか
	m_bAttack = false;						//攻撃状態に入っているかどうかをクリア

	m_nNumAll = 0;				//数の最大数
	m_nType = 0;			//種類
	bLoop = false;							//終了するかどうか
	m_nKey = 0;								//キーの数
	m_nCounter = 0;						//モーションカウンター
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

	m_nKey = 5;								//キーの数

	m_nFrameCnt = 0;

	SetPosition(pos);

	nTex = 0;


	m_bAttack = false;				//攻撃状態かどうかを初期化


	for (int nCntInfo = 0; nCntInfo < MAX_PART; nCntInfo++)
	{
		m_aInfo[nCntInfo].nNumKey = 0;

		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			m_aInfo[nCntInfo].aKeyinfo[nCnt].nFrame = 120;
		}
	}

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
		m_Enemystate = ENEMYSTATE_NONE;

		SetState(m_Enemystate);

		m_nCntState = 30;

		m_bDeath = false;

		m_nLife[0] = 10;

	//全てのパーツ数を初期化
	m_nNumModel = MAX_MODEL;

	//モデル生成
	m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 32.0f, 0.0f), fRot, 0, fWidth, fHeight,0);
	m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, -1.0f, 0.0f), fRot, 1, fWidth, fHeight,0);
	m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 18.0f, 0.0f), fRot, 2, fWidth, fHeight,0);
	m_apModel[3] = CModel::Create(D3DXVECTOR3(4.0f, -10.0f, 0.0f), fRot, 3, fWidth, fHeight,0);
	m_apModel[4] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 0.0f), fRot, 4, fWidth, fHeight,0);
	m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 5, fWidth, fHeight,0);
	m_apModel[6] = CModel::Create(D3DXVECTOR3(-4.0f, -10.0f, 0.0f), fRot, 6, fWidth, fHeight, 0);
	m_apModel[7] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 1.0f), fRot, 7, fWidth, fHeight,0);
	m_apModel[8] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 8, fWidth, fHeight,0);
	m_apModel[9] = CModel::Create(D3DXVECTOR3(5.0f, 15.0f, -1.0f), fRot, 9, fWidth, fHeight,0);
	m_apModel[10] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), fRot, 10, fWidth, fHeight,0);
	m_apModel[11] = CModel::Create(D3DXVECTOR3(5.7f, 0.0f, 0.0f), fRot, 11, fWidth, fHeight,0);
	m_apModel[12] = CModel::Create(D3DXVECTOR3(6.0f, 0.0f, 0.0f), fRot, 12, fWidth, fHeight,0);
	m_apModel[13] = CModel::Create(D3DXVECTOR3(-5.0f, 15.0f, -1.0f), fRot, 13, fWidth, fHeight, 0);
	m_apModel[14] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.5f), fRot, 14, fWidth, fHeight, 0);
	m_apModel[15] = CModel::Create(D3DXVECTOR3(-5.7f, 0.0f, -0.5f), fRot, 15, fWidth, fHeight, 0);
	m_apModel[16] = CModel::Create(D3DXVECTOR3(-6.0f, 0.0f, 0.0f), fRot, 16, fWidth, fHeight, 0);

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
	
	//種類を設定
	SetType(CObject::TYPE_ENEMY);

	m_nCnt = nTex;

	SetCnt(m_nCnt);

	m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	SetCol(m_ColEnemy);
	
	D3DXVECTOR3 move = GetMove();

	//移動量の初期化
	move.x = 0.0f;

	//移動量のセット
	SetMove(move);

	SetDeath(m_bDeath,nTex);

	SetLife(m_nLife[0], 0);

	SetMotionEnemy(MOTIONTYPE_NEUTRAL);

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

	//敵の行動を決める処理
	int nMove;

	
		//鍵の位置をランダムにする処理
		nMove = rand() % 70 + 1;

	//オブジェクト3dのデータをもらう
	/*CObject3d *pobject3d = CGame::GetObject3d();
	bool bShowenemy = pobject3d->GetShowEnemy();*/

	D3DXVECTOR3 pos = GetPosition();

	m_posold = pos; //前回の位置を記録

	D3DXVECTOR3 move = GetMove();

	D3DXVECTOR3 rot = GetRot();

	CPlayer *pPlayer = CGame::GetPlayer();

	//重力処理
	move.y -= 1.0f;

	if (move.y >= -1.0f)
	{

	}

	if (m_Enemystate != ENEMYSTATE_DAMAGE)
	{
		if (pos.z <= 0.0f)
		{//敵の位置(Z)が0だったら
			/*bShowenemy = true;

			pobject3d->SetShowEnemy(bShowenemy);*/
			if (nMove < 63 && nMove > 60)
			{
				move.x = 1.0f;

				if (m_nType != MOTIONTYPE_MOVE)
				{
					SetMotionEnemy(MOTIONTYPE_MOVE);
				}
			}
			if (nMove < 65 && nMove > 63)
			{
				move.x = -1.0f;

				if (m_nType != MOTIONTYPE_MOVE)
				{
					SetMotionEnemy(MOTIONTYPE_MOVE);
				}
			}
			if (nMove < 68 && nMove > 66)
			{
				m_bAttack = true;

				m_Enemystate = ENEMYSTATE_ATTACK;

				if (m_nType != MOTIONTYPE_PUNCH)
				{
					SetMotionEnemy(MOTIONTYPE_PUNCH);
				}
			}
			/*if (nMove < 68 && nMove > 66)
			{
				m_bAttack = true;

				m_Enemystate = ENEMYSTATE_ATTACK;

				if (m_nType != MOTIONTYPE_KICK)
				{
					SetMotionEnemy(MOTIONTYPE_KICK);
				}
			}*/
			if (nMove < 70 && nMove > 68)
			{
				m_Enemystate = ENEMYSTATE_GURD;

				if (m_nType != MOTIONTYPE_PUNCH)
				{
					SetMotionEnemy(MOTIONTYPE_PUNCH);
				}
			}
			else if (nMove < 60)
			{
				if (m_nType != MOTIONTYPE_NEUTRAL)
				{
					SetMotionEnemy(MOTIONTYPE_NEUTRAL);
				}
			}

			m_Enemystate = ENEMYSTATE_ATTACK;

			SetState(m_Enemystate);

			if (move.x <= 0.0f)
			{
				rot.y = D3DX_PI * -0.5f;
			}
			else
			{
				rot.y = D3DX_PI * -0.5f;
			}

			//床の判定
			if (pos.y <= 1.0f)
			{
				m_bJump = false;
				move.y = 0.0f;
				pos.y = 1.0f;

				SetJump(m_bJump);
			}

			if (pos.x >= pPlayer->GetPosition().x)
			{
				move.x = -2.0f;
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
	}
	else if(m_Enemystate == ENEMYSTATE_DAMAGE)
	{
		m_nCntState--;

		move = GetMove();

		pos += move;

		SetPosition(pos);

		SetMotionEnemy(MOTIONTYPE_DAMAGE);

		if (m_nCntState == 0)
		{
			m_nCntState = 30;

			SetState(ENEMYSTATE_NONE);


		}
	}

	//
	//{//敵の位置(Z)が0以外だったら
	//	if (m_pPlayer->GetPosition().x - 100.0f <= pos.x + 200.0f
	//		&&m_pPlayer->GetPosition().x + 10.0f >= pos.x
	//		&& m_pPlayer->GetPosition().y + 5.0f >= pos.y)
	//	{
	//		/*bShowenemy = false;*/

	//	/*	pobject3d->SetShowEnemy(bShowenemy);*/

	//		move.z = -8.0f;

	//		pos.z += move.z;

	//		if (pos.z <= 0.0f)
	//		{
	//			pos.z = 0.0f;
	//		}

	//		if (pos.z >= 8.0f && pos.z <= 11.0f)
	//		{
	//			CSound::PlaySound(CSound::SOUND_LABEL_SE_WINDOW);
	//			CSound::PlaySound(CSound::SOUND_LABEL_SE_SCREAM);

	//			CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 2, 20.0f, 20.0f);

	//			/*SetState(ENEMYSTATE_NONE);*/
	//		}

	//		SetPosition(pos);

	//	}

	//	if (m_pPlayer->GetPosition().x + 50.0f <= pos.x
	//		&&m_pPlayer->GetPosition().x - 10.0f >= pos.x - 200.0f
	//		&& m_pPlayer->GetPosition().y + 5.0f >= pos.y)
	//	{
	//		/*bShowenemy = false;*/

	//		/*pobject3d->SetShowEnemy(bShowenemy);*/

	//		move.z = -8.0f;

	//		pos.z += move.z;

	//		if (pos.z <= 0.0f)
	//		{
	//			pos.z = 0.0f;
	//		}

	//		if (pos.z >= 8.0f && pos.z <= 11.0f)
	//		{
	//			CSound::PlaySound(CSound::SOUND_LABEL_SE_WINDOW);
	//			CSound::PlaySound(CSound::SOUND_LABEL_SE_SCREAM);

	//			CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 2, 20.0f, 20.0f);

	//			/*SetState(ENEMYSTATE_NONE);*/

	//			SetMove(D3DXVECTOR3(-3.0f, move.y, 0.0f));
	//		}

	//		SetPosition(pos);
	//	}
	//}

	/*if (bShowenemy == false)
	{
		m_Enemystate = ENEMYSTATE_NONE;

		SetState(m_Enemystate);
	}*/

	/*if (bShowenemy == true && pos.z > 0.0f)
	{
		m_Enemystate = ENEMYSTATE_STANBY;

		SetState(m_Enemystate);
	}*/

	SetRot(rot);

	//デバッグ表示の情報を渡す
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("敵の総数 : %d\n", m_nEnemy);

	//敵の場所デバック情報
	pDebug->Print("敵の場所 X : %f Y : %f Z : %f\n", pos.x, pos.y, pos.z);

	pDebug->Print("敵の移動量 X : %f Y : %f Z : %f\n", move.x, move.y, move.z);

	pDebug->Print("敵0の体力 : %d\n", m_nLife[0]);
	pDebug->Print("敵1の体力 : %d\n", m_nLife[1]);
	pDebug->Print("敵2の体力 : %d\n", m_nLife[2]);
#endif


	////感染度が100になると死ぬ処理
	//if (pTime->Get() == 100)
	//{
	//	//パーティクルの生成
	//	CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 1, 1.0f, 1.0f);

	//	m_bDeath = true;

	//	SetDeath(m_bDeath);
	//}
	/*return;*/

	D3DXVECTOR3 PosDiff; //モーションの差分を求める
	D3DXVECTOR3 RotDiff; //モーションの差分を求める

						 //モーション情報挿入用
	D3DXVECTOR3 MotionPos;
	D3DXVECTOR3 MotionRot;

	//フレームカウントを加算
	m_nFrameCnt++;

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

		case MOTIONTYPE_PUNCH:

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

			else if (m_nKey == 4)
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

				m_bAttack = false;

			}
			break;

			case MOTIONTYPE_KICK:
				//モーションキック
				if (m_nKey == 0)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.8f;

					//ふたつ目のパーツ(体)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = -0.2f;

					//みっつ目のパーツ(頭)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//よっつ目のパーツ(左肩)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

					//いつつ目のパーツ(左腕)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.3f;

					//むっつ目のパーツ(左手)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = -0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = -1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = 0.0f;

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
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.8f;

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

				else if (m_nKey == 1)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.8f;

					//ふたつ目のパーツ(体)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = -0.2f;

					//みっつ目のパーツ(頭)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//よっつ目のパーツ(左肩)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

					//いつつ目のパーツ(左腕)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.3f;

					//むっつ目のパーツ(左手)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = -0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = -1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = 0.0f;

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
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.8f;

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

				else if (m_nKey == 2)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.8f;

					//ふたつ目のパーツ(体)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = -0.2f;

					//みっつ目のパーツ(頭)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//よっつ目のパーツ(左肩)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

					//いつつ目のパーツ(左腕)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.3f;

					//むっつ目のパーツ(左手)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = -0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = -1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = 0.0f;

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
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.8f;

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

				else if (m_nKey == 3)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.8f;

					//ふたつ目のパーツ(体)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = -0.2f;

					//みっつ目のパーツ(頭)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//よっつ目のパーツ(左肩)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

					//いつつ目のパーツ(左腕)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.3f;

					//むっつ目のパーツ(左手)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = -0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = -1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = 0.0f;

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
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.8f;

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

				else if (m_nKey == 4)
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

					m_bAttack = false;
				}
				break;

				case MOTIONTYPE_DAMAGE:
					//モーション移動
					if (m_nKey == 0)
					{
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.2f;

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

						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.2f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.1f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = -0.3f;

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

						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.5f;
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
					break;
		}
	}

	//再生フレーム数に達したら現在のキーを1つ進める
	m_nCounter++;

	m_aInfo[m_nKey].nNumKey = 1;

	
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
		if (m_nFrameCnt > 60)
		{
			m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
			m_nCounter = 0;
			m_nFrameCnt = 0;
		}

		break;

	case MOTIONTYPE_PUNCH:
		if (m_nFrameCnt > 60)
		{
			m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
			m_nCounter = 0;
			m_nFrameCnt = 0;

			if (m_nKey == 1)
			{
				SetMotionEnemy(MOTIONTYPE_NEUTRAL);
			}
		}

		break;

	case MOTIONTYPE_KICK:
		if (m_nFrameCnt > 60)
		{
			m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
			m_nCounter = 0;
			m_nFrameCnt = 0;

			if (m_nKey == 1)
			{
				SetMotionEnemy(MOTIONTYPE_NEUTRAL);
			}
		}
		break;

	case MOTIONTYPE_DAMAGE:
		if (m_nFrameCnt > 60)
		{
			m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
			m_nCounter = 0;
			m_nFrameCnt = 0;
		}

		if (m_nKey == 1)
		{
			SetMotionEnemy(MOTIONTYPE_NEUTRAL);
		}

		break;
	}

	//m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;

	/*m_nKey = (m_nKey + 1) % m_nKey;*/
		}

//============================
//ポリゴンの描画
//============================
void CEnemy::Draw(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
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

		if (m_bDeath == false)
		{
			for (int nCntMat = 0; nCntMat < m_nNumModel; nCntMat++)
			{
				if (m_Enemystate == ENEMYSTATE_NONE)
				{
					m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

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

				////現在のマテリアルを取得
				//pDevice->GetMaterial(&matDef);

				////マテリアルデータへのポインタを取得
				//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

			}
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

	SetMotionEnemy(MOTIONTYPE_DAMAGE);

	//デバッグ表示の情報を渡す
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProck();
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
	case ENEMYSTATE_NONE:

		

		break;

	case ENEMYSTATE_ATTACK:

		break;

	case ENEMYSTATE_DAMAGE:

			break;
		

	case ENEMYSTATE_GURD:

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

//============================
//死亡してるかどうかの取得
//============================
bool CEnemy::GetDeath(void)
{
	return m_bDeath;
}

//============================
//死亡してるかどうかをセットする
//============================
void CEnemy::SetDeath(bool bDeath,int nEnemy)
{
	m_bDeath = bDeath;
}

//============================
//敵が何番めかの取得
//============================
int CEnemy::GetCnt(void)
{
	return m_nCnt;
}

//============================
//敵が何番めかセットする
//============================
void CEnemy::SetCnt(int nCnt)
{
	m_nCnt = nCnt;
}

//============================
//モーションの設定
//============================
void CEnemy::SetMotionEnemy(MOTIONTYPE nType)
{
	m_nType = nType;		 //モーションのタイプ
	m_nKey = 0;				 //現在のキーNO
	m_nCounter = 0;	 //モーションカウンター

	switch (m_nType)
	{
	case MOTIONTYPE_NEUTRAL:

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

		break;

	case MOTIONTYPE_MOVE:
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
	
		break;

	case MOTIONTYPE_PUNCH:
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
		
		break;

		case MOTIONTYPE_DAMAGE:
			//モーションダメージ
		
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosX = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosY = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosZ = 0.0f;
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotX = -0.1f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotY = -1.3f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotZ = -0.2f;
										
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
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotX = 0.2f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotY = 0.1f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotZ = -0.3f;
										  
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
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotX = 1.5f;
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
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotY = -0.7f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotZ = 0.0f;
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosX = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosY = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosZ = 0.0f;
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotX = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotY = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotZ = 0.0f;
			
			break;
	}

}