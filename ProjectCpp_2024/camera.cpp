//============================================================================================
//
//�J�������Ǘ����鏈��[camera.cpp]
// Author seiya kagaya
//
//============================================================================================
#include "camera.h"
#include "input.h"
//#include "player.h"
#include "renderer.h"
#include "manager.h"
//#include "player3D.h"
#include <time.h>
//#include "object_motion.h"
#include "player_motion.h"
#include "enemy_motion_fast.h"
#include "enemy_motion_Nomal.h"
#include "ObstacleSet.h"

#define NOMINMAX
#include <windows.h>
#undef min//���h�~
#undef max
#include <algorithm>

D3DXVECTOR3 CCamera::CameraPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

float CCamera::m_Screen_Width = (float)SCREEN_WIDTH;//�X�N���[������
float CCamera::m_Screen_Height = (float)SCREEN_HEIGHT;//�X�N���[���c��

//=============================
//�R���X�g���N�^
//=============================
CCamera::CCamera()
{
	// ���݂̎��Ԃ��V�[�h�l�Ƃ��Đݒ�
	srand(static_cast<unsigned int>(time(0)));

}
//=============================
//�f�X�g���N�^
//=============================
CCamera::~CCamera()
{
}
//=============================
//������
//=============================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(700.0f, 800.0f, 0.0f);//���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_nShakeFlame = 0;
	m_fMag = 0.0f;


	//for (int i = 0; i < 8; i++)
	//{
	//	m_LockOnUI[i] = CLockOnUI::Create();
	//}


	//m_LockOnUI_Main = CLockOnUIMain::Create();


	return S_OK;
}
//=============================
//�I��
//=============================
void CCamera::Uninit()
{
	//for (int i = 0; i < 8; i++)
	//{
	//	if (m_LockOnUI[i] != nullptr)
	//	{
	//		delete m_LockOnUI[i];
	//		m_LockOnUI[i] = nullptr;
	//	}
	//}

	//if (m_LockOnUI_Main != nullptr)
	//{
	//	delete m_LockOnUI_Main;
	//	m_LockOnUI_Main = nullptr;
	//}
}
//=============================
//�X�V
//=============================
void CCamera::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();


	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_TITLE || NowState == CScene::MODE_TUTORIAL)
	{//�Q�[��/OP/tutorial

		CManager* pManager = CManager::GetInstance();

		if (pManager->GetbNow3DMode() == false)
		{//2D
			ActionUpdate2D();
		}
		else
		{//3D
			ActionUpdate3D();//�����Ƀ��b�N�I���n���͂����Ă���
		}



	}
	else if (NowState == CScene::MODE_OP)
	{
	//	float fLength;


	//	m_posV= D3DXVECTOR3(4000.0f, 5500.0f, 4000.0f);

	//	m_posR = D3DXVECTOR3(5000.0f, 5150.0f, 5000.0f);;
	//	

	//	fLength = 700.0f;

	//	m_posV.x += m_Move.x;
	//	m_posV.y += m_Move.y;
	//	m_posV.z -= m_Move.z;

	//	m_rot.x += m_rotMove.x;
	//	m_rot.y += m_rotMove.y;
	//	m_rot.z += m_rotMove.z;

	//	if (m_rot.x > D3DX_PI * 0.25f)//���񐧌�
	//	{
	//		m_rot.x = D3DX_PI * 0.24999f;
	//	}
	//	if (m_rot.x < -D3DX_PI * 0.35f)
	//	{
	//		m_rot.x = -D3DX_PI * 0.34999f;
	//	}

	//	if (m_rot.y < -3.14f)
	//	{
	//		m_rot.y = 3.14f;
	//	}
	//	else if (m_rot.y > 3.14f)
	//	{
	//		m_rot.y = -3.14f;
	//	}


	//	//��������p�x								//
	//	m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1�R�T�C���V�[�^��������--�R�T�C���t�@�C��������
	//	m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Y�͕��Ղ̂��߂����Ȃ�
	//	m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//�P�Ɠ�������
	//	//posR��			������PosV	������+�ɕύX


	////�ړ��ʂ��X�V(�^�������Ō���)
	//	m_Move.x += (0.0f - m_Move.x) * CAMERA_MOVE_DAMPING_RATIO;
	//	m_Move.y += (0.0f - m_Move.y) * CAMERA_MOVE_DAMPING_RATIO;
	//	m_Move.z += (0.0f - m_Move.z) * CAMERA_MOVE_DAMPING_RATIO;


	//	m_rotMove.x += (0.0f - m_rotMove.x) * CAMERA_ROT_DAMPING_RATIO;
	//	m_rotMove.y += (0.0f - m_rotMove.y) * CAMERA_ROT_DAMPING_RATIO;
	//	m_rotMove.z += (0.0f - m_rotMove.z) * CAMERA_ROT_DAMPING_RATIO;



	//	//	m_posR.z += 150.0f;
	//	CameraPos = m_posV;



		ActionUpdate3D();
	}





}
//=============================
//�X�V--2D
//=============================
void  CCamera::ActionUpdate2D()
{
	float fLength;

	m_posR = D3DXVECTOR3(0.0f, 25.0f, 0.0f);

	//�J��������	
	fLength = 3250.0f * 0.16f;

	//�p�x�ɂ��ʒu����
	m_rot.x = -0.42f;
	m_rot.y = 0.0f;
	m_rot.z = 0.0f;



	//player�̈ʒu���擾
	CObject* pObj = nullptr;
	pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);

		CObject::DATA EscData;

		EscData = pPlayer->GetClassData();

		m_posR = EscData.Pos;//�����_

	}

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	if (keyboard->GetPress(DIK_4) == true)
	{//
		m_CameraType = false;
	}
	else if (keyboard->GetPress(DIK_5) == true)
	{//
		m_CameraType = true;
	}

	CScene::MODE NowState = CScene::GetNowScene();


	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2)
	{//�Q�[����
	//�J��������	

		if (m_CameraType == false)
		{
			m_posR.y += 50.0f;
			fLength = 3250.0f * 0.65f;

			//�p�x�ɂ��ʒu����
			m_rot.x = 0.0f;
			m_rot.y = 0.0f;
			m_rot.z = 0.0f;


		}
		else
		{
			m_posR.y += 50.0f;
			fLength = 3250.0f * 0.95f;

			//�p�x�ɂ��ʒu����
			m_rot.x = -1.35f;
			m_rot.y = 0.0f;
			m_rot.z = 0.0f;


		}

	}
	else if (NowState == CScene::MODE_TITLE || NowState == CScene::MODE_RESULT)
	{//�^�C�g��
		m_posR = D3DXVECTOR3(0.0f, 165.0f, 0.0f);

		//�J��������	
		fLength = 3250.0f * 0.29f;

		//�p�x�ɂ��ʒu����
		m_rot.x = -0.42f;
		m_rot.y = 0.0f;
		m_rot.z = 0.0f;
	}





	//��������p�x								//
	m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1�R�T�C���V�[�^��������--�R�T�C���t�@�C��������
	m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Y�͕��Ղ̂��߂����Ȃ�
	m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//�P�Ɠ�������
	//posR��			������PosV	������+�ɕύX

//	m_posR.z += 150.0f;
	CameraPos = m_posV;
}
//=============================
//�X�V--3D
//=============================
void  CCamera::ActionUpdate3D()
{
	Input3DCamera();//�R�R�ɓG���b�N�I�����肪�����Ă���

	float fLength;


	//�J��������	
	fLength = 500.0f;


	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CScene::MODE NowState = CScene::GetNowScene();

	//player�̈ʒu���擾
	CObject* pObj = nullptr;
	pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	//	D3DXVECTOR3 SETPOS_R=

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);

		CObject::DATA EscData;

		EscData = pPlayer->GetClassData();

