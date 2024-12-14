//=========================================================
//
// enemy_motion_fast�̓���[enemy_motion_fast.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy_motion_fast.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"
//#include "ballet3D.h"
#include "line.h"
#include "tankfootprint.h"
#include "ShotFire.h"
#include "score.h"
#include "Explosion3D.h"
#include "newbullet.h"
#include "movesmoke.h"
#include "missile.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectMotionEnemyfast::CObjectMotionEnemyfast(int nPriority) :CObjectMotionEnemyBase(nPriority)
{
}
//=============================
// �f�X�g���N�^
//=============================
CObjectMotionEnemyfast::~CObjectMotionEnemyfast()
{
}

//=============================
// ������
//=============================
HRESULT CObjectMotionEnemyfast::Init()
{
	CObjectMotion::Init();
	SetObjectType(CObject::OBJECT_MOTIONENEMY_FAST);

	//	LoadRouteTable();

	m_nLife = 100;

	float fLength[3];
	fLength[0] = 80.0f;
	fLength[1] = 80.0f;
	fLength[2] = 100.0f;

	SetOBBLength(fLength);//OBB�����i�[

	m_nMoveCnt = 0;
	fRotTurret = 0.0f;
	m_BulletDelay = BULLETSHOTDELAY;

	m_LockOnUI = CLockOnUI::Create();
	m_LockOnUI_Main = CLockOnUIMain::Create();
	return S_OK;
}

//=============================
// �j��
//=============================
void CObjectMotionEnemyfast::Uninit()
{
	m_LockOnUI->SetDeath(true);
	m_LockOnUI_Main->SetDeath(true);
	CObjectMotion::Uninit();
}

