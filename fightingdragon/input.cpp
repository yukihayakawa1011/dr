//============================
//
//入力処理(input.cpp)
//Author:早川 友貴
//
//============================
#include "input.h"

//
////マウスパッド
//LPDIRECTINPUTDEVICE8 pDevMouse = NULL;  //入力デバイスへのポインタ
//DIMOUSESTATE2 MouseState; //全入力情報の保管

//静的メンバ変数宣言
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//コンストラクタ
CInput::CInput()
{
	m_pInput = NULL;	//入力をクリア
	m_pDevice = NULL;	//デバイスをクリア
}

//デストラクタ
CInput::~CInput()
{

}

	
//=====================
//デバイスの初期化
//=====================
HRESULT CInput::Init (HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}

		////キーボード
		//if (FAILED(InitKeyboard(hWnd)))
		//{
		//	return E_FAIL;
		//}
	}

	////マウス
	//InitMousepad(hWnd);

	return S_OK;
}

//デバイスの終了処理
void CInput::Uninit(void)
{
	////ゲームパッド
	//UninitGamepad();

	////マウス
	//UninitMousepad();

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	//DirectInputデバイスの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//キーボードのコンストラクタ
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aKeyStateTrigger[nCnt] = 0;
		m_aKeyStateRelease[nCnt] = 0;
	}
}

//キーボードのデストラクタ
CInputKeyboard::~CInputKeyboard()
{

}

//======================
//キーボードの初期化処理
//======================
HRESULT CInputKeyboard::Init(HINSTANCE hInstans, HWND hWnd)
{
	CInput::Init(hInstans, hWnd);

	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}

//======================
//キーボード終了処理
//======================
void CInputKeyboard::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();  //キーボードのアクセス権を放棄

		m_pDevice->Release();

		m_pDevice = NULL;
	}

	//DirectInputデバイスの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//======================
//キーボード更新処理
//======================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];  //キーボードの入力情報

	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //キーボードのトリガー情報を保存
																		
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) &~aKeyState[nCntKey]; //キーボードのリリース情報を保存

			m_aKeyState[nCntKey] = aKeyState[nCntKey];  //キーボードのプレス情報を保存
		}
	}

	else
	{
		m_pDevice->Acquire();   //キーボードへのアクセス権を獲得
	}

}

//キーボードのプレス情報を取得
bool CInputKeyboard::GetPless(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//キーボードのトリガー情報を取得
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//キーボードのリリース情報を取得
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//ゲームパッドのコンストラクタ
CInputGamePad::CInputGamePad()
{
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			ZeroMemory(&m_aGamepadState[nCnt], sizeof(XINPUT_STATE)); //パッドのプレス情報
			ZeroMemory(&m_aGamepadState[nCnt], sizeof(XINPUT_STATE)); //パッドのトリガー情報
			ZeroMemory(&m_aGamepadState[nCnt], sizeof(XINPUT_STATE)); //パッドのリリース情報
		}
}		

//ゲームパッドのデストラクタ
CInputGamePad::~CInputGamePad()
{

}


//============================
//ゲームパッドの初期化
//============================
HRESULT CInputGamePad::Init(HWND hWnd)
{
	int nCnt;

	//ゲームパッド設定を有効にする
	XInputEnable(true);

	//メモリの情報の初期化
	for (nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		memset(&m_aGamepadState[nCnt], 0, sizeof(XINPUT_STATE)); //プレス情報

		memset(&m_aGamepadStateTrigger[nCnt], 0, sizeof(XINPUT_STATE)); //トリガー情報

		memset(&m_aGamepadStateRelease[nCnt], 0, sizeof(XINPUT_STATE)); //リリース情報
	}
	
	return S_OK;
}

//======================
//ゲームパッドの終了
//======================
void CInputGamePad::Uninit(void)
{
	//ゲームパッド設定を有効にする
	XInputEnable(false);
}

//======================
//ゲームパッドの更新
//======================
void CInputGamePad::Update(void)
{
	int nCnt;

	XINPUT_STATE aGamepadState[NUM_KEY_MAX];

	for (nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		//入力デバイスからデータを取得
		if (XInputGetState(nCnt, &aGamepadState[nCnt]) == ERROR_SUCCESS)
		{
			m_aGamepadStateTrigger[nCnt].Gamepad.wButtons = (m_aGamepadState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons)
				& aGamepadState[nCnt].Gamepad.wButtons; //トリガーのデータを取得

			m_aGamepadStateRelease[nCnt].Gamepad.wButtons = (m_aGamepadState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons)
				&~aGamepadState[nCnt].Gamepad.wButtons; //リリースのデータを取得

			m_aGamepadState[nCnt] = aGamepadState[nCnt];  //プレスのデータを取得
		}
	}
}

