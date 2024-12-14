//============================================================================================
//
//カメラを管理する処理[camera.cpp]
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
#undef min//干渉防止
#undef max
#include <algorithm>

D3DXVECTOR3 CCamera::CameraPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

float CCamera::m_Screen_Width = (float)SCREEN_WIDTH;//スクリーン横幅
float CCamera::m_Screen_Height = (float)SCREEN_HEIGHT;//スクリーン縦幅

//=============================
//コンストラクタ
//=============================
CCamera::CCamera()
{
	// 現在の時間をシード値として設定
	srand(static_cast<unsigned int>(time(0)));

}
//=============================
//デストラクタ
//=============================
CCamera::~CCamera()
{
}
//=============================
//初期化
//=============================
HRESULT CCamera::Init()
{
	m_posV = D3DXVECTOR3(700.0f, 800.0f, 0.0f);//視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//上方向ベクトル
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
//終了
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
//更新
//=============================
void CCamera::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();


	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_TITLE || NowState == CScene::MODE_TUTORIAL)
	{//ゲーム/OP/tutorial

		CManager* pManager = CManager::GetInstance();

		if (pManager->GetbNow3DMode() == false)
		{//2D
			ActionUpdate2D();
		}
		else
		{//3D
			ActionUpdate3D();//ここにロックオン系がはいっている
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

	//	if (m_rot.x > D3DX_PI * 0.25f)//旋回制限
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


	//	//こっから角度								//
	//	m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1コサインシータを欠けた--コサインファイを欠けた
	//	m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Yは普遍のためかくない
	//	m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//１と同じ感じ
	//	//posRは			ここがPosV	ここは+に変更


	////移動量を更新(疑似慣性で減衰)
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
//更新--2D
//=============================
void  CCamera::ActionUpdate2D()
{
	float fLength;

	m_posR = D3DXVECTOR3(0.0f, 25.0f, 0.0f);

	//カメラ距離	
	fLength = 3250.0f * 0.16f;

	//角度による位置調整
	m_rot.x = -0.42f;
	m_rot.y = 0.0f;
	m_rot.z = 0.0f;



	//playerの位置を取得
	CObject* pObj = nullptr;
	pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);

		CObject::DATA EscData;

		EscData = pPlayer->GetClassData();

		m_posR = EscData.Pos;//注視点

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
	{//ゲーム中
	//カメラ距離	

		if (m_CameraType == false)
		{
			m_posR.y += 50.0f;
			fLength = 3250.0f * 0.65f;

			//角度による位置調整
			m_rot.x = 0.0f;
			m_rot.y = 0.0f;
			m_rot.z = 0.0f;


		}
		else
		{
			m_posR.y += 50.0f;
			fLength = 3250.0f * 0.95f;

			//角度による位置調整
			m_rot.x = -1.35f;
			m_rot.y = 0.0f;
			m_rot.z = 0.0f;


		}

	}
	else if (NowState == CScene::MODE_TITLE || NowState == CScene::MODE_RESULT)
	{//タイトル
		m_posR = D3DXVECTOR3(0.0f, 165.0f, 0.0f);

		//カメラ距離	
		fLength = 3250.0f * 0.29f;

		//角度による位置調整
		m_rot.x = -0.42f;
		m_rot.y = 0.0f;
		m_rot.z = 0.0f;
	}





	//こっから角度								//
	m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1コサインシータを欠けた--コサインファイを欠けた
	m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Yは普遍のためかくない
	m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//１と同じ感じ
	//posRは			ここがPosV	ここは+に変更

//	m_posR.z += 150.0f;
	CameraPos = m_posV;
}
//=============================
//更新--3D
//=============================
void  CCamera::ActionUpdate3D()
{
	Input3DCamera();//ココに敵ロックオン周りが入っている

	float fLength;


	//カメラ距離	
	fLength = 500.0f;


	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CScene::MODE NowState = CScene::GetNowScene();

	//playerの位置を取得
	CObject* pObj = nullptr;
	pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	//	D3DXVECTOR3 SETPOS_R=

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);

		CObject::DATA EscData;

		EscData = pPlayer->GetClassData();

//		m_posR = EscData.Pos;//注視点


		if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2)
		{//ゲーム中
		//カメラ距離	

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

			if (m_rot.x > D3DX_PI * 0.25f)//旋回制限
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


			//こっから角度								//
			m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1コサインシータを欠けた--コサインファイを欠けた
			m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Yは普遍のためかくない
			m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//１と同じ感じ
			//posRは			ここがPosV	ここは+に変更


		}
		else if (NowState == CScene::MODE_TITLE || NowState == CScene::MODE_RESULT)
		{//タイトル
			m_posR = D3DXVECTOR3(0.0f, 25.0f, 0.0f);

			//カメラ距離	
			fLength = 3250.0f * 0.16f;

			//角度による位置調整
			m_rot.x = -0.42f;
			m_rot.y = 0.0f;
			m_rot.z = 0.0f;

			//こっから角度								//
			m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1コサインシータを欠けた--コサインファイを欠けた
			m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Yは普遍のためかくない
			m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//１と同じ感じ
			//posRは			ここがPosV	ここは+に変更
		}
		else if (NowState == CScene::MODE_OP)
		{
			//カメラ距離	

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

			if (m_rot.x > D3DX_PI * 0.25f)//旋回制限
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


			//こっから角度								//
			m_posV.x = m_posR.x + fLength * cosf(m_rot.x) * sinf(m_rot.y);//1コサインシータを欠けた--コサインファイを欠けた
			m_posV.y = m_posR.y - fLength * sinf(m_rot.x);						//2Yは普遍のためかくない
			m_posV.z = m_posR.z - fLength * cosf(m_rot.x) * cosf(m_rot.y);//3//１と同じ感じ
			//posRは			ここがPosV	ここは+に変更


		}


		//移動量を更新(疑似慣性で減衰)
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
//３D専用カメラ操作
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

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);

	//中間点までの距離
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//差分を半分に

	//中間点をたしてデッドゾーンと最大点の中間点を算出(通常入力、微入力の判別分岐点)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;


	//-------------------------------------------------------------------------------------------------------------------------
	//右スティック

	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_UP))
	{
		DebuCameraLength+=2;
	}
	else if (JoyPad->GetPress(CInputJoyPad::JOYKEY_DOWN))
	{
		DebuCameraLength-=2;
	}

	bool MoveNowCom2 = false;//入力の有無(コントローラ)

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)
	//	Xdate = 1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Dがおされた(右)
	//	Xdate = -1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Wがおされた(上)
		//Zdate = -1.0f;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Sがおされた(下)
		//Zdate = 1.0f;
		MoveNowCom2 = true;
	}

	int sThumbRX = joykeystate.Gamepad.sThumbRX;
	int sThumbRY = joykeystate.Gamepad.sThumbRY;

	// スティックの入力値からベクトルの大きさを計算
	float magnitude = std::sqrt(static_cast<float>(sThumbRX * sThumbRX) + static_cast<float>(sThumbRY * sThumbRY));

