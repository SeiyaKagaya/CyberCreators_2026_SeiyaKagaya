//=======================================================
//
//scene�Ɋւ��鏈��[scene.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "scene.h"
#include "object3D.h"
#include "score.h"
#include "time.h"
#include "font.h"
#include "fade.h"
#include "manager.h"
#include "ObstacleSet.h"
#include "object_motion.h"
#include "player_motion.h"
#include "enemy_motion_Nomal.h"
#include "StageCollisionBox.h"
#include "tankfootprint.h"
#include "player_motion.h"
#include "enemy_motion_fast.h"
#include "target_UI.h"
#include "pause.h"
#include "Explosion3D.h"
#include "Tutorial.h"
#include "Game_UI.h"
#include "result.h"
#include "newbullet.h"

// �ÓI�����o�[�ϐ��̒�`
CScene::MODE CScene::m_NowState = CScene::MODE_TITLE; // �����l��MODE_TITLE�ɐݒ�
bool CScene::m_bStageClear = false;


//++
//++�V�[�����ׂĂ̊Ǘ�
//++
 

//===================================
// �R���X�g���N�^
//===================================
CScene::CScene()
{
	CManager* pManager = CManager::GetInstance();
	
	m_Pause = pManager->GetPause();
	m_StayUI = pManager->GetStayUI();
}

//===================================
// �f�X�g���N�^
//===================================
CScene::~CScene()
{
}

//===================================
// ������
//===================================
HRESULT CScene::Init()
{
	return E_NOTIMPL;
}

//===================================
// �I��
//===================================
void CScene::Uninit()
{

}

//===================================
// �X�V
//===================================
void CScene::Update()
{
}

//===================================
// �`��
//===================================
void CScene::Draw()
{
}

//===================================
// ����
//===================================
CScene* CScene::Create(MODE mode)
{
	CScene* pScene = nullptr;
	SetNowScene(mode);

	switch (mode)
	{
	case MODE_TITLE:
		pScene = new CTitle;

		break;

	case MODE_GAME:
		pScene = new CGame;
		break;

	case MODE_GAME2:
		pScene = new CGame2;
		break;

	case MODE_GAME3:
		pScene = new CGame3;
		break;
	case MODE_GAME4:
		pScene = new CGame4;
		break;

	case MODE_RESULT:
		pScene = new CResult;
		break;
	case MODE_TUTORIAL:
		pScene = new CTutorial;
		break;
	}

	return pScene;
}

//===================================
// ���݂̃V�[�����i�[
//===================================
void CScene::SetNowScene(MODE SetScene)
{
	m_NowState = SetScene;
}

//===================================
// �Q�[���N���A����
//===================================
void CScene::SetStageClear(bool bSet)
{
	m_bStageClear = bSet;
}

//===================================
// �N���A��Ԃ��擾
//===================================
bool CScene::GetStageClear()
{
	return m_bStageClear;
}

//===================================
// ���݂̃V�[�����擾
//===================================
CScene::MODE CScene::GetNowScene()
{
	return m_NowState;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+�Q�[���V�[��
//+

//===================================
// �R���X�g���N�^
//===================================
CGame::CGame()
{
}

//===================================
// �f�X�g���N�^
//===================================
CGame::~CGame()
{
}

//===================================
// ������
//===================================
HRESULT CGame::Init()
{
	CTime::Create();

	CObject3D::Create();//����

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//�X�e�[�W�z�u�����[�h

	CScore::Create();

	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//�o�H�e�[�u�������[�h

	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//�ˌ��n�_�����[�h

	CObjectMotion::DATA SetData = CObject::DataInit();//����������
	
	//�z�u��
	SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, 1200.0f);
	SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(3450.0f, 0.0f, 1200.0f);
	SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, -150.0f);
	SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, 2400.0f + 150.0f);
	SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	SetData.MinLength = D3DXVECTOR3(-160.0f, 0.0f, -160.0f);
	SetData.MaxLength = D3DXVECTOR3(160.0f, 300.0f, 160.0f);
	StageCollisionBox::Create(SetData);


	//player���ŏ��I
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
	SetData.Pos = D3DXVECTOR3(180.0f, 0.0f, 180.0f);
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------

	CObjectMotionPlayer::SetPlayerNum(1);//�c��i�[

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������

	SetData.Pos = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(1000.0f, 0.0f, 2000.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(2000.0f, 0.0f, 1200.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------

	CGameUI::Create();

	m_StayTime = STAYFRAME;

	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);

	CSound* pSound = pManager->GetSound();
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//===================================
// �I��
//===================================
void CGame::Uninit()
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM001);
}

