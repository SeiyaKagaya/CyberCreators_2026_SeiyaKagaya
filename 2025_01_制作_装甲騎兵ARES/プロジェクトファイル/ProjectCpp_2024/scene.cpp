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
//#include "enemy_motion_fast.h"
//#include "target_UI.h"
#include "pause.h"
#include "Explosion3D.h"
#include "Tutorial.h"

#include "result.h"
//#include "ballet3D.h"
#include "newbullet.h"
#include "debugwall.h"
#include "3D-2DhitObject.h"
#include "sky.h"
#include "enemy_motion_fast.h"
#include "sea.h"
#include "3DParticle.h"
#include "missile.h"
#include "object_B2.h"
#include "enemy_motion_boss.h"
#include "enemy_motion_guard.h"
#include "motion_ship.h"

// �ÓI�����o�[�ϐ��̒�`
CScene::MODE CScene::m_NowState = CScene::MODE_TITLE; // �����l��MODE_TITLE�ɐݒ�
bool CScene::m_bStageClear = false;
bool CScene::m_bNextStageStay = false;

int CScene::m_ClearNum = 0;

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
	ResetClearNum();

	CScene* pScene = nullptr;

	CCamera::ResetCount();

	SetNowScene(mode);

	m_bNextStageStay = false;

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

	case MODE_RESULT:
		pScene = new CResult;
		break;
	case MODE_TUTORIAL:
		pScene = new CTutorial;
		break;
	case MODE_OP:
		pScene = new COP;
		break;
	case MODE_MOVIE:
		pScene = new CMovie;
		break;
	case MODE_MOVIE2:
		pScene = new CMovie2;
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
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------




///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------





//	CObjectFootPrint::Create(D3DXVECTOR3(10.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CObjectFootPrint::Create(D3DXVECTOR3(0.0f, 1.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CObjectFootPrint::Create(D3DXVECTOR3(30.0f, 1.0f, 30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

//	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM000);

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
	//	Explosion3D::Create(D3DXVECTOR3(10.0f, 500.0f, 10.0f));

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
	const char* aData = "���b�R��";
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 607.0f, SCREEN_HEIGHT / 2.0f - 308.0f, 0.0f), 193, CFont::FONT_MILITARY, D3DXCOLOR(0.5f, 0.4f, 0.1f, 1.0f), aData);

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 610.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 215, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

	aData = "ARES";
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 57.0f, SCREEN_HEIGHT / 2.0f + 108.0f, 0.0f), 193, CFont::FONT_MILITARY, D3DXCOLOR(0.5f, 0.4f, 0.1f, 1.0f), aData);

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 65.0f, SCREEN_HEIGHT / 2.0f + 110.0f, 0.0f), 218, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);





	aData = "Start�{�^��/A�{�^��";

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
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 310.0f, SCREEN_HEIGHT / 2.0f + 200.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(0.1f, 0.1f, 0.1f, (float)m_nbuttonCnt * 0.01f), aData);


}


///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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

///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//===================================
// �R���X�g���N�^
//===================================
COP::COP()
{
}

