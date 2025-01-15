//=========================================================
//
// enemy_motion_Nomal�̓���[enemy_motion_Nomal.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy_motion_guard.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"
//#include "ballet3D.h"
#include "line.h"
#include "tankfootprint.h"
//#include "ShotFire.h"
#include "score.h"
#include "Explosion3D.h"
#include "newbullet.h"
#include "ShotFire.h"
#include "missile.h"
//#include "movesmoke.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectMotionEnemyGuard::CObjectMotionEnemyGuard(int nPriority) :CObjectMotionEnemyBase(nPriority)
{
}
//=============================
// �f�X�g���N�^
//=============================
CObjectMotionEnemyGuard::~CObjectMotionEnemyGuard()
{
}

//=============================
// ������
//=============================
HRESULT CObjectMotionEnemyGuard::Init()
{
	CObjectMotion::Init();
	SetObjectType(CObject::OBJECT_MOTIONENEMY_BOSS_GUARD);

	//	LoadRouteTable();

	m_nLife = 1000;

	float fLength[3];
	fLength[0] = 200.0f;
	fLength[1] = 200.0f;
	fLength[2] = 1100.0f;

	SetOBBLength(fLength);//OBB�����i�[

	m_nMoveCnt = 0;
	m_fRotTurret = 0.0f;
	m_nBulletDelay = BULLETSHOTDELAY;

	m_LockOnUI = CLockOnUI::Create();
	m_LockOnUI_Main = CLockOnUIMain::Create();
	return S_OK;
}

//=============================
// �j��
//=============================
void CObjectMotionEnemyGuard::Uninit()
{
	CScene::AddClearNum(1);

	m_LockOnUI->SetDeath(true);
	m_LockOnUI_Main->SetDeath(true);

	CObjectMotion::Uninit();
}

