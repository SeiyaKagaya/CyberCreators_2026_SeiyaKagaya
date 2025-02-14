//=========================================================
//
// player_motion[player_motion.cpp]
// Author seiya kagaya
//
//=========================================================
#include "player_motion.h"
#include "renderer.h"
#include "manager.h"
#include "tankfootprint.h"
#include "ShotFire.h"
#include "score.h"
#include "target_UI.h"
#include "linerinterUI.h"
#include "Explosion3D.h"
#include "movesmoke.h"

int CObjectMotionPlayer::m_nNumPlayerAll = START_PLAYER_NUM;//�����l

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
	fLength[0] = OBB_LENGTH[0];
	fLength[1] = OBB_LENGTH[1];
	fLength[2] = OBB_LENGTH[2];

	m_nMoveCnt = 0;

	SetOBBLength(fLength);//OBB�����i�[

	DATA classData = GetClassData();

	SetClassData(classData);

	m_nLife = LIFE;

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* keyboard = pManager->GetKeyboard();

	keyboard->GetMouseRayIntersection(*pManager->GetCamera());//�}�E�X�ʒu

	m_TargetPos = keyboard->GetScreenPosRayIntersection(*pManager->GetCamera(), D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));//�}�E�X�ʒu

	CScene::MODE NowState = CScene::GetNowScene();

	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_GAME4)
	{//�Q�[����
		m_pHPUI = CObjectHPLatterUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pHPGauge[0] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pHPGauge[1] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else if (NowState == CScene::MODE_TITLE|| NowState == CScene::MODE_RESULT)
	{//�^�C�g��		
	}
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


	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_GAME4)
	{//�Q�[����
		if (m_bDown == false)
		{
			if (ShotDelay > 0)
			{
				ShotDelay--;
			}

			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();
			CInputKeyboard* keyboard = pManager->GetKeyboard();
			CInputJoyPad* JoyPad = pManager->GetJoyPad();
			XINPUT_STATE joykeystate;

			//�V���C�p�b�g�̏�Ԃ��擾
			DWORD dwResult = XInputGetState(0, &joykeystate);

			//Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
			D3DXVECTOR3 TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			m_TargetPos += m_BulletPosMove;

			//�ړ��ʂ��X�V(�^�������Ō���)
			m_BulletPosMove.x += (0.0f - m_BulletPosMove.x) * (DAMPING_RATIO);
			m_BulletPosMove.y += (0.0f - m_BulletPosMove.y) * (DAMPING_RATIO);
			m_BulletPosMove.z += (0.0f - m_BulletPosMove.z) * (DAMPING_RATIO);
			
			if (dwResult == ERROR_SUCCESS)
			{//�p�b�h�ڑ�����
			}
			else
			{
				pManager->bSetInputState(false);
			}
			
			if (pManager->bGetInputState() == true)
			{//������@--true�ŃR���g���[���[
				//�L�[�{�[�h/�R���g���[���[���͔��f(�ړ�)
				ControllerInput();
				TargetPos = m_TargetPos;
			}
			else
			{//�L�[�{�[�h���͔��f(�ړ�)
				Input();

				TargetPos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());//�}�E�X�ʒu

				m_TargetPos = TargetPos;
			}

			m_TargetPos += GetClassData().move;

			//--------------------------------------
			//�Ə��ʒu����(���@���~�`)

			if (pManager->bGetInputState() == true)
			{//������@--true�ŃR���g���[���[
				D3DXVECTOR3 PlayerPos = GetClassData().Pos;
				
				//�x�N�g���v�Z
				D3DXVECTOR3 VEC = m_TargetPos - PlayerPos;

				//�x�N�g���̒���
				float fDistance = D3DXVec3Length(&VEC);

				//���������a�𒴂���
				if (fDistance > STICK_RADIUS)
				{
					// �x�N�g���𐳋K��
					D3DXVec3Normalize(&VEC, &VEC);

					// �x�N�g���̕����ɔ��a�؂�܂œ�����
					m_TargetPos = PlayerPos + VEC * STICK_RADIUS;
				}
			}
			//--------------------------------------

			CObjectTargetUI::Create(m_TargetPos);
			CObjectTargetUI::Create(m_TargetPos);
			CObjectTargetUI::Create(m_TargetPos);

			CObjectMotion::Update();//�X�V

			DATA classData = GetClassData();

			//-----------------------------------------��e�n
			for (int i = 0; i < CNewBulletALL::MAXBULLETALL; i++)
			{
				CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

				CNewBullet* pBullet = pBulletAll->GetBulletData(i);

				if (pBullet->GetbUse() == true)
				{
					if (pBullet->GetHitEscapeTime() <= 0)
					{//�����}���ȍ~�̎�

						COBB pObb2 = pBullet->GetOBB();
						COBB MyObb = GetOBB();

						D3DXVECTOR3 HitPos;
						bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//�����蔻��

						if (btest == true)
						{
							//pBullet->SetDeath(true);
							pBullet->SetGoodby();

							m_nLife -= DAMAGE;
						}
					}
					else
					{//�}������
						if (pBullet->GetCaller() != this)
						{//���˂����e�����g����Ȃ��Ƃ�
							COBB pObb2 = pBullet->GetOBB();
							COBB MyObb = GetOBB();

							D3DXVECTOR3 HitPos;
							bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//�����蔻��

							if (btest == true)
							{
								//pBullet->SetDeath(true);
								pBullet->SetGoodby();

								m_nLife -= DAMAGE;
							}
						}
					}
				}
			}

		
			m_pHPUI->SetPos(classData.Pos + UI_POS[0]);
	
			m_pHPGauge[0]->SetPos(classData.Pos + UI_POS[1]);
	
			m_pHPGauge[1]->SetPos(classData.Pos + UI_POS[2]);
	
			m_pHPGauge[0]->SetSize(UI_SIZE[0]);
			m_pHPGauge[1]->SetSize(D3DXVECTOR3((float)m_nLife, UI_SIZE[1].y, UI_SIZE[1].z));

			m_pHPGauge[0]->SetCol(HP_UI_COLOR[0]);
			m_pHPGauge[1]->SetCol(HP_UI_COLOR[1]);

			if (m_nLife <= 0)
			{
				m_bDown = true;

				CScore::AddScore(-(CScore::DETH_PENALTY));

				m_nLife = LIFE;

				m_ResetCnt = 0;

				m_nNumPlayerAll--;

				for (int i = 0; i < GetMaxLoadPartsNum(); i++)
				{//�p�[�c��DEATH
					GetModelParts(i)->DrawOkBool(false);

					Explosion3D::Create(GetClassData().Pos);
				}
				m_pHPUI->SetDeath(true);

				m_pHPGauge[0]->SetDeath(true);
				m_pHPGauge[1]->SetDeath(true);

				if (m_nNumPlayerAll < 0)
				{

				}
				else
				{
					m_Resue = CRescue::Create(classData.Pos + UI_POS[3]);
				}
			}
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
			}

			SetClassData(classData);

			//�����蔻��v�Z
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

			//�����蔻��v�Z
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);

			classData = GetClassData();

			//�^�[�Q�b�g�̕����ɖC����������
			  //----------------------------------------------------------------------------------

			DATA ChangeData = DataInit();

			//����
			D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, TargetPos.y, TargetPos.z) - classData.Pos;

			// XZ���ʏ�̊p�x
			float angleXZ = atan2f(enemyDirection.z, enemyDirection.x);

			ChangeData.rot.x = 0.0f; // �悶���h�����߂ɕK�v�Ȓ���
			ChangeData.rot.y = -(angleXZ + D3DX_PI*0.5f); // ����������
			ChangeData.rot.z = 0.0f;

			//		 Y���̊p�x
			float angleY = atan2f(enemyDirection.y, sqrtf(enemyDirection.x * enemyDirection.x + enemyDirection.z * enemyDirection.z));

			// Y���p�x���N�����v
			if (angleY < MIN_ANGLE_Y)
			{
				angleY = MIN_ANGLE_Y;
			}
			else if (angleY > MAX_ANGLE_Y)
			{
				angleY = MAX_ANGLE_Y;
			}

			ChangeData.rot.x = angleY; // Y������������

			//���N���X����p�[�c�Ƀf�[�^���󂯓n��
			SetChangeDataInObjectMotion(ChangeData);


			//���`�⊮�n�_
			SetLinearInterpolation();
			SetClassData(classData);

		}
		else
		{
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

				m_pHPUI = CObjectHPLatterUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pHPGauge[0] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pHPGauge[1] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				m_Resue->SetDeath(true);
			}
		}
	}
	else if (NowState == CScene::MODE_TITLE)
	{//�^�C�g��
		DATA classData = GetClassData();

		EscCntFootPrint++;
		if (EscCntFootPrint >= FOOTPRINT)
		{
			EscCntFootPrint = 0;
			CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z), classData.rot);
			//CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z));
		}

		classData.rot.y = D3DX_PI*0.5f;

		SetClassData(classData);

		DATA Head;
		Head = CObject::DataInit();
		Head.rot.y = D3DX_PI*0.5f;

		//���N���X����p�[�c�Ƀf�[�^���󂯓n��
		SetChangeDataInObjectMotion(Head);

		CObjectMotion::Update();//------------------�X�V

		SetNowMotion_Parent(1);//�ړ�motion
		SetNowMotion_Sub(1);//�ړ�motion

	}
	else if (NowState == CScene::MODE_RESULT)
	{//
		DATA classData = GetClassData();

		EscCntFootPrint++;
		if (EscCntFootPrint >= FOOTPRINT)
		{
			EscCntFootPrint = 0;
			CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z), classData.rot);
		//	CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z));
		}

		classData.rot.y = -D3DX_PI*0.5f;

		SetClassData(classData);

		DATA Head;
		Head = CObject::DataInit();
		Head.rot.y = -D3DX_PI*0.5f;

		//���N���X����p�[�c�Ƀf�[�^���󂯓n��
		SetChangeDataInObjectMotion(Head);

		CObjectMotion::Update();//------------------�X�V

		SetNowMotion_Parent(1);//�ړ�motion
		SetNowMotion_Sub(1);//�ړ�motion
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
CObjectMotionPlayer* CObjectMotionPlayer::Create(const char* pfilePass, DATA SetData)
{
	CObjectMotionPlayer* pObstacle = new CObjectMotionPlayer;

	pObstacle->SetFilePass(pfilePass);//�p�X�i�[

	pObstacle->Init();

	// �擾
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)AABB_BOX_PLAYER, (float)AABB_BOX_PLAYER*2.0f, (float)AABB_BOX_PLAYER);
	SetData.MinLength = D3DXVECTOR3(-(float)AABB_BOX_PLAYER, 0.0f, -(float)AABB_BOX_PLAYER);
	pObstacle->SetClassData(SetData);

	pObstacle->SetStartPos(SetData.Pos);

	return pObstacle;
}

