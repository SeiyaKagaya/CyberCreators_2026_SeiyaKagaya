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

// 静的メンバー変数の定義
CScene::MODE CScene::m_NowState = CScene::MODE_TITLE; // 初期値をMODE_TITLEに設定
bool CScene::m_bStageClear = false;


//++
//++シーンすべての管理
//++
 

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


//+
//+ゲームシーン
//+

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
	CTime::Create();

	CObject3D::Create();//現状床

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//ステージ配置物ロード

	CScore::Create();

	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//経路テーブルをロード

	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//射撃地点をロード

	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時
	
	//配置物
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


	//playerが最初！
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
	SetData.Pos = D3DXVECTOR3(180.0f, 0.0f, 180.0f);
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------

	CObjectMotionPlayer::SetPlayerNum(1);//残基格納

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化

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
// 終了
//===================================
void CGame::Uninit()
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	if (pSound != nullptr)
	{
		pSound->StopSound(CSound::SOUND_LABEL_BGM001);
	}
}

//===================================
// 更新
//===================================
void CGame::Update()
{
	// マウスカーソルを非表示にする
	int nDrawCnt = ShowCursor(FALSE);

	while (true)
	{
		if (nDrawCnt >= 0)
		{//表示状態のとき
			nDrawCnt = ShowCursor(FALSE);
		}
		else
		{//非表示状態のとき

			if (nDrawCnt < -1)
			{//下がりすぎ防止
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
			{//敵殲滅	
				m_bNext = true;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//制限時間切れ
				m_bNext = false;
				m_bStay2BOOL = true;
			}

			// 配置物プライオリティの先頭を取得
			CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

			if (pObject != nullptr)
			{ // 先頭がない==プライオリティまるっとない

				if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
				{ // 対象のモデルのとき

					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					CObject::DATA EscData;

					// ここで使用分宣言
					CObjectMotionPlayer* pMotionPlayer;

					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					if (pMotionPlayer->GetPlayerNum() < 0)
					{//残機まいなすに

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
					{//次に
						CScore::AddScore(CTime::GetTime() * CScore::TIMEBONUS);

						pManager->SetEndStatusState(true);
						pManager->SetStayState(true);
					}
					else
					{//戻る
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

			//ショイパットの状態を取得
			DWORD dwResult = XInputGetState(0, &joykeystate);

			if (pManager->bGetInputState() == true)
			{//操作方法--trueでコントローラー
				if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

					if (pManager->GetEndStatusState()==true)
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

	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "自機残機：%d", CObjectMotionPlayer::GetPlayerNum()); // 数値を文字列に変換してCDataにコピー
	// mousePos.x と mousePos.y がマウスの位置
	CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_SOUKOUMINCHO, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);
	
	if (pManager->GetPauseState() == true)
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//待機画面
		m_StayUI->Draw();

		char aData2[100];

		int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		snprintf(aData2, sizeof(aData2), "タイムボーナス:%d", nSetNum); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);
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

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f,0.2f,0.2f, (float)m_nbuttonCnt * 0.01f), aData2);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+ゲーム2シーン
//+


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
	CTime::Create();

	CObject3D::Create();//現状床

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE2\\model.txt");//ステージ配置物ロード

	CScore::Create();

	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE2\\RouteResult.csv");//経路テーブルをロード
	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時

	//配置物
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

	//playerが最初！
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
	SetData.Pos = D3DXVECTOR3(1200.0f, 0.0f, 1200.0f);
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);//残基格納

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
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
// 終了
//===================================
void CGame2::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM002);
}

//===================================
// 更新
//===================================
void CGame2::Update()
{
	// マウスカーソルを非表示にする
	int nDrawCnt = ShowCursor(FALSE);

	while (true)
	{
		if (nDrawCnt >= 0)
		{//表示状態のとき
			nDrawCnt = ShowCursor(FALSE);
		}
		else
		{//非表示状態のとき

			if (nDrawCnt < -1)
			{//下がりすぎ防止
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
			{//敵殲滅	
				m_bNext = true;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//制限時間切れ
				m_bNext = false;
				m_bStay2BOOL = true;
			}

			// 配置物プライオリティの先頭を取得
			CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

			if (pObject != nullptr)
			{ // 先頭がない==プライオリティまるっとない

				if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
				{ // 対象のモデルのとき

					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					CObject::DATA EscData;

					// ここで使用分宣言
					CObjectMotionPlayer* pMotionPlayer;

					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					if (pMotionPlayer->GetPlayerNum() < 0)
					{//残機まいなすに
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
					{//次に
						CScore::AddScore(CTime::GetTime() * CScore::TIMEBONUS);

						pManager->SetEndStatusState(true);
						pManager->SetStayState(true);
					}
					else
					{//戻る
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
			//ショイパットの状態を取得
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

			//ショイパットの状態を取得
			DWORD dwResult = XInputGetState(0, &joykeystate);

			//PAUSE起動
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
						pFade->SetFade(CScene::MODE_GAME3);

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
						CManager* pManager = CManager::GetInstance();
						pManager->SetStayStatusState(false);
						pManager->SetStayState(false);
						pManager->SetPauseState(false);

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_GAME3);
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

//===================================
// 描画
//===================================
void CGame2::Draw()
{
	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "自機残機：%d", CObjectMotionPlayer::GetPlayerNum()); // 数値を文字列に変換してCDataにコピー
	// mousePos.x と mousePos.y がマウスの位置
	CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_MILITARY, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();

	if (pManager->GetPauseState() == true)
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//待機画面
		m_StayUI->Draw();

		char aData2[100];

		int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		snprintf(aData2, sizeof(aData2), "タイムボーナス:%d", nSetNum); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);

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

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt*0.01f), aData2);
		}
		else
		{//キーボード入力反映(移動)
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "マウス右クリックで次に"); // 数値を文字列に変換してCDataにコピー

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt * 0.01f), aData2);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+ゲーム3シーン
//+


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
	CTime::Create();

	CObject3D::Create();//現状床

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE3\\model.txt");//ステージ配置物ロード

	CScore::Create();

	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE3\\RouteResult.csv");//経路テーブルをロード
	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時

	//配置物
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




	//playerが最初！
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
	SetData.Pos = D3DXVECTOR3(2550.0f, 0.0f, 450.0f);
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------
	CObjectMotionPlayer::SetPlayerNum(1);//残基格納

	//	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
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
// 終了
//===================================
void CGame3::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM003);
}

