//=========================================================
//
// enemy_motion_Nomal�̓���[enemy_motion_Nomal.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy_motion_Nomal.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"
#include "line.h"
#include "tankfootprint.h"
#include "score.h"
#include "Explosion3D.h"
#include "newbullet.h"
#include "ShotFire.h"
#include "missile.h"

//=============================
// �R���X�g���N�^
//=============================
CObjectMotionEnemyNomal::CObjectMotionEnemyNomal(int nPriority) :CObjectMotionEnemyBase(nPriority)
{
}

//=============================
// �f�X�g���N�^
//=============================
CObjectMotionEnemyNomal::~CObjectMotionEnemyNomal()
{
}

//=============================
// ������
//=============================
HRESULT CObjectMotionEnemyNomal::Init()
{
	CObjectMotion::Init();
	SetObjectType(CObject::OBJECT_MOTIONENEMY_NOMAL);

	m_nLife = NORMAL_LIFE;

	float fLength[3];
	fLength[0] = 110.0f;
	fLength[1] = 70.0f;
	fLength[2] = 110.0f;

	SetOBBLength(fLength);//OBB�����i�[

	m_nMoveCnt = 0;
	m_fRotTurret = 1.57f;
	m_nBulletDelay = BULLETSHOTDELAY;

	m_LockOnUI = CLockOnUI::Create();//�~�T�C�����b�N�I��
	m_LockOnUI_Main = CLockOnUIMain::Create();//�o���b�g���b�N�I��
	return S_OK;
}

//=============================
// �j��
//=============================
void CObjectMotionEnemyNomal::Uninit()
{
	m_LockOnUI->SetDeath(true);
	m_LockOnUI_Main->SetDeath(true);

	CObjectMotion::Uninit();
}

//=============================
// �X�V
//=============================
void CObjectMotionEnemyNomal::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();

	if (CScene::GetStayNextStage() == false)
	{//�ҋ@��Ԃ�

		if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3)
		{//�Q�[����

			for (int i = 0; i < GetMaxLoadPartsNum(); i++)
			{
				GetModelParts(i)->ChengeRGBAbool(true, D3DXCOLOR(0.3f, 0.1f, 0.3f, 1.0f));
			}

			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();

			CObjectMotion::Update();

			DATA classData = GetClassData();

			//�n��
			if (classData.Pos.y < 0)
			{
				classData.Pos.y = 0;
			}

			//-----------------------------------------------------------------------------�����_���ړ�
			m_nMoveCnt++;
			
			if (MAXMOVECNT <= m_nMoveCnt)
			{
				m_nMoveCnt = 0;

				int fRandomShot = ((rand() % 100) - 50);//(50~-50)�܂ł̗���

				if (classData.Pos.y < 800)
				{//���x600�ȉ�
											//�s�������̑I�ʂƔ{��
					float fRandom = (float)((rand() % 4) - 2);//(2~-2)�܂ł̗���
					float fRandom3 = (float)((rand() % 4) - 2);//(2~-2)�܂ł̗���
					
					float fRandomY = fRandom;//Y�����p
					if (fRandom < 0)
					{//�}�C�i�X�����̎�
						fRandomY *= -1.6f;
					}

					float fRando2 = (float)((rand() % 10) - 5);//(5~-5)�܂ł̗���

					fRando2 *= 0.2f;//����������

					classData.move = D3DXVECTOR3(AIRMOVESPEED * fRandom * fRando2, AIRMOVESPEED * 4.0f, AIRMOVESPEED * fRandom * fRandom3);
				}
				else
				{
					//�s�������̑I�ʂƔ{��
					float fRandom = (float)((rand() % 4) - 2);//(2~-2)�܂ł̗���
					float fRandom3 = (float)((rand() % 4) - 2);//(2~-2)�܂ł̗���

					float	fRandomY = fRandom;//Y�����p

					if (fRandom < 0)
					{//�}�C�i�X�����̎�
						fRandomY *= -1.2f;
					}

					float fRando2 = (float)((rand() % 10) - 5);//(5~-5)�܂ł̗���

					fRando2 *= 0.2f;//����������

					classData.move = D3DXVECTOR3(AIRMOVESPEED * fRandom * fRando2, AIRMOVESPEED * fRandomY, AIRMOVESPEED * fRandom * fRandom3);
				}

				SetClassData(classData);
			}
			else
			{
				//�d��
				classData.move.y -= GRAVITY * 0.1f;
			}
			//-----------------------------------------------------------------------------�����_���ړ��I���

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

			SetClassData(classData);

			//�����蔻��v�Z
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

			//�����蔻��v�Z
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);

			classData = GetClassData();

			//�G�ˌ��ǐ�
			Attack();

			DATA SetData = DataInit();
			SetData.Pos = GetClassData().Pos;
			SetData.Pos.y += LOCKDIFF;

			m_LockOnUI_Main->SetDATA(SetData);
			m_LockOnUI->SetDATA(SetData);

			//���S��
			if (m_nLife <= 0)
			{
				//�~�T�C���̒ǔ����J�b�g����
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

			SetClassData(classData);


			//�_���[�W���o
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
		else if (NowState == CScene::MODE_MOVIE || NowState == CScene::MODE_MOVIE2)
		{//
			DATA ChangeData = DataInit();

			// �ύX�f�[�^�𔽉f
			SetChangeDataInObjectMotion(ChangeData);

			CObjectMotion::Update();//------------------�X�V

			//���[�V�����Z�b�g
			SetNowMotion_Parent(MOTIONTYPE_STANDBY);
			SetNowMotion_Sub(MOTIONTYPE_STANDBY);
		}
	}
	else
	{//�ҋ@���
		DATA ChangeData = DataInit();

		// �ύX�f�[�^�𔽉f
		SetChangeDataInObjectMotion(ChangeData);

		//���[�V�����Z�b�g
		SetNowMotion_Parent(MOTIONTYPE_STANDBY);
		SetNowMotion_Sub(MOTIONTYPE_STANDBY);

		//���[�V�����Đ�
		Motion_Parent();
		Motion_Sub();
	}
}