//ゲームパッドのプレス情報を取得
bool CInputGamePad::GetPless(JOYKEY nKey, int nPlayer)
{
	return(m_aGamepadState[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

//ゲームパッドのトリガー情報を取得
bool CInputGamePad::GetTrigger(JOYKEY nKey, int nPlayer)
{
	return(m_aGamepadStateTrigger[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

//ゲームパッドのリリース情報を取得
bool CInputGamePad::GetRelease(JOYKEY nKey, int nPlayer)
{
	return(m_aGamepadStateRelease[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

//左スティックの関数(X軸のプレス)
SHORT CInputGamePad::GetGameStickL_X_Press(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadState[nPlayer].Gamepad.sThumbLX;
}

//左スティックの関数(Y軸のプレス)
SHORT CInputGamePad::GetGameStickL_Y_Press(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadState[nPlayer].Gamepad.sThumbLY;
}

//左スティックの関数(X軸のトリガー)
SHORT CInputGamePad::GetGameStickL_X_Trigger(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateTrigger[nPlayer].Gamepad.sThumbLX;
}

//左スティックの関数(Y軸のトリガー)
SHORT CInputGamePad::GetGameStickL_Y_Trigger(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateTrigger[nPlayer].Gamepad.sThumbLY;
}

//左スティックの関数(X軸のリリース)
SHORT CInputGamePad::GetGameStickL_X_Release(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateRelease[nPlayer].Gamepad.sThumbLX;
}

//左スティックの関数(Y軸のリリース)
SHORT CInputGamePad::GetGameStickL_Y_Release(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateRelease[nPlayer].Gamepad.sThumbLY;
}

//右スティックの関数(X軸のプレス)
SHORT CInputGamePad::GetGameStickR_X_Press(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadState[nPlayer].Gamepad.sThumbRX;
}
//右スティックの関数(Y軸のプレス)
SHORT CInputGamePad::GetGameStickR_Y_Press(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadState[nPlayer].Gamepad.sThumbRY;
}

//右スティックの関数(X軸のトリガー)
SHORT CInputGamePad::GetGameStickR_X_Trigger(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateTrigger[nPlayer].Gamepad.sThumbRX;
}

//右スティックの関数(Y軸のトリガー)
SHORT CInputGamePad::GetGameStickR_Y_Trigger(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateTrigger[nPlayer].Gamepad.sThumbRY;
}

//右スティックの関数(X軸のリリース)
SHORT CInputGamePad::GetGameStickR_X_Release(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateRelease[nPlayer].Gamepad.sThumbRX;
}

//右スティックの関数(Y軸のリリース)
SHORT CInputGamePad::GetGameStickR_Y_Release(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateRelease[nPlayer].Gamepad.sThumbRY;
}

////======================
////マウスの初期化処理
////======================
//HRESULT InitMousepad(HWND hWnd)
//{
//
//	//入力デバイス(マウス)の生成
//	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &pDevMouse, NULL)))
//	{
//		return E_FAIL;
//	}
//
//	//データフォーマットを設定
//	if (FAILED(pDevMouse->SetDataFormat(&c_dfDIMouse2)))
//	{
//		return E_FAIL;
//	}
//
//	//協調モードを設定
//	if (FAILED(pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
//	{
//		return E_FAIL;
//	}
//
//	//キーボードへのアクセス権を獲得
//	pDevMouse->Acquire();
//
//	return S_OK;
//}







////======================
////マウス終了処理
////======================
//void UninitMousepad(void)
//{
//	//入力デバイス(キーボード)の破棄
//	if (pDevMouse != NULL)
//	{
//		pDevMouse->Unacquire();  //キーボードのアクセス権を放棄
//
//		pDevMouse->Release();
//
//		pDevMouse = NULL;
//	}
//}
//
//
//

//
////======================
////マウス更新処理
////======================
//void UpdateMousepad(void)
//{
//	DIMOUSESTATE2 mouse;  //マウスの入力情報
//
//	int nCntKey;
//
//	//入力デバイスからデータを取得
//	if (SUCCEEDED(pDevMouse->GetDeviceState(sizeof(mouse), &mouse)))
//	{
//		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
//		{
//			//MouseState = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //マウスのトリガー情報を保存
//
//			//g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) &~aKeyState[nCntKey]; //マウスのリリース情報を保存
//
//			MouseState = mouse;  //マウスのプレス情報を保存
//		}
//	}
//
//	else
//	{
//		pDevMouse->Acquire();   //マウスへのアクセス権を獲得
//	}
//
//}

//
////マウスのデバック表示
//void GetMouseDebuc(void)
//{
//	//ローカル変数宣言
//	char aStr[256];
//
//	//フォントの取得
//	LPD3DXFONT pFont = GetFont();
//
//	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
//	{
//		//範囲の指定
//		RECT rect = { 0,30 + nCnt * 30,SCREEN_WINDTH,SCREEN_HEIGHT };
//
//		//文字列に代入
//		if (nCnt < NUM_KEY_MAX)
//		{
//			sprintf(&aStr[0], "rgbButtons[%d] : %d", nCnt, MouseState.rgbButtons[nCnt]);
//		}
//
//		//テキストの描画
//		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//
//	}
//}