//=============================
//�L�[�{�[�h����
//=============================
void CObjectMotionPlayer::Input()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	DATA classData = GetClassData();
	
	bool bMoveNow = false;

	float Xdate = 0.0f;
	float Zdate = 0.0f;

	float fRotDest = 0.0f;

	//���𐶐����Ă悢��������
	bool bNoShot = false;
	bool bShot = false;
	//----------------------------------------------------------------------------------------------------------�L�[�{�[�h
	//�L�[�{�[�h
	if (keyboard->GetPress(DIK_A) == true)
	{//A�������ꂽ(��)
		Xdate =	1;
		bMoveNow = true;
	}
	else if (keyboard->GetPress(DIK_D) == true)
	{//D�������ꂽ(�E)
		Xdate = -1;
		bMoveNow = true;
	}

	if (keyboard->GetPress(DIK_W) == true)
	{//W�������ꂽ(��)
		Zdate = -1.0f;
		bMoveNow = true;
	}
	else if (keyboard->GetPress(DIK_S) == true)
	{//S�������ꂽ(��)
		Zdate = 1.0f;
		bMoveNow = true;
	}

	//�ړ������Ԃ̎�
	if (bMoveNow == true)
	{
		m_nMoveCnt++;

		SetNowMotion_Parent(1);//�ړ�motion

		float Angle = atan2f(Xdate, Zdate);//���ꂪ���p

		CCamera* pCamera = pManager->GetCamera();

		D3DXVECTOR3 CameraRot = pCamera->GetRot();

		//------����͍���
		fRotDest = (Angle - CameraRot.y - (1.0f * D3DX_PI));
		
		classData.move.x = sinf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//�O�p�֐����p���Ĉړ��̒�������
		classData.move.z = cosf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//�O�p�֐����p���Ĉړ��̒�������
		
		//�ϊ�
		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
	}

