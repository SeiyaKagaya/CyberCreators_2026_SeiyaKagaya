//=======================================================
//
//���͂Ɋւ��鏈��[input.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "input.h"
#include "renderer.h"
#include "manager.h"

LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//=============================
//�R���X�g���N�^ 
//=============================
CInput::CInput()
{
	m_pDevicce = nullptr;
}
//=============================
// �f�X�g���N�^
//=============================
CInput::~CInput()
{
}
//=============================
// �����ݒ�
//=============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//=============================
// �I������
//=============================
void CInput::Uninit()
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevicce != NULL)
	{
		m_pDevicce->Unacquire();//�L�[�{�[�h�ւ̃A�N�Z�X����j��
		m_pDevicce->Release();
		m_pDevicce = NULL;
	}
	
	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//=============================
// �R���X�g���N�^
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

	//�}�E�X����
	ZeroMemory(&m_mouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&m_prevMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(m_mouseButtonState, sizeof(m_mouseButtonState));
	ZeroMemory(m_mouseButtonTriggerState, sizeof(m_mouseButtonTriggerState));
	ZeroMemory(m_mouseButtonReleaseState, sizeof(m_mouseButtonReleaseState));
}
//=============================
// �f�X�g���N�^
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
		m_pMouse->Unacquire();//�A�N�Z�X����j��
		m_pMouse->Release();
		m_pMouse = nullptr;
	}
}
//=============================
// �����ݒ�
//=============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(CInput::Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}

		//���̑��L�[�{�[�h�p�̐����A�ݒ�

		//���̓f�o�C�X�i�L�[�{�[�h�j�̐���
		if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevicce, NULL)))
		{
			return E_FAIL;
		}

		//�f�[�^�t�H�[�}�b�g��ݒ�
		if (FAILED(m_pDevicce->SetDataFormat(&c_dfDIKeyboard)))
		{
			return E_FAIL;
		}

		//�������[�h��ݒ�
		if (FAILED(m_pDevicce->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
		{
			return E_FAIL;
		}


		// �}�E�X�f�o�C�X�̐����A�ݒ�
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
// �j��
//=============================
void CInputKeyboard::Uninit()
{
	if (m_pMouse != nullptr)
	{
		m_pMouse->Unacquire();//�A�N�Z�X����j��
		m_pMouse->Release();
		m_pMouse = nullptr;
	}


	CInput::Uninit();

}

//=============================
// �X�V
//=============================
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY];//�L�[�{�[�h�̓��͏��

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevicce->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			//�����[�X����ԏザ��Ȃ��Ɠ��삵�Ȃ�
			//�r�b�g���Z����g���ă����[�X,���s�[�g�̏���ۑ�����(�܂������Ɨ������ĂȂ�)
			m_akeyReleaseState[nCntKey] = (m_akeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			m_akeyRepeatState[nCntKey] = (m_akeyState[nCntKey] & aKeyState[nCntKey]);

			m_akeyTriggerState[nCntKey] = (m_akeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//�L�[�{�[�h�̃g���K�[����ۑ�����
			m_akeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃v���X����ۑ�����
		}
	}
	else
	{
		m_pDevicce->Acquire();//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

	// �}�E�X�̏�Ԏ擾
	if (SUCCEEDED(m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
	{
		// �}�E�X�̏�Ԃ�O�̏�ԂƔ�r����
		for (int i = 0; i < 4; i++)
		{
			if (m_mouseState.rgbButtons[i] & 0x80)
			{
				if (!(m_prevMouseState.rgbButtons[i] & 0x80))
				{
					// �{�^���������ꂽ
					m_mouseButtonTriggerState[i] = true;
				}
				m_mouseButtonState[i] = true;
			}
			else
			{
				if (m_prevMouseState.rgbButtons[i] & 0x80)
				{
					// �{�^���������ꂽ
					m_mouseButtonReleaseState[i] = true;
				}
				m_mouseButtonState[i] = false;
			}
		}

		// �}�E�X�̑O�̏�Ԃ��X�V
		m_prevMouseState = m_mouseState;
	}
	else
	{
		m_pMouse->Acquire();//Mouse�ւ̃A�N�Z�X�����l��
	}
}
//=============================
// �}�E�X�X�N���[�����W�擾
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

			// �E�B���h�E���S��ʕ\���̏ꍇ�A�X�N���[�����W���N���C�A���g���W�ɕϊ����Ȃ�
			if (!(rect.right - rect.left == GetSystemMetrics(SM_CXSCREEN) &&
				rect.bottom - rect.top == GetSystemMetrics(SM_CYSCREEN)))
			{
				// �����ŁA�X�N���[�����W���N���C�A���g���W�ɕϊ�����
				ScreenToClient(hwnd, &point);
			}
		}
	}

	//--------------------------------------
		//�Ə�����ʊO�ɂłȂ��悤��
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
// �}�E�X�̍��W�����_
//=============================
D3DXVECTOR3 CInputKeyboard::GetMouseRayIntersection(const CCamera& camera)
{
	////�R���g���[���ڑ����͕ʂ̍��W��n��
	//CRenderer* pRenderer = nullptr;

	//CManager* pManager = CManager::GetInstance();

	//CInputKeyboard* keyboard = pManager->GetKeyboard();

	//CInputJoyPad* JoyPad = pManager->GetJoyPad();

	//XINPUT_STATE joykeystate;

	////�V���C�p�b�g�̏�Ԃ��擾
	//DWORD dwResult = XInputGetState(0, &joykeystate);

	//if (dwResult == ERROR_SUCCESS)
	//{//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)

	//}
	//else
	//{//�L�[�{�[�h���͔��f(�ړ�)

	//}




	POINT mousePos = GetMousePosition(); // �}�E�X��2D�X�N���[�����W�擾

	int screenWidth, screenHeight;

	D3DXVECTOR2 ScreenSize= CCamera::GetScreenSize();
	screenWidth = (int)ScreenSize.x;
	screenHeight = (int)ScreenSize.y;


	// �E�B���h�E�̃N���C�A���g�̈�̒��S���W���v�Z
	int clientCenterX = screenWidth / 2;
	int clientCenterY = screenHeight / 2;
	
	// �r���[�|�[�g�̐ݒ�
	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;

	// �}�E�X���W���E�B���h�E�̃N���C�A���g���W�ɕϊ�
	D3DXVECTOR3 screenPos((float)mousePos.x, (float)mousePos.y, 0.0f); // ����̓}�E�X�̈ʒu

	// ���������̍��W�ϊ������i�X�N���[����Ԃ���3D��Ԃւ̕ϊ��j�͂��̂܂܂ł�
	D3DXMATRIX projMatrix, viewMatrix, worldMatrix;

	// �J��������ˉe�s��ƃr���[�s����擾
	projMatrix = camera.GetProjectionMatrix();
	viewMatrix = camera.GetViewMatrix();

	// ���[���h�s��͒P�ʍs����g�p
	D3DXMatrixIdentity(&worldMatrix);

	// �X�N���[����Ԃ̍��W���������Ԃɕϊ�
	D3DXVECTOR3 nearPoint, farPoint;

	// �X�N���[����Ԃ̍��W��3D��Ԃ̍��W�ɕϊ�����֐�
	D3DXVec3Unproject(&nearPoint, &screenPos, &viewport, &projMatrix, &viewMatrix, &worldMatrix);
	screenPos.z = 1.0f;
	D3DXVec3Unproject(&farPoint, &screenPos, &viewport, &projMatrix, &viewMatrix, &worldMatrix);

	// ���C�̕���
	D3DXVECTOR3 rayDir = farPoint - nearPoint;
	D3DXVec3Normalize(&rayDir, &rayDir);

	// ���C�ƕ���(y=0)�̌�_���v�Z
	float t = -nearPoint.y / rayDir.y;

	D3DXVECTOR3 intersection = nearPoint + rayDir * t;

	return intersection;
}

//=============================
//�QD���W���X�N���[�����W�����_��
//=============================
D3DXVECTOR3 CInputKeyboard::GetScreenPosRayIntersection(const CCamera& camera, D3DXVECTOR3 Pos)
{
	POINT mousePos;//GetMousePosition(); // �}�E�X��2D�X�N���[�����W�擾

	mousePos.x = (LONG)Pos.x;
	mousePos.y = (LONG)Pos.y;

	int screenWidth, screenHeight;

	D3DXVECTOR2 ScreenSize = CCamera::GetScreenSize();
	screenWidth = (int)ScreenSize.x;
	screenHeight = (int)ScreenSize.y;


	// �E�B���h�E�̃N���C�A���g�̈�̒��S���W���v�Z
	int clientCenterX = screenWidth / 2;
	int clientCenterY = screenHeight / 2;

	// �r���[�|�[�g�̐ݒ�
	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;

	// �}�E�X���W���E�B���h�E�̃N���C�A���g���W�ɕϊ�
	D3DXVECTOR3 screenPos((float)mousePos.x, (float)mousePos.y, 0.0f); // ����̓}�E�X�̈ʒu

	// ���������̍��W�ϊ������i�X�N���[����Ԃ���3D��Ԃւ̕ϊ��j�͂��̂܂܂ł�
	D3DXMATRIX projMatrix, viewMatrix, worldMatrix;

	// �J��������ˉe�s��ƃr���[�s����擾
	projMatrix = camera.GetProjectionMatrix();
	viewMatrix = camera.GetViewMatrix();

	// ���[���h�s��͒P�ʍs����g�p
	D3DXMatrixIdentity(&worldMatrix);

	// �X�N���[����Ԃ̍��W���������Ԃɕϊ�
	D3DXVECTOR3 nearPoint, farPoint;

	// �X�N���[����Ԃ̍��W��3D��Ԃ̍��W�ɕϊ�����֐�
	D3DXVec3Unproject(&nearPoint, &screenPos, &viewport, &projMatrix, &viewMatrix, &worldMatrix);
	screenPos.z = 1.0f;
	D3DXVec3Unproject(&farPoint, &screenPos, &viewport, &projMatrix, &viewMatrix, &worldMatrix);

	// ���C�̕���
	D3DXVECTOR3 rayDir = farPoint - nearPoint;
	D3DXVec3Normalize(&rayDir, &rayDir);

	// ���C�ƕ���(y=0)�̌�_���v�Z
	float t = -nearPoint.y / rayDir.y;

	D3DXVECTOR3 intersection = nearPoint + rayDir * t;

	return intersection;
}
//=============================
//�v���X 
//=============================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_akeyState[nKey] & 0x80) != 0;
}
//=============================
// �g���K�[
//=============================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_akeyTriggerState[nKey] & 0x80) != 0;
}
//=============================
// �����[�X
//=============================
bool CInputKeyboard::GetRelease(int nKey)
{
	return (m_akeyReleaseState[nKey] & 0x80) != 0;
}
//=============================
// ���s�[�g
//=============================
bool CInputKeyboard::GetRepeat(int nKey)
{
	return (m_akeyRepeatState[nKey] & 0x80) != 0;
}
//=============================
// �}�E�X�{�^���̃v���X
//=============================
bool CInputKeyboard::GetMouseButtonPress(MouseKey nMouseKey)
{
	if (nMouseKey < 0 || nMouseKey >= 4) return false;
	return m_mouseButtonState[nMouseKey];
}
//=============================
// �}�E�X�{�^���̃g���K�[
//=============================
bool CInputKeyboard::GetMouseButtonTrigger(MouseKey nMouseKey)
{
	if (nMouseKey < 0 || nMouseKey >= 4) return false;
	bool state = m_mouseButtonTriggerState[nMouseKey];
	m_mouseButtonTriggerState[nMouseKey] = false; // �g���K�[��Ԃ����Z�b�g
	return state;
}
//=============================
// �}�E�X�{�^���̃����[�X
//=============================
bool CInputKeyboard::GetMouseButtonRelease(MouseKey nMouseKey)
{
	if (nMouseKey < 0 || nMouseKey >= 4) return false;
	bool state = m_mouseButtonReleaseState[nMouseKey];
	m_mouseButtonReleaseState[nMouseKey] = false; // �����[�X��Ԃ����Z�b�g
	return state;
}
//=============================
// �}�E�X�{�^���̃��s�[�g
//=============================
bool CInputKeyboard::GetMouseButtonRepeat(MouseKey nMouseKey)
{
	if (nMouseKey < 0 || nMouseKey >= 4) return false;
	return m_mouseButtonRepeatState[nMouseKey];
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//=============================
//�R���X�g���N�^
//=============================
CInputJoyPad::CInputJoyPad()
{
	m_JoykeyState = {};
	m_JoykeyStateTrigger = {};
	m_JoykeyStateRelease = {};
	m_JoykeyStateRepeat = {};
}

//=============================
//�f�X�g���N�^
//=============================
CInputJoyPad::~CInputJoyPad()
{
}

//=============================
//������
//=============================
HRESULT CInputJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�������̃N���A
	memset(&m_JoykeyState, 0, sizeof(XINPUT_STATE));

	//Xinput�̃X�e�[�g�̐ݒ�i�L�����p�j
	XInputEnable(true);

	return S_OK;

}

