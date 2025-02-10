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
// �R���X�g���N�^
//=============================
CPlayer3D::CPlayer3D(int nPriority) :CObjectX(nPriority)
{
}

//=============================
//�f�X�g���N�^
//=============================
CPlayer3D::~CPlayer3D()
{
}

//=============================
//������
//=============================
HRESULT CPlayer3D::Init()
{
	CObjectX::Init();
    CRenderer* pRenderer = nullptr;
    CManager* pManager = CManager::GetInstance();
    pRenderer = pManager->GetRenderer();

    LPD3DXMESH pMesh = nullptr;//Mesh�|�C���^
    LPD3DXBUFFER pBuffMat = nullptr;//�}�e���A���ւ̃|�C���^
    DWORD dwNumMat = 0;//�}�e���A���̐�

    LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
    //�t�@�C���̓ǂݍ���
    D3DXLoadMeshFromX("DATA\\MODEL\\TestTank_NoMotion.x",
        D3DXMESH_SYSTEMMEM,
        EscDevice,
        NULL,
        &pBuffMat,
        NULL,
        &dwNumMat,
        &pMesh);

    SetXfireData(pMesh, pBuffMat, dwNumMat);//�f�[�^�i�[

    SetObjectType(CObject::OBJECT_PLAYER3D);

    SetSizeMag(D3DXVECTOR3(1.0f, 1.0f, 1.0f));//�傫���{��

	//�擾
	DATA EscData = GetDATA();
	EscData = GetDATA();//�Ď擾
	EscData.MinLength = D3DXVECTOR3(-50.0f, -50.0f,-50.0f);
	EscData.MaxLength = D3DXVECTOR3(50.0f, 50.0f, 50.0f);
	EscData.rot.y = D3DX_PI;

	SetDATA(EscData);//�i�[

    return S_OK;
}

//=============================
//�j��
//=============================
void CPlayer3D::Uninit()
{
    CObjectX::Uninit();
}

//=============================
//�X�V
//=============================
void CPlayer3D::Update()
{
	//�擾
	DATA EscData = GetDATA();
	EscData = GetDATA();//�Ď擾

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	if (JoyPad->IsJoyPadConnected())//�ڑ���
	{
		Action_JoyPad(); // �W���C�p�b�h����
		Action_Keyboard();
	}
	else
	{
		Action_Keyboard();
	}

	EscData = GetDATA();//�Ď擾

	EscData.OldPos = EscData.Pos;
	EscData.Pos += EscData.move;

	SetDATA(EscData);//�i�[

	HitCollision();

	EscData = GetDATA();//�Ď擾

	bool bHit = false;

	//�ړ��ʂ��X�V(�^�������Ō���)
	EscData.move.x += (0.0f - EscData.move.x) * (DAMPING_RATIO);
	EscData.move.y += (0.0f - EscData.move.y) * (DAMPING_RATIO);
	EscData.move.z += (0.0f - EscData.move.z) * (DAMPING_RATIO);

    SetDATA(EscData);//�i�[
    
    CObjectX::Update();
}

//=============================
//�`��
//=============================
void CPlayer3D::Draw()
{
    SizeMagChangebool(true);
    CObjectX::Draw();
}

//=============================
//����
//=============================
CPlayer3D* CPlayer3D::Create()
{
	CPlayer3D* pPlayer3D = new CPlayer3D;
	pPlayer3D->Init();
	return pPlayer3D;
}

//=============================
//�����tKeyboard
//=============================
void CPlayer3D::Action_Keyboard()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* keyboard = pManager->GetKeyboard();

	//---------------------------------------------------------�ړ��n
	//�擾
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

	SetDATA(EscData);//�i�[
}

//=============================
//�����t�W���C�p�b�h
//=============================
void CPlayer3D::Action_JoyPad()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputJoyPad* JoyPad = pManager->GetJoyPad();
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);
	//�擾
	DATA EscData = GetDATA();

	float MoveSpeed = 0.2f;

	bool bMove = false;

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//A�������ꂽ(��)

		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//D�������ꂽ(�E)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//W�������ꂽ(��)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//S�������ꂽ(��)
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
		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbLX, (float)-joykeystate.Gamepad.sThumbLY);//���ꂪ���p

		EscData.move.x = sinf(Angle2 - (1.0f * D3DX_PI)) * MoveSpeed * 10.0f;//�O�p�֐����p���Ĉړ��̒�������
		EscData.move.z = cosf(Angle2 - (1.0f * D3DX_PI)) * MoveSpeed * 10.0f;//�O�p�֐����p���Ĉړ��̒�������

	}

	bool bMove2 = false;

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//A�������ꂽ(��)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//D�������ꂽ(�E)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//W�������ꂽ(��)
		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//S�������ꂽ(��)
		bMove = true;
	}

	if (bMove == true)
	{
		float Angle2 = atan2f((float)joykeystate.Gamepad.sThumbRX, (float)-joykeystate.Gamepad.sThumbRY);//���ꂪ���p
		EscData.rot.y = (-Angle2);
	}

	if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) == true)
	{
			EscData.move.y = cosf(-0.75f * D3DX_PI) * (2.0f * 15.0f);
	}

	//���̗͂L�����m�F���ĕ���
	if (joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD || joykeystate.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)//�g���K�[
	{//L2�L�[
	}

	SetDATA(EscData);//�i�[
}

//=============================
//�����蔻��܂Ƃ�
//=============================
void CPlayer3D::HitCollision()
{
}

//=============================
//�f�[�^�擾(player�͂悭�g�p����)
//=============================
CObject::DATA CPlayer3D::GetPlayerData()
{
	//�擾
	DATA EscData = GetDATA();
	return EscData;
}