//	float vecX, vecY;

	//if (magnitude > 0)
	//{
	//	// 値を正規化（単位ベクトルを計算）
	//	vecX = sThumbRX / magnitude;
	//	vecY = sThumbRY / magnitude;
	//	// ターゲットの位置を計算
	//	m_TargetPos.x = classData.Pos.x + vecX * 500.0f; // X方向に一定距離進む
	//	m_TargetPos.y = (classData.Pos.y + 150.0f) + vecY * 500.0f; // Y方向に一定距離進む
	//	m_TargetPos.z = 0;

	//}
	//else
	//{
	//	// スティックが中央の場合はベクトルを0に
	//	vecX = 0.0f;
	//	vecY = 0.0f;
	//}

	float MoveSpeed2 = 3.0f;

	if (MoveNowCom2 == false)
	{
	
	}
	else
	{//デッドゾーン超えた
		//Controller移動

		m_rotMove.y -= (joykeystate.Gamepad.sThumbRX * JoyStickDiffCamera);
		m_rotMove.x += (joykeystate.Gamepad.sThumbRY * JoyStickDiffCamera);
	}
	//-------------------------------------------------------------------------------------------------------------------------


	LockOnEnemy();//LOCK ON処理
}
//=============================
//カメラ設定
//=============================
void CCamera::SetCamera()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();


	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),//視野角
		(float)m_Screen_Width / (float)m_Screen_Height,//画面のアスペクト比
		10.0f,//ｚ軸最小値
		59000.0f);//z軸最大値

	//プロジェクションマトリックスの設定
	EscDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
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

	//ビューマトリックスの設定
	EscDevice->SetTransform(D3DTS_VIEW, &m_mtxView);


	
}
//=============================
//カメラ揺れ
//=============================
void CCamera::SetShake(int ShakeFlame, float Magnitude)
{
	m_fMag = Magnitude;
	m_nShakeFlame = ShakeFlame;
}
//=============================
//スクリーンサイズ格納
//=============================
void CCamera::SetScreenSize(float screenWidth, float screenHeight)
{
	m_Screen_Width = (float)screenWidth;
	m_Screen_Height = (float)screenHeight;
}
//=============================
//スクリーンザイズ取得
//=============================
D3DXVECTOR2 CCamera::GetScreenSize()
{
	return D3DXVECTOR2((float)m_Screen_Width, (float)m_Screen_Height);
}
//=============================
//角度取得
//=============================
D3DXVECTOR3 CCamera::GetRot()
{
	return m_rot;
}