//=============================
// �X�V
//=============================
void CObjectMotionEnemyGuard::Update()
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

	
			//����A������GRID�ԍ������������
			bool bChange = false;

			//�Ƃ肠����player �̕����ɖC����������
			//----------------------------------------------------------------------------------
			//player�̈ʒu���擾
			CObject* pObj = nullptr;
			pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

			D3DXVECTOR3 TargetPos = {};

			if (pObj != nullptr)
			{
				CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);

				CObject::DATA EscData;

				EscData = pPlayer->GetClassData();

				TargetPos = EscData.Pos;//�����_

				if (m_nOldTargetGRIDNum != pPlayer->GetNowGRIDNum())
				{//�ߋ��̑���ʒu�ԍ��Ƃ��܂̑���ʒu�ԍ����ꏏ����Ȃ���
					//�i�[
					m_nOldTargetGRIDNum = pPlayer->GetNowGRIDNum();
					bChange = true;
				}
			}


			////�ړ��搧�肱���܂�
			////---------------------------------------------------------------------------------------------------------------------------------
			//// �^�[�Q�b�g�ʒu�ւ̈ړ�����
			//D3DXVECTOR3 direction = m_TargetPos - classData.Pos; // �����x�N�g��

			//float distance = D3DXVec3Length(&direction); // �^�[�Q�b�g�܂ł̋���

			//if (distance > 1.0f) // �߂����Ȃ��ꍇ�ɂ݈̂ړ�
			//{
			//	D3DXVec3Normalize(&direction, &direction); // �����x�N�g���̐��K��

			//	float MoveSpeed = MOVESPEED;//�ړ����x

			//	// �ړ�
			//	classData.move.x = direction.x * MoveSpeed;
			//	classData.move.z = direction.z * MoveSpeed;


			//	// �ڕW�����̌v�Z
			//	float targetAngle = atan2f(direction.x, direction.z);

			//	//�p�x�ϓ�
			//	classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, targetAngle + D3DX_PI);

			//	m_nMoveCnt++;

			//	if (m_nMoveCnt >= CObjectFootPrint::STANPFLAME)
			//	{
			//		m_nMoveCnt = 0;
			//		//CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z), classData.rot);
			////		CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z));
			//	}
			//}
			//else
			//{
			//	// �^�[�Q�b�g�ʒu�ɋ߂�����ꍇ�͈ړ����~
			//	classData.move.x = 0.0f;
			//	classData.move.z = 0.0f;
			//}
			////------------------------------------------------------------------------------------------------------------------




			//�Փˑ��E--�G��

			CMathProc::CollisionData HitData = CMathProc::CheckCircleCollision_Cancel(classData.Pos, classData.Radius, CObject::OBJECT_MOTIONENEMY_NOMAL, LAYERINDEX_MOTIONENEMY_NOMAL, this);

			if (HitData.bHit == true)
			{
				classData.Pos += HitData.ResultDistance;
				HitData.bHit = false;
			}

			HitData = CMathProc::CheckCircleCollision_Cancel(classData.Pos, classData.Radius, CObject::OBJECT_MOTIONENEMY_FAST, LAYERINDEX_MOTIONENEMY_FAST, this);

			if (HitData.bHit == true)
			{
				classData.Pos += HitData.ResultDistance;
				HitData.bHit = false;
			}


			SetClassData(classData);

			//�����蔻��v�Z
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

			//�����蔻��v�Z
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);

			//	classData.rot.y = 0.0f;

			classData.move.x = 0.0f;
			classData.move.y = 0.0f;
			classData.move.z = 2.0f;


			classData = GetClassData();



			//�G�ˌ��ǐ�
			//-------------------------------------------------------------------------------------------------------------------------------------------------------

			Attack();


			DATA SetData = DataInit();
			SetData.Pos = GetClassData().Pos;
			SetData.Pos.y += LOCKDIFF;

			m_LockOnUI_Main->SetDATA(SetData);
			m_LockOnUI->SetDATA(SetData);






			//------------------------------------------------------------------------------------------------------------------------------------------------------



			if (m_nLife <= 0)
			{
			//	CScene::AddClearNum(1);

				SetNowMotion_Parent(MOTIONTYPE_STANDBY);
				SetNowMotion_Sub(MOTIONTYPE_STANDBY);
				//CObjectMotion::Update();
				//Motion_Parent();
				//Motion_Sub();
				classData = GetClassData();

				classData.move.y = -1;
				SetClassData(classData);

				m_nEscCnt--;

				if (m_nEscCnt < 0)
				{
					CScore::AddScore(CScore::TANK_SCORE1*3);
					
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
		else if (NowState == CScene::MODE_MOVIE)
		{
		CObjectMotion::Update();//------------------�X�V


		//SetNowMotion_Parent(MOTIONTYPE_STANDBY);
		//SetNowMotion_Sub(MOTIONTYPE_STANDBY);
		}
		else if (NowState == CScene::MODE_MOVIE2)
		{
			m_nCntFrame++;

			DATA classData = GetClassData();
			//classData.rot.x = -1.57f;
			//classData.move.z = -7.0f;

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
				//Explosion3D::Create(D3DXVECTOR3(classData.Pos.x, classData.Pos.y, classData.Pos.z));
			}

			if (m_nCntFrame > 650)
			{//

			}

			if (m_nCntFrame >= 800 && m_nCntFrame < 1260)
			{
				//			m_CTextWindow->SetText(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 320.0f, SCREEN_HEIGHT * 0.5f - 345.0f, 0.0f), 25, 40, 2, "�N�\�b............�����ފ́I\n.........................\n...............", D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 240);

				classData.move.y = +0.5f;
				classData.move.z = 1.2f;

			}

			if (m_nCntFrame > 1260)
			{
				classData.move.y = 0.0f;
				classData.move.z = 0.0f;
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
	else
	{//�ҋ@���
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
void CObjectMotionEnemyGuard::Draw()
{
	CObjectMotion::Draw();

	//char cData2[100] = {};
	//snprintf(cData2, sizeof(cData2), "�G���݂�GRID/%d�ړ���GRID%d", m_OldMyGRIDNum, NowMoveGRIDNum); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
	//// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
	//CFont::DrawTextSet(D3DXVECTOR3(1000.0f, 320.0f, 0.0f), 20, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), cData2);

}

//=============================
// ����
//=============================
CObjectMotionEnemyGuard* CObjectMotionEnemyGuard::Create(std::string pfilePass, DATA SetData)
{
	CObjectMotionEnemyGuard* pObstacle = new CObjectMotionEnemyGuard;

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

//=============================
// �U�����W�b�N
//=============================
void CObjectMotionEnemyGuard::Attack()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();


	DATA TargetData = DataInit();

	//�C���̈ʒu�Ɋ�Â��C�e���ˌ��̈ʒu----------------------------------------------+-----------------
	//�������f���̃f�[�^
	CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

	D3DXMATRIX pMat = pParts->GetMtxWorld();

	D3DXMATRIX EscMtxWorld;

	D3DXMATRIX mtxTrans, mtxRot;//�v�Z�p�}�g���b�N�X

	DATA pEscDATA = pParts->GetDATA();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&EscMtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_fRotTurret, 0.0f, 0.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//�����̐e�̃}�g���b�N�X�����Ă�
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

	D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//�C�e�ˏo��	
	//-----------------------------------------------------------------------------------------------

	//+�G���A�ɑ΂����e�\���ˌ�

	//+�����\���Ə��ˌ�

	//----------------------------------------------------------------------------------
	//player�̈ʒu���擾
	CObject* pObj = nullptr;
	pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	D3DXVECTOR3 TargetPos = {};

	CObject::DATA EscData;

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);

		EscData = pPlayer->GetClassData();
		EscData.Pos.y += 130.0f;
	}

	//�Ə��ʒu�Ɋ�Â�
	TurretRotation(SetPos, EscData.Pos, TargetData.move);
	//----------------------------------------------------------------------------------

	if (m_nMissileDelay <= 0)
	{
		CObject* pObj = nullptr;
		pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MISSILE_MNG, CObject::OBJECT_MISSILE_MNG);

		CMissileALL* pMissile = static_cast<CMissileALL*>(pObj);
		DATA Setdata = DataInit();

		Setdata.Pos = GetClassData().Pos;

		pMissile->SetMissile(Setdata, 0, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), nullptr, CMissileALL::SHOTTYPE_ENEMY);

		m_nMissileDelay = MISSILESHOTDELAY;





		CSound* pSound = pManager->GetSound();
		pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);
	}
	else
	{
		m_nMissileDelay--;
	}



	if (m_nBulletDelay <= 0)
	{
		DATA SETDATA = CObject::DataInit();

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&EscMtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_fRotTurret, 0.0f, 0.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -210.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

		//�����̐e�̃}�g���b�N�X�����Ă�
		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

		D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//�C�e�ˏo��	

		SETDATA.Pos = SetPos;
		SETDATA.rot.y = m_fRotTurret;

		D3DXVECTOR3 BulletMim = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
		D3DXVECTOR3 BulletMax = D3DXVECTOR3(30.0f, 30.0f, 30.0f);



		bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_NOMAL, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_NOMAL, SETDATA.Pos, BulletMim, BulletMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
		}

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_NOMAL, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D);
		}

		if (bNoShot == false)
		{

			// ���݂̖C���ʒu����̔��ˎ��C�emove�x�N�g��
			D3DXVECTOR3 direction = D3DXVECTOR3(EscData.Pos.x, EscData.Pos.y, EscData.Pos.z) - SetPos;
			D3DXVec3Normalize(&direction, &direction); // �����x�N�g���𐳋K��

			// �o���b�g�̑����������ăx�N�g�����C��
			D3DXVECTOR3 BulletMoveIF = direction * BULLETMOVESPEED_NOMAL;

			SETDATA.move = BulletMoveIF;

			CRenderer* pRenderer = nullptr;

			CManager* pManager = CManager::GetInstance();

			//		CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

		//			pBulletAll->SetBullet(SETDATA, 0, D3DXCOLOR(0.7f, 0.3f, 0.3f, 1.0f), this);

			CObject* pObj = nullptr;
			pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_NEWBULLET_MNG, CObject::OBJECT_NEWBULLET_MNG);

			if (pObj != nullptr)
			{
				CNewBulletALL* pBulletMNG = static_cast<CNewBulletALL*>(pObj);
				pBulletMNG->SetBullet(SETDATA, 0, D3DXCOLOR(0.7f, 0.3f, 0.7f, 0.8f), this, CNewBulletALL::SHOTTYPE_ENEMY);

				if (GetInScreenTarget() == true)
				{
					CSound* pSound = pManager->GetSound();
					pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);
				}
			}


			CObjectShotFire::Create(SETDATA.Pos);
			CObjectShotFire::Create(SETDATA.Pos);

			m_nBulletDelay = BULLETSHOTDELAY;
		}
	}
	else
	{
		m_nBulletDelay--;
	}
}