//===================================
// �X�V
//===================================
void CGame::Update()
{
	// �}�E�X�J�[�\�����\���ɂ���
	int nDrawCnt = ShowCursor(FALSE);

	while (true)
	{
		if (nDrawCnt >= 0)
		{//�\����Ԃ̂Ƃ�
			nDrawCnt = ShowCursor(FALSE);
		}
		else
		{//��\����Ԃ̂Ƃ�

			if (nDrawCnt < -1)
			{//�����肷���h�~
				nDrawCnt = ShowCursor(TRUE);
			}
			break;
		}
	}

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();

	if (pManager->GetStayState() == false)
	{
		if (pManager->GetPauseState() == false)
		{

			if (CObjectMotionEnemyBase::GetEnemyAllNum() <= 0)
			{//�G�r��	
				m_bNext = true;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//�������Ԑ؂�
				m_bNext = false;
				m_bStay2BOOL = true;
			}

			// �z�u���v���C�I���e�B�̐擪���擾
			CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

			if (pObject != nullptr)
			{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

				if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
				{ // �Ώۂ̃��f���̂Ƃ�

					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					CObject::DATA EscData;

					// �����Ŏg�p���錾
					CObjectMotionPlayer* pMotionPlayer;

					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					if (pMotionPlayer->GetPlayerNum() < 0)
					{//�c�@�܂��Ȃ���

						m_bNext = false;
						m_bStay2BOOL = true;
					}
				}
			}

			if (m_bStay2BOOL == true)
			{
				m_Stay2--;

				if (m_Stay2<=0)
				{
					m_bStay2BOOL = false;

					if (m_bNext == true)
					{//����
						CScore::AddScore(CTime::GetTime() * CScore::TIMEBONUS);

						pManager->SetEndStatusState(true);
						pManager->SetStayState(true);
					}
					else
					{//�߂�
						pManager->SetEndStatusState(false);
						pManager->SetStayState(true);
					}
					m_bNext = false;

					m_Stay2 = STAYFRAME2;
				}
			}
		}
		else
		{
			m_Pause->Update();
		}
	}
	else
	{
		m_StayUI->Update();

		if (m_StayPush == false)
		{
			m_StayTime--;

			if (m_StayTime <= 0)
			{
				m_StayTime = STAYFRAME;

				m_StayPush = true;
			}
		}
		else
		{
			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* keyboard = pManager->GetKeyboard();
			CInputJoyPad* JoyPad = pManager->GetJoyPad();
			XINPUT_STATE joykeystate;

			//�V���C�p�b�g�̏�Ԃ��擾
			DWORD dwResult = XInputGetState(0, &joykeystate);

			if (pManager->bGetInputState() == true)
			{//������@--true�ŃR���g���[���[
				if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

					if (pManager->GetEndStatusState()==true)
					{//�N���ARoute

						CManager* pManager = CManager::GetInstance();
						pManager->SetStayStatusState(false);
						pManager->SetStayState(false);
						pManager->SetPauseState(false);

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_GAME2);
					}
					else
					{//�s�k
						CManager* pManager = CManager::GetInstance();
						pManager->SetStayStatusState(false);
						pManager->SetStayState(false);
						pManager->SetPauseState(false);

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);
					}
				}
			}
			else
			{//�L�[�{�[�h���͔��f(�ړ�)
				if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

					if (pManager->GetEndStatusState() == true)
					{//�N���ARoute
						CManager* pManager = CManager::GetInstance();
						pManager->SetStayStatusState(false);
						pManager->SetStayState(false);
						pManager->SetPauseState(false);

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_GAME2);
					}
					else
					{//�s�k
						CManager* pManager = CManager::GetInstance();
						pManager->SetStayStatusState(false);
						pManager->SetStayState(false);
						pManager->SetPauseState(false);

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);
					}
				}
			}
		}
	}
}

//===================================
// �`��
//===================================
void CGame::Draw()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();

	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "���@�c�@�F%d", CObjectMotionPlayer::GetPlayerNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
	// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
	CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);
	
	if (pManager->GetPauseState() == true)
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//�ҋ@���
		m_StayUI->Draw();

		char aData2[100];

		int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		snprintf(aData2, sizeof(aData2), "�^�C���{�[�i�X:%d", nSetNum); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);
	}

	if (m_StayPush == true)
	{//�����ҋ@

		if (m_bButtonBool == false)
		{
			m_nbuttonCnt += 2;

			if (m_nbuttonCnt > BUTTONCNT)
			{
				m_nbuttonCnt = BUTTONCNT;
				m_bButtonBool = true;
			}
		}
		else
		{
			m_nbuttonCnt -= 2;

			if (m_nbuttonCnt < 0)
			{
				m_nbuttonCnt = 0;
				m_bButtonBool = false;
			}
		}

		if (pManager->bGetInputState() == true)
		{//������@--true�ŃR���g���[���[
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "A�{�^���Ŏ���"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);
		}
		else
		{//�L�[�{�[�h���͔��f(�ړ�)
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "�}�E�X�E�N���b�N�Ŏ���"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f,0.2f,0.2f, (float)m_nbuttonCnt * 0.01f), aData2);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+�Q�[��2�V�[��
//+


//===================================
// �R���X�g���N�^
//===================================
CGame2::CGame2()
{
}

//===================================
// �f�X�g���N�^
//===================================
CGame2::~CGame2()
{
}

//===================================
// ������
//===================================
HRESULT CGame2::Init()
{
	CTime::Create();

	CObject3D::Create();//����

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE2\\model.txt");//�X�e�[�W�z�u�����[�h

	CScore::Create();

	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE2\\RouteResult.csv");//�o�H�e�[�u�������[�h
	CObjectMotion::DATA SetData = CObject::DataInit();//����������

	//�z�u��
	SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, 1200.0f);
	SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	StageCollisionBox::Create(SetData);


	SetData.Pos = D3DXVECTOR3(3450.0f, 0.0f, 1200.0f);
	SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	StageCollisionBox::Create(SetData);


	SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, -150.0f);
	SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, 2400.0f + 150.0f);
	SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	StageCollisionBox::Create(SetData);


	SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	SetData.MinLength = D3DXVECTOR3(-160.0f, 0.0f, -160.0f);
	SetData.MaxLength = D3DXVECTOR3(160.0f, 300.0f, 160.0f);
	StageCollisionBox::Create(SetData);

	//player���ŏ��I
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
	SetData.Pos = D3DXVECTOR3(1200.0f, 0.0f, 1200.0f);
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);//�c��i�[

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
	SetData.Pos = D3DXVECTOR3(300.0f, 0.0f, 2100.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(300.0f, 0.0f, 300.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(3000.0f, 0.0f, 300.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(3150.0f, 0.0f, 2250.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------

	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);

	CGameUI::Create();

	CSound* pSound = pManager->GetSound();
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM002);

	return S_OK;
}

//===================================
// �I��
//===================================
void CGame2::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM002);
}