#if 1

	if (ShotDelay <= 0)
	{
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left))
		{//���{�^���������ꂽ

			//�������f���̃f�[�^
			CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

			D3DXMATRIX pMat = pParts->GetMtxWorld();

			D3DXMATRIX EscMtxWorld;

			D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&EscMtxWorld);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, TANKFIRE_OFFSETPOS_Z);

			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

			//�����̐e�̃}�g���b�N�X�����Ă�
			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

			//Mouse�̕�����ballet���΂�
			//----------------------------------------------------------------------------------

			DATA SetData;
			SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

			D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41,/* pMat._42*/BULLET_SHOT_POS_Y, pMat._43);

			//Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
			D3DXVECTOR3 TargetPos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

			TargetPos.y = BULLET_SHOT_POS_Y;

			// TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
			D3DXVECTOR3 direction = TargetPos - DirectionPos;

			// �����x�N�g���𐳋K���i�P�ʃx�N�g���ɂ���j
			D3DXVec3Normalize(&direction, &direction);

			SetData.move = direction * BULLETMOVE;//���x��������

			// SetData.rot.y ���^�[�Q�b�g�̕����ɍ��킹��
			SetData.rot.x = 0.0f;
			SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
			SetData.rot.z = 0.0f;

			//----------------------------------------------------------------------------------

			D3DXVECTOR3 SetHitMin = D3DXVECTOR3(-BULLETSIZE, -BULLETSIZE, -BULLETSIZE);
			D3DXVECTOR3 SetHitMax = D3DXVECTOR3(BULLETSIZE, BULLETSIZE, BULLETSIZE);

			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

			if (bNoShot == false)
			{
				bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
			}

			if (bNoShot == false)
			{
				SetNowMotion_Sub(2);//�U��motion

				CRenderer* pRenderer = nullptr;

				CManager* pManager = CManager::GetInstance();

				CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

				pBulletAll->SetBullet(SetData, 2,BULLET_COLOR, this);
					
				ShotDelay = BULLETSHOTDELAY;

				CObjectShotFire::Create(SetData.Pos);
				CObjectShotFire::Create(SetData.Pos);
				bShot = true;
			}
		}
	}