//		m_posR = EscData.Pos;//�����_


		if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2)
		{//�Q�[����
		//�J��������	

			m_posR.x = EscData.Pos.x;
			m_posR.y = EscData.Pos.y + 330.0f;
			m_posR.z = EscData.Pos.z;


			fLength = 700.0f;

			m_posV.x += m_Move.x;
			m_posV.y += m_Move.y;
			m_posV.z -= m_Move.z;

			m_rot.x += m_rotMove.x;
			m_rot.y += m_rotMove.y;
			m_rot.z += m_rotMove.z;

			if (m_rot.x > D3DX_PI * 0.25f)//���񐧌�
			{
				m_rot.x = D3DX_PI * 0.24999f;
			}
			if (m_rot.x < -D3DX_PI * 0.35f)
			{
				m_rot.x = -D3DX_PI * 0.34999f;
			}

			if (m_rot.y < -3.14f)
			{
				m_rot.y = 3.14f;
			}
			else if (m_rot.y > 3.14f)
			{
				m_rot.y = -3.14f;
			}


			//��������p�x								//
			m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1�R�T�C���V�[�^��������--�R�T�C���t�@�C��������
			m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Y�͕��Ղ̂��߂����Ȃ�
			m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//�P�Ɠ�������
			//posR��			������PosV	������+�ɕύX


		}
		else if (NowState == CScene::MODE_TITLE || NowState == CScene::MODE_RESULT)
		{//�^�C�g��
			m_posR = D3DXVECTOR3(0.0f, 25.0f, 0.0f);

			//�J��������	
			fLength = 3250.0f * 0.16f;

			//�p�x�ɂ��ʒu����
			m_rot.x = -0.42f;
			m_rot.y = 0.0f;
			m_rot.z = 0.0f;

			//��������p�x								//
			m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1�R�T�C���V�[�^��������--�R�T�C���t�@�C��������
			m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Y�͕��Ղ̂��߂����Ȃ�
			m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//�P�Ɠ�������
			//posR��			������PosV	������+�ɕύX
		}
		else if (NowState == CScene::MODE_OP)
		{
			//�J��������	

			m_posR.x = EscData.Pos.x;
			m_posR.y = EscData.Pos.y + 130.0f;
			m_posR.z = EscData.Pos.z;


			fLength = DebuCameraLength;

			m_posV.x += m_Move.x;
			m_posV.y += m_Move.y;
			m_posV.z -= m_Move.z;

			m_rot.x += m_rotMove.x;
			m_rot.y += m_rotMove.y;
			m_rot.z += m_rotMove.z;

			if (m_rot.x > D3DX_PI * 0.25f)//���񐧌�
			{
				m_rot.x = D3DX_PI * 0.24999f;
			}
			if (m_rot.x < -D3DX_PI * 0.35f)
			{
				m_rot.x = -D3DX_PI * 0.34999f;
			}

			if (m_rot.y < -3.14f)
			{
				m_rot.y = 3.14f;
			}
			else if (m_rot.y > 3.14f)
			{
				m_rot.y = -3.14f;
			}


			//��������p�x								//
			m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1�R�T�C���V�[�^��������--�R�T�C���t�@�C��������
			m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Y�͕��Ղ̂��߂����Ȃ�
			m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//�P�Ɠ�������
			//posR��			������PosV	������+�ɕύX


		}


		//�ړ��ʂ��X�V(�^�������Ō���)
		m_Move.x += (0.0f - m_Move.x) * CAMERA_MOVE_DAMPING_RATIO;
		m_Move.y += (0.0f - m_Move.y) * CAMERA_MOVE_DAMPING_RATIO;
		m_Move.z += (0.0f - m_Move.z) * CAMERA_MOVE_DAMPING_RATIO;


		m_rotMove.x += (0.0f - m_rotMove.x) * CAMERA_ROT_DAMPING_RATIO;
		m_rotMove.y += (0.0f - m_rotMove.y) * CAMERA_ROT_DAMPING_RATIO;
		m_rotMove.z += (0.0f - m_rotMove.z) * CAMERA_ROT_DAMPING_RATIO;



	//	m_posR.z += 150.0f;
		CameraPos = m_posV;
	}
}
//=============================
//�RD��p�J��������
//=============================
void CCamera::Input3DCamera()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CCamera* pCamera = pManager->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	//���ԓ_�܂ł̋���
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//�����𔼕���

	//���ԓ_�������ăf�b�h�]�[���ƍő�_�̒��ԓ_���Z�o(�ʏ���́A�����͂̔��ʕ���_)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;


	//-------------------------------------------------------------------------------------------------------------------------
	//�E�X�e�B�b�N

	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_UP))
	{
		DebuCameraLength+=2;
	}
	else if (JoyPad->GetPress(CInputJoyPad::JOYKEY_DOWN))
	{
		DebuCameraLength-=2;
	}

	bool MoveNowCom2 = false;//���̗͂L��(�R���g���[��)

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//A�������ꂽ(��)
	//	Xdate = 1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//D�������ꂽ(�E)
	//	Xdate = -1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//W�������ꂽ(��)
		//Zdate = -1.0f;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//S�������ꂽ(��)
		//Zdate = 1.0f;
		MoveNowCom2 = true;
	}

	int sThumbRX = joykeystate.Gamepad.sThumbRX;
	int sThumbRY = joykeystate.Gamepad.sThumbRY;

	// �X�e�B�b�N�̓��͒l����x�N�g���̑傫�����v�Z
	float magnitude = std::sqrt(static_cast<float>(sThumbRX * sThumbRX) + static_cast<float>(sThumbRY * sThumbRY));

