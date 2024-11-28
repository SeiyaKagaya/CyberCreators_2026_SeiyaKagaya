//=======================================================
//
//mainに関する処理[main.cpp]
// Auther seiya kagaya
//
//=======================================================
#include"main.h"

#include "manager.h"
// メモリーリーク検出
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define FIND_MEM_LEAKS
#endif // _DEBUG

#ifdef FIND_MEM_LEAKS
#define _NEW new (NORMALBLOCK, FILE, __LINE)
#else
#define _NEW new
#endif // FIND_MEM_LEAKS



int g_nCountFPS = 0;

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = nullptr;


//===================================
//メイン関数
//===================================
int WINAPI WinMain(	_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hInstancePrev,
					_In_ LPSTR lpCmdLine,
					_In_ int nCmdShow)
{
//	// メモリリーク検出を有効化
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//
	_CrtSetBreakAlloc(41770);


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							//ウィンドウのスタイル
		WindowProc,							//ウィンドウのプロージャ
		0,									//0にする（通常は使用せず）
		0,									//0にする（通常は使用せず）
		hInstance,							//インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),	//タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライント領域の表示色
		NULL,								//メニューバー
		CLASS_NAME,							//ウィンドウクラスの定義
		LoadIcon(NULL, IDI_APPLICATION)		//ファイルのアイコン
	};

	HWND hWnd;
	MSG msg;
	RECT rect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };//画面サイズの構造体
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定サイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを作成
	hWnd = CreateWindowEx(0,	//拡張ウィンドウスタイル
		CLASS_NAME,				//ウィンドウクラスの名前
		WINDOW_NAME,			//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
		0,//CW_USEDEFAULT,			//ウィンドウ左上X座標///-----------------------------言われたらもとに戻す
		0,//CW_USEDEFAULT,			//ウィンドウ左上Y
		(rect.right - rect.left),//幅　
		(rect.bottom - rect.top),//高さ
		NULL,					//親ウィンドウのハンドル
		NULL,					//メニューハンドル｜拡張子ウィンドウID
		hInstance,				//インスタンスハンドル
		NULL);					//ウィンドウ作成データ
	



	////初期化処理
	//if (FAILED(Init(hWnd, TRUE)))
	//{//初期化が失敗した場合
	//	return-1;//できなかったらここで終わり
	//}


	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);//ウィンドウの表示状態を設定
	UpdateWindow(hWnd);        //クライアント領域を更新



	CManager* pManager = CManager::GetInstance();
	if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

		//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);//仮想キーメッセージを文字メッセージを変換
				DispatchMessage(&msg); //ウィンドウプロージャーへメッセージを放出
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / GAME_FPS))
			{

				dwExecLastTime = dwCurrentTime;	

				pManager->Update();

				pManager->Draw();

				dwFrameCount++;
			}
		}
	}

	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);


	CObject::ReleaseAll();//全部破棄

	pManager->Uninit();

	


	//自動で破棄されるため
	//if (pManager !=nullptr)
	//{
	//	delete pManager;
	//	pManager = nullptr;
	//}


	return (int)msg.wParam;
}
//=======================================
//ウィンドウプロシージャー
//=======================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool result = false;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			result = (MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION) == IDYES);
			if (result == true)
			{
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	case WM_SIZE:

		int screenWidth, screenHeight;

		GetWindowSize(hWnd, screenWidth, screenHeight);

		// カメラの設定を更新する
		CCamera::SetScreenSize((float)screenWidth, (float)screenHeight);

		// クライアント領域の再調整
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

		// ウィンドウのサイズを再設定
		SetWindowPos(hWnd, NULL, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, SWP_NOMOVE | SWP_NOZORDER);

		break;




	case WM_CLOSE:
		result = (MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONQUESTION) == IDYES);
		if (result == true)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//===========================
//FPS取得
//===========================
int GetFPS(void)
{
	return g_nCountFPS;
}
//===========================
// ウィンドウの幅と高さを取得する関数
//===========================
void GetWindowSize(HWND hWnd, int& width, int& height)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
}