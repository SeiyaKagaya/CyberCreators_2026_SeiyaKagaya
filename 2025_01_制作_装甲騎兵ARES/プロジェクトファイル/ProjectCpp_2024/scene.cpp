//=======================================================
//
//sceneに関する処理[scene.cpp]
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
//#include "tankfootprint.h"
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

// 静的メンバー変数の定義
CScene::MODE CScene::m_NowState = CScene::MODE_TITLE; // 初期値をMODE_TITLEに設定
bool CScene::m_bStageClear = false;
bool CScene::m_bNextStageStay = false;

int CScene::m_ClearNum = 0;

//===================================
// コンストラクタ
//===================================
CScene::CScene()
{
	CManager* pManager = CManager::GetInstance();

	m_Pause = pManager->GetPause();

	m_StayUI = pManager->GetStayUI();
}
//===================================
// デストラクタ
//===================================
CScene::~CScene()
{
}
//===================================
// 初期化
//===================================
HRESULT CScene::Init()
{
	return E_NOTIMPL;
}
//===================================
// 終了
//===================================
void CScene::Uninit()
{

}
//===================================
// 更新
//===================================
void CScene::Update()
{
}
//===================================
// 描画
//===================================
void CScene::Draw()
{
}
//===================================
// 生成
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
// 現在のシーンを格納
//===================================
void CScene::SetNowScene(MODE SetScene)
{
	m_NowState = SetScene;
}
//===================================
// ゲームクリア判定
//===================================
void CScene::SetStageClear(bool bSet)
{
	m_bStageClear = bSet;
}
//===================================
// クリア状態か取得
//===================================
bool CScene::GetStageClear()
{
	return m_bStageClear;
}
//===================================
// 現在のシーンを取得
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
// コンストラクタ
//===================================
CTitle::CTitle()
{
}
//===================================
// デストラクタ
//===================================
CTitle::~CTitle()
{
}
//===================================
// 初期化
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

	//playerが最初！
//-------------------------------------------------------------
	CObject::DATA SetData = CObject::DataInit();//初期化
	SetData.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------





//	CObjectFootPrint::Create(D3DXVECTOR3(10.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CObjectFootPrint::Create(D3DXVECTOR3(0.0f, 1.0f, 20.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//CObjectFootPrint::Create(D3DXVECTOR3(30.0f, 1.0f, 30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

//	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();

	if (pSound != nullptr)
	{
		pSound->StopSound();
	}

	pSound->PlaySound(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}
//===================================
// 終了
//===================================
void CTitle::Uninit()
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	if (pSound != nullptr)
	{
		pSound->StopSound(CSound::SOUND_LABEL_BGM000);
	}
}
//===================================
// 更新
//===================================
void CTitle::Update()
{
	//	Explosion3D::Create(D3DXVECTOR3(10.0f, 500.0f, 10.0f));

		// マウスカーソルを表示にする
	int nDrawCnt = ShowCursor(TRUE);

	while (true)
	{
		if (nDrawCnt > 0)
		{//表示状態のとき
			if (nDrawCnt > 1)
			{//2超える
				nDrawCnt = ShowCursor(FALSE);
			}

			break;
		}
		else
		{//非表示状態のとき
			nDrawCnt = ShowCursor(TRUE);
		}
	}


	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);

	if (dwResult == ERROR_SUCCESS)
	{//キーボード/コントローラー入力反映(移動)
//		ControllerInput();
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_START) || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A))
		{//左マウスクリック/STARTキー/Aキー
			CSound* pSound = pManager->GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER2);

			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_TUTORIAL);
		}

	}
	else
	{//キーボード入力反映(移動)
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
		{//エンターもしくは左マウスクリック
			CSound* pSound = pManager->GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER2);
			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_TUTORIAL);
		}


	}




}
//===================================
// 描画
//===================================
void CTitle::Draw()
{
	const char* aData = "装甲騎兵";
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 607.0f, SCREEN_HEIGHT / 2.0f - 308.0f, 0.0f), 193, CFont::FONT_MILITARY, D3DXCOLOR(0.5f, 0.4f, 0.1f, 1.0f), aData);

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 610.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 215, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

	aData = "ARES";
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 57.0f, SCREEN_HEIGHT / 2.0f + 108.0f, 0.0f), 193, CFont::FONT_MILITARY, D3DXCOLOR(0.5f, 0.4f, 0.1f, 1.0f), aData);

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 65.0f, SCREEN_HEIGHT / 2.0f + 110.0f, 0.0f), 218, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);





	aData = "Startボタン/Aボタン";

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
// コンストラクタ
//===================================
CTutorial::CTutorial()
{
}

//===================================
// デストラクタ
//===================================
CTutorial::~CTutorial()
{
}
//===================================
// 初期化
//===================================
HRESULT CTutorial::Init()
{
	CScore::ResetScore();

	m_TutorialUI = CTutorialUI::Create();



	return E_NOTIMPL;
}
//===================================
// 終了
//===================================
void CTutorial::Uninit()
{
	m_TutorialUI->Uninit();
	delete m_TutorialUI;


}
//===================================
// 更新
//===================================
void CTutorial::Update()
{
	// マウスカーソルを表示にする
	int nDrawCnt = ShowCursor(TRUE);

	while (true)
	{
		if (nDrawCnt > 0)
		{//表示状態のとき
			if (nDrawCnt > 1)
			{//2超える
				nDrawCnt = ShowCursor(FALSE);
			}

			break;
		}
		else
		{//非表示状態のとき
			nDrawCnt = ShowCursor(TRUE);
		}
	}


	m_TutorialUI->Update();

}
//===================================
// 描画
//===================================
void CTutorial::Draw()
{
	CManager* pManager = CManager::GetInstance();

	m_TutorialUI->Draw();


}

///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//===================================
// コンストラクタ
//===================================
COP::COP()
{
}

//===================================
// デストラクタ
//===================================
COP::~COP()
{

}
//===================================
// 初期化
//===================================
HRESULT COP::Init()
{
	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時

	SetData.Pos = D3DXVECTOR3(14950.0f, 10.0f, 14950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);

	//playerが最初！
//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
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

		//フォグカラー設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));


	//D3DFOG_EXP(密度指定の場合のみ設定する)
	float m_fFogDensity = 0.00005f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));

	//フォグの有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	m_pLongPush = CLongPush::Create();

	return E_NOTIMPL;
}
//===================================
// 終了
//===================================
void COP::Uninit()
{
	//m_pLongPush->Uninit();
	//m_CGameUI->Uninit();
	//m_CGameUI->SetDeath(true);
	//m_CTextWindow->Uninit();
	//m_CTextWindow->SetDeath(true);

}
//===================================
// 更新
//===================================
void COP::Update()
{
	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);

	m_nCnt++;

	if (m_nCnt == 100)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 3, "まもなく降下ポイント。\nコース問題なし。\n投下スタンバイ。", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 140);

		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 1, "<B-2パイロット>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 565);
	}


	if (m_nCnt == 390)
	{
		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 5, "3.........2.........1.........\n投下。", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 140);

	}

	if (m_nCnt == 720)
	{
		m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
	}





	if (m_nCnt == 760)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 2, "スピリッド1、\nこれより作戦空域を離脱。\nプレイヤー。ご武運を。", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80);
		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 1, "<B-2パイロット>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 190);
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


	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonPress(CInputKeyboard::MouseKey_Left) == true)
	{
		m_pLongPush->AddCnt();
	}
	else
	{
		m_pLongPush->SubCnt();
	}

	m_pLongPush->Update();

	if (m_pLongPush->PushOkBool())
	{
		CSound* pSound = pManager->GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);
		m_nCnt = 0;
		CFade* pFade = pManager->GetFade();
		pFade->SetFade(CScene::MODE_GAME);
	}

}
//===================================
// 描画
//===================================
void COP::Draw()
{
	CManager* pManager = CManager::GetInstance();



}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------


