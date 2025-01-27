//=========================================================
//
// player_motion[player_motion.cpp]
// Author seiya kagaya
//
//=========================================================
#include "player_motion.h"
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
#include "enemy_motion_boss.h"
#include "enemy_motion_guard.h"
#include"CBulletLine.h"
//#include "movesmoke.h"

int CObjectMotionPlayer::m_nNumPlayerAll = START_PLAYER_NUM;//�����l�R



//=============================
// �R���X�g���N�^
//=============================
CObjectMotionPlayer::CObjectMotionPlayer(int nPriority) :CObjectMotion(nPriority)
{
}

//=============================
// �f�X�g���N�^
//=============================
CObjectMotionPlayer::~CObjectMotionPlayer()
{
	m_nNumPlayerAll--;
}

//=============================
// ������
//=============================
HRESULT CObjectMotionPlayer::Init()
{
	CObjectMotion::Init();


	SetObjectType(CObject::OBJECT_MOTIONPLAYER);

	float fLength[3];
	fLength[0] = 70.0f;
	fLength[1] = 140.0f;
	fLength[2] = 60.0f;

	m_nMoveCnt = 0;

	SetOBBLength(fLength);//OBB�����i�[


	DATA classData = GetClassData();

	classData.Pos = m_RESTART_POS;

	SetClassData(classData);

	m_nLife = START_LIFE;
	m_bDown = false;
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	keyboard->GetMouseRayIntersection(*pManager->GetCamera());//�}�E�X�ʒu

//	m_TargetPos = keyboard->GetScreenPosRayIntersection(*pManager->GetCamera(), D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));//�}�E�X�ʒu
	m_TargetPos = D3DXVECTOR3(-4000.0f, 3200.0f,0.0f);

	CScene::MODE NowState = CScene::GetNowScene();



	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 /*|| NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_GAME4*/)
	{//�Q�[����
		//m_pHPUI = CObjectHPLatterUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//m_pHPGauge[0] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//m_pHPGauge[1] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	}
	else if (NowState == CScene::MODE_TITLE|| NowState == CScene::MODE_RESULT)
	{//�^�C�g��
	
		
	}

	for (int i = 0; i < GetMaxLoadPartsNum(); i++)
	{//
		GetModelParts(i)->SetMotionPoint(this);
	}

	DATA SetDATA = CObject::DataInit();
	SetDATA.MaxLength = D3DXVECTOR3(3.0f, 6.0f, 3.0f);
	SetDATA.MinLength = D3DXVECTOR3(-3.0f, 0.0f, -3.0f);

	m_pShield = CShield::Create(SetDATA, false);
	m_pShield->SetParent(GetModelParts(2));

	m_pBulletLine = CBulletLine::Create(SetDATA,this);
	m_pBulletLine->SetParent(GetModelParts(2));

	return S_OK;
}

//=============================
// �j��
//=============================
void CObjectMotionPlayer::Uninit()
{
	CObjectMotion::Uninit();
}

