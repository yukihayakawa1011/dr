//============================
//
//���͏���(input.cpp)
//Author:���� �F�M
//
//============================
#include "input.h"

//
////�}�E�X�p�b�h
//LPDIRECTINPUTDEVICE8 pDevMouse = NULL;  //���̓f�o�C�X�ւ̃|�C���^
//DIMOUSESTATE2 MouseState; //�S���͏��̕ۊ�

//�ÓI�����o�ϐ��錾
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//�R���X�g���N�^
CInput::CInput()
{
	m_pInput = NULL;	//���͂��N���A
	m_pDevice = NULL;	//�f�o�C�X���N���A
}

//�f�X�g���N�^
CInput::~CInput()
{

}

	
//=====================
//�f�o�C�X�̏�����
//=====================
HRESULT CInput::Init (HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}

		////�L�[�{�[�h
		//if (FAILED(InitKeyboard(hWnd)))
		//{
		//	return E_FAIL;
		//}
	}

	////�}�E�X
	//InitMousepad(hWnd);

	return S_OK;
}

//�f�o�C�X�̏I������
void CInput::Uninit(void)
{
	////�Q�[���p�b�h
	//UninitGamepad();

	////�}�E�X
	//UninitMousepad();

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	//DirectInput�f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//�L�[�{�[�h�̃R���X�g���N�^
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < 256; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aKeyStateTrigger[nCnt] = 0;
		m_aKeyStateRelease[nCnt] = 0;
	}
}

//�L�[�{�[�h�̃f�X�g���N�^
CInputKeyboard::~CInputKeyboard()
{

}

//======================
//�L�[�{�[�h�̏���������
//======================
HRESULT CInputKeyboard::Init(HINSTANCE hInstans, HWND hWnd)
{
	CInput::Init(hInstans, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}

//======================
//�L�[�{�[�h�I������
//======================
void CInputKeyboard::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();  //�L�[�{�[�h�̃A�N�Z�X�������

		m_pDevice->Release();

		m_pDevice = NULL;
	}

	//DirectInput�f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//======================