//===================================
// �X�V
//===================================
void CGame2::Update()
{
	// �}�E�X�J�[�\�����\���ɂ���
	int nDrawCnt = ShowCursor(FALSE);

	while (true)
	{
		if (nDrawCnt >= 0)
		{//�\����Ԃ̂Ƃ�
			nDrawCnt = ShowCursor(FALSE);
		}
		else
		{//��\����Ԃ̂Ƃ�

			if (nDrawCnt < -1)
			{//�����肷���h�~
				nDrawCnt = ShowCursor(TRUE);
			}
			break;
		}
	}

	CManager* pManager = CManager::GetInstance();

	if (pManager->GetStayState() == false)
	{
		if (pManager->GetPauseState() == false)
		{
			if (CObjectMotionEnemyBase::GetEnemyAllNum() <= 0)
			{//�G�r��	
				m_bNext = true;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//�������Ԑ؂�
				m_bNext = false;
				m_bStay2BOOL = true;
			}

			// �z�u���v���C�I���e�B�̐擪���擾
			CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

			if (pObject != nullptr)
			{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

				if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
				{ // �Ώۂ̃��f���̂Ƃ�

					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					CObject::DATA EscData;

					// �����Ŏg�p���錾
					CObjectMotionPlayer* pMotionPlayer;

					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					if (pMotionPlayer->GetPlayerNum() < 0)
					{//�c�@�܂��Ȃ���
						m_bNext = false;
						m_bStay2BOOL = true;
					}
				}
			}


			if (m_bStay2BOOL == true)
			{
				m_Stay2--;

				if (m_Stay2 <= 0)
				{
					m_bStay2BOOL = false;

					if (m_bNext == true)
					{//����
						CScore::AddScore(CTime::GetTime() * CScore::TIMEBONUS);

						pManager->SetEndStatusState(true);
						pManager->SetStayState(true);
					}
					else
					{//�߂�
						pManager->SetEndStatusState(false);
						pManager->SetStayState(true);
					}
					m_bNext = false;

					m_Stay2 = STAYFRAME2;
				}
			}

			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* keyboard = pManager->GetKeyboard();
			CInputJoyPad* JoyPad = pManager->GetJoyPad();
			XINPUT_STATE joykeystate;
			//�V���C�p�b�g�̏�Ԃ��擾
			DWORD dwResult = XInputGetState(0, &joykeystate);
		}
		else
		{
			m_Pause->Update();
		}
	}
	else
	{
		m_StayUI->Update();

		if (m_StayPush == false)
		{
			m_StayTime--;

			if (m_StayTime <= 0)
			{
				m_StayTime = STAYFRAME;

				m_StayPush = true;
			}
		}
		else
		{
			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* keyboard = pManager->GetKeyboard();
			CInputJoyPad* JoyPad = pManager->GetJoyPad();
			XINPUT_STATE joykeystate;

			//�V���C�p�b�g�̏�Ԃ��擾
			DWORD dwResult = XInputGetState(0, &joykeystate);

			//PAUSE�N��
			if (pManager->bGetInputState() == true)
			{//������@--true�ŃR���g���[���[
				if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


					if (pManager->GetEndStatusState() == true)
					{//�N���ARoute
						CManager* pManager = CManager::GetInstance();
						pManager->SetStayStatusState(false);
						pManager->SetStayState(false);
						pManager->SetPauseState(false);


						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_GAME3);

					}
					else
					{//�s�k
						CManager* pManager = CManager::GetInstance();
						pManager->SetStayStatusState(false);
						pManager->SetStayState(false);
						pManager->SetPauseState(false);


						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);
					}
				}
			}
			else
			{//�L�[�{�[�h���͔��f(�ړ�)
				if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

					if (pManager->GetEndStatusState() == true)
					{//�N���ARoute
						CManager* pManager = CManager::GetInstance();
						pManager->SetStayStatusState(false);
						pManager->SetStayState(false);
						pManager->SetPauseState(false);

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_GAME3);
					}
					else
					{//�s�k
						CManager* pManager = CManager::GetInstance();
						pManager->SetStayStatusState(false);
						pManager->SetStayState(false);
						pManager->SetPauseState(false);

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);
					}
				}
			}
		}
	}
}

