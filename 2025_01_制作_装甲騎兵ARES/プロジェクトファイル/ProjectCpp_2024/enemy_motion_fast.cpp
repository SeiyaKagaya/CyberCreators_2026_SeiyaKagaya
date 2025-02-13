//=========================================================
//
// enemy_motion_fastの動き[enemy_motion_fast.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy_motion_fast.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"
#include "line.h"
//#include "tankfootprint.h"
#include "ShotFire.h"
#include "score.h"
#include "Explosion3D.h"
#include "newbullet.h"
//#include "movesmoke.h"
#include "missile.h"
#include "shadow.h"

//=============================
// コンストラクタ
//=============================
CObjectMotionEnemyfast::CObjectMotionEnemyfast(int nPriority) :CObjectMotionEnemyBase(nPriority)
{
}

//=============================
// デストラクタ
//=============================
CObjectMotionEnemyfast::~CObjectMotionEnemyfast()
{
}

//=============================
// 初期化
//=============================
HRESULT CObjectMotionEnemyfast::Init()
{
	CObjectMotion::Init();
	SetObjectType(CObject::OBJECT_MOTIONENEMY_FAST);

	m_nLife = 100;

	float fLength[3];
	fLength[0] = 110.0f;
	fLength[1] = 70.0f;
	fLength[2] = 110.0f;

	SetOBBLength(fLength);//OBB長さ格納

	m_nMoveCnt = 0;
	m_fRotTurret = 0.0f;
	m_BulletDelay = BULLETSHOTDELAY;

	//ロックオンUI系
	m_LockOnUI = CLockOnUI::Create();
	m_LockOnUI_Main = CLockOnUIMain::Create();
	
	return S_OK;
}

//=============================
// 破棄
//=============================
void CObjectMotionEnemyfast::Uninit()
{
	m_LockOnUI->SetDeath(true);
	m_LockOnUI_Main->SetDeath(true);
	CObjectMotion::Uninit();
}

//=============================
// 更新
//=============================
void CObjectMotionEnemyfast::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();

	if (CScene::GetStayNextStage() == false)
	{//待機状態か
		if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3)
		{//ゲーム中

			for (int i = 0; i < GetMaxLoadPartsNum(); i++)
			{
				GetModelParts(i)->ChengeRGBAbool(true, D3DXCOLOR(0.3f, 0.1f, 0.3f, 1.0f));
			}

			CRenderer* pRenderer = nullptr;
			CManager* pManager = CManager::GetInstance();

			CObjectMotion::Update();//----------------

			DATA classData = GetClassData();


			//衝突相殺--敵と
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

			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);

			classData = GetClassData();

			//敵射撃管制
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

			SetClassData(classData);


			//ダメージ演出
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

			D3DXVECTOR3 SetPos = GetClassData().Pos;
			SetPos.y += 6.0f;
			CShadow::Create(SetPos,true);
		}
		else if (NowState == CScene::MODE_MOVIE|| NowState == CScene::MODE_MOVIE2)
		{//
			DATA ChangeData = DataInit();
		
			// 変更データを反映
			SetChangeDataInObjectMotion(ChangeData);

			CObjectMotion::Update();//------------------更新

			//モーション格納
			SetNowMotion_Parent(MOTIONTYPE_STANDBY);
			SetNowMotion_Sub(MOTIONTYPE_STANDBY);

			D3DXVECTOR3 SetPos = GetClassData().Pos;
			SetPos.y += 6.0f;
			CShadow::Create(SetPos,true);
		}
	}
	else
	{//待機状態
		DATA ChangeData = DataInit();

		// 変更データを反映
		SetChangeDataInObjectMotion(ChangeData);

		SetNowMotion_Parent(MOTIONTYPE_STANDBY);
		SetNowMotion_Sub(MOTIONTYPE_STANDBY);

		Motion_Parent();
		Motion_Sub();

		D3DXVECTOR3 SetPos = GetClassData().Pos;
		SetPos.y += 6.0f;
		CShadow::Create(SetPos,true);
	}
}

//=============================
// 描画
//=============================
void CObjectMotionEnemyfast::Draw()
{
	CObjectMotion::Draw();
}

//=============================
// 生成
//=============================
CObjectMotionEnemyfast* CObjectMotionEnemyfast::Create(std::string pfilePass, DATA SetData)
{
	CObjectMotionEnemyfast* pObstacle = new CObjectMotionEnemyfast;

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
void CObjectMotionEnemyfast::Attack()
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

	if (m_BulletDelay <= 0)
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


		//射撃地点がうもれていないか
		//-----------------------------------------------
		bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_FAST, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_FAST, SETDATA.Pos, BulletMim, BulletMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
		}

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONENEMY_FAST, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D);
		}
		//-----------------------------------------------
		
		//射撃
		if (bNoShot == false)
		{
			// 現在の砲塔位置からの発射時砲弾moveベクトル
			D3DXVECTOR3 direction =  D3DXVECTOR3(EscData.Pos.x, EscData.Pos.y, EscData.Pos.z)- SetPos;
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

			m_BulletDelay = BULLETSHOTDELAY;
		}
	}
	else
	{
		m_BulletDelay--;
	}

}

//==================================
// 砲塔旋回
//==================================
void CObjectMotionEnemyfast::TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	DATA ChangeData = DataInit(); 
	DATA classData = GetClassData();

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

	float minYAngle = -1.1f; // 下側の角度の限界
	float maxYAngle = 1.1f;  // 上側の角度の限界

	//方向
	enemyDirection = D3DXVECTOR3(TargetPos.x, TargetPos.y+270.0f, TargetPos.z) - D3DXVECTOR3(classData.Pos.x, classData.Pos.y, classData.Pos.z);

	// XZ平面上の角度
	float angleXZ = atan2f(enemyDirection.z, enemyDirection.x);

	ChangeData.rot.x = 0.0f; // よじりを防ぐために必要な調整
	ChangeData.rot.y = -(angleXZ + 1.57f); // 腰を向ける
	ChangeData.rot.z = 0.0f;

	//		 Y軸の角度
	float angleY = (atan2f(enemyDirection.y, sqrtf(enemyDirection.x * enemyDirection.x + enemyDirection.z * enemyDirection.z)) - (D3DX_PI * 0.124f));

	// Y軸角度をクランプ
	if (angleY < minYAngle)
	{
		angleY = minYAngle;
	}
	else if (angleY > maxYAngle)
	{
		angleY = maxYAngle;
	}

	ChangeData.rot.x = angleY; // Y方向を向ける


		// 変更データを反映
	SetChangeDataInObjectMotion(ChangeData);
}

//==================================
// 牽制射撃
//==================================
void CObjectMotionEnemyfast::ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
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

	}
}