//=============================
// �`��
//=============================
void CObjectMotionEnemyNomal::Draw()
{
	CObjectMotion::Draw();
}

//=============================
// ����
//=============================
CObjectMotionEnemyNomal* CObjectMotionEnemyNomal::Create(std::string pfilePass, DATA SetData)
{
	CObjectMotionEnemyNomal* pObstacle = new CObjectMotionEnemyNomal;

	pObstacle->SetFilePass(pfilePass);//�p�X�i�[

	pObstacle->Init();
	// �擾
	DATA EscData = pObstacle->GetClassData();
	
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)(CObjectMotionEnemyBase::AABB_BOX), (float)(CObjectMotionEnemyBase::AABB_BOX)*2.0f, (float)(CObjectMotionEnemyBase::AABB_BOX));
	SetData.MinLength = D3DXVECTOR3(-(float)(CObjectMotionEnemyBase::AABB_BOX), 0.0f, -(float)(CObjectMotionEnemyBase::AABB_BOX));
	
	pObstacle->SetClassData(SetData);

	return pObstacle;
}

//=============================
// �U�����W�b�N
//=============================
void CObjectMotionEnemyNomal::Attack()
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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_fRotTurret, 0.0f, 0.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//�����̐e�̃}�g���b�N�X�����Ă�
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

	D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//�C�e�ˏo��	
	
	
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


		//�ˌ��n�_�H�����ݖh�~����
		//----------------------------------------------
		bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_FAST, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_FAST, SETDATA.Pos, BulletMim, BulletMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
		}

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_FAST, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D);
		}
		//----------------------------------------------

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


			//�ˌ�
			//-----------------------------------------------------------------
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
			//-----------------------------------------------------------------
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
void CObjectMotionEnemyNomal::TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	// �N���X�f�[�^���擾
	DATA classData = GetClassData();
	DATA ChangeData = DataInit();

	// �ڕW�������v�Z
	D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, 0.0f, TargetPos.z) - D3DXVECTOR3(classData.Pos.x, 0.0f, classData.Pos.z);

	// XZ���ʏ�̖ڕW�p�x���v�Z
	float targetAngleXZ = atan2f(enemyDirection.z, -enemyDirection.x) + (D3DX_PI*0.5f);

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
void CObjectMotionEnemyNomal::ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
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
}