//===================================
// �`��
//===================================
void CGame2::Draw()
{
	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "���@�c�@�F%d", CObjectMotionPlayer::GetPlayerNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
	// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
	CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_MILITARY, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();

	if (pManager->GetPauseState() == true)
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//�ҋ@���
		m_StayUI->Draw();

		char aData2[100];

		int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		snprintf(aData2, sizeof(aData2), "�^�C���{�[�i�X:%d", nSetNum); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);

	}

	if (m_StayPush == true)
	{//�����ҋ@
		if (m_bButtonBool == false)
		{
			m_nbuttonCnt += 2;

			if (m_nbuttonCnt > BUTTONCNT)
			{
				m_nbuttonCnt = BUTTONCNT;
				m_bButtonBool = true;
			}
		}
		else
		{
			m_nbuttonCnt -= 2;

			if (m_nbuttonCnt < 0)
			{
				m_nbuttonCnt = 0;
				m_bButtonBool = false;
			}
		}

		if (pManager->bGetInputState() == true)
		{//������@--true�ŃR���g���[���[
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "A�{�^���Ŏ���"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt*0.01f), aData2);
		}
		else
		{//�L�[�{�[�h���͔��f(�ړ�)
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "�}�E�X�E�N���b�N�Ŏ���"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+�Q�[��3�V�[��
//+


//===================================
// �R���X�g���N�^
//===================================
CGame3::CGame3()
{
}

//===================================
// �f�X�g���N�^
//===================================
CGame3::~CGame3()
{
}

//===================================
// ������
//===================================
HRESULT CGame3::Init()
{
	CTime::Create();

	CObject3D::Create();//����

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE3\\model.txt");//�X�e�[�W�z�u�����[�h

	CScore::Create();

	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE3\\RouteResult.csv");//�o�H�e�[�u�������[�h
	CObjectMotion::DATA SetData = CObject::DataInit();//����������

	//�z�u��
	SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, 1200.0f);
	SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(3450.0f, 0.0f, 1200.0f);
	SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, -150.0f);
	SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, 2400.0f + 150.0f);
	SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	SetData.MinLength = D3DXVECTOR3(-160.0f, 0.0f, -160.0f);
	SetData.MaxLength = D3DXVECTOR3(160.0f, 300.0f, 160.0f);
	StageCollisionBox::Create(SetData);




	//player���ŏ��I
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
	SetData.Pos = D3DXVECTOR3(2550.0f, 0.0f, 450.0f);
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);//�c��i�[

	//	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
	SetData.Pos = D3DXVECTOR3(750.0f, 0.0f, 450.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, 1000.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(750.0f, 0.0f, 1950.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(1900.0f, 0.0f, 2050.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(2800.0f, 0.0f, 2150.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------
	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);

	CGameUI::Create();

	CSound* pSound = pManager->GetSound();
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM003);
	
	return S_OK;
}

//===================================
// �I��
//===================================
void CGame3::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM003);
}

//===================================
// �X�V
//===================================
void CGame3::Update()
{
	// �}�E�X�J�[�\�����\���ɂ���
	int nDrawCnt = ShowCursor(FALSE);

	while (true)
	{
		if (nDrawCnt >= 0)
		{//�\����Ԃ̂Ƃ�
			nDrawCnt = ShowCursor(FALSE);
		}
		else
		{//��\����Ԃ̂Ƃ�

			if (nDrawCnt < -1)
			{//�����肷���h�~
				nDrawCnt = ShowCursor(TRUE);
			}
			break;
		}
	}

	CManager* pManager = CManager::GetInstance();

	if (pManager->GetStayState() == false)
	{
		if (pManager->GetPauseState() == false)
		{
			if (CObjectMotionEnemyBase::GetEnemyAllNum() <= 0)
			{//�G�r��	
				m_bNext = true;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//�������Ԑ؂�
				m_bNext = false;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//�������Ԑ؂�

				pManager->SetEndStatusState(false);
				pManager->SetStayState(true);
			}

			// �z�u���v���C�I���e�B�̐擪���擾
			CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

			if (pObject != nullptr)
			{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

				if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
				{ // �Ώۂ̃��f���̂Ƃ�

					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					CObject::DATA EscData;

					// �����Ŏg�p���錾
					CObjectMotionPlayer* pMotionPlayer;

					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					if (pMotionPlayer->GetPlayerNum() < 0)
					{//�c�@�܂��Ȃ���
					
						m_bNext = false;
						m_bStay2BOOL = true;
					}
				}
			}

			if (m_bStay2BOOL == true)
			{
				m_Stay2--;

				if (m_Stay2 <= 0)
				{
					m_bStay2BOOL = false;

					if (m_bNext == true)
					{//����
						CScore::AddScore(CTime::GetTime() * CScore::TIMEBONUS);

						pManager->SetEndStatusState(true);
						pManager->SetStayState(true);
					}
					else
					{//�߂�
						pManager->SetEndStatusState(false);
						pManager->SetStayState(true);
					}
					m_bNext = false;
					m_Stay2 = STAYFRAME2;
				}
			}

			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* keyboard = pManager->GetKeyboard();
			CInputJoyPad* JoyPad = pManager->GetJoyPad();
			XINPUT_STATE joykeystate;

			//�V���C�p�b�g�̏�Ԃ��擾
			DWORD dwResult = XInputGetState(0, &joykeystate);
		}
		else
		{
			m_Pause->Update();
		}
	}
	else
	{
		m_StayUI->Update();

		if (m_StayPush == false)
		{
			m_StayTime--;

			if (m_StayTime <= 0)
			{
				m_StayTime = STAYFRAME;

				m_StayPush = true;
			}
		}
		else
		{
			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* keyboard = pManager->GetKeyboard();
			CInputJoyPad* JoyPad = pManager->GetJoyPad();
			XINPUT_STATE joykeystate;

			//�V���C�p�b�g�̏�Ԃ��擾
			DWORD dwResult = XInputGetState(0, &joykeystate);

			//PAUSE�N��
			if (pManager->bGetInputState() == true)
			{//������@--true�ŃR���g���[���[
				if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

					if (pManager->GetEndStatusState() == true)
					{//�N���ARoute
	
						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_GAME4);
					}
					else
					{//�s�k

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);
					}
				}
			}
			else
			{//�L�[�{�[�h���͔��f(�ړ�)
				if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


					if (pManager->GetEndStatusState() == true)
					{//�N���ARoute
					
						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_GAME4);
				
					}
					else
					{//�s�k
						
						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);

					}
				}
			}
		}
	}
}

