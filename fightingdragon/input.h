//============================
//
//入力処理(input.h)
//Author:早川 友貴
//
//============================

#ifndef _INPUT_H_   //このマクロ定義がされていなかったら
#define _INPUT_H_  //2重インクルード防止のマクロを定義する

#include "main.h"
#include "Xinput.h"
#pragma comment(lib,"xinput.lib")

//マクロ定義
#define NUM_KEY_MAX (256)  //キーの最大数
#define MAX_PLAYER  (4) //キーの最大数


class CInput
{
public:
	CInput();
	virtual~CInput();

	virtual HRESULT Init(HINSTANCE hInstans, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstans, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPless(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];				//キーボード用
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];		//トリガー用
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];		//リリース用
};

class CInputGamePad : public CInput
{
public:

	//コントローラーのボタンを定義
	typedef enum
	{
		BUTTON_UP = 0, //上十字ボタン
		BUTTON_DOWN,   //下十字ボタン
		BUTTON_LEFT,   //左十字ボタン
		BUTTON_RIGHT,  //右十字ボタン
		BUTTON_START,  //スタートボタン
		BUTTON_BACK,   //バックボタン
		BUTTON_LEFT_STICK_PUSH, //左スティック押し込み
		BUTTON_RIGHT_STICK_PUSH, //右スティック押し込み
		BUTTON_LB,  //LBボタン
		BUTTON_RB,  //RBボタン
		BUTTON_LT,  //LTボタン
		BUTTON_RT,  //RTボタン
		BUTTON_A,   //Aボタン
		BUTTON_B,   //Bボタン
		BUTTON_X,   //Xボタン
		BUTTON_Y,   //Yボタン
		BUTTON_STICK_LX,	//左スティックのX
		BUTTON_STICK_LY,	//左スティックのY
		BUTTON_STICK_RX,	//右スティックのX
		BUTTON_STICK_RY,	//右スティックのY
		BUTTON_MAX
	}JOYKEY;

	CInputGamePad();
	~CInputGamePad();

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPless(JOYKEY nKey, int nPlayer);
	bool GetTrigger(JOYKEY nKey, int nPlayer);
	bool GetRelease(JOYKEY nKey, int nPlayer);

	//左スティックの関数
	SHORT GetGameStickL_X_Press(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickL_Y_Press(JOYKEY nKey, int nPlayer);

	SHORT GetGameStickL_X_Trigger(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickL_Y_Trigger(JOYKEY nKey, int nPlayer);

	SHORT GetGameStickL_X_Release(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickL_Y_Release(JOYKEY nKey, int nPlayer);

	//右スティックの関数
	SHORT GetGameStickR_X_Press(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickR_Y_Press(JOYKEY nKey, int nPlayer);

	SHORT GetGameStickR_X_Trigger(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickR_Y_Trigger(JOYKEY nKey, int nPlayer);

	SHORT GetGameStickR_X_Release(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickR_Y_Release(JOYKEY nKey, int nPlayer);

private:

	//ゲームパッド
	XINPUT_STATE m_aGamepadState[NUM_KEY_MAX]; //パッドのプレス情報
	XINPUT_STATE m_aGamepadStateTrigger[NUM_KEY_MAX]; //パッドのトリガー情報
	XINPUT_STATE m_aGamepadStateRelease[NUM_KEY_MAX]; //パッドのリリース情報
};

//
////デバイス統括
//HRESULT InitDevice(HINSTANCE hInstance, HWND hWnd);
//void UninitDevice(void);
//void UpdateDevice(void);
//
//
////プロトタイプ宣言(キーボード・ゲームパッド・マウスパッド)
////キーボードの関数
//HRESULT InitKeyboard(HWND hWnd);
//void UninitKeyboard(void);
//void UpdateKeyboard(void);
//void UninitGamepad(void);
//void UpdateGamepad(void);
//bool GetKeyboardPress(int nKey);
//bool GetKeyboardTrigger(int nKey);
//bool GetKeyboardRelease(int nKey);
//
////ゲームパッドの関数
//HRESULT InitGamepad(HWND hWnd);
//bool GetGamepadPress(JOYKEY nKey, int nPlayer);
//bool GetGamepadTrigger(JOYKEY nKey, int nPlayer);
//bool GetGamepadRelease(JOYKEY nKey, int nPlayer);
//
////マウスパッドの関数
//HRESULT InitMousepad(HWND hWnd);
//void UninitMousepad(void);
//void UpdateMousepad(void);
////void DrawMousepad(void);
//void GetMouseDebuc(void);
//

#endif 