//=============================
// �X�V
//=============================
void CObjectMotionEnemyfast::Update()
{
	for (int i = 0; i < GetMaxLoadPartsNum(); i++)
	{//�p�[�c��DEATH
		GetModelParts(i)->ChengeRGBAbool(true, D3DXCOLOR(0.3f, 0.1f, 0.3f, 1.0f));
	}

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();



	CObjectMotion::Update();//----------------



	DATA classData = GetClassData();


	//����A������GRID�ԍ������������
	bool bChange = false;


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

		if (m_OldTargetGRIDNum != pPlayer->GetNowGRIDNum())
		{//�ߋ��̑���ʒu�ԍ��Ƃ��܂̑���ʒu�ԍ����ꏏ����Ȃ���
			//�i�[
			m_OldTargetGRIDNum = pPlayer->GetNowGRIDNum();
			bChange = true;
		}
	}

	//�ړ��搧��
	//---------------------------------------------------------------------------------------------------------------------------------

	if (m_OldMyGRIDNum != GetNowGRIDNum())
	{//�����̉ߋ��̈ʒu�ԍ��ƌ��݂̈ʒu�ԍ����Ⴄ�Ƃ�
		//�i�[
		m_OldMyGRIDNum = GetNowGRIDNum();
		bChange = true;
	}

	if (bChange == true)
	{//���҂ǂ��炩�̈ʒu�ԍ��ɕύX����������
		CMathProc::Point pPoint;

		int NextMoveGridNum = CMathProc::GetNextMoveGridNum(m_OldTargetGRIDNum, m_OldMyGRIDNum);//���̌o�R�n

		NowMoveGRIDNum = NextMoveGridNum;


		//�ړ��搧��̕⍲------

		pPoint = CMathProc::GetPointfromObjectNum(NextMoveGridNum);

		if (pPoint.x == CMathProc::GetPointfromObjectNum(m_OldTargetGRIDNum).x && pPoint.y == CMathProc::GetPointfromObjectNum(m_OldTargetGRIDNum).y)
		{//�S�[�����ڑO
			classData.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			//�ڕW�ʒu�ʒu�����̖ڕWGRIDD�ʒu
			m_TargetPos = D3DXVECTOR3((float)((CMathProc::GRIDLEGTH)*pPoint.x) + (CMathProc::GRIDLEGTH * 0.5f), 0.0f, (float)((CMathProc::GRIDLEGTH)*pPoint.y) + (CMathProc::GRIDLEGTH * 0.5f));
	//		SetNowMotion_Parent(1);//�ړ�motion
		}
	}
	//�ړ��搧�肱���܂�
	//---------------------------------------------------------------------------------------------------------------------------------



	// �^�[�Q�b�g�ʒu�ւ̈ړ�����
	D3DXVECTOR3 direction = m_TargetPos - classData.Pos; // �����x�N�g��

	float distance = D3DXVec3Length(&direction); // �^�[�Q�b�g�܂ł̋���

	if (distance > 1.0f) // �߂����Ȃ��ꍇ�ɂ݈̂ړ�
	{
		D3DXVec3Normalize(&direction, &direction); // �����x�N�g���̐��K��

		float MoveSpeed = MOVESPEED;//�ړ����x

		// �ړ�
	//	classData.move.x = direction.x * MoveSpeed;
	//	classData.move.z = direction.z * MoveSpeed;


		// �ڕW�����̌v�Z
		float targetAngle = atan2f(direction.x, direction.z);

		//�p�x�ϓ�
		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, targetAngle + D3DX_PI);

		m_nMoveCnt++;

		if (m_nMoveCnt >= CObjectFootPrint::STANPFLAME)
		{
			m_nMoveCnt = 0;
			CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z), classData.rot);
			CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z));
		}
	}
	else
	{
		// �^�[�Q�b�g�ʒu�ɋ߂�����ꍇ�͈ړ����~
		classData.move.x = 0.0f;
		classData.move.z = 0.0f;
	}





	//�Փˑ��E--�G��

	CMathProc::CollisionData HitData = CMathProc::CheckCircleCollision_Cancel(classData.Pos, classData.Radius, CObject::OBJECT_MOTIONENEMY_FAST, LAYERINDEX_MOTIONENEMY_FAST, this);

	if (HitData.bHit == true)
	{
		classData.Pos += HitData.ResultDistance;
	}
	
	HitData = CMathProc::CheckCircleCollision_Cancel(classData.Pos, classData.Radius, CObject::OBJECT_MOTIONENEMY_NOMAL, LAYERINDEX_MOTIONENEMY_NOMAL, this);

	if (HitData.bHit == true)
	{
		classData.Pos += HitData.ResultDistance;
		HitData.bHit = false;
	}






	//CMathProc::CollisionData HitData = CMathProc::CheckCircleCollision_Cancel(classData.Pos, classData.Radius, CObject::OBJECT_MOTIONPLAYER, LAYERINDEX_MOTIONPLAYER, this);

	//if (HitData.bHit == true)
	//{
	//	classData.Pos += HitData.ResultDistance;
	//}



	SetClassData(classData);

	//�����蔻��v�Z
	m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

	//�����蔻��v�Z
	m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);


	classData = GetClassData();




	////��e�n
	////----------------------------------------------------------------------------------
	//pObj = nullptr;
	//pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_NEWBULLET_MNG, CObject::OBJECT_NEWBULLET_MNG);

	//if (pObj != nullptr)
	//{
	//	CNewBulletALL* pBulletMNG = static_cast<CNewBulletALL*>(pObj);
	//	
	//	for (int i = 0; i < CNewBulletALL::MAXBULLETALL; i++)
	//	{
	//		CNewBullet* pBullet = pBulletMNG->GetBulletData(i);
	//	
	//		if (pBullet->GetbUse() == true)
	//		{//�e���@�\���Ă���Ƃ�

	//			void* Test = pBullet->GetpCaller();

	//			if (Test != this)
	//			{//���g�����˂����{�l����Ȃ���

	//				if (pBullet->GetShotType() == CNewBulletALL::SHOTTYPE_PLAYER)
	//				{
	//					if (pBullet->GetHitEscapeTime() <= 0)
	//					{//�����}���ȍ~�̎�

	//						COBB pObb2 = pBullet->GetOBB();
	//						COBB MyObb = GetOBB();

	//						D3DXVECTOR3 HitPos;
	//						bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//�����蔻��

	//						if (btest == true)
	//						{
	//							//pBullet->SetDeath(true);
	//							pBullet->SetGoodby();

	//							m_nLife -= 100;
	//						}
	//					}
	//					else
	//					{//�}������
	//						if (pBullet->GetCaller() != this)
	//						{//���˂����e�����g����Ȃ��Ƃ�
	//							COBB pObb2 = pBullet->GetOBB();
	//							COBB MyObb = GetOBB();

	//							D3DXVECTOR3 HitPos;
	//							bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//�����蔻��

	//							if (btest == true)
	//							{
	//								//pBullet->SetDeath(true);
	//								pBullet->SetGoodby();

	//								m_nLife -= 100;
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}


	//�G�ˌ��ǐ�
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	//Attack();


	







	//------------------------------------------------------------------------------------------------------------------------------------------------------



	if (m_nLife <= 0)
	{
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

	if (pManager->GetbNow3DMode() == false)
	{//2D
	}
	else
	{
	//	if (GetNormalLockOn())
	//	{
	////		m_LockOnUI->SetPos(D3DXVECTOR3(classData.Pos.x, classData.Pos.y + 75.0f, classData.Pos.z));
	//		//���b�N�I������Ă��炱����Ăяo��
	//	//	m_LockOnUI->SetDrawOk(true);
	//	}
	//	else
	//	{
	////		m_LockOnUI->SetDrawOk(false);
	//	}
		//if (GetBulletLockOn())
		//{
		//	m_LockOnUI_Main->SetPos(D3DXVECTOR3(classData.Pos.x, classData.Pos.y + 75.0f, classData.Pos.z));
		//	//���b�N�I������Ă��炱����Ăяo��
		//	m_LockOnUI_Main->SetDrawOk(true);
		//	////���C���^�[�Q�b�g��
		//	//SetPriorityAttackTarget(true);
		//}
		//else
		//{
		//	//���b�N�I������Ă��炱����Ăяo��
		//	m_LockOnUI_Main->SetDrawOk(false);
		//	////���C���^�[�Q�b�g��
		//	//SetPriorityAttackTarget(false);
		//}
	}


	classData.move.x = 10.0f;

	SetClassData(classData);
}

