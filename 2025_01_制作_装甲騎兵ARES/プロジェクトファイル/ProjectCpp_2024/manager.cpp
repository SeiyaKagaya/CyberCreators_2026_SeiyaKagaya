//=========================================================
//
// manager.cpp�Ŏg���֐�[manager.h]
// Author seiya kagaya
//
//=========================================================
#include "manager.h"


//#include "object2D.h"
//#include "polygon.h"

//#include "player.h"
//#include "background.h"
//#include "enemy.h"
//#include "item.h"
//#include "block.h"
//#include "score.h"
#include "object3D.h"
//#include"objectX.h"
//#include "player3D.h"
//#include "block3D.h"
#include <stdio.h>

//// �ÓI�����o�ϐ�
//CRenderer* CManager::m_pRenderer = nullptr;
//CInputKeyboard* CManager::m_pKeyboard = nullptr;
//
//CAllTexture* CManager::m_allTexture = nullptr;







CScene* CManager::m_pScene = nullptr;

CAllTexture* CManager::m_allTexture = nullptr;

//=============================
// �R���X�g���N�^
//=============================
CManager::CManager()
{
	m_pRenderer =nullptr;//�����_���[
	m_pScene = nullptr;
	m_pKeyboard =nullptr;
	m_pjoyPad = nullptr;
	m_allTexture=nullptr;//�e�N�X�`���Ǘ�
	m_pFont = nullptr;//�t�H���g
}
//=============================
// �f�X�g���N�^
//=============================
CManager::~CManager()
{
}
//=============================
// �����ݒ�
//=============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[
	m_pRenderer = new CRenderer();
	m_pRenderer->Init(hWnd,TRUE);


	
	
	//	pManager->SetNewBulletAll(CNewBulletALL::Create());
	


	//�L�[�{�[�h
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd);

	//�p�b�h
	m_pjoyPad = new CInputJoyPad();
	m_pjoyPad->Init(hInstance, hWnd);

	//�e�N�X�`��
	m_allTexture = new CAllTexture();
	m_allTexture->Init();

	//�t�H���g
	m_pFont = new CFont();
	m_pFont->InitText();

	//�t�F�[�h
	m_pFade = new CFade();
	m_pFade->Init(CScene::MODE_TITLE);

	
	//�ŏ��̃V�[���ݒ�
	m_pFade->SetFade(CScene::MODE_TITLE);

	
	//	SetMode(CScene::MODE_TITLE);

//	m_pScene->Init();

	//���C�g
	m_pLight = new CLight();
	m_pLight->Init();

	//�J����
	m_pCamera = new CCamera();
	m_pCamera->Init();


	m_Pause = CPause::Create();
	m_StayUI = CStayUI::Create();

	m_Sound = CSound::Create(hWnd);


