//=======================================================
//
//polygon�Ɋւ��鏈��[polygon.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "player.h"
#include "renderer.h"
#include "main.h"
#include "manager.h"
#include "input.h"
#include"ballet.h"
#include <cmath> // �O�p�֐����g�����߂ɕK�v
#include "all_texture.h"

//=============================
//�R���X�g���N�^
//=============================
CPlayer::CPlayer(int nPriority) :CObject2D(nPriority), m_nCounterAnim(0), m_nDirectionMove(1), m_nPatternAnim(0), m_MAG(0.3f), m_bLandingNow(false)
{
	m_HitData.bHit = false;
	m_HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	m_HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_HitData.targetIndex = -1;

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
	
	//�擾
	DATA EscData = GetDATA();
	EscData.Pos = D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 2.0f, 0.0f);
	SetDATA(EscData);//�i�[

	SetObjectType(CObject2D::OBJECT_PLAYER);
}

//=============================
//�f�X�g���N�^
//=============================
CPlayer::~CPlayer()
{
}

//=============================
//�����ݒ�(���_�o�b�t�@����)
//=============================
HRESULT CPlayer::Init()
{
	CObject2D::Init();//��{�ݒ�
	//�擾
	LPDIRECT3DVERTEXBUFFER9 ESCpVtxBuff = GetpVtxBuffer();

	VERTEX_2D* pVtx;
	ESCpVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o
	m_fLength = sqrtf(PLAYER_HEIGHT * PLAYER_HEIGHT * m_MAG + PLAYER_WIDE * PLAYER_WIDE * m_MAG) / 2.0f;//��*��+����*����

	//�Ίp���̊p�x���Z�o
	m_fAngle = atan2f(PLAYER_WIDE * m_MAG, PLAYER_HEIGHT * m_MAG);//�����A��

	//�擾
	DATA EscData = GetDATA();
	EscData.Radius = m_fLength;
	EscData.MinLength = D3DXVECTOR3(-PLAYER_WIDE/2, -PLAYER_HEIGHT/2, 0.0f);//����
	EscData.MaxLength = D3DXVECTOR3(PLAYER_WIDE/2, PLAYER_HEIGHT/2, 0.0f);//����

	SetDATA(EscData);//�i�[

	pVtx[0].pos.x = EscData.Pos.x - PLAYER_WIDE / 2;//����
	pVtx[0].pos.y = EscData.Pos.y - PLAYER_HEIGHT / 2;//����
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = EscData.Pos.x + PLAYER_WIDE / 2;//�E��
	pVtx[1].pos.y = EscData.Pos.y - PLAYER_HEIGHT / 2;//�E��
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = EscData.Pos.x - PLAYER_WIDE / 2;//����
	pVtx[2].pos.y = EscData.Pos.y + PLAYER_HEIGHT / 2;//����
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = EscData.Pos.x + PLAYER_WIDE / 2;//�E��
	pVtx[3].pos.y = EscData.Pos.y + PLAYER_HEIGHT / 2;//�E��
	pVtx[3].pos.z = 0.0f;

	//�e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * m_nDirectionMove));//����//�j���[�g�����̏��
	pVtx[1].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * m_nDirectionMove));//�E��
	pVtx[2].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//����
	pVtx[3].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//�E��

	ESCpVtxBuff->Unlock();
		
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();
	
	//�e�N�X�`���ǂݍ���
	LPDIRECT3DTEXTURE9	m_ESCpTexture = nullptr;

	//�e�N�X�`���擾
	CAllTexture* pTexture = pManager->GetTexture();

	int texIndex = pTexture->Regist("DATA\\TEXTURE\\Player001.png", EscDevice);//�e�N�X�`���o�^

	m_ESCpTexture = pTexture->GetAddress(texIndex);
	BindTexture(m_ESCpTexture);//�ݒ�

	SetDATA(EscData);//�i�[

	SetObjectType(CObject2D::OBJECT_PLAYER);

	return S_OK;
}