//	float vecX, vecY;

	//if (magnitude > 0)
	//{
	//	// �l�𐳋K���i�P�ʃx�N�g�����v�Z�j
	//	vecX = sThumbRX / magnitude;
	//	vecY = sThumbRY / magnitude;
	//	// �^�[�Q�b�g�̈ʒu���v�Z
	//	m_TargetPos.x = classData.Pos.x + vecX * 500.0f; // X�����Ɉ�苗���i��
	//	m_TargetPos.y = (classData.Pos.y + 150.0f) + vecY * 500.0f; // Y�����Ɉ�苗���i��
	//	m_TargetPos.z = 0;

	//}
	//else
	//{
	//	// �X�e�B�b�N�������̏ꍇ�̓x�N�g����0��
	//	vecX = 0.0f;
	//	vecY = 0.0f;
	//}

	float MoveSpeed2 = 3.0f;

	if (MoveNowCom2 == false)
	{
	
	}
	else
	{//�f�b�h�]�[��������
		//Controller�ړ�

		m_rotMove.y -= (joykeystate.Gamepad.sThumbRX * JoyStickDiffCamera);
		m_rotMove.x += (joykeystate.Gamepad.sThumbRY * JoyStickDiffCamera);
	}
	//-------------------------------------------------------------------------------------------------------------------------


	LockOnEnemy();//LOCK ON����
}
//=============================
//�J�����ݒ�
//=============================
void CCamera::SetCamera()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),//����p
		(float)m_Screen_Width / (float)m_Screen_Height,//��ʂ̃A�X�y�N�g��
		10.0f,//�����ŏ��l
		59000.0f);//z���ő�l

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	EscDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);






	//----------------------------------------------------------
	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_fMag > 1)
	{
		m_fMag--;
		float nRandomX = (float)(rand() % (int)m_fMag);
		float nRandomY = (float)(rand() % (int)m_fMag);
		float nRandomZ = (float)(rand() % (int)m_fMag);

		adjust = D3DXVECTOR3(nRandomX * 0.1f, nRandomY * 0.1f, nRandomZ * 0.1f);

		D3DXVECTOR3 adjustedPosV = m_posV + adjust;
		D3DXVECTOR3 adjustedPosR = m_posR + adjust;

		D3DXMatrixLookAtLH(&m_mtxView, &adjustedPosV, &adjustedPosR, &m_vecU);
		//-----------------------------------------------------------
	}

	//�r���[�}�g���b�N�X�̐ݒ�
	EscDevice->SetTransform(D3DTS_VIEW, &m_mtxView);


	
}
//=============================
//�J�����h��
//=============================
void CCamera::SetShake(int ShakeFlame, float Magnitude)
{
	m_fMag = Magnitude;
	m_nShakeFlame = ShakeFlame;
}
//=============================
//�X�N���[���T�C�Y�i�[
//=============================
void CCamera::SetScreenSize(float screenWidth, float screenHeight)
{
	m_Screen_Width = (float)screenWidth;
	m_Screen_Height = (float)screenHeight;
}
//=============================
//�X�N���[���U�C�Y�擾
//=============================
D3DXVECTOR2 CCamera::GetScreenSize()
{
	return D3DXVECTOR2((float)m_Screen_Width, (float)m_Screen_Height);
}
//=============================
//�p�x�擾
//=============================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}

