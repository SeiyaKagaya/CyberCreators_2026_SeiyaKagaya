//=======================================================
//
//入力に関する処理[input.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "input.h"
#include "renderer.h"
#include "manager.h"

LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//=============================
//コンストラクタ 
//=============================
CInput::CInput()
{
	m_pDevicce = nullptr;
}
//=============================
// デストラクタ
//=============================
CInput::~CInput()
{
}
//=============================
// 初期設定
//=============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//=============================
// 終了処理
//=============================
void CInput::Uninit()
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevicce != NULL)
	{
		m_pDevicce->Unacquire();//キーボードへのアクセス権を破棄
		m_pDevicce->Release();
		m_pDevicce = NULL;
	}
	
	//DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//=============================
// コンストラクタ
//=============================
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
	{
		m_akeyState[nCnt] = {};
		m_akeyTriggerState[nCnt] = {};
		m_akeyReleaseState[nCnt] = {};
		m_akeyRepeatState[nCnt] = {};
	}

	//マウス周り
	ZeroMemory(&m_mouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_prevMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(m_mouseButtonState, sizeof(m_mouseButtonState));
	ZeroMemory(m_mouseButtonTriggerState, sizeof(m_mouseButtonTriggerState));
	ZeroMemory(m_mouseButtonReleaseState, sizeof(m_mouseButtonReleaseState));
}
//=============================
// デストラクタ
//=============================
CInputKeyboard::~CInputKeyboard()
{
	for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
	{
		m_akeyState[nCnt] = {};
		m_akeyTriggerState[nCnt] = {};
		m_akeyReleaseState[nCnt] = {};
		m_akeyRepeatState[nCnt] = {};
	}

	if (m_pMouse!=nullptr)
	{
		m_pMouse->Unacquire();//アクセス権を破棄
		m_pMouse->Release();
		m_pMouse = nullptr;
	}
}
//=============================
// 初期設定
//=============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(CInput::Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}

		//その他キーボード用の生成、設定

		//入力デバイス（キーボード）の生成
		if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevicce, NULL)))
		{
			return E_FAIL;
		}

		//データフォーマットを設定
		if (FAILED(m_pDevicce->SetDataFormat(&c_dfDIKeyboard)))
		{
			return E_FAIL;
		}

		//協調モードを設定
		if (FAILED(m_pDevicce->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}


		// マウスデバイスの生成、設定
		if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL)))
		{
			return E_FAIL;
		}
		if (FAILED(m_pMouse->SetDataFormat(&c_dfDIMouse)))
		{
			return E_FAIL;
		}
		if (FAILED(m_pMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}
	}

	m_hWnd = hWnd;

	return S_OK;
}

//=============================
// 破棄
//=============================
void CInputKeyboard::Uninit()
{
	if (m_pMouse != nullptr)
	{
		m_pMouse->Unacquire();//アクセス権を破棄
		m_pMouse->Release();
		m_pMouse = nullptr;
	}


	CInput::Uninit();

}

