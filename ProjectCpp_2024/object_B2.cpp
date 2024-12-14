//=========================================================
//
// player_motion[player_motion.cpp]
// Author seiya kagaya
//
//=========================================================
#include "object_B2.h"
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

int CObjectB2::m_nNumPlayerAll = START_PLAYER_NUM;//�����l�R

//=============================
// �R���X�g���N�^
//=============================
CObjectB2::CObjectB2(int nPriority) :CObjectMotion(nPriority)
{
}

//=============================
// �f�X�g���N�^
//=============================
CObjectB2::~CObjectB2()
{
	m_nNumPlayerAll--;
}

//=============================
// ������
//=============================
HRESULT CObjectB2::Init()
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
void CObjectB2::Uninit()
{
	CObjectMotion::Uninit();
}

//=============================
// �X�V
//=============================
void CObjectB2::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();

	if (NowState == CScene::MODE_OP)
	{//�^�C�g��

		m_nCntFrame++;

		DATA classData = GetClassData();





	//	classData.rot.x = -1.57f;

		SetClassData(classData);

		DATA Head;
		Head = CObject::DataInit();
		//Head.rot.x = 1.57f;

		//���N���X����p�[�c�Ƀf�[�^���󂯓n��
		SetChangeDataInObjectMotion(Head);

	

		if (m_nCntFrame == 300/*&& m_nCntFrame<360*/)
		{
			SetNowMotion_Parent(MOTIONTYPE_OP1);
			//	SetNowMotion_Sub(MOTIONTYPE_HIGH_MOVE_FRONT);
		}
		else if (m_nCntFrame >= 420 && m_nCntFrame<700)
		{
			SetNowMotion_Parent(MOTIONTYPE_OP2);
			//	SetNowMotion_Parent((MOTIONTYPE)2);
			//	SetNowMotion_Sub(MOTIONTYPE_HIGH_MOVE_FRONT);
		}
		else if (m_nCntFrame >= 701 && m_nCntFrame < 820)
		{
			SetNowMotion_Parent(MOTIONTYPE_OP3);
			//	SetNowMotion_Parent((MOTIONTYPE)2);
			//	SetNowMotion_Sub(MOTIONTYPE_HIGH_MOVE_FRONT);
		}

	CObjectMotion::Update();//------------------�X�V
	}

}

//=============================
// �`��
//=============================
void CObjectB2::Draw()
{
	CObjectMotion::Draw();
}

//=============================
// ����
//=============================
CObjectB2* CObjectB2::Create(const char* pfilePass, DATA SetData)
{
	CObjectB2* pObstacle = new CObjectB2;

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
