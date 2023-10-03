//============================
//
//�|���S���`��(main.cpp)
//Author:���� �F�M
//
//============================ 
#include "main.h"
#include "manager.h"
#include <stdio.h>
#include "debugproc.h"

//�}�N����`
#define CLASS_NAME    "WindowClass"        //�E�C���h�E�N���X�̖��O
#define WINDOW_NAME   "�^�C�g������" //�E�C���h�E�̖��O�i�L���v�V�����ɕ\���j



//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int						nCountFPS = 0;            //FPS�J�E���^
//LPD3DXFONT				g_pFont = NULL;             //�t�H���g�ւ̃|�C���^
//bool					g_bDispDebug = false;		//�f�o�b�O�\����ON/OFF

//============================
//���C���֐�
//============================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//�I�����Ƀ��������[�N���o��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�}�l�[�W���[�̐���
	CManager *pManager = NULL;

	//�E�C���h�E�N���X�̍\���̂�錾
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),           //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,                   //�E�C���h�E�̃X�^�C��
		WindowProc,                  //�E�C���h�E�v���V�[�W��
		0,                           //�O�ɂ���i�ʏ�͒ʗp���Ȃ�)
		0,							//0�ɂ���i�ʏ�͒ʗp���Ȃ��j
		hInstance,					//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),  //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),  //�N���C�A���g�̈�̔w�i�F
		NULL,						//���j���[�o�[
		CLASS_NAME,                 //�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),
	};

	HWND hWnd;				//�E�C���h�E�n���h��(���ʎq)

	MSG msg;				//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	RegisterClassEx(&wcex);			//�E�C���h�E�N���X�̓o�^

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h���쐬
	hWnd = CreateWindowEx(0,	//�g���E�C���h�E�X�^�C��
		CLASS_NAME,			//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,  //�E�C���h�E�X�^�C��
		CW_USEDEFAULT,      //�E�C���h�E�̍���X���W
		CW_USEDEFAULT,      //�E�C���h�E�̍���Y���W
		(rect.right - rect.left),     //�E�C���h�E�̕�
		(rect.bottom - rect.top),     //�E�C���h�E�̍���
		NULL,                 //�e�E�C���h�E�̃n���h��
		NULL,					//���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,			//�C���X�^���X�n���h��
		NULL);				    //�E�C���h�E�쐬�f�[�^

	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwExecLastTime;       //�Ō�ɏ�����������
	DWORD dwFrameCount;			//�t���[���J�E���g
	DWORD dwFPSLASTTIME;        //�Ō��FPS���v����������

	if (pManager == NULL)
	{
		pManager = NEW_DBG CManager;

		//�}�l�[�W���[�̏�����
		pManager->Init(hInstance, hWnd, TRUE);
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;  //����������
	dwExecLastTime = timeGetTime();		//���ݎ������擾(�ۑ�)
	dwFrameCount = 0;  //����������
	dwFPSLASTTIME = timeGetTime();      //FPS���ݐ��l���擾(�ۑ�)

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);       //�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);				  //�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���

				break;

			}

			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg); //���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);  //�E�C���h�E�v���[�W���փ��b�Z�[�W�𑗏o
			}
		}

		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();   //���ݎ������擾

			if ((dwCurrentTime - dwFPSLASTTIME) >= 500)
			{//0.5�b�o��
			 //FPS���v��
				nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLASTTIME);

				dwFPSLASTTIME = dwCurrentTime;   //FPS�𑪒肵��������ۑ�

				dwFrameCount = 0;   //�t���[���J�E���g���N���A
			}

			if (dwCurrentTime - dwExecLastTime >= (1000 / 60))
			{//60����1�b�o��

				dwExecLastTime = dwCurrentTime;  //�����J�n�̎���[���ݎ���]��ۑ�

			//�}�l�[�W���[�̍X�V
				pManager->Update();

				//�}�l�[�W���[�̕`��
				pManager->Draw();

				dwFrameCount++;         //�t���[���J�E���g�����Z

				//�f�o�b�O�\���̏���n��
				CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
				pDebug->Print("FPS : %d\n",nCountFPS);
#endif
			}
		}
	}

	//�}�l�[�W���[�̔j��
	if (pManager != NULL)
	{
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}
	
	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;

}

//�E�C���h�E�v���[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;  //�A��

	switch (uMsg)
	{
	case WM_DESTROY:   //�E�C���h�E�j���̃��b�Z�[�W

					   //WM_QUIT�Ƀ��b�Z�[�W�𑗂�
		PostQuitMessage(0);

		break;

	case WM_KEYDOWN:  //�L�[�������̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE:  //[ESC]�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂���", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{

				//�E�C���h�E��j������
				DestroyWindow(hWnd);

			}

			else
			{
				return 0;   //0��Ԃ��Ȃ��ƏI�����Ă��܂�
			}

			break;
		}
		break;

	case WM_CLOSE:  //����{�^���������̃��b�Z�[�W

		nID = MessageBox(hWnd, "�I�����܂���", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{

			//�E�C���h�E��j������
			DestroyWindow(hWnd);

		}

		else
		{
			return 0;   //0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}

		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  //����̏�����Ԃ�
}

////======================
////FPS�̕\��
////======================
//void DrawFPS(void)
//{
//	RECT rect = { 0,0,SCREEN_WINDTH,SCREEN_HEIGHT };
//
//	char aStr[256];
//
//	//������ɑ��
//	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
//
//	//�e�L�X�g�̕`��
//	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//}