//=============================
// 更新
//=============================
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY];//キーボードの入力情報

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevicce->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			//リリースが一番上じゃないと動作しない
			//ビット演算を駆使してリリース,リピートの情報を保存する(まだちゃんと理解してない)
			m_akeyReleaseState[nCntKey] = (m_akeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_akeyRepeatState[nCntKey] = (m_akeyState[nCntKey] & aKeyState[nCntKey]);

			m_akeyTriggerState[nCntKey] = (m_akeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//キーボードのトリガー情報を保存する
			m_akeyState[nCntKey] = aKeyState[nCntKey];//キーボードのプレス情報を保存する
		}
	}
	else
	{
		m_pDevicce->Acquire();//キーボードへのアクセス権を獲得
	}

	// マウスの状態取得
	if (SUCCEEDED(m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
	{
		// マウスの状態を前の状態と比較する
		for (int i = 0; i < 4; i++)
		{
			if (m_mouseState.rgbButtons[i] & 0x80)
			{
				if (!(m_prevMouseState.rgbButtons[i] & 0x80))
				{
					// ボタンが押された
					m_mouseButtonTriggerState[i] = true;
				}
				m_mouseButtonState[i] = true;
			}
			else
			{
				if (m_prevMouseState.rgbButtons[i] & 0x80)
				{
					// ボタンが離された
					m_mouseButtonReleaseState[i] = true;
				}
				m_mouseButtonState[i] = false;
			}
		}

		// マウスの前の状態を更新
		m_prevMouseState = m_mouseState;
	}
	else
	{
		m_pMouse->Acquire();//Mouseへのアクセス権を獲得
	}
}
//=============================
// マウススクリーン座標取得
//=============================
POINT CInputKeyboard::GetMousePosition()
{
	POINT point;
	if (GetCursorPos(&point))
	{
		HWND hwnd = GetActiveWindow();
		if (hwnd)
		{
			RECT rect;
			GetClientRect(hwnd, &rect);

			// ウィンドウが全画面表示の場合、スクリーン座標をクライアント座標に変換しない
			if (!(rect.right - rect.left == GetSystemMetrics(SM_CXSCREEN) &&
				rect.bottom - rect.top == GetSystemMetrics(SM_CYSCREEN)))
			{
				// ここで、スクリーン座標をクライアント座標に変換する
				ScreenToClient(hwnd, &point);
			}
		}
	}

	//--------------------------------------
		//照準が画面外にでないように
	if (point.x < 0)
	{
		point.x = 0;
	}
	else if (point.x > (LONG)SCREEN_WIDTH)
	{
		point.x = (LONG)SCREEN_WIDTH;
	}

	if (point.y < 0)
	{
		point.y = 0;
	}
	else if (point.y > (LONG)SCREEN_HEIGHT)
	{
		point.y = (LONG)SCREEN_HEIGHT;
	}
	//--------------------------------------


	return point;
}
//=============================
// マウスの座標交差点
//=============================
D3DXVECTOR3 CInputKeyboard::GetMouseRayIntersection(const CCamera& camera)
{
	////コントローラ接続時は別の座標を渡す
	//CRenderer* pRenderer = nullptr;

	//CManager* pManager = CManager::GetInstance();

	//CInputKeyboard* keyboard = pManager->GetKeyboard();

	//CInputJoyPad* JoyPad = pManager->GetJoyPad();

	//XINPUT_STATE joykeystate;

	////ショイパットの状態を取得
	//DWORD dwResult = XInputGetState(0, &joykeystate);

	//if (dwResult == ERROR_SUCCESS)
	//{//キーボード/コントローラー入力反映(移動)

	//}
	//else
	//{//キーボード入力反映(移動)

	//}




	POINT mousePos = GetMousePosition(); // マウスの2Dスクリーン座標取得

	int screenWidth, screenHeight;

	D3DXVECTOR2 ScreenSize= CCamera::GetScreenSize();
	screenWidth = (int)ScreenSize.x;
	screenHeight = (int)ScreenSize.y;


	// ウィンドウのクライアント領域の中心座標を計算
	int clientCenterX = screenWidth / 2;
	int clientCenterY = screenHeight / 2;
	
	// ビューポートの設定
	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;

	// マウス座標をウィンドウのクライアント座標に変換
	D3DXVECTOR3 screenPos((float)mousePos.x, (float)mousePos.y, 0.0f); // これはマウスの位置

	// ここから先の座標変換処理（スクリーン空間から3D空間への変換）はそのままです
	D3DXMATRIX projMatrix, viewMatrix, worldMatrix;

	// カメラから射影行列とビュー行列を取得
	projMatrix = camera.GetProjectionMatrix();
	viewMatrix = camera.GetViewMatrix();

	// ワールド行列は単位行列を使用
	D3DXMatrixIdentity(&worldMatrix);

	// スクリーン空間の座標を視錐台空間に変換
	D3DXVECTOR3 nearPoint, farPoint;

	// スクリーン空間の座標を3D空間の座標に変換する関数
	D3DXVec3Unproject(&nearPoint, &screenPos, &viewport, &projMatrix, &viewMatrix, &worldMatrix);
	screenPos.z = 1.0f;
	D3DXVec3Unproject(&farPoint, &screenPos, &viewport, &projMatrix, &viewMatrix, &worldMatrix);

	// レイの方向
	D3DXVECTOR3 rayDir = farPoint - nearPoint;
	D3DXVec3Normalize(&rayDir, &rayDir);

	// レイと平面(y=0)の交点を計算
	float t = -nearPoint.y / rayDir.y;

	D3DXVECTOR3 intersection = nearPoint + rayDir * t;

	return intersection;
}

//=============================
//２D座標をスクリーン座標交差点に
//=============================
D3DXVECTOR3 CInputKeyboard::GetScreenPosRayIntersection(const CCamera& camera, D3DXVECTOR3 Pos)
{
	POINT mousePos;//GetMousePosition(); // マウスの2Dスクリーン座標取得

	mousePos.x = (LONG)Pos.x;
	mousePos.y = (LONG)Pos.y;

	int screenWidth, screenHeight;

	D3DXVECTOR2 ScreenSize = CCamera::GetScreenSize();
	screenWidth = (int)ScreenSize.x;
	screenHeight = (int)ScreenSize.y;


	// ウィンドウのクライアント領域の中心座標を計算
	int clientCenterX = screenWidth / 2;
	int clientCenterY = screenHeight / 2;

	// ビューポートの設定
	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;

	// マウス座標をウィンドウのクライアント座標に変換
	D3DXVECTOR3 screenPos((float)mousePos.x, (float)mousePos.y, 0.0f); // これはマウスの位置

	// ここから先の座標変換処理（スクリーン空間から3D空間への変換）はそのままです
	D3DXMATRIX projMatrix, viewMatrix, worldMatrix;

	// カメラから射影行列とビュー行列を取得
	projMatrix = camera.GetProjectionMatrix();
	viewMatrix = camera.GetViewMatrix();

	// ワールド行列は単位行列を使用
	D3DXMatrixIdentity(&worldMatrix);

	// スクリーン空間の座標を視錐台空間に変換
	D3DXVECTOR3 nearPoint, farPoint;

	// スクリーン空間の座標を3D空間の座標に変換する関数
	D3DXVec3Unproject(&nearPoint, &screenPos, &viewport, &projMatrix, &viewMatrix, &worldMatrix);
	screenPos.z = 1.0f;
	D3DXVec3Unproject(&farPoint, &screenPos, &viewport, &projMatrix, &viewMatrix, &worldMatrix);

	// レイの方向
	D3DXVECTOR3 rayDir = farPoint - nearPoint;
	D3DXVec3Normalize(&rayDir, &rayDir);

	// レイと平面(y=0)の交点を計算
	float t = -nearPoint.y / rayDir.y;

	D3DXVECTOR3 intersection = nearPoint + rayDir * t;

	return intersection;
}
//=============================
//プレス 
//=============================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_akeyState[nKey] & 0x80) != 0;
}
//=============================
// トリガー
//=============================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_akeyTriggerState[nKey] & 0x80) != 0;
}
//=============================
// リリース
//=============================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_akeyReleaseState[nKey] & 0x80) != 0;
}
//=============================
// リピート
//=============================
bool CInputKeyboard::GetRepeat(int nKey)
{
	return (m_akeyRepeatState[nKey] & 0x80) != 0;
}
//=============================
// マウスボタンのプレス
//=============================
bool CInputKeyboard::GetMouseButtonPress(MouseKey nMouseKey)
{
	if (nMouseKey < 0 || nMouseKey >= 4) return false;
	return m_mouseButtonState[nMouseKey];
}
//=============================
// マウスボタンのトリガー
//=============================
bool CInputKeyboard::GetMouseButtonTrigger(MouseKey nMouseKey)
{
	if (nMouseKey < 0 || nMouseKey >= 4) return false;
	bool state = m_mouseButtonTriggerState[nMouseKey];
	m_mouseButtonTriggerState[nMouseKey] = false; // トリガー状態をリセット
	return state;
}
//=============================
// マウスボタンのリリース
//=============================
bool CInputKeyboard::GetMouseButtonRelease(MouseKey nMouseKey)
{
	if (nMouseKey < 0 || nMouseKey >= 4) return false;
	bool state = m_mouseButtonReleaseState[nMouseKey];
	m_mouseButtonReleaseState[nMouseKey] = false; // リリース状態をリセット
	return state;
}
//=============================
// マウスボタンのリピート
//=============================
bool CInputKeyboard::GetMouseButtonRepeat(MouseKey nMouseKey)
{
	if (nMouseKey < 0 || nMouseKey >= 4) return false;
	return m_mouseButtonRepeatState[nMouseKey];
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//=============================
//コンストラクタ
//=============================
CInputJoyPad::CInputJoyPad()
{
	m_JoykeyState = {};
	m_JoykeyStateTrigger = {};
	m_JoykeyStateRelease = {};
	m_JoykeyStateRepeat = {};
}

//=============================
//デストラクタ
//=============================
CInputJoyPad::~CInputJoyPad()
{
}

//=============================
//初期化
//=============================
HRESULT CInputJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//メモリのクリア
	memset(&m_JoykeyState, 0, sizeof(XINPUT_STATE));

	//Xinputのステートの設定（有効活用）
	XInputEnable(true);

	return S_OK;

}