//===================================
// 更新
//===================================
void CGame3::Update()
{
	// マウスカーソルを非表示にする
	int nDrawCnt = ShowCursor(FALSE);

	while (true)
	{
		if (nDrawCnt >= 0)
		{//表示状態のとき
			nDrawCnt = ShowCursor(FALSE);
		}
		else
		{//非表示状態のとき

			if (nDrawCnt < -1)
			{//下がりすぎ防止
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
			{//敵殲滅	
				m_bNext = true;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//制限時間切れ
				m_bNext = false;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//制限時間切れ

				pManager->SetEndStatusState(false);
				pManager->SetStayState(true);
			}

			// 配置物プライオリティの先頭を取得
			CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

			if (pObject != nullptr)
			{ // 先頭がない==プライオリティまるっとない

				if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
				{ // 対象のモデルのとき

					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					CObject::DATA EscData;

					// ここで使用分宣言
					CObjectMotionPlayer* pMotionPlayer;

					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					if (pMotionPlayer->GetPlayerNum() < 0)
					{//残機まいなすに
					
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
					{//次に
						CScore::AddScore(CTime::GetTime() * CScore::TIMEBONUS);

						pManager->SetEndStatusState(true);
						pManager->SetStayState(true);
					}
					else
					{//戻る
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

			//ショイパットの状態を取得
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

			//ショイパットの状態を取得
			DWORD dwResult = XInputGetState(0, &joykeystate);

			//PAUSE起動
			if (pManager->bGetInputState() == true)
			{//操作方法--trueでコントローラー
				if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);

					if (pManager->GetEndStatusState() == true)
					{//クリアRoute
	
						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_GAME4);
					}
					else
					{//敗北

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
					
						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_GAME4);
				
					}
					else
					{//敗北
						
						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);

					}
				}
			}
		}
	}
}

