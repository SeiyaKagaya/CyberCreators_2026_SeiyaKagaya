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

	return S_OK;
}
//=============================
//終了
//=============================
void CCamera::Uninit()
{
}
//=============================
//更新
//=============================
void CCamera::Update()
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



	//for (int nPriority = 0; nPriority < CObject::LAYERINDEX_MAX; nPriority++)
	//{
	//	for (int nCnt = 0; nCnt < CObject::GetnNumAll(); nCnt++)
	//	{//全object周回

	////		CObject* pObject = CObject::GetObjectData(nCnt, (CObject::LAYERINDEX)nPriority);//オブジェクトデータ取得

	//		if (pObject != nullptr)
	//		{
	//			CObject::OBJECTTYPE type = pObject->GetObjectType();//タイプ取得

	//			if (type == CObject::OBJECT_MOTIONPLAYER)
	//			{//探しているplayerと一致

	//				CObject::DATA EscData;

	//				/*	CPlayer3D* pPlayer = static_cast<CPlayer3D*>(pObject);

	//					EscData = pPlayer->GetDATA();*/
	//				CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObject);


	//				EscData = pPlayer->GetClassData();


	//				m_posR = D3DXVECTOR3(EscData.Pos.x, EscData.Pos.y, EscData.Pos.z);//注視点
	//				break;
	//			}
	//		}
	//	}
	//}

//	m_posR = D3DXVECTOR3(0.0f,0.0f,0.0f);//注視点


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
	else if (NowState == CScene::MODE_TITLE|| NowState == CScene::MODE_RESULT)
	{//タイトル
		m_posR = D3DXVECTOR3(0.0f, 25.0f, 0.0f);

		//カメラ距離	
		fLength = 3250.0f*0.16f;

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
		9000.0f);//z軸最大値

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