//=============================
// �X�V
//=============================
void CObjectMotionPlayer::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();

	if (CScene::GetStayNextStage() == false)
	{//�ҋ@��Ԃ�
		if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3)
		{//�Q�[����
	
			m_guard = false;//Reset
	
			if (m_GameStart == false)
			{
	
				DATA classData = GetClassData();
	
				classData.OldPos = m_RESTART_POS;
				classData.Pos = m_RESTART_POS;
				classData.rot.y = -D3DX_PI * 0.5f;
	
				SetClassData(classData);
				m_GameStart = true;
			}
	
	
			if (m_bDown == false)
			{
				CRenderer* pRenderer = nullptr;
	
				CManager* pManager = CManager::GetInstance();
	
				CInputKeyboard* keyboard = pManager->GetKeyboard();
	
				CInputJoyPad* JoyPad = pManager->GetJoyPad();
	
				XINPUT_STATE joykeystate;
	
				//�V���C�p�b�g�̏�Ԃ��擾
				DWORD dwResult = XInputGetState(0, &joykeystate);
	
	
	
				
	
	
	
	
				if (pManager->GetbNow3DMode() == false)
				{//2D
				}
				else
				{//3D
	
					if (m_nMissileStock < MISSILEMAX)
					{//�~�T�C���s��
						m_nMissileRecoveryCnt++;
						if (m_nMissileRecoveryCnt > RECOVERY_MISSILE)
						{//�~�T�C���񕜃t���[�����B
							m_nMissileRecoveryCnt = 0;//���Z�b�g
							m_nMissileStock++;//�~�T�C������
						}
					}
				}
	
				if (m_ShotDelay > 0)
				{
					m_ShotDelay--;
				}
	
				DATA classData = GetClassData();
	
				if (pManager->GetbNow3DMode() == false)
				{//2D
					m_TargetPos.x += classData.move.x;
					m_TargetPos.y += classData.move.y;
				}
	
				if (pManager->GetbNow3DMode() == false)
				{//2D
	
				//	�V�[���h����
				//----------------------------------------------------------------------------------
				// ���S���W DirectionPos ��ݒ�
					D3DXVECTOR3 DirectionPos = classData.Pos;
					DirectionPos.y += SHIELD_SET_ADDPOS;
	
					// �����x�N�g�����v�Z
					D3DXVECTOR3 direction = m_TargetPos - DirectionPos;
	
					// XZ ���ʂł̊p�x���v�Z (���������Ƃ���~���p�x)
					float angleRadians = atan2f(direction.x, -direction.y); // -direction.x �Ŋ��������ɕύX
	
					// ��]�f�[�^��ݒ� (X ����]�Ƃ��ēn���ꍇ)
					D3DXVECTOR3 SetRot = D3DXVECTOR3(angleRadians + (-D3DX_PI * 0.5f), (-D3DX_PI * 0.5f), 0.0f);
	
					// �V�[���h�̉�]��ݒ�
					m_pShield->SetRot(SetRot);
					//m_pBulletLine->SetRot(SetRot);

					D3DXVECTOR3 SETPOS = m_TargetPos;
	
					D3DXVec3Normalize(&direction, &direction);
	
					SETPOS -= direction * 180.0f;
	
					m_pShield->SetPos(SETPOS);
					//m_pBulletLine->SetPos(SETPOS);
					//----------------------------------------------------------------------------------
				}
				else
				{//3D
					//	�V�[���h����
				//----------------------------------------------------------------------------------
	
					D3DXVECTOR3 ESCDATA = D3DXVECTOR3(classData.Pos.x, classData.Pos.y + 150.0f, classData.Pos.z);
	
					m_pShield->SetPos(ESCDATA);
	
				}
	
				if (pManager->GetbNow3DMode() == false)
				{//2D
	
					//���`�⊮�n�_
					SetLinearInterpolation();
				}
				else
				{//3D
				}
	
				if (dwResult != ERROR_SUCCESS)
				{//�p�b�h�ڑ�����
					pManager->bSetInputState(true);
				}
	
				if (pManager->GetbNow3DMode() == false)
				{//2D
					if (pManager->bGetInputState() == true)
					{//������@--true�ŃR���g���[���[
						//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)
						ControllerInput2D();
					}
	
				}
				else
				{//3D
					if (pManager->bGetInputState() == true)
					{//������@--true�ŃR���g���[���[
						//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)
						ControllerInput3D();
					}
				}
	
	
				//-----------------------------�t���h�~
				
				if (NowState == CScene::MODE_GAME2 )
				{//�Q�[����
					classData = GetClassData();
					float HitMin = classData.Pos.x + classData.MinLength.x;
					D3DXVECTOR3 My_Collision_Min_Pos = classData.Pos + classData.MinLength;
					D3DXVECTOR3 My_Collision_Max_Pos = classData.Pos + classData.MaxLength;
					
					D3DXVECTOR3 TargetPos = D3DXVECTOR3(-15000.0f, 7000.0f, 5000.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(TargetPos.x + 15000.0f, TargetPos.y + 7000.0f, TargetPos.z + 9000.0f);
					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(TargetPos.x - 15000.0f, TargetPos.y - 7000.0f, TargetPos.z - 9000.0f);


					if (My_Collision_Min_Pos.z < TarGet_Collision_Max_Pos.z &&
						My_Collision_Max_Pos.z > TarGet_Collision_Min_Pos.z &&
						My_Collision_Min_Pos.x - classData.Pos.x + classData.OldPos.x >= TarGet_Collision_Max_Pos.x &&
						My_Collision_Min_Pos.x < TarGet_Collision_Max_Pos.x &&
						My_Collision_Min_Pos.y < TarGet_Collision_Max_Pos.y &&
						My_Collision_Max_Pos.y > TarGet_Collision_Min_Pos.y)
					{

						classData.Pos.x = TarGet_Collision_Max_Pos.x + (My_Collision_Max_Pos.x - classData.Pos.x) + 0.1f; // �ڐG�ʉ����Ԃ�
						SetClassData(classData);
					}
				}
				else if (NowState == CScene::MODE_GAME3)
				{//�Q�[����
					classData = GetClassData();
					float HitMin = classData.Pos.x + classData.MinLength.x;
					D3DXVECTOR3 My_Collision_Min_Pos = classData.Pos + classData.MinLength;
					D3DXVECTOR3 My_Collision_Max_Pos = classData.Pos + classData.MaxLength;

					D3DXVECTOR3 TargetPos = D3DXVECTOR3(12500 - 15000.0f, 10000.0f, 5000.0f);
					D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(TargetPos.x + 15000.0f, TargetPos.y + 10000.0f, TargetPos.z + 9000.0f);
					D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(TargetPos.x - 15000.0f, TargetPos.y - 10000.0f, TargetPos.z - 9000.0f);

					if (My_Collision_Min_Pos.z < TarGet_Collision_Max_Pos.z &&
						My_Collision_Max_Pos.z > TarGet_Collision_Min_Pos.z &&
						My_Collision_Min_Pos.x - classData.Pos.x + classData.OldPos.x >= TarGet_Collision_Max_Pos.x &&
						My_Collision_Min_Pos.x < TarGet_Collision_Max_Pos.x &&
						My_Collision_Min_Pos.y < TarGet_Collision_Max_Pos.y &&
						My_Collision_Max_Pos.y > TarGet_Collision_Min_Pos.y)
					{

						classData.Pos.x = TarGet_Collision_Max_Pos.x + (My_Collision_Max_Pos.x - classData.Pos.x) + 0.1f; // �ڐG�ʉ����Ԃ�
						SetClassData(classData);
					}
					//-------------------------
				}
	
	
	
	
	
	
				//GUARD�`�悷�邩
				if (m_guard == true)
				{
					m_pShield->setDrawOk(true);
					if (pManager->GetbNow3DMode() == false)
					{//2D
						m_pBulletLine->setDrawOk(false);
					}
				}
				else
				{
					m_pShield->setDrawOk(false);
					if (pManager->GetbNow3DMode() == false)
					{//2D
						m_pBulletLine->setDrawOk(true);
					}
				}
	
				classData = GetClassData();
	
				//--------------------------------------
				//�Ə��ʒu����(���@���~�`)
				if (pManager->GetbNow3DMode() == false)
				{//2D
	
	
	
					if (pManager->bGetInputState() == true)
					{//������@--true�ŃR���g���[���[
						D3DXVECTOR3 PlayerPos = GetClassData().Pos;
						float fRadius = TARGET_SET_ADDPOS * 2.0f;
	
						//m_TargetPos�����̉~�̒��Ɏ��߂�
						PlayerPos.y += TARGET_SET_ADDPOS;
	
						//�x�N�g���v�Z
						D3DXVECTOR3 VEC = m_TargetPos - PlayerPos;
	
						//�x�N�g���̒���
						float fDistance = D3DXVec3Length(&VEC);
	
						//���������a�𒴂���
						if (fDistance > fRadius)
						{
							// �x�N�g���𐳋K��
							D3DXVec3Normalize(&VEC, &VEC);
	
							// �x�N�g���̕����ɔ��a�؂�܂œ�����
							m_TargetPos = PlayerPos + VEC * fRadius;
	
						}
					}
	
	
					//�̌����ϓ�(2D)
					if (m_TargetPos.x >= classData.Pos.x)
					{//�E����
						SetFrontMove(true);//�E���ʂ�bool��set
						classData.rot.y = -D3DX_PI * 0.5f;
					}
					else
					{//������
						SetFrontMove(false);
						classData.rot.y = D3DX_PI * 0.5f;
					}
	
				}
				else
				{//3D
	
				}
	
				SetClassData(classData);
				classData = GetClassData();
	
				//�̗�--------------------------------------------------------
				if (m_nLife <= 0)
				{
					m_bDown = true;
	
					CScore::AddScore(-(CScore::DETH_PENALTY));
	
					m_nLife = START_LIFE;
	
					m_ResetCnt = 0;
	
					m_nNumPlayerAll--;
	
					for (int i = 0; i < GetMaxLoadPartsNum(); i++)
					{//�p�[�c��DEATH
						GetModelParts(i)->DrawOkBool(false);
	
						Explosion3D::Create(GetClassData().Pos);
	
					}
				}
	
				//�Փˑ��E--�G��-------------------------------------------------------
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
				}
				//------------------------------------------------------------------------
	
	
				bool bHit = false;//���n����
	
				SetClassData(classData);
	
	
				//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
				//�����ɓ]���������ؕ�
				float fTestGravity = -60.0f;
	
				DATA TestData = GetClassData();
	
				D3DXVECTOR3 TestPos = TestData.Pos;//�ʒu�ۑ�
				TestPos.y += fTestGravity;
	
				//�����蔻��v�Z
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, TestPos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
					SetClassData(TestData);//�e�X�g����Ȃ̂ŁA���ʂ�߂�
				}
	
				//�����蔻��v�Z
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, TestPos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
					SetClassData(TestData);//�e�X�g����Ȃ̂ŁA���ʂ�߂�
				}
	
				D3DXVECTOR3 rayDirection = D3DXVECTOR3(0, -1, 0); // �������̃��C
	
				m_HitData = CStageCollisionBox3D2D::bHitColision(TestPos, rayDirection, OBJECT_MOTIONPLAYER, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
					SetClassData(TestData);//�e�X�g����Ȃ̂ŁA���ʂ�߂�
				}
	
				//�����蔻��v�Z
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, TestPos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
					SetClassData(TestData);//�e�X�g����Ȃ̂ŁA���ʂ�߂�
				}
	
	
				if (bHit == false)
				{//�ڐG�������ĂȂ���==�ݒu��Ԍp�����Ă͂����Ȃ�
	
					if (classData.Pos.y > 0.0f)
					{
						SetIsOnGroundBool(false);//���n��ԉ���
					}
				}
				//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	
	
				//�d��--------------------------------------------------------
				if (!GetIsOnGroundBool())
				{//���n��ԂłȂ���
	
					//�d��
					classData.move.y -= GRAVITY * 0.1f;
				}
				else
				{//���n
	
				}
				SetClassData(classData);
				//------------------------------------------------------------
	
	
	
				//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
				//�����蔻��{�́i���n�n�j
	
				//�����蔻��v�Z
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
				}
	
				//�����蔻��v�Z
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
	
				}
	
				//�����蔻��v�Z
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
				}
	
				classData = GetClassData();
	
				if (!GetIsLandingTriggerBool())
				{//���n���Ă����ԂłȂ���
					// �ڒn����
					if (bHit || classData.Pos.y <= 0.0f)
					{//�ڐG
	
						if (classData.move.y <= 0.0f)
						{
							classData.move.y = 0.0f;
						}
	
						if (!GetIsOnGroundBool())
						{// ���ݐڒn���Ă����ԂłȂ�
							SetIsLandingTriggerBool(true); // ���n�g���K�[�𔭓�
						}
	
						SetIsOnGroundBool(true);  // �ڒn��Ԃɐݒ�
					}
				}
	
				// �ʒu�ω��ɂ��ڒn��Ԃ̉���
				float POSY = std::floor(GetOldPosY());
				float NOWPOSY = std::floor(classData.Pos.y);
	
				if (NOWPOSY != POSY)
				{
					m_RandingCutCnt++;
	
					if (m_RandingCutCnt >= RANDINGTRIGGER_FARAME)
					{
						// �ڒn��Ԃ̉���
						SetIsOnGroundBool(false);
					}
				}
				else
				{
					m_RandingCutCnt = 0;
				}
	
	
				// ���[�V�����Đ�����
				// �󒆃��[�V�����̏���
				if (!GetIsOnGroundBool() && !GetIsLandingTriggerBool())
				{//���n��Ԃ���Ȃ������n�u�Ԃ���Ȃ�
	
	
					if (/*GetNowMotionParent() != MOTIONTYPE_HIGH_MOVE_FRONT &&*/
						GetNowMotionParent() != MOTIONTYPE_HIGH_MOVE_LEFT &&
						GetNowMotionParent() != MOTIONTYPE_HIGH_MOVE_RIGHT &&
						GetNowMotionParent() != MOTIONTYPE_HIGH_MOVE_BACK)
					{
	
						SetNowMotion_Parent(MOTIONTYPE_JUMP); // �󒆃��[�V�����̍Đ�
	
						// ���[�V�����ϓ�
					//	SetNowMotion_Parent(MOTIONTYPE_STANDBY); // �ҋ@
	
					//	m_OldInputMotionParent = MOTIONTYPE_STANDBY; // �ړ��n���͂�ێ�
					}
				}
	
				// ���n���[�V�����̃g���K�[
				if (GetIsLandingTriggerBool() && GetIsOnGroundBool())
				{//���n��Ԃ����n�u��
					SetNowMotion_Parent(MOTIONTYPE_RANDING); // ���n���[�V�����̍Đ�
					SetIsLandingTriggerBool(false); // ���n�g���K�[�����Z�b�g
				}
	
				SetClassData(classData);
	
				//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	
				classData = GetClassData();
	
				//�^�[�Q�b�g�̕����ɖC����������(��)
				if (pManager->GetbNow3DMode() == false)
				{//2D
	
				  //�^�[�Q�b�g�̕����ɖC����������(��)2D
				  //----------------------------------------------------------------------------------
	
					DATA ChangeData = DataInit();
	
					float minYAngle = -1.1f; // �����̊p�x�̌��E
					float maxYAngle = 1.1f;  // �㑤�̊p�x�̌��E
	
					//����
					D3DXVECTOR3 enemyDirection = D3DXVECTOR3(m_TargetPos.x, m_TargetPos.y, m_TargetPos.z) - classData.Pos;
	
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
		
					//���N���X����p�[�c�Ƀf�[�^���󂯓n��
					SetChangeDataInObjectMotion(ChangeData);


					//	�V�[���h����
					//----------------------------------------------------------------------------------
					// ���S���W DirectionPos ��ݒ�
					D3DXVECTOR3 DirectionPos = classData.Pos;
					DirectionPos.y += SHIELD_SET_ADDPOS;

					// �����x�N�g�����v�Z
					D3DXVECTOR3 direction = m_TargetPos - DirectionPos;

					// XZ ���ʂł̊p�x���v�Z (���������Ƃ���~���p�x)
					float angleRadians = atan2f(direction.x, -direction.y); // -direction.x �Ŋ��������ɕύX

					// ��]�f�[�^��ݒ� (X ����]�Ƃ��ēn���ꍇ)
					D3DXVECTOR3 SetRot /*= D3DXVECTOR3(angleY + (-D3DX_PI * 0.5f), (-D3DX_PI * 0.5f), 0.0f)*/;

					float Diff = -0.065f;

					//�̌����ϓ�(2D)
					if (m_TargetPos.x >= classData.Pos.x)
					{//�E����
						SetRot = D3DXVECTOR3(angleY + Diff, (-D3DX_PI * 0.5f), 0.0f);
					}
					else
					{//������
						SetRot = D3DXVECTOR3(angleY + Diff, (D3DX_PI * 0.5f), 0.0f);
					}

					m_pBulletLine->SetRot(SetRot);

					D3DXVECTOR3 SETPOS = m_TargetPos;

					D3DXVec3Normalize(&direction, &direction);


					//�̌����ϓ�(2D)
					if (m_TargetPos.x >= classData.Pos.x)
					{//�E����
						SETPOS -= direction * 180.0f;
					}
					else
					{//������
						SETPOS -= direction * 180.0f;
					}
					SETPOS.y += 100.0f;


					//					m_pShield->SetPos(SETPOS);
					m_pBulletLine->SetPos(SETPOS);
					//----------------------------------------------------------------------------------
				}
				else
				{//3D
					//�^�[�Q�b�g�̕����ɖC����������(��)3D
				  //----------------------------------------------------------------------------------
					bool bLockOn = false;
	
					DATA ChangeData = DataInit();
	
					// �z�u���v���C�I���e�B�̐擪���擾
					CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_FAST);
	
					if (pObject != nullptr)
					{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�
	
						CObjectMotionEnemyfast* pEnemyFast;
						pEnemyFast = (CObjectMotionEnemyfast*)pObject;
	
						while (pObject != nullptr)
						{
							CObject::DATA EscEnemyData = pEnemyFast->GetClassData();
	
							if (pEnemyFast->GetLockOnUIMain()->bGetDrawOk() == true)
							{//�o���b�g���b�N�I�����`����
								bLockOn = true;
	
								float minYAngle = -1.1f; // �����̊p�x�̌��E
								float maxYAngle = 1.1f;  // �㑤�̊p�x�̌��E
	
								//����
								D3DXVECTOR3 enemyDirection = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 600.0f, EscEnemyData.Pos.z) - classData.Pos;
	
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
	
	
	
							//	m_TargetPos = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y+60.0f, EscEnemyData.Pos.z);
								break;
							}
							else
							{
								CObject* pNext = pObject->GetNext();
								pObject = pNext;
								pEnemyFast = (CObjectMotionEnemyfast*)pObject;
							}
						}
					}
	
					if (bLockOn == false)
					{//�܂����b�N�I�����Ȃ�
					// �z�u���v���C�I���e�B�̐擪���擾
						CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_NOMAL);
	
						if (pObject != nullptr)
						{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�
	
							CObjectMotionEnemyNomal* pEnemyNomal;
							pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;
	
							while (pObject != nullptr)
							{
								CObject::DATA EscEnemyData = pEnemyNomal->GetClassData();
	
								if (pEnemyNomal->GetLockOnUIMain()->bGetDrawOk() == true)
								{//�o���b�g���b�N�I�����`����
									bLockOn = true;
	
									float minYAngle = -1.1f; // �����̊p�x�̌��E
									float maxYAngle = 1.1f;  // �㑤�̊p�x�̌��E
	
									//����
									D3DXVECTOR3 enemyDirection = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 600.0f, EscEnemyData.Pos.z) - classData.Pos;
	
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
	
	
									m_TargetPos = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 60.0f, EscEnemyData.Pos.z);
									break;
								}
								else
								{
									CObject* pNext = pObject->GetNext();
									pObject = pNext;
									pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;
								}
							}
						}
					}
	
	
	
					if (bLockOn == false)
					{//�܂����b�N�I�����Ȃ�
					// �z�u���v���C�I���e�B�̐擪���擾
						CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS);
	
						if (pObject != nullptr)
						{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�
	
							CObjectMotionEnemyBoss* pEnemyBoss;
							pEnemyBoss = (CObjectMotionEnemyBoss*)pObject;
	
							while (pObject != nullptr)
							{
								CObject::DATA EscEnemyData = pEnemyBoss->GetClassData();
	
								if (pEnemyBoss->GetLockOnUIMain()->bGetDrawOk() == true)
								{//�o���b�g���b�N�I�����`����
									bLockOn = true;
	
									float minYAngle = -1.1f; // �����̊p�x�̌��E
									float maxYAngle = 1.1f;  // �㑤�̊p�x�̌��E
	
									//����
									D3DXVECTOR3 enemyDirection = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 600.0f, EscEnemyData.Pos.z) - classData.Pos;
	
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
	
	
									m_TargetPos = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 60.0f, EscEnemyData.Pos.z);
									break;
								}
								else
								{
									CObject* pNext = pObject->GetNext();
									pObject = pNext;
									pEnemyBoss = (CObjectMotionEnemyBoss*)pObject;
								}
							}
						}
					}
	
	
	
	
	
					if (bLockOn == false)
					{//�܂����b�N�I�����Ȃ�
					// �z�u���v���C�I���e�B�̐擪���擾
						CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS_GUARD);
	
						if (pObject != nullptr)
						{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�
	
							CObjectMotionEnemyGuard* pEnemyGuard;
							pEnemyGuard = (CObjectMotionEnemyGuard*)pObject;
	
							while (pObject != nullptr)
							{
								CObject::DATA EscEnemyData = pEnemyGuard->GetClassData();
	
								if (pEnemyGuard->GetLockOnUIMain()->bGetDrawOk() == true)
								{//�o���b�g���b�N�I�����`����
									bLockOn = true;
	
									float minYAngle = -1.1f; // �����̊p�x�̌��E
									float maxYAngle = 1.1f;  // �㑤�̊p�x�̌��E
	
									//����
									D3DXVECTOR3 enemyDirection = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 600.0f, EscEnemyData.Pos.z) - classData.Pos;
	
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
	
	
									m_TargetPos = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 60.0f, EscEnemyData.Pos.z);
									break;
								}
								else
								{
									CObject* pNext = pObject->GetNext();
									pObject = pNext;
									pEnemyGuard = (CObjectMotionEnemyGuard*)pObject;
								}
							}
						}
					}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
					if (bLockOn == false)
					{//�܂����b�N�I�����Ȃ�
					 //�Ώۂ����Ȃ�
						ChangeData.rot.y = classData.rot.y;
					}
	
	
					//���N���X����p�[�c�Ƀf�[�^���󂯓n��(������Ώۂ���Ȃ��Ƃ��͏����l������)
					SetChangeDataInObjectMotion(ChangeData);
				}
	
	
				//�ꔲ���΍�
				if (classData.Pos.y <= 0)
				{
					classData.Pos.y = 0;
				}
	
	
				SetClassData(classData);
	
	
				if (m_guard == true)
				{
					SetNowMotion_Sub(MOTIONTYPE_GUARD);
				}
	
	
				//����
				//----------------------------------------------------------------------------
				if (!GetIsOnGroundBool() && !GetIsLandingTriggerBool())
				{//���n��Ԃ���Ȃ������n�u�Ԃ���Ȃ�
					if (GetBoostNow() == true)
					{
						classData = GetClassData();
	
						//�ړ��ʂ��X�V(�^�������Ō���)
						classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_BOOST_XZ);
						classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_BOOST_Y);
						classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_BOOST_XZ);
	
						SetClassData(classData);
	
						CObjectMotion::Update();//------------------�X�V
					}
					else
					{
						if (m_BoostRestCnt > 0)
						{
							m_BoostRestCnt--;
	
							classData = GetClassData();
	
							//�ړ��ʂ��X�V(�^�������Ō���)
							classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_BOOST_XZ * 0.5f);
							classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_BOOST_Y * 0.5f);
							classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_BOOST_XZ * 0.5f);
						}
						else
						{
							classData = GetClassData();
	
							//�ړ��ʂ��X�V(�^�������Ō���)
							classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_LOAD_XZ * 0.5f);
							classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_Y * 0.5f);
							classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_LOAD_XZ * 0.5f);
						}
	
	
						SetClassData(classData);
	
						CObjectMotion::Update();//------------------�X�V
					}
				}
				else
				{//�n��
					if (GetBoostNow() == true)
					{
						classData = GetClassData();
	
						//�ړ��ʂ��X�V(�^�������Ō���)
						classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_BOOST_XZ);
						classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_BOOST_Y);
						classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_BOOST_XZ);
	
						SetClassData(classData);
	
						CObjectMotion::Update();//------------------�X�V
					}
					else
					{
						if (m_BoostRestCnt > 0)
						{
							m_BoostRestCnt--;
	
							classData = GetClassData();
	
							//�ړ��ʂ��X�V(�^�������Ō���)
							classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_BOOST_XZ);
							classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_BOOST_Y);
							classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_BOOST_XZ);
						}
						else
						{
							classData = GetClassData();
	
							//�ړ��ʂ��X�V(�^�������Ō���)
							classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_LOAD_XZ);
							classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_Y);
							classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_LOAD_XZ);
						}
	
	
						SetClassData(classData);
	
						CObjectMotion::Update();//------------------�X�V
					}
				}
	
				if (!GetIsOnGroundBool() && !GetIsLandingTriggerBool())
				{//���n��Ԃ���Ȃ������n�u�Ԃ���Ȃ�
	
	
					if (m_nBoostLife < BOOST_LIFE)
					{
						m_nBoostRecoveryCnt++;
						if (m_nBoostRecoveryCnt >= RECOVERY_Boost)
						{
							m_nBoostLife+=3;
							m_nBoostRecoveryCnt = 0;
						}
					}
				}
				else
				{//���n
					if (m_nBoostLife < BOOST_LIFE)
					{
						m_nBoostRecoveryCnt++;
						if (m_nBoostRecoveryCnt >= (RECOVERY_Boost-1))
						{
							m_nBoostLife+=3;
							m_nBoostRecoveryCnt = 0;
						}
					}
	
				}
	
				
	
	
	
	
	
	
	
	
	
	
	
				//--------------------------------------------------------------------------------
	
				classData = GetClassData();
	
			}
			else
			{//Restart�܂�
				m_ResetCnt++;
	
				if (m_ResetCnt >= RESET_CNT)
				{
					DATA SETDATA = GetClassData();
	
					SETDATA.Pos = m_RESTART_POS;//���W�X�V
					SetClassData(SETDATA);
	
					m_ResetCnt = 0;
					m_bDown = false;
					for (int i = 0; i < GetMaxLoadPartsNum(); i++)
					{//�p�[�c��DEATH
						GetModelParts(i)->DrawOkBool(true);
	
					}
				}
			}
	
		}
		else if (NowState == CScene::MODE_TITLE)
		{//�^�C�g��
			DATA classData = GetClassData();
	
			m_EscCntFootPrint++;
			if (m_EscCntFootPrint >= 5)
			{
				m_EscCntFootPrint = 0;
				//	CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z), classData.rot);
				//	CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z));
			}
	
	
			classData.rot.y = 1.57f;
	
			SetClassData(classData);
	
			DATA Head;
			Head = CObject::DataInit();
			Head.rot.y = 1.57f;
	
			//���N���X����p�[�c�Ƀf�[�^���󂯓n��
			SetChangeDataInObjectMotion(Head);
	
			CObjectMotion::Update();//------------------�X�V
	
	
			SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//�ړ�motion
			SetNowMotion_Sub(MOTIONTYPE_MOVE_FRONT);//�ړ�motion
	
	
		}
		else if (NowState == CScene::MODE_RESULT)
		{//
			DATA classData = GetClassData();
	
			m_EscCntFootPrint++;
			if (m_EscCntFootPrint >= 5)
			{
				m_EscCntFootPrint = 0;
				//CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z), classData.rot);
				//CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z));
			}
	
	
			classData.rot.y = -1.57f;
	
			SetClassData(classData);
	
			DATA Head;
			Head = CObject::DataInit();
			Head.rot.y = -1.57f;
	
			//���N���X����p�[�c�Ƀf�[�^���󂯓n��
			SetChangeDataInObjectMotion(Head);
	
			CObjectMotion::Update();//------------------�X�V
	
	
			SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//�ړ�motion
			SetNowMotion_Sub(MOTIONTYPE_MOVE_FRONT);//�ړ�motion
	
	
		}
		else if (NowState == CScene::MODE_OP)
		{//
	
			DATA classData = GetClassData();
	
			//�����ł͂����move�i�s�t���[���J�E���g�Ƃ��ė��p
			m_EscCntFootPrint++;
	
			if (m_EscCntFootPrint >= 580 && m_EscCntFootPrint < 3000)
			{
				int nSet = (m_EscCntFootPrint - 579);
				if (nSet < 15)
				{
					classData.Pos.y += -1.0f* nSet;
					classData.rot.x += -0.005f * nSet;
				}
				else
				{
					classData.Pos.y += -30.0f;
	
				
				}
	
	
			}
			else
			{
				classData.rot.x = -1.57f;
	
			}
	
	
			SetClassData(classData);
	
			DATA Head;
			Head = CObject::DataInit();
			//Head.rot.x = 1.57f;
	
			//���N���X����p�[�c�Ƀf�[�^���󂯓n��
			SetChangeDataInObjectMotion(Head);
	
			CObjectMotion::Update();//------------------�X�V
	
	
			SetNowMotion_Parent(MOTIONTYPE_OP0);//�ړ�motion
			SetNowMotion_Sub(MOTIONTYPE_OP0);//�ړ�motion
	
	
		}
		else if (NowState == CScene::MODE_MOVIE)
		{//
	
			DATA classData = GetClassData();
	
			classData.rot.y = -1.57f;

			DATA ChangeData = DataInit();
			ChangeData.rot.y = classData.rot.y;

			//���N���X����p�[�c�Ƀf�[�^���󂯓n��(������Ώۂ���Ȃ��Ƃ��͏����l������)
			SetChangeDataInObjectMotion(ChangeData);
			
			SetClassData(classData);
	
			CObjectMotion::Update();//------------------�X�V
	
	
			SetNowMotion_Parent(MOTIONTYPE_STANDBY);
			SetNowMotion_Sub(MOTIONTYPE_STANDBY);
		}
		else if (NowState == CScene::MODE_MOVIE2)
		{//

		DATA classData = GetClassData();

		classData.rot.y = -2.5824623f;

		DATA ChangeData = DataInit();
		ChangeData.rot.y = classData.rot.y;

		//���N���X����p�[�c�Ƀf�[�^���󂯓n��(������Ώۂ���Ȃ��Ƃ��͏����l������)
		SetChangeDataInObjectMotion(ChangeData);

		SetClassData(classData);

		CObjectMotion::Update();//------------------�X�V


		SetNowMotion_Parent(MOTIONTYPE_STANDBY);
		SetNowMotion_Sub(MOTIONTYPE_STANDBY);
		}
	
	
		if (m_DamageFrameCnt > 0)
		{
			m_DamageFrameCnt--;
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
void CObjectMotionPlayer::Draw()
{


		CObjectMotion::Draw();
}

//=============================
// ����
//=============================
CObjectMotionPlayer* CObjectMotionPlayer::Create(std::string pfilePass, DATA SetData)
{
	CObjectMotionPlayer* pObstacle = new CObjectMotionPlayer;

	pObstacle->SetFilePass(pfilePass);//�p�X�i�[
	pObstacle->SetStartPos(SetData.Pos);
	pObstacle->Init();

	// �擾
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)AABB_BOX_PLAYER, (float)AABB_BOX_PLAYER*3.0f, (float)AABB_BOX_PLAYER);
	SetData.MinLength = D3DXVECTOR3(-(float)AABB_BOX_PLAYER, +53.0f, -(float)AABB_BOX_PLAYER);
	pObstacle->SetClassData(SetData);


	return pObstacle;
}