//=============================
//終了
//=============================
void CInputJoyPad::Uninit()
{
	//Xinputのステートの設定
	XInputEnable(false);
}

//=============================
//更新
//=============================
void CInputJoyPad::Update()
{
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{
		//リリースが一番上じゃないと動作しない
			//ビット演算を駆使してリリース,リピートの情報を保存する(まだちゃんと理解してない)
		m_JoykeyStateRelease.Gamepad.wButtons = (m_JoykeyState.Gamepad.wButtons ^ joykeystate.Gamepad.wButtons) & ~joykeystate.Gamepad.wButtons;		//リリース処理	

		m_JoykeyStateRepeat.Gamepad.wButtons = (m_JoykeyState.Gamepad.wButtons & joykeystate.Gamepad.wButtons);											//リピート処理	

		m_JoykeyStateTrigger.Gamepad.wButtons = (m_JoykeyState.Gamepad.wButtons & joykeystate.Gamepad.wButtons) ^ joykeystate.Gamepad.wButtons;			//トリガー処理	


		// スティックのデッドゾーン
		if ((m_JoykeyState.Gamepad.sThumbLX <  (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) &&
			m_JoykeyState.Gamepad.sThumbLX > -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000)) &&
			(m_JoykeyState.Gamepad.sThumbLY <  (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) &&
				m_JoykeyState.Gamepad.sThumbLY > -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000)))
		{
			m_JoykeyState.Gamepad.sThumbLX = 0;
			m_JoykeyState.Gamepad.sThumbLY = 0;
		}

		m_JoykeyState = joykeystate;
	}
}