//===================================
// 描画
//===================================
void CGame3::Draw()
{
	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "自機残機：%d", CObjectMotionPlayer::GetPlayerNum()); // 数値を文字列に変換してCDataにコピー
	
	// mousePos.x と mousePos.y がマウスの位置
	CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_MILITARY, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();

	if (pManager->GetPauseState() == true)
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//待機画面
		m_StayUI->Draw();

		char aData2[100];

		int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		snprintf(aData2, sizeof(aData2), "タイムボーナス:%d", nSetNum); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);
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

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt*0.01f), aData2);
		}
		else
		{//キーボード入力反映(移動)
			char aData2[100];

			snprintf(aData2, sizeof(aData2), "マウス右クリックで次に"); // 数値を文字列に変換してCDataにコピー

			CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100.0f, SCREEN_HEIGHT / 2.0f + 70.0f, 0.0f), 60, CFont::FONT_DIGITAL, D3DXCOLOR(0.2f, 0.2f, 0.2f, (float)m_nbuttonCnt*0.01f), aData2);
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+ゲーム4シーン
//+


//===================================
// コンストラクタ
//===================================
CGame4::CGame4()
{
}

//===================================
// デストラクタ
//===================================
CGame4::~CGame4()
{
}

//===================================
// 初期化
//===================================
HRESULT CGame4::Init()
{
	CTime::Create();

	CObject3D::Create();//現状床

	CObstacleSet::DataLoad("DATA\\\MAPS\\STAGE1\\model.txt");//ステージ配置物ロード

	CScore::Create();

	CMathProc::LoadRouteCSV("DATA\\MAPS\\STAGE1\\RouteResult.csv");//経路テーブルをロード

	CMathProc::LoadShotPoint("DATA\\MAPS\\STAGE1\\ShotPoint.txt");//射撃地点をロード

	CObjectMotion::DATA SetData = CObject::DataInit();//初期化同時

	//配置物
	//-------------------------------------------------------------------------------------------------------------------
	//左端
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


	//playerが最初！
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化
	SetData.Pos = D3DXVECTOR3(180.0f, 0.0f, 180.0f);
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------

	CObjectMotionPlayer::SetPlayerNum(1);//残基格納

	//enemy
	//-------------------------------------------------------------
	SetData = CObject::DataInit();//初期化

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
// 終了
//===================================
void CGame4::Uninit()
{
	CManager* pManager = CManager::GetInstance();

	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM004);
}

//===================================
// 更新
//===================================
void CGame4::Update()
{
	// マウスカーソルを非表示にする
	int nDrawCnt = ShowCursor(FALSE);

	while (true)
	{
		if (nDrawCnt >= 0)
		{//表示状態のとき
			nDrawCnt = ShowCursor(FALSE);
		}
		else
		{//非表示状態のとき

			if (nDrawCnt < -1)
			{//下がりすぎ防止
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
			{//敵殲滅	
				m_bNext = true;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//制限時間切れ
				m_bNext = false;
				m_bStay2BOOL = true;
			}

			if (CTime::GetTime() <= 0)
			{//制限時間切れ

				pManager->SetEndStatusState(false);
				pManager->SetStayState(true);
			}

			// 配置物プライオリティの先頭を取得
			CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

			if (pObject != nullptr)
			{ // 先頭がない==プライオリティまるっとない

				if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
				{ // 対象のモデルのとき

					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					CObject::DATA EscData;

					// ここで使用分宣言
					CObjectMotionPlayer* pMotionPlayer;

					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					if (pMotionPlayer->GetPlayerNum() < 0)
					{//残機まいなすに

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
					{//次に
						CScore::AddScore(CTime::GetTime() * CScore::TIMEBONUS);

						pManager->SetEndStatusState(true);
						pManager->SetStayState(true);
						CScene::SetStageClear(true);
					}
					else
					{//戻る
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

			//ショイパットの状態を取得
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

			//ショイパットの状態を取得
			DWORD dwResult = XInputGetState(0, &joykeystate);

			//PAUSE起動
			if (pManager->bGetInputState() == true)
			{//操作方法--trueでコントローラー
				if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_A) || keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER1);


					if (pManager->GetEndStatusState() == true)
					{//クリアRoute

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);
					}
					else
					{//敗北

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

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);

					}
					else
					{//敗北

						CFade* pFade = pManager->GetFade();
						pFade->SetFade(CScene::MODE_RESULT);
					}
				}
			}
		}
	}
}