//=============================
// Controller����--2D
//=============================
void CObjectMotionPlayer::ControllerInput2D()
{
	CRenderer* pRenderer = nullptr;
	
	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CCamera* pCamera = pManager->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	//���ԓ_�܂ł̋���
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//�����𔼕���

	//���ԓ_�������ăf�b�h�]�[���ƍő�_�̒��ԓ_���Z�o(�ʏ���́A�����͂̔��ʕ���_)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;

//	bool bMoveNow = false;

	float Xdate = 0.0f;
	float Zdate = 0.0f;
	float fRotDest = 0.0f;

//	bool MoveNow = false;//�ړ����͂ł��Ă邩

	DATA classData = GetClassData();

	//���𐶐����Ă悢��������
	bool bNoShot = false;
	bool bShot = false;
	bool bNomalMove = false;

	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_L1))
	{
		SetNowMotion_Sub(MOTIONTYPE_GUARD);//�h��
		SetbGuard(true);
	}

	if (GetbGuard() == false)
	{//GUARD���ĂȂ�
		//----------------------------------------------------------------�ˌ�
		if (m_ShotDelay <= 0)
		{
			if (joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{//
					//�������f���̃f�[�^
				CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

				D3DXMATRIX pMat = pParts->GetMtxWorld();

				D3DXMATRIX pMat2 = pParts->GetMtxWorld();
				
				D3DXMATRIX EscMtxWorld;
				D3DXMATRIX EscMtxWorld2;

				D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

				D3DXMATRIX mtxTrans2;//�v�Z�p�}�g���b�N�X

				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&EscMtxWorld);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, 0.0f, SHOTPOS_Y, SHOTPOS_Z);

				D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

				//�����̐e�̃}�g���b�N�X�����Ă�
				D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);



				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&EscMtxWorld2);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans2, 0.0f, 0.0f, SHOTPOS_Z-100.0f);

				D3DXMatrixMultiply(&EscMtxWorld2, &EscMtxWorld2, &mtxTrans2);

				//�����̐e�̃}�g���b�N�X�����Ă�
				D3DXMatrixMultiply(&EscMtxWorld2, &EscMtxWorld2, &pMat2);

				//Mouse�̕�����ballet���΂�
				//----------------------------------------------------------------------------------

				DATA SetData;
				SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

				D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41, pMat._42/*BULLET_SHOT_POS_Y*/, /*pMat._43*/0.0f);

				//Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
				D3DXVECTOR3 TargetPos = D3DXVECTOR3(EscMtxWorld2._41, EscMtxWorld2._42, 0.0f);

				float fX = (float)((rand() % 40) - 20);
				float fY = (float)((rand() % 40) - 20);

				TargetPos += D3DXVECTOR3(fX, fY, 0.0f);



				// TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
				D3DXVECTOR3 direction = TargetPos - DirectionPos;

				// �����x�N�g���𐳋K���i�P�ʃx�N�g���ɂ���j
				D3DXVec3Normalize(&direction, &direction);


				float speed = (int)BULLETSPEED;//���x(��X�ύX)
				SetData.move = direction * speed;//���x��������

				// SetData.rot.y ���^�[�Q�b�g�̕����ɍ��킹��
				SetData.rot.x = 0.0f;
				SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
				SetData.rot.z = 0.0f;

				//----------------------------------------------------------------------------------


				D3DXVECTOR3 SetHitMin = D3DXVECTOR3(-9.0f, -9.0f, -9.0f);
				D3DXVECTOR3 SetHitMax = D3DXVECTOR3(9.0f, 9.0f, 9.0f);

				bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

				if (bNoShot == false)
				{
					bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
				}

				if (bNoShot == false)
				{
					bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D);
				}


				if (bNoShot == false)
				{
					SetNowMotion_Sub(MOTIONTYPE_ATTACK);//�U��motion

					CRenderer* pRenderer = nullptr;

					CManager* pManager = CManager::GetInstance();

					//CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

					//pBulletAll->SetBullet(SetData, 0, D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f), this);
					CObject* pObj = nullptr;
					pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_NEWBULLET_MNG, CObject::OBJECT_NEWBULLET_MNG);

					if (pObj != nullptr)
					{
						CNewBulletALL* pBulletMNG = static_cast<CNewBulletALL*>(pObj);
						pBulletMNG->SetBullet(SetData, 0, D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f), this, CNewBulletALL::SHOTTYPE_PLAYER);
					
						CSound* pSound = pManager->GetSound();
						pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);
					}

					m_ShotDelay = 4;

					CObjectShotFire::Create(SetData.Pos);
					bShot = true;
				}
			}
		}
		//----------------------------------------------------------------�ˌ�
	}

	SetClassData(classData);
	
	if (GetBoostNow() == false)
	{
		if (m_nBoostLife >= BOOSTMOVE_USE)
		{
			if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_X))
			{//Boost
				m_nBoostCnt = BOOST_FARAME;
				m_BoostRestCnt = BOOST_RESTFARAME;
				SetBoostNow(true);
				m_nBoostLife -= BOOSTMOVE_USE;
			}
		}
	}
	else
	{
		m_nBoostCnt--;
		if (m_nBoostCnt<=0)
		{
			SetBoostNow(false);
		}
	}
	
	////-----------------------------------------------------------�R���g���[���[��
	bool MoveNowCom = false;//���̗͂L��(�R���g���[��)

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//A�������ꂽ(��)
	//	Xdate = 1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//D�������ꂽ(�E)
	//	Xdate = -1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//W�������ꂽ(��)
		//Zdate = -1.0f;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//S�������ꂽ(��)
		//Zdate = 1.0f;
		MoveNowCom = true;
	}



	//�ړ������Ԃ̎�
	if (MoveNowCom == true)
	{
		m_nMoveCnt++;

		if (m_nMoveCnt >= CObjectFootPrint::STANPFLAME)
		{
			m_nMoveCnt = 0;
			//CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z), classData.rot);
		}

		if (GetBoostNow() == true)
		{
			if (m_nBoostCnt<= BOOST_FARAME&& m_nBoostCnt< BOOST_FARAME*0.4f)
			{//����
				classData.move.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 1.8f;
//				classData.move.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 1.3f;

			}
			else
			{//�I��
				classData.move.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 1.5f;
//				classData.move.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 1.1f;

			}
			
		}
		else
		{
			if (m_BoostRestCnt > 0)
			{
				classData.move.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 1.65f;
//				classData.move.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 1.05f;
			}
			else
			{
				classData.move.x = (joykeystate.Gamepad.sThumbLX * JoyStickDiff * 1.45f);
//				classData.move.z = (joykeystate.Gamepad.sThumbLY * JoyStickDiff);
			}
		}

		if (GetFrontMove() == true)
		{//�E����

			if (classData.move.x>=0)
			{//�O�i
				if (GetBoostNow() == true)
				{
					SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_FRONT);//�ړ�
					m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_FRONT;//�ړ��n���͂�ێ�

				}
				else
				{
					SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//�ړ�
					m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//�ړ��n���͂�ێ�
				}
			
				classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
			}
			else
			{//���
				classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest);

				if (GetBoostNow() == true)
				{
					SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_BACK);//�ړ�
					m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_BACK;//�ړ��n���͂�ێ�

				}
				else
				{
					SetNowMotion_Parent(MOTIONTYPE_MOVE_BACK);//�ړ�
					m_OldInputMotionParent = MOTIONTYPE_MOVE_BACK;//�ړ��n���͂�ێ�
				}
				
			}
		}
		else
		{//������
			if (classData.move.x < 0)
			{//�O�i
				classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
			
				if (GetBoostNow() == true)
				{
					SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_FRONT);//�ړ�
					m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_FRONT;//�ړ��n���͂�ێ�

				}
				else
				{
					SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//�ړ�
					m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//�ړ��n���͂�ێ�
				}
			}
			else
			{//���
				classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest);
			
				if (GetBoostNow() == true)
				{
					SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_BACK);//�ړ�
					m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_BACK;//�ړ��n���͂�ێ�
				}
				else
				{
					SetNowMotion_Parent(MOTIONTYPE_MOVE_BACK);//�ړ�
					m_OldInputMotionParent = MOTIONTYPE_MOVE_BACK;//�ړ��n���͂�ێ�
				}
			}
		}
		
	}
	else
	{//�ړ����Ȃ������ꍇ

		if (GetNowMotionParent() != MOTIONTYPE_STANDBY &&
			GetNowMotionParent() != MOTIONTYPE_JUMP &&
			GetNowMotionParent() != MOTIONTYPE_RANDING &&
			GetNowMotionParent() != MOTIONTYPE_ATTACK)
		{
			// ���[�V�����ϓ�
			SetNowMotion_Parent(MOTIONTYPE_STANDBY); // �ҋ@

			m_OldInputMotionParent = MOTIONTYPE_STANDBY; // �ړ��n���͂�ێ�
		}

		if (GetNowMotionSub() != MOTIONTYPE_ATTACK)
		{//���[�V�����ϓ�
			SetNowMotion_Sub(MOTIONTYPE_STANDBY);//�ҋ@

			m_OldInputMotionParent = MOTIONTYPE_STANDBY;//�ړ��n���͂�ێ�
		}

	}
	//-------------------------------------------------------------------------------------------------------------------------
	//�E�X�e�B�b�N

	 bool MoveNowCom2 = false;//���̗͂L��(�R���g���[��)

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//A�������ꂽ(��)
	//	Xdate = 1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2000))
	{//D�������ꂽ(�E)
	//	Xdate = -1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2000))
	{//W�������ꂽ(��)
		//Zdate = -1.0f;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2000))
	{//S�������ꂽ(��)
		//Zdate = 1.0f;
		MoveNowCom2 = true;
	}

	int sThumbRX = joykeystate.Gamepad.sThumbRX;
	int sThumbRY = joykeystate.Gamepad.sThumbRY;

	// �X�e�B�b�N�̓��͒l����x�N�g���̑傫�����v�Z
	float magnitude = std::sqrt(static_cast<float>(sThumbRX * sThumbRX) + static_cast<float>(sThumbRY * sThumbRY));

	float vecX, vecY;

	if (magnitude > 3000)
	{
		// �l�𐳋K���i�P�ʃx�N�g�����v�Z�j
		vecX = sThumbRX / magnitude;
		vecY = sThumbRY / magnitude;
		//// �^�[�Q�b�g�̈ʒu���v�Z
		m_TargetPos.x = classData.Pos.x + vecX * 500.0f; // X�����Ɉ�苗���i��
		m_TargetPos.y = (classData.Pos.y + 150.0f) + vecY * 500.0f; // Y�����Ɉ�苗���i��
		m_TargetPos.z = 0;

	}
	else 
	{
		// �X�e�B�b�N�������̏ꍇ�̓x�N�g����0��
		vecX = 0.0f;
		vecY = 0.0f;


		//�����Ő��ʂƂ̍������p�x�ő��������

	}

	float MoveSpeed2 = MOVESPEED;

	if (MoveNowCom2 == false)
	{

	}
	else
	{//Controller

		//Controller�ړ�

		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbRX, (float)-joykeystate.Gamepad.sThumbRY);//���ꂪ���p

		fRotDest = (Angle2 - CameraRot.y - (1.0f * D3DX_PI));

		D3DXVECTOR3 ESCTargetMove= D3DXVECTOR3(0.0f,0.0f,0.0f);

		if (GetBoostNow() == true)
		{
			if (m_nBoostCnt <= BOOST_FARAME && m_nBoostCnt > BOOST_FARAME * 0.5f)
			{//����
				ESCTargetMove.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 4.0f;//�O�p�֐����p���Ĉړ��̒�������
				ESCTargetMove.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 4.0f;//�O�p�֐����p���Ĉړ��̒�������

			}
			else
			{//�I��

				ESCTargetMove.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 3.0f;//�O�p�֐����p���Ĉړ��̒�������
				ESCTargetMove.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 3.0f;//�O�p�֐����p���Ĉړ��̒�������
			}
		}
		else
		{
			ESCTargetMove.x = (joykeystate.Gamepad.sThumbLX * JoyStickDiff);
			ESCTargetMove.z = (joykeystate.Gamepad.sThumbLY * JoyStickDiff);
		}

		m_TargetPos+= ESCTargetMove;

	}
	//-------------------------------------------------------------------------------------------------------------------------

	if (m_nBoostLife >= 1)
	{
		//����
		if (JoyPad->GetPress(CInputJoyPad::JOYKEY_A))
		{
			classData.move.y += 15.0f;
			m_nBoostLife-= BOOSTJUMP_USE;
		}
	}

	SetClassData(classData);

	classData = GetClassData();
	classData.Pos.z = 0.0f;

	SetClassData(classData);
}
//=============================
// Controller����--3D
//=============================
void CObjectMotionPlayer::ControllerInput3D()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	CCamera* pCamera = pManager->GetCamera();

	D3DXVECTOR3 CameraRot = pCamera->GetRot();

	CInputJoyPad* JoyPad = pManager->GetJoyPad();

	XINPUT_STATE joykeystate;

	
		

	//�V���C�p�b�g�̏�Ԃ��擾
	DWORD dwResult = XInputGetState(0, &joykeystate);

	//���ԓ_�܂ł̋���
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//�����𔼕���

	//���ԓ_�������ăf�b�h�]�[���ƍő�_�̒��ԓ_���Z�o(�ʏ���́A�����͂̔��ʕ���_)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;

	
	float Xdata = 0.0f;
	float Zdata = 0.0f;
	float fRotDest = 0.0f;