//=============================
//プレス
//=============================
bool CInputJoyPad::GetPress(JOYkey nKey)
{
	return (m_JoykeyState.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}
//=============================
//トリガー
//=============================
bool CInputJoyPad::GetTrigger(JOYkey nKey)
{
	return (m_JoykeyStateTrigger.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}
//=============================
//リリース
//=============================
bool CInputJoyPad::GetRelease(JOYkey nKey)
{
	return (m_JoykeyStateRelease.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}
//=============================
//リピード
//=============================
bool CInputJoyPad::GetRepeat(JOYkey nKey)
{
	return (m_JoykeyStateRepeat.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}
//=============================
//バイブレーション左
//=============================
void CInputJoyPad::VibrationLeft(int MotorSpeed)
{
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{

		//関数分け

		////動く
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = MotorSpeed; // use any value between 0-65535 here
		//vibration.wRightMotorSpeed = 16000; // use any value between 0-65535 here
		XInputSetState(0, &vibration);
	}
}
//=============================
//バイブレーション右
//=============================
void CInputJoyPad::VibrationRight(int MotorSpeed)
{
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{

		//関数分け

		////動く
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		//vibration.wLeftMotorSpeed = 32000; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = MotorSpeed; // use any value between 0-65535 here
		XInputSetState(0, &vibration);
	}
}
//=============================
// ジョイパッドの接続有無を確認する関数の実装
//=============================
bool CInputJoyPad::IsJoyPadConnected()
{
	XINPUT_STATE state;
	return (XInputGetState(0, &state) == ERROR_SUCCESS);
}