//==================================
// �C������
//==================================
void CObjectMotionEnemyGuard::TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	// �N���X�f�[�^���擾
	DATA classData = GetClassData();
	DATA ChangeData = DataInit();

	// �ڕW�������v�Z
	D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, 0.0f, TargetPos.z) - D3DXVECTOR3(classData.Pos.x, 0.0f, classData.Pos.z);

	// XZ���ʏ�̖ڕW�p�x���v�Z
	float targetAngleXZ = atan2f(enemyDirection.z, -enemyDirection.x) + (D3DX_PI * 0.5f);

	// ���݂̖C����XZ���ʏ�̊p�x
	float currentAngleXZ = m_fRotTurret;


	// �p�x��͈͓��Ɏ��߂�
	targetAngleXZ = fmodf(targetAngleXZ + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

	// �p�x�̍���
	float rotDiff = targetAngleXZ - currentAngleXZ;

	// �������͈͊O�Ȃ�␳---------------------------------------------------------------�߂����������Ɠ��e���ׂ�
	if (fabsf(rotDiff) > D3DX_PI)
	{
		rotDiff = (rotDiff < 0) ? (rotDiff + 2 * D3DX_PI) : (rotDiff - 2 * D3DX_PI);
	}

	currentAngleXZ += rotDiff * MOVEROT;

	if (currentAngleXZ > D3DX_PI)
	{
		currentAngleXZ -= (2.0f * D3DX_PI);
	}
	else if (currentAngleXZ < -D3DX_PI)
	{
		currentAngleXZ += (2.0f * D3DX_PI);
	}


	ChangeData.rot.y = currentAngleXZ;

	m_fRotTurret = currentAngleXZ;


	// �ύX�f�[�^�𔽉f
	SetChangeDataInObjectMotion(ChangeData);

}

