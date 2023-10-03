//============================
//
//オブジェクト処理(object.cpp)
//Author:早川 友貴
//
//============================
#include "object.h"
#include "camera.h"
#include "debugproc.h"
#include "mode.h"
#include "pause.h"

//静的変数宣言
CObject *CObject::m_apObject[MAX_OBJECT];
int  CObject::m_nNumAll;
//============================
//コンストラクタ
//============================
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject <= MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			m_apObject[nCntObject] = this;		//自分自身を大美優
			m_nId = nCntObject;					//自分自身のIDを保存
			m_nNumAll++;						//総数をカウントアップ
			break;
		}
	}

	m_Type = TYPE_NONE;							//タイプをクリア

}

//============================
//コンストラクタ
//============================
CObject::CObject(TYPE type)
{
	SetType(type);
}

//============================
//デストラクタ
//============================
CObject::~CObject()
{

}

//============================
//全てのオブジェクトの破棄
//============================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//============================
//全てのオブジェクトの更新
//============================
void CObject::UpdateAll(void)
{
	/*CPause *pause;
	pause = NEW_DBG CPause;
	bool bPause = pause->GetPause();

	if (bPause == false)
	{*/
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntObject] != NULL)
			{
				m_apObject[nCntObject]->Update();
			}
		}
	/*}*/
	/*else
	{
		return;
	}*/
	
	//デバッグ表示の情報を渡す
	CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("オブジェクトの総数 : %d\n", m_nNumAll);
#endif
}

//============================
//全てのオブジェクトの描画
//============================
void CObject::DrawAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->Draw();
		}
	}
}

//============================
//オブジェクトの破棄
//============================
void CObject::Release(void)
{
	int nCnt = m_nId;

	if (m_apObject[nCnt] != NULL)
	{
		delete m_apObject[nCnt];

		m_apObject[nCnt] = NULL;

		m_nNumAll--;		//総数をカウントダウン
	}
}

//==============================
//種類の設定
//==============================
void CObject::SetType(TYPE type)
{
	m_Type = type;
}

//==============================
//種類の取得
//==============================
CObject::TYPE CObject::GetType(void)
{
	return m_Type;
}

//何番目のオブジェクトか指定
CObject *CObject:: GetObject(int nIdx)
{
	return m_apObject[nIdx];
}