//�L�[�{�[�h�X�V����
//======================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];  //�L�[�{�[�h�̓��͏��

	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�L�[�{�[�h�̃g���K�[����ۑ�
																		
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) &~aKeyState[nCntKey]; //�L�[�{�[�h�̃����[�X����ۑ�

			m_aKeyState[nCntKey] = aKeyState[nCntKey];  //�L�[�{�[�h�̃v���X����ۑ�
		}
	}

	else
	{
		m_pDevice->Acquire();   //�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

}

//�L�[�{�[�h�̃v���X�����擾
bool CInputKeyboard::GetPless(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�̃g���K�[�����擾
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//�L�[�{�[�h�̃����[�X�����擾
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//�Q�[���p�b�h�̃R���X�g���N�^
CInputGamePad::CInputGamePad()
{
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			ZeroMemory(&m_aGamepadState[nCnt], sizeof(XINPUT_STATE)); //�p�b�h�̃v���X���
			ZeroMemory(&m_aGamepadState[nCnt], sizeof(XINPUT_STATE)); //�p�b�h�̃g���K�[���
			ZeroMemory(&m_aGamepadState[nCnt], sizeof(XINPUT_STATE)); //�p�b�h�̃����[�X���
		}
}		

//�Q�[���p�b�h�̃f�X�g���N�^
CInputGamePad::~CInputGamePad()
{

}


//============================
//�Q�[���p�b�h�̏�����
//============================
HRESULT CInputGamePad::Init(HWND hWnd)
{
	int nCnt;

	//�Q�[���p�b�h�ݒ��L���ɂ���
	XInputEnable(true);

	//�������̏��̏�����
	for (nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		memset(&m_aGamepadState[nCnt], 0, sizeof(XINPUT_STATE)); //�v���X���

		memset(&m_aGamepadStateTrigger[nCnt], 0, sizeof(XINPUT_STATE)); //�g���K�[���

		memset(&m_aGamepadStateRelease[nCnt], 0, sizeof(XINPUT_STATE)); //�����[�X���
	}
	
	return S_OK;
}

//======================
//�Q�[���p�b�h�̏I��
//======================
void CInputGamePad::Uninit(void)
{
	//�Q�[���p�b�h�ݒ��L���ɂ���
	XInputEnable(false);
}

//======================
//�Q�[���p�b�h�̍X�V
//======================
void CInputGamePad::Update(void)
{
	int nCnt;

	XINPUT_STATE aGamepadState[NUM_KEY_MAX];

	for (nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		//���̓f�o�C�X����f�[�^���擾
		if (XInputGetState(nCnt, &aGamepadState[nCnt]) == ERROR_SUCCESS)
		{
			m_aGamepadStateTrigger[nCnt].Gamepad.wButtons = (m_aGamepadState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons)
				& aGamepadState[nCnt].Gamepad.wButtons; //�g���K�[�̃f�[�^���擾

			m_aGamepadStateRelease[nCnt].Gamepad.wButtons = (m_aGamepadState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons)
				&~aGamepadState[nCnt].Gamepad.wButtons; //�����[�X�̃f�[�^���擾

			m_aGamepadState[nCnt] = aGamepadState[nCnt];  //�v���X�̃f�[�^���擾
		}
	}
}

//�Q�[���p�b�h�̃v���X�����擾
bool CInputGamePad::GetPless(JOYKEY nKey, int nPlayer)
{
	return(m_aGamepadState[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

//�Q�[���p�b�h�̃g���K�[�����擾
bool CInputGamePad::GetTrigger(JOYKEY nKey, int nPlayer)
{
	return(m_aGamepadStateTrigger[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

//�Q�[���p�b�h�̃����[�X�����擾
bool CInputGamePad::GetRelease(JOYKEY nKey, int nPlayer)
{
	return(m_aGamepadStateRelease[nPlayer].Gamepad.wButtons &(0x01 << nKey)) ? true : false;
}

//���X�e�B�b�N�̊֐�(X���̃v���X)
SHORT CInputGamePad::GetGameStickL_X_Press(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadState[nPlayer].Gamepad.sThumbLX;
}

//���X�e�B�b�N�̊֐�(Y���̃v���X)
SHORT CInputGamePad::GetGameStickL_Y_Press(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadState[nPlayer].Gamepad.sThumbLY;
}

//���X�e�B�b�N�̊֐�(X���̃g���K�[)
SHORT CInputGamePad::GetGameStickL_X_Trigger(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateTrigger[nPlayer].Gamepad.sThumbLX;
}

//���X�e�B�b�N�̊֐�(Y���̃g���K�[)
SHORT CInputGamePad::GetGameStickL_Y_Trigger(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateTrigger[nPlayer].Gamepad.sThumbLY;
}

//���X�e�B�b�N�̊֐�(X���̃����[�X)
SHORT CInputGamePad::GetGameStickL_X_Release(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateRelease[nPlayer].Gamepad.sThumbLX;
}

//���X�e�B�b�N�̊֐�(Y���̃����[�X)
SHORT CInputGamePad::GetGameStickL_Y_Release(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateRelease[nPlayer].Gamepad.sThumbLY;
}

//�E�X�e�B�b�N�̊֐�(X���̃v���X)
SHORT CInputGamePad::GetGameStickR_X_Press(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadState[nPlayer].Gamepad.sThumbRX;
}
//�E�X�e�B�b�N�̊֐�(Y���̃v���X)
SHORT CInputGamePad::GetGameStickR_Y_Press(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadState[nPlayer].Gamepad.sThumbRY;
}

//�E�X�e�B�b�N�̊֐�(X���̃g���K�[)
SHORT CInputGamePad::GetGameStickR_X_Trigger(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateTrigger[nPlayer].Gamepad.sThumbRX;
}

//�E�X�e�B�b�N�̊֐�(Y���̃g���K�[)
SHORT CInputGamePad::GetGameStickR_Y_Trigger(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateTrigger[nPlayer].Gamepad.sThumbRY;
}

//�E�X�e�B�b�N�̊֐�(X���̃����[�X)
SHORT CInputGamePad::GetGameStickR_X_Release(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateRelease[nPlayer].Gamepad.sThumbRX;
}

//�E�X�e�B�b�N�̊֐�(Y���̃����[�X)
SHORT CInputGamePad::GetGameStickR_Y_Release(JOYKEY nKey, int nPlayer)
{
	return m_aGamepadStateRelease[nPlayer].Gamepad.sThumbRY;
}

////======================
////�}�E�X�̏���������
////======================
//HRESULT InitMousepad(HWND hWnd)
//{
//
//	//���̓f�o�C�X(�}�E�X)�̐���
//	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &pDevMouse, NULL)))
//	{
//		return E_FAIL;
//	}
//
//	//�f�[�^�t�H�[�}�b�g��ݒ�
//	if (FAILED(pDevMouse->SetDataFormat(&c_dfDIMouse2)))
//	{
//		return E_FAIL;
//	}
//
//	//�������[�h��ݒ�
//	if (FAILED(pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
//	{
//		return E_FAIL;
//	}
//
//	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
//	pDevMouse->Acquire();
//
//	return S_OK;
//}







////======================
////�}�E�X�I������
////======================
//void UninitMousepad(void)
//{
//	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
//	if (pDevMouse != NULL)
//	{
//		pDevMouse->Unacquire();  //�L�[�{�[�h�̃A�N�Z�X�������
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
////�}�E�X�X�V����
////======================
//void UpdateMousepad(void)
//{
//	DIMOUSESTATE2 mouse;  //�}�E�X�̓��͏��
//
//	int nCntKey;
//
//	//���̓f�o�C�X����f�[�^���擾
//	if (SUCCEEDED(pDevMouse->GetDeviceState(sizeof(mouse), &mouse)))
//	{
//		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
//		{
//			//MouseState = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�}�E�X�̃g���K�[����ۑ�
//
//			//g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) &~aKeyState[nCntKey]; //�}�E�X�̃����[�X����ۑ�
//
//			MouseState = mouse;  //�}�E�X�̃v���X����ۑ�
//		}
//	}
//
//	else
//	{
//		pDevMouse->Acquire();   //�}�E�X�ւ̃A�N�Z�X�����l��
//	}
//
//}

//
////�}�E�X�̃f�o�b�N�\��
//void GetMouseDebuc(void)
//{
//	//���[�J���ϐ��錾
//	char aStr[256];
//
//	//�t�H���g�̎擾
//	LPD3DXFONT pFont = GetFont();
//
//	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
//	{
//		//�͈͂̎w��
//		RECT rect = { 0,30 + nCnt * 30,SCREEN_WINDTH,SCREEN_HEIGHT };
//
//		//������ɑ��
//		if (nCnt < NUM_KEY_MAX)
//		{
//			sprintf(&aStr[0], "rgbButtons[%d] : %d", nCnt, MouseState.rgbButtons[nCnt]);
//		}
//
//		//�e�L�X�g�̕`��
//		pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//
//	}
//}