//=============================
// ロックオン処理
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
		float distanceSquared; // 2D距離^2
		int enemyType;
	};

	std::vector<LockOnTarget> potentialTargets;

	// プレイヤーの位置を取得
	CObject* pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);
	CObject::DATA PlayerEscData;

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);
		PlayerEscData = pPlayer->GetClassData();
		PlayerEscData.Pos.y += 130.0f;
	}

	// 敵のスクリーン座標を更新
	SetAllEnemyScreenPos();

	// 高速タイプ敵を処理
	CObject* pObjectFast = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_FAST);

	if (pObjectFast != nullptr)
	{
		while (pObjectFast != nullptr)
		{
			CObjectMotionEnemyfast* pEnemyFast = (CObjectMotionEnemyfast*)pObjectFast;
			CObject::DATA EscEnemyData = pEnemyFast->GetClassData();
			EscEnemyData.Pos.y += 50.0f;
			//リセット
			pEnemyFast->GetLockOnUI()->SetDrawOk(false);
			pEnemyFast->GetLockOnUIMain()->SetDrawOk(false);


			if (IsInScreen(pEnemyFast->GetScreenPos()) && IsFacingCamera(EscEnemyData.Pos))
			{
				// カメラと敵の距離を計算
				D3DXVECTOR3 cameraToEnemy = pEnemyFast->GetClassData().Pos - m_posV;
				float distance = D3DXVec3Length(&cameraToEnemy);//対象との距離

				if (distance < LOCKMISSLEDDISTANCE)
				{//ミサイル範囲
						// 2D距離計算
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

	// 通常タイプ敵を処理
	CObject* pObjectNormal = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_NOMAL);

	if (pObjectNormal != nullptr)
	{
		while (pObjectNormal != nullptr)
		{
			CObjectMotionEnemyNomal* pEnemyNomal = (CObjectMotionEnemyNomal*)pObjectNormal;
			CObject::DATA EscEnemyData = pEnemyNomal->GetClassData();
			EscEnemyData.Pos.y += 50.0f;

			//リセット
			pEnemyNomal->GetLockOnUI()->SetDrawOk(false);
			pEnemyNomal->GetLockOnUIMain()->SetDrawOk(false);


			if (IsInScreen(pEnemyNomal->GetScreenPos()) && IsFacingCamera(EscEnemyData.Pos))
			{
				// カメラと敵の距離を計算
				D3DXVECTOR3 cameraToEnemy = pEnemyNomal->GetClassData().Pos - m_posV;
				float distance = D3DXVec3Length(&cameraToEnemy);//対象との距離

				if (distance < LOCKMISSLEDDISTANCE)
				{//ミサイル範囲
					
					// 2D距離計算
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

	// 距離順にソート
	std::sort(potentialTargets.begin(), potentialTargets.end(), [](const LockOnTarget& a, const LockOnTarget& b) {
		return a.distanceSquared < b.distanceSquared;
		});

	// 8体のロックオン対象を選定
	int lockOnCount = std::min(8, static_cast<int>(potentialTargets.size()));
	for (int i = 0; i < lockOnCount; ++i)
	{
		CObject* pEnemy = potentialTargets[i].pEnemy;
		if (potentialTargets[i].enemyType == 0)
		{
			auto* pEnemyFast = static_cast<CObjectMotionEnemyfast*>(pEnemy);
			if (pEnemyFast)
			{
				//ミサイルロック
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
				//ミサイルロック
				pEnemyNomal->GetLockOnUI()->SetDrawOk(true);

				CObject::DATA SETDATA = CObject::DataInit();
				SETDATA.Pos = pEnemyNomal->GetClassData().Pos;
				SETDATA.Pos.y += 40.0f;
				pEnemyNomal->GetLockOnUI()->SetDATA(SETDATA);

			}
		}
	}

	// 一番中心に近い敵をバレットロックオン
	if (lockOnCount > 0)
	{
		CObject* pEnemy = potentialTargets[0].pEnemy;
		if (potentialTargets[0].enemyType == 0)
		{
			auto* pClosestEnemyFast = static_cast<CObjectMotionEnemyfast*>(pEnemy);
			//ミサイルロック
			pClosestEnemyFast->GetLockOnUIMain()->SetDrawOk(true);

			CObject::DATA SETDATA = CObject::DataInit();
			SETDATA.Pos = pClosestEnemyFast->GetClassData().Pos;
			SETDATA.Pos.y += 40.0f;
			pClosestEnemyFast->GetLockOnUIMain()->SetDATA(SETDATA);

		}
		else if (potentialTargets[0].enemyType == 1)
		{
			auto* pClosestEnemyNomal = static_cast<CObjectMotionEnemyNomal*>(pEnemy);
			//ミサイルロック
			pClosestEnemyNomal->GetLockOnUIMain()->SetDrawOk(true);

			CObject::DATA SETDATA = CObject::DataInit();
			SETDATA.Pos = pClosestEnemyNomal->GetClassData().Pos;
			SETDATA.Pos.y += 40.0f;
			pClosestEnemyNomal->GetLockOnUIMain()->SetDATA(SETDATA);

		}
	}
}





//=============================
// 全敵スクリーン座標変換セット
//=============================
void CCamera::SetAllEnemyScreenPos()
{
	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	pRenderer = pManager->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ビュー行列と射影行列の設定
	D3DXMATRIX viewMatrix, projectionMatrix;

	// カメラの位置、注視点、上方向を考慮してビュー行列を設定
	D3DXVECTOR3 cameraPosition = m_posV;
	D3DXVECTOR3 cameraLookAt = m_posR;
	D3DXVECTOR3 cameraUp(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&viewMatrix, &cameraPosition, &cameraLookAt, &cameraUp);

	D3DXMatrixPerspectiveFovLH(&projectionMatrix,
		D3DXToRadian(45.0f), // 視野角
		(float)m_Screen_Width / (float)m_Screen_Height, // アスペクト比
		10.0f, // Z軸最小値
		59000.0f // Z軸最大値
	);

	// ビューポートの設定
	D3DVIEWPORT9 viewport;
	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = (DWORD)m_Screen_Width;
	viewport.Height = (DWORD)m_Screen_Height;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;

	// 高速敵のスクリーン座標変換
	CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_FAST);

	while (pObject != nullptr)
	{
		CObjectMotionEnemyfast* pEnemyFast = (CObjectMotionEnemyfast*)pObject;
		CObject::DATA EscEnemyData = pEnemyFast->GetClassData();

		D3DXVECTOR3 worldPos = EscEnemyData.Pos;
		D3DXVECTOR3 screenPos;

		// ワールド座標からスクリーン座標への変換
		D3DXVec3Project(&screenPos, &worldPos, &viewport, &projectionMatrix, &viewMatrix, nullptr);

		pEnemyFast->SetSCREENPOS(screenPos);

		pObject = pObject->GetNext();
	}

	// 通常敵のスクリーン座標変換
	pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONENEMY_NOMAL);

	while (pObject != nullptr)
	{
		CObjectMotionEnemyNomal* pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;
		CObject::DATA EscEnemyData = pEnemyNomal->GetClassData();

		D3DXVECTOR3 worldPos = EscEnemyData.Pos;
		D3DXVECTOR3 screenPos;

		// ワールド座標からスクリーン座標への変換
		D3DXVec3Project(&screenPos, &worldPos, &viewport, &projectionMatrix, &viewMatrix, nullptr);

		pEnemyNomal->SetSCREENPOS(screenPos);

		pObject = pObject->GetNext();
	}
}

//=============================
// カメラが対象の方を向いているかどうかを判定
//=============================
bool CCamera::IsFacingCamera(D3DXVECTOR3 enemyPosition)
{
	//カメラ取得
	D3DXVECTOR3 cameraPosition = m_posV;
	D3DXVECTOR3 cameraLookAt = m_posR;

	D3DXVECTOR3 toEnemy = enemyPosition - cameraPosition;
	D3DXVec3Normalize(&toEnemy, &toEnemy);//カメラ位置と敵位置のベクトル算出

	D3DXVECTOR3 cameraForward;
	D3DXVECTOR3 diffVector = cameraLookAt - cameraPosition;//カメラの見ているベクトル算出
	D3DXVec3Normalize(&cameraForward, &diffVector);

	// カメラの前方ベクトルと敵へのベクトルがほぼ同じ方向を向いているかどうかを判定
	float dotProduct = D3DXVec3Dot(&toEnemy, &cameraForward);
	return (dotProduct > 0.5f); //誤差範囲以内で返す
}
//=============================
// スクリーン座標が画面内にあるかどうかを判定
//=============================
bool CCamera::IsInScreen(D3DXVECTOR3 screenPosition)
{
	return (screenPosition.x >= 0 && screenPosition.x <= SCREEN_WIDTH &&
		screenPosition.y >= 0 && screenPosition.y <= SCREEN_HEIGHT &&
		screenPosition.z >= 0 && screenPosition.z <= 1);
}

//=============================
// RAYが交差してるか
//=============================
bool CCamera::IntersectRayAABB(
	const D3DXVECTOR3& rayStart,
	const D3DXVECTOR3& rayDir,
	const D3DXVECTOR3& boxMin,
	const D3DXVECTOR3& boxMax,
	float& tMin,
	float& tMax)
{
	tMin = 0.0f;           // レイの始点のパラメータ
	tMax = FLT_MAX;        // レイの終点のパラメータ

	for (int i = 0; i < 3; ++i) { // X, Y, Z 方向それぞれでチェック
		if (rayDir[i] != 0.0f) {
			float t1 = (boxMin[i] - rayStart[i]) / rayDir[i];
			float t2 = (boxMax[i] - rayStart[i]) / rayDir[i];

			if (t1 > t2) std::swap(t1, t2);

			tMin = std::max(tMin, t1);
			tMax = std::min(tMax, t2);

			if (tMin > tMax) {
				return false; // レイがAABBと交差していない
			}
		}
		else if (rayStart[i] < boxMin[i] || rayStart[i] > boxMax[i]) {
			return false; // レイがAABBの範囲外
		}
	}

	return true; // レイがAABBと交差
}