//===================================
// コンストラクタ
//===================================
CGame::CGame()
{
}
//===================================
// デストラクタ
//===================================
CGame::~CGame()
{

}
//===================================
// 初期化
//===================================
HRESULT CGame::Init()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//フォグの有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);



	CTime::Create();
	CTime::ChangeTime(150);

	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//	CObject3D::Create();//現状床

	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時

	SetData.Pos = D3DXVECTOR3(4950.0f, 10.0f, 4950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);

	SetData.Pos.y += 20.0f;
	SetData.rot.y = D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.2f);

	SetData.Pos.y += 30.0f;
	SetData.rot.y = -D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.1f);

	SetData = CObject::DataInit();//初期化同時

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//ステージ配置物ロード

	CScore::Create();

	//	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//経路テーブルをロード

	//	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//射撃地点をロード


	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();

	CNewBulletALL::Create();
	CObject3DParticleAll::Create();
	CMissileALL::Create();

	SetStayNextStage(false);

	//配置物
	//-------------------------------------------------------------------------------------------------------------------

	////左端
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















	//6500
	//3250

	//--------------------------------------------------------------------------------------------------------------------
	//2Dステージ配置物
	float ZPos = 250.0f;
	float Zlong = 750.0f;

	//左の橋
	SetData.Pos = D3DXVECTOR3(-17450, 1600.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(7750, 500.0f, Zlong - 200.0f);
	SetData.MinLength = D3DXVECTOR3(-7750.0f, -500.0f, -Zlong - 200.0f);
	StageCollisionBox::Create(SetData);
	//StageCollisionBox

	//stage左端進入不可
	SetData.Pos = D3DXVECTOR3(-26500.0f, 8000.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(1300, 8000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1300, -8000.0f, -Zlong);
	StageCollisionBox::Create(SetData);


	//トラック当たり判定
	SetData.Pos = D3DXVECTOR3(-21250.0f, 2130.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(300, 200.0f, Zlong*0.3f);	//DEBUG視認性
	SetData.MinLength = D3DXVECTOR3(-300, -200.0f, -Zlong*0.3f);
	StageCollisionBox::Create(SetData);

	//橋上の擁壁
	SetData.Pos = D3DXVECTOR3(-19750.0f, 2100.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(140, 1000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-140, -1000.0f, -Zlong);
	StageCollisionBox::Create(SetData);

	//洞窟上進入不可
	SetData.Pos = D3DXVECTOR3(-9000.0f, 10300.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 7000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -7000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステ左侵入不可
	SetData.Pos = D3DXVECTOR3(800.0f, 9000.0f, 8000.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 9000.0f, 7000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -9000.0f, -7000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステ奥進入不可
	SetData.Pos = D3DXVECTOR3(4600.0f, 9000.0f, 16000.0f);
	SetData.MaxLength = D3DXVECTOR3(4600.0f, 9000.0f, Zlong + 200.0f);
	SetData.MinLength = D3DXVECTOR3(-4600.0f, -9000.0f, -(Zlong + 200.0f));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//慣れステ奥進入不可2
	SetData.Pos = D3DXVECTOR3(6000.0f, 9000.0f, 17600.0f);
	SetData.MaxLength = D3DXVECTOR3(6000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-6000.0f, -9000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//慣れステ右侵入不可
	SetData.Pos = D3DXVECTOR3(10050.0f, 2430.0f, 8350.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 2370.0f, 9000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -2370.0f, -9000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//慣れステ右床
	SetData.Pos = D3DXVECTOR3(13000.0f, 2370.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(2200.0f, 2370.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-2200.0f, -2370.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステ右床上壁
	SetData.Pos = D3DXVECTOR3(11550.0f, 10170.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(960.0f, 3000.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-960.0f, -3000.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//慣れステ右壁
	SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 10200.0f);
	SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, Zlong + 8350.0f);
	SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -Zlong - 8350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステからボス手前進入不可
	SetData.Pos = D3DXVECTOR3(16000.0f, 9000.0f, -(Zlong * 2.0f) + 180.0f);
	SetData.MaxLength = D3DXVECTOR3(16000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-16000.0f, -9000.0f, -(Zlong));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);





		//洞窟右パイプ1
	SetData.Pos = D3DXVECTOR3(4650.0f, 400.0f, 50.0f);
	SetData.MaxLength = D3DXVECTOR3(4650.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-4650.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//洞窟奥行きパイプ2
	SetData.Pos = D3DXVECTOR3(4200.0f, 400.0f, 4150.0f);
	SetData.MaxLength = D3DXVECTOR3(500.0f, 480.0f, 4150.0f);
	SetData.MinLength = D3DXVECTOR3(-500.0f, -480.0f, -4150.0f);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);Set
	StageCollisionBox::Create(SetData);



	//洞窟右パイプ3(一個上)
	SetData.Pos = D3DXVECTOR3(2000.0f, 2850.0f, 5800.0f);
	SetData.MaxLength = D3DXVECTOR3(2000.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2000.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//洞窟右パイプ4(奥)
	SetData.Pos = D3DXVECTOR3(6600.0f, 400.0f, 7750.0f);
	SetData.MaxLength = D3DXVECTOR3(2600.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong + 100.0f);
	//	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong - 100.0f);
	StageCollisionBox::Create(SetData);

	//洞窟右パイプ3(2個上)
	SetData.Pos = D3DXVECTOR3(7900.0f, 4250.0f, 9900.0f);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);


	//ボスステ右床
	SetData.Pos = D3DXVECTOR3(28980.0f, 68.0f, 9150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//ボスステ真ん中床
	SetData.Pos = D3DXVECTOR3(21915.0f, 68.0f, 2200.0f);
	SetData.MaxLength = D3DXVECTOR3(4765.0f, 68.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-4765.0f, -68.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//ボスステ左床
	SetData.Pos = D3DXVECTOR3(14850.0f, 68.0f, 9150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//ボスステ真ん中奥壁
	SetData.Pos = D3DXVECTOR3(21915.0f, 4000.0f, 22050.0f);
	SetData.MaxLength = D3DXVECTOR3(9765.0f, 4000.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-9765.0f, -4000.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//ボスステ右壁
	SetData.Pos = D3DXVECTOR3(32250.0f, 9000.0f, 9200.0f);
	SetData.MaxLength = D3DXVECTOR3(1000.0f, 9000.0f, Zlong + 9300.0f);
	SetData.MinLength = D3DXVECTOR3(-1000.0f, -9000.0f, -Zlong - 9300.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);












	//一番下ロング
	SetData.Pos = D3DXVECTOR3(-3600.0f, 150.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(3600.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-3600.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//一番右下段
	SetData.Pos = D3DXVECTOR3(-750.0f, 600.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(750.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-750.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番右中段
	SetData.Pos = D3DXVECTOR3(-300.0f, 1950.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番上段右
	SetData.Pos = D3DXVECTOR3(-1200.0f, 2850.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1200.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1200.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番上段左
	SetData.Pos = D3DXVECTOR3(-3900.0f, 3000.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//右２番目上段
	SetData.Pos = D3DXVECTOR3(-1500.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//右２番目中上段
	SetData.Pos = D3DXVECTOR3(-1650.0f, 1650.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//右3番目中段
	SetData.Pos = D3DXVECTOR3(-3000.0f, 1500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//中央中段右
	SetData.Pos = D3DXVECTOR3(-3750.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 750.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-150.0f, -750.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//中央中段左
	SetData.Pos = D3DXVECTOR3(-4350.0f, 1200.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 600.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -600.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//中央左上部
	SetData.Pos = D3DXVECTOR3(-6000.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//中央左中部
	SetData.Pos = D3DXVECTOR3(-6300.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//最左部
	SetData.Pos = D3DXVECTOR3(-8550.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1350.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1350.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//床下
	SetData.Pos = D3DXVECTOR3(-4950.0f, -500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//屋根上
	SetData.Pos = D3DXVECTOR3(-4950.0f, 3800.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//-------------------------------------------------------------------------------------------------------------------



	//playerが最初！
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(-25000.0f, 2700.0f, 0.0f);
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------

	CObjectMotionPlayer::SetPlayerNum(1);

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化

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
// 終了
//===================================
void CGame::Uninit()
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	if (pSound != nullptr)
	{
	//	pSound->StopSound(CSound::SOUND_LABEL_BGM001);//ここではとめない
	}

	//m_CGameUI->Uninit();
//	m_CGameUI->SetDeath(true);
	//m_CTextWindow->Uninit();
//	m_CTextWindow->SetDeath(true);
}
//===================================
// 更新
//===================================
void CGame::Update()
{
	//// マウスカーソルを表示にする
	//int nDrawCnt = ShowCursor(TRUE);

	//while (true)
	//{
	//	if (nDrawCnt > 0)
	//	{//表示状態のとき
	//		if (nDrawCnt > 1)
	//		{//2超える
	//			nDrawCnt = ShowCursor(FALSE);
	//		}

	//		break;
	//	}
	//	else
	//	{//非表示状態のとき
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
				{//Reset起動してない
					CInputKeyboard* keyboard = pManager->GetKeyboard();
					if (keyboard->GetPress(DIK_RSHIFT) == true)
					{//右シフト押された
						m_CGameUI->AllUiRestart();

						//mode切り替え
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
				{//起動してる
					m_CGameUI->AllUiRestart();
				}

				if (CObjectMotionEnemyBoss::GetEnemyAllNum() <= 0)
				{//敵殲滅	
					m_bNext = false;//true
					m_bStay2BOOL = true;
				}

				if (CTime::GetTime() <= 0)
				{//制限時間切れ
					m_bNext = false;
					m_bStay2BOOL = true;
					pManager->SetStayState(true);
				}



				//-------------------------------------------------------------------------
				//エリアごとの処理部
				// 配置物プライオリティの先頭を取得

				CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

				if (pObject != nullptr)
				{ // 先頭がない==プライオリティまるっとない

					if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
					{ // 対象のモデルのとき
						CObject::DATA EscData;

						// ここで使用分宣言
						CObjectMotionPlayer* pMotionPlayer;

						pMotionPlayer = (CObjectMotionPlayer*)pObject;

						D3DXVECTOR3 PlayerPos = pMotionPlayer->GetClassData().Pos;

						if (pMotionPlayer->GetPlayerNum() < 0)
						{//残機まいなすに

							m_bNext = false;
							m_bStay2BOOL = true;
							pManager->SetStayState(true);
						}

						D3DXVECTOR3 GateMin = D3DXVECTOR3(-300.0f, 780.0f, -100.0f);
						D3DXVECTOR3 GateMax = D3DXVECTOR3(1500.0f, 2000.0f, 100.0f);
	
						//エリア内にいるとき
						if (CMathProc::Check3DBoxInPos(GateMin, GateMax, PlayerPos) == true)
						{
							SetStayNextStage(true);//ゴール地点に到達

							m_bTextSetEnd[0] = true;
							m_bTextSetEnd[1] = true;
							m_bTextSetEnd[2] = true;
						}


						if (m_bTextSet[0] == false)
						{
							GateMin = D3DXVECTOR3(-24700.0f, -10000.0f, -100.0f);
							GateMax = D3DXVECTOR3(-22700.0f, 10000.0f, 100.0f);

							//エリア内にいるとき
							if (CMathProc::Check3DBoxInPos(GateMin, GateMax, PlayerPos) == true)
							{
								m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

								m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 2, "左スティックで移動\nA、LTボタンでジャンプだ！\n長押しで飛翔するぞ！", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120);
								m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "< 司令部 >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 230);
								m_nTextEndCnt = 270;
								m_bTextSet[0] = true;//1番目のコメントセットOn
							}
						}

						if (m_bTextSet[1] == false)
						{
							GateMin = D3DXVECTOR3(-19100.0f, -10000.0f, -100.0f);
							GateMax = D3DXVECTOR3(-17100.0f, 10000.0f, 100.0f);

							//エリア内にいるとき
							if (CMathProc::Check3DBoxInPos(GateMin, GateMax, PlayerPos) == true)
							{
								m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

								m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 2, "敵がいるぞ！\n右スティックで照準\nTRボタンで発砲だ!", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150);
								m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "< 司令部 >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 230);
								m_nTextEndCnt = 300;
								m_bTextSet[1] = true;//2番目のコメントセットOn
							}
						}

						if (m_bTextSet[2] == false)
						{
							GateMin = D3DXVECTOR3(-7850.0f, -10000.0f, -100.0f);
							GateMax = D3DXVECTOR3(-5850.0f, 10000.0f, 100.0f);

							//エリア内にいるとき
							if (CMathProc::Check3DBoxInPos(GateMin, GateMax, PlayerPos) == true)
							{
								m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

								m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 2, "攻撃が激しい時は\nLBボタンでガードだ!\n照準方向にバリアが出るぞ", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150);
								m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "< 司令部 >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 240);
								m_nTextEndCnt = 310;
								m_bTextSet[2] = true;//3番目のコメントセットOn
							}
						}
					}
				}

				if (m_bTextSet[0] == true)
				{
					if (m_bTextSetEnd[0] == false)
					{
						m_nTextEndCnt--;
						if (m_nTextEndCnt <= 0)
						{
							m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
							m_bTextSetEnd[0] = true;
						}
					}
				}
				if (m_bTextSet[1] == true)
				{
					m_bTextSetEnd[0] = true;

					if (m_bTextSetEnd[1] == false)
					{
						m_nTextEndCnt--;
						if (m_nTextEndCnt <= 0)
						{
							m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
							m_bTextSetEnd[1] = true;
						}
					}
				}
				if (m_bTextSet[2] == true)
				{
					m_bTextSetEnd[0] = true;
					m_bTextSetEnd[1] = true;

					if (m_bTextSetEnd[2] == false)
					{
						m_nTextEndCnt--;
						if (m_nTextEndCnt <= 0)
						{
							m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
							m_bTextSetEnd[2] = true;
						}
					}
				}
				//--------------------------------------------------------------------------

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

				//ショイパットの状態を取得
				DWORD dwResult = XInputGetState(0, &joykeystate);

				if (pManager->bGetInputState() == true)
				{//操作方法--trueでコントローラー
					if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
					{
						CSound* pSound = pManager->GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

						if (pManager->GetEndStatusState() == true)
						{//クリアRoute

							CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_GAME2);

						}
						else
						{//敗北
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
				{//キーボード入力反映(移動)
					if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
					{
						CSound* pSound = pManager->GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


						if (pManager->GetEndStatusState() == true)
						{//クリアRoute
					/*		CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_GAME2);*/

						}
						else
						{//敗北
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
	{//次のステージに遷移
		m_nCnt++;


		if (m_nCnt == 10)
		{
			m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 3, "配管群に到着。\n偵察開始。", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80);
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
// 描画
//===================================
void CGame::Draw()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();


	//	CObstacleSet::DebugSetDataDraw();//設置用デバッグ描画
		//char cData2[100] = {};
		//snprintf(cData2, sizeof(cData2), "残機：%d", CObjectMotionPlayer::GetPlayerNum()); // 数値を文字列に変換してCDataにコピー
		//// mousePos.x と mousePos.y がマウスの位置
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
	{//待機画面
		m_StayUI->Draw();

		//char aData2[100];

		//int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		//snprintf(aData2, sizeof(aData2), "タイムボーナス:%d", nSetNum); // 数値を文字列に変換してCDataにコピー

		//CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);


	}

	if (m_StayPush == true)
	{//押す待機

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
		{//操作方法--trueでコントローラー
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "Aボタンで次に"); // 数値を文字列に変換してCDataにコピー

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);

		}
		else
		{//キーボード入力反映(移動)
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "マウス右クリックで次に"); // 数値を文字列に変換してCDataにコピー

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);

		}
	}


	//char aData2[100];

	//snprintf(aData2, sizeof(aData2), "現在のたま%d", CBullet3D::BulletNum()); // 数値を文字列に変換してCDataにコピー

	//CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), aData2);




}


///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//===================================
// コンストラクタ
//===================================
CMovie::CMovie()
{
}

//===================================
// デストラクタ
//===================================
CMovie::~CMovie()
{

}
//===================================
// 初期化
//===================================
HRESULT CMovie::Init()
{
	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時

	SetData.Pos = D3DXVECTOR3(14950.0f, 10.0f, 14950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);



	float Zlong = 750.0f;
	float ZPos = 250.0f;




	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//ステージ配置物ロード




	////慣れステ左侵入不可
	//SetData.Pos = D3DXVECTOR3(800.0f, 9000.0f, 8000.0f);
	//SetData.MaxLength = D3DXVECTOR3(800.0f, 9000.0f, 7000.0f);
	//SetData.MinLength = D3DXVECTOR3(-800.0f, -9000.0f, -7000.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////慣れステ奥進入不可
	//SetData.Pos = D3DXVECTOR3(4600.0f, 9000.0f, 16000.0f);
	//SetData.MaxLength = D3DXVECTOR3(4600.0f, 9000.0f, Zlong + 200.0f);
	//SetData.MinLength = D3DXVECTOR3(-4600.0f, -9000.0f, -(Zlong + 200.0f));
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	////慣れステ奥進入不可2
	//SetData.Pos = D3DXVECTOR3(6000.0f, 9000.0f, 17600.0f);
	//SetData.MaxLength = D3DXVECTOR3(6000.0f, 9000.0f, Zlong);
	//SetData.MinLength = D3DXVECTOR3(-6000.0f, -9000.0f, -Zlong);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	////慣れステ右侵入不可
	//SetData.Pos = D3DXVECTOR3(10050.0f, 2370.0f, 8350.0f);
	//SetData.MaxLength = D3DXVECTOR3(800.0f, 2370.0f, 9000.0f);
	//SetData.MinLength = D3DXVECTOR3(-800.0f, -2370.0f, -9000.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	////慣れステ右床
	//SetData.Pos = D3DXVECTOR3(13000.0f, 2370.0f, 0.0f);
	//SetData.MaxLength = D3DXVECTOR3(2200.0f, 2370.0f, Zlong + 350.0f);
	//SetData.MinLength = D3DXVECTOR3(-2200.0f, -2370.0f, -Zlong - 350.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////慣れステ右床上壁
	//SetData.Pos = D3DXVECTOR3(11550.0f, 10170.0f, 0.0f);
	//SetData.MaxLength = D3DXVECTOR3(960.0f, 3000.0f, Zlong + 350.0f);
	//SetData.MinLength = D3DXVECTOR3(-960.0f, -3000.0f, -Zlong - 350.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	////慣れステ右壁
	//SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 10200.0f);
	//SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, Zlong + 8350.0f);
	//SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -Zlong - 8350.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////慣れステからボス手前進入不可
	//SetData.Pos = D3DXVECTOR3(16000.0f, 9000.0f, -(Zlong * 2.0f) + 180.0f);
	//SetData.MaxLength = D3DXVECTOR3(16000.0f, 9000.0f, Zlong);
	//SetData.MinLength = D3DXVECTOR3(-16000.0f, -9000.0f, -(Zlong));
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);





	//	//洞窟右パイプ1
	//SetData.Pos = D3DXVECTOR3(4650.0f, 400.0f, 50.0f);
	//SetData.MaxLength = D3DXVECTOR3(4650.0f, 480.0f, Zlong - 100.0f);
	//SetData.MinLength = D3DXVECTOR3(-4650.0f, -480.0f, -Zlong + 100.0f);
	//StageCollisionBox::Create(SetData);

	////洞窟奥行きパイプ2
	//SetData.Pos = D3DXVECTOR3(4200.0f, 400.0f, 4150.0f);
	//SetData.MaxLength = D3DXVECTOR3(500.0f, 480.0f, 4150.0f);
	//SetData.MinLength = D3DXVECTOR3(-500.0f, -480.0f, -4150.0f);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);Set
	//StageCollisionBox::Create(SetData);



	////洞窟右パイプ3(一個上)
	//SetData.Pos = D3DXVECTOR3(2000.0f, 2850.0f, 5800.0f);
	//SetData.MaxLength = D3DXVECTOR3(2000.0f, 480.0f, Zlong - 100.0f);
	//SetData.MinLength = D3DXVECTOR3(-2000.0f, -480.0f, -Zlong + 100.0f);
	//StageCollisionBox::Create(SetData);

	////洞窟右パイプ4(奥)
	//SetData.Pos = D3DXVECTOR3(6600.0f, 400.0f, 7750.0f);
	//SetData.MaxLength = D3DXVECTOR3(2600.0f, 480.0f, Zlong - 100.0f);
	//SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong + 100.0f);
	////	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong - 100.0f);
	//StageCollisionBox::Create(SetData);

	////洞窟右パイプ3(2個上)
	//SetData.Pos = D3DXVECTOR3(7900.0f, 4250.0f, 9900.0f);
	//SetData.MaxLength = D3DXVECTOR3(1500.0f, 480.0f, Zlong - 100.0f);
	//SetData.MinLength = D3DXVECTOR3(-1500.0f, -480.0f, -Zlong + 100.0f);
	//StageCollisionBox::Create(SetData);


	////ボスステ右床
	//SetData.Pos = D3DXVECTOR3(28980.0f, 68.0f, 9150.0f);
	//SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	//SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	////ボスステ真ん中床
	//SetData.Pos = D3DXVECTOR3(21915.0f, 68.0f, 2200.0f);
	//SetData.MaxLength = D3DXVECTOR3(4765.0f, 68.0f, 2945.0f);
	//SetData.MinLength = D3DXVECTOR3(-4765.0f, -68.0f, -2945.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////ボスステ左床
	//SetData.Pos = D3DXVECTOR3(14850.0f, 68.0f, 9150.0f);
	//SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	//SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	////ボスステ真ん中奥壁
	//SetData.Pos = D3DXVECTOR3(21915.0f, 4000.0f, 22050.0f);
	//SetData.MaxLength = D3DXVECTOR3(9765.0f, 4000.0f, 2945.0f);
	//SetData.MinLength = D3DXVECTOR3(-9765.0f, -4000.0f, -2945.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	////ボスステ右壁
	//SetData.Pos = D3DXVECTOR3(32250.0f, 9000.0f, 9200.0f);
	//SetData.MaxLength = D3DXVECTOR3(1000.0f, 9000.0f, Zlong + 9300.0f);
	//SetData.MinLength = D3DXVECTOR3(-1000.0f, -9000.0f, -Zlong - 9300.0f);
	//StageCollisionBox::Create(SetData);
	////CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);












	//一番下ロング
	SetData.Pos = D3DXVECTOR3(-3600.0f, 150.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(3600.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-3600.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//一番右下段
	SetData.Pos = D3DXVECTOR3(-750.0f, 600.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(750.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-750.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番右中段
	SetData.Pos = D3DXVECTOR3(-300.0f, 1950.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番上段右
	SetData.Pos = D3DXVECTOR3(-1200.0f, 2850.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1200.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1200.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番上段左
	SetData.Pos = D3DXVECTOR3(-3900.0f, 3000.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//右２番目上段
	SetData.Pos = D3DXVECTOR3(-1500.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//右２番目中上段
	SetData.Pos = D3DXVECTOR3(-1650.0f, 1650.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//右3番目中段
	SetData.Pos = D3DXVECTOR3(-3000.0f, 1500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//中央中段右
	SetData.Pos = D3DXVECTOR3(-3750.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 750.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-150.0f, -750.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//中央中段左
	SetData.Pos = D3DXVECTOR3(-4350.0f, 1200.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 600.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -600.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//中央左上部
	SetData.Pos = D3DXVECTOR3(-6000.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//中央左中部
	SetData.Pos = D3DXVECTOR3(-6300.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//最左部
	SetData.Pos = D3DXVECTOR3(-8550.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1350.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1350.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//床下
	SetData.Pos = D3DXVECTOR3(-4950.0f, -500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//屋根上
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
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(3850.0f, 3370.0f, 5310.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(7280.0f, 4760.0f, 9360.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9350.0f, 4760.0f, 12980.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9320.0f, 4760.0f, 6400.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9300.0f, 4760.0f, 1940.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);










	//playerが最初！
//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(800.0f, 890.0f, 0.0f);
	//SetData.rot.y = -1.57f;
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);


	m_CGameUI = CGameUI::Create();
	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();


	m_pLongPush = CLongPush::Create();

	return S_OK;
}
//===================================
// 終了
//===================================
void CMovie::Uninit()
{
	//m_CGameUI->Uninit();
	//m_CGameUI->SetDeath(true);
	//m_CTextWindow->Uninit();
	//m_CTextWindow->SetDeath(true);

}
//===================================
// 更新
//===================================
void CMovie::Update()
{
	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);

	m_nCnt++;

	if (m_nCnt == 100)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 3, "外壁右上に入口を確認。\nパイプを利用して登ることを\n推奨。", D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 240);

		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<COM>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1060);
	}


	if (m_nCnt == 450)
	{
		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 3, "立体戦闘モード起動\n操作が3Dになり中央に\n近い相手に射撃で発砲。", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);

	}

	if (m_nCnt == 800)
	{
		//m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 2, "ミサイルの使用を許可。\n青いロックの相手に発射。\n時間経過で補充される。", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);
		//m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 1, "<B-2パイロット>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 190);
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


	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonPress(CInputKeyboard::MouseKey_Left) == true)
	{
		m_pLongPush->AddCnt();
	}
	else
	{
		m_pLongPush->SubCnt();
	}

	m_pLongPush->Update();

	if (m_pLongPush->PushOkBool())
	{
		CSound* pSound = pManager->GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);
		m_nCnt = 0;
		CFade* pFade = pManager->GetFade();
		pFade->SetFade(CScene::MODE_GAME2);
	}

}
//===================================
// 描画
//===================================
void CMovie::Draw()
{
	CManager* pManager = CManager::GetInstance();



}






//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//===================================
// コンストラクタ
//===================================
CGame2::CGame2()
{
}
//===================================
// デストラクタ
//===================================
CGame2::~CGame2()
{
}
//===================================
// 初期化
//===================================
HRESULT CGame2::Init()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//フォグの有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);



	CTime::Create();

	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//	CObject3D::Create();//現状床

	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時

	SetData.Pos = D3DXVECTOR3(4950.0f, 10.0f, 4950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);

	SetData.Pos.y += 20.0f;
	SetData.rot.y = D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.2f);

	SetData.Pos.y += 30.0f;
	SetData.rot.y = -D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.1f);

	SetData = CObject::DataInit();//初期化同時

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//ステージ配置物ロード

	CScore::Create();

	//	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//経路テーブルをロード

	//	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//射撃地点をロード


	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();

	pManager->SetbNow3DMode(true);

	m_CGameUI = CGameUI::Create();

	CNewBulletALL::Create();
	CObject3DParticleAll::Create();
	CMissileALL::Create();

	SetStayNextStage(false);

	//配置物
	//-------------------------------------------------------------------------------------------------------------------



	//-------------------------------------------------------------------------------------------------------------------

	SetData.Pos = D3DXVECTOR3(-(3300.0f * 0.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));



	SetData.Pos = D3DXVECTOR3(-(3300.0f * 1.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));




	SetData.Pos = D3DXVECTOR3(-(3300.0f * 2.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));


















	//--------------------------------------------------------------------------------------------------------------------
	//2Dステージ配置物
	float ZPos = 250.0f;
	float Zlong = 750.0f;

	//左の橋
	SetData.Pos = D3DXVECTOR3(-17450, 1600.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(7750, 500.0f, Zlong - 200.0f);
	SetData.MinLength = D3DXVECTOR3(-7750.0f, -500.0f, -Zlong - 200.0f);
	StageCollisionBox::Create(SetData);
	//StageCollisionBox

	//stage左端進入不可
	SetData.Pos = D3DXVECTOR3(-26500.0f, 8000.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(1300, 8000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1300, -8000.0f, -Zlong);
	StageCollisionBox::Create(SetData);


	//トラック当たり判定
	SetData.Pos = D3DXVECTOR3(-21250.0f, 2130.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(300, 200.0f, Zlong * 0.3f);	//DEBUG視認性
	SetData.MinLength = D3DXVECTOR3(-300, -200.0f, -Zlong * 0.3f);
	StageCollisionBox::Create(SetData);

	//橋上の擁壁
	SetData.Pos = D3DXVECTOR3(-19750.0f, 2100.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(140, 1000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-140, -1000.0f, -Zlong);
	StageCollisionBox::Create(SetData);


	//洞窟上進入不可
	SetData.Pos = D3DXVECTOR3(-9000.0f, 10300.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 7000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -7000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステ左侵入不可
	SetData.Pos = D3DXVECTOR3(800.0f, 9000.0f, 8000.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 9000.0f, 7000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -9000.0f, -7000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステ奥進入不可
	SetData.Pos = D3DXVECTOR3(4600.0f, 9000.0f, 16000.0f);
	SetData.MaxLength = D3DXVECTOR3(4600.0f, 9000.0f, Zlong + 200.0f);
	SetData.MinLength = D3DXVECTOR3(-4600.0f, -9000.0f, -(Zlong + 200.0f));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//慣れステ奥進入不可2
	SetData.Pos = D3DXVECTOR3(6000.0f, 9000.0f, 17600.0f);
	SetData.MaxLength = D3DXVECTOR3(6000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-6000.0f, -9000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//慣れステ右侵入不可
	SetData.Pos = D3DXVECTOR3(10050.0f, 2430.0f, 8350.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 2370.0f, 9000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -2370.0f, -9000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//慣れステ右床
	SetData.Pos = D3DXVECTOR3(13000.0f, 2370.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(2200.0f, 2370.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-2200.0f, -2370.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステ右床上壁
	SetData.Pos = D3DXVECTOR3(11550.0f, 10170.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(960.0f, 3000.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-960.0f, -3000.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//慣れステ右壁
	SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 10200.0f);
	SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, Zlong + 8350.0f);
	SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -Zlong - 8350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステからボス手前進入不可
	SetData.Pos = D3DXVECTOR3(16000.0f, 9000.0f, -(Zlong * 2.0f) + 180.0f);
	SetData.MaxLength = D3DXVECTOR3(16000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-16000.0f, -9000.0f, -(Zlong));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);





		//洞窟右パイプ1
	SetData.Pos = D3DXVECTOR3(4650.0f, 400.0f, 50.0f);
	SetData.MaxLength = D3DXVECTOR3(4650.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-4650.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//洞窟奥行きパイプ2
	SetData.Pos = D3DXVECTOR3(4200.0f, 400.0f, 4150.0f);
	SetData.MaxLength = D3DXVECTOR3(500.0f, 480.0f, 4150.0f);
	SetData.MinLength = D3DXVECTOR3(-500.0f, -480.0f, -4150.0f);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);Set
	StageCollisionBox::Create(SetData);



	//洞窟右パイプ3(一個上)
	SetData.Pos = D3DXVECTOR3(2000.0f, 2850.0f, 5800.0f);
	SetData.MaxLength = D3DXVECTOR3(2000.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2000.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//洞窟右パイプ4(奥)
	SetData.Pos = D3DXVECTOR3(6600.0f, 400.0f, 7750.0f);
	SetData.MaxLength = D3DXVECTOR3(2600.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong + 100.0f);
	//	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong - 100.0f);
	StageCollisionBox::Create(SetData);

	//洞窟右パイプ3(2個上)
	SetData.Pos = D3DXVECTOR3(7900.0f, 4250.0f, 9900.0f);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);


	//ボスステ右床
	SetData.Pos = D3DXVECTOR3(28980.0f, 68.0f, 9150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//ボスステ真ん中床
	SetData.Pos = D3DXVECTOR3(21915.0f, 68.0f, 2200.0f);
	SetData.MaxLength = D3DXVECTOR3(4765.0f, 68.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-4765.0f, -68.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//ボスステ左床
	SetData.Pos = D3DXVECTOR3(14850.0f, 68.0f, 9150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 9900.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -9900.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//ボスステ真ん中奥壁
	SetData.Pos = D3DXVECTOR3(21915.0f, 4000.0f, 22050.0f);
	SetData.MaxLength = D3DXVECTOR3(9765.0f, 4000.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-9765.0f, -4000.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//ボスステ右壁
	SetData.Pos = D3DXVECTOR3(32250.0f, 9000.0f, 9200.0f);
	SetData.MaxLength = D3DXVECTOR3(1000.0f, 9000.0f, Zlong + 9300.0f);
	SetData.MinLength = D3DXVECTOR3(-1000.0f, -9000.0f, -Zlong - 9300.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);












	//一番下ロング
	SetData.Pos = D3DXVECTOR3(-3600.0f, 150.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(3600.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-3600.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//一番右下段
	SetData.Pos = D3DXVECTOR3(-750.0f, 600.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(750.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-750.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番右中段
	SetData.Pos = D3DXVECTOR3(-300.0f, 1950.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番上段右
	SetData.Pos = D3DXVECTOR3(-1200.0f, 2850.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1200.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1200.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番上段左
	SetData.Pos = D3DXVECTOR3(-3900.0f, 3000.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//右２番目上段
	SetData.Pos = D3DXVECTOR3(-1500.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//右２番目中上段
	SetData.Pos = D3DXVECTOR3(-1650.0f, 1650.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//右3番目中段
	SetData.Pos = D3DXVECTOR3(-3000.0f, 1500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//中央中段右
	SetData.Pos = D3DXVECTOR3(-3750.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 750.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-150.0f, -750.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//中央中段左
	SetData.Pos = D3DXVECTOR3(-4350.0f, 1200.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 600.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -600.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//中央左上部
	SetData.Pos = D3DXVECTOR3(-6000.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//中央左中部
	SetData.Pos = D3DXVECTOR3(-6300.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//最左部
	SetData.Pos = D3DXVECTOR3(-8550.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1350.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1350.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//床下
	SetData.Pos = D3DXVECTOR3(-4950.0f, -500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//屋根上
	SetData.Pos = D3DXVECTOR3(-4950.0f, 3800.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//-------------------------------------------------------------------------------------------------------------------



	//playerが最初！
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(1200.0f, 893.0f, 0.0f);
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------

	CObjectMotionPlayer::SetPlayerNum(1);

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化

	//SetData.Pos = D3DXVECTOR3(-7500.0f, 2100.0f, 0.0f);
	//SetData.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	SetData.Pos = D3DXVECTOR3(8620.0f, 900.0f, 30.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(4260.0f, 900.0f, 4760.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(4110.0f, 900.0f, 7720.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(6580.0f, 900.0f, 7860.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(8750.0f, 900.0f, 7850.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(2040.0f, 3370.0f, 5290.0f);
	CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(3850.0f, 3370.0f, 5310.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(7280.0f, 4960.0f, 9360.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9350.0f, 4960.0f, 12980.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9320.0f, 4960.0f, 6400.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);
	SetData.Pos = D3DXVECTOR3(9300.0f, 4960.0f, 1940.0f);
		CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", SetData);











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
// 終了
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
// 更新
//===================================
void CGame2::Update()
{
	//// マウスカーソルを表示にする
//int nDrawCnt = ShowCursor(TRUE);

//while (true)
//{
//	if (nDrawCnt > 0)
//	{//表示状態のとき
//		if (nDrawCnt > 1)
//		{//2超える
//			nDrawCnt = ShowCursor(FALSE);
//		}

//		break;
//	}
//	else
//	{//非表示状態のとき
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
				{//Reset起動してない
					CInputKeyboard* keyboard = pManager->GetKeyboard();
					if (keyboard->GetPress(DIK_RSHIFT) == true)
					{//右シフト押された
						m_CGameUI->AllUiRestart();

						//mode切り替え
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
				{//起動してる
					m_CGameUI->AllUiRestart();
				}

				if (CObjectMotionEnemyBoss::GetEnemyAllNum() <= 0)
				{//敵殲滅	
					m_bNext = false;//true
					m_bStay2BOOL = true;
				}

				if (CTime::GetTime() <= 0)
				{//制限時間切れ
					m_bNext = false;
					m_bStay2BOOL = true;
					pManager->SetStayState(true);
				}


				// 配置物プライオリティの先頭を取得
				CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

				if (pObject != nullptr)
				{ // 先頭がない==プライオリティまるっとない

					if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
					{ // 対象のモデルのとき
						CObject::DATA EscData;

						// ここで使用分宣言
						CObjectMotionPlayer* pMotionPlayer;

						pMotionPlayer = (CObjectMotionPlayer*)pObject;

						D3DXVECTOR3 PlayerPos = pMotionPlayer->GetClassData().Pos;

						if (pMotionPlayer->GetPlayerNum() < 0)
						{//残機まいなすに

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


				//時間経過テキスト
				//----------------------------------
				m_nTextEndCnt++;

				if (m_nTextEndCnt == 180)
				{
					m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);
					m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 2, "球形バリアを解禁した。\n方向を気にせずに\nガードできるぞ！", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120);
					m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "< 司令部 >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 230);
				}

				if (m_nTextEndCnt == 440)
				{
					m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
				}

				if (m_nTextEndCnt == 600)
				{
					m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);
					m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 2, "戦闘ヘリは機敏だ\nRBボタンでミサイル発射だ\n上手く活用するんだ！", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120);
					m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "< 司令部 >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 230);
				}

				if (m_nTextEndCnt == 900)
				{
					m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
				}
				//----------------------------------
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

				//ショイパットの状態を取得
				DWORD dwResult = XInputGetState(0, &joykeystate);

				if (pManager->bGetInputState() == true)
				{//操作方法--trueでコントローラー
					if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
					{
						CSound* pSound = pManager->GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

						if (pManager->GetEndStatusState() == true)
						{//クリアRoute

							CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_GAME2);

						}
						else
						{//敗北
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
				{//キーボード入力反映(移動)
					if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
					{
						CSound* pSound = pManager->GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


						if (pManager->GetEndStatusState() == true)
						{//クリアRoute
					/*		CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_GAME2);*/

						}
						else
						{//敗北
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
	{//次のステージに遷移
		m_nCnt++;


		if (m_nCnt == 10)
		{
			m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 3, "軍港前に到着。\n待機する。", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80);
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
// 描画
//===================================
void CGame2::Draw()
{
	//	CObstacleSet::DebugSetDataDraw();//設置用デバッグ描画
	char cData2[100] = {};
	//snprintf(cData2, sizeof(cData2), "自機残機：%d", CObjectMotionPlayer::GetPlayerNum()); // 数値を文字列に変換してCDataにコピー
	//// mousePos.x と mousePos.y がマウスの位置
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
	{//待機画面
		m_StayUI->Draw();

		//char aData2[100];

		//int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		//snprintf(aData2, sizeof(aData2), "タイムボーナス:%d", nSetNum); // 数値を文字列に変換してCDataにコピー

		//CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);

	}

	if (m_StayPush == true)
	{//押す待機
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
		{//操作方法--trueでコントローラー
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "Aボタンで次に"); // 数値を文字列に変換してCDataにコピー

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);

		}
		else
		{//キーボード入力反映(移動)
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "マウス右クリックで次に"); // 数値を文字列に変換してCDataにコピー

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);

		}
	}
}
///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//===================================
// コンストラクタ
//===================================
CMovie2::CMovie2()
{
}

//===================================
// デストラクタ
//===================================
CMovie2::~CMovie2()
{

}
//===================================
// 初期化
//===================================
HRESULT CMovie2::Init()
{
	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時

	SetData.Pos = D3DXVECTOR3(14950.0f, 10.0f, 14950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);



	float Zlong = 750.0f;
	float ZPos = 250.0f;




	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//ステージ配置物ロード




	//playerが最初！
//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(13650.0f, 4750.0f, 850.0f);
	//SetData.rot.y = -1.57f;
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);


	SetData.Pos = D3DXVECTOR3(19500.0f, 0.0f, 17500.0f);
	//SetData.rot.y = -1.57f;
	CObjectShip::Create("DATA\\motion_friendship.txt", SetData);



	SetData.Pos = D3DXVECTOR3(28267.3f, 130.5f, 14727.2f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29990.5f, 130.5f, 11353.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29007.5f, 130.5f, 8101.8f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29471.1f, 130.5f, 1642.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(25086.5f, 130.5f, 1537.6f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(20708.3f, 130.5f, 2084.1f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14638.1f, 130.5f, 3419.4f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(15514.9f, 130.5f, 6690.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14446.6f, 130.5f, 10788.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(13519.9f, 130.5f, 14477.9f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(15073.8f, 130.5f, 17979.7f);
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
	m_pLongPush = CLongPush::Create();
	return S_OK;
}
//===================================
// 終了
//===================================
void CMovie2::Uninit()
{
	//m_pLongPush->Uninit();
	//m_CGameUI->Uninit();
	//m_CGameUI->SetDeath(true);
	//m_CTextWindow->Uninit();
	//m_CTextWindow->SetDeath(true);

}
//===================================
// 更新
//===================================
void CMovie2::Update()
{
	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);

	m_nCnt++;

	if (m_nCnt == 100)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "これより、\n敵新型強襲揚陸艦\nの捕縛を開始。", D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 260);

		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<捕縛艦隊>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1060);
	}


	if (m_nCnt == 450)
	{
		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 3, "....!!\n12時よりアクティブソナー！\n魚雷接近！回避！", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);

	}

	if (m_nCnt == 800)
	{
		//m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 2, "クソッ............総員退艦！\n.........................\n...............", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);
		//m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 1, "<B-2パイロット>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 190);
	}

	if (m_nCnt == 1210)
	{
		m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
	}



	if (m_nCnt == 1250)
	{
		m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 20, 40, 3, "  -Mission Update-\n敵砲潜水艦により捕縛失敗!!\n潜水艦と揚陸艦を撃沈せよ!", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 470);


		m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<司令部>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000);
	}

	if (m_nCnt == 1680)
	{
		m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 20, 40, 3, "三隻撃沈時点で作戦成功。\nそして時間切れで逃亡とみなし\n失敗とする。", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 380);

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





	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonPress(CInputKeyboard::MouseKey_Left) == true)
	{
		m_pLongPush->AddCnt();
	}
	else
	{
		m_pLongPush->SubCnt();
	}

	m_pLongPush->Update();

	if (m_pLongPush->PushOkBool())
	{
		CSound* pSound = pManager->GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);
		m_nCnt = 0;
		CFade* pFade = pManager->GetFade();
		pFade->SetFade(CScene::MODE_GAME3);
	}



}
//===================================
// 描画
//===================================
void CMovie2::Draw()
{
	CManager* pManager = CManager::GetInstance();



}



//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//===================================
// コンストラクタ
//===================================
CGame3::CGame3()
{
}
//===================================
// デストラクタ
//===================================
CGame3::~CGame3()
{
}
//===================================
// 初期化
//===================================
HRESULT CGame3::Init()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//フォグの有効設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);



	CTime::Create();
	CTime::ChangeTime(70);

	Sky3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//	CObject3D::Create();//現状床

	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時

	SetData.Pos = D3DXVECTOR3(4950.0f, 10.0f, 4950.0f);
	CSea::Create(SetData.Pos, SetData.rot, 0.7f);

	SetData.Pos.y += 20.0f;
	SetData.rot.y = D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.2f);

	SetData.Pos.y += 30.0f;
	SetData.rot.y = -D3DX_PI * 0.5f;
	CSea::Create(SetData.Pos, SetData.rot, 0.1f);

	SetData = CObject::DataInit();//初期化同時

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//ステージ配置物ロード

	CScore::Create();

	//	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//経路テーブルをロード

	//	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//射撃地点をロード


	m_CTextWindow = CTextWindow::Create();
	m_CTextWindowSub = CTextWindow::Create();

	pManager->SetbNow3DMode(true);

	m_CGameUI = CGameUI::Create();

	CNewBulletALL::Create();
	CObject3DParticleAll::Create();
	CMissileALL::Create();

	SetStayNextStage(false);

	//配置物
	//-------------------------------------------------------------------------------------------------------------------


	//-------------------------------------------------------------------------------------------------------------------

	SetData.Pos = D3DXVECTOR3(-(3300.0f * 0.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));



	SetData.Pos = D3DXVECTOR3(-(3300.0f * 1.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));




	SetData.Pos = D3DXVECTOR3(-(3300.0f * 2.5f), (3300.0f * 0.5f), +(3300.0f * 0.8f));
	CDebugwall::Create(SetData.Pos, D3DXVECTOR3(-1.57f, 0.0f, 0.0f));


















	//--------------------------------------------------------------------------------------------------------------------
	//2Dステージ配置物
	float ZPos = 250.0f;
	float Zlong = 750.0f;

	//左の橋
	SetData.Pos = D3DXVECTOR3(-17450, 1600.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(7750, 500.0f, Zlong - 200.0f);
	SetData.MinLength = D3DXVECTOR3(-7750.0f, -500.0f, -Zlong - 200.0f);
	StageCollisionBox::Create(SetData);
	//StageCollisionBox

	//stage左端進入不可
	SetData.Pos = D3DXVECTOR3(-26500.0f, 8000.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(1300, 8000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1300, -8000.0f, -Zlong);
	StageCollisionBox::Create(SetData);


	//トラック当たり判定
	SetData.Pos = D3DXVECTOR3(-21250.0f, 2130.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(300, 200.0f, Zlong * 0.3f);	//DEBUG視認性
	SetData.MinLength = D3DXVECTOR3(-300, -200.0f, -Zlong * 0.3f);
	StageCollisionBox::Create(SetData);

	//橋上の擁壁
	SetData.Pos = D3DXVECTOR3(-19750.0f, 2100.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(140, 1000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-140, -1000.0f, -Zlong);
	StageCollisionBox::Create(SetData);

	//洞窟上進入不可
	SetData.Pos = D3DXVECTOR3(-9000.0f, 10300.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 7000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -7000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステ左侵入不可
	SetData.Pos = D3DXVECTOR3(800.0f, 9000.0f, 8000.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 9000.0f, 7000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -9000.0f, -7000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステ奥進入不可
	SetData.Pos = D3DXVECTOR3(4600.0f, 9000.0f, 16000.0f);
	SetData.MaxLength = D3DXVECTOR3(4600.0f, 9000.0f, Zlong + 200.0f);
	SetData.MinLength = D3DXVECTOR3(-4600.0f, -9000.0f, -(Zlong + 200.0f));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//慣れステ奥進入不可2
	SetData.Pos = D3DXVECTOR3(6000.0f, 9000.0f, 17600.0f);
	SetData.MaxLength = D3DXVECTOR3(6000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-6000.0f, -9000.0f, -Zlong);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//慣れステ右侵入不可
	SetData.Pos = D3DXVECTOR3(10050.0f, 2430.0f, 8350.0f);
	SetData.MaxLength = D3DXVECTOR3(800.0f, 2370.0f, 9000.0f);
	SetData.MinLength = D3DXVECTOR3(-800.0f, -2370.0f, -9000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//慣れステ右床
	SetData.Pos = D3DXVECTOR3(13000.0f, 2370.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(2200.0f, 2370.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-2200.0f, -2370.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステ右床上壁
	SetData.Pos = D3DXVECTOR3(11550.0f, 10170.0f, 0.0f);
	SetData.MaxLength = D3DXVECTOR3(960.0f, 3000.0f, Zlong + 350.0f);
	SetData.MinLength = D3DXVECTOR3(-960.0f, -3000.0f, -Zlong - 350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//慣れステ右壁
	SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 10200.0f);
	SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, Zlong + 8350.0f);
	SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -Zlong - 8350.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//慣れステからボス手前進入不可
	SetData.Pos = D3DXVECTOR3(16000.0f, 9000.0f, -(Zlong * 2.0f) + 180.0f);
	SetData.MaxLength = D3DXVECTOR3(16000.0f, 9000.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-16000.0f, -9000.0f, -(Zlong));
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);





		//洞窟右パイプ1
	SetData.Pos = D3DXVECTOR3(4650.0f, 400.0f, 50.0f);
	SetData.MaxLength = D3DXVECTOR3(4650.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-4650.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//洞窟奥行きパイプ2
	SetData.Pos = D3DXVECTOR3(4200.0f, 400.0f, 4150.0f);
	SetData.MaxLength = D3DXVECTOR3(500.0f, 480.0f, 4150.0f);
	SetData.MinLength = D3DXVECTOR3(-500.0f, -480.0f, -4150.0f);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);Set
	StageCollisionBox::Create(SetData);



	//洞窟右パイプ3(一個上)
	SetData.Pos = D3DXVECTOR3(2000.0f, 2850.0f, 5800.0f);
	SetData.MaxLength = D3DXVECTOR3(2000.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2000.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);

	//洞窟右パイプ4(奥)
	SetData.Pos = D3DXVECTOR3(6600.0f, 400.0f, 7750.0f);
	SetData.MaxLength = D3DXVECTOR3(2600.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong + 100.0f);
	//	SetData.MinLength = D3DXVECTOR3(-2600.0f, -480.0f, -Zlong - 100.0f);
	StageCollisionBox::Create(SetData);

	//洞窟右パイプ3(2個上)
	SetData.Pos = D3DXVECTOR3(7900.0f, 4250.0f, 9900.0f);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 480.0f, Zlong - 100.0f);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -480.0f, -Zlong + 100.0f);
	StageCollisionBox::Create(SetData);



	//慣れステ右壁
	SetData.Pos = D3DXVECTOR3(11540.0f, 9000.0f, 22150.0f);
	SetData.MaxLength = D3DXVECTOR3(970.0f, 9000.0f, 22150.0f);
	SetData.MinLength = D3DXVECTOR3(-970.0f, -9000.0f, -22150.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//ボスステ右床----------------------------------------------------------------------------
	SetData.Pos = D3DXVECTOR3(28980.0f, 68.0f, 22150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 22150.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -22150.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//ボスステ真ん中床
	SetData.Pos = D3DXVECTOR3(21915.0f, 68.0f, 2200.0f);
	SetData.MaxLength = D3DXVECTOR3(4765.0f, 68.0f, 2945.0f);
	SetData.MinLength = D3DXVECTOR3(-4765.0f, -68.0f, -2945.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//ボスステ左床
	SetData.Pos = D3DXVECTOR3(14850.0f, 68.0f, 22150.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 68.0f, 22150.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -68.0f, -22150.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//橋左側土台
	SetData.Pos = D3DXVECTOR3(14850.0f, 160.0f, 25350.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 2300.0f, 1100.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -2300.0f, -1100.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);
	
	//橋真ん中
	SetData.Pos = D3DXVECTOR3(21915.0f, 2235.0f, 25350.0f);
	SetData.MaxLength = D3DXVECTOR3(4765.0f, 225.0f, 1100.0f);
	SetData.MinLength = D3DXVECTOR3(-4765.0f, -225.0f, -1100.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//橋右側土台
	SetData.Pos = D3DXVECTOR3(28980.0f, 160.0f, 25350.0f);
	SetData.MaxLength = D3DXVECTOR3(2300.0f, 2300.0f, 1100.0f);
	SetData.MinLength = D3DXVECTOR3(-2300.0f, -2300.0f, -1100.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//ボスステ真ん中奥壁
	SetData.Pos = D3DXVECTOR3(21915.0f, 4000.0f, 44300.0f);
	SetData.MaxLength = D3DXVECTOR3(9765.0f, 4000.0f, 3000.0f);
	SetData.MinLength = D3DXVECTOR3(-9765.0f, -4000.0f, -3000.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//ボスステ右壁
	SetData.Pos = D3DXVECTOR3(32250.0f, 9000.0f, 22150.0f);
	SetData.MaxLength = D3DXVECTOR3(1000.0f, 9000.0f, 22150.0f);
	SetData.MinLength = D3DXVECTOR3(-1000.0f, -9000.0f, -22150.0f);
	StageCollisionBox::Create(SetData);
	//CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);
	//------------------------------------------------------------------------------------------------











	//一番下ロング
	SetData.Pos = D3DXVECTOR3(-3600.0f, 150.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(3600.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-3600.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//一番右下段
	SetData.Pos = D3DXVECTOR3(-750.0f, 600.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(750.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-750.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番右中段
	SetData.Pos = D3DXVECTOR3(-300.0f, 1950.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番上段右
	SetData.Pos = D3DXVECTOR3(-1200.0f, 2850.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1200.0f, 450.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1200.0f, -450.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//一番上段左
	SetData.Pos = D3DXVECTOR3(-3900.0f, 3000.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1500.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1500.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//右２番目上段
	SetData.Pos = D3DXVECTOR3(-1500.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(900.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-900.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//右２番目中上段
	SetData.Pos = D3DXVECTOR3(-1650.0f, 1650.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);



	//右3番目中段
	SetData.Pos = D3DXVECTOR3(-3000.0f, 1500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 300.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -300.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//中央中段右
	SetData.Pos = D3DXVECTOR3(-3750.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(150.0f, 750.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-150.0f, -750.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//中央中段左
	SetData.Pos = D3DXVECTOR3(-4350.0f, 1200.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(450.0f, 600.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-450.0f, -600.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);


	//中央左上部
	SetData.Pos = D3DXVECTOR3(-6000.0f, 2250.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(600.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-600.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//中央左中部
	SetData.Pos = D3DXVECTOR3(-6300.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(300.0f, 150.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-300.0f, -150.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//最左部
	SetData.Pos = D3DXVECTOR3(-8550.0f, 1050.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(1350.0f, 1050.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-1350.0f, -1050.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//床下
	SetData.Pos = D3DXVECTOR3(-4950.0f, -500.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);

	//屋根上
	SetData.Pos = D3DXVECTOR3(-4950.0f, 3800.0f, ZPos);
	SetData.MaxLength = D3DXVECTOR3(4950.0f, 500.0f, Zlong);
	SetData.MinLength = D3DXVECTOR3(-4950.0f, -500.0f, -Zlong);
	CStageCollisionBox3D2D::Create(SetData, CStageCollisionBox3D2D::TYPE_NOMALBLOCK);




	//-------------------------------------------------------------------------------------------------------------------



	//playerが最初！
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
//	SetData.Pos = D3DXVECTOR3(-4200.0f, 3200.0f, 0.0f);
	SetData.Pos = D3DXVECTOR3(13760.0f, 4730.0f, 700.0f);
	CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);



	SetData.Pos = D3DXVECTOR3(28267.3f, 130.5f, 14727.2f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29990.5f, 130.5f, 11353.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(29007.5f, 130.5f, 8101.8f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(29471.1f, 130.5f, 1642.4f);
	//CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(25086.5f, 130.5f, 1537.6f);
	//CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(20708.3f, 130.5f, 2084.1f);
	//CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(14638.1f, 130.5f, 3419.4f);
	//CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(15514.9f, 130.5f, 6690.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(14446.6f, 130.5f, 10788.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(13519.9f, 130.5f, 14477.9f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	SetData.Pos = D3DXVECTOR3(15073.8f, 130.5f, 17979.7f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);



	SetData.Pos = D3DXVECTOR3(23601.0f, 2460.0f, 24536.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(19378.0f, 2460.0f, 24421.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(24601.0f, 2460.0f, 26036.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(18378.0f, 2460.0f, 26021.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);


	SetData.Pos = D3DXVECTOR3(16469.0f, 1000.0f, 13094.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(15748.0f, 1000.0f, 18604.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(15714.0f, 1000.0f, 30260.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(16274.0f, 1000.0f, 36257.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(27469.0f, 1000.0f, 13094.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(27748.0f, 1000.0f, 18604.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(27714.0f, 1000.0f, 30260.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(27274.0f, 1000.0f, 36257.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);
	SetData.Pos = D3DXVECTOR3(27229.0f, 1000.0f, 31664.0f);
	CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);


	//SetData.Pos = D3DXVECTOR3(16489.6f, 867.6f, 7604.4f);
	//CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(16256.6f, 867.9f, 11816.8f);
	//CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(18592.6f, 871.9f, 3222.6f);
	//CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(23563.8f, 827.2f, 3104.1f);
	//CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);

	//SetData.Pos = D3DXVECTOR3(24397.4f, 824.2f, 9599.4f);
	//CObjectMotionEnemyfast::Create("DATA\\motion_Tank.txt", SetData);


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
// 終了
//===================================
void CGame3::Uninit()
{
	//m_pLongPush->Uninit();

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
// 更新
//===================================
void CGame3::Update()
{
	//// マウスカーソルを表示にする
//int nDrawCnt = ShowCursor(TRUE);

//while (true)
//{
//	if (nDrawCnt > 0)
//	{//表示状態のとき
//		if (nDrawCnt > 1)
//		{//2超える
//			nDrawCnt = ShowCursor(FALSE);
//		}

//		break;
//	}
//	else
//	{//非表示状態のとき
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
				{//Reset起動してない

					m_nCnt++;

					if (m_nCnt == 60)
					{
						m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "バリアは護衛艦からだ！\n護衛艦を先に攻撃せよ！", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 260);

						m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<司令部>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 720);
					}


					if (m_nCnt == 510)
					{
						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 2, "速力からの推測！\n60秒で逃げられる！\n急ぐんだ！", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 260);

					}
					if (m_nCnt == 870)
					{
						m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					}


					if (m_nCnt == 1000)
					{
						m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "ミサイルは脅威だ！\nガードか回避するんだ！", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 200);

						m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<司令部>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 380);
					}
					if (m_nCnt == 1400)
					{
						m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					}

					if (m_nCnt == 2300)
					{
						m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "残り30秒！まずいぞ！\n急いで撃破するんだ！", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 200);

						m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<司令部>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 380);
					}
					if (m_nCnt == 2700)
					{
						m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					}



					if (m_nCnt == 3200)
					{
						m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

						m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 4, "くそ！逃げられてしまう！", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 200);

						m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<司令部>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 380);
					}
					if (m_nCnt == 3600)
					{
						m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					}


					//if (m_nCnt == 1250)
					//{
					//	m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

					//	m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 20, 40, 3, "  -Mission Update-\n敵砲潜水艦により捕縛失敗!!\n潜水艦と揚陸艦を撃沈せよ!", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 470);


					//	m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "<司令部>", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000);
					//}

					//if (m_nCnt == 1680)
					//{
					//	m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 20, 40, 3, "三隻撃沈時点で作戦成功。\nそして時間切れで逃亡とみなし\n失敗とする。", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 380);

					//}

					//if (m_nCnt == 2300)
					//{
					//	m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
					//}










					CInputKeyboard* keyboard = pManager->GetKeyboard();
					if (keyboard->GetPress(DIK_RSHIFT) == true)
					{//右シフト押された
						m_CGameUI->AllUiRestart();

						//mode切り替え
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
				{//起動してる
					m_CGameUI->AllUiRestart();
				}

				//if (CObjectMotionEnemyBoss::GetEnemyAllNum() <= 0)
				//{//敵殲滅	
				//	m_bNext = false;//true
				//	m_bStay2BOOL = true;
				//}

				if (CObjectMotionEnemyBoss::GetEnemyAllNum() <= 0)
				{//敵殲滅	
					m_bNext = false;//true
					m_bStay2BOOL = true;
					pManager->SetStayState(true);
					pManager->SetEndStatusState(true);
					CScene::SetStageClear(true);
				}



				if (CTime::GetTime() <= 0)
				{//制限時間切れ
					m_bNext = false;
					m_bStay2BOOL = true;
					pManager->SetStayState(true);
				}


				// 配置物プライオリティの先頭を取得
				CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

				if (pObject != nullptr)
				{ // 先頭がない==プライオリティまるっとない

					if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
					{ // 対象のモデルのとき
						CObject::DATA EscData;

						// ここで使用分宣言
						CObjectMotionPlayer* pMotionPlayer;

						pMotionPlayer = (CObjectMotionPlayer*)pObject;

						D3DXVECTOR3 PlayerPos = pMotionPlayer->GetClassData().Pos;

						if (pMotionPlayer->GetPlayerNum() < 0)
						{//残機まいなすに

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

				//ショイパットの状態を取得
				DWORD dwResult = XInputGetState(0, &joykeystate);

				if (pManager->bGetInputState() == true)
				{//操作方法--trueでコントローラー
					if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
					{
						CSound* pSound = pManager->GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

						if (pManager->GetEndStatusState() == true)
						{//クリアRoute

							CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_RESULT);

						}
						else
						{//敗北
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
				{//キーボード入力反映(移動)
					if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
					{
						CSound* pSound = pManager->GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


						if (pManager->GetEndStatusState() == true)
						{//クリアRoute
					/*		CManager* pManager = CManager::GetInstance();
							pManager->SetStayStatusState(false);
							pManager->SetStayState(false);
							pManager->SetPauseState(false);


							CFade* pFade = pManager->GetFade();
							pFade->SetFade(CScene::MODE_GAME2);*/

						}
						else
						{//敗北
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
	{//次のステージに遷移
		//m_nCnt++;


		//if (m_nCnt == 10)
		//{
		//	m_CGameUI->SetStateChangeUi(true, CGameUI::UI_TEXTWINDOW);

		//	m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 310.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 24, 40, 3, "軍港前に到着。\n待機する。", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80);
		//	m_CTextWindowSub->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 410.0f, SCREEN_HEIGHT * 0.5f - 265.0f, 0.0f), 16, 40, 2, "< COM >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 170);
		//}

		//if (m_nCnt == 220)
		//{
		//	m_CGameUI->SetStateChangeUi(false, CGameUI::UI_TEXTIMAGE);
		//}

		//if (m_nCnt == 300)
		//{
		//	//			CTime::ChangeTime(CTime::GetTime());
		//	CFade* pFade = pManager->GetFade();
		//	pFade->SetFade(CScene::MODE_MOVIE2);
		//}

	}
}
//===================================
// 描画
//===================================
void CGame3::Draw()
{
	//	CObstacleSet::DebugSetDataDraw();//設置用デバッグ描画
	char cData2[100] = {};
	//snprintf(cData2, sizeof(cData2), "自機残機：%d", CObjectMotionPlayer::GetPlayerNum()); // 数値を文字列に変換してCDataにコピー
	//// mousePos.x と mousePos.y がマウスの位置
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
	{//待機画面
		m_StayUI->Draw();

		//char aData2[100];

	//	int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		//snprintf(aData2, sizeof(aData2), "タイムボーナス:%d", nSetNum); // 数値を文字列に変換してCDataにコピー

		//CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);

	}

	if (m_StayPush == true)
	{//押す待機
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
		{//操作方法--trueでコントローラー
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "Aボタンで次に"); // 数値を文字列に変換してCDataにコピー

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);

		}
		else
		{//キーボード入力反映(移動)
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "マウス右クリックで次に"); // 数値を文字列に変換してCDataにコピー

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);

		}
	}
}















///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//===================================
// コンストラクタ
//===================================
CResult::CResult()
{
}

//===================================
// デストラクタ
//===================================
CResult::~CResult()
{
}
//===================================
// 初期化
//===================================
HRESULT CResult::Init()
{
	CScore::AddScore(CScore::TANK_SCORE1);



	CObject3D::Create();

	if (CScene::GetStageClear() == true)
	{
		//playerが最初！
	//-------------------------------------------------------------
		CObject::DATA SetData = CObject::DataInit();//初期化
		SetData.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CObjectMotionPlayer::Create("DATA\\motion_ARES-42.txt", SetData);
		//-------------------------------------------------------------
	}

	CResultUI::Create();

	//スコアロード
	ScoreLoad();

	m_ScoreNum[5] = CScore::GetScore();

	m_NUM = m_ScoreNum[5];

	CScore::ResetScore();

	// 降順（大きい順）にソート
	std::sort(m_ScoreNum, m_ScoreNum + 6, std::greater<int>());


	ScoreWrite();


	CManager* pManager = CManager::GetInstance();
	pManager->SetStayStatusState(false);
	pManager->SetStayState(false);
	pManager->SetPauseState(false);

	CSound* pSound = pManager->GetSound();

	if (pSound != nullptr)
	{
		pSound->StopSound();
	}

	pSound->PlaySound(CSound::SOUND_LABEL_SE_JET);

	return E_NOTIMPL;
}
//===================================
// 終了
//===================================
void CResult::Uninit()
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	if (pSound != nullptr)
	{
		pSound->StopSound(CSound::SOUND_LABEL_SE_JET);
	}
}
//===================================
// 更新
//===================================
void CResult::Update()
{

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);


	// マウスカーソルを表示にする
	int nDrawCnt = ShowCursor(TRUE);

	while (true)
	{
		if (nDrawCnt > 0)
		{//表示状態のとき
			if (nDrawCnt > 1)
			{//2超える
				nDrawCnt = ShowCursor(FALSE);
			}

			break;
		}
		else
		{//非表示状態のとき
			nDrawCnt = ShowCursor(TRUE);
		}
	}


	if (dwResult == ERROR_SUCCESS)
	{//キーボード/コントローラー入力反映(移動)
//		ControllerInput();
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_START) || JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A))
		{//左マウスクリック/STARTキー/Aキー

			CSound* pSound = pManager->GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_TITLE);
		}
	}
	else
	{//キーボード入力反映(移動)
		if (keyboard->GetTrigger(DIK_RETURN) == true || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
		{//エンターもしくは左マウスクリック
			CSound* pSound = pManager->GetSound();
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

			CFade* pFade = pManager->GetFade();
			pFade->SetFade(CScene::MODE_TITLE);
		}
	}
}
//===================================
// 描画
//===================================
void CResult::Draw()
{
	const char* aData = {};

	if (CScene::GetStageClear() == true)
	{
		aData = "ゲームクリア!!!";

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 570.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 80, CFont::FONT_KEIFONT, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), aData);
	}
	else
	{
		aData = "途中敗退...";

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 570.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 80, CFont::FONT_GENKAI, D3DXCOLOR(0.1f, 0.1f, 0.1f, 0.8f), aData);
	}

	char aData2[100];

	snprintf(aData2, sizeof(aData2), "今回のスコア:%d", m_NUM); // 数値を文字列に変換してCDataにコピー

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 220.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), aData2);






	if (m_ScoreNum[0] != m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "1 位:%d", m_ScoreNum[0]); // 数値を文字列に変換してCDataにコピー
		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 120.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);

	}
	else
	{
		snprintf(aData2, sizeof(aData2), "1 位:%d", m_ScoreNum[0]); // 数値を文字列に変換してCDataにコピー
		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 120.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}
	if (m_ScoreNum[1] != m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "2位:%d", m_ScoreNum[1]); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 60.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);

	}
	else
	{
		snprintf(aData2, sizeof(aData2), "2位:%d", m_ScoreNum[1]); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f - 60.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}
	if (m_ScoreNum[2] != m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "3位:%d", m_ScoreNum[2]); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 0.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);


	}
	else
	{
		snprintf(aData2, sizeof(aData2), "3位:%d", m_ScoreNum[2]); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 0.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}
	if (m_ScoreNum[3] != m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "4位:%d", m_ScoreNum[3]); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 60.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);

	}
	else
	{
		snprintf(aData2, sizeof(aData2), "4位:%d", m_ScoreNum[3]); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 60.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}
	if (m_ScoreNum[4] != m_NUM)
	{
		snprintf(aData2, sizeof(aData2), "5位:%d", m_ScoreNum[4]); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 120.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData2);

	}
	else
	{
		snprintf(aData2, sizeof(aData2), "5位:%d", m_ScoreNum[4]); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 280.0f, SCREEN_HEIGHT / 2.0f + 120.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), aData2);

	}











	aData = "Startボタン/Aボタン";
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
// スコアロード
//===================================
void CResult::ScoreLoad()
{
	FILE* pFile = nullptr; // ファイルポインタを宣言

	pFile = fopen("DATA\\score.txt", "r");

	if (pFile != nullptr)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fscanf(pFile, "%d", &m_ScoreNum[nCnt]);
		}

		fclose(pFile);//閉じる
	}

}
//===================================
// スコア描画
//===================================
void CResult::ScoreWrite()
{
	FILE* pFile = nullptr; // ファイルポインタを宣言

	pFile = fopen("DATA\\score.txt", "w");

	if (pFile != nullptr)
	{
		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			fprintf(pFile, "%d\n", m_ScoreNum[nCnt]);
		}

		fclose(pFile);//閉じる
	}
}



