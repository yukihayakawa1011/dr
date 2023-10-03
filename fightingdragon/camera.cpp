//============================

//カメラ処理(camera.cpp)
//Author:早川 友貴

//============================
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "debugproc.h"
#include "player.h"
#include "mode.h"

//カメラのモード(列挙)
typedef enum
{
	MODE_CAMV = 0,
	MODE_CAMR,
	MODE_CAMMAX
}MODE_CAM;

////グローバル変数
//Camera g_Camera; //カメラの情報				
//MODE_CAM g_Mode;

//========================
//コンストラクタ
//========================
CCamera::CCamera()
{
	//m_mtxView = NULL;			//マトリックスのビュー
	//m_mtxProjection;		//マトリックスのプロジェクション

	m_posV = D3DXVECTOR3(0.0f,0.0f,0.0f);				//視点のクリア
	m_posR = D3DXVECTOR3(0.0f,0.0f,0.0f);				//注視点のクリア
	m_vecU = D3DXVECTOR3(0.0f,0.0f,0.0f);				//方向ベクトルのクリア
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//傾きのクリア

	m_fAngle = 0.0f;
	m_Length = 0.0f;
}

//========================
//デストラクタ
//========================
CCamera::~CCamera()
{

}

//========================
//カメラの初期化処理
//========================
HRESULT CCamera::Init(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 pos = pPlayer->GetPosition();

	m_posV = D3DXVECTOR3(pos.x, pos.y, -500.0f);	//視点
	m_posR = D3DXVECTOR3(pos.x, pos.y, pos.z);      //注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		    //上方向ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			   //向き

	// //視点を固定する場合
	//m_fAngle = atan2f
	//(//対角線の角度
	//	m_posR.x - m_posV.x,
	//	m_posV.z - m_posR.z
	//);

	//m_Length = sqrtf
	//(//対角線の長さ
	//	(m_posR.x - m_posV.x)* (m_posR.x - m_posV.x) +
	//	(m_posV.z - m_posR.z) * ( m_posV.z - m_posR.z)
	//) * 0.5f;

	return S_OK;
}

//======================
//カメラの終了処理
//======================
void CCamera::Uninit(void)
{

}

