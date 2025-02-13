//=========================================================
//
// enemy_motion_Nomalの動き[enemy_motion_Nomal.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy_motion_guard.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"
#include "line.h"
//#include "tankfootprint.h"
#include "score.h"
#include "Explosion3D.h"
#include "newbullet.h"
#include "ShotFire.h"
#include "missile.h"

int CObjectMotionEnemyGuard::m_nNumENemyAll = 0;

//=============================
// コンストラクタ
//=============================
CObjectMotionEnemyGuard::CObjectMotionEnemyGuard(int nPriority) :CObjectMotionEnemyBase(nPriority)
{
	m_nNumENemyAll++;
}
//=============================
// デストラクタ
//=============================
CObjectMotionEnemyGuard::~CObjectMotionEnemyGuard()
{
	m_nNumENemyAll--;
}

//=============================
// 初期化
//=============================
HRESULT CObjectMotionEnemyGuard::Init()
{
	CObjectMotion::Init();
	SetObjectType(CObject::OBJECT_MOTIONENEMY_BOSS_GUARD);

	m_nLife = 1000;

	float fLength[3];
	fLength[0] = 200.0f;
	fLength[1] = 200.0f;
	fLength[2] = 1100.0f;

	SetOBBLength(fLength);//OBB長さ格納

	m_nMoveCnt = 0;
	m_fRotTurret = 0.0f;
	m_nBulletDelay = BULLETSHOTDELAY;

	//ロックオン系
	m_LockOnUI = CLockOnUI::Create();
	m_LockOnUI_Main = CLockOnUIMain::Create();

	return S_OK;
}

//=============================
// 破棄
//=============================
void CObjectMotionEnemyGuard::Uninit()
{
	CScene::AddClearNum(1);

	m_LockOnUI->SetDeath(true);
	m_LockOnUI_Main->SetDeath(true);

	CObjectMotion::Uninit();
}

//=============================
// 更新
//=============================
void CObjectMotionEnemyGuard::Update()
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

			//衝突相殺--敵と
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

			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);

			classData = GetClassData();

			classData.move.x = 0.0f;
			classData.move.y = 0.0f;
			classData.move.z = 8.8f;

			//敵射撃管制
			Attack();

			DATA SetData = DataInit();
			SetData.Pos = GetClassData().Pos;
			SetData.Pos.y += LOCKDIFF;

			m_LockOnUI_Main->SetDATA(SetData);
			m_LockOnUI->SetDATA(SetData);

			//死亡時
			if (m_nLife <= 0)
			{
				//モーションセット
				SetNowMotion_Parent(MOTIONTYPE_STANDBY);
				SetNowMotion_Sub(MOTIONTYPE_STANDBY);

				classData = GetClassData();

				classData.move.y = -1;
				SetClassData(classData);

				m_nEscCnt--;

				if (m_nEscCnt < 0)
				{
					CScore::AddScore(CScore::TANK_SCORE1 * 3);

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
		else if (NowState == CScene::MODE_MOVIE)
		{
			DATA ChangeData = DataInit();

			// 変更データを反映
			SetChangeDataInObjectMotion(ChangeData);

			CObjectMotion::Update();//------------------更新
		}
		else if (NowState == CScene::MODE_MOVIE2)
		{
			m_nCntFrame++;

			DATA classData = GetClassData();

			if (m_nCntFrame >= 800 && m_nCntFrame < 1260)
			{
				classData.move.y = +0.5f;
				classData.move.z = 1.2f;

			}

			if (m_nCntFrame > 1260)
			{
				classData.move.y = 0.0f;
				classData.move.z = 0.0f;
			}

			SetClassData(classData);

			DATA ChangeData = DataInit();

			// 変更データを反映
			SetChangeDataInObjectMotion(ChangeData);

			CObjectMotion::Update();//------------------更新
		}

	}
	else
	{//待機状態
		DATA ChangeData = DataInit();

		// 変更データを反映
		SetChangeDataInObjectMotion(ChangeData);

		//モーションセット
		SetNowMotion_Parent(MOTIONTYPE_STANDBY);
		SetNowMotion_Sub(MOTIONTYPE_STANDBY);
	
		//モーション再生
		Motion_Parent();
		Motion_Sub();
	}
	

}

