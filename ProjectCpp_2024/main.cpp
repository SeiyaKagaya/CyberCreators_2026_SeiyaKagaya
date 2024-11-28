//=======================================================
//
//main�Ɋւ��鏈��[main.cpp]
// Auther seiya kagaya
//
//=======================================================
#include"main.h"

#include "manager.h"
// �������[���[�N���o
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
//���C���֐�
//===================================
int WINAPI WinMain(	_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hInstancePrev,
					_In_ LPSTR lpCmdLine,
					_In_ int nCmdShow)
{
//	// ���������[�N���o��L����
_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//
	_CrtSetBreakAlloc(41770);


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							//�E�B���h�E�̃X�^�C��
		WindowProc,							//�E�B���h�E�̃v���[�W��
		0,									//0�ɂ���i�ʏ�͎g�p�����j
		0,									//0�ɂ���i�ʏ�͎g�p�����j
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),	//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C���g�̈�̕\���F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�B���h�E�N���X�̒�`
		LoadIcon(NULL, IDI_APPLICATION)		//�t�@�C���̃A�C�R��
	};

	HWND hWnd;
	MSG msg;
	RECT rect = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };//��ʃT�C�Y�̍\����
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E���쐬
	hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
		CLASS_NAME,				//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
		0,//CW_USEDEFAULT,			//�E�B���h�E����X���W///-----------------------------����ꂽ����Ƃɖ߂�
		0,//CW_USEDEFAULT,			//�E�B���h�E����Y
		(rect.right - rect.left),//���@
		(rect.bottom - rect.top),//����
		NULL,					//�e�E�B���h�E�̃n���h��
		NULL,					//���j���[�n���h���b�g���q�E�B���h�EID
		hInstance,				//�C���X�^���X�n���h��
		NULL);					//�E�B���h�E�쐬�f�[�^
	



	////����������
	//if (FAILED(Init(hWnd, TRUE)))
	//{//�����������s�����ꍇ
	//	return-1;//�ł��Ȃ������炱���ŏI���
	//}


	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);//�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);        //�N���C�A���g�̈���X�V



	CManager* pManager = CManager::GetInstance();
	if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

		//���b�Z�[�W���[�v
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
				TranslateMessage(&msg);//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W��ϊ�
				DispatchMessage(&msg); //�E�B���h�E�v���[�W���[�փ��b�Z�[�W����o
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

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);


	CObject::ReleaseAll();//�S���j��

	pManager->Uninit();

	


	//�����Ŕj������邽��
	//if (pManager !=nullptr)
	//{
	//	delete pManager;
	//	pManager = nullptr;
	//}


	return (int)msg.wParam;
}
//=======================================
//�E�B���h�E�v���V�[�W���[
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
			result = (MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION) == IDYES);
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

		// �J�����̐ݒ���X�V����
		CCamera::SetScreenSize((float)screenWidth, (float)screenHeight);

		// �N���C�A���g�̈�̍Ē���
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

		// �E�B���h�E�̃T�C�Y���Đݒ�
		SetWindowPos(hWnd, NULL, 0, 0, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, SWP_NOMOVE | SWP_NOZORDER);

		break;




	case WM_CLOSE:
		result = (MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONQUESTION) == IDYES);
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
//FPS�擾
//===========================
int GetFPS(void)
{
	return g_nCountFPS;
}
//===========================
// �E�B���h�E�̕��ƍ������擾����֐�
//===========================
void GetWindowSize(HWND hWnd, int& width, int& height)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
}