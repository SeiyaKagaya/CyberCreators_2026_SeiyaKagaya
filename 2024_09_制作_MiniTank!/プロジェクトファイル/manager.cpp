//=========================================================
//
// manager.cpp�Ŏg���֐�[manager.h]
// Author seiya kagaya
//
//=========================================================
#include "manager.h"

#include "polygon.h"
#include "object3D.h"
#include "player3D.h"
#include "block3D.h"
#include <stdio.h>

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

	//���C�g
	m_pLight = new CLight();
	m_pLight->Init();

	//�J����
	m_pCamera = new CCamera();
	m_pCamera->Init();


	m_Pause = CPause::Create();
	m_StayUI = CStayUI::Create();

	m_Sound = CSound::Create(hWnd);

	return S_OK;
}

//=============================
// �I������
//=============================
void CManager::Uninit()
{
	m_NewBulletAll->ReleaseAllBullet();

	m_Sound->UninitSound();
	if (m_Sound != nullptr)
	{
		delete m_Sound;
	}

	m_Pause->Uninit();
	m_StayUI->Uninit();

	if (m_Pause != nullptr)
	{
		delete m_Pause;
	}
	if (m_pCamera != nullptr)
	{
		delete m_StayUI;
	}

	m_pLight->Uninit();
	m_pCamera->Uninit();

	m_pFade->Uninit();

	m_allTexture->Uninit();

	m_pjoyPad->Uninit();

	m_pKeyboard->Uninit();

	m_pFont->UninitText();

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
	m_pCamera->Update();	
	m_pKeyboard->Update();
	m_pjoyPad->Update();
	m_pRenderer->Update();
	
	if (GetPauseState() == false)
	{
		if (m_pScene != nullptr)
		{

			m_pScene->Update();
		}
		XINPUT_STATE joykeystate;

		//�V���C�p�b�g�̏�Ԃ��擾
		DWORD dwResult = XInputGetState(0, &joykeystate);


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
	else
	{
		if (m_Pause != nullptr)
		{
			m_Pause->Update();
		}
	}

	m_StayUI->Update();

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

//==========================
//�o���b�g�Ǘ��擾
//==========================
CNewBulletALL* CManager::GetNewBulletAll()
{
	return m_NewBulletAll;
}

//==========================
//�o���b�gMNG�擾
//==========================
void CManager::SetNewBulletAll(CNewBulletALL* GetNewBulletAll)
{
	m_NewBulletAll = GetNewBulletAll;
}

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

//==========================
//��~��Ԃ��i�[
//==========================
void CManager::SetPauseState(bool Pause)
{
	m_bStopNow = Pause;
}

//==========================
//�Î~��Ԃ�
//==========================
bool CManager::GetPauseState()
{
	return m_bStopNow;
}

//==========================
//�ҋ@��Ԃ��i�[
//==========================
void CManager::SetStayState(bool Stay)
{
	m_bStaybool = Stay;
}

//==========================
//�ҋ@��Ԃ��Ԃ�
//==========================
bool CManager::GetStayState()
{
	return m_bStaybool;
}

//==========================
//���݂̃X�e�[�g���i�[
//==========================
void CManager::SetStayStatusState(bool Stay)
{
	m_bStayStatus = Stay;
}

//==========================
//���݂̃X�e�[�g��Ԃ�
//==========================
bool CManager::GetStayStatusState()
{
	return m_bStayStatus;
}

//==========================
//�I�����傤�������i�[
//==========================
void CManager::SetEndStatusState(bool Stay)
{
	m_EndState = Stay;
}

//==========================
//�I����Ԃ���Ԃ�
//==========================
bool CManager::GetEndStatusState()
{
	return m_EndState;
}

//==========================
//�|�[�Y��Ԃ�
//==========================
CPause* CManager::GetPause()
{
	return m_Pause;
}

//==========================
//�ҋ@UI��Ԃ�
//==========================
CStayUI* CManager::GetStayUI()
{
	return m_StayUI;
}

//==========================
//Sound��Ԃ�
//==========================
CSound* CManager::GetSound()
{
	return m_Sound;
}