//=============================
// �`��
//=============================
void CObjectMotionEnemyfast::Draw()
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
CObjectMotionEnemyfast* CObjectMotionEnemyfast::Create(const char* pfilePass, DATA SetData)
{
	CObjectMotionEnemyfast* pObstacle = new CObjectMotionEnemyfast;

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
void CObjectMotionEnemyfast::Attack()
{
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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, fRotTurret, 0.0f, 0.0f);

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

	if (m_BulletDelay <= 0)
	{
		DATA SETDATA = CObject::DataInit();

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&EscMtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, fRotTurret, 0.0f, 0.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -210.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

		//�����̐e�̃}�g���b�N�X�����Ă�
		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

		D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//�C�e�ˏo��	

		SETDATA.Pos = SetPos;
		SETDATA.rot.y = fRotTurret;

		D3DXVECTOR3 BulletMim = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
		D3DXVECTOR3 BulletMax = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

		//�H�����ݖh�~
		bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SETDATA.Pos, BulletMim, BulletMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
		}

		if (bNoShot == false)
		{

			// ���݂̖C���ʒu����̔��ˎ��C�emove�x�N�g��
			D3DXVECTOR3 direction =  D3DXVECTOR3(EscData.Pos.x, EscData.Pos.y, EscData.Pos.z)- SetPos;
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
				pBulletMNG->SetBullet(SETDATA, 0, D3DXCOLOR(0.7f, 0.3f, 0.3f, 1.0f), this, CNewBulletALL::SHOTTYPE_ENEMY);
			}


			CObjectShotFire::Create(SETDATA.Pos);
			CObjectShotFire::Create(SETDATA.Pos);

			m_BulletDelay = BULLETSHOTDELAY;
		}
	}
	else
	{
		m_BulletDelay--;
	}

}
//=============================
// �t�F�[�Y�P
//=============================
CObject::DATA CObjectMotionEnemyfast::phase1(D3DXVECTOR3 ShotPos)
{
	// �N���X�f�[�^���擾
	DATA classData = GetClassData();

	// �C�e�ˏo���̏����ʒu
	D3DXVECTOR3 SetPos = ShotPos;

	// ���݂̖C���ʒu����̔��ˎ��C�emove�x�N�g��
	D3DXVECTOR3 direction = SetPos - D3DXVECTOR3(classData.Pos.x, 50.0f, classData.Pos.z);
	D3DXVec3Normalize(&direction, &direction); // �����x�N�g���𐳋K��

	// �o���b�g�̑����������ăx�N�g�����C��
	D3DXVECTOR3 BulletMoveIF = direction * BULLETMOVESPEED_NOMAL;

	// �v���C���[�̈ʒu���擾
	CObject* pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	D3DXVECTOR3 TargetPos = {};
	D3DXVECTOR3 TargetMove = {};

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);
		CObject::DATA EscData = pPlayer->GetClassData();

		TargetPos = EscData.Pos; // �����_
		TargetMove = pPlayer->GetNowMove();
	}

	// �����̕����Ɍ������Ă���ꍇ�̏�����ǉ�
	D3DXVECTOR3 relativePos = SetPos - TargetPos;
	D3DXVECTOR3 relativeVel = BulletMoveIF - TargetMove;
	float timeToIntersection = -D3DXVec3Dot(&relativePos, &relativeVel) / D3DXVec3LengthSq(&relativeVel);

	// timeToIntersection�����܂��̓[���̏ꍇ�̏C��
	if (timeToIntersection <= 0)
	{
		timeToIntersection = 0.01f; // �ŏ��̐��̎��Ԃ�ݒ�
	}

	// ����̗\���ʒu�i�����_�j���v�Z
	D3DXVECTOR3 predictedIntersection = TargetPos + TargetMove * timeToIntersection;

	// �����x�N�g�����Čv�Z
	//����̗\���ʒu�ƒe�۔��˒n�_�̍���
	D3DXVECTOR3 nESC = predictedIntersection - SetPos;

	D3DXVec3Normalize(&direction, &nESC);
	BulletMoveIF = direction * BULLETMOVESPEED_NOMAL;

	// �Ə��ʒu�ƃo���b�g�̈ړ��x�N�g����Ԃ�
	CObject::DATA EscDATA;
	EscDATA.Pos = predictedIntersection;
	EscDATA.move = BulletMoveIF;

	return EscDATA;
}