#else

#endif // 1

	

	if (m_nMoveCnt>= FOOTPRINT)
	{
		m_nMoveCnt = 0;
		CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, POSY, classData.Pos.z), classData.rot);
	//	CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z));
	}

	SetClassData(classData);

}

//=============================
// Controller����
//=============================
void CObjectMotionPlayer::ControllerInput()
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


	bool bMoveNow = false;

	float Xdate = 0.0f;
	float Zdate = 0.0f;

	float fRotDest = 0.0f;

	bool MoveNow = false;//�ړ����͂ł��Ă邩


	DATA classData = GetClassData();

	//���𐶐����Ă悢��������
	bool bNoShot = false;
	bool bShot = false;
	bool bNomalMove = false;

	//----------------------------------------------------------------------------------------------------------�L�[�{�[�h
	//�L�[�{�[�h
	if (keyboard->GetPress(DIK_A) == true)
	{//A�������ꂽ(��)
		Xdate = 1;
		bMoveNow = true;
		bNomalMove = true;//�ʏ�ړ���Ԃɂ���
	}
	else if (keyboard->GetPress(DIK_D) == true)
	{//D�������ꂽ(�E)
		Xdate = -1;
		bMoveNow = true;
		bNomalMove = true;//�ʏ�ړ���Ԃɂ���
	}

	if (keyboard->GetPress(DIK_W) == true)
	{//W�������ꂽ(��)
		Zdate = -1.0f;
		bMoveNow = true;
		bNomalMove = true;//�ʏ�ړ���Ԃɂ���
	}
	else if (keyboard->GetPress(DIK_S) == true)
	{//S�������ꂽ(��)
		Zdate = 1.0f;
		bMoveNow = true;
		bNomalMove = true;//�ʏ�ړ���Ԃɂ���
	}

	//�ړ������Ԃ̎�
	if (bMoveNow == true)
	{
		m_nMoveCnt++;

		SetNowMotion_Parent(1);//�ړ�motion

		float Angle = atan2f(Xdate, Zdate);//���ꂪ���p

		CCamera* pCamera = pManager->GetCamera();

		D3DXVECTOR3 CameraRot = pCamera->GetRot();

		//------����͍���
		fRotDest = (Angle - CameraRot.y - (1.0f * D3DX_PI));

		classData.move.x = sinf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//�O�p�֐����p���Ĉړ��̒�������
		classData.move.z = cosf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//�O�p�֐����p���Ĉړ��̒�������

	//�ϊ�
		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);

	}

