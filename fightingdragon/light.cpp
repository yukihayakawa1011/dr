//============================
//
//ライト処理(light.cpp)
//Author:早川 友貴
//
//============================
#include "manager.h"
#include "light.h"
#include "renderer.h"
#include "debugproc.h"

//========================
//コンストラクタ
//========================
CLight::CLight()
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));

		m_VecDir[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//========================
//デストラクタ
//========================
CLight::~CLight()
{

}

//========================
//ライトの初期化処理
//========================
HRESULT CLight::Init(void)
{
	int nCnt;

	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		if (nCnt == 0)
		{
			//ライトの拡散光を設定
			m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を指定
			m_VecDir[nCnt] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
		}

		if (nCnt == 1)
		{
			//ライトの拡散光を設定
			m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を指定
			m_VecDir[nCnt] = D3DXVECTOR3(-0.2f, 0.9f, -0.4f);
		}

		if (nCnt == 2)
		{
			//ライトの拡散光を設定
			m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を指定
			m_VecDir[nCnt] = D3DXVECTOR3(0.9f, 0.1f, 0.4f);
		}

		D3DXVec3Normalize(&m_VecDir[nCnt], &m_VecDir[nCnt]); //ベクトルを正規化する

		m_aLight[nCnt].Direction = m_VecDir[nCnt];

		//ライトを設定する
		pDevice->SetLight(nCnt, &m_aLight[nCnt]);

		//ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//======================
//ライトの終了処理
//======================
void CLight::Uninit(void)
{

}

//==========================
//ライトの更新処理
//==========================
void CLight::Update(void)
{
	//デバッグ表示の情報を渡す
	CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("\nライトの向き0 X : %f Y : %f Z : %f\n", m_VecDir[0].x, m_VecDir[0].y, m_VecDir[0].z);
	pDebug->Print("ライトの向き1 X : %f Y : %f Z : %f\n", m_VecDir[1].x, m_VecDir[1].y, m_VecDir[1].z);
	pDebug->Print("ライトの向き2 X : %f Y : %f Z : %f\n", m_VecDir[2].x, m_VecDir[2].y, m_VecDir[2].z);
#endif

}