//===================================
// �`��
//===================================
void CGame3::Draw()
{
	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "���@�c�@�F%d", CObjectMotionPlayer::GetPlayerNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
	
	// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
	CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_MILITARY, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();

	if (pManager->GetPauseState() == true)
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//�ҋ@���
		m_StayUI->Draw();

		char aData2[100];

		int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		snprintf(aData2, sizeof(aData2), "�^�C���{�[�i�X:%d", nSetNum); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);
	}

	if (m_StayPush == true)
	{//�����ҋ@
		if (m_bButtonBool == false)
		{
			m_nbuttonCnt += 2;

			if (m_nbuttonCnt > BUTTONCNT)
			{
				m_nbuttonCnt = BUTTONCNT;
				m_bButtonBool = true;
			}
		}
		else
		{
			m_nbuttonCnt -= 2;

			if (m_nbuttonCnt < 0)
			{
				m_nbuttonCnt = 0;
				m_bButtonBool = false;
			}
		}

		if (pManager->bGetInputState() == true)
		{//������@--true�ŃR���g���[���[
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "A�{�^���Ŏ���"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt*0.01f), aData2);
		}
		else
		{//�L�[�{�[�h���͔��f(�ړ�)
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "�}�E�X�E�N���b�N�Ŏ���"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt*0.01f), aData2);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+�Q�[��4�V�[��
//+


//===================================
// �R���X�g���N�^
//===================================
CGame4::CGame4()
{
}

//===================================
// �f�X�g���N�^
//===================================
CGame4::~CGame4()
{
}

//===================================
// ������
//===================================
HRESULT CGame4::Init()
{
	CTime::Create();

	CObject3D::Create();//����

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//�X�e�[�W�z�u�����[�h

	CScore::Create();

	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//�o�H�e�[�u�������[�h

	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//�ˌ��n�_�����[�h

	CObjectMotion::DATA SetData = CObject::DataInit();//����������

	//�z�u��
	//-------------------------------------------------------------------------------------------------------------------
	//���[
	SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, 1200.0f);
	SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	StageCollisionBox::Create(SetData);


	SetData.Pos = D3DXVECTOR3(3450.0f, 0.0f, 1200.0f);
	SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	StageCollisionBox::Create(SetData);


	SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, -150.0f);
	SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	StageCollisionBox::Create(SetData);

	SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, 2400.0f + 150.0f);
	SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	StageCollisionBox::Create(SetData);


	SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	SetData.MinLength = D3DXVECTOR3(-160.0f, 0.0f, -160.0f);
	SetData.MaxLength = D3DXVECTOR3(160.0f, 300.0f, 160.0f);
	StageCollisionBox::Create(SetData);
	//-------------------------------------------------------------------------------------------------------------------


	//player���ŏ��I
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
	SetData.Pos = D3DXVECTOR3(180.0f, 0.0f, 180.0f);
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------

	CObjectMotionPlayer::SetPlayerNum(1);//�c��i�[

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������

	SetData.Pos = D3DXVECTOR3(2000.0f, 0.0f, 2000.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(1900.0f, 0.0f, 1900.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(1000.0f, 0.0f, 2000.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(2000.0f, 0.0f, 1200.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(1900.0f, 0.0f, 1500.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(1500.0f, 0.0f, 1500.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(1600.0f, 0.0f, 1600.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(2600.0f, 0.0f, 1400.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(2700.0f, 0.0f, 1000.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(2700.0f, 0.0f, 300.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(3000, 0.0f, 300.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------

	CGameUI::Create();

	m_StayTime = STAYFRAME;

	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);

	CSound* pSound = pManager->GetSound();
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM004);

	return S_OK;
}

//===================================
// �I��
//===================================
void CGame4::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM004);
}

//===================================
// �X�V
//===================================
void CGame4::Update()
{
	// �}�E�X�J�[�\�����\���ɂ���
	int nDrawCnt = ShowCursor(FALSE);

	while (true)
	{
		if (nDrawCnt >= 0)
		{//�\����Ԃ̂Ƃ�
			nDrawCnt = ShowCursor(FALSE);
		}
		else
		{//��\����Ԃ̂Ƃ�

			if (nDrawCnt < -1)
			{//�����肷���h�~
				nDrawCnt = ShowCursor(TRUE);
			}
			break;
		}
	}

	CManager* pManager = CManager::GetInstance();

	if (pManager->GetStayState() == false)
	{
		if (pManager->GetPauseState() == false)
		{
			if (CObjectMotionEnemyBase::GetEnemyAllNum() <= 0)
			{//�G�r��	
				m_bNext = true;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//�������Ԑ؂�
				m_bNext = false;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//�������Ԑ؂�

				pManager->SetEndStatusState(false);
				pManager->SetStayState(true);
			}

			// �z�u���v���C�I���e�B�̐擪���擾
			CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

			if (pObject != nullptr)
			{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

				if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
				{ // �Ώۂ̃��f���̂Ƃ�

					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					CObject::DATA EscData;

					// �����Ŏg�p���錾
					CObjectMotionPlayer* pMotionPlayer;

					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					if (pMotionPlayer->GetPlayerNum() < 0)
					{//�c�@�܂��Ȃ���

						m_bNext = false;
						m_bStay2BOOL = true;
					}
				}
			}

			if (m_bStay2BOOL == true)
			{
				m_Stay2--;

				if (m_Stay2 <= 0)
				{
					m_bStay2BOOL = false;

					if (m_bNext == true)
					{//����
						CScore::AddScore(CTime::GetTime() * CScore::TIMEBONUS);

						pManager->SetEndStatusState(true);
						pManager->SetStayState(true);
						CScene::SetStageClear(true);
					}
					else
					{//�߂�
						pManager->SetEndStatusState(false);
						pManager->SetStayState(true);
					}
					m_bNext = false;
					m_Stay2 = STAYFRAME2;
				}
			}

			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* keyboard = pManager->GetKeyboard();
			CInputJoyPad* JoyPad = pManager->GetJoyPad();
			XINPUT_STATE joykeystate;

			//�V���C�p�b�g�̏�Ԃ��擾
			DWORD dwResult = XInputGetState(0, &joykeystate);
		}
		else
		{
			m_Pause->Update();
		}
	}
	else
	{
		m_StayUI->Update();

		if (m_StayPush == false)
		{
			m_StayTime--;

			if (m_StayTime <= 0)
			{
				m_StayTime = STAYFRAME;

				m_StayPush = true;
			}
		}
		else
		{
			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* keyboard = pManager->GetKeyboard();
			CInputJoyPad* JoyPad = pManager->GetJoyPad();
			XINPUT_STATE joykeystate;

			//�V���C�p�b�g�̏�Ԃ��擾
			DWORD dwResult = XInputGetState(0, &joykeystate);

			//PAUSE�N��
			if (pManager->bGetInputState() == true)
			{//������@--true�ŃR���g���[���[
				if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


					if (pManager->GetEndStatusState() == true)
					{//�N���ARoute

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);
					}
					else
					{//�s�k

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);

					}
				}
			}
			else
			{//�L�[�{�[�h���͔��f(�ړ�)
				if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

					if (pManager->GetEndStatusState() == true)
					{//�N���ARoute

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);

					}
					else
					{//�s�k

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);
					}
				}
			}
		}
	}
}

