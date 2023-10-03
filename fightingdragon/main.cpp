//============================
//
//ポリゴン描画(main.cpp)
//Author:早川 友貴
//
//============================ 
#include "main.h"
#include "manager.h"
#include <stdio.h>
#include "debugproc.h"

//マクロ定義
#define CLASS_NAME    "WindowClass"        //ウインドウクラスの名前
#define WINDOW_NAME   "タイトル未定" //ウインドウの名前（キャプションに表示）



//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int						nCountFPS = 0;            //FPSカウンタ
//LPD3DXFONT				g_pFont = NULL;             //フォントへのポインタ
//bool					g_bDispDebug = false;		//デバッグ表示のON/OFF

//============================
//メイン関数
//============================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//終了時にメモリリークを出力
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//マネージャーの生成
	CManager *pManager = NULL;

	//ウインドウクラスの構造体を宣言
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),           //WNDCLASSEXのメモリサイズ
		CS_CLASSDC,                   //ウインドウのスタイル
		WindowProc,                  //ウインドウプロシージャ
		0,                           //０にする（通常は通用しない)
		0,							//0にする（通常は通用しない）
		hInstance,					//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),  //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),  //クライアント領域の背景色
		NULL,						//メニューバー
		CLASS_NAME,                 //ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),
	};

	HWND hWnd;				//ウインドウハンドル(識別子)

	MSG msg;				//メッセージを格納する変数

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	RegisterClassEx(&wcex);			//ウインドウクラスの登録

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドを作成
	hWnd = CreateWindowEx(0,	//拡張ウインドウスタイル
		CLASS_NAME,			//ウインドウクラスの名前
		WINDOW_NAME,			//ウインドウの名前
		WS_OVERLAPPEDWINDOW,  //ウインドウスタイル
		CW_USEDEFAULT,      //ウインドウの左上X座標
		CW_USEDEFAULT,      //ウインドウの左上Y座標
		(rect.right - rect.left),     //ウインドウの幅
		(rect.bottom - rect.top),     //ウインドウの高さ
		NULL,                 //親ウインドウのハンドル
		NULL,					//メニューハンドルまたは子ウインドウID
		hInstance,			//インスタンスハンドル
		NULL);				    //ウインドウ作成データ

	DWORD dwCurrentTime;		//現在時刻
	DWORD dwExecLastTime;       //最後に処理した時刻
	DWORD dwFrameCount;			//フレームカウント
	DWORD dwFPSLASTTIME;        //最後にFPSを計測した時刻

	if (pManager == NULL)
	{
		pManager = NEW_DBG CManager;

		//マネージャーの初期化
		pManager->Init(hInstance, hWnd, TRUE);
	}

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;  //初期化する
	dwExecLastTime = timeGetTime();		//現在時刻を取得(保存)
	dwFrameCount = 0;  //初期化する
	dwFPSLASTTIME = timeGetTime();      //FPS現在数値を取得(保存)

	//ウインドウの表示
	ShowWindow(hWnd, nCmdShow);       //ウインドウの表示状態を設定
	UpdateWindow(hWnd);				  //クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける

				break;

			}

			else
			{
				//メッセージの設定
				TranslateMessage(&msg); //仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);  //ウインドウプロージャへメッセージを送出
			}
		}

		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();   //現在時刻を取得

			if ((dwCurrentTime - dwFPSLASTTIME) >= 500)
			{//0.5秒経過
			 //FPSを計測
				nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLASTTIME);

				dwFPSLASTTIME = dwCurrentTime;   //FPSを測定した時刻を保存

				dwFrameCount = 0;   //フレームカウントをクリア
			}

			if (dwCurrentTime - dwExecLastTime >= (1000 / 60))
			{//60分の1秒経過

				dwExecLastTime = dwCurrentTime;  //処理開始の時刻[現在時刻]を保存

			//マネージャーの更新
				pManager->Update();

				//マネージャーの描画
				pManager->Draw();

				dwFrameCount++;         //フレームカウントを加算

				//デバッグ表示の情報を渡す
				CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
				pDebug->Print("FPS : %d\n",nCountFPS);
#endif
			}
		}
	}

	//マネージャーの破棄
	if (pManager != NULL)
	{
		pManager->Uninit();

		delete pManager;

		pManager = NULL;
	}
	
	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;

}

//ウインドウプロージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;  //帰り

	switch (uMsg)
	{
	case WM_DESTROY:   //ウインドウ破棄のメッセージ

					   //WM_QUITにメッセージを送る
		PostQuitMessage(0);

		break;

	case WM_KEYDOWN:  //キー押したのメッセージ

		switch (wParam)
		{
		case VK_ESCAPE:  //[ESC]キーが押された

			nID = MessageBox(hWnd, "終了しますか", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{

				//ウインドウを破棄する
				DestroyWindow(hWnd);

			}

			else
			{
				return 0;   //0を返さないと終了してしまう
			}

			break;
		}
		break;

	case WM_CLOSE:  //閉じるボタン押したのメッセージ

		nID = MessageBox(hWnd, "終了しますか", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{

			//ウインドウを破棄する
			DestroyWindow(hWnd);

		}

		else
		{
			return 0;   //0を返さないと終了してしまう
		}

		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  //既定の処理を返す
}

////======================
////FPSの表示
////======================
//void DrawFPS(void)
//{
//	RECT rect = { 0,0,SCREEN_WINDTH,SCREEN_HEIGHT };
//
//	char aStr[256];
//
//	//文字列に代入
//	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
//
//	//テキストの描画
//	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//}