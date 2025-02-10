//=========================================================
//
// input.cppで使う関数[input.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _INPUT_H
#define _INPUT_H//二重インクルード防止

#include "main.h"
#include "camera.h"

#define MAX_KEY	(256)//最大キー数

class CInput
{
public:
	CInput();//コンストラクタ
	~CInput();//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	virtual void Uninit();
	virtual void Update() = 0;
	
protected:

	//	全入力処理で共有
	static	LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevicce = {};

	//大事
	HWND m_hWnd{};
};


//キーボード系
class CInputKeyboard : CInput
{
public:

	CInputKeyboard();//コンストラクタ
	~CInputKeyboard();//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	void Uninit();
	void Update();

	//各入力判定
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

	//マウス系
	 typedef enum
	{
		MouseKey_Left=0,
		MouseKey_Right,
		MouseKey_Center,
		MouseKey_Fourth,
	}MouseKey;

	//0：左ボタン（通常の左クリック）
	//1：右ボタン（通常の右クリック）
	//2：中央ボタン（通常のホイールクリック）
	//3：第4ボタン（サイドボタンの一つ。通常は「戻る」ボタンとして使われることが多い）
		
	bool GetMouseButtonPress(MouseKey nMouseKey);
	bool GetMouseButtonTrigger(MouseKey nMouseKey);
	bool GetMouseButtonRelease(MouseKey nMouseKey);
	bool GetMouseButtonRepeat(MouseKey nMouseKey);

	POINT GetMousePosition();//スクリーン座標取得
	D3DXVECTOR3 GetMouseRayIntersection(const CCamera& camera);//スクリーン座標と3D空間座標交差点計算
	D3DXVECTOR3 GetScreenPosRayIntersection(const CCamera& camera,D3DXVECTOR3 Pos);//スクリーン位置を３D空間座標に変換

private:
	BYTE m_akeyState[MAX_KEY] = {};
	BYTE m_akeyTriggerState[MAX_KEY] = {};
	BYTE m_akeyReleaseState[MAX_KEY] = {};
	BYTE m_akeyRepeatState[MAX_KEY] = {};

	//マウス系
	LPDIRECTINPUTDEVICE8 m_pMouse = {};  // マウスデバイス
	DIMOUSESTATE m_mouseState = {};
	DIMOUSESTATE m_prevMouseState = {};

	//各入力方式のステート
	bool m_mouseButtonState[4] = {};
	bool m_mouseButtonTriggerState[4] = {};
	bool m_mouseButtonReleaseState[4] = {};
	bool m_mouseButtonRepeatState[4] = {};
};


//パッド操作型
class CInputJoyPad : CInput
{
public:
	typedef enum
	{
		JOYKEY_UP = 0,			//十字キー上
		JOYKEY_DOWN,			//十字キー下
		JOYKEY_LEFT,			//十字キー左
		JOYKEY_RIGHT,			//十字キー右
		JOYKEY_START,			//スタ-ト
		JOYKEY_BACK,			//バック
		JOYKEY_LPUSH,			//Lトリガー
		JOYKEY_RPUSH,			//Rトリガー
		JOYKEY_L1,				//L1ボタン
		JOYKEY_R1,				//R1ボタン
		JOYKEY_L2,				//L2ボタン
		JOYKEY_R2,				//R2ボタン
		JOYKEY_A,				//Aボタン
		JOYKEY_B,				//Bボタン
		JOYKEY_X,				//Xボタン
		JOYKEY_Y,				//Yボタン
		JOYKEY_MAX,
	}JOYkey;


	CInputJoyPad();//コンストラクタ
	~CInputJoyPad();//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	void Uninit();
	void Update();

	//各入力方式
	bool GetPress(JOYkey nKey);
	bool GetTrigger(JOYkey nKey);
	bool GetRelease(JOYkey nKey);
	bool GetRepeat(JOYkey nKey);


	//コントローラー振動処理
	void VibrationLeft(int MotorSpeed);
	void VibrationRight(int MotorSpeed);

	// ジョイパッドの接続有無を確認する関数の宣言
	bool IsJoyPadConnected();

private:
	XINPUT_STATE m_JoykeyState;								//ゲームパッドのプレス情報
	XINPUT_STATE m_JoykeyStateTrigger;						//ゲームパッドのトリガー情報
	XINPUT_STATE m_JoykeyStateRelease;						//ゲームパッドのリリース情報
	XINPUT_STATE m_JoykeyStateRepeat;						//ゲームパッドのリピート情報

};
#endif