//	bool MoveNow = false;//�ړ����͂ł��Ă邩

	DATA classData = GetClassData();

	//���𐶐����Ă悢��������
	bool bNoShot = false;
	bool bShot = false;
	bool bNomalMove = false;

	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_L1))
	{
		SetNowMotion_Sub(MOTIONTYPE_GUARD);//�h��
		SetbGuard(true);
	}

	if (GetbGuard() == false)
	{//GUARD���ĂȂ�

		if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_R1))
		{
			CRenderer* pRenderer = nullptr;

			CManager* pManager = CManager::GetInstance();

			CObject* pObj = nullptr;
			pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MISSILE_MNG, CObject::OBJECT_MISSILE_MNG);


			//�������f���̃f�[�^
			CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

			D3DXMATRIX pMat = pParts->GetMtxWorld();

			D3DXMATRIX EscMtxWorld;

			D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&EscMtxWorld);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, 0.0f, SHOTPOS_Y, 0.0f);

			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

			//�����̐e�̃}�g���b�N�X�����Ă�
			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

			//Mouse�̕�����ballet���΂�
			//----------------------------------------------------------------------------------

			DATA SetData=DataInit();
			SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

//			SetData.move.x = -80.0f;
			SetData.move.y = +160.0f;
			SetData.move.z = -80.0f;




		  //----------------------------------------------------------------------------------
			bool bLockOn = false;

			DATA ChangeData = DataInit();

			// �z�u���v���C�I���e�B�̐擪���擾
			CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_FAST);

			if (pObject != nullptr)
			{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

				CObjectMotionEnemyfast* pEnemyFast;
				pEnemyFast = (CObjectMotionEnemyfast*)pObject;

				while (pObject != nullptr)
				{
					if (m_nMissileStock > 0)
					{
						CObject::DATA EscEnemyData = pEnemyFast->GetClassData();

						if (pEnemyFast->GetLockOnUI()->bGetDrawOk() == true)
						{//���b�N�I�����`����
							bLockOn = true;

							if (pObj != nullptr)
							{
								CMissileALL* pMissile = static_cast<CMissileALL*>(pObj);
								pMissile->SetMissile(SetData, 0, D3DXCOLOR(1.0f, 0.1f, 1.0f, 1.0f), pEnemyFast, CMissileALL::SHOTTYPE_PLAYER);

								m_nMissileStock--;

								CSound* pSound = pManager->GetSound();
								pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);

								//CNewBulletALL* pBulletMNG = static_cast<CNewBulletALL*>(pObj);
								//pBulletMNG->SetBullet(SetData, 0, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f), pEnemyFast, CNewBulletALL::SHOTTYPE_PLAYER);
							}
						}
						//break;
						CObject* pNext = pObject->GetNext();
						pObject = pNext;
						pEnemyFast = (CObjectMotionEnemyfast*)pObject;
					}
					else
					{
						break;
					}
				}
			}

			// �z�u���v���C�I���e�B�̐擪���擾
			 pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_NOMAL);

			if (pObject != nullptr)
			{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

				CObjectMotionEnemyNomal* pEnemyNomal;
				pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;

				while (pObject != nullptr)
				{
					if (m_nMissileStock > 0)
					{
						CObject::DATA EscEnemyData = pEnemyNomal->GetClassData();

						if (pEnemyNomal->GetLockOnUI()->bGetDrawOk() == true)
						{//�o���b�g���b�N�I�����`����
							bLockOn = true;

							if (pObj != nullptr)
							{
								CMissileALL* pMissile = static_cast<CMissileALL*>(pObj);
								pMissile->SetMissile(SetData, 0, D3DXCOLOR(1.0f, 0.1f, 1.0f, 1.0f), pEnemyNomal, CMissileALL::SHOTTYPE_PLAYER);
								m_nMissileStock--;
								/*CNewBulletALL* pBulletMNG = static_cast<CNewBulletALL*>(pObj);
								pBulletMNG->SetBullet(SetData, 0, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f), pEnemyNomal, CNewBulletALL::SHOTTYPE_PLAYER);*/
								CSound* pSound = pManager->GetSound();
								pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);
							}

							//break;
							CObject* pNext = pObject->GetNext();
							pObject = pNext;
							pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;
						}
						else
						{
							CObject* pNext = pObject->GetNext();
							pObject = pNext;
							pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;


						}
					}
					else
					{
						break;
					}
				}
			}




			// �z�u���v���C�I���e�B�̐擪���擾
			pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS);

			if (pObject != nullptr)
			{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

				CObjectMotionEnemyBoss* pEnemyBoss;
				pEnemyBoss = (CObjectMotionEnemyBoss*)pObject;

				while (pObject != nullptr)
				{
					if (m_nMissileStock > 0)
					{
						CObject::DATA EscEnemyData = pEnemyBoss->GetClassData();

						if (pEnemyBoss->GetLockOnUI()->bGetDrawOk() == true)
						{//�o���b�g���b�N�I�����`����
							bLockOn = true;

							if (pObj != nullptr)
							{
								CMissileALL* pMissile = static_cast<CMissileALL*>(pObj);
								pMissile->SetMissile(SetData, 0, D3DXCOLOR(1.0f, 0.1f, 1.0f, 1.0f), pEnemyBoss, CMissileALL::SHOTTYPE_PLAYER);
								m_nMissileStock--;
								/*CNewBulletALL* pBulletMNG = static_cast<CNewBulletALL*>(pObj);
								pBulletMNG->SetBullet(SetData, 0, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f), pEnemyNomal, CNewBulletALL::SHOTTYPE_PLAYER);*/
								CSound* pSound = pManager->GetSound();
								pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);
							}

							//break;
							CObject* pNext = pObject->GetNext();
							pObject = pNext;
							pEnemyBoss = (CObjectMotionEnemyBoss*)pObject;
						}
						else
						{
							CObject* pNext = pObject->GetNext();
							pObject = pNext;
							pEnemyBoss = (CObjectMotionEnemyBoss*)pObject;


						}
					}
					else
					{
						break;
					}
				}
			}




			// �z�u���v���C�I���e�B�̐擪���擾
			pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS_GUARD);

			if (pObject != nullptr)
			{ // �擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

				CObjectMotionEnemyGuard* pEnemyGuard;
				pEnemyGuard = (CObjectMotionEnemyGuard*)pObject;

				while (pObject != nullptr)
				{
					if (m_nMissileStock > 0)
					{
						CObject::DATA EscEnemyData = pEnemyGuard->GetClassData();

						if (pEnemyGuard->GetLockOnUI()->bGetDrawOk() == true)
						{//�o���b�g���b�N�I�����`����
							bLockOn = true;

							if (pObj != nullptr)
							{
								CMissileALL* pMissile = static_cast<CMissileALL*>(pObj);
								pMissile->SetMissile(SetData, 0, D3DXCOLOR(1.0f, 0.1f, 0.0f, 0.8f), pEnemyGuard, CMissileALL::SHOTTYPE_PLAYER);
								m_nMissileStock--;
								/*CNewBulletALL* pBulletMNG = static_cast<CNewBulletALL*>(pObj);
								pBulletMNG->SetBullet(SetData, 0, D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f), pEnemyNomal, CNewBulletALL::SHOTTYPE_PLAYER);*/
								CSound* pSound = pManager->GetSound();
								pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOTFIRE);
							}

							//break;
							CObject* pNext = pObject->GetNext();
							pObject = pNext;
							pEnemyGuard = (CObjectMotionEnemyGuard*)pObject;
						}
						else
						{
							CObject* pNext = pObject->GetNext();
							pObject = pNext;
							pEnemyGuard = (CObjectMotionEnemyGuard*)pObject;


						}
					}
					else 
					{
						break;
					}
				}
			}



		}
		//------------------------------------------------------------------------------------------------------------------------

		//----------------------------------------------------------------�ˌ�
		if (m_ShotDelay <= 0)
		{
			if (joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{//
					//�������f���̃f�[�^
				CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

				D3DXMATRIX pMat = pParts->GetMtxWorld();

				D3DXMATRIX EscMtxWorld;

				D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&EscMtxWorld);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, 0.0f, SHOTPOS_Y, SHOTPOS_Z);

				D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

				//�����̐e�̃}�g���b�N�X�����Ă�
				D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

				//Mouse�̕�����ballet���΂�
				//----------------------------------------------------------------------------------

				DATA SetData;
				SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

				D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41, pMat._42, pMat._43);
				//��L�͐Î~���̂݁A�ړ��L��͂̂��ق�



				
				D3DXVECTOR3 TargetPos;

				if (m_bBuletLockOn == false)
				{//�o���b�g���b�N�I�����Ȃ�
					TargetPos = SetData.Pos;
				}
				else
				{
					TargetPos = m_TargetPos;
				}



				// TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
				D3DXVECTOR3 direction = TargetPos - DirectionPos;

			
				float speed = (int)BULLETSPEED;//���x(��X�ύX)
				D3DXVec3Normalize(&direction, &direction);

				SetData.move = direction * speed;//���x��������

		//		CMathProc::SetPositionldPredictedImpactPoint(SetData.Pos, SetData.move, TargetPos,)

				// SetData.rot.y ���^�[�Q�b�g�̕����ɍ��킹��
				SetData.rot.x = 0.0f;
				SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
				SetData.rot.z = 0.0f;

				//----------------------------------------------------------------------------------


				D3DXVECTOR3 SetHitMin = D3DXVECTOR3(-9.0f, -9.0f, -9.0f);
				D3DXVECTOR3 SetHitMax = D3DXVECTOR3(9.0f, 9.0f, 9.0f);

				bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

				if (bNoShot == false)
				{
					bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
				}

				if (bNoShot == false)
				{
					bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D);
				}


				if (bNoShot == false)
				{
					SetNowMotion_Sub(MOTIONTYPE_ATTACK);//�U��motion

					CRenderer* pRenderer = nullptr;

					CManager* pManager = CManager::GetInstance();

					CObject* pObj = nullptr;

					pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_NEWBULLET_MNG, CObject::OBJECT_NEWBULLET_MNG);

					if (pObj != nullptr)
					{
						CNewBulletALL* pBulletMNG = static_cast<CNewBulletALL*>(pObj);
						pBulletMNG->SetBullet(SetData, 0, D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f), this, CNewBulletALL::SHOTTYPE_PLAYER);
					}

					m_ShotDelay = 4;

					CObjectShotFire::Create(SetData.Pos);
					bShot = true;
				}
			}
		}
		//----------------------------------------------------------------�ˌ�
	}

	SetClassData(classData);

	if (GetBoostNow() == false)
	{
		if (m_nBoostLife >= BOOSTMOVE_USE)
		{
			if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_X))
			{//Boost
				m_nBoostCnt = BOOST_FARAME;
				m_BoostRestCnt = BOOST_RESTFARAME;
				SetBoostNow(true);
				m_nBoostLife -= BOOSTMOVE_USE;
			}
		}
	}
	else
	{
		m_nBoostCnt--;
		if (m_nBoostCnt <= 0)
		{
			SetBoostNow(false);
		}
	}

	////-----------------------------------------------------------�R���g���[���[��
	bool MoveNowCom = false;//���̗͂L��(�R���g���[��)

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//A�������ꂽ(��)
		Xdata = 1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//D�������ꂽ(�E)
		Xdata = -1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//W�������ꂽ(��)
		Zdata = -1.0f;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//S�������ꂽ(��)
		Zdata = 1.0f;
		MoveNowCom = true;
	}









	//�ړ������Ԃ̎�
	if (MoveNowCom == true)
	{
		m_nMoveCnt++;

		if (m_nMoveCnt >= CObjectFootPrint::STANPFLAME)
		{
			m_nMoveCnt = 0;
			//CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z), classData.rot);
		}


		//�J�����̊p�x�擾
		D3DXVECTOR3 SETROT = pManager->GetCamera()->GetRot();

		// �ړ��x�N�g��
		float moveX = joykeystate.Gamepad.sThumbLX * JoyStickDiff;
		float moveZ = joykeystate.Gamepad.sThumbLY * JoyStickDiff;

		// �����u�[�X�g���Ȃ�A�ړ��ʂ𒲐�
		if (GetBoostNow() == true)
		{
			if (m_nBoostCnt <= BOOST_FARAME && m_nBoostCnt < BOOST_FARAME * 0.4f)
			{//����
				moveX *= 1.3f;
				moveZ *= 1.3f;
			}
			else
			{//�I��
				moveX *= 1.1f;
				moveZ *= 1.1f;
			}
		}
		else
		{
			if (m_BoostRestCnt > 0)
			{
				moveX *= 1.05f;
				moveZ *= 1.05f;
			}
			else
			{
				moveX *= 0.55f;
				moveZ *= 0.55f;
			}
		}

		// �J�����̊p�x�ɍ��킹�Ĉړ��x�N�g������]
		float rotatedX = moveX * cos(SETROT.y) - moveZ * sin(SETROT.y);
		float rotatedZ = moveX * sin(SETROT.y) + moveZ * cos(SETROT.y);

		fRotDest = -SETROT.y + D3DX_PI;

		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest);


		// �ŏI�I�Ȉړ���
		classData.move.x += rotatedX;
		classData.move.z += rotatedZ;


		//�擪�ړ�rot��move�̕����̍��ق����ɑ��^�т�ϓ�������
		//----------------------------------------------------
		//classData.move.z��classData.move.x�̕��p(�ړ�������rot�Ƃ���)��fRotDest(�ڕW�p�x)�̍��قŕϓ�
		//float FrontLineR = -(D3DX_PI * 0.5f - 0.57f);
		//float FrontLine2R = -(D3DX_PI * 0.5f + 0.57f);
		//float FrontLineL = (D3DX_PI * 0.5f - 0.57f);
		//float FrontLine2L = (D3DX_PI * 0.5f + 0.57f);



	

		int sThumbLX = joykeystate.Gamepad.sThumbLX;
		int sThumbLY = joykeystate.Gamepad.sThumbLY;

		// �X�e�B�b�N�̕������p�x�Ōv�Z
		float angle = std::atan2(static_cast<float>(sThumbLY), static_cast<float>(sThumbLX)) - D3DX_PI * 0.5f;

		// �p�x�𐳋K�� 
		if (angle < -D3DX_PI) angle += 2 * D3DX_PI;
		if (angle > D3DX_PI) angle -= 2 * D3DX_PI;

		// Boost��Ԃ��𔻒�
//		if (GetBoostNow() == true)
//		{
		if (!GetIsOnGroundBool())
		{//���n��ԂłȂ���
			// �O��
			if (angle >= -D3DX_PI / 4 && angle <= D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_FRONT); // �O�ړ�
				m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_FRONT;
			}
			// ������
			else if (angle > D3DX_PI / 4 && angle <= 3 * D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_LEFT); // ���ړ�
				m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_LEFT;
			}
			// �E����
			else if (angle < -D3DX_PI / 4 && angle >= -3 * D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_RIGHT); // �E�ړ�
				m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_RIGHT;
			}
			// ���
			else
			{
				SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_BACK); // ��ړ�
				m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_BACK;
			}
		}
		else
		{
			// �O��
			if (angle >= -D3DX_PI / 4 && angle <= D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT); // �O�ړ�
				m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;
			}
			// �E����
			else if (angle > D3DX_PI / 4 && angle <= 2 * D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT); // �E�ړ�
				m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;
			}
			// ������
			else if (angle < -D3DX_PI / 4 && angle >= -2 * D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT); // ���ړ�
				m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;
			}
			// ���
			else
			{
				SetNowMotion_Parent(MOTIONTYPE_MOVE_BACK); // ��ړ�
				m_OldInputMotionParent = MOTIONTYPE_MOVE_BACK;
			}
		}
	}
	else
	{//�ړ����Ȃ������ꍇ

		if (GetNowMotionParent() != MOTIONTYPE_STANDBY &&
			GetNowMotionParent() != MOTIONTYPE_JUMP &&
			GetNowMotionParent() != MOTIONTYPE_RANDING &&
			GetNowMotionParent() != MOTIONTYPE_ATTACK)
		{
			// ���[�V�����ϓ�
			SetNowMotion_Parent(MOTIONTYPE_STANDBY); // �ҋ@

			m_OldInputMotionParent = MOTIONTYPE_STANDBY; // �ړ��n���͂�ێ�
		}

		if (GetNowMotionSub() != MOTIONTYPE_ATTACK)
		{//���[�V�����ϓ�
			SetNowMotion_Sub(MOTIONTYPE_STANDBY);//�ҋ@

			m_OldInputMotionParent = MOTIONTYPE_STANDBY;//�ړ��n���͂�ێ�
		}

	}














	//-------------------------------------------------------------------------------------------------------------------------
	//�E�X�e�B�b�N

	bool MoveNowCom2 = false;//���̗͂L��(�R���g���[��)

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//A�������ꂽ(��)
	//	Xdate = 1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//D�������ꂽ(�E)
	//	Xdate = -1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//W�������ꂽ(��)
		//Zdate = -1.0f;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//S�������ꂽ(��)
		//Zdate = 1.0f;
		MoveNowCom2 = true;
	}

	int sThumbRX = joykeystate.Gamepad.sThumbRX;
	int sThumbRY = joykeystate.Gamepad.sThumbRY;

	// �X�e�B�b�N�̓��͒l����x�N�g���̑傫�����v�Z
	float magnitude = std::sqrt(static_cast<float>(sThumbRX * sThumbRX) + static_cast<float>(sThumbRY * sThumbRY));

	float vecX, vecY;

	if (magnitude > 0)
	{
		// �l�𐳋K���i�P�ʃx�N�g�����v�Z�j
		vecX = sThumbRX / magnitude;
		vecY = sThumbRY / magnitude;
		// �^�[�Q�b�g�̈ʒu���v�Z
//		m_TargetPos.x = classData.Pos.x + vecX * 500.0f; // X�����Ɉ�苗���i��
	//	m_TargetPos.y = (classData.Pos.y + 150.0f) + vecY * 500.0f; // Y�����Ɉ�苗���i��
	//	m_TargetPos.z = 0;

	}
	else
	{
		// �X�e�B�b�N�������̏ꍇ�̓x�N�g����0��
		vecX = 0.0f;
		vecY = 0.0f;
	}

	float MoveSpeed2 = MOVESPEED;

	//if (MoveNowCom2 == false)
	//{

	//}
	//else
	//{//Controller

	//	//Controller�ړ�

	//	float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbRX, (float)-joykeystate.Gamepad.sThumbRY);//���ꂪ���p

	//	fRotDest = (Angle2 - CameraRot.y - (1.0f * D3DX_PI));

	//	D3DXVECTOR3 ESCTargetMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	if (GetBoostNow() == true)
	//	{
	//		if (m_nBoostCnt <= BOOST_FARAME && m_nBoostCnt > BOOST_FARAME * 0.5f)
	//		{//����
	//			ESCTargetMove.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 4.0f;//�O�p�֐����p���Ĉړ��̒�������
	//			ESCTargetMove.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 4.0f;//�O�p�֐����p���Ĉړ��̒�������

	//		}
	//		else
	//		{//�I��

	//			ESCTargetMove.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 3.0f;//�O�p�֐����p���Ĉړ��̒�������
	//			ESCTargetMove.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 3.0f;//�O�p�֐����p���Ĉړ��̒�������
	//		}
	//	}
	//	else
	//	{
	//		ESCTargetMove.x = (joykeystate.Gamepad.sThumbLX * JoyStickDiff);
	//		ESCTargetMove.z = (joykeystate.Gamepad.sThumbLY * JoyStickDiff);
	//	}

	//	m_TargetPos += ESCTargetMove;

	//	
	//}
	//-------------------------------------------------------------------------------------------------------------------------


	//����
	if (m_nBoostLife >= 1)
	{
		if (JoyPad->GetPress(CInputJoyPad::JOYKEY_A))
		{
			classData.move.y += 10.0f;
			m_nBoostLife-= BOOSTJUMP_USE;
		}
	}

	SetClassData(classData);

}
//=============================
// �c�@�i�[
//=============================
void CObjectMotionPlayer::SetPlayerNum(int SetNum)
{
	m_nNumPlayerAll = SetNum;
}
//=============================
// �c�@�擾
//=============================
int CObjectMotionPlayer::GetPlayerNum()
{
	return m_nNumPlayerAll;
}
//=============================
// Restart�n�_�i�[
//=============================
void CObjectMotionPlayer::SetStartPos(D3DXVECTOR3 pos)
{
	m_RESTART_POS = pos;
}
//=============================
// �ˌ��ʒu�擾
//=============================
D3DXVECTOR3 CObjectMotionPlayer::GetTARGETPOS()
{
	return m_TargetPos;
}