//=============================
// ���b�N�I������
//=============================
void CCamera::LockOnEnemy()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	
	struct LockOnTarget
	{
		CObject* pEnemy;
		float distanceSquared; // 2D����^2
		int enemyType;
	};

	std::vector<LockOnTarget> potentialTargets;

	// �v���C���[�̈ʒu���擾
	CObject* pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);
	CObject::DATA PlayerEscData;

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);
		PlayerEscData = pPlayer->GetClassData();
		PlayerEscData.Pos.y += 130.0f;
	}

	// �G�̃X�N���[�����W���X�V
	SetAllEnemyScreenPos();

	// �����^�C�v�G������
	CObject* pObjectFast = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_FAST);

	if (pObjectFast != nullptr)
	{
		while (pObjectFast != nullptr)
		{
			CObjectMotionEnemyfast* pEnemyFast = (CObjectMotionEnemyfast*)pObjectFast;
			CObject::DATA EscEnemyData = pEnemyFast->GetClassData();
			EscEnemyData.Pos.y += 50.0f;
			//���Z�b�g
			pEnemyFast->GetLockOnUI()->SetDrawOk(false);
			pEnemyFast->GetLockOnUIMain()->SetDrawOk(false);


			if (IsInScreen(pEnemyFast->GetScreenPos()) && IsFacingCamera(EscEnemyData.Pos))
			{
				// �J�����ƓG�̋������v�Z
				D3DXVECTOR3 cameraToEnemy = pEnemyFast->GetClassData().Pos - m_posV;
				float distance = D3DXVec3Length(&cameraToEnemy);//�ΏۂƂ̋���

				if (distance < LOCKMISSLEDDISTANCE)
				{//�~�T�C���͈�
						// 2D�����v�Z
					double dx = (double)(SCREEN_WIDTH / 2.0f) - (double)pEnemyFast->GetScreenPos().x;
					double dy = (double)(SCREEN_HEIGHT / 2.0f) - (double)pEnemyFast->GetScreenPos().y;
					double distance2D = dx * dx + dy * dy;

					LockOnTarget target{ pEnemyFast, static_cast<float>(distance2D), 0 };
					potentialTargets.push_back(target);
				}
				else
				{
				}
			}

			pObjectFast = pObjectFast->GetNext();
		}
	}

	// �ʏ�^�C�v�G������
	CObject* pObjectNormal = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_NOMAL);

	if (pObjectNormal != nullptr)
	{
		while (pObjectNormal != nullptr)
		{
			CObjectMotionEnemyNomal* pEnemyNomal = (CObjectMotionEnemyNomal*)pObjectNormal;
			CObject::DATA EscEnemyData = pEnemyNomal->GetClassData();
			EscEnemyData.Pos.y += 50.0f;

			//���Z�b�g
			pEnemyNomal->GetLockOnUI()->SetDrawOk(false);
			pEnemyNomal->GetLockOnUIMain()->SetDrawOk(false);


			if (IsInScreen(pEnemyNomal->GetScreenPos()) && IsFacingCamera(EscEnemyData.Pos))
			{
				// �J�����ƓG�̋������v�Z
				D3DXVECTOR3 cameraToEnemy = pEnemyNomal->GetClassData().Pos - m_posV;
				float distance = D3DXVec3Length(&cameraToEnemy);//�ΏۂƂ̋���

				if (distance < LOCKMISSLEDDISTANCE)
				{//�~�T�C���͈�
					
					// 2D�����v�Z
					double dx = (double)(SCREEN_WIDTH / 2.0f) - (double)pEnemyNomal->GetScreenPos().x;
					double dy = (double)(SCREEN_HEIGHT / 2.0f) - (double)pEnemyNomal->GetScreenPos().y;
					double distance2D = dx * dx + dy * dy;

					LockOnTarget target{ pEnemyNomal, static_cast<float>(distance2D), 1 };
					potentialTargets.push_back(target);

				}
				else
				{

				}
			}

			pObjectNormal = pObjectNormal->GetNext();
		}
	}

	// �������Ƀ\�[�g
	std::sort(potentialTargets.begin(), potentialTargets.end(), [](const LockOnTarget& a, const LockOnTarget& b) {
		return a.distanceSquared < b.distanceSquared;
		});

	// 8�̂̃��b�N�I���Ώۂ�I��
	int lockOnCount = std::min(8, static_cast<int>(potentialTargets.size()));
	for (int i = 0; i < lockOnCount; ++i)
	{
		CObject* pEnemy = potentialTargets[i].pEnemy;
		if (potentialTargets[i].enemyType == 0)
		{
			auto* pEnemyFast = static_cast<CObjectMotionEnemyfast*>(pEnemy);
			if (pEnemyFast)
			{
				//�~�T�C�����b�N
				pEnemyFast->GetLockOnUI()->SetDrawOk(true);

				CObject::DATA SETDATA = CObject::DataInit();
				SETDATA.Pos = pEnemyFast->GetClassData().Pos;
				SETDATA.Pos.y += 40.0f;
				pEnemyFast->GetLockOnUI()->SetDATA(SETDATA);
			}
		}
		else if (potentialTargets[i].enemyType == 1)
		{
			auto* pEnemyNomal = static_cast<CObjectMotionEnemyNomal*>(pEnemy);
			if (pEnemyNomal)
			{
				//�~�T�C�����b�N
				pEnemyNomal->GetLockOnUI()->SetDrawOk(true);

				CObject::DATA SETDATA = CObject::DataInit();
				SETDATA.Pos = pEnemyNomal->GetClassData().Pos;
				SETDATA.Pos.y += 40.0f;
				pEnemyNomal->GetLockOnUI()->SetDATA(SETDATA);

			}
		}
	}

	// ��Ԓ��S�ɋ߂��G���o���b�g���b�N�I��
	if (lockOnCount > 0)
	{
		CObject* pEnemy = potentialTargets[0].pEnemy;
		if (potentialTargets[0].enemyType == 0)
		{
			auto* pClosestEnemyFast = static_cast<CObjectMotionEnemyfast*>(pEnemy);
			//�~�T�C�����b�N
			pClosestEnemyFast->GetLockOnUIMain()->SetDrawOk(true);

			CObject::DATA SETDATA = CObject::DataInit();
			SETDATA.Pos = pClosestEnemyFast->GetClassData().Pos;
			SETDATA.Pos.y += 40.0f;
			pClosestEnemyFast->GetLockOnUIMain()->SetDATA(SETDATA);

		}
		else if (potentialTargets[0].enemyType == 1)
		{
			auto* pClosestEnemyNomal = static_cast<CObjectMotionEnemyNomal*>(pEnemy);
			//�~�T�C�����b�N
			pClosestEnemyNomal->GetLockOnUIMain()->SetDrawOk(true);

			CObject::DATA SETDATA = CObject::DataInit();
			SETDATA.Pos = pClosestEnemyNomal->GetClassData().Pos;
			SETDATA.Pos.y += 40.0f;
			pClosestEnemyNomal->GetLockOnUIMain()->SetDATA(SETDATA);

		}
	}
}





