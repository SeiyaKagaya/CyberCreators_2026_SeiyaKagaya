//=========================================================
//
// manager.cppで使う関数[manager.h]
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
// コンストラクタ
//=============================
CManager::CManager()
{
	m_pRenderer =nullptr;//レンダラー
	m_pScene = nullptr;
	m_pKeyboard =nullptr;
	m_pjoyPad = nullptr;
	m_allTexture=nullptr;//テクスチャ管理
	m_pFont = nullptr;//フォント
}

//=============================
// デストラクタ
//=============================
CManager::~CManager()
{
}

//=============================
// 初期設定
//=============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラー
	m_pRenderer = new CRenderer();
	m_pRenderer->Init(hWnd,TRUE);

	//キーボード
	m_pKeyboard = new CInputKeyboard();
	m_pKeyboard->Init(hInstance, hWnd);

	//パッド
	m_pjoyPad = new CInputJoyPad();
	m_pjoyPad->Init(hInstance, hWnd);

	//テクスチャ
	m_allTexture = new CAllTexture();
	m_allTexture->Init();

	//フォント
	m_pFont = new CFont();
	m_pFont->InitText();

	//フェード
	m_pFade = new CFade();
	m_pFade->Init(CScene::MODE_TITLE);

	
	//最初のシーン設定
	m_pFade->SetFade(CScene::MODE_TITLE);

	//ライト
	m_pLight = new CLight();
	m_pLight->Init();

	//カメラ
	m_pCamera = new CCamera();
	m_pCamera->Init();


	m_Pause = CPause::Create();
	m_StayUI = CStayUI::Create();

	m_Sound = CSound::Create(hWnd);

	return S_OK;
}

//=============================
// 終了処理
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

	CObject::ReleaseAll();//全オブジェクト開放

	if (m_pRenderer!=nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//終了処理
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
}

//=============================
// 更新(レンダラー)
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

		//ショイパットの状態を取得
		DWORD dwResult = XInputGetState(0, &joykeystate);


		//PAUSE起動
		if (bGetInputState() == true)
		{//操作方法--trueでコントローラー
			if (m_pjoyPad->GetTrigger(CInputJoyPad::JOYKEY_START) == true || m_pKeyboard->GetTrigger(DIK_SPACE))
			{
				m_Sound->PlaySound(CSound::SOUND_LABEL_SE_ENTER2);

				SetPauseState(true);
			}
		}
		else
		{//キーボード入力反映(移動)
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
// 描画処理(レンダラー)
//=============================
void CManager::Draw()
{
	m_pRenderer->Draw();
}

//=============================
// レンダラー取得
//=============================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//=============================
// キーボード取得
//=============================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//=============================
// キーボード取得
//=============================
CInputJoyPad* CManager::GetJoyPad()
{
	return m_pjoyPad;
}

//=============================
// 静的インスタンス生成
//=============================
CManager* CManager::GetInstance()
{
	static CManager instance;

	return &instance;
}

//=============================
// シーン設定
//=============================
void CManager::SetMode(CScene::MODE mode)
{
	//終了処理
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
//カメラ取得
//=============================
CCamera* CManager::GetCamera()
{
	return m_pCamera;
}

//==========================
//ライト取得
//==========================
CLight* CManager::GetLight()
{
	return m_pLight;
}

//==========================
//シーン取得
//==========================
CScene* CManager::GetScene()
{
	return m_pScene;
}

//==========================
//フェード取得
//==========================
CFade* CManager::GetFade()
{
	return m_pFade;
}

//==========================
//バレット管理取得
//==========================
CNewBulletALL* CManager::GetNewBulletAll()
{
	return m_NewBulletAll;
}

//==========================
//バレットMNG取得
//==========================
void CManager::SetNewBulletAll(CNewBulletALL* GetNewBulletAll)
{
	m_NewBulletAll = GetNewBulletAll;
}

//==========================
//テクスチャ取得
//==========================
CAllTexture* CManager::GetTexture()
{
	return m_allTexture;
}

//==========================
//入力方式取得
//==========================
bool CManager::bGetInputState()
{
	return m_bInputState;
}

//==========================
//入力方式格納
//==========================
void CManager::bSetInputState(bool InputState)
{
	m_bInputState = InputState;
}

//==========================
//停止状態か格納
//==========================
void CManager::SetPauseState(bool Pause)
{
	m_bStopNow = Pause;
}

//==========================
//静止状態か
//==========================
bool CManager::GetPauseState()
{
	return m_bStopNow;
}

//==========================
//待機状態か格納
//==========================
void CManager::SetStayState(bool Stay)
{
	m_bStaybool = Stay;
}

//==========================
//待機状態か返す
//==========================
bool CManager::GetStayState()
{
	return m_bStaybool;
}

//==========================
//現在のステートを格納
//==========================
void CManager::SetStayStatusState(bool Stay)
{
	m_bStayStatus = Stay;
}

//==========================
//現在のステートを返す
//==========================
bool CManager::GetStayStatusState()
{
	return m_bStayStatus;
}

//==========================
//終了じょうたいか格納
//==========================
void CManager::SetEndStatusState(bool Stay)
{
	m_EndState = Stay;
}

//==========================
//終了状態かを返す
//==========================
bool CManager::GetEndStatusState()
{
	return m_EndState;
}

//==========================
//ポーズを返す
//==========================
CPause* CManager::GetPause()
{
	return m_Pause;
}

//==========================
//待機UIを返す
//==========================
CStayUI* CManager::GetStayUI()
{
	return m_StayUI;
}

//==========================
//Soundを返す
//==========================
CSound* CManager::GetSound()
{
	return m_Sound;
}