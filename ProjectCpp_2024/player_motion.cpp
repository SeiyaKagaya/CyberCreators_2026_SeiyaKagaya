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
	fLength[0] = 90.0f;
	fLength[1] = 90.0f;
	fLength[2] = 120.0f;

	m_nMoveCnt = 0;

	SetOBBLength(fLength);//OBB�����i�[


	DATA classData = GetClassData();

	classData.Pos = m_RESTART_POS;

	SetClassData(classData);

	m_nLife = 300;
	//m_bDown = false;
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	keyboard->GetMouseRayIntersection(*pManager->GetCamera());//�}�E�X�ʒu

//	m_TargetPos = keyboard->GetScreenPosRayIntersection(*pManager->GetCamera(), D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));//�}�E�X�ʒu
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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


	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2)
	{//�Q�[����

		if (m_GameStart == false)
		{


			DATA classData = GetClassData();

			classData.Pos = m_RESTART_POS;

			SetClassData(classData);
			m_GameStart = true;
		}
		


	
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


			//������@--false�ŃL�[�}�E/true�̓p�b�h
		//	pManager->bSetInputState(false);



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


			DATA classData = GetClassData();










			//2D
			//--------------------------------------
			//�Ə��ʒu����(���@���~�`)

			if (pManager->bGetInputState() == true)
			{//������@--true�ŃR���g���[���[
				D3DXVECTOR3 PlayerPos = GetClassData().Pos;
				float fRadius = 600.0f;

				//m_TargetPos�����̉~�̒��Ɏ��߂�

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
			//--------------------------------------



	


		

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

							m_nLife -= 100;
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

								m_nLife -= 100;
							}
						}

					}
				}
			}

						
			
			//for (int i = 0; i < GetMaxLoadPartsNum(); i++)
			//{//�p�[�c��DEATH
			//	GetModelParts(i)->SetColorChangeBool(true);
			//	GetModelParts(i)->SetChangeColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

			//}
			D3DXVECTOR3 SetPos = classData.Pos;
			SetPos.x -= 150.0f;
			SetPos.y += 400.0f;
			SetPos.z += 100.0f;

	
			if (m_nLife <= 0)
			{
				m_bDown = true;

				CScore::AddScore(-(CScore::DETH_PENALTY));

				m_nLife = 300;

				m_ResetCnt = 0;

				m_nNumPlayerAll--;

				for (int i = 0; i < GetMaxLoadPartsNum(); i++)
				{//�p�[�c��DEATH
					GetModelParts(i)->DrawOkBool(false);

					Explosion3D::Create(GetClassData().Pos);




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



			//�d��
			if (!GetIsOnGroundBool())
			{//���n��ԂłȂ���

				//�d��
				classData.move.y -= GRAVITY * 0.1f;
			}
			else
			{//���n
	//			classData.Pos.y = 0.0f;

			}
			SetClassData(classData);



			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
			//�����蔻��{��

			//�����蔻��v�Z
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

			if (m_HitData.HitAngle.y==1.0f)
			{
				bHit = true;
			}

			//�����蔻��v�Z
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);

			if (m_HitData.HitAngle.y == 1.0f)
			{
				bHit = true;
			}
			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

			classData = GetClassData();


			// �ړ�����
			// move��pos�ړ�
			// �d�͏���
			// �d�͂�pos�ړ�
			
			// �n�ʐڐG�̔���
			
			// �n�ʐڐG�̔���
			
			// �n�ʐڐG�̔���


			if (!GetIsLandingTriggerBool())
			{//���n���Ă����ԂłȂ���
				// �ڒn����
				if (bHit || classData.Pos.y <= 0.0f)
				{//�ڐG
					/*if (classData.Pos.y <= 0.0f)
					{

					}*/


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
				// �ڒn��Ԃ̉���
				SetIsOnGroundBool(false);
			}

			// ���[�V�����Đ�����
			// �󒆃��[�V�����̏���
			if (!GetIsOnGroundBool() && !GetIsLandingTriggerBool())
			{//���n��Ԃ���Ȃ������n�u�Ԃ���Ȃ�
				SetNowMotion_Parent(MOTIONTYPE_JUMP); // �󒆃��[�V�����̍Đ�
			}

			// ���n���[�V�����̃g���K�[
			if (GetIsLandingTriggerBool() && GetIsOnGroundBool())
			{//���n��Ԃ����n�u��
				SetNowMotion_Parent(MOTIONTYPE_RANDING); // ���n���[�V�����̍Đ�
				SetIsLandingTriggerBool(false); // ���n�g���K�[�����Z�b�g
			}








			SetClassData(classData);


















			classData = GetClassData();


			//�^�[�Q�b�g�̕����ɖC����������
			  //----------------------------------------------------------------------------------

			DATA ChangeData = DataInit();

			float minYAngle = -0.1f; // �����̊p�x�̌��E
			float maxYAngle = 0.1f;  // �㑤�̊p�x�̌��E


			//����
			D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, TargetPos.y, TargetPos.z) - classData.Pos;

			// XZ���ʏ�̊p�x
			float angleXZ = atan2f(enemyDirection.z, enemyDirection.x);

			ChangeData.rot.x = 0.0f; // �悶���h�����߂ɕK�v�Ȓ���
			ChangeData.rot.y = -(angleXZ + 1.57f); // ����������
			ChangeData.rot.z = 0.0f;

			//		 Y���̊p�x
			float angleY = atan2f(enemyDirection.y, sqrtf(enemyDirection.x * enemyDirection.x + enemyDirection.z * enemyDirection.z));

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


			//���`�⊮�n�_
			SetLinearInterpolation();







			//// �e�̌������l�����ĕ␳
			//float parentAngle = atan2f(g_Model.ModelParts[g_Model.ModelParts[1].PEARENT].mtxWorld._31, g_Model.ModelParts[g_Model.ModelParts[1].PEARENT].mtxWorld._11);
			//ESCROT.y -= parentAngle;

			//// �ʒu�𔽉f
			//D3DXMatrixTranslation(&mtxTrans, g_Model.ModelParts[1].Pos.x, g_Model.ModelParts[1].Pos.y - 70.0f, g_Model.ModelParts[1].Pos.z);

			//D3DXMatrixMultiply(&g_Model.ModelParts[1].mtxWorld, &g_Model.ModelParts[1].mtxWorld, &mtxTrans);


			if (classData.Pos.y<=0)
			{
				classData.Pos.y = 0;
			}


			SetClassData(classData);




			CObjectMotion::Update();//------------------�X�V

			classData = GetClassData();
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

			
			}

		}
	}
	else if (NowState == CScene::MODE_TITLE)
	{//�^�C�g��
		DATA classData = GetClassData();

		EscCntFootPrint++;
		if (EscCntFootPrint >= 5)
		{
			EscCntFootPrint = 0;
			CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z), classData.rot);
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

		EscCntFootPrint++;
		if (EscCntFootPrint >= 5)
		{
			EscCntFootPrint = 0;
			CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, -8.5f, classData.Pos.z), classData.rot);
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



}