//=============================
// �S�G�X�N���[�����W�ϊ��Z�b�g
//=============================
void CCamera::SetAllEnemyScreenPos()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �r���[�s��Ǝˉe�s��̐ݒ�
	D3DXMATRIX viewMatrix, projectionMatrix;

	// �J�����̈ʒu�A�����_�A��������l�����ăr���[�s���ݒ�
	D3DXVECTOR3 cameraPosition = m_posV;
	D3DXVECTOR3 cameraLookAt = m_posR;
	D3DXVECTOR3 cameraUp(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&viewMatrix, &cameraPosition, &cameraLookAt, &cameraUp);

	D3DXMatrixPerspectiveFovLH(&projectionMatrix,
		D3DXToRadian(45.0f), // ����p
		(float)m_Screen_Width / (float)m_Screen_Height, // �A�X�y�N�g��
		10.0f, // Z���ŏ��l
		59000.0f // Z���ő�l
	);

	// �r���[�|�[�g�̐ݒ�
	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = (DWORD)m_Screen_Width;
	viewport.Height = (DWORD)m_Screen_Height;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;

	// �����G�̃X�N���[�����W�ϊ�
	CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_FAST);

	while (pObject != nullptr)
	{
		CObjectMotionEnemyfast* pEnemyFast = (CObjectMotionEnemyfast*)pObject;
		CObject::DATA EscEnemyData = pEnemyFast->GetClassData();

		D3DXVECTOR3 worldPos = EscEnemyData.Pos;
		D3DXVECTOR3 screenPos;

		// ���[���h���W����X�N���[�����W�ւ̕ϊ�
		D3DXVec3Project(&screenPos, &worldPos, &viewport, &projectionMatrix, &viewMatrix, nullptr);

		pEnemyFast->SetSCREENPOS(screenPos);

		pObject = pObject->GetNext();
	}

	// �ʏ�G�̃X�N���[�����W�ϊ�
	pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_NOMAL);

	while (pObject != nullptr)
	{
		CObjectMotionEnemyNomal* pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;
		CObject::DATA EscEnemyData = pEnemyNomal->GetClassData();

		D3DXVECTOR3 worldPos = EscEnemyData.Pos;
		D3DXVECTOR3 screenPos;

		// ���[���h���W����X�N���[�����W�ւ̕ϊ�
		D3DXVec3Project(&screenPos, &worldPos, &viewport, &projectionMatrix, &viewMatrix, nullptr);

		pEnemyNomal->SetSCREENPOS(screenPos);

		pObject = pObject->GetNext();
	}
}

