//============================
//
//モーション処理(motion.cpp)
//Author:早川 友貴
//
//============================
#include "main.h"
#include "model.h"
#include "renderer.h"
#include "motion.h"

//============================
//コンストラクタ
//============================
CMotion::CMotion()
{
	m_nNumAll = 0;				//数の最大数
	m_nType = 0;			//種類
	bLoop = false;							//終了するかどうか
	m_nKey = 0;								//キーの数
	m_nCounter = 0;						//モーションカウンター
	m_bFinish = false;						//終了するかどうか

	m_nNumModel = 0;						//モーションの総数
}

//============================
//デストラクタ
//============================
CMotion::~CMotion()
{

}

//============================
//生成処理
//============================
CMotion *CMotion::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CMotion *pModel;

	//オブジェクト2Dの生成
	pModel = NEW_DBG CMotion;

	//初期化処理
	pModel->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex, fWidth, fHeight);

	return pModel;
}

//====================
//モーションの初期化
//====================
HRESULT CMotion::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	////デバイスの取得
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fHeight = 0.0f;
	fWidth = 0.0f;
	nTex = 0;
	fRot = 0.0f;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================
//モーション設定
//=============================
void CMotion::Set(int nType)
{
	m_aInfo[MAX_PARTS];						//パーツの最大数
	m_nType = nType;						//種類
	bLoop = true;							//終了するかどうか
	m_nKey = 0;								//キーの数
	m_nCounter = 1;						//モーションカウンター
	m_bFinish = false;						//終了するかどうか

	m_nNumAll = 0;				//数の最大数

	m_nNumModel = 2;						//モーションの総数

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_aInfo[nCnt].nNumKey = 1;
		m_aInfo[nCnt].aKeyinfo[m_nKey].nFrame = 1;
	}

	//全モーション(パーツ)の初期設定
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		D3DXVECTOR3 pos;
					   
		D3DXVECTOR3 rot;

		//パーツの位置・向きを設定
		pos = D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fPosX,
			m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fPosY,
			m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fPosZ);

		rot = D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fRotX,
			m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fRotY,
			m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fRotZ);
	}
}

//モーションの終了処理
void CMotion::Uninit(void)
{
	
}