//==================================
// �����ˌ�
//==================================
void CObjectMotionEnemyGuard::ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	//�������f���̃f�[�^
	CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

	D3DXMATRIX pMat = pParts->GetMtxWorld();

	D3DXMATRIX EscMtxWorld;

	D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&EscMtxWorld);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//�����̐e�̃}�g���b�N�X�����Ă�
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);


	//�w��̕�����ballet���΂�
	//----------------------------------------------------------------------------------

	DATA SetData;
	SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

	D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41,/* pMat._42*/BULLET_SHOT_POS_Y, pMat._43);

	ShotPos.y = BULLET_SHOT_POS_Y;

	// TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
	D3DXVECTOR3 direction = ShotPos - DirectionPos;

	// �����x�N�g���𐳋K���i�P�ʃx�N�g���ɂ���j
	D3DXVec3Normalize(&direction, &direction);


	float speed = 12.0f;//���x(��X�ύX)
	SetData.move = direction * speed;//���x��������


	// SetData.rot.y ���^�[�Q�b�g�̕����ɍ��킹��
	SetData.rot.x = 0.0f;
	SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
	SetData.rot.z = 0.0f;

	//----------------------------------------------------------------------------------


	D3DXVECTOR3 SetHitMin = D3DXVECTOR3(-10.0f, -10.0f, -10.0f);
	D3DXVECTOR3 SetHitMax = D3DXVECTOR3(10.0f, 10.0f, 10.0f);

	bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

	if (bNoShot == false)
	{
		bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
	}

	if (bNoShot == false)
	{
		//	SetNowMotion_Sub(2);//�U��motion

		//	CBullet3D::Create(SetData,0);//�N���G�C�g
	}
}