//=============================
//�I������(���_�o�b�t�@�j��)
//=============================
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//=============================
//�X�V(���_���̍X�V)
//=============================
void CPlayer::Update()
{
	bool HitData = false;
	
	//�擾
	DATA EscData = GetDATA();

	Action_Keyboard();//Keyboard����
	
	EscData = GetDATA();//�Ď擾

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	if (JoyPad->IsJoyPadConnected())//�ڑ���
	{
		Action_JoyPad(); // �W���C�p�b�h����
	}

	EscData = GetDATA();//�Ď擾
	EscData.OldPos = EscData.Pos;
	EscData.Pos += EscData.move;

	m_nPatternAnim++;

	if (m_bLandingNow == false)
	{
		EscData.move.y += 0.9f;//�����d��
	}
	
	m_bLandingNow = false;//���nReset

	SetDATA(EscData);//�i�[

	HitCollision();

	EscData = GetDATA();//�Ď擾

	bool bHit = false;

	if (EscData.Pos.x+ PLAYER_WIDE/2 >=SCREEN_WIDTH)
	{//�E
		EscData.Pos.x = SCREEN_WIDTH - (PLAYER_WIDE / 2.0f  - DISTANCE);
		bHit = true;
	}
	else if (EscData.Pos.x - PLAYER_WIDE / 2.0f <= 0)
	{//��
		EscData.Pos.x =(PLAYER_WIDE / 2.0f + DISTANCE);
		bHit = true;
	}
	if (EscData.Pos.y +DISTANCE>= SCREEN_HEIGHT)
	{//��
		EscData.Pos.y = SCREEN_HEIGHT - (DISTANCE* 2.0f);

		bHit = true;
		m_bLandingNow = true;
	}
	else if (EscData.Pos.y - PLAYER_HEIGHT/ 2.0f <= 0)
	{//��
		EscData.Pos.y = (PLAYER_HEIGHT/ 2.0f + DISTANCE);
		bHit = true;
	}

	//�ړ��ʂ��X�V(�^�������Ō���)
	EscData.move.x += (0.0f - EscData.move.x) * 0.1f;

	SetDATA(EscData);//�i�[
	InputpVtx();//�|���S���X�V
	CObject2D::Update();
}

//=============================
//�`�揈��(POLYGON�`��)
//=============================
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//=============================
//Object����
//=============================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = new CPlayer;
	pPlayer->Init();

	return pPlayer;
}

//=============================
//�ݒ�i�[
//=============================
void CPlayer::InputpVtx()
{
	//�擾
	DATA EscData = GetDATA();
	VERTEX_2D EscVtx[BASE_INDEX];

	EscVtx[0].pos.x = EscData.Pos.x - PLAYER_WIDE / 2;//����
	EscVtx[0].pos.y = EscData.Pos.y - PLAYER_HEIGHT / 2;//����
	EscVtx[0].pos.z = 0.0f;

	EscVtx[1].pos.x = EscData.Pos.x + PLAYER_WIDE / 2;//�E��
	EscVtx[1].pos.y = EscData.Pos.y - PLAYER_HEIGHT / 2;//�E��
	EscVtx[1].pos.z = 0.0f;

	EscVtx[2].pos.x = EscData.Pos.x - PLAYER_WIDE / 2;//����
	EscVtx[2].pos.y = EscData.Pos.y + PLAYER_HEIGHT / 2;//����
	EscVtx[2].pos.z = 0.0f;

	EscVtx[3].pos.x = EscData.Pos.x + PLAYER_WIDE / 2;//�E��
	EscVtx[3].pos.y = EscData.Pos.y + PLAYER_HEIGHT / 2;//�E��
	EscVtx[3].pos.z = 0.0f;

	//�e�N�X�`�����W���X�V
	EscVtx[0].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * m_nDirectionMove));//����//�j���[�g�����̏��
	EscVtx[1].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * m_nDirectionMove));//�E��
	EscVtx[2].tex = D3DXVECTOR2(((1.0f / 4) * m_nPatternAnim), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//����
	EscVtx[3].tex = D3DXVECTOR2(((1.0f / 4) * (m_nPatternAnim + 1.0f)), ((1.0f / 2) * (m_nDirectionMove + 1.0f)));//�E��

	SetpVtx(EscVtx);
}

//=============================
//�����tKeyboard
//=============================
void CPlayer::Action_Keyboard()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* keyboard = pManager->GetKeyboard();

	//---------------------------------------------------------�ړ��n
	//�擾
	DATA EscData = GetDATA();

	float MoveSpeed = 1.0f;

	if (keyboard->GetPress(DIK_W) == true)
	{
		EscData.move.y += -MoveSpeed;
	
	}
	if (keyboard->GetPress(DIK_A) == true)
	{
		EscData.move.x += -MoveSpeed;
		m_nDirectionMove = 1;
	}
	if (keyboard->GetPress(DIK_S) == true)
	{
		EscData.move.y += MoveSpeed;
	}
	if (keyboard->GetPress(DIK_D) == true)
	{
		EscData.move.x += MoveSpeed;
		m_nDirectionMove = 0;
	}

	if (keyboard->GetTrigger(DIK_SPACE) == true)
	{
		EscData.move.y = cosf(-0.75f * D3DX_PI) * (2.0f * 15.0f);
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

	//---------------------------------------------------------�ړ��n�����܂�
	if (keyboard->GetPress(DIK_N) == true)
	{
		if (MAXSHOTDERAY <= m_BulletShotDelay)
		{
			DATA SetData;
			SetData.Pos = EscData.Pos + D3DXVECTOR3(0.0f, -35.0f, 0.0f);

			SetData.move = D3DXVECTOR3(cos(-EscData.rot.z * D3DX_PI), sin(-EscData.rot.z * D3DX_PI), 0.0f);//�p�x����
			CBullet::Create(SetData);

			m_BulletShotDelay = 0;
		}
		else
		{
			m_BulletShotDelay++;
		}
	}

	if (keyboard->GetTrigger(DIK_DOWN) == true)
	{
		DATA SetData;
		SetData.Pos = EscData.Pos;
		SetData.move = D3DXVECTOR3(cos(-EscData.rot.z * D3DX_PI), sin(-EscData.rot.z * D3DX_PI), 0.0f);//�p�x����

		CBullet::Create(SetData);
	}

	SetDATA(EscData);//�i�[
}