//モーションの更新処理
void CMotion::Update(void)
{
	float fDiff; //モーションの差分を求める

	//全モデルの更新(パーツ)の更新
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		int nNextKey = m_nKey + 1;

		if (nNextKey > m_aInfo[m_nType].nNumKey)
		{
			nNextKey = 0;
		}

		//キーの差分を求める
		fDiff = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_frotDestX
			- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_frotDestX;

		//パーツの位置や差分を計算する
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
																										  
		//パーツの位置・向きを設定
		m_ppModel[nCntModel]->SetPos(D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX,
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY, m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ));

		m_ppModel[nCntModel]->SetRot(D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX,
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY, m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ));

		switch (m_nType)
		{
		case MOTIONTYPE_NEUTRAL:

			if (m_nKey == 0)
			{
				//ひとつ目のパーツ(スカート)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ふたつ目のパーツ(体)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//みっつ目のパーツ(頭)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//よっつ目のパーツ(左肩)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//いつつ目のパーツ(左腕)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//むっつ目のパーツ(左手)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ななつ目のパーツ(右肩)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -1.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//やっつ目のパーツ(右腕)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.8f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ここのつ目のパーツ(右手)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅっこ目のパーツ(左脚)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅういっこ目のパーツ(左足)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうに目のパーツ(右脚)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうさん目のパーツ(右足)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 180)
				{
					m_nKey = 1;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 1)
			{
				//ひとつ目のパーツ(スカート)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ふたつ目のパーツ(体)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//みっつ目のパーツ(頭)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//よっつ目のパーツ(左肩)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//いつつ目のパーツ(左腕)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//むっつ目のパーツ(左手)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ななつ目のパーツ(右肩)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -1.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//やっつ目のパーツ(右腕)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.8f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ここのつ目のパーツ(右手)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅっこ目のパーツ(左脚)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅういっこ目のパーツ(左足)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうに目のパーツ(右脚)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうさん目のパーツ(右足)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 180)
				{
					m_nKey = 2;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 2)
			{
				//ひとつ目のパーツ(スカート)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ふたつ目のパーツ(体)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//みっつ目のパーツ(頭)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//よっつ目のパーツ(左肩)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//いつつ目のパーツ(左腕)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//むっつ目のパーツ(左手)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ななつ目のパーツ(右肩)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -1.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//やっつ目のパーツ(右腕)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;
						
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.8f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ここのつ目のパーツ(右手)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅっこ目のパーツ(左脚)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅういっこ目のパーツ(左足)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうに目のパーツ(右脚)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうさん目のパーツ(右足)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						 
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 180)
				{
					m_nKey = 3;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 3)
			{
				//ひとつ目のパーツ(スカート)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ふたつ目のパーツ(体)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//みっつ目のパーツ(頭)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//よっつ目のパーツ(左肩)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//いつつ目のパーツ(左腕)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//むっつ目のパーツ(左手)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ななつ目のパーツ(右肩)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -1.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//やっつ目のパーツ(右腕)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.8f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ここのつ目のパーツ(右手)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅっこ目のパーツ(左脚)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅういっこ目のパーツ(左足)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうに目のパーツ(右脚)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうさん目のパーツ(右足)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						 
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;
			}

			break;

		case MOTIONTYPE_MOVE:

			if (m_nKey == 0)
			{
				//ひとつ目のパーツ(スカート)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ふたつ目のパーツ(体)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//みっつ目のパーツ(頭)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//よっつ目のパーツ(左肩)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//いつつ目のパーツ(左腕)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 2.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//むっつ目のパーツ(左手)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ななつ目のパーツ(右肩)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//やっつ目のパーツ(右腕)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;
						
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;
				
				//ここのつ目のパーツ(右手)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅっこ目のパーツ(左脚)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅういっこ目のパーツ(左足)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうに目のパーツ(右脚)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						 
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = -1.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうさん目のパーツ(右足)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						 
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 60)
				{
					m_nKey = 1;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 1)
			{
				//ひとつ目のパーツ(スカート)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				//ふたつ目のパーツ(体)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//みっつ目のパーツ(頭)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//よっつ目のパーツ(左肩)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//いつつ目のパーツ(左腕)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 2.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//むっつ目のパーツ(左手)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ななつ目のパーツ(右肩)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//やっつ目のパーツ(右腕)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ここのつ目のパーツ(右手)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅっこ目のパーツ(左脚)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅういっこ目のパーツ(左足)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうに目のパーツ(右脚)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = -1.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうさん目のパーツ(右足)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 60)
				{
					m_nKey = 2;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 2)
			{
				//ひとつ目のパーツ(スカート)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				//ふたつ目のパーツ(体)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//みっつ目のパーツ(頭)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//よっつ目のパーツ(左肩)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//いつつ目のパーツ(左腕)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 2.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//むっつ目のパーツ(左手)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ななつ目のパーツ(右肩)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//やっつ目のパーツ(右腕)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ここのつ目のパーツ(右手)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅっこ目のパーツ(左脚)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅういっこ目のパーツ(左足)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうに目のパーツ(右脚)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = -1.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうさん目のパーツ(右足)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 60)
				{
					m_nKey = 3;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 3)
			{
				//ひとつ目のパーツ(スカート)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				//ふたつ目のパーツ(体)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//みっつ目のパーツ(頭)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//よっつ目のパーツ(左肩)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//いつつ目のパーツ(左腕)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 2.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//むっつ目のパーツ(左手)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ななつ目のパーツ(右肩)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//やっつ目のパーツ(右腕)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//ここのつ目のパーツ(右手)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅっこ目のパーツ(左脚)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅういっこ目のパーツ(左足)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうに目のパーツ(右脚)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = -1.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//じゅうさん目のパーツ(右足)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
			}
			break;
		}

	}

	//再生フレーム数に達したら現在のキーを1つ進める
	m_nCounter++;

	m_nKey = 0;

	m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
}

//==========================
//モーションの種類を取得
//==========================
int CMotion::GetType(void)
{
	return m_nType;
}

//==========================
//モーション終了するかどうか
//==========================
bool CMotion::IsFinish(void)
{
	return m_bFinish;
}

//==========================
//Info設定
//==========================
void CMotion::SetInfo(INFO info)
{
	m_aInfo[0] = info;
}