//=============================
// �`��
//=============================
void CObjectMotionPlayer::Draw()
{
//	if (m_bDown == false)
////	{
//		for (int i = 0; i < GetMaxLoadPartsNum(); i++)
//		{//�p�[�c��DEATH
//			GetModelParts(i)->SetColorChangeBool(true);
//			GetModelParts(i)->SetChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
//		}
//
//		CObjectMotion::Draw();
//	}
//	else
//	{
//		for (int i = 0; i < GetMaxLoadPartsNum(); i++)
//		{//�p�[�c��DEATH
//			GetModelParts(i)->SetColorChangeBool(true);
//			GetModelParts(i)->SetChangeColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
//
//		}

		CObjectMotion::Draw();
//	}

#if _DEBUG

	/*if (btest == true)
	{
		const char* aData = "�ڐG";


		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);
	}
	else if (btest == false)
	{
		const char* aData = "�݂�";

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);
	}*/

	
	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "���݂�GRID/%d", (int)GetNowGRIDNum()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
	// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
	CFont::DrawTextSet(D3DXVECTOR3(1000.0f, 550.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), cData2);

#endif // 

	//char cData3[100] = {};
	//snprintf(cData3, sizeof(cData3), "���݂�tama/%d", CBullet3D::GetNumBuulet()); // ���l�𕶎���ɕϊ�����CData�ɃR�s�[
	//// mousePos.x �� mousePos.y ���}�E�X�̈ʒu
	//CFont::DrawTextSet(D3DXVECTOR3(1000.0f, 550.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), cData3);


	
}

