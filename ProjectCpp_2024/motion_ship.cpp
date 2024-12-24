//=========================================================
//
// player_motion[player_motion.cpp]
// Author seiya kagaya
//
//=========================================================
#include "motion_ship.h"
#include "renderer.h"
#include "manager.h"
//#include "ballet3D.h"
#include "tankfootprint.h"
//#include "ShotFire.h"
#include "score.h"
//#include "target_UI.h"
//#include "linerinterUI.h"
#include "Explosion3D.h"
#include "ShotFire.h"
#include "movesmoke.h"
#include "3D-2DhitObject.h"
#include "linerinterUI.h"
#include "linerinterUI.h"
#include "shield.h"
#include "enemy_motion_Nomal.h"
#include "enemy_motion_fast.h"
#include "missile.h"
//#include "movesmoke.h"

int CObjectShip::m_nNumPlayerAll = START_PLAYER_NUM;//初期値３




//=============================
// コンストラクタ
//=============================
CObjectShip::CObjectShip(int nPriority) :CObjectMotion(nPriority)
{
}

//=============================
// デストラクタ
//=============================
CObjectShip::~CObjectShip()
{
	m_nNumPlayerAll--;
}

//=============================
// 初期化
//=============================
HRESULT CObjectShip::Init()
{
	CObjectMotion::Init();


	SetObjectType(CObject::OBJECT_MOTIONB2);

	float fLength[3];
	fLength[0] = 70.0f;
	fLength[1] = 140.0f;
	fLength[2] = 60.0f;

	//	m_nMoveCnt = 0;

	SetOBBLength(fLength);//OBB長さ格納


	DATA classData = GetClassData();

	//	classData.Pos = m_RESTART_POS;

	SetClassData(classData);

	//	m_nLife = START_LIFE;
		//m_bDown = false;
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	keyboard->GetMouseRayIntersection(*pManager->GetCamera());//マウス位置

//	m_TargetPos = keyboard->GetScreenPosRayIntersection(*pManager->GetCamera(), D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));//マウス位置
//	m_TargetPos = D3DXVECTOR3(-4000.0f, 3200.0f, 0.0f);

	CScene::MODE NowState = CScene::GetNowScene();



	//	SetSizeMag(D3DXVECTOR3(3.0f, 3.0f, 3.0f));//大きさ倍率

	return S_OK;
}

//=============================
// 破棄
//=============================
void CObjectShip::Uninit()
{
	CObjectMotion::Uninit();
}

//=============================
// 更新
//=============================
void CObjectShip::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();

	if (NowState == CScene::MODE_MOVIE2)
	{
		m_nCntFrame++;

		DATA classData = GetClassData();
		//classData.rot.x = -1.57f;
		classData.move.z = -7.0f;

		if (m_nCntFrame >= 300 && m_nCntFrame < 450)
		{
			//  SetNowMotion_Parent(MOTIONTYPE_OP1);
			//	SetNowMotion_Sub();
		}

		if (m_nCntFrame == 450)
		{
//			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 3, "....!!\n12時よりアクティブソナー！\n魚雷接近！回避！", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);
		}

		if (m_nCntFrame == 650)
		{//爆発
			Explosion3D::Create(D3DXVECTOR3(classData.Pos.x, classData.Pos.y, classData.Pos.z));
		}

		if (m_nCntFrame > 650 && m_nCntFrame < 1250)
		{//
			classData.move.y = -1.0f;
			classData.move.z = -0.2f;

			SetNowMotion_Parent(MOTIONTYPE_OP1);
			SetNowMotion_Sub(MOTIONTYPE_OP1);
		}

		if (m_nCntFrame == 800)
		{
//			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 2, "クソッ............総員退艦！\n.........................\n...............", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);
		}

		

		SetClassData(classData);


		//DATA Head;
		//Head = CObject::DataInit();
		////Head.rot.x = 1.57f;

		////基底クラスからパーツにデータを受け渡し
		//SetChangeDataInObjectMotion(Head);



		CObjectMotion::Update();//------------------更新
	}
}

//=============================
// 描画
//=============================
void CObjectShip::Draw()
{
	CObjectMotion::Draw();
}

//=============================
// 生成
//=============================
CObjectShip* CObjectShip::Create(std::string pfilePass, DATA SetData)
{
	CObjectShip* pObstacle = new CObjectShip;

	pObstacle->SetFilePass(pfilePass);//パス格納
//	pObstacle->SetStartPos(SetData.Pos);
	pObstacle->Init();

	// 取得
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)AABB_BOX_PLAYER, (float)AABB_BOX_PLAYER * 3.0f, (float)AABB_BOX_PLAYER);
	SetData.MinLength = D3DXVECTOR3(-(float)AABB_BOX_PLAYER, +35.0f, -(float)AABB_BOX_PLAYER);
	pObstacle->SetClassData(SetData);


	return pObstacle;
}