//===================================
// 描画
//===================================
void CGame4::Draw()
{
	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "自機残機：%d", CObjectMotionPlayer::GetPlayerNum()); // 数値を文字列に変換してCDataにコピー
	// mousePos.x と mousePos.y がマウスの位置
	CFont::DrawTextSet(D3DXVECTOR3(50.0f, 10.0f, 0.0f), 40, CFont::FONT_MILITARY, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), cData2);

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	if (pManager->GetPauseState() == true)
	{
		m_Pause->Draw();
	}

	if (pManager->GetStayState() == true)
	{//待機画面
		m_StayUI->Draw();

		char aData2[100];

		int nSetNum = (CTime::GetTime() * CScore::TIMEBONUS);

		snprintf(aData2, sizeof(aData2), "タイムボーナス:%d", nSetNum); // 数値を文字列に変換してCDataにコピー

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 300.0f, SCREEN_HEIGHT / 2.0f + 85.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 0.0, 1.0f, 1.0f), aData2);
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
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//+
//+タイトルシーン
//+


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
	CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
	//-------------------------------------------------------------

	CSound* pSound = pManager->GetSound();
	pSound->PlaySoundA(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//===================================
// 終了
//===================================
void CTitle::Uninit()
{
	CManager* pManager = CManager::GetInstance();
	CSound* pSound = pManager->GetSound();
	pSound->StopSound(CSound::SOUND_LABEL_BGM000);
}

//===================================
// 更新
//===================================
void CTitle::Update()
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
	const char* aData = "Mini-";
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 607.0f, SCREEN_HEIGHT / 2.0f - 308.0f, 0.0f), 193, CFont::FONT_MILITARY, D3DXCOLOR(0.5f, 0.4f, 0.1f, 1.0f), aData);

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f-610.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 215, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

	aData = "Tank!";
	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 107.0f, SCREEN_HEIGHT / 2.0f - 308.0f, 0.0f), 193, CFont::FONT_MILITARY, D3DXCOLOR(0.5f, 0.4f, 0.1f, 1.0f), aData);

	CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 110.0f, SCREEN_HEIGHT / 2.0f - 310.0f, 0.0f), 218, CFont::FONT_GENKAI, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);

	aData = "マウス左クリック/Startボタン/Aボタン";
	
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
//+リザルトシーン
//+


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
	CObject3D::Create();

	if (CScene::GetStageClear() == true)
	{
		//playerが最初！
	//-------------------------------------------------------------
		CObject::DATA SetData = CObject::DataInit();//初期化
		SetData.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CObjectMotionPlayer::Create("DATA\\motion_Tank.txt", SetData);
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
	pSound->StopSound(CSound::SOUND_LABEL_SE_JET);
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
	
	if (m_ScoreNum[0]!= m_NUM)
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

	aData = "マウス左クリック/Startボタン/Aボタン";

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
// Score取得
//=============================
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

//=============================
// スコア書き出し
//=============================
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
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



//+
//+チュートリアルシーン
//+



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