//==========================
//カメラの更新処理
//==========================
void CCamera::Update(void)
{
	/*D3DXVECTOR3 g_ModelPos = PosModel();*/

	/*CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();*/

	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 pos = pPlayer->GetPosition();

	m_posV = D3DXVECTOR3(pos.x, pos.y + 25.0f, -500.0f); //視点
	m_posR = D3DXVECTOR3(pos.x, pos.y, pos.z);     //注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		   //上方向ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			   //向き

	////奥移動
	//if (pInputKeyboard->GetPless(DIK_UP) == true)
	//{
	//	//左移動
	//	if (pInputKeyboard->GetPless(DIK_LEFTARROW) == true)
	//	{
	//		m_posV.x += sinf(m_rot.z + 0.25f * -D3DX_PI) * 1.0f;
	//		m_posV.z += cosf(m_rot.z + 0.25f * -D3DX_PI) * 1.0f;
	//		m_posR.x += sinf(m_rot.z + 0.25f * -D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.25f * -D3DX_PI) * 1.0f;
	//	}

	//	//右移動
	//	else if (pInputKeyboard->GetPless(DIK_RIGHTARROW) == true)
	//	{
	//		m_posV.x += sinf(m_rot.z + 0.25f * D3DX_PI) * 1.0f;
	//		m_posV.z += cosf(m_rot.z + 0.25f * D3DX_PI) * 1.0f;
	//		m_posR.x += sinf(m_rot.z + 0.25f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.25f * D3DX_PI) * 1.0f;
	//	}

	//	else
	//	{
	//		m_posV.z += cosf(m_rot.z + 0.0f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.0f * D3DX_PI) * 1.0f;
	//	}
	//}

	////手前移動
	//else if (pInputKeyboard->GetPless(DIK_DOWNARROW) == true)
	//{
	//	//左移動
	//	if (pInputKeyboard->GetPless(DIK_LEFTARROW) == true)
	//	{
	//		m_posV.x += sinf(m_rot.z + 0.75f * -D3DX_PI) * 1.0f;
	//		m_posV.z += cosf(m_rot.z + 0.75f * -D3DX_PI) * 1.0f;
	//		m_posR.x += sinf(m_rot.z + 0.75f * -D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.75f * -D3DX_PI) * 1.0f;
	//	}

	//	//右移動
	//	else if (pInputKeyboard->GetPless(DIK_RIGHTARROW) == true)
	//	{

	//		m_posV.x += sinf(m_rot.z + 0.75f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.75f * D3DX_PI) * 1.0f;
	//		m_posV.x += sinf(m_rot.z + 0.75f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 0.75f * D3DX_PI) * 1.0f;
	//	}

	//	else
	//	{
	//		m_posV.z += cosf(m_rot.z + 1.0f * D3DX_PI) * 1.0f;
	//		m_posR.z += cosf(m_rot.z + 1.0f * D3DX_PI) * 1.0f;
	//	}
	//}


	////左移動
	//else if (pInputKeyboard->GetPless(DIK_LEFTARROW) == true)
	//{
	//	m_posV.x += sinf(m_rot.z + 0.5f * -D3DX_PI) * 1.0f;
	//	m_posR.z += cosf(m_rot.z + 0.5f * -D3DX_PI) * 1.0f;
	//}

	////右移動
	//else if (pInputKeyboard->GetPless(DIK_RIGHTARROW) == true)
	//{
	//	m_posV.x += sinf(m_rot.z + 0.5f * D3DX_PI) * 1.0f;
	//	m_posR.z += cosf(m_rot.z + 0.5f * D3DX_PI) * 1.0f;
	//}

	////上移動
	//if (pInputKeyboard->GetPless(DIK_N) == true)
	//{
	//	m_posV.y -= 1.0f;
	//	m_posR.y -= 1.0f;
	//}

	////下移動
	//if (pInputKeyboard->GetPless(DIK_B) == true)
	//{
	//	m_posV.y += 1.0f;
	//	m_posR.y += 1.0f;

	//}

	////注視点右移動
	//if (pInputKeyboard->GetPless(DIK_L) == true)
	//{
	//	//カメラがロックされている場合
	//	m_rot.y += 0.1f;
	//}

	////注視点左移動
	//if (pInputKeyboard->GetPless(DIK_K) == true)
	//{
	//	//カメラがロックされている場合
	//	m_rot.y -= 0.1f;
	//}

	////注視点上移動
	//if (pInputKeyboard->GetPless(DIK_P) == true)
	//{
	//	//カメラがロックされている場合
	//	m_posR.y += 1.0f;
	//}

	////注視点上移動
	//if (pInputKeyboard->GetPless(DIK_O) == true)
	//{
	//	//カメラがロックされている場合
	//	m_posR.y -= 1.0f;
	//}

	////モードを変える処理
	//if (GetKeyboardTrigger(DIK_I) == true)
	//{
	//	switch (g_Mode)
	//	{
	//	case 0:

	//		g_Mode = MODE_CAMR;

	//		break;

	//	case 1:

	//		g_Mode = MODE_CAMV;

	//		break;
	//	}
	//}


	////モード選択
	//if (g_Mode == 0)
	//{//もしモードが0なら1にする処理
	// //y軸(視点)をロック
	//	/*m_posR.x = m_posV.x + sinf(m_rot.y + D3DX_PI * m_fAngle) * m_Length;
	//	m_posR.y = 0.0f;
	//	m_posR.z = m_posV.z + cosf(m_rot.y + D3DX_PI* m_fAngle) * m_Length;*/
	//}

	//else
	//{//もしモードが1なら0にする処理
	// //y軸(注視店)をロック
		//m_posV.x = m_posR.x - sinf(m_rot.y + D3DX_PI - m_fAngle) * m_Length;
		///*g_Camera.posV.y = 0.0f;*/
		//m_posV.z = m_posR.z - cosf(m_rot.y + D3DX_PI - m_fAngle) * m_Length;

	//	g_Camera.posR = D3DXVECTOR3(g_ModelPos.x, g_ModelPos.y, g_ModelPos.z);
	//}

		//デバッグ表示の情報を渡す
		CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
		//カメラの位置をデバッグ表示
		pDebug->Print("カメラの位置 X : %f Y : %f Z : %f\n", m_posV.x, m_posV.y, m_posV.z);

		//カメラの注視点をデバッグ表示
		pDebug->Print("カメラの注視点 X : %f Y : %f Z : %f", m_posR.x, m_posR.y, m_posR.z);
#endif
}

//=======================
//カメラの設定
//=======================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成(透視投影)
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),  //視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, //画面のアスペクト比
		10.0f,  //Z値の最小値
		1000.0f); //Z値の最大値

	////プロジェクションマトリックスを作成(平行投影)
	//D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
	//	8.0f, //画面の幅
	//	1.0f, //画面の高さ
	//	10.0f,  //Z値の最小値
	//	1000.0f); //Z値の最大値

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,	  //視点
		&m_posR,   //注視点
		&m_vecU);  //上方向ベクトル

						  //ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

////==========================
////カメラの視点の情報を渡す処理
////===========================
//D3DXVECTOR3 Getposv(void)
//{
//	return g_Camera.posV;
//}
//
////============================
////カメラの注視点の情報を渡す処理
////===========================
//D3DXVECTOR3 Getposr(void)
//{
//	return g_Camera.posR;
//}
//
////============================
////カメラの視点の情報を渡す処理
////===========================
//D3DXVECTOR3 Getrot(void)
//{
//	return g_Camera.rot;
//}