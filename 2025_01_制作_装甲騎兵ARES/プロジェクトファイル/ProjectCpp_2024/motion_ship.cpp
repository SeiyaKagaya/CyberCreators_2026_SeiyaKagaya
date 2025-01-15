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

int CObjectShip::m_nNumPlayerAll = START_PLAYER_NUM;//�����l�R




//=============================
// �R���X�g���N�^
//=============================
CObjectShip::CObjectShip(int nPriority) :CObjectMotion(nPriority)
{
}

//=============================
// �f�X�g���N�^
//=============================
CObjectShip::~CObjectShip()
{
	m_nNumPlayerAll--;
}

//=============================
// ������
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

	SetOBBLength(fLength);//OBB�����i�[


	DATA classData = GetClassData();

	//	classData.Pos = m_RESTART_POS;

	SetClassData(classData);

	//	m_nLife = START_LIFE;
		//m_bDown = false;
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	keyboard->GetMouseRayIntersection(*pManager->GetCamera());//�}�E�X�ʒu

//	m_TargetPos = keyboard->GetScreenPosRayIntersection(*pManager->GetCamera(), D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));//�}�E�X�ʒu
//	m_TargetPos = D3DXVECTOR3(-4000.0f, 3200.0f, 0.0f);

	CScene::MODE NowState = CScene::GetNowScene();



	//	SetSizeMag(D3DXVECTOR3(3.0f, 3.0f, 3.0f));//�傫���{��

	return S_OK;
}

//=============================
// �j��
//=============================
void CObjectShip::Uninit()
{
	CObjectMotion::Uninit();
}

//=============================
// �X�V
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
//			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 20, 3, "....!!\n12�����A�N�e�B�u�\�i�[�I\n�����ڋ߁I����I", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);
		}

		if (m_nCntFrame == 650)
		{//����
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
//			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 2, "�N�\�b............�����ފ́I\n.........................\n...............", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);
		}

		

		SetClassData(classData);


		//DATA Head;
		//Head = CObject::DataInit();
		////Head.rot.x = 1.57f;

		////���N���X����p�[�c�Ƀf�[�^���󂯓n��
		//SetChangeDataInObjectMotion(Head);



		CObjectMotion::Update();//------------------�X�V
	}
}

//=============================
// �`��
//=============================
void CObjectShip::Draw()
{
	CObjectMotion::Draw();
}

//=============================
// ����
//=============================
CObjectShip* CObjectShip::Create(std::string pfilePass, DATA SetData)
{
	CObjectShip* pObstacle = new CObjectShip;

	pObstacle->SetFilePass(pfilePass);//�p�X�i�[
//	pObstacle->SetStartPos(SetData.Pos);
	pObstacle->Init();

	// �擾
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)AABB_BOX_PLAYER, (float)AABB_BOX_PLAYER * 3.0f, (float)AABB_BOX_PLAYER);
	SetData.MinLength = D3DXVECTOR3(-(float)AABB_BOX_PLAYER, +35.0f, -(float)AABB_BOX_PLAYER);
	pObstacle->SetClassData(SetData);


	return pObstacle;
}