//=============================
// �J�������Ώۂ̕��������Ă��邩�ǂ����𔻒�
//=============================
bool CCamera::IsFacingCamera(D3DXVECTOR3 enemyPosition)
{
	//�J�����擾
	D3DXVECTOR3 cameraPosition = m_posV;
	D3DXVECTOR3 cameraLookAt = m_posR;

	D3DXVECTOR3 toEnemy = enemyPosition - cameraPosition;
	D3DXVec3Normalize(&toEnemy, &toEnemy);//�J�����ʒu�ƓG�ʒu�̃x�N�g���Z�o

	D3DXVECTOR3 cameraForward;
	D3DXVECTOR3 diffVector = cameraLookAt - cameraPosition;//�J�����̌��Ă���x�N�g���Z�o
	D3DXVec3Normalize(&cameraForward, &diffVector);

	// �J�����̑O���x�N�g���ƓG�ւ̃x�N�g�����قړ��������������Ă��邩�ǂ����𔻒�
	float dotProduct = D3DXVec3Dot(&toEnemy, &cameraForward);
	return (dotProduct > 0.5f); //�덷�͈͈ȓ��ŕԂ�
}
//=============================
// �X�N���[�����W����ʓ��ɂ��邩�ǂ����𔻒�
//=============================
bool CCamera::IsInScreen(D3DXVECTOR3 screenPosition)
{
	return (screenPosition.x >= 0 && screenPosition.x <= SCREEN_WIDTH &&
		screenPosition.y >= 0 && screenPosition.y <= SCREEN_HEIGHT &&
		screenPosition.z >= 0 && screenPosition.z <= 1);
}