//	m_pScore=CScore::Create();

	//CObject3D::Create();

	//CPlayer3D::Create();

	//CBlock3D::Create();

	return S_OK;
}
//=============================
// �I������
//=============================
void CManager::Uninit()
{
	

	m_Sound->UninitSound();
	if (m_Sound != nullptr)
	{
		delete m_Sound;
		m_Sound = nullptr;
	}

	m_Pause->Uninit();

	if (m_Pause != nullptr)
	{
		delete m_Pause;
		m_Pause = nullptr;
	}

	m_StayUI->Uninit();
	if (m_StayUI != nullptr)
	{
		delete m_StayUI;
		m_StayUI = nullptr;
	}

	m_pLight->Uninit();
	if (m_pLight != nullptr)
	{
		delete m_pLight;
		m_pLight = nullptr;
	}

	m_pCamera->Uninit();
	if (m_pCamera != nullptr)
	{
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	m_pFade->Uninit();
	if (m_pFade != nullptr)
	{
		delete m_pFade;
		m_pFade = nullptr;
	}

	m_allTexture->Uninit();
	if (m_allTexture != nullptr)
	{
		delete m_allTexture;
		m_allTexture = nullptr;
	}

	m_pjoyPad->Uninit();
	if (m_pjoyPad != nullptr)
	{
		delete m_pjoyPad;
		m_pjoyPad = nullptr;
	}

	m_pKeyboard->Uninit();
	if (m_pKeyboard != nullptr)
	{
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	m_pFont->UninitText();
	if (m_pFont != nullptr)
	{
		delete m_pFont;
		m_pFont = nullptr;
	}

	CObject::ReleaseAll();//�S�I�u�W�F�N�g�J��

	if (m_pRenderer!=nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}



	//�I������
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
}
//=============================
// �X�V(�����_���[)
//=============================
void CManager::Update()
{
	//if (m_pKeyboard->GetTrigger(DIK_1) == true)
	//{
	//	m_pFade->SetFade(CScene::MODE_TITLE);
	//}
	//if (m_pKeyboard->GetTrigger(DIK_2) == true)
	//{
	//	m_pFade->SetFade(CScene::MODE_GAME);
	//}
	//if (m_pKeyboard->GetTrigger(DIK_3) == true)
	//{
	//	m_pFade->SetFade(CScene::MODE_RESULT);
	//}

	//if (m_pKeyboard->GetTrigger(DIK_4) == true)
	//{
	//	m_pFade->SetFade(CScene::MODE_GAME2);
	//}
	//if (m_pKeyboard->GetTrigger(DIK_5) == true)
	//{
	//	m_pFade->SetFade(CScene::MODE_GAME3);
	//}





	m_pCamera->Update();
	
	m_pKeyboard->Update();
	m_pjoyPad->Update();
	m_pRenderer->Update();//-------------������object���ׂĂ̍X�V�������Ă�
	
	

	
	
	if (GetPauseState() == false)
	{
		if (m_pScene != nullptr)
		{

			m_pScene->Update();
		}
		XINPUT_STATE joykeystate;

		//�V���C�p�b�g�̏�Ԃ��擾
		DWORD dwResult = XInputGetState(0, &joykeystate);


		CScene::MODE NowState = m_pScene->GetNowScene();


		if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3)
		{//�Q�[����
		//PAUSE�N��
			if (bGetInputState() == true)
			{//������@--true�ŃR���g���[���[
				if (m_pjoyPad->GetTrigger(CInputJoyPad::JOYKEY_START) == true || m_pKeyboard->GetTrigger(DIK_SPACE))
				{
					m_Sound->PlaySound(CSound::SOUND_LABEL_SE_ENTER2);

					SetPauseState(true);
				}
			}
			else
			{//�L�[�{�[�h���͔��f(�ړ�)
				if (m_pKeyboard->GetTrigger(DIK_SPACE))
				{
					SetPauseState(true);
				}
			}
		}
	}
	else
	{
		if (m_Pause != nullptr)
		{
			m_Pause->Update();
		}
	}

	m_StayUI->Update();

//	m_pScore->Update();

	m_pFade->Update();

	m_pLight->Update();


	
}
//=============================
// �`�揈��(�����_���[)
//=============================
void CManager::Draw()
{
	m_pRenderer->Draw();

	

}
//=============================
// �����_���[�擾
//=============================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}
//=============================
// �L�[�{�[�h�擾
//=============================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}
//=============================
// �L�[�{�[�h�擾
//=============================
CInputJoyPad* CManager::GetJoyPad()
{
	return m_pjoyPad;
}
//=============================
// �ÓI�C���X�^���X����
//=============================
CManager* CManager::GetInstance()
{
	static CManager instance;

	return &instance;
}
//=============================
// �V�[���ݒ�
//=============================
void CManager::SetMode(CScene::MODE mode)
{
	//�I������
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	m_pScene = CScene::Create(mode);
	m_pScene->Init();
}

//=============================
//�J�����擾
//=============================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}
//==========================
//���C�g�擾
//==========================
CLight* CManager::GetLight()
{
	return m_pLight;
}
//==========================
//�V�[���擾
//==========================
CScene* CManager::GetScene()
{
	return m_pScene;
}
//==========================
//�t�F�[�h�擾
//==========================
CFade* CManager::GetFade()
{
	return m_pFade;
}
////==========================
////�o���b�g�Ǘ��擾
////==========================
//CNewBulletALL* CManager::GetNewBulletAll()
//{
//	return m_NewBulletAll;
//}
//void CManager::SetNewBulletAll(CNewBulletALL* GetNewBulletAll)
//{
//	m_NewBulletAll = GetNewBulletAll;
//}
//CScore* CManager::GetScore()
//{
//	return m_pScore;
//}
//==========================
//�e�N�X�`���擾
//==========================
CAllTexture* CManager::GetTexture()
{
	return m_allTexture;
}
//==========================
//���͕����擾
//==========================
bool CManager::bGetInputState()
{
	return m_bInputState;
}
//==========================
//���͕����i�[
//==========================
void CManager::bSetInputState(bool InputState)
{
	m_bInputState = InputState;
}
void CManager::SetPauseState(bool Pause)
{
	m_bStopNow = Pause;
}

bool CManager::GetPauseState()
{
	return m_bStopNow;
}

void CManager::SetStayState(bool Stay)
{
	m_bStaybool = Stay;
}

bool CManager::GetStayState()
{
	return m_bStaybool;
}

void CManager::SetStayStatusState(bool Stay)
{
	m_bStayStatus = Stay;
}

bool CManager::GetStayStatusState()
{
	return m_bStayStatus;
}

void CManager::SetEndStatusState(bool Stay)
{
	m_EndState = Stay;
}

bool CManager::GetEndStatusState()
{
	return m_EndState;
}

CPause* CManager::GetPause()
{
	return m_Pause;
}

CStayUI* CManager::GetStayUI()
{
	return m_StayUI;
}

CSound* CManager::GetSound()
{
	return m_Sound;
}