//=============================
// ���`�⊮�n�_�`��
//=============================
void CObjectMotionPlayer::SetLinearInterpolation()
{

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();



				//�������f���̃f�[�^
	CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

	D3DXMATRIX pMat = pParts->GetMtxWorld();

	D3DXMATRIX pMat2 = pParts->GetMtxWorld();

	D3DXMATRIX EscMtxWorld;
	D3DXMATRIX EscMtxWorld2;

	D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

	D3DXMATRIX mtxTrans2;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&EscMtxWorld);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, SHOTPOS_Y, SHOTPOS_Z);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//�����̐e�̃}�g���b�N�X�����Ă�
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);



	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&EscMtxWorld2);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans2, 0.0f, 0.0f, SHOTPOS_Z - 100.0f);

	D3DXMatrixMultiply(&EscMtxWorld2, &EscMtxWorld2, &mtxTrans2);

	//�����̐e�̃}�g���b�N�X�����Ă�
	D3DXMatrixMultiply(&EscMtxWorld2, &EscMtxWorld2, &pMat2);

	//Mouse�̕�����ballet���΂�
	//----------------------------------------------------------------------------------

	DATA SetData;
	SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

	D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41, pMat._42/*BULLET_SHOT_POS_Y*/, /*pMat._43*/0.0f);

	//Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