//=============================
// 描画
//=============================
void CObjectMotionEnemyGuard::Draw()
{
	CObjectMotion::Draw();
}

//=============================
// 生成
//=============================
CObjectMotionEnemyGuard* CObjectMotionEnemyGuard::Create(std::string pfilePass, DATA SetData)
{
	CObjectMotionEnemyGuard* pObstacle = new CObjectMotionEnemyGuard;

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
void CObjectMotionEnemyGuard::Attack()
{
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_fRotTurret, 0.0f, 0.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//自分の親のマトリックス欠けてる
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

	D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//砲弾射出口	



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

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&EscMtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_fRotTurret, 0.0f, 0.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -210.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

		//自分の親のマトリックス欠けてる
		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

		D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//砲弾射出口	

		SETDATA.Pos = SetPos;
		SETDATA.rot.y = m_fRotTurret;

		D3DXVECTOR3 BulletMim = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
		D3DXVECTOR3 BulletMax = D3DXVECTOR3(30.0f, 30.0f, 30.0f);


		//射撃地点埋もれてないか
		bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_NOMAL, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_NOMAL, SETDATA.Pos, BulletMim, BulletMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
		}

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_NOMAL, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D);
		}

		//射撃
		if (bNoShot == false)
		{
			// 現在の砲塔位置からの発射時砲弾moveベクトル
			D3DXVECTOR3 direction = D3DXVECTOR3(EscData.Pos.x, EscData.Pos.y, EscData.Pos.z) - SetPos;
			D3DXVec3Normalize(&direction, &direction); // 方向ベクトルを正規化

			// バレットの速さをかけてベクトルを修正
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
// 砲塔旋回
//==================================
void CObjectMotionEnemyGuard::TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	// クラスデータを取得
	DATA classData = GetClassData();
	DATA ChangeData = DataInit();

	// 目標方向を計算
	D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, 0.0f, TargetPos.z) - D3DXVECTOR3(classData.Pos.x, 0.0f, classData.Pos.z);

	// XZ平面上の目標角度を計算
	float targetAngleXZ = atan2f(enemyDirection.z, -enemyDirection.x) + (D3DX_PI * 0.5f);

	// 現在の砲塔のXZ平面上の角度
	float currentAngleXZ = m_fRotTurret;


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

	m_fRotTurret = currentAngleXZ;


	// 変更データを反映
	SetChangeDataInObjectMotion(ChangeData);

}

//==================================
// 牽制射撃
//==================================
void CObjectMotionEnemyGuard::ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	//動くモデルのデータ
	CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

	D3DXMATRIX pMat = pParts->GetMtxWorld();

	D3DXMATRIX EscMtxWorld;

	D3DXMATRIX mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&EscMtxWorld);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//自分の親のマトリックス欠けてる
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);


	//指定の方向にballetを飛ばす
	//----------------------------------------------------------------------------------

	DATA SetData;
	SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

	D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41,/* pMat._42*/BULLET_SHOT_POS_Y, pMat._43);

	ShotPos.y = BULLET_SHOT_POS_Y;

	// TargetPos から SetData.Pos への方向ベクトルを計算
	D3DXVECTOR3 direction = ShotPos - DirectionPos;

	// 方向ベクトルを正規化（単位ベクトルにする）
	D3DXVec3Normalize(&direction, &direction);


	float speed = 12.0f;//速度(後々変更)
	SetData.move = direction * speed;//速度をかける


	// SetData.rot.y をターゲットの方向に合わせる
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
		//	SetNowMotion_Sub(2);//攻撃motion

		//	CBullet3D::Create(SetData,0);//クリエイト
	}
}