#if 1

	if (ShotDelay <= 0)
	{
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) || joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{//���{�^���������ꂽ

			//�������f���̃f�[�^
			CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

			D3DXMATRIX pMat = pParts->GetMtxWorld();

			D3DXMATRIX EscMtxWorld;

			D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&EscMtxWorld);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, TANKFIRE_OFFSETPOS_Z);

			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

			//�����̐e�̃}�g���b�N�X�����Ă�
			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);


			//Mouse�̕�����ballet���΂�
			//----------------------------------------------------------------------------------

			DATA SetData;
			SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

			D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41,/* pMat._42*/BULLET_SHOT_POS_Y, pMat._43);

			//Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
			D3DXVECTOR3 TargetPos = m_TargetPos;

			TargetPos.y = BULLET_SHOT_POS_Y;

			// TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
			D3DXVECTOR3 direction = TargetPos - DirectionPos;

			// �����x�N�g���𐳋K���i�P�ʃx�N�g���ɂ���j
			D3DXVec3Normalize(&direction, &direction);

			SetData.move = direction * BULLETMOVE;//���x��������

			// SetData.rot.y ���^�[�Q�b�g�̕����ɍ��킹��
			SetData.rot.x = 0.0f;
			SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
			SetData.rot.z = 0.0f;

			//----------------------------------------------------------------------------------
			D3DXVECTOR3 SetHitMin = D3DXVECTOR3(-BULLETSIZE, -BULLETSIZE, -BULLETSIZE);
			D3DXVECTOR3 SetHitMax = D3DXVECTOR3(BULLETSIZE, BULLETSIZE, BULLETSIZE);

			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

			if (bNoShot == false)
			{
				bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
			}

			if (bNoShot == false)
			{
				SetNowMotion_Sub(2);//�U��motion

				CRenderer* pRenderer = nullptr;

				CManager* pManager = CManager::GetInstance();

				CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

				pBulletAll->SetBullet(SetData, 2,BULLET_COLOR, this);

				ShotDelay = BULLETSHOTDELAY;

				CObjectShotFire::Create(SetData.Pos);
				CObjectShotFire::Create(SetData.Pos);
				bShot = true;
			}
		}
	}
#else