//===================================
// �`��
//===================================
void CGame4::Draw()
{
	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "���@�c�@�F%d", CObjectMotionPlayer::GetPlayerNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
	// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
	CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_MILITARY, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	if (pManager->GetPauseState() == true)
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//�ҋ@���
		m_StayUI->Draw();

		char aData2[100];

		int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		snprintf(aData2, sizeof(aData2), "�^�C���{�[�i�X:%d", nSetNum); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);
	}

	if (m_StayPush == true)
	{//�����ҋ@
		if (m_bButtonBool == false)
		{
			m_nbuttonCnt += 2;

			if (m_nbuttonCnt > BUTTONCNT)
			{
				m_nbuttonCnt = BUTTONCNT;
				m_bButtonBool = true;
			}
		}
		else
		{
			m_nbuttonCnt -= 2;

			if (m_nbuttonCnt < 0)
			{
				m_nbuttonCnt = 0;
				m_bButtonBool = false;
			}
		}

		if (pManager->bGetInputState() == true)
		{//������@--true�ŃR���g���[���[
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "A�{�^���Ŏ���"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);

		}
		else
		{//�L�[�{�[�h���͔��f(�ړ�)
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "�}�E�X�E�N���b�N�Ŏ���"); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);

		}
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+�^�C�g���V�[��
//+


//===================================
// �R���X�g���N�^
//===================================
CTitle::CTitle()
{
}

//===================================
// �f�X�g���N�^
//===================================
CTitle::~CTitle()
{
}

//===================================
// ������
//===================================
HRESULT CTitle::Init()
{	
	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);
	
	CScene::SetStageClear(false);
	CScore::ResetScore();
	CObject3D::Create();
	
	//player���ŏ��I
//-------------------------------------------------------------
	CObject::DATA SetData = CObject::DataInit();//������
	SetData.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------

	CSound* pSound = pManager->GetSound();
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//===================================
// �I��
//===================================
void CTitle::Uninit()
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM000);
}

