//============================
//
//���͏���(input.h)
//Author:���� �F�M
//
//============================

#ifndef _INPUT_H_   //���̃}�N����`������Ă��Ȃ�������
#define _INPUT_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "Xinput.h"
#pragma comment(lib,"xinput.lib")

//�}�N����`
#define NUM_KEY_MAX (256)  //�L�[�̍ő吔
#define MAX_PLAYER  (4) //�L�[�̍ő吔


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
	BYTE m_aKeyState[NUM_KEY_MAX];				//�L�[�{�[�h�p
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];		//�g���K�[�p
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];		//�����[�X�p
};

class CInputGamePad : public CInput
{
public:

	//�R���g���[���[�̃{�^�����`
	typedef enum
	{
		BUTTON_UP = 0, //��\���{�^��
		BUTTON_DOWN,   //���\���{�^��
		BUTTON_LEFT,   //���\���{�^��
		BUTTON_RIGHT,  //�E�\���{�^��
		BUTTON_START,  //�X�^�[�g�{�^��
		BUTTON_BACK,   //�o�b�N�{�^��
		BUTTON_LEFT_STICK_PUSH, //���X�e�B�b�N��������
		BUTTON_RIGHT_STICK_PUSH, //�E�X�e�B�b�N��������
		BUTTON_LB,  //LB�{�^��
		BUTTON_RB,  //RB�{�^��
		BUTTON_LT,  //LT�{�^��
		BUTTON_RT,  //RT�{�^��
		BUTTON_A,   //A�{�^��
		BUTTON_B,   //B�{�^��
		BUTTON_X,   //X�{�^��
		BUTTON_Y,   //Y�{�^��
		BUTTON_STICK_LX,	//���X�e�B�b�N��X
		BUTTON_STICK_LY,	//���X�e�B�b�N��Y
		BUTTON_STICK_RX,	//�E�X�e�B�b�N��X
		BUTTON_STICK_RY,	//�E�X�e�B�b�N��Y
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

	//���X�e�B�b�N�̊֐�
	SHORT GetGameStickL_X_Press(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickL_Y_Press(JOYKEY nKey, int nPlayer);

	SHORT GetGameStickL_X_Trigger(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickL_Y_Trigger(JOYKEY nKey, int nPlayer);

	SHORT GetGameStickL_X_Release(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickL_Y_Release(JOYKEY nKey, int nPlayer);

	//�E�X�e�B�b�N�̊֐�
	SHORT GetGameStickR_X_Press(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickR_Y_Press(JOYKEY nKey, int nPlayer);

	SHORT GetGameStickR_X_Trigger(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickR_Y_Trigger(JOYKEY nKey, int nPlayer);

	SHORT GetGameStickR_X_Release(JOYKEY nKey, int nPlayer);
	SHORT GetGameStickR_Y_Release(JOYKEY nKey, int nPlayer);

private:

	//�Q�[���p�b�h
	XINPUT_STATE m_aGamepadState[NUM_KEY_MAX]; //�p�b�h�̃v���X���
	XINPUT_STATE m_aGamepadStateTrigger[NUM_KEY_MAX]; //�p�b�h�̃g���K�[���
	XINPUT_STATE m_aGamepadStateRelease[NUM_KEY_MAX]; //�p�b�h�̃����[�X���
};

//
////�f�o�C�X����
//HRESULT InitDevice(HINSTANCE hInstance, HWND hWnd);
//void UninitDevice(void);
//void UpdateDevice(void);
//
//
////�v���g�^�C�v�錾(�L�[�{�[�h�E�Q�[���p�b�h�E�}�E�X�p�b�h)
////�L�[�{�[�h�̊֐�
//HRESULT InitKeyboard(HWND hWnd);
//void UninitKeyboard(void);
//void UpdateKeyboard(void);
//void UninitGamepad(void);
//void UpdateGamepad(void);
//bool GetKeyboardPress(int nKey);
//bool GetKeyboardTrigger(int nKey);
//bool GetKeyboardRelease(int nKey);
//
////�Q�[���p�b�h�̊֐�
//HRESULT InitGamepad(HWND hWnd);
//bool GetGamepadPress(JOYKEY nKey, int nPlayer);
//bool GetGamepadTrigger(JOYKEY nKey, int nPlayer);
//bool GetGamepadRelease(JOYKEY nKey, int nPlayer);
//
////�}�E�X�p�b�h�̊֐�
//HRESULT InitMousepad(HWND hWnd);
//void UninitMousepad(void);
//void UpdateMousepad(void);
////void DrawMousepad(void);
//void GetMouseDebuc(void);
//

#endif 


