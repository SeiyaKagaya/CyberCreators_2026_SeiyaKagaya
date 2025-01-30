//=========================================================
//
// enemy_motion_Nomalの動き[enemy_motion_Nomal.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy_motion_boss.h"
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
#include "enemy_motion_guard.h"
#include "enemy_motion_Nomal.h"
//#include "movesmoke.h"

int CObjectMotionEnemyBoss::m_nNumENemyAll = 0;

//=============================
// コンストラクタ
//=============================
CObjectMotionEnemyBoss::CObjectMotionEnemyBoss(int nPriority) :CObjectMotionEnemyBase(nPriority)
{
	m_nNumENemyAll++;
}
//=============================
// デストラクタ
//=============================
CObjectMotionEnemyBoss::~CObjectMotionEnemyBoss()
{
	m_nNumENemyAll--;
}

//=============================
// 初期化
//=============================
HRESULT CObjectMotionEnemyBoss::Init()
{
	CObjectMotion::Init();
	SetObjectType(CObject::OBJECT_MOTIONENEMY_BOSS);

	//	LoadRouteTable();

	m_nLife = 1000;

	float fLength[3];
	fLength[0] = 300.0f;
	fLength[1] = 200.0f;
	fLength[2] = 1300.0f;

	SetOBBLength(fLength);//OBB長さ格納

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
// 破棄
//=============================
void CObjectMotionEnemyBoss::Uninit()
{
	CScene::AddClearNum(1);

	m_LockOnUI->SetDeath(true);
	m_LockOnUI_Main->SetDeath(true);

	CObjectMotion::Uninit();
}

//=============================
// 更新
//=============================
void CObjectMotionEnemyBoss::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();

	if (CScene::GetStayNextStage() == false)
	{//待機状態か

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
			//Attack();

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
						{ // 先頭がない==プライオリティまるっとない
							pMissile->KillMissileTarget(this);
						}
					}

					CScore::AddScore(CScore::TANK_SCORE1);

					SetDeath(true);

					Explosion3D::Create(GetClassData().Pos);
					for (int i = 0; i < GetMaxLoadPartsNum(); i++)
					{//パーツもDEATH
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

			// 変更データを反映
			SetChangeDataInObjectMotion(ChangeData);


			CObjectMotion::Update();//------------------更新

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
	{//待機状態
		DATA ChangeData = DataInit();

		// 変更データを反映
		SetChangeDataInObjectMotion(ChangeData);

		SetNowMotion_Parent(MOTIONTYPE_STANDBY);
		SetNowMotion_Sub(MOTIONTYPE_STANDBY);
		//CObjectMotion::Update();
		Motion_Parent();
		Motion_Sub();


	}
}

//=============================
// 描画
//=============================
void CObjectMotionEnemyBoss::Draw()
{
	CObjectMotion::Draw();
	m_pShield->Draw();
}

//=============================
// 生成
//=============================
CObjectMotionEnemyBoss* CObjectMotionEnemyBoss::Create(std::string pfilePass, DATA SetData)
{
	CObjectMotionEnemyBoss* pObstacle = new CObjectMotionEnemyBoss;

	pObstacle->SetFilePass(pfilePass);//パス格納

	pObstacle->Init();
	// 取得
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)(CObjectMotionEnemyBase::AABB_BOX), (float)(CObjectMotionEnemyBase::AABB_BOX) * 2.0f, (float)(CObjectMotionEnemyBase::AABB_BOX));
	SetData.MinLength = D3DXVECTOR3(-(float)(CObjectMotionEnemyBase::AABB_BOX), 0.0f, -(float)(CObjectMotionEnemyBase::AABB_BOX));
	pObstacle->SetClassData(SetData);

	return pObstacle;
}


//=============================
// 攻撃ロジック
//=============================
void CObjectMotionEnemyBoss::Attack()
{
	DATA TargetData = DataInit();

	//砲塔の位置に基づく砲弾発射口の位置----------------------------------------------+-----------------
	//動くモデルのデータ
	CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

	D3DXMATRIX pMat = pParts->GetMtxWorld();

	D3DXMATRIX EscMtxWorld;

	D3DXMATRIX mtxTrans, mtxRot;//計算用マトリックス

	DATA pEscDATA = pParts->GetDATA();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&EscMtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, fRotTurret, 0.0f, 0.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//自分の親のマトリックス欠けてる
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

	D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//砲弾射出口	
	//-----------------------------------------------------------------------------------------------

	//+エリアに対し跳弾予測射撃

	//+精密予測照準射撃

	//----------------------------------------------------------------------------------
	//playerの位置を取得
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

	//照準位置に基づき
	TurretRotation(SetPos, EscData.Pos, TargetData.move);
	//----------------------------------------------------------------------------------

	if (m_nBulletDelay <= 0)
	{
		DATA SETDATA = CObject::DataInit();

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&EscMtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, fRotTurret, 0.0f, 0.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -210.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

		//自分の親のマトリックス欠けてる
		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

		D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//砲弾射出口	

		SETDATA.Pos = SetPos;
		SETDATA.rot.y = fRotTurret;

		D3DXVECTOR3 BulletMim = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
		D3DXVECTOR3 BulletMax = D3DXVECTOR3(30.0f, 30.0f, 30.0f);



		bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_NOMAL, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);



		// 現在の砲塔位置からの発射時砲弾moveベクトル
		D3DXVECTOR3 direction = D3DXVECTOR3(EscData.Pos.x, EscData.Pos.y, EscData.Pos.z) - SetPos;
		D3DXVec3Normalize(&direction, &direction); // 方向ベクトルを正規化

		// バレットの速さをかけてベクトルを修正
		D3DXVECTOR3 BulletMoveIF = direction * BULLETMOVESPEED_NOMAL;

		SETDATA.move = BulletMoveIF;

		CRenderer* pRenderer = nullptr;

		CManager* pManager = CManager::GetInstance();


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
	else
	{
		m_nBulletDelay--;
	}
}

//==================================
// 砲塔旋回
//==================================
void CObjectMotionEnemyBoss::TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	// クラスデータを取得
	DATA classData = GetClassData();
	DATA ChangeData = DataInit();

	// 目標方向を計算
	D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, 0.0f, TargetPos.z) - D3DXVECTOR3(classData.Pos.x, 0.0f, classData.Pos.z);

	// XZ平面上の目標角度を計算
	float targetAngleXZ = atan2f(enemyDirection.z, -enemyDirection.x) + (D3DX_PI * 0.5f);

	// 現在の砲塔のXZ平面上の角度
	float currentAngleXZ = fRotTurret;


	// 角度を範囲内に収める
	targetAngleXZ = fmodf(targetAngleXZ + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

	// 角度の差分
	float rotDiff = targetAngleXZ - currentAngleXZ;

	// 差分が範囲外なら補正---------------------------------------------------------------近いうちちゃんと内容調べる
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

	fRotTurret = currentAngleXZ;


	// 変更データを反映
	SetChangeDataInObjectMotion(ChangeData);
}