//===================================
// �X�V
//===================================
void CTitle::Update()
{
	// �}�E�X�J�[�\����\���ɂ���
	int nDrawCnt = ShowCursor(TRUE);

	while (true)
	{
		if (nDrawCnt > 0)
		{//�\����Ԃ̂Ƃ�
			if (nDrawCnt > 1)
			{//2������
				nDrawCnt = ShowCursor(FALSE);
			}

			break;
		}
		else
		{//��\����Ԃ̂Ƃ�
			nDrawCnt = ShowCursor(TRUE);
		}
	}

	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* keyboard = pManager->GetKeyboard();
	CInputJoyPad* JoyPad = pManager->GetJoyPad();
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	if (dwResult == ERROR_SUCCESS)
	{//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)
//		ControllerInput();
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_START) || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A))
		{//���}�E�X�N���b�N/START�L�[/A�L�[
			CSound* pSound = pManager->GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER2);

			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_TUTORIAL);
		}
	}
	else
	{//�L�[�{�[�h���͔��f(�ړ�)
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
		{//�G���^�[�������͍��}�E�X�N���b�N
			CSound* pSound = pManager->GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER2);
			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_TUTORIAL);
		}
	}
}

//===================================
// �`��
//===================================
void CTitle::Draw()
{
	const char* aData = "Mini-";
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 607.0f, SCREEN_HEIGHT / 2.0f - 308.0f, 0.0f), 193, CFont::FONT_MILITARY, D3DXCOLOR(0.5f, 0.4f, 0.1f, 1.0f), aData);

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f-610.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 215, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

	aData = "Tank!";
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 107.0f, SCREEN_HEIGHT / 2.0f - 308.0f, 0.0f), 193, CFont::FONT_MILITARY, D3DXCOLOR(0.5f, 0.4f, 0.1f, 1.0f), aData);

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 110.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 218, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

	aData = "�}�E�X���N���b�N/Start�{�^��/A�{�^��";
	
	if (m_bButtonBool==false)
	{
		m_nbuttonCnt+=2;

		if (m_nbuttonCnt>BUTTONCNT)
		{
			m_nbuttonCnt = BUTTONCNT;
			m_bButtonBool = true;
		}
	}
	else
	{
		m_nbuttonCnt-=2;

		if (m_nbuttonCnt < 0)
		{
			m_nbuttonCnt = 0;
			m_bButtonBool = false;
		}
	}
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 310.0f, SCREEN_HEIGHT / 2.0f + 200.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, (float)m_nbuttonCnt*0.01f), aData);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+���U���g�V�[��
//+


//===================================
// �R���X�g���N�^
//===================================
CResult::CResult()
{
}

//===================================
// �f�X�g���N�^
//===================================
CResult::~CResult()
{
}

//===================================
// ������
//===================================
HRESULT CResult::Init()
{
	CObject3D::Create();

	if (CScene::GetStageClear() == true)
	{
		//player���ŏ��I
	//-------------------------------------------------------------
		CObject::DATA SetData = CObject::DataInit();//������
		SetData.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
		//-------------------------------------------------------------
	}

	CResultUI::Create();

	//�X�R�A���[�h
	ScoreLoad();

	m_ScoreNum[5] = CScore::GetScore();

	m_NUM = m_ScoreNum[5];

	CScore::ResetScore();

	// �~���i�傫�����j�Ƀ\�[�g
	std::sort(m_ScoreNum, m_ScoreNum + 6, std::greater<int>());

	ScoreWrite();

	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);

	CSound* pSound = pManager->GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_SE_JET);

	return E_NOTIMPL;
}

//===================================
// �I��
//===================================
void CResult::Uninit()
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_SE_JET);
}

//===================================
// �X�V
//===================================
void CResult::Update()
{
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* keyboard = pManager->GetKeyboard();
	CInputJoyPad* JoyPad = pManager->GetJoyPad();
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	// �}�E�X�J�[�\����\���ɂ���
	int nDrawCnt = ShowCursor(TRUE);

	while (true)
	{
		if (nDrawCnt > 0)
		{//�\����Ԃ̂Ƃ�
			if (nDrawCnt > 1)
			{//2������
				nDrawCnt = ShowCursor(FALSE);
			}

			break;
		}
		else
		{//��\����Ԃ̂Ƃ�
			nDrawCnt = ShowCursor(TRUE);
		}
	}

	if (dwResult == ERROR_SUCCESS)
	{//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)
//		ControllerInput();
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_START) || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A))
		{//���}�E�X�N���b�N/START�L�[/A�L�[

			CSound* pSound = pManager->GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_TITLE);
		}
	}
	else
	{//�L�[�{�[�h���͔��f(�ړ�)
		if (keyboard->GetTrigger(DIK_RETURN) == true || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
		{//�G���^�[�������͍��}�E�X�N���b�N
			CSound* pSound = pManager->GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_TITLE);
		}
	}
}