#endif // 1

	if (m_nMoveCnt >= FOOTPRINT)
	{
		m_nMoveCnt = 0;
		CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, POSY, classData.Pos.z), classData.rot);
		//CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z));
	}

	SetClassData(classData);
	
	////----------------------------------------------------------------------------------------------------------�R���g���[���[	
	bool MoveNowCom = false;//���̗͂L��(�R���g���[��)

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - STICK_SUB))
	{//A�������ꂽ(��)
	//	Xdate = 1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - STICK_SUB))
	{//D�������ꂽ(�E)
	//	Xdate = -1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - STICK_SUB))
	{//W�������ꂽ(��)
		//Zdate = -1.0f;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - STICK_SUB))
	{//S�������ꂽ(��)
		//Zdate = 1.0f;
		MoveNowCom = true;
	}

	if (MoveNowCom == false)
	{
		//�ړ������Ԃ̎�
		if (bMoveNow == true)
		{
			float Angle = atan2f(Xdate, Zdate);//���ꂪ���p

			//------����͍���
			fRotDest = (Angle - CameraRot.y - (1.0f * D3DX_PI));

			classData.move.x = sinf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//�O�p�֐����p���Ĉړ��̒�������
			classData.move.z = cosf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//�O�p�֐����p���Ĉړ��̒�������

		//�ϊ�
			classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
			MoveNow = true;
		}
	}
	else
	{//Controller

		//Controller�ړ�

		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbLX, (float)-joykeystate.Gamepad.sThumbLY);//���ꂪ���p

		fRotDest = (Angle2 - CameraRot.y - (1.0f * D3DX_PI));

		classData.move.x = sinf(Angle2 - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//�O�p�֐����p���Ĉړ��̒�������
		classData.move.z = cosf(Angle2 - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//�O�p�֐����p���Ĉړ��̒�������
		MoveNow = true;
	}

	//�ړ������Ԃ̎�
	if (MoveNow == true)
	{

		if (m_nMoveCnt >= FOOTPRINT)
		{
			m_nMoveCnt = 0;
			CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, POSY, classData.Pos.z), classData.rot);
		//	CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, POSY, classData.Pos.z));
		}

		classData.move = D3DXVECTOR3(joykeystate.Gamepad.sThumbLX * 0.0002f, 0.0f, joykeystate.Gamepad.sThumbLY * 0.0002f);
		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);	
	}


	//-------------------------------------------------------------------------------------------------------------------------
	//�E�X�e�B�b�N

	 bool MoveNowCom2 = false;//���̗͂L��(�R���g���[��)

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - STICK_SUB))
	{//A�������ꂽ(��)
	//	Xdate = 1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - STICK_SUB))
	{//D�������ꂽ(�E)
	//	Xdate = -1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - STICK_SUB))
	{//W�������ꂽ(��)
		//Zdate = -1.0f;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - STICK_SUB))
	{//S�������ꂽ(��)
		//Zdate = 1.0f;
		MoveNowCom2 = true;
	}

	float MoveSpeed2 = 40.0f;

	if (MoveNowCom2 == false)
	{
		//�ړ������Ԃ̎�
		if (bMoveNow == true)
		{
			float Angle = atan2f(Xdate, Zdate);//���ꂪ���p

			//------����͍���
			fRotDest = (Angle - CameraRot.y - (1.0f * D3DX_PI));

			m_BulletPosMove.x = sinf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MoveSpeed2;//�O�p�֐����p���Ĉړ��̒�������
			m_BulletPosMove.z = cosf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MoveSpeed2;//�O�p�֐����p���Ĉړ��̒�������

			MoveNow = true;
		}
	}
	else
	{//Controller
		//Controller�ړ�

		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbRX, (float)-joykeystate.Gamepad.sThumbRY);//���ꂪ���p

		fRotDest = (Angle2 - CameraRot.y - (1.0f * D3DX_PI));

		m_BulletPosMove.x = sinf(Angle2 - CameraRot.y - (1.0f * D3DX_PI)) * MoveSpeed2;//�O�p�֐����p���Ĉړ��̒�������
		m_BulletPosMove.z = cosf(Angle2 - CameraRot.y - (1.0f * D3DX_PI)) * MoveSpeed2;//�O�p�֐����p���Ĉړ��̒�������
		MoveNow = true;
	}



	//�ړ������Ԃ̎�
	if (MoveNow == true)
	{
		m_BulletPosMove = D3DXVECTOR3(joykeystate.Gamepad.sThumbRX * STICK_MAG, 0.0f, joykeystate.Gamepad.sThumbRY * STICK_MAG);
	}
	//-------------------------------------------------------------------------------------------------------------------------

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
// �����ʒu�i�[
//=============================
void CObjectMotionPlayer::SetStartPos(D3DXVECTOR3 pos)
{
	m_RESTART_POS = pos;
}

//=============================
// �ڕW�n�_�擾
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

	D3DXMATRIX EscMtxWorld;

	D3DXMATRIX mtxTrans;//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&EscMtxWorld);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, TANKFIRE_OFFSETPOS_Z);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//�����̐e�̃}�g���b�N�X�����Ă�
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

	//Mouse�̕�����ballet���΂�
	//----------------------------------------------------------------------------------

	DATA SetData;
	SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

	D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41,/* pMat._42*/BULLET_SHOT_POS_Y, pMat._43);


	//Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
	D3DXVECTOR3 TargetPos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

	TargetPos.y = BULLET_SHOT_POS_Y;

	// TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
	D3DXVECTOR3 direction = TargetPos - DirectionPos;

	// �����x�N�g���𐳋K���i�P�ʃx�N�g���ɂ���j
	D3DXVec3Normalize(&direction, &direction);

	SetData.move = direction * BULLETMOVE;//���x��������

	// SetData.rot.y ���^�[�Q�b�g�̕����ɍ��킹��
	SetData.rot.x = 0.0f;
	SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
	SetData.rot.z = 0.0f;

	D3DXVECTOR3 Pos[POINTER_NUM];

	// ���˒n�_�iSetData.Pos�j�ƏƏ��n�_�im_TargetPos�j���g����5�̒��Ԓn�_���v�Z
	D3DXVECTOR3 startPos = SetData.Pos;  // ���˒n�_
	D3DXVECTOR3 targetPos = m_TargetPos; // �Ə��n�_

	// ���˒n�_����Ə��n�_�܂ł̕����x�N�g�����v�Z
	direction = targetPos - startPos;

	// �����x�N�g����5��������
	float step = 1.0f / (float)(POINTER_NUM-1); // 5�ӏ��̒��Ԓn�_���v�Z���邽�߂̃X�e�b�v�i0, 0.25, 0.5, 0.75, 1.0�j

	// 5�ӏ��̒��Ԓn�_���i�[
	for (int i = 0; i < POINTER_NUM; ++i)
	{
		float t = i * step; // ���`��Ԃ̊���
		Pos[i] = startPos + direction * t; // ���`��Ԃɂ�蒆�Ԓn�_���v�Z
	}

	for (int i = 1; i < POINTER_NUM; ++i)
	{
		CObjectLINEUI::Create(Pos[i]);
	}
}