//			D3DXVECTOR3 TargetPos = m_TargetPos;
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(EscMtxWorld2._41, EscMtxWorld2._42, 0.0f);


	// TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
	D3DXVECTOR3 direction = TargetPos - DirectionPos;

	// �����x�N�g���𐳋K���i�P�ʃx�N�g���ɂ���j
	D3DXVec3Normalize(&direction, &direction);


	float speed = (int)BULLETSPEED;//���x(��X�ύX)
	SetData.move = direction * (speed*0.7f);//���x��������

	// 5�ӏ��̒��Ԓn�_���i�[
	for (int i = 0; i < 7; ++i) 
	{
		
		SetData.Pos +=  SetData.move ; // ���`��Ԃɂ�蒆�Ԓn�_���v�Z
	//	CObjectLINEUI::Create(SetData.Pos);
	}

}
//=============================
// �G���b�N�I������
//=============================
void CObjectMotionPlayer::LockOnEnemy()
{
}
//=============================
// �X�N���[�����W����ʓ��ɂ��邩�ǂ����𔻒�
//=============================
bool IsInScreen(D3DXVECTOR3 screenPosition)
{
	return (screenPosition.x >= 0 && screenPosition.x <= SCREEN_WIDTH &&
		screenPosition.y >= 0 && screenPosition.y <= SCREEN_HEIGHT &&
		screenPosition.z >= 0 && screenPosition.z <= 1);
}


////=============================
//// �_�E����Ԋi�[
////=============================
//void CObjectMotionPlayer::SetDawn(bool Dawn)
//{
//	m_bDown = Dawn;
//}
////=============================
//// �_�E����Ԏ擾
////=============================
//bool CObjectMotionPlayer::GetDawn()
//{
//	return m_bDown;
//}