//=============================
// �t�F�[�Y2
//=============================
CObject::DATA CObjectMotionEnemyfast::phase2()
{
	//-3.14����3.14�܂ł̕��p�Ɉ��Ԋu�ŉ����őł����ݒe�̎����܂łɈ�ԋ߂��������̂�ۑ����Ă������A����
	//���e��n��/�e�̑��x��BULLETMOVESPEED_NOMAL/�����͒��e���E��

	float calculationRot = D3DX_PI * 0.999f;

	// �N���X�f�[�^���擾
	DATA classData = GetClassData();

	//�C���̈ʒu�Ɋ�Â��C�e���ˌ��̈ʒu--------------------------------------------------------------
	//�������f���̃f�[�^
	CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

	D3DXMATRIX pMat = pParts->GetMtxWorld();

	D3DXMATRIX EscMtxWorld;

	D3DXMATRIX mtxTrans, mtxRot;//�v�Z�p�}�g���b�N�X

	DATA pEscDATA = pParts->GetDATA();

	//------------------------------------------------------------------------
	bool bOk = false;

	float GoodRot = 0.0f;
	float GoodRength = 99999.0f;
	int GoodFrame = 999;

	typedef struct
	{
		D3DXVECTOR3 Pos1;
		D3DXVECTOR3 Pos2;
	}ESCLINE;

	ESCLINE ESCLine[3] = {};


	// �v���C���[�̈ʒu���擾
	CObject* pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	D3DXVECTOR3 TargetPos = {};
	D3DXVECTOR3 TargetMove = {};

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);
		CObject::DATA EscData = pPlayer->GetClassData();

		TargetPos = EscData.Pos; // �����_
		TargetMove = pPlayer->GetNowMove();
	}



	while (bOk == false)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&EscMtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, calculationRot, 0.0f, 0.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);


		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

		//�����̐e�̃}�g���b�N�X�����Ă�
		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);


		D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//�C�e�ˏo��	
		D3DXVECTOR3 SetOldPos = SetPos;

		bool bBulletUpdate = false;
		int UpdateLifeCnt = 0;
		D3DXVECTOR3 Min = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
		D3DXVECTOR3 Max = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

