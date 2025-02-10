//=========================================================
//
// player3D[player3D.cpp]
// Author seiya kagaya
//
//=========================================================
#include "player3D.h"
#include "renderer.h"
#include "manager.h"

//=============================
// コンストラクタ
//=============================
CPlayer3D::CPlayer3D(int nPriority) :CObjectX(nPriority)
{
}

//=============================
//デストラクタ
//=============================
CPlayer3D::~CPlayer3D()
{
}

//=============================
//初期化
//=============================
HRESULT CPlayer3D::Init()
{
	CObjectX::Init();
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr;//Meshポインタ
    LPD3DXBUFFER pBuffMat = nullptr;//マテリアルへのポインタ
    DWORD dwNumMat = 0;//マテリアルの数

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    //ファイルの読み込み
    D3DXLoadMeshFromX("DATA\\MODEL\\TestTank_NoMotion.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    SetXfireData(pMesh, pBuffMat, dwNumMat);//データ格納

    SetObjectType(CObject::OBJECT_PLAYER3D);

    SetSizeMag(D3DXVECTOR3(1.0f, 1.0f, 1.0f));//大きさ倍率

	//取得
	DATA EscData = GetDATA();
	EscData = GetDATA();//再取得
	EscData.MinLength = D3DXVECTOR3(-50.0f, -50.0f,-50.0f);
	EscData.MaxLength = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	EscData.rot.y = D3DX_PI;

	SetDATA(EscData);//格納

    return S_OK;
}

//=============================
//破棄
//=============================
void CPlayer3D::Uninit()
{
    CObjectX::Uninit();
}

//=============================
//更新
//=============================
void CPlayer3D::Update()
{
	//取得
	DATA EscData = GetDATA();
	EscData = GetDATA();//再取得

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	if (JoyPad->IsJoyPadConnected())//接続時
	{
		Action_JoyPad(); // ジョイパッド操作
		Action_Keyboard();
	}
	else
	{
		Action_Keyboard();
	}

	EscData = GetDATA();//再取得

	EscData.OldPos = EscData.Pos;
	EscData.Pos += EscData.move;

	SetDATA(EscData);//格納

	HitCollision();

	EscData = GetDATA();//再取得

	bool bHit = false;

	//移動量を更新(疑似慣性で減衰)
	EscData.move.x += (0.0f - EscData.move.x) * (DAMPING_RATIO);
	EscData.move.y += (0.0f - EscData.move.y) * (DAMPING_RATIO);
	EscData.move.z += (0.0f - EscData.move.z) * (DAMPING_RATIO);

    SetDATA(EscData);//格納
    
    CObjectX::Update();
}

//=============================
//描画
//=============================
void CPlayer3D::Draw()
{
    SizeMagChangebool(true);
    CObjectX::Draw();
}

//=============================
//生成
//=============================
CPlayer3D* CPlayer3D::Create()
{
	CPlayer3D* pPlayer3D = new CPlayer3D;
	pPlayer3D->Init();
	return pPlayer3D;
}

//=============================
//操作受付Keyboard
//=============================
void CPlayer3D::Action_Keyboard()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* keyboard = pManager->GetKeyboard();

	//---------------------------------------------------------移動系
	//取得
	DATA EscData = GetDATA();

	float MoveSpeed = 4.5f;

	if (keyboard->GetPress(DIK_W) == true)
	{
		EscData.move.z += MoveSpeed;
	}
	if (keyboard->GetPress(DIK_A) == true)
	{
		EscData.move.x += -MoveSpeed;
	}
	if (keyboard->GetPress(DIK_S) == true)
	{
		EscData.move.z += -MoveSpeed;
	}
	if (keyboard->GetPress(DIK_D) == true)
	{
		EscData.move.x += MoveSpeed;
	}

	if (keyboard->GetPress(DIK_LEFT) == true)
	{
		EscData.rot.z += 0.03f;
	}
	if (keyboard->GetPress(DIK_RIGHT) == true)
	{
		EscData.rot.z -= 0.03f;
	}

	SetDATA(EscData);//格納
}

//=============================
//操作受付ジョイパッド
//=============================
void CPlayer3D::Action_JoyPad()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputJoyPad* JoyPad = pManager->GetJoyPad();
	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);
	//取得
	DATA EscData = GetDATA();

	float MoveSpeed = 0.2f;

	bool bMove = false;

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)

		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Dがおされた(右)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Wがおされた(上)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Sがおされた(下)
		bMove = true;
	}

	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_UP) == true)
	{
		EscData.move.z += MoveSpeed;

	}
	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_LEFT) == true)
	{
		EscData.move.x += -MoveSpeed;
	}
	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_DOWN) == true)
	{
		EscData.move.z += -MoveSpeed;
	}
	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_RIGHT) == true)
	{
		EscData.move.x += MoveSpeed;
	}

	if (bMove == true)
	{
		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbLX, (float)-joykeystate.Gamepad.sThumbLY);//これが方角

		EscData.move.x = sinf(Angle2 - (1.0f * D3DX_PI)) * MoveSpeed * 10.0f;//三角関数利用して移動の長さを代入
		EscData.move.z = cosf(Angle2 - (1.0f * D3DX_PI)) * MoveSpeed * 10.0f;//三角関数利用して移動の長さを代入

	}

	bool bMove2 = false;

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Dがおされた(右)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Wがおされた(上)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Sがおされた(下)
		bMove = true;
	}

	if (bMove == true)
	{
		float Angle2 = atan2f((float)joykeystate.Gamepad.sThumbRX, (float)-joykeystate.Gamepad.sThumbRY);//これが方角
		EscData.rot.y = (-Angle2);
	}

	if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) == true)
	{
			EscData.move.y = cosf(-0.75f * D3DX_PI) * (2.0f * 15.0f);
	}

	//入力の有無を確認して分岐
	if (joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD || joykeystate.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)//トリガー
	{//L2キー
	}

	SetDATA(EscData);//格納
}

//=============================
//当たり判定まとめ
//=============================
void CPlayer3D::HitCollision()
{
}

//=============================
//データ取得(playerはよく使用する)
//=============================
CObject::DATA CPlayer3D::GetPlayerData()
{
	//取得
	DATA EscData = GetDATA();
	return EscData;
}