//=============================
// ����
//=============================
CObjectMotionPlayer* CObjectMotionPlayer::Create(const char* pfilePass, DATA SetData)
{
	CObjectMotionPlayer* pObstacle = new CObjectMotionPlayer;

	pObstacle->SetFilePass(pfilePass);//�p�X�i�[
	pObstacle->SetStartPos(SetData.Pos);
	pObstacle->Init();

	// �擾
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)AABB_BOX_PLAYER, (float)AABB_BOX_PLAYER*2.5f, (float)AABB_BOX_PLAYER);
	SetData.MinLength = D3DXVECTOR3(-(float)AABB_BOX_PLAYER, 0.0f, -(float)AABB_BOX_PLAYER);
	pObstacle->SetClassData(SetData);



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



	//���ԓ_�܂ł̋���
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//�����𔼕���

	//���ԓ_�������ăf�b�h�]�[���ƍő�_�̒��ԓ_���Z�o(�ʏ���́A�����͂̔��ʕ���_)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;

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



	if (keyboard->GetPress(DIK_LSHIFT)==true)
	{//���{�^���������ꂽ
		classData.move.y += 35.0f;
	}

	if (keyboard->GetPress(DIK_LCONTROL) == true)
	{//���{�^���������ꂽ
		classData.move.y -= 3.0f;
	}


	//�ړ������Ԃ̎�
	if (bMoveNow == true)
	{
		m_nMoveCnt++;


		SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//�ړ�motion
		m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//�ړ��n���͂�ێ�

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
	else
	{//�ړ����͂Ȃ�

		int Test = GetNowMotionParent();

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
		}
		
	}

	//if (keyboard->GetTrigger(DIK_DELETE) == true)
	//{
	//	CManager* pManager = CManager::GetInstance();
	//	pManager->GetCamera()->SetShake(45, 45);
	//}

#if 1

	if (ShotDelay <= 0)
	{
		if (keyboard->GetMouseButtonPress(CInputKeyboard::MouseKey_Left))
		{//���{�^���������ꂽ

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


			float speed = 14.0f;//���x(��X�ύX)
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

			SetNowMotion_Sub(MOTIONTYPE_ATTACK);//�U��motion
			
			if (bNoShot == false)
			{

			

				CRenderer* pRenderer = nullptr;

				CManager* pManager = CManager::GetInstance();

				CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

			//	pBulletAll->SetBullet(SetData, 2, D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f), this);
				
				ShotDelay = 0;

			}



		}
	}
#else

#endif // 1


	if (m_nMoveCnt>= CObjectFootPrint::STANPFLAME)
	{
		m_nMoveCnt = 0;
		CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x,3.0f, classData.Pos.z), classData.rot);
	///	CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z));
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


	//���ԓ_�܂ł̋���
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//�����𔼕���

	//���ԓ_�������ăf�b�h�]�[���ƍő�_�̒��ԓ_���Z�o(�ʏ���́A�����͂̔��ʕ���_)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;


	bool bMoveNow = false;

	float Xdate = 0.0f;
	float Zdate = 0.0f;

	float fRotDest = 0.0f;

	bool MoveNow = false;//�ړ����͂ł��Ă邩


//	float MoveSpeed = 4.5f * 1.8f;

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


		SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//�ړ�motion

		m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//�ړ��n���͂�ێ�

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
	else
	{//�ړ����͂Ȃ�

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
			D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

			//�����̐e�̃}�g���b�N�X�����Ă�
			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);


			//Mouse�̕�����ballet���΂�
			//----------------------------------------------------------------------------------

			DATA SetData;
			SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

			D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41, pMat._42/*BULLET_SHOT_POS_Y*/, /*pMat._43*/0.0f);


			//Mouse�ŉ�ʂɎw���Ă�3D��ԍ��W�擾
			D3DXVECTOR3 TargetPos = m_TargetPos;
		//	SetData.Pos = classData.Pos;
		///	SetData.Pos.y = 150.0f;//test---------------------------------------------------------------------

			// TargetPos ���� SetData.Pos �ւ̕����x�N�g�����v�Z
			D3DXVECTOR3 direction = TargetPos - DirectionPos;

			// �����x�N�g���𐳋K���i�P�ʃx�N�g���ɂ���j
			D3DXVec3Normalize(&direction, &direction);


			float speed = 14.0f;//���x(��X�ύX)
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
				SetNowMotion_Sub(MOTIONTYPE_ATTACK);//�U��motion

				CRenderer* pRenderer = nullptr;

				CManager* pManager = CManager::GetInstance();

				CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

				pBulletAll->SetBullet(SetData, 2, D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f), this);

				ShotDelay = 3;

		//		CObjectShotFire::Create(SetData.Pos);
		//		CObjectShotFire::Create(SetData.Pos);
				bShot = true;
			}
		}
	}
#else