//		int EscReflect = CBullet3D::MAXREFLECTION - 1;




		// ���݂̖C���ʒu����̔��ˎ��C�emove�x�N�g��
		D3DXVECTOR3 direction = SetPos - D3DXVECTOR3(classData.Pos.x, EscMtxWorld._42, classData.Pos.z);
		D3DXVec3Normalize(&direction, &direction); // �����x�N�g���𐳋K��

		// �o���b�g�̑����������ăx�N�g�����C��
		D3DXVECTOR3 BulletMoveIF = direction * BULLETMOVESPEED_NOMAL * 6.5f;


		ESCLine[0].Pos1 = SetPos;

		bool bOk22 = false;

		while (bBulletUpdate == false)
		{//ballet�������̉�����

			SetOldPos = SetPos;
			SetPos += BulletMoveIF;






			//�����蔻��v�Z
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_BULLET3D, SetPos, SetOldPos, Min, Max, OBJECT_HITBOX, LAYERINDEX_HITBOX, BulletMoveIF, NULL);

			if (m_HitData.bHit == false)
			{
				//�����蔻��v�Z
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_BULLET3D, SetPos, SetOldPos, Min, Max, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, BulletMoveIF, NULL);
			}

			if (m_HitData.bHit == true)
			{//�ڐG
				BulletMoveIF = m_HitData.ReflectionVector;

				

			//	EscReflect--;
			}










			// �����̕����Ɍ������Ă���ꍇ�̏�����ǉ�
			D3DXVECTOR3 relativePos = SetPos - TargetPos;
			D3DXVECTOR3 relativeVel = BulletMoveIF - TargetMove;
			float timeToIntersection = -D3DXVec3Dot(&relativePos, &relativeVel) / D3DXVec3LengthSq(&relativeVel);

			// timeToIntersection�����܂��̓[���̏ꍇ�̏C��
			if (timeToIntersection <= 0)
			{
				timeToIntersection = 0.01f; // �ŏ��̐��̎��Ԃ�ݒ�
			}

			// ����̗\���ʒu�i�����_�j���v�Z
			D3DXVECTOR3 predictedIntersection = TargetPos + TargetMove * timeToIntersection;

			//�����ŕǂɎՂ��Ă邩���f--------------------------------------
			CMathProc::CollisionData HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, predictedIntersection, 250.0f, CObject::OBJECT_OBSTACLE, CObject::LAYERINDEX_OBSTACLE);

			// �e�����̍����v�Z
			float dx = predictedIntersection.x - SetPos.x;
			float dy = predictedIntersection.y - SetPos.y;
			float dz = predictedIntersection.z - SetPos.z;

			// �������v�Z
			float MaxLength = (float)fabs(sqrtf(dx * dx + dy * dy + dz * dz)) + 2.0f;

			if (HitData.bHit == false)
			{
				HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, predictedIntersection, MaxLength, CObject::OBJECT_HITBOX, CObject::LAYERINDEX_HITBOX);
			}

			if (HitData.bHit == false)
			{
				HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, predictedIntersection, MaxLength, CObject::OBJECT_MOTIONENEMY_NOMAL, CObject::LAYERINDEX_MOTIONENEMY_NOMAL);
			}

			if (HitData.bHit == false)
			{//�Ղ��ĂȂ�
				if (GoodRength >= MaxLength)
				{
					GoodRength = MaxLength;//�ŏ��l�X�V
					GoodFrame = UpdateLifeCnt;//���̎��̃t���[����
					GoodRot = calculationRot;//���̂Ƃ��̊p�x

				}
			}


		

			UpdateLifeCnt++;

			if (UpdateLifeCnt > 80)
			{
				ESCLine[2].Pos2 = SetPos;
				break;
			}
		}

		//���̊p�x��
		calculationRot += D3DX_PI * 0.1f;

		if (D3DX_PI < calculationRot)
		{//�v�Z����o��
			bOk = true;
		}
	}


	//�I����O���ۑ����������ɔ��C����
	//float GoodRot = 0.0f;			�p�x
	//float GoodRength = 99999.0f;	//�ΏۂƂ̋���(�Ղ���̖���)
	//float GoodFrame = 999.0f;		//��ԋ߂������t���[����



	for (int i = 0; i < 3; i++)
	{
		Cline::Create(ESCLine[i].Pos1, ESCLine[i].Pos2, D3DXCOLOR(0, 0, 1, 1));
	}


	DATA EscDATA;

	//�Ƃ肠����rot�̂ݓn��
	//�t���[������͗\���Ɏg��������....�B
	EscDATA.rot.y = GoodRot;

	//	GoodRength = MaxLength;//�ŏ��l�X�V
	//	GoodFrame = UpdateLifeCnt;//���̎��̃t���[����
	//	GoodRot = calculationRot;//���̂Ƃ��̊p�x





	return EscDATA;
}
//==================================
// �C������
//==================================
void CObjectMotionEnemyfast::TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	//// �N���X�f�[�^���擾
	//DATA classData = GetClassData();
	//DATA ChangeData = DataInit();




	//// �ύX�f�[�^�𔽉f
	//SetChangeDataInObjectMotion(ChangeData);

	DATA ChangeData = DataInit(); 
	DATA classData = GetClassData();


	// �ڕW�������v�Z
	D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, 0.0f, TargetPos.z) - D3DXVECTOR3(classData.Pos.x, 0.0f, classData.Pos.z);

	// XZ���ʏ�̖ڕW�p�x���v�Z
	float targetAngleXZ = atan2f(enemyDirection.z, -enemyDirection.x) + (D3DX_PI * 0.5f);

	// ���݂̖C����XZ���ʏ�̊p�x
	float currentAngleXZ = fRotTurret;


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




	float minYAngle = -1.1f; // �����̊p�x�̌��E
	float maxYAngle = 1.1f;  // �㑤�̊p�x�̌��E


	//����
	enemyDirection = D3DXVECTOR3(TargetPos.x, TargetPos.y+270.0f, TargetPos.z) - D3DXVECTOR3(classData.Pos.x, classData.Pos.y, classData.Pos.z);

	// XZ���ʏ�̊p�x
	float angleXZ = atan2f(enemyDirection.z, enemyDirection.x);

	ChangeData.rot.x = 0.0f; // �悶���h�����߂ɕK�v�Ȓ���
	ChangeData.rot.y = -(angleXZ + 1.57f); // ����������
	ChangeData.rot.z = 0.0f;

	//		 Y���̊p�x
	float angleY = (atan2f(enemyDirection.y, sqrtf(enemyDirection.x * enemyDirection.x + enemyDirection.z * enemyDirection.z)) - (D3DX_PI * 0.124f));

	// Y���p�x���N�����v
	if (angleY < minYAngle)
	{
		angleY = minYAngle;
	}
	else if (angleY > maxYAngle)
	{
		angleY = maxYAngle;
	}

	ChangeData.rot.x = angleY; // Y������������


		// �ύX�f�[�^�𔽉f
	SetChangeDataInObjectMotion(ChangeData);
}

//==================================
// �����ˌ�
//==================================
void CObjectMotionEnemyfast::ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
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

	}
}