//===================================
// �f�X�g���N�^
//===================================
COP::~COP()
{

}
//===================================
// ������
//===================================
HRESULT COP::Init()
{
	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectMotion::DATA SetData = CObject::DataInit();//����������

	SetData.Pos = D3DXVECTOR3(14950.0f, 10.0f, 14950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);

	//player���ŏ��I
//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(5000.0f, 5490.0f, 5100.0f);
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);

	SetData.Pos = D3DXVECTOR3(5000.0f, 5200.0f, 5000.0f);
	CObjectB2::Create("DATA\\motion_B-2.txt", SetData);

	m_CGameUI = CGameUI::Create();
	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//D3DXCOLOR SetCol = (1.0f, 1.0f, 1.0f, 1.0f);


	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
	//	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

		//�t�H�O�J���[�ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));


	//D3DFOG_EXP(���x�w��̏ꍇ�̂ݐݒ肷��)
	float m_fFogDensity = 0.00005f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));

	//�t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	return E_NOTIMPL;
}
//===================================
// �I��
//===================================
void COP::Uninit()
{
	//m_CGameUI->Uninit();
	//m_CGameUI->SetDeath(true);
	//m_CTextWindow->Uninit();
	//m_CTextWindow->SetDeath(true);

}
//===================================
// �X�V
//===================================
void COP::Update()
{
	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	m_nCnt++;

	if (m_nCnt == 100)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 3, "�܂��Ȃ��~���|�C���g�B\n�R�[�X���Ȃ��B\n�����X�^���o�C�B", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 140);

		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 1, "<B-2�p�C���b�g>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 565);
	}


	if (m_nCnt == 390)
	{
		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 5, "3.........2.........1.........\n�����B", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 140);

	}

	if (m_nCnt == 720)
	{
		m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
	}





	if (m_nCnt == 760)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 2, "�X�s���b�h1�A\n����������𗣒E�B\n�v���C���[�B�����^���B", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80);
		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 1, "<B-2�p�C���b�g>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 190);
	}

	if (m_nCnt == 1010)
	{
		m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
	}



	if (m_nCnt == 1150)
	{
		CFade* pFade = pManager->GetFade();
		pFade->SetFade(CScene::MODE_GAME);
	}


	if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
	{
		CSound* pSound = pManager->GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);
		m_nCnt = 0;
		CFade* pFade = pManager->GetFade();
		pFade->SetFade(CScene::MODE_GAME);
	}


}
//===================================
// �`��
//===================================
void COP::Draw()
{
	CManager* pManager = CManager::GetInstance();



}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------


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
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);



	CTime::Create();
	CTime::ChangeTime(340);

	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//	CObject3D::Create();//����

	CObjectMotion::DATA SetData = CObject::DataInit();//����������

	SetData.Pos = D3DXVECTOR3(4950.0f, 10.0f, 4950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);

	SetData.Pos.y += 20.0f;
	SetData.rot.y = D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.2f);

	SetData.Pos.y += 30.0f;
	SetData.rot.y = -D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.1f);

	SetData = CObject::DataInit();//����������

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//�X�e�[�W�z�u�����[�h

	CScore::Create();

	//	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//�o�H�e�[�u�������[�h

	//	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//�ˌ��n�_�����[�h


	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();

	CNewBulletALL::Create();
	CObject3DParticleAll::Create();
	CMissileALL::Create();

	SetStayNextStage(false);

	//�z�u��
	//-------------------------------------------------------------------------------------------------------------------

	////���[
	//SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, 1200.0f);
	//SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	//SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	//StageCollisionBox::Create(SetData);


	//SetData.Pos = D3DXVECTOR3(3450.0f, 0.0f, 1200.0f);
	//SetData.MinLength = D3DXVECTOR3(-150.0f, 0.0f, -1200.0f);
	//SetData.MaxLength = D3DXVECTOR3(150.0f, 300.0f, 1200.0f);
	//StageCollisionBox::Create(SetData);


	//SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, -150.0f);
	//SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	//SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	//StageCollisionBox::Create(SetData);

	//SetData.Pos = D3DXVECTOR3(1650.0f, 0.0f, 2400.0f + 150.0f);
	//SetData.MinLength = D3DXVECTOR3(-1650.0f, 0.0f, -150.0f);
	//SetData.MaxLength = D3DXVECTOR3(1650.0f, 300.0f, 150.0f);
	//StageCollisionBox::Create(SetData);


	//SetData.Pos = D3DXVECTOR3(-150.0f, 0.0f, -150.0f);
	//SetData.MinLength = D3DXVECTOR3(-160.0f, 0.0f, -160.0f);
	//SetData.MaxLength = D3DXVECTOR3(160.0f, 300.0f, 160.0f);
	//StageCollisionBox::Create(SetData);


	//-------------------------------------------------------------------------------------------------------------------

	SetData.Pos = D3DXVECTOR3(-(3300.0f * 0.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));



	SetData.Pos = D3DXVECTOR3(-(3300.0f * 1.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));




	SetData.Pos = D3DXVECTOR3(-(3300.0f * 2.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));


















	//--------------------------------------------------------------------------------------------------------------------
	//2D�X�e�[�W�z�u��
	float ZPos = 250.0f;
	float Zlong = 750.0f;

	//���̋�
	SetData.Pos = D3DXVECTOR3(-14200, 1600.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(4500, 500.0f, Zlong - 200.0f);
	SetData.MinLength = D3DXVECTOR3(-4500.0f, -500.0f, -Zlong - 200.0f);
	StageCollisionBox::Create(SetData);
	//StageCollisionBox

	//stage���[�i���s��
	SetData.Pos = D3DXVECTOR3(-20000.0f, 8000.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(1300, 8000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1300, -8000.0f, -Zlong);
	StageCollisionBox::Create(SetData);

	//���A��i���s��
	SetData.Pos = D3DXVECTOR3(-9000.0f, 10300.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 7000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -7000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e���N���s��
	SetData.Pos = D3DXVECTOR3(800.0f, 9000.0f, 8000.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 9000.0f, 7000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -9000.0f, -7000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e���i���s��
	SetData.Pos = D3DXVECTOR3(4600.0f, 9000.0f, 16000.0f);
	SetData.MaxLength = D3DXVECTOR3(4600.0f, 9000.0f, Zlong + 200.0f);
	SetData.MinLength = D3DXVECTOR3(-4600.0f, -9000.0f, -(Zlong + 200.0f));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����X�e���i���s��2
	SetData.Pos = D3DXVECTOR3(6000.0f, 9000.0f, 17600.0f);
	SetData.MaxLength = D3DXVECTOR3(6000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-6000.0f, -9000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����X�e�E�N���s��
	SetData.Pos = D3DXVECTOR3(10050.0f, 2370.0f, 8350.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 2370.0f, 9000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -2370.0f, -9000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//����X�e�E��
	SetData.Pos = D3DXVECTOR3(13000.0f, 2370.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(2200.0f, 2370.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-2200.0f, -2370.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e�E�����
	SetData.Pos = D3DXVECTOR3(11550.0f, 10170.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(960.0f, 3000.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-960.0f, -3000.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//����X�e�E��
	SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 10200.0f);
	SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, Zlong + 8350.0f);
	SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -Zlong - 8350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e����{�X��O�i���s��
	SetData.Pos = D3DXVECTOR3(16000.0f, 9000.0f, -(Zlong * 2.0f) + 180.0f);
	SetData.MaxLength = D3DXVECTOR3(16000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-16000.0f, -9000.0f, -(Zlong));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);





		//���A�E�p�C�v1
	SetData.Pos = D3DXVECTOR3(4650.0f, 400.0f, 50.0f);
	SetData.MaxLength = D3DXVECTOR3(4650.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-4650.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//���A���s���p�C�v2
	SetData.Pos = D3DXVECTOR3(4200.0f, 400.0f, 4150.0f);
	SetData.MaxLength = D3DXVECTOR3(500.0f, 480.0f, 4150.0f);
	SetData.MinLength = D3DXVECTOR3(-500.0f, -480.0f, -4150.0f);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);Set
	StageCollisionBox::Create(SetData);



	//���A�E�p�C�v3(���)
	SetData.Pos = D3DXVECTOR3(2000.0f, 2850.0f, 5800.0f);
	SetData.MaxLength = D3DXVECTOR3(2000.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2000.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//���A�E�p�C�v4(��)
	SetData.Pos = D3DXVECTOR3(6600.0f, 400.0f, 7750.0f);
	SetData.MaxLength = D3DXVECTOR3(2600.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong + 100.0f);
	//	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong - 100.0f);
	StageCollisionBox::Create(SetData);

	//���A�E�p�C�v3(2��)
	SetData.Pos = D3DXVECTOR3(7900.0f, 4250.0f, 9900.0f);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);


	//�{�X�X�e�E��
	SetData.Pos = D3DXVECTOR3(28980.0f, 68.0f, 9150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�{�X�X�e�^�񒆏�
	SetData.Pos = D3DXVECTOR3(21915.0f, 68.0f, 2200.0f);
	SetData.MaxLength = D3DXVECTOR3(4765.0f, 68.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-4765.0f, -68.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�{�X�X�e����
	SetData.Pos = D3DXVECTOR3(14850.0f, 68.0f, 9150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�{�X�X�e�^�񒆉���
	SetData.Pos = D3DXVECTOR3(21915.0f, 4000.0f, 22050.0f);
	SetData.MaxLength = D3DXVECTOR3(9765.0f, 4000.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-9765.0f, -4000.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//�{�X�X�e�E��
	SetData.Pos = D3DXVECTOR3(32250.0f, 9000.0f, 9200.0f);
	SetData.MaxLength = D3DXVECTOR3(1000.0f, 9000.0f, Zlong + 9300.0f);
	SetData.MinLength = D3DXVECTOR3(-1000.0f, -9000.0f, -Zlong - 9300.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);












	//��ԉ������O
	SetData.Pos = D3DXVECTOR3(-3600.0f, 150.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(3600.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-3600.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//��ԉE���i
	SetData.Pos = D3DXVECTOR3(-750.0f, 600.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(750.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-750.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԉE���i
	SetData.Pos = D3DXVECTOR3(-300.0f, 1950.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԏ�i�E
	SetData.Pos = D3DXVECTOR3(-1200.0f, 2850.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1200.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1200.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԏ�i��
	SetData.Pos = D3DXVECTOR3(-3900.0f, 3000.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�E�Q�Ԗڏ�i
	SetData.Pos = D3DXVECTOR3(-1500.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�E�Q�Ԗڒ���i
	SetData.Pos = D3DXVECTOR3(-1650.0f, 1650.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//�E3�Ԗڒ��i
	SetData.Pos = D3DXVECTOR3(-3000.0f, 1500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�������i�E
	SetData.Pos = D3DXVECTOR3(-3750.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 750.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-150.0f, -750.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�������i��
	SetData.Pos = D3DXVECTOR3(-4350.0f, 1200.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 600.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -600.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�������㕔
	SetData.Pos = D3DXVECTOR3(-6000.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����������
	SetData.Pos = D3DXVECTOR3(-6300.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//�ō���
	SetData.Pos = D3DXVECTOR3(-8550.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1350.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1350.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����
	SetData.Pos = D3DXVECTOR3(-4950.0f, -500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//������
	SetData.Pos = D3DXVECTOR3(-4950.0f, 3800.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//-------------------------------------------------------------------------------------------------------------------



	//player���ŏ��I
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(-18000.0f, 2700.0f, 0.0f);
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------

	CObjectMotionPlayer::SetPlayerNum(1);

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������

	SetData.Pos = D3DXVECTOR3(-7500.0f, 2100.0f, 0.0f);
	SetData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(-6300.0f, 300.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(-4500.0f, 300.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);



	SetData.Pos = D3DXVECTOR3(-4500.0f, 1800.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(-3900.0f, 1800.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(-1700.0f, 1800.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(-3300.0f, 300.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(-1200.0f, 900.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);



	SetData.Pos = D3DXVECTOR3(-16653.0f, 2066.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(-14851.0f, 2066.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(-12794.0f, 2066.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(-10935.0f, 2066.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(-9088.20f, 2100.0f, 0.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	//----------------------------------------------------------------------------

	//SetData.Pos = D3DXVECTOR3(21500.0f, 0.0f, 7500.0f);
	//CObjectMotionEnemyBoss::Create("DATA\\motion_BossShip.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(19500.0f, 0.0f, 7500.0f);
	//CObjectMotionEnemyGuard::Create("DATA\\motion_warship.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(23500.0f, 0.0f, 7500.0f);
	//CObjectMotionEnemyGuard::Create("DATA\\motion_warship.txt", SetData);











	//-------------------------------------------------------------

	m_CGameUI = CGameUI::Create();

	m_StayTime = STAYFRAME;

	//	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);


	CSound* pSound = pManager->GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM001);

	//m_bNow3DMode = true;

	//

	pManager->SetbNow3DMode(false);


	return S_OK;
}
//===================================
// �I��
//===================================
void CGame::Uninit()
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	if (pSound != nullptr)
	{
	//	pSound->StopSound(CSound::SOUND_LABEL_BGM001);//�����ł͂Ƃ߂Ȃ�
	}

	//m_CGameUI->Uninit();
//	m_CGameUI->SetDeath(true);
	//m_CTextWindow->Uninit();
//	m_CTextWindow->SetDeath(true);
}
//===================================
// �X�V
//===================================
void CGame::Update()
{
	//// �}�E�X�J�[�\����\���ɂ���
	//int nDrawCnt = ShowCursor(TRUE);

	//while (true)
	//{
	//	if (nDrawCnt > 0)
	//	{//�\����Ԃ̂Ƃ�
	//		if (nDrawCnt > 1)
	//		{//2������
	//			nDrawCnt = ShowCursor(FALSE);
	//		}

	//		break;
	//	}
	//	else
	//	{//��\����Ԃ̂Ƃ�
	//		nDrawCnt = ShowCursor(TRUE);
	//	}
	//}

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	if (GetStayNextStage() == false)
	{
		if (pManager->GetStayState() == false)
		{
			if (pManager->GetPauseState() == false)
			{
				if (m_CGameUI->GetAllUiRestartNow() == false)
				{//Reset�N�����ĂȂ�
					CInputKeyboard* keyboard = pManager->GetKeyboard();
					if (keyboard->GetPress(DIK_RSHIFT) == true)
					{//�E�V�t�g�����ꂽ
						m_CGameUI->AllUiRestart();

						//mode�؂�ւ�
						if (pManager->GetbNow3DMode() == false)
						{
							pManager->SetbNow3DMode(true);
						}
						else
						{
							pManager->SetbNow3DMode(false);
						}
					}
				}
				else
				{//�N�����Ă�
					m_CGameUI->AllUiRestart();
				}

				if (CObjectMotionEnemyBoss::GetEnemyAllNum() <= 0)
				{//�G�r��	
					m_bNext = false;//true
					m_bStay2BOOL = true;
				}

				if (CTime::GetTime() <= 0)
				{//�������Ԑ؂�
					m_bNext = false;
					m_bStay2BOOL = true;
					pManager->SetStayState(true);
				}


				// �z�u���v���C�I���e�B�̐擪���擾
				CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

				if (pObject != nullptr)
				{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

					if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
					{ // �Ώۂ̃��f���̂Ƃ�
						CObject::DATA EscData;

						// �����Ŏg�p���錾
						CObjectMotionPlayer* pMotionPlayer;

						pMotionPlayer = (CObjectMotionPlayer*)pObject;

						D3DXVECTOR3 PlayerPos = pMotionPlayer->GetClassData().Pos;

						if (pMotionPlayer->GetPlayerNum() < 0)
						{//�c�@�܂��Ȃ���

							m_bNext = false;
							m_bStay2BOOL = true;
							pManager->SetStayState(true);
						}

						D3DXVECTOR3 GateMin = D3DXVECTOR3(-300.0f, 780.0f, -100.0f);
						D3DXVECTOR3 GateMax = D3DXVECTOR3(1500.0f, 2000.0f, 100.0f);

						if (GateMin.x <= PlayerPos.x && GateMax.x >= PlayerPos.x)
						{
							if (GateMin.y <= PlayerPos.y && GateMax.y >= PlayerPos.y)
							{
								if (GateMin.z <= PlayerPos.z && GateMax.z >= PlayerPos.z)
								{
									SetStayNextStage(true);
								}
							}
						}
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
				else
				{//�L�[�{�[�h���͔��f(�ړ�)
					if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
					{
						CSound* pSound = pManager->GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


						if (pManager->GetEndStatusState() == true)
						{//�N���ARoute
					/*		CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_GAME2);*/

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
	else
	{//���̃X�e�[�W�ɑJ��
		m_nCnt++;


		if (m_nCnt == 10)
		{
			m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 3, "�z�ǌQ�ɓ����B\n��@�J�n�B", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80);
			m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "< COM >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 170);
		}

		if (m_nCnt == 220)
		{
			m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
		}

		if (m_nCnt == 300)
		{
			//			CTime::ChangeTime(CTime::GetTime());
			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_MOVIE);
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


	//	CObstacleSet::DebugSetDataDraw();//�ݒu�p�f�o�b�O�`��
		//char cData2[100] = {};
		//snprintf(cData2, sizeof(cData2), "�c�@�F%d", CObjectMotionPlayer::GetPlayerNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
		//// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
		//CFont::DrawTextSet(D3DXVECTOR3(20.0f, 220.0f, 0.0f), 30, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);
		//
	if (pManager->GetPauseState() == false)
	{
	}
	else
	{
		m_Pause->Draw();
	}



	if (pManager->GetStayState() == true)
	{//�ҋ@���
		m_StayUI->Draw();

		//char aData2[100];

		//int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		//snprintf(aData2, sizeof(aData2), "�^�C���{�[�i�X:%d", nSetNum); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		//CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);


	}

	if (m_StayPush == true)
	{//�����ҋ@

//		CScore::AddScore();



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


	//char aData2[100];

	//snprintf(aData2, sizeof(aData2), "���݂̂���%d", CBullet3D::BulletNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

	//CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), aData2);




}


///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//===================================
// �R���X�g���N�^
//===================================
CMovie::CMovie()
{
}

//===================================
// �f�X�g���N�^
//===================================
CMovie::~CMovie()
{

}
//===================================
// ������
//===================================
HRESULT CMovie::Init()
{
	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectMotion::DATA SetData = CObject::DataInit();//����������

	SetData.Pos = D3DXVECTOR3(14950.0f, 10.0f, 14950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);



	float Zlong = 750.0f;
	float ZPos = 250.0f;




	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//�X�e�[�W�z�u�����[�h




	////����X�e���N���s��
	//SetData.Pos = D3DXVECTOR3(800.0f, 9000.0f, 8000.0f);
	//SetData.MaxLength = D3DXVECTOR3(800.0f, 9000.0f, 7000.0f);
	//SetData.MinLength = D3DXVECTOR3(-800.0f, -9000.0f, -7000.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////����X�e���i���s��
	//SetData.Pos = D3DXVECTOR3(4600.0f, 9000.0f, 16000.0f);
	//SetData.MaxLength = D3DXVECTOR3(4600.0f, 9000.0f, Zlong + 200.0f);
	//SetData.MinLength = D3DXVECTOR3(-4600.0f, -9000.0f, -(Zlong + 200.0f));
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	////����X�e���i���s��2
	//SetData.Pos = D3DXVECTOR3(6000.0f, 9000.0f, 17600.0f);
	//SetData.MaxLength = D3DXVECTOR3(6000.0f, 9000.0f, Zlong);
	//SetData.MinLength = D3DXVECTOR3(-6000.0f, -9000.0f, -Zlong);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	////����X�e�E�N���s��
	//SetData.Pos = D3DXVECTOR3(10050.0f, 2370.0f, 8350.0f);
	//SetData.MaxLength = D3DXVECTOR3(800.0f, 2370.0f, 9000.0f);
	//SetData.MinLength = D3DXVECTOR3(-800.0f, -2370.0f, -9000.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	////����X�e�E��
	//SetData.Pos = D3DXVECTOR3(13000.0f, 2370.0f, 0.0f);
	//SetData.MaxLength = D3DXVECTOR3(2200.0f, 2370.0f, Zlong + 350.0f);
	//SetData.MinLength = D3DXVECTOR3(-2200.0f, -2370.0f, -Zlong - 350.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////����X�e�E�����
	//SetData.Pos = D3DXVECTOR3(11550.0f, 10170.0f, 0.0f);
	//SetData.MaxLength = D3DXVECTOR3(960.0f, 3000.0f, Zlong + 350.0f);
	//SetData.MinLength = D3DXVECTOR3(-960.0f, -3000.0f, -Zlong - 350.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	////����X�e�E��
	//SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 10200.0f);
	//SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, Zlong + 8350.0f);
	//SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -Zlong - 8350.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////����X�e����{�X��O�i���s��
	//SetData.Pos = D3DXVECTOR3(16000.0f, 9000.0f, -(Zlong * 2.0f) + 180.0f);
	//SetData.MaxLength = D3DXVECTOR3(16000.0f, 9000.0f, Zlong);
	//SetData.MinLength = D3DXVECTOR3(-16000.0f, -9000.0f, -(Zlong));
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);





	//	//���A�E�p�C�v1
	//SetData.Pos = D3DXVECTOR3(4650.0f, 400.0f, 50.0f);
	//SetData.MaxLength = D3DXVECTOR3(4650.0f, 480.0f, Zlong - 100.0f);
	//SetData.MinLength = D3DXVECTOR3(-4650.0f, -480.0f, -Zlong + 100.0f);
	//StageCollisionBox::Create(SetData);

	////���A���s���p�C�v2
	//SetData.Pos = D3DXVECTOR3(4200.0f, 400.0f, 4150.0f);
	//SetData.MaxLength = D3DXVECTOR3(500.0f, 480.0f, 4150.0f);
	//SetData.MinLength = D3DXVECTOR3(-500.0f, -480.0f, -4150.0f);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);Set
	//StageCollisionBox::Create(SetData);



	////���A�E�p�C�v3(���)
	//SetData.Pos = D3DXVECTOR3(2000.0f, 2850.0f, 5800.0f);
	//SetData.MaxLength = D3DXVECTOR3(2000.0f, 480.0f, Zlong - 100.0f);
	//SetData.MinLength = D3DXVECTOR3(-2000.0f, -480.0f, -Zlong + 100.0f);
	//StageCollisionBox::Create(SetData);

	////���A�E�p�C�v4(��)
	//SetData.Pos = D3DXVECTOR3(6600.0f, 400.0f, 7750.0f);
	//SetData.MaxLength = D3DXVECTOR3(2600.0f, 480.0f, Zlong - 100.0f);
	//SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong + 100.0f);
	////	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong - 100.0f);
	//StageCollisionBox::Create(SetData);

	////���A�E�p�C�v3(2��)
	//SetData.Pos = D3DXVECTOR3(7900.0f, 4250.0f, 9900.0f);
	//SetData.MaxLength = D3DXVECTOR3(1500.0f, 480.0f, Zlong - 100.0f);
	//SetData.MinLength = D3DXVECTOR3(-1500.0f, -480.0f, -Zlong + 100.0f);
	//StageCollisionBox::Create(SetData);


	////�{�X�X�e�E��
	//SetData.Pos = D3DXVECTOR3(28980.0f, 68.0f, 9150.0f);
	//SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	//SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	////�{�X�X�e�^�񒆏�
	//SetData.Pos = D3DXVECTOR3(21915.0f, 68.0f, 2200.0f);
	//SetData.MaxLength = D3DXVECTOR3(4765.0f, 68.0f, 2945.0f);
	//SetData.MinLength = D3DXVECTOR3(-4765.0f, -68.0f, -2945.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////�{�X�X�e����
	//SetData.Pos = D3DXVECTOR3(14850.0f, 68.0f, 9150.0f);
	//SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	//SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////�{�X�X�e�^�񒆉���
	//SetData.Pos = D3DXVECTOR3(21915.0f, 4000.0f, 22050.0f);
	//SetData.MaxLength = D3DXVECTOR3(9765.0f, 4000.0f, 2945.0f);
	//SetData.MinLength = D3DXVECTOR3(-9765.0f, -4000.0f, -2945.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	////�{�X�X�e�E��
	//SetData.Pos = D3DXVECTOR3(32250.0f, 9000.0f, 9200.0f);
	//SetData.MaxLength = D3DXVECTOR3(1000.0f, 9000.0f, Zlong + 9300.0f);
	//SetData.MinLength = D3DXVECTOR3(-1000.0f, -9000.0f, -Zlong - 9300.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);












	//��ԉ������O
	SetData.Pos = D3DXVECTOR3(-3600.0f, 150.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(3600.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-3600.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//��ԉE���i
	SetData.Pos = D3DXVECTOR3(-750.0f, 600.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(750.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-750.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԉE���i
	SetData.Pos = D3DXVECTOR3(-300.0f, 1950.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԏ�i�E
	SetData.Pos = D3DXVECTOR3(-1200.0f, 2850.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1200.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1200.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԏ�i��
	SetData.Pos = D3DXVECTOR3(-3900.0f, 3000.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�E�Q�Ԗڏ�i
	SetData.Pos = D3DXVECTOR3(-1500.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�E�Q�Ԗڒ���i
	SetData.Pos = D3DXVECTOR3(-1650.0f, 1650.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//�E3�Ԗڒ��i
	SetData.Pos = D3DXVECTOR3(-3000.0f, 1500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�������i�E
	SetData.Pos = D3DXVECTOR3(-3750.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 750.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-150.0f, -750.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�������i��
	SetData.Pos = D3DXVECTOR3(-4350.0f, 1200.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 600.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -600.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�������㕔
	SetData.Pos = D3DXVECTOR3(-6000.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����������
	SetData.Pos = D3DXVECTOR3(-6300.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//�ō���
	SetData.Pos = D3DXVECTOR3(-8550.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1350.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1350.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����
	SetData.Pos = D3DXVECTOR3(-4950.0f, -500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//������
	SetData.Pos = D3DXVECTOR3(-4950.0f, 3800.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);





	SetData.Pos = D3DXVECTOR3(8620.0f, 880.0f, 30.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(4260.0f, 880.0f, 4760.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(4110.0f, 880.0f, 7720.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(6580.0f, 880.0f, 7860.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(8750.0f, 880.0f, 7850.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(2040.0f, 3370.0f, 5290.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(3850.0f, 3370.0f, 5310.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(7280.0f, 4760.0f, 9360.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9350.0f, 4760.0f, 12980.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9320.0f, 4760.0f, 6400.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9300.0f, 4760.0f, 1940.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);










	//player���ŏ��I
//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(800.0f, 890.0f, 0.0f);
	//SetData.rot.y = -1.57f;
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);


	m_CGameUI = CGameUI::Create();
	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();



	return S_OK;
}
//===================================
// �I��
//===================================
void CMovie::Uninit()
{
	//m_CGameUI->Uninit();
	//m_CGameUI->SetDeath(true);
	//m_CTextWindow->Uninit();
	//m_CTextWindow->SetDeath(true);

}
//===================================
// �X�V
//===================================
void CMovie::Update()
{
	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	m_nCnt++;

	if (m_nCnt == 100)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 3, "�O�ǉE��ɓ������m�F�B\n�p�C�v�𗘗p���ēo�邱�Ƃ�\n�����B", D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 240);

		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<COM>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1060);
	}


	if (m_nCnt == 450)
	{
		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 3, "���̐퓬���[�h�N��\n���삪3D�ɂȂ蒆����\n�߂�����Ɏˌ��Ŕ��C�B", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);

	}

	if (m_nCnt == 800)
	{
		//m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 2, "�~�T�C���̎g�p�����B\n�����b�N�̑���ɔ��ˁB\n���Ԍo�߂ŕ�[�����B", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);
		//m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 1, "<B-2�p�C���b�g>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 190);
	}

	if (m_nCnt == 1210)
	{
		m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
	}



	if (m_nCnt == 1250)
	{
		CFade* pFade = pManager->GetFade();
		pFade->SetFade(CScene::MODE_GAME2);
	}


	if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
	{
		CSound* pSound = pManager->GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);
		m_nCnt = 0;
		CFade* pFade = pManager->GetFade();
		pFade->SetFade(CScene::MODE_GAME2);
	}


}
//===================================
// �`��
//===================================
void CMovie::Draw()
{
	CManager* pManager = CManager::GetInstance();



}






//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);



	CTime::Create();

	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//	CObject3D::Create();//����

	CObjectMotion::DATA SetData = CObject::DataInit();//����������

	SetData.Pos = D3DXVECTOR3(4950.0f, 10.0f, 4950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);

	SetData.Pos.y += 20.0f;
	SetData.rot.y = D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.2f);

	SetData.Pos.y += 30.0f;
	SetData.rot.y = -D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.1f);

	SetData = CObject::DataInit();//����������

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//�X�e�[�W�z�u�����[�h

	CScore::Create();

	//	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//�o�H�e�[�u�������[�h

	//	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//�ˌ��n�_�����[�h


	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();

	pManager->SetbNow3DMode(true);

	m_CGameUI = CGameUI::Create();

	CNewBulletALL::Create();
	CObject3DParticleAll::Create();
	CMissileALL::Create();

	SetStayNextStage(false);

	//�z�u��
	//-------------------------------------------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------------------------------------

	SetData.Pos = D3DXVECTOR3(-(3300.0f * 0.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));



	SetData.Pos = D3DXVECTOR3(-(3300.0f * 1.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));




	SetData.Pos = D3DXVECTOR3(-(3300.0f * 2.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));


















	//--------------------------------------------------------------------------------------------------------------------
	//2D�X�e�[�W�z�u��
	float ZPos = 250.0f;
	float Zlong = 750.0f;

	//���̋�
	SetData.Pos = D3DXVECTOR3(-14200, 1600.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(4500, 500.0f, Zlong - 200.0f);
	SetData.MinLength = D3DXVECTOR3(-4500.0f, -500.0f, -Zlong - 200.0f);
	StageCollisionBox::Create(SetData);
	//StageCollisionBox

	//stage���[�i���s��
	SetData.Pos = D3DXVECTOR3(-20000.0f, 8000.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(1300, 8000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1300, -8000.0f, -Zlong);
	StageCollisionBox::Create(SetData);

	//���A��i���s��
	SetData.Pos = D3DXVECTOR3(-9000.0f, 10300.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 7000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -7000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e���N���s��
	SetData.Pos = D3DXVECTOR3(800.0f, 9000.0f, 8000.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 9000.0f, 7000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -9000.0f, -7000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e���i���s��
	SetData.Pos = D3DXVECTOR3(4600.0f, 9000.0f, 16000.0f);
	SetData.MaxLength = D3DXVECTOR3(4600.0f, 9000.0f, Zlong + 200.0f);
	SetData.MinLength = D3DXVECTOR3(-4600.0f, -9000.0f, -(Zlong + 200.0f));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����X�e���i���s��2
	SetData.Pos = D3DXVECTOR3(6000.0f, 9000.0f, 17600.0f);
	SetData.MaxLength = D3DXVECTOR3(6000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-6000.0f, -9000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����X�e�E�N���s��
	SetData.Pos = D3DXVECTOR3(10050.0f, 2370.0f, 8350.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 2370.0f, 9000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -2370.0f, -9000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//����X�e�E��
	SetData.Pos = D3DXVECTOR3(13000.0f, 2370.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(2200.0f, 2370.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-2200.0f, -2370.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e�E�����
	SetData.Pos = D3DXVECTOR3(11550.0f, 10170.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(960.0f, 3000.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-960.0f, -3000.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//����X�e�E��
	SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 10200.0f);
	SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, Zlong + 8350.0f);
	SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -Zlong - 8350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e����{�X��O�i���s��
	SetData.Pos = D3DXVECTOR3(16000.0f, 9000.0f, -(Zlong * 2.0f) + 180.0f);
	SetData.MaxLength = D3DXVECTOR3(16000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-16000.0f, -9000.0f, -(Zlong));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);





		//���A�E�p�C�v1
	SetData.Pos = D3DXVECTOR3(4650.0f, 400.0f, 50.0f);
	SetData.MaxLength = D3DXVECTOR3(4650.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-4650.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//���A���s���p�C�v2
	SetData.Pos = D3DXVECTOR3(4200.0f, 400.0f, 4150.0f);
	SetData.MaxLength = D3DXVECTOR3(500.0f, 480.0f, 4150.0f);
	SetData.MinLength = D3DXVECTOR3(-500.0f, -480.0f, -4150.0f);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);Set
	StageCollisionBox::Create(SetData);



	//���A�E�p�C�v3(���)
	SetData.Pos = D3DXVECTOR3(2000.0f, 2850.0f, 5800.0f);
	SetData.MaxLength = D3DXVECTOR3(2000.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2000.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//���A�E�p�C�v4(��)
	SetData.Pos = D3DXVECTOR3(6600.0f, 400.0f, 7750.0f);
	SetData.MaxLength = D3DXVECTOR3(2600.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong + 100.0f);
	//	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong - 100.0f);
	StageCollisionBox::Create(SetData);

	//���A�E�p�C�v3(2��)
	SetData.Pos = D3DXVECTOR3(7900.0f, 4250.0f, 9900.0f);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);


	//�{�X�X�e�E��
	SetData.Pos = D3DXVECTOR3(28980.0f, 68.0f, 9150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�{�X�X�e�^�񒆏�
	SetData.Pos = D3DXVECTOR3(21915.0f, 68.0f, 2200.0f);
	SetData.MaxLength = D3DXVECTOR3(4765.0f, 68.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-4765.0f, -68.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�{�X�X�e����
	SetData.Pos = D3DXVECTOR3(14850.0f, 68.0f, 9150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�{�X�X�e�^�񒆉���
	SetData.Pos = D3DXVECTOR3(21915.0f, 4000.0f, 22050.0f);
	SetData.MaxLength = D3DXVECTOR3(9765.0f, 4000.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-9765.0f, -4000.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//�{�X�X�e�E��
	SetData.Pos = D3DXVECTOR3(32250.0f, 9000.0f, 9200.0f);
	SetData.MaxLength = D3DXVECTOR3(1000.0f, 9000.0f, Zlong + 9300.0f);
	SetData.MinLength = D3DXVECTOR3(-1000.0f, -9000.0f, -Zlong - 9300.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);












	//��ԉ������O
	SetData.Pos = D3DXVECTOR3(-3600.0f, 150.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(3600.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-3600.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//��ԉE���i
	SetData.Pos = D3DXVECTOR3(-750.0f, 600.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(750.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-750.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԉE���i
	SetData.Pos = D3DXVECTOR3(-300.0f, 1950.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԏ�i�E
	SetData.Pos = D3DXVECTOR3(-1200.0f, 2850.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1200.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1200.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԏ�i��
	SetData.Pos = D3DXVECTOR3(-3900.0f, 3000.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�E�Q�Ԗڏ�i
	SetData.Pos = D3DXVECTOR3(-1500.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�E�Q�Ԗڒ���i
	SetData.Pos = D3DXVECTOR3(-1650.0f, 1650.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//�E3�Ԗڒ��i
	SetData.Pos = D3DXVECTOR3(-3000.0f, 1500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�������i�E
	SetData.Pos = D3DXVECTOR3(-3750.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 750.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-150.0f, -750.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�������i��
	SetData.Pos = D3DXVECTOR3(-4350.0f, 1200.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 600.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -600.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�������㕔
	SetData.Pos = D3DXVECTOR3(-6000.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����������
	SetData.Pos = D3DXVECTOR3(-6300.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//�ō���
	SetData.Pos = D3DXVECTOR3(-8550.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1350.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1350.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����
	SetData.Pos = D3DXVECTOR3(-4950.0f, -500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//������
	SetData.Pos = D3DXVECTOR3(-4950.0f, 3800.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//-------------------------------------------------------------------------------------------------------------------



	//player���ŏ��I
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(1200.0f, 893.0f, 0.0f);
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------

	CObjectMotionPlayer::SetPlayerNum(1);

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������

	//SetData.Pos = D3DXVECTOR3(-7500.0f, 2100.0f, 0.0f);
	//SetData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetData.Pos = D3DXVECTOR3(8620.0f, 880.0f, 30.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(4260.0f, 880.0f, 4760.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(4110.0f, 880.0f, 7720.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(6580.0f, 880.0f, 7860.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(8750.0f, 880.0f, 7850.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(2040.0f, 3370.0f, 5290.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(3850.0f, 3370.0f, 5310.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(7280.0f, 4760.0f, 9360.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9350.0f, 4760.0f, 12980.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9320.0f, 4760.0f, 6400.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9300.0f, 4760.0f, 1940.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_hellcpter.txt", SetData);











	//-------------------------------------------------------------

	m_StayTime = STAYFRAME;

	//	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);


	//CSound* pSound = pManager->GetSound();


	//pSound->StopSound(CSound::SOUND_LABEL_BGM001);

	//pSound->PlaySound(CSound::SOUND_LABEL_BGM002);

	//m_bNow3DMode = true;

	//

//	m_CGameUI->AllUiRestart();

	return S_OK;
}
//===================================
// �I��
//===================================
void CGame2::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CSound* pSound = pManager->GetSound();
	if (pSound != nullptr)
	{
		pSound->StopSound(CSound::SOUND_LABEL_BGM001);
	}
		//m_CGameUI->Uninit();
		//m_CGameUI->SetDeath(true);
}
//===================================
// �X�V
//===================================
void CGame2::Update()
{
	//// �}�E�X�J�[�\����\���ɂ���
//int nDrawCnt = ShowCursor(TRUE);

//while (true)
//{
//	if (nDrawCnt > 0)
//	{//�\����Ԃ̂Ƃ�
//		if (nDrawCnt > 1)
//		{//2������
//			nDrawCnt = ShowCursor(FALSE);
//		}

//		break;
//	}
//	else
//	{//��\����Ԃ̂Ƃ�
//		nDrawCnt = ShowCursor(TRUE);
//	}
//}

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	if (GetStayNextStage() == false)
	{
		if (pManager->GetStayState() == false)
		{
			if (pManager->GetPauseState() == false)
			{
				if (m_CGameUI->GetAllUiRestartNow() == false)
				{//Reset�N�����ĂȂ�
					CInputKeyboard* keyboard = pManager->GetKeyboard();
					if (keyboard->GetPress(DIK_RSHIFT) == true)
					{//�E�V�t�g�����ꂽ
						m_CGameUI->AllUiRestart();

						//mode�؂�ւ�
						if (pManager->GetbNow3DMode() == false)
						{
							pManager->SetbNow3DMode(true);
						}
						else
						{
							pManager->SetbNow3DMode(false);
						}
					}
				}
				else
				{//�N�����Ă�
					m_CGameUI->AllUiRestart();
				}

				if (CObjectMotionEnemyBoss::GetEnemyAllNum() <= 0)
				{//�G�r��	
					m_bNext = false;//true
					m_bStay2BOOL = true;
				}

				if (CTime::GetTime() <= 0)
				{//�������Ԑ؂�
					m_bNext = false;
					m_bStay2BOOL = true;
					pManager->SetStayState(true);
				}


				// �z�u���v���C�I���e�B�̐擪���擾
				CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

				if (pObject != nullptr)
				{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

					if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
					{ // �Ώۂ̃��f���̂Ƃ�
						CObject::DATA EscData;

						// �����Ŏg�p���錾
						CObjectMotionPlayer* pMotionPlayer;

						pMotionPlayer = (CObjectMotionPlayer*)pObject;

						D3DXVECTOR3 PlayerPos = pMotionPlayer->GetClassData().Pos;

						if (pMotionPlayer->GetPlayerNum() < 0)
						{//�c�@�܂��Ȃ���

							m_bNext = false;
							m_bStay2BOOL = true;
							pManager->SetStayState(true);
						}

						D3DXVECTOR3 GateMin = D3DXVECTOR3(10800.0f, 4000.0f, -500.0f);
						D3DXVECTOR3 GateMax = D3DXVECTOR3(13000.0f, 9000.0f, 1100.0f);

						if (GateMin.x <= PlayerPos.x && GateMax.x >= PlayerPos.x)
						{
							if (GateMin.y <= PlayerPos.y && GateMax.y >= PlayerPos.y)
							{
								if (GateMin.z <= PlayerPos.z && GateMax.z >= PlayerPos.z)
								{
									SetStayNextStage(true);
								}
							}
						}
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
				else
				{//�L�[�{�[�h���͔��f(�ړ�)
					if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
					{
						CSound* pSound = pManager->GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


						if (pManager->GetEndStatusState() == true)
						{//�N���ARoute
					/*		CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_GAME2);*/

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
	else
	{//���̃X�e�[�W�ɑJ��
		m_nCnt++;


		if (m_nCnt == 10)
		{
			m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 3, "�R�`�O�ɓ����B\n�ҋ@����B", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80);
			m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "< COM >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 170);
		}

		if (m_nCnt == 220)
		{
			m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
		}

		if (m_nCnt == 300)
		{
			//			CTime::ChangeTime(CTime::GetTime());
			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_MOVIE2);
		}

	}
}
//===================================
// �`��
//===================================
void CGame2::Draw()
{
	//	CObstacleSet::DebugSetDataDraw();//�ݒu�p�f�o�b�O�`��
	char cData2[100] = {};
	//snprintf(cData2, sizeof(cData2), "���@�c�@�F%d", CObjectMotionPlayer::GetPlayerNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
	//// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
	//CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_MILITARY, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);



	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	if (pManager->GetPauseState() == false)
	{
	}
	else
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//�ҋ@���
		m_StayUI->Draw();

		//char aData2[100];

		//int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		//snprintf(aData2, sizeof(aData2), "�^�C���{�[�i�X:%d", nSetNum); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		//CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);

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
///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//===================================
// �R���X�g���N�^
//===================================
CMovie2::CMovie2()
{
}

//===================================
// �f�X�g���N�^
//===================================
CMovie2::~CMovie2()
{

}
//===================================
// ������
//===================================
HRESULT CMovie2::Init()
{
	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectMotion::DATA SetData = CObject::DataInit();//����������

	SetData.Pos = D3DXVECTOR3(14950.0f, 10.0f, 14950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);



	float Zlong = 750.0f;
	float ZPos = 250.0f;




	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//�X�e�[�W�z�u�����[�h




	//player���ŏ��I
//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(13650.0f, 4750.0f, 850.0f);
	//SetData.rot.y = -1.57f;
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);


	SetData.Pos = D3DXVECTOR3(19500.0f, 0.0f, 17500.0f);
	//SetData.rot.y = -1.57f;
	CObjectShip::Create("DATA\\motion_friendship.txt", SetData);



	SetData.Pos = D3DXVECTOR3(28267.3f, 109.2f, 14727.2f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29990.5f, 134.1f, 11353.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29007.5f, 98.2f, 8101.8f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29471.1f, 132.4f, 1642.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(25086.5f, 138.0f, 1537.6f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(20708.3f, 102.6f, 2084.1f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14638.1f, 111.3f, 3419.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(15514.9f, 138.0f, 6690.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14446.6f, 95.7f, 10788.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(13519.9f, 104.4f, 14477.9f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(15073.8f, 111.5f, 17979.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14489.6f, 867.6f, 7604.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14256.6f, 867.9f, 11816.8f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(16592.6f, 871.9f, 3222.6f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(25563.8f, 827.2f, 3104.1f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29397.4f, 824.2f, 9599.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);












	SetData.Pos = D3DXVECTOR3(23500.0f, 0.0f, 17500.0f);
	//SetData.rot.y = -1.57f;
	CObjectShip::Create("DATA\\motion_friendship.txt", SetData);

	SetData.Pos = D3DXVECTOR3(21500.0f, 0.0f, 7500.0f);
	CObjectMotionEnemyBoss::Create("DATA\\motion_BossShip.txt", SetData);

	SetData.Pos = D3DXVECTOR3(19500.0f, -310.0f, 7500.0f);
	CObjectMotionEnemyGuard::Create("DATA\\motion_warship.txt", SetData);

	SetData.Pos = D3DXVECTOR3(23500.0f, -310.0f, 7500.0f);
	CObjectMotionEnemyGuard::Create("DATA\\motion_warship.txt", SetData);

	m_CGameUI = CGameUI::Create();
	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();

	return S_OK;
}
//===================================
// �I��
//===================================
void CMovie2::Uninit()
{
	//m_CGameUI->Uninit();
	//m_CGameUI->SetDeath(true);
	//m_CTextWindow->Uninit();
	//m_CTextWindow->SetDeath(true);

}
//===================================
// �X�V
//===================================
void CMovie2::Update()
{
	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	m_nCnt++;

	if (m_nCnt == 100)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "������A\n�G�V�^���P�g����\n�̕ߔ����J�n�B", D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 260);

		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<�ߔ��͑�>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1060);
	}


	if (m_nCnt == 450)
	{
		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 3, "....!!\n12�����A�N�e�B�u�\�i�[�I\n�����ڋ߁I����I", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);

	}

	if (m_nCnt == 800)
	{
		//m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 2, "�N�\�b............�����ފ́I\n.........................\n...............", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);
		//m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 1, "<B-2�p�C���b�g>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 190);
	}

	if (m_nCnt == 1210)
	{
		m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
	}



	if (m_nCnt == 1250)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 20, 40, 3, "  -Mission Update-\n�G�C�����͂ɂ��ߔ����s!!\n�����͂Ɨg���͂���������!", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 470);


		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<�i�ߕ�>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000);
	}

	if (m_nCnt == 1680)
	{
		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 20, 40, 3, "�O�ǌ������_�ō�퐬���B\n�����Ď��Ԑ؂�œ��S�Ƃ݂Ȃ�\n���s�Ƃ���B", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 380);

	}

	if (m_nCnt == 2300)
	{
		m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
	}



	if (m_nCnt == 2450)
	{
		CFade* pFade = pManager->GetFade();
		pFade->SetFade(CScene::MODE_GAME3);
	}


	if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
	{
		CSound* pSound = pManager->GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);
		m_nCnt = 0;
		CFade* pFade = pManager->GetFade();
		pFade->SetFade(CScene::MODE_GAME3);
	}


}
//===================================
// �`��
//===================================
void CMovie2::Draw()
{
	CManager* pManager = CManager::GetInstance();



}



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�H�O�̗L���ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);



	CTime::Create();
	CTime::ChangeTime(70);

	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//	CObject3D::Create();//����

	CObjectMotion::DATA SetData = CObject::DataInit();//����������

	SetData.Pos = D3DXVECTOR3(4950.0f, 10.0f, 4950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);

	SetData.Pos.y += 20.0f;
	SetData.rot.y = D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.2f);

	SetData.Pos.y += 30.0f;
	SetData.rot.y = -D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.1f);

	SetData = CObject::DataInit();//����������

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//�X�e�[�W�z�u�����[�h

	CScore::Create();

	//	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//�o�H�e�[�u�������[�h

	//	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//�ˌ��n�_�����[�h


	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();

	pManager->SetbNow3DMode(true);

	m_CGameUI = CGameUI::Create();

	CNewBulletALL::Create();
	CObject3DParticleAll::Create();
	CMissileALL::Create();

	SetStayNextStage(false);

	//�z�u��
	//-------------------------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------------------------

	SetData.Pos = D3DXVECTOR3(-(3300.0f * 0.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));



	SetData.Pos = D3DXVECTOR3(-(3300.0f * 1.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));




	SetData.Pos = D3DXVECTOR3(-(3300.0f * 2.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));


















	//--------------------------------------------------------------------------------------------------------------------
	//2D�X�e�[�W�z�u��
	float ZPos = 250.0f;
	float Zlong = 750.0f;

	//���̋�
	SetData.Pos = D3DXVECTOR3(-14200, 1600.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(4500, 500.0f, Zlong - 200.0f);
	SetData.MinLength = D3DXVECTOR3(-4500.0f, -500.0f, -Zlong - 200.0f);
	StageCollisionBox::Create(SetData);
	//StageCollisionBox

	//stage���[�i���s��
	SetData.Pos = D3DXVECTOR3(-20000.0f, 8000.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(1300, 8000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1300, -8000.0f, -Zlong);
	StageCollisionBox::Create(SetData);

	//���A��i���s��
	SetData.Pos = D3DXVECTOR3(-9000.0f, 10300.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 7000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -7000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e���N���s��
	SetData.Pos = D3DXVECTOR3(800.0f, 9000.0f, 8000.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 9000.0f, 7000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -9000.0f, -7000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e���i���s��
	SetData.Pos = D3DXVECTOR3(4600.0f, 9000.0f, 16000.0f);
	SetData.MaxLength = D3DXVECTOR3(4600.0f, 9000.0f, Zlong + 200.0f);
	SetData.MinLength = D3DXVECTOR3(-4600.0f, -9000.0f, -(Zlong + 200.0f));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����X�e���i���s��2
	SetData.Pos = D3DXVECTOR3(6000.0f, 9000.0f, 17600.0f);
	SetData.MaxLength = D3DXVECTOR3(6000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-6000.0f, -9000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����X�e�E�N���s��
	SetData.Pos = D3DXVECTOR3(10050.0f, 2370.0f, 8350.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 2370.0f, 9000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -2370.0f, -9000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//����X�e�E��
	SetData.Pos = D3DXVECTOR3(13000.0f, 2370.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(2200.0f, 2370.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-2200.0f, -2370.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e�E�����
	SetData.Pos = D3DXVECTOR3(11550.0f, 10170.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(960.0f, 3000.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-960.0f, -3000.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//����X�e�E��
	SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 10200.0f);
	SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, Zlong + 8350.0f);
	SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -Zlong - 8350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//����X�e����{�X��O�i���s��
	SetData.Pos = D3DXVECTOR3(16000.0f, 9000.0f, -(Zlong * 2.0f) + 180.0f);
	SetData.MaxLength = D3DXVECTOR3(16000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-16000.0f, -9000.0f, -(Zlong));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);





		//���A�E�p�C�v1
	SetData.Pos = D3DXVECTOR3(4650.0f, 400.0f, 50.0f);
	SetData.MaxLength = D3DXVECTOR3(4650.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-4650.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//���A���s���p�C�v2
	SetData.Pos = D3DXVECTOR3(4200.0f, 400.0f, 4150.0f);
	SetData.MaxLength = D3DXVECTOR3(500.0f, 480.0f, 4150.0f);
	SetData.MinLength = D3DXVECTOR3(-500.0f, -480.0f, -4150.0f);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);Set
	StageCollisionBox::Create(SetData);



	//���A�E�p�C�v3(���)
	SetData.Pos = D3DXVECTOR3(2000.0f, 2850.0f, 5800.0f);
	SetData.MaxLength = D3DXVECTOR3(2000.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2000.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//���A�E�p�C�v4(��)
	SetData.Pos = D3DXVECTOR3(6600.0f, 400.0f, 7750.0f);
	SetData.MaxLength = D3DXVECTOR3(2600.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong + 100.0f);
	//	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong - 100.0f);
	StageCollisionBox::Create(SetData);

	//���A�E�p�C�v3(2��)
	SetData.Pos = D3DXVECTOR3(7900.0f, 4250.0f, 9900.0f);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);



	//����X�e�E��
	SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 22150.0f);
	SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, 22150.0f);
	SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -22150.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�{�X�X�e�E��----------------------------------------------------------------------------
	SetData.Pos = D3DXVECTOR3(28980.0f, 68.0f, 22150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 22150.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -22150.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�{�X�X�e�^�񒆏�
	SetData.Pos = D3DXVECTOR3(21915.0f, 68.0f, 2200.0f);
	SetData.MaxLength = D3DXVECTOR3(4765.0f, 68.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-4765.0f, -68.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�{�X�X�e����
	SetData.Pos = D3DXVECTOR3(14850.0f, 68.0f, 22150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 22150.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -22150.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�{�X�X�e�^�񒆉���
	SetData.Pos = D3DXVECTOR3(21915.0f, 4000.0f, 44300.0f);
	SetData.MaxLength = D3DXVECTOR3(9765.0f, 4000.0f, 3000.0f);
	SetData.MinLength = D3DXVECTOR3(-9765.0f, -4000.0f, -3000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//�{�X�X�e�E��
	SetData.Pos = D3DXVECTOR3(32250.0f, 9000.0f, 22150.0f);
	SetData.MaxLength = D3DXVECTOR3(1000.0f, 9000.0f, 22150.0f);
	SetData.MinLength = D3DXVECTOR3(-1000.0f, -9000.0f, -22150.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);
	//------------------------------------------------------------------------------------------------











	//��ԉ������O
	SetData.Pos = D3DXVECTOR3(-3600.0f, 150.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(3600.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-3600.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//��ԉE���i
	SetData.Pos = D3DXVECTOR3(-750.0f, 600.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(750.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-750.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԉE���i
	SetData.Pos = D3DXVECTOR3(-300.0f, 1950.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԏ�i�E
	SetData.Pos = D3DXVECTOR3(-1200.0f, 2850.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1200.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1200.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//��ԏ�i��
	SetData.Pos = D3DXVECTOR3(-3900.0f, 3000.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�E�Q�Ԗڏ�i
	SetData.Pos = D3DXVECTOR3(-1500.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�E�Q�Ԗڒ���i
	SetData.Pos = D3DXVECTOR3(-1650.0f, 1650.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//�E3�Ԗڒ��i
	SetData.Pos = D3DXVECTOR3(-3000.0f, 1500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�������i�E
	SetData.Pos = D3DXVECTOR3(-3750.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 750.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-150.0f, -750.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//�������i��
	SetData.Pos = D3DXVECTOR3(-4350.0f, 1200.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 600.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -600.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//�������㕔
	SetData.Pos = D3DXVECTOR3(-6000.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����������
	SetData.Pos = D3DXVECTOR3(-6300.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//�ō���
	SetData.Pos = D3DXVECTOR3(-8550.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1350.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1350.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//����
	SetData.Pos = D3DXVECTOR3(-4950.0f, -500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//������
	SetData.Pos = D3DXVECTOR3(-4950.0f, 3800.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//-------------------------------------------------------------------------------------------------------------------



	//player���ŏ��I
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//������
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(13760.0f, 4730.0f, 700.0f);
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);


	SetData.Pos = D3DXVECTOR3(28267.3f, 109.2f, 14727.2f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29990.5f, 134.1f, 11353.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29007.5f, 98.2f, 8101.8f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29471.1f, 132.4f, 1642.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(25086.5f, 138.0f, 1537.6f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(20708.3f, 102.6f, 2084.1f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14638.1f, 111.3f, 3419.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(15514.9f, 138.0f, 6690.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14446.6f, 95.7f, 10788.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(13519.9f, 104.4f, 14477.9f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(15073.8f, 111.5f, 17979.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14489.6f, 867.6f, 7604.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14256.6f, 867.9f, 11816.8f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(16592.6f, 871.9f, 3222.6f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(25563.8f, 827.2f, 3104.1f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29397.4f, 824.2f, 9599.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);


	////-----------------------------------sssss-----------------------------------------

	//SetData.Pos = D3DXVECTOR3(21500.0f, 0.0f, 7500.0f);
	//CObjectMotionEnemyBoss::Create("DATA\\motion_BossShip.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(19500.0f, 0.0f, 7500.0f);
	//CObjectMotionEnemyGuard::Create("DATA\\motion_warship.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(23500.0f, 0.0f, 7500.0f);
	//CObjectMotionEnemyGuard::Create("DATA\\motion_warship.txt", SetData);





	SetData.Pos = D3DXVECTOR3(21500.0f, 0.0f, 7500.0f);
	CObjectMotionEnemyBoss::Create("DATA\\motion_BossShip.txt", SetData);

	SetData.Pos = D3DXVECTOR3(18500.0f, 10.0f, 7500.0f);
	CObjectMotionEnemyGuard::Create("DATA\\motion_warship.txt", SetData);

	SetData.Pos = D3DXVECTOR3(24500.0f, 10.0f, 7500.0f);
	CObjectMotionEnemyGuard::Create("DATA\\motion_warship.txt", SetData);





	//-------------------------------------------------------------

	m_StayTime = STAYFRAME;

	//	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);


	CSound* pSound = pManager->GetSound();


	pSound->StopSound(CSound::SOUND_LABEL_BGM001);


	pSound->PlaySound(CSound::SOUND_LABEL_BGM002);

	//m_bNow3DMode = true;

	//

//	m_CGameUI->AllUiRestart();

	return S_OK;
}
//===================================
// �I��
//===================================
void CGame3::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CSound* pSound = pManager->GetSound();
	if (pSound != nullptr)
	{
		pSound->StopSound(CSound::SOUND_LABEL_BGM002);
	}
	//m_CGameUI->Uninit();
	//m_CGameUI->SetDeath(true);
}
//===================================
// �X�V
//===================================
void CGame3::Update()
{
	//// �}�E�X�J�[�\����\���ɂ���
//int nDrawCnt = ShowCursor(TRUE);

//while (true)
//{
//	if (nDrawCnt > 0)
//	{//�\����Ԃ̂Ƃ�
//		if (nDrawCnt > 1)
//		{//2������
//			nDrawCnt = ShowCursor(FALSE);
//		}

//		break;
//	}
//	else
//	{//��\����Ԃ̂Ƃ�
//		nDrawCnt = ShowCursor(TRUE);
//	}
//}

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	if (GetStayNextStage() == false)
	{
		if (pManager->GetStayState() == false)
		{
			if (pManager->GetPauseState() == false)
			{
				if (m_CGameUI->GetAllUiRestartNow() == false)
				{//Reset�N�����ĂȂ�

					m_nCnt++;

					if (m_nCnt == 60)
					{
						m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "�o���A�͌�q�͂��炾�I\n��q�͂��ɍU������I", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 260);

						m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<�i�ߕ�>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 720);
					}


					if (m_nCnt == 510)
					{
						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 2, "���͂���̐����I\n60�b�œ�������I\n�}���񂾁I", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 260);

					}
					if (m_nCnt == 870)
					{
						m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					}


					if (m_nCnt == 1000)
					{
						m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "�~�T�C���͋��Ђ��I\n�K�[�h���������񂾁I", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 200);

						m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<�i�ߕ�>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 380);
					}
					if (m_nCnt == 1400)
					{
						m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					}

					if (m_nCnt == 2300)
					{
						m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "�c��30�b�I�܂������I\n�}���Ō��j����񂾁I", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 200);

						m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<�i�ߕ�>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 380);
					}
					if (m_nCnt == 2700)
					{
						m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					}



					if (m_nCnt == 3200)
					{
						m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "�����I�������Ă��܂��I", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 200);

						m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<�i�ߕ�>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 380);
					}
					if (m_nCnt == 3600)
					{
						m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					}


					//if (m_nCnt == 1250)
					//{
					//	m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

					//	m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 20, 40, 3, "  -Mission Update-\n�G�C�����͂ɂ��ߔ����s!!\n�����͂Ɨg���͂���������!", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 470);


					//	m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<�i�ߕ�>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000);
					//}

					//if (m_nCnt == 1680)
					//{
					//	m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 20, 40, 3, "�O�ǌ������_�ō�퐬���B\n�����Ď��Ԑ؂�œ��S�Ƃ݂Ȃ�\n���s�Ƃ���B", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 380);

					//}

					//if (m_nCnt == 2300)
					//{
					//	m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					//}










					CInputKeyboard* keyboard = pManager->GetKeyboard();
					if (keyboard->GetPress(DIK_RSHIFT) == true)
					{//�E�V�t�g�����ꂽ
						m_CGameUI->AllUiRestart();

						//mode�؂�ւ�
						if (pManager->GetbNow3DMode() == false)
						{
							pManager->SetbNow3DMode(true);
						}
						else
						{
							pManager->SetbNow3DMode(false);
						}
					}
				}
				else
				{//�N�����Ă�
					m_CGameUI->AllUiRestart();
				}

				if (CObjectMotionEnemyBoss::GetEnemyAllNum() <= 0)
				{//�G�r��	
					m_bNext = false;//true
					m_bStay2BOOL = true;
				}

				if (CObjectMotionEnemyBoss::GetEnemyAllNum() <= 0)
				{//�G�r��	
					m_bNext = false;//true
					m_bStay2BOOL = true;
					pManager->SetStayState(true);
					pManager->SetEndStatusState(true);
					CScene::SetStageClear(true);
				}



				if (CTime::GetTime() <= 0)
				{//�������Ԑ؂�
					m_bNext = false;
					m_bStay2BOOL = true;
					pManager->SetStayState(true);
				}


				// �z�u���v���C�I���e�B�̐擪���擾
				CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

				if (pObject != nullptr)
				{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

					if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
					{ // �Ώۂ̃��f���̂Ƃ�
						CObject::DATA EscData;

						// �����Ŏg�p���錾
						CObjectMotionPlayer* pMotionPlayer;

						pMotionPlayer = (CObjectMotionPlayer*)pObject;

						D3DXVECTOR3 PlayerPos = pMotionPlayer->GetClassData().Pos;

						if (pMotionPlayer->GetPlayerNum() < 0)
						{//�c�@�܂��Ȃ���

							m_bNext = false;
							m_bStay2BOOL = true;
							pManager->SetStayState(true);

						}


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

						if (pManager->GetEndStatusState() == true)
						{//�N���ARoute

							CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_RESULT);

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
					/*		CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_GAME2);*/

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
	else
	{//���̃X�e�[�W�ɑJ��
		m_nCnt++;


		if (m_nCnt == 10)
		{
			m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 3, "�R�`�O�ɓ����B\n�ҋ@����B", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80);
			m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "< COM >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 170);
		}

		if (m_nCnt == 220)
		{
			m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
		}

		if (m_nCnt == 300)
		{
			//			CTime::ChangeTime(CTime::GetTime());
			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_MOVIE2);
		}

	}
}
//===================================
// �`��
//===================================
void CGame3::Draw()
{
	//	CObstacleSet::DebugSetDataDraw();//�ݒu�p�f�o�b�O�`��
	char cData2[100] = {};
	//snprintf(cData2, sizeof(cData2), "���@�c�@�F%d", CObjectMotionPlayer::GetPlayerNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
	//// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
	//CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_MILITARY, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);



	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	if (pManager->GetPauseState() == false)
	{
	}
	else
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//�ҋ@���
		m_StayUI->Draw();

		//char aData2[100];

	//	int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		//snprintf(aData2, sizeof(aData2), "�^�C���{�[�i�X:%d", nSetNum); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[

		//CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);

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















///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
	CScore::AddScore(CScore::TANK_SCORE1);



	CObject3D::Create();

	if (CScene::GetStageClear() == true)
	{
		//player���ŏ��I
	//-------------------------------------------------------------
		CObject::DATA SetData = CObject::DataInit();//������
		SetData.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
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






	if (m_ScoreNum[0] != m_NUM)
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
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 310.0f, SCREEN_HEIGHT / 2.0f + 200.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, (float)m_nbuttonCnt * 0.01f), aData);

}

//===================================
// �X�R�A���[�h
//===================================
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
//===================================
// �X�R�A�`��
//===================================
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