#endif // 1


	if (m_nMoveCnt >= CObjectFootPrint::STANPFLAME)
	{
		m_nMoveCnt = 0;
		CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z), classData.rot);
	//	CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z));
	}


	SetClassData(classData);
	























	
	






	////----------------------------------------------------------------------------------------------------------�R���g���[���[


	
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
		SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//�ړ�
		m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//�ړ��n���͂�ێ�

		m_nMoveCnt++;


		if (m_nMoveCnt >= CObjectFootPrint::STANPFLAME)
		{
			m_nMoveCnt = 0;
			CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z), classData.rot);
		//	CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z));
		}

		//float DDIIFF = 12000.0f;

		////�ʏ���͂܂œ|���Ă���
		//if (BranchPoint + DDIIFF <= joykeystate.Gamepad.sThumbLY  || -BranchPoint - DDIIFF >= joykeystate.Gamepad.sThumbLY )
		//{
		//	bNomalMove = true;//�ʏ�ړ���Ԃɂ���
		//}
		//if (BranchPoint + DDIIFF <= joykeystate.Gamepad.sThumbLX  || -BranchPoint - DDIIFF >= joykeystate.Gamepad.sThumbLX )
		//{
		//	bNomalMove = true;//�ʏ�ړ���Ԃɂ���
		//}

		//if (bNomalMove == true)
		//{//�ʏ�ړ���
		//	float fMag = 0.8f;

		//	classData.move = classData.move * fMag;
		//}
		//else
		//{
		//	float fMag = 0.4f;

		//	classData.move = classData.move * fMag;
		//}

		classData.move = D3DXVECTOR3(joykeystate.Gamepad.sThumbLX * 0.0002f, 0.0f, joykeystate.Gamepad.sThumbLY * 0.0002f);


		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
	
	
	}
	else
	{
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
		m_TargetPos.x = classData.Pos.x + vecX * 500.0f; // X�����Ɉ�苗���i��
		m_TargetPos.y = (classData.Pos.y + 150.0f) + vecY * 500.0f; // Y�����Ɉ�苗���i��
		m_TargetPos.z = 0;

	}
	else 
	{
		// �X�e�B�b�N�������̏ꍇ�̓x�N�g����0��
		vecX = 0.0f;
		vecY = 0.0f;
	}

	








//	D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float MoveSpeed2 = MOVESPEED*2.0f;

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

		//�ϊ�
		//	classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
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
		//float DDIIFF = 12000.0f;

		////�ʏ���͂܂œ|���Ă���
		//if (BranchPoint + DDIIFF <= joykeystate.Gamepad.sThumbRY || -BranchPoint - DDIIFF >= joykeystate.Gamepad.sThumbRY )
		//{
		//	bNomalMove = true;//�ʏ�ړ���Ԃɂ���
		//}
		//if (BranchPoint + DDIIFF <= joykeystate.Gamepad.sThumbRX || -BranchPoint - DDIIFF >= joykeystate.Gamepad.sThumbRX )
		//{
		//	bNomalMove = true;//�ʏ�ړ���Ԃɂ���
		//}

		m_BulletPosMove = D3DXVECTOR3(joykeystate.Gamepad.sThumbRX * 0.0015f, 0.0f, joykeystate.Gamepad.sThumbRY * 0.0015f);

		//if (bNomalMove == true)
		//{//�ʏ�ړ���
		//	float fMag = 0.8f;

		//	m_BulletPosMove = m_BulletPosMove * fMag;
		//}
		//else
		//{
		//	float fMag = 0.25f;

		//	m_BulletPosMove = m_BulletPosMove * fMag;
		//}



	//	classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);


	}
	//-------------------------------------------------------------------------------------------------------------------------


	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_A))
	{
		classData.move.y += 35.0f;
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
void CObjectMotionPlayer::SetStartPos(D3DXVECTOR3 pos)
{
	m_RESTART_POS = pos;
}
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
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

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


	float speed = 14.0f;//���x(��X�ύX)
	SetData.move = direction * speed;//���x��������


	// SetData.rot.y ���^�[�Q�b�g�̕����ɍ��킹��
	SetData.rot.x = 0.0f;
	SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
	SetData.rot.z = 0.0f;



	D3DXVECTOR3 Pos[7];

	// ���˒n�_�iSetData.Pos�j�ƏƏ��n�_�im_TargetPos�j���g����5�̒��Ԓn�_���v�Z
	D3DXVECTOR3 startPos = SetData.Pos;  // ���˒n�_
	D3DXVECTOR3 targetPos = m_TargetPos; // �Ə��n�_

	// ���˒n�_����Ə��n�_�܂ł̕����x�N�g�����v�Z
	direction = targetPos - startPos;

	// �����x�N�g����5��������
	float step = 1.0f / 6.0f; // 5�ӏ��̒��Ԓn�_���v�Z���邽�߂̃X�e�b�v�i0, 0.25, 0.5, 0.75, 1.0�j

	// 5�ӏ��̒��Ԓn�_���i�[
	for (int i = 0; i < 7; ++i) 
	{
		float t = i * step; // ���`��Ԃ̊���
		Pos[i] = startPos + direction * t; // ���`��Ԃɂ�蒆�Ԓn�_���v�Z
	}


	for (int i = 1; i < 10; ++i)
	{
	//	CObjectLINEUI::Create(Pos[i]);
	}
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