//=============================
// RAY���������Ă邩
//=============================
bool CCamera::IntersectRayAABB(
	const D3DXVECTOR3& rayStart,
	const D3DXVECTOR3& rayDir,
	const D3DXVECTOR3& boxMin,
	const D3DXVECTOR3& boxMax,
	float& tMin,
	float& tMax)
{
	tMin = 0.0f;           // ���C�̎n�_�̃p�����[�^
	tMax = FLT_MAX;        // ���C�̏I�_�̃p�����[�^

	for (int i = 0; i < 3; ++i) { // X, Y, Z �������ꂼ��Ń`�F�b�N
		if (rayDir[i] != 0.0f) {
			float t1 = (boxMin[i] - rayStart[i]) / rayDir[i];
			float t2 = (boxMax[i] - rayStart[i]) / rayDir[i];

			if (t1 > t2) std::swap(t1, t2);

			tMin = std::max(tMin, t1);
			tMax = std::min(tMax, t2);

			if (tMin > tMax) {
				return false; // ���C��AABB�ƌ������Ă��Ȃ�
			}
		}
		else if (rayStart[i] < boxMin[i] || rayStart[i] > boxMax[i]) {
			return false; // ���C��AABB�͈̔͊O
		}
	}

	return true; // ���C��AABB�ƌ���
}