//===================================
// �`��
//===================================
void CResult::Draw()
{
	const char* aData = {};

	if (CScene::GetStageClear() == true)
	{
		aData = "�Q�[���N���A!!!";

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 570.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 80, CFont::FONT_KEIFONT, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), aData);
	}
	else
	{
		 aData = "�r���s��...";

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 570.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 80, CFont::FONT_GENKAI, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.8f), aData);
	}

	char aData2[100];

	snprintf(aData2, sizeof(aData2), "����̃X�R�A:%d", m_NUM); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 220.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), aData2);
	
	if (m_ScoreNum[0]!= m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "1 ��:%d", m_ScoreNum[0]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 120.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);

	}
	else
	{
		snprintf(aData2, sizeof(aData2), "1 ��:%d", m_ScoreNum[0]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 120.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}
	if (m_ScoreNum[1] != m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "2��:%d", m_ScoreNum[1]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 60.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);

	}
	else
	{
		snprintf(aData2, sizeof(aData2), "2��:%d", m_ScoreNum[1]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 60.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}
	if (m_ScoreNum[2] != m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "3��:%d", m_ScoreNum[2]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 0.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);

	}
	else
	{
		snprintf(aData2, sizeof(aData2), "3��:%d", m_ScoreNum[2]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 0.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}
	if (m_ScoreNum[3] != m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "4��:%d", m_ScoreNum[3]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 60.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);

	}
	else
	{
		snprintf(aData2, sizeof(aData2), "4��:%d", m_ScoreNum[3]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 60.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}
	if (m_ScoreNum[4] != m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "5��:%d", m_ScoreNum[4]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 120.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);

	}
	else
	{
		snprintf(aData2, sizeof(aData2), "5��:%d", m_ScoreNum[4]); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 120.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}

	aData = "�}�E�X���N���b�N/Start�{�^��/A�{�^��";

	if (m_bButtonBool == false)
	{
		m_nbuttonCnt += 2;

		if (m_nbuttonCnt > BUTTONCNT)
		{
			m_nbuttonCnt = BUTTONCNT;
			m_bButtonBool = true;
		}
	}
	else
	{
		m_nbuttonCnt -= 2;

		if (m_nbuttonCnt < 0)
		{
			m_nbuttonCnt = 0;
			m_bButtonBool = false;
		}
	}
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 310.0f, SCREEN_HEIGHT / 2.0f + 200.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, (float)m_nbuttonCnt*0.01f), aData);
}

//=============================
// Score�擾
//=============================
void CResult::ScoreLoad()
{
	FILE* pFile = nullptr; // �t�@�C���|�C���^��錾

	pFile = fopen("DATA\\score.txt", "r");

	if (pFile != nullptr)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fscanf(pFile, "%d", &m_ScoreNum[nCnt]);
		}

		fclose(pFile);//����
	}
}

//=============================
// �X�R�A�����o��
//=============================
void CResult::ScoreWrite()
{
	FILE* pFile = nullptr; // �t�@�C���|�C���^��錾

	pFile = fopen("DATA\\score.txt", "w");

	if (pFile != nullptr)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fprintf(pFile, "%d\n", m_ScoreNum[nCnt]);
		}

		fclose(pFile);//����
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



//+
//+�`���[�g���A���V�[��
//+



//===================================
// �R���X�g���N�^
//===================================
CTutorial::CTutorial()
{
}

//===================================
// �f�X�g���N�^
//===================================
CTutorial::~CTutorial()
{
}

//===================================
// ������
//===================================
HRESULT CTutorial::Init()
{
	CScore::ResetScore();

	m_TutorialUI = CTutorialUI::Create();

	return E_NOTIMPL;
}

//===================================
// �I��
//===================================
void CTutorial::Uninit()
{
	m_TutorialUI->Uninit();
	delete m_TutorialUI;
}

//===================================
// �X�V
//===================================
void CTutorial::Update()
{
	// �}�E�X�J�[�\����\���ɂ���
	int nDrawCnt = ShowCursor(TRUE);

	while (true)
	{
		if (nDrawCnt > 0)
		{//�\����Ԃ̂Ƃ�
			if (nDrawCnt > 1)
			{//2������
				nDrawCnt = ShowCursor(FALSE);
			}

			break;
		}
		else
		{//��\����Ԃ̂Ƃ�
			nDrawCnt = ShowCursor(TRUE);
		}
	}
	m_TutorialUI->Update();
}

//===================================
// �`��
//===================================
void CTutorial::Draw()
{
	CManager* pManager = CManager::GetInstance();

	m_TutorialUI->Draw();
}