//=============================
//�I��
//=============================
void CInputJoyPad::Uninit()
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(false);
}

//=============================
//�X�V
//=============================
void CInputJoyPad::Update()
{
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{
		//�����[�X����ԏザ��Ȃ��Ɠ��삵�Ȃ�
			//�r�b�g���Z����g���ă����[�X,���s�[�g�̏���ۑ�����(�܂������Ɨ������ĂȂ�)
		m_JoykeyStateRelease.Gamepad.wButtons = (m_JoykeyState.Gamepad.wButtons ^ joykeystate.Gamepad.wButtons) & ~joykeystate.Gamepad.wButtons;		//�����[�X����	

		m_JoykeyStateRepeat.Gamepad.wButtons = (m_JoykeyState.Gamepad.wButtons & joykeystate.Gamepad.wButtons);											//���s�[�g����	

		m_JoykeyStateTrigger.Gamepad.wButtons = (m_JoykeyState.Gamepad.wButtons & joykeystate.Gamepad.wButtons) ^ joykeystate.Gamepad.wButtons;			//�g���K�[����	


		// �X�e�B�b�N�̃f�b�h�]�[��
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
//�v���X
//=============================
bool CInputJoyPad::GetPress(JOYkey nKey)
{
	return (m_JoykeyState.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}
//=============================
//�g���K�[
//=============================
bool CInputJoyPad::GetTrigger(JOYkey nKey)
{
	return (m_JoykeyStateTrigger.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}
//=============================
//�����[�X
//=============================
bool CInputJoyPad::GetRelease(JOYkey nKey)
{
	return (m_JoykeyStateRelease.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}
//=============================
//���s�[�h
//=============================
bool CInputJoyPad::GetRepeat(JOYkey nKey)
{
	return (m_JoykeyStateRepeat.Gamepad.wButtons & (0x01 << nKey)) ? true : false;
}
//=============================
//�o�C�u���[�V������
//=============================
void CInputJoyPad::VibrationLeft(int MotorSpeed)
{
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{

		//�֐�����

		////����
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = MotorSpeed; // use any value between 0-65535 here
		//vibration.wRightMotorSpeed = 16000; // use any value between 0-65535 here
		XInputSetState(0, &vibration);
	}
}
//=============================
//�o�C�u���[�V�����E
//=============================
void CInputJoyPad::VibrationRight(int MotorSpeed)
{
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{

		//�֐�����

		////����
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		//vibration.wLeftMotorSpeed = 32000; // use any value between 0-65535 here
		vibration.wRightMotorSpeed = MotorSpeed; // use any value between 0-65535 here
		XInputSetState(0, &vibration);
	}
}
//=============================
// �W���C�p�b�h�̐ڑ��L�����m�F����֐��̎���
//=============================
bool CInputJoyPad::IsJoyPadConnected()
{
	XINPUT_STATE state;
	return (XInputGetState(0, &state) == ERROR_SUCCESS);
}
