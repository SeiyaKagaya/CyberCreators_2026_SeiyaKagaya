//=========================================================
//
// enemy_motion_Nomal�̓���[enemy_motion_Nomal.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy_motion_boss.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"
//#include "ballet3D.h"
#include "line.h"
//#include "tankfootprint.h"
//#include "ShotFire.h"
#include "score.h"
#include "Explosion3D.h"
#include "newbullet.h"
#include "ShotFire.h"
#include "missile.h"
#include "enemy_motion_guard.h"
#include "enemy_motion_Nomal.h"
//#include "movesmoke.h"

int CObjectMotionEnemyBoss::m_nNumENemyAll = 0;

//=============================
// �R���X�g���N�^
//=============================
CObjectMotionEnemyBoss::CObjectMotionEnemyBoss(int nPriority) :CObjectMotionEnemyBase(nPriority)
{
	m_nNumENemyAll++;
}
//=============================
// �f�X�g���N�^
//=============================
CObjectMotionEnemyBoss::~CObjectMotionEnemyBoss()
{
	m_nNumENemyAll--;
}

//=============================
// ������
//=============================
HRESULT CObjectMotionEnemyBoss::Init()
{
	CObjectMotion::Init();
	SetObjectType(CObject::OBJECT_MOTIONENEMY_BOSS);

	float fLength[3];
	fLength[0] = 300.0f;
	fLength[1] = 200.0f;
	fLength[2] = 1300.0f;

	SetOBBLength(fLength);//OBB�����i�[

	m_nMoveCnt = 0;
	fRotTurret = 0.0f;
	m_nBulletDelay = BULLETSHOTDELAY;

	m_LockOnUI = CLockOnUI::Create();
	m_LockOnUI_Main = CLockOnUIMain::Create();

	DATA setdata = DataInit();
	m_pShield = CShield::Create(setdata,true);

	return S_OK;
}

//=============================
// �j��
//=============================
void CObjectMotionEnemyBoss::Uninit()
{
	CScene::AddClearNum(1);

	m_LockOnUI->SetDeath(true);
	m_LockOnUI_Main->SetDeath(true);

	CObjectMotion::Uninit();
}

//=============================
// �X�V
//=============================
void CObjectMotionEnemyBoss::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();

	if (CScene::GetStayNextStage() == false)
	{//�ҋ@��Ԃ�

		if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3)
		{
			for (int i = 0; i < GetMaxLoadPartsNum(); i++)
			{
				GetModelParts(i)->ChengeRGBAbool(true, D3DXCOLOR(0.3f, 0.3f, 0.0f, 1.0f));
			}

			CRenderer* pRenderer = nullptr;

			CManager* pManager = CManager::GetInstance();


			CObjectMotion::Update();//----------------



			DATA classData = GetClassData();

			classData.move.x = 0.0f;
			classData.move.y = 0.0f;
			classData.move.z = 8.8f;

			m_nEnemyCreateCnt++;
			if (m_nEnemyCreateCnt > EMNEMY_DROPCOUNT)
			{
				m_nEnemyCreateCnt = 0;
				CObjectMotionEnemyNomal::Create("DATA\\motion_hellcpter.txt", GetClassData());
			}


			//------------------------------------------------------------------------------------------------------------------------------------------------------
			

			DATA SetData = DataInit();
			SetData.Pos = GetClassData().Pos;
			SetData.Pos.y += LOCKDIFF;

			m_LockOnUI_Main->SetDATA(SetData);
			m_LockOnUI->SetDATA(SetData);

			D3DXVECTOR3 ESCDATA = D3DXVECTOR3(classData.Pos.x, classData.Pos.y + 150.0f, classData.Pos.z);

			m_pShield->SetPos(ESCDATA);

			if (CObjectMotionEnemyGuard::GetEnemyAllNum() > 0)
			{
				m_pShield->setDrawOk(true);
			}
			else
			{
				m_pShield->setDrawOk(false);
			}


			if (m_nLife <= 0)
			{
				SetNowMotion_Parent(MOTIONTYPE_OP0);
				SetNowMotion_Sub(MOTIONTYPE_OP0);
				//CObjectMotion::Update();
				//Motion_Parent();
				//Motion_Sub();
				classData = GetClassData();

				classData.move.y = -1;
				SetClassData(classData);


				m_nEscCnt--;
				if (m_nEscCnt < 0)
				{
					CScore::AddScore(CScore::TANK_SCORE1 * 4);

					CObject* pObj = nullptr;
					pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MISSILE_MNG, CObject::OBJECT_MISSILE_MNG);
					if (pObj != nullptr)
					{
						CMissileALL* pMissile = static_cast<CMissileALL*>(pObj);
						if (pMissile != nullptr)
						{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�
							pMissile->KillMissileTarget(this);
						}

					}

					CScore::AddScore(CScore::TANK_SCORE1);

					SetDeath(true);

					Explosion3D::Create(GetClassData().Pos);
					for (int i = 0; i < GetMaxLoadPartsNum(); i++)
					{//�p�[�c��DEATH
						GetModelParts(i)->SetDeath(true);
					}
				}
			}




			SetClassData(classData);

			if (m_nDamageFrameCnt > 0)
			{
				m_nDamageFrameCnt--;
				for (int i = 0; i < GetMaxLoadPartsNum(); i++)
				{//

					GetModelParts(i)->ChengeRGBAbool(true, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				}

			}
			else
			{
				for (int i = 0; i < GetMaxLoadPartsNum(); i++)
				{//
					GetModelParts(i)->ChengeRGBAbool(false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}
		else if (NowState == CScene::MODE_MOVIE2)
		{
			DATA ChangeData = DataInit();

			// �ύX�f�[�^�𔽉f
			SetChangeDataInObjectMotion(ChangeData);


			CObjectMotion::Update();//------------------�X�V

			m_nMovieCnt++;

			if (m_nMovieCnt > 1200)
			{
				m_pShield->setDrawOk(true);
			}
			//SetNowMotion_Parent(MOTIONTYPE_STANDBY);
			//SetNowMotion_Sub(MOTIONTYPE_STANDBY);
		}
	}
	else
	{//�ҋ@���
		DATA ChangeData = DataInit();

		// �ύX�f�[�^�𔽉f
		SetChangeDataInObjectMotion(ChangeData);

		SetNowMotion_Parent(MOTIONTYPE_STANDBY);
		SetNowMotion_Sub(MOTIONTYPE_STANDBY);
		//CObjectMotion::Update();
		Motion_Parent();
		Motion_Sub();


	}
	




}

//=============================
// �`��
//=============================
void CObjectMotionEnemyBoss::Draw()
{
	CObjectMotion::Draw();
	m_pShield->Draw();
}

//=============================
// ����
//=============================
CObjectMotionEnemyBoss* CObjectMotionEnemyBoss::Create(std::string pfilePass, DATA SetData)
{
	CObjectMotionEnemyBoss* pObstacle = new CObjectMotionEnemyBoss;

	pObstacle->SetFilePass(pfilePass);//�p�X�i�[

	pObstacle->Init();
	// �擾
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)(CObjectMotionEnemyBase::AABB_BOX), (float)(CObjectMotionEnemyBase::AABB_BOX) * 2.0f, (float)(CObjectMotionEnemyBase::AABB_BOX));
	SetData.MinLength = D3DXVECTOR3(-(float)(CObjectMotionEnemyBase::AABB_BOX), 0.0f, -(float)(CObjectMotionEnemyBase::AABB_BOX));
	pObstacle->SetClassData(SetData);


	return pObstacle;
}