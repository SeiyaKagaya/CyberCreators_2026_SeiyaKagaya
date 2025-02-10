//=========================================================
//
// input.cpp�Ŏg���֐�[input.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _INPUT_H
#define _INPUT_H//��d�C���N���[�h�h�~

#include "main.h"
#include "camera.h"

#define MAX_KEY	(256)//�ő�L�[��

class CInput
{
public:
	CInput();//�R���X�g���N�^
	~CInput();//�f�X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	virtual void Uninit();
	virtual void Update() = 0;
	
protected:

	//	�S���͏����ŋ��L
	static	LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevicce = {};

	//�厖
	HWND m_hWnd{};
};


//�L�[�{�[�h�n
class CInputKeyboard : CInput
{
public:

	CInputKeyboard();//�R���X�g���N�^
	~CInputKeyboard();//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	void Uninit();
	void Update();

	//�e���͔���
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

	//�}�E�X�n
	 typedef enum
	{
		MouseKey_Left=0,
		MouseKey_Right,
		MouseKey_Center,
		MouseKey_Fourth,
	}MouseKey;

	//0�F���{�^���i�ʏ�̍��N���b�N�j
	//1�F�E�{�^���i�ʏ�̉E�N���b�N�j
	//2�F�����{�^���i�ʏ�̃z�C�[���N���b�N�j
	//3�F��4�{�^���i�T�C�h�{�^���̈�B�ʏ�́u�߂�v�{�^���Ƃ��Ďg���邱�Ƃ������j
		
	bool GetMouseButtonPress(MouseKey nMouseKey);
	bool GetMouseButtonTrigger(MouseKey nMouseKey);
	bool GetMouseButtonRelease(MouseKey nMouseKey);
	bool GetMouseButtonRepeat(MouseKey nMouseKey);

	POINT GetMousePosition();//�X�N���[�����W�擾
	D3DXVECTOR3 GetMouseRayIntersection(const CCamera& camera);//�X�N���[�����W��3D��ԍ��W�����_�v�Z
	D3DXVECTOR3 GetScreenPosRayIntersection(const CCamera& camera,D3DXVECTOR3 Pos);//�X�N���[���ʒu���RD��ԍ��W�ɕϊ�

private:
	BYTE m_akeyState[MAX_KEY] = {};
	BYTE m_akeyTriggerState[MAX_KEY] = {};
	BYTE m_akeyReleaseState[MAX_KEY] = {};
	BYTE m_akeyRepeatState[MAX_KEY] = {};

	//�}�E�X�n
	LPDIRECTINPUTDEVICE8 m_pMouse = {};  // �}�E�X�f�o�C�X
	DIMOUSESTATE m_mouseState = {};
	DIMOUSESTATE m_prevMouseState = {};

	//�e���͕����̃X�e�[�g
	bool m_mouseButtonState[4] = {};
	bool m_mouseButtonTriggerState[4] = {};
	bool m_mouseButtonReleaseState[4] = {};
	bool m_mouseButtonRepeatState[4] = {};
};


//�p�b�h����^
class CInputJoyPad : CInput
{
public:
	typedef enum
	{
		JOYKEY_UP = 0,			//�\���L�[��
		JOYKEY_DOWN,			//�\���L�[��
		JOYKEY_LEFT,			//�\���L�[��
		JOYKEY_RIGHT,			//�\���L�[�E
		JOYKEY_START,			//�X�^-�g
		JOYKEY_BACK,			//�o�b�N
		JOYKEY_LPUSH,			//L�g���K�[
		JOYKEY_RPUSH,			//R�g���K�[
		JOYKEY_L1,				//L1�{�^��
		JOYKEY_R1,				//R1�{�^��
		JOYKEY_L2,				//L2�{�^��
		JOYKEY_R2,				//R2�{�^��
		JOYKEY_A,				//A�{�^��
		JOYKEY_B,				//B�{�^��
		JOYKEY_X,				//X�{�^��
		JOYKEY_Y,				//Y�{�^��
		JOYKEY_MAX,
	}JOYkey;


	CInputJoyPad();//�R���X�g���N�^
	~CInputJoyPad();//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	void Uninit();
	void Update();

	//�e���͕���
	bool GetPress(JOYkey nKey);
	bool GetTrigger(JOYkey nKey);
	bool GetRelease(JOYkey nKey);
	bool GetRepeat(JOYkey nKey);


	//�R���g���[���[�U������
	void VibrationLeft(int MotorSpeed);
	void VibrationRight(int MotorSpeed);

	// �W���C�p�b�h�̐ڑ��L�����m�F����֐��̐錾
	bool IsJoyPadConnected();

private:
	XINPUT_STATE m_JoykeyState;								//�Q�[���p�b�h�̃v���X���
	XINPUT_STATE m_JoykeyStateTrigger;						//�Q�[���p�b�h�̃g���K�[���
	XINPUT_STATE m_JoykeyStateRelease;						//�Q�[���p�b�h�̃����[�X���
	XINPUT_STATE m_JoykeyStateRepeat;						//�Q�[���p�b�h�̃��s�[�g���

};
#endif