//=============================
//�����t�W���C�p�b�h
//=============================
void CPlayer::Action_JoyPad()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputJoyPad* JoyPad = pManager->GetJoyPad();
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	//�擾
	DATA EscData = GetDATA();

	float MoveSpeed = 1.0f;

	bool bMove = false;

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//A�������ꂽ(��)
		m_nDirectionMove = 1;

		bMove = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//D�������ꂽ(�E)
		m_nDirectionMove = 0;
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
		EscData.move.y += -MoveSpeed;
	}
	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_LEFT) == true)
	{
		EscData.move.x += -MoveSpeed;
		m_nDirectionMove = 1;
	}
	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_DOWN) == true)
	{
		EscData.move.y += MoveSpeed;
	}
	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_RIGHT) == true)
	{
		EscData.move.x += MoveSpeed;
		m_nDirectionMove = 0;
	}

	if (bMove == true)
	{
		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbLX, (float)-joykeystate.Gamepad.sThumbLY);//���ꂪ���p

		EscData.move.x = sinf(Angle2 - (1.0f * D3DX_PI)) * MoveSpeed * 10.0f;//�O�p�֐����p���Ĉړ��̒�������
		EscData.move.y = -cosf(Angle2 - (1.0f * D3DX_PI)) * MoveSpeed * 10.0f;//�O�p�֐����p���Ĉړ��̒�������
	
	}

	bool bMove2= false;

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
		EscData.rot.z = (Angle2/D3DX_PI)+ 1.5f;
	}

	if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A)== true)
	{
		EscData.move.y = cosf(-0.75f * D3DX_PI) * (2.0f * 15.0f);
	}

	//���̗͂L�����m�F���ĕ���
	if (joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD || joykeystate.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)//�g���K�[
	{//L2�L�[
	
		if (MAXSHOTDERAY <= m_BulletShotDelay)
		{
			DATA SetData;
			SetData.Pos = EscData.Pos + D3DXVECTOR3(0.0f, -35.0f, 0.0f);

			SetData.move = D3DXVECTOR3(cos(-EscData.rot.z * D3DX_PI), sin(-EscData.rot.z * D3DX_PI), 0.0f);//�p�x����
			CBullet::Create(SetData);

			m_BulletShotDelay = 0;
		}
		else
		{
			m_BulletShotDelay++;
		}
	}
	SetDATA(EscData);//�i�[
}
//=============================
//�����蔻��܂Ƃ�
//=============================
void CPlayer::HitCollision()
{
	//�擾
	DATA EscData = GetDATA();

	//�����蔻��v�Z
	m_HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_BLOCK);

	if (m_HitData.bHit == true)
	{//�ڐG
		if (m_HitData.HitAngle.x == 1)
		{//�E
			EscData.Pos.x += m_HitData.ResultDistance.x;

			EscData.move.x = 0.0f;
		}
		else if (m_HitData.HitAngle.x == -1)
		{//��
			EscData.Pos.x -= m_HitData.ResultDistance.x;
			EscData.move.x = 0.0f;
		}
		else if (m_HitData.HitAngle.y == 1)
		{//��
 			EscData.Pos.y += m_HitData.ResultDistance.y;

			EscData.move.y = 0.0f;
		}
		else if (m_HitData.HitAngle.y == -1)
		{//��
			EscData.Pos.y -= m_HitData.ResultDistance.y;
			EscData.move.y = 0.0f;
		}
	}

	SetDATA(EscData);//�i�[

	//����Reset
	m_HitData.bHit = false;

	//�����蔻��v�Z
	m_HitData = CMathProc::CheckBoxCollision_2D(EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject2D::OBJECT_ITEM);

}