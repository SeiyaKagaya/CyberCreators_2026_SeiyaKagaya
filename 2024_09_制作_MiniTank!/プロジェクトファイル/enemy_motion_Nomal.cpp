//=========================================================
//
// enemy_motion_Nomalの動き[enemy_motion_Nomal.cpp]
// Author seiya kagaya
//
//=========================================================
#include "enemy_motion_Nomal.h"
#include "renderer.h"
#include "manager.h"
#include "player_motion.h"
#include "line.h"
#include "tankfootprint.h"
#include "ShotFire.h"
#include "score.h"
#include "Explosion3D.h"
#include "newbullet.h"
#include "movesmoke.h"

//=============================
// コンストラクタ
//=============================
CObjectMotionEnemyNomal::CObjectMotionEnemyNomal(int nPriority) :CObjectMotionEnemyBase(nPriority)
{
}

//=============================
// デストラクタ
//=============================
CObjectMotionEnemyNomal::~CObjectMotionEnemyNomal()
{
}

//=============================
// 初期化
//=============================
HRESULT CObjectMotionEnemyNomal::Init()
{
	CObjectMotion::Init();
	SetObjectType(CObject::OBJECT_MOTIONENEMY_NOMAL);

	m_nLife = LIFE;
	float fLength[3];
	fLength[0] = OBB_LENGTH[0];
	fLength[1] = OBB_LENGTH[1];
	fLength[2] = OBB_LENGTH[2];

	SetOBBLength(fLength);//OBB長さ格納

	m_nMoveCnt = 0;
	fRotTurret = 0.0f;
	m_BulletDelay = BULLETSHOTDELAY;
	return S_OK;
}

//=============================
// 破棄
//=============================
void CObjectMotionEnemyNomal::Uninit()
{
	CObjectMotion::Uninit();
}

//=============================
// 更新
//=============================
void CObjectMotionEnemyNomal::Update()
{
	for (int i = 0; i < GetMaxLoadPartsNum(); i++)
	{
		GetModelParts(i)->ChengeRGBAbool(true, ENEMY_COLOR);
	}

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();

	CObjectMotion::Update();

	DATA classData = GetClassData();

	//相手、自分のGRID番号がかわったか
	bool bChange = false;


	//playerの位置を取得
	CObject* pObj = nullptr;
	pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	D3DXVECTOR3 TargetPos = {};

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);

		CObject::DATA EscData;

		EscData = pPlayer->GetClassData();

		TargetPos = EscData.Pos;//注視点

		if (m_OldTargetGRIDNum != pPlayer->GetNowGRIDNum())
		{//過去の相手位置番号といまの相手位置番号が一緒じゃない時
			//格納
			m_OldTargetGRIDNum = pPlayer->GetNowGRIDNum();
			bChange = true;
		}
	}

	//移動先制定
	//---------------------------------------------------------------------------------------------------------------------------------
	if (m_OldMyGRIDNum!=GetNowGRIDNum())
	{//自分の過去の位置番号と現在の位置番号が違うとき
		//格納
		m_OldMyGRIDNum = GetNowGRIDNum();
		bChange = true;
	}

	if (bChange == true)
	{//両者どちらかの位置番号に変更があった時
		CMathProc::Point pPoint;

		int NextMoveGridNum = CMathProc::GetNextMoveGridNum(m_OldTargetGRIDNum, m_OldMyGRIDNum);//次の経由地
		
		NowMoveGRIDNum = NextMoveGridNum;


		//移動先制定の補佐------
		pPoint = CMathProc::GetPointfromObjectNum(NextMoveGridNum);

		if (pPoint.x == CMathProc::GetPointfromObjectNum(m_OldTargetGRIDNum).x && pPoint.y == CMathProc::GetPointfromObjectNum(m_OldTargetGRIDNum).y)
		{//ゴールが目前
			classData.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		else
		{
			//目標位置位置を次の目標GRIDD位置
			m_TargetPos = D3DXVECTOR3((float)((CMathProc::GRIDLEGTH)*pPoint.x) + (CMathProc::GRIDLEGTH * 0.5f), 0.0f, (float)((CMathProc::GRIDLEGTH)*pPoint.y) + (CMathProc::GRIDLEGTH * 0.5f));
			SetNowMotion_Parent(1);//移動motion
		}
	}
	//移動先制定ここまで
	//---------------------------------------------------------------------------------------------------------------------------------

	// ターゲット位置への移動処理
	D3DXVECTOR3 direction = m_TargetPos - classData.Pos; // 方向ベクトル

	float distance = D3DXVec3Length(&direction); // ターゲットまでの距離

	if (distance > 1.0f) // 近すぎない場合にのみ移動
	{
		D3DXVec3Normalize(&direction, &direction); // 方向ベクトルの正規化

		float MoveSpeed = MOVESPEED;//移動速度

		// 移動
		classData.move.x = direction.x * MoveSpeed;
		classData.move.z = direction.z * MoveSpeed;


		// 目標方向の計算
		float targetAngle = atan2f(direction.x, direction.z);

		//角度変動
		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, targetAngle + D3DX_PI);

		m_nMoveCnt++;

		if (m_nMoveCnt >= STAMPCNT)
		{
			m_nMoveCnt = 0;
			CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, POSY, classData.Pos.z), classData.rot);
			//CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z));
		}
	}
	else
	{
		// ターゲット位置に近すぎる場合は移動を停止
		classData.move.x = 0.0f;
		classData.move.z = 0.0f;
	}
	
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

	//-----------------------------------------被弾系
	for (int i = 0; i < CNewBulletALL::MAXBULLETALL; i++)
	{
		CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

		CNewBullet* pBullet = pBulletAll->GetBulletData(i);

		if (pBullet->GetbUse() == true)
		{
			if (pBullet->GetHitEscapeTime() <= 0)
			{//自爆抑制以降の時

				COBB pObb2 = pBullet->GetOBB();
				COBB MyObb = GetOBB();

				D3DXVECTOR3 HitPos;
				bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//当たり判定

				if (btest == true)
				{
					//pBullet->SetDeath(true);
					pBullet->SetGoodby();

					m_nLife -= DAMAGE;
				}
			}
			else
			{//抑制期間
				if (pBullet->GetCaller() != this)
				{//発射した親が自身じゃないとき
					COBB pObb2 = pBullet->GetOBB();
					COBB MyObb = GetOBB();

					D3DXVECTOR3 HitPos;
					bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//当たり判定

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

	//敵射撃管制
	Attack();

	if (m_nLife <= 0)
	{
		CScore::AddScore(CScore::TANK_SCORE1);

		SetDeath(true);

		Explosion3D::Create(GetClassData().Pos);

		for (int i = 0; i < GetMaxLoadPartsNum(); i++)
		{//パーツもDEATH
			GetModelParts(i)->SetDeath(true);
		}
	}

	SetClassData(classData);
}

//=============================
// 描画
//=============================
void CObjectMotionEnemyNomal::Draw()
{
	CObjectMotion::Draw();
}

//=============================
// 生成
//=============================
CObjectMotionEnemyNomal* CObjectMotionEnemyNomal::Create(const char* pfilePass, DATA SetData)
{
	CObjectMotionEnemyNomal* pObstacle = new CObjectMotionEnemyNomal;

	pObstacle->SetFilePass(pfilePass);//パス格納

	pObstacle->Init();
	// 取得
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = (float)RADIUS;
	SetData.MaxLength = D3DXVECTOR3((float)(CObjectMotionEnemyBase::AABB_BOX), (float)(CObjectMotionEnemyBase::AABB_BOX)*2.0f, (float)(CObjectMotionEnemyBase::AABB_BOX));
	SetData.MinLength = D3DXVECTOR3(-(float)(CObjectMotionEnemyBase::AABB_BOX), 0.0f, -(float)(CObjectMotionEnemyBase::AABB_BOX));
	pObstacle->SetClassData(SetData);

	return pObstacle;
}

//=============================
// 攻撃ロジック
//=============================
void CObjectMotionEnemyNomal::Attack()
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
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, TANKFIRE_OFFSETPOS_Z);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//自分の親のマトリックス欠けてる
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

	D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//砲弾射出口	
	//-----------------------------------------------------------------------------------------------

	DATA classData = GetClassData();

	D3DXVECTOR3 PlayerPos = {};
	float MaxLength = 2200.0f;

	// 配置物プライオリティの先頭を取得
	CObject* pObject = CObject::GetpTop(CObject::LAYERINDEX_MOTIONPLAYER);

	if (pObject != nullptr)
	{ // 先頭がない==プライオリティまるっとない

		if (pObject->GetObjectType() == CObject::OBJECT_MOTIONPLAYER)
		{ // 対象のモデルのとき

			D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			CObject::DATA EscData;

			// ここで使用分宣言
			CObjectMotionPlayer* pMotionPlayer;

			pMotionPlayer = (CObjectMotionPlayer*)pObject;


			EscData = pMotionPlayer->GetClassData();

			PlayerPos = EscData.Pos;



			// 各成分の差を計算
			float dx = PlayerPos.x - classData.Pos.x;
			float dy = PlayerPos.y - classData.Pos.y;
			float dz = PlayerPos.z - classData.Pos.z;

			// 距離を計算
			MaxLength = (float)fabs(sqrtf(dx * dx + dy * dy + dz * dz)) + 2.0f;

		}
	}

	//ここで壁に遮られてるか判断--------------------------------------
	CMathProc::CollisionData HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, PlayerPos, MaxLength, CObject::OBJECT_OBSTACLE, CObject::LAYERINDEX_OBSTACLE);

	if (HitData.bHit == false)
	{
		HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, PlayerPos, MaxLength, CObject::OBJECT_HITBOX, CObject::LAYERINDEX_HITBOX);
	}

	if (HitData.bHit == false)
	{
		HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, PlayerPos, MaxLength, CObject::OBJECT_MOTIONENEMY_NOMAL, CObject::LAYERINDEX_MOTIONENEMY_NOMAL);
	}

	if (HitData.bHit == false)
	{//射線通ってる

#if _DEBUG

		Cline::Create(SetPos, PlayerPos, D3DXCOLOR(1, 0, 0, 1));//相手までライン
#else
#endif

		//直接照準における砲弾命中地点予測
		TargetData = phase1(SetPos);
	}
	else
	{//遮られてる時

#if _DEBUG

		Cline::Create(SetPos, HitData.ContactPoint, D3DXCOLOR(1, 0, 0, 1));//衝突地点までライン
#else
#endif
		TargetData.Pos = CMathProc::GetShotPos(classData.Pos);

		//ここで壁に遮られてるか判断--------------------------------------
		CMathProc::CollisionData HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, TargetData.Pos, MaxLength, CObject::OBJECT_OBSTACLE, CObject::LAYERINDEX_OBSTACLE);

		if (HitData.bHit == false)
		{
			HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, TargetData.Pos, MaxLength, CObject::OBJECT_HITBOX, CObject::LAYERINDEX_HITBOX);
		}

		if (HitData.bHit == false)
		{
			HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, TargetData.Pos, MaxLength, CObject::OBJECT_MOTIONENEMY_NOMAL, CObject::LAYERINDEX_MOTIONENEMY_NOMAL);
		}

		if (HitData.bHit == false)
		{//射線通ってる
		}
		else
		{
			// StatRot.yは角度（ラジアン）で与えられると仮定
			// 回転角度に基づいて進行方向の単位ベクトルを計算
			float dirX = cosf(classData.rot.y + D3DX_PI*0.5f);
			float dirZ = -sinf(classData.rot.y + D3DX_PI*0.5f);

			// 進行距離ベクトルを計算
			D3DXVECTOR3 directionVectorESC = D3DXVECTOR3(dirX, 0.0f, dirZ) * TARGETSPEED;

			// 新しい座標を計算
			D3DXVECTOR3 destinationESC = SetPos + directionVectorESC;
			TargetData.Pos = destinationESC;
		}
	}

	//+エリアに対し跳弾予測射撃

	//+精密予測照準射撃


	//照準位置に基づき
	TurretRotation(SetPos, TargetData.Pos, TargetData.move);


	if (m_BulletDelay <= 0)
	{

		if (HitData.bHit == false)//------------------------------------------------------------------------------//NOMALはここのみ
		{//射線通ってる

			DATA SETDATA = CObject::DataInit();

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&EscMtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, fRotTurret, 0.0f, 0.0f);

			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);


			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, TANKFIRE_OFFSETPOS_Z);

			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

			//自分の親のマトリックス欠けてる
			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

			D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//砲弾射出口	

			SETDATA.Pos = SetPos;
			SETDATA.rot.y = fRotTurret;

			D3DXVECTOR3 BulletMim = D3DXVECTOR3(-BULLETSIZE, -BULLETSIZE, -BULLETSIZE);
			D3DXVECTOR3 BulletMax = D3DXVECTOR3(BULLETSIZE, BULLETSIZE, BULLETSIZE);

			//食い込み防止
			bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

			if (bNoShot == false)
			{
				bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SETDATA.Pos, BulletMim, BulletMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
			}

			if (bNoShot == false)
			{


				// 現在の砲塔位置からの発射時砲弾moveベクトル
				D3DXVECTOR3 direction = SetPos - D3DXVECTOR3(classData.Pos.x, EscMtxWorld._42, classData.Pos.z);
				D3DXVec3Normalize(&direction, &direction); // 方向ベクトルを正規化

				// バレットの速さをかけてベクトルを修正
				D3DXVECTOR3 BulletMoveIF = direction * MOVESPEED2;

				SETDATA.move = BulletMoveIF;


				CRenderer* pRenderer = nullptr;

				CManager* pManager = CManager::GetInstance();

				CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

				pBulletAll->SetBullet(SETDATA, 0, BULLET_COLOR, this);

				//CBullet3D::Create(SETDATA, reflectNum, D3DXCOLOR(0.2f, 0.5f, 0.5f, 0.25f), this);

				CObjectShotFire::Create(SETDATA.Pos);
				CObjectShotFire::Create(SETDATA.Pos);

				m_BulletDelay = BULLETSHOTDELAY;
			}
		}
	}
	else
	{
		m_BulletDelay--;
	}

	//	}
#if _DEBUG

	//敵照準位置(目標)
	//----------------------------------------------------------------------
	Cline::Create(SetPos, TargetData.Pos, D3DXCOLOR(1, 1, 1, 1));
	float TargetSin = 50.0f;
	Cline::Create(D3DXVECTOR3(TargetData.Pos.x - TargetSin, TargetData.Pos.y, TargetData.Pos.z - TargetSin), D3DXVECTOR3(TargetData.Pos.x + TargetSin, TargetData.Pos.y, TargetData.Pos.z + TargetSin), D3DXCOLOR(1, 1, 1, 1));
	Cline::Create(D3DXVECTOR3(TargetData.Pos.x - TargetSin, TargetData.Pos.y, TargetData.Pos.z + TargetSin), D3DXVECTOR3(TargetData.Pos.x + TargetSin, TargetData.Pos.y, TargetData.Pos.z - TargetSin), D3DXCOLOR(1, 1, 1, 1));
	//----------------------------------------------------------------------

	// StatRot.yは角度（ラジアン）で与えられると仮定
   // 回転角度に基づいて進行方向の単位ベクトルを計算
	float dirX = cosf(fRotTurret + D3DX_PI*0.5f);
	float dirZ = -sinf(fRotTurret + D3DX_PI*0.5f);

	// 進行距離ベクトルを計算
	D3DXVECTOR3 directionVector = D3DXVECTOR3(dirX, 0.0f, dirZ) * TARGETSPEED;

	// 新しい座標を計算
	D3DXVECTOR3 destination = SetPos + directionVector;

	Cline::Create(SetPos, destination, D3DXCOLOR(1, 0, 1, 1));
	Cline::Create(SetPos, destination, D3DXCOLOR(1, 0, 1, 1));
#else

#endif // _DE
}

//=============================
// フェーズ１
//=============================
CObject::DATA CObjectMotionEnemyNomal::phase1(D3DXVECTOR3 ShotPos)
{
	// クラスデータを取得
	DATA classData = GetClassData();

	// 砲弾射出口の初期位置
	D3DXVECTOR3 SetPos = ShotPos;

	// 現在の砲塔位置からの発射時砲弾moveベクトル
	D3DXVECTOR3 direction = SetPos - D3DXVECTOR3(classData.Pos.x, 0.0f, classData.Pos.z);
	D3DXVec3Normalize(&direction, &direction); // 方向ベクトルを正規化

	// バレットの速さをかけてベクトルを修正
	D3DXVECTOR3 BulletMoveIF = direction * MOVESPEED2;

	// プレイヤーの位置を取得
	CObject* pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	D3DXVECTOR3 TargetPos = {};
	D3DXVECTOR3 TargetMove = {};

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);
		CObject::DATA EscData = pPlayer->GetClassData();

		TargetPos = EscData.Pos; // 注視点
		TargetMove = pPlayer->GetNowMove();
	}

	// 自分の方向に向かってくる場合の処理を追加
	D3DXVECTOR3 relativePos = SetPos - TargetPos;
	D3DXVECTOR3 relativeVel = BulletMoveIF - TargetMove;
	float timeToIntersection = -D3DXVec3Dot(&relativePos, &relativeVel) / D3DXVec3LengthSq(&relativeVel);

	// timeToIntersectionが負またはゼロの場合の修正
	if (timeToIntersection <= 0)
	{
		timeToIntersection = 0.01f; // 最小の正の時間を設定
	}

	// 相手の予測位置（交差点）を計算
	D3DXVECTOR3 predictedIntersection = TargetPos + TargetMove * timeToIntersection;

	// 方向ベクトルを再計算
	//相手の予測位置と弾丸発射地点の差分
	D3DXVECTOR3 nESC = predictedIntersection - SetPos;

	D3DXVec3Normalize(&direction, &nESC);
	BulletMoveIF = direction * MOVESPEED2;

	// 照準位置とバレットの移動ベクトルを返す
	CObject::DATA EscDATA;
	EscDATA.Pos = predictedIntersection;
	EscDATA.move = BulletMoveIF;

	return EscDATA;
}

//=============================
// フェーズ2
//=============================
CObject::DATA CObjectMotionEnemyNomal::phase2()
{
	//-3.14から3.14までの方角に一定間隔で仮説で打ち込み弾の寿命までに一番近かったものを保存しておき発泡する
	//跳弾はn回/弾の速度はMOVESPEED2/寿命は跳弾限界時

	float calculationRot=D3DX_PI*0.999f;

	// クラスデータを取得
	DATA classData = GetClassData();

	//砲塔の位置に基づく砲弾発射口の位置--------------------------------------------------------------
	//動くモデルのデータ
	CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

	D3DXMATRIX pMat = pParts->GetMtxWorld();

	D3DXMATRIX EscMtxWorld;

	D3DXMATRIX mtxTrans, mtxRot;//計算用マトリックス

	DATA pEscDATA = pParts->GetDATA();

	//------------------------------------------------------------------------
	bool bOk = false;

	float GoodRot = 0.0f;
	float GoodRength = 99999.0f;
	//int GoodFrame = 999;

	typedef struct
	{
		D3DXVECTOR3 Pos1;
		D3DXVECTOR3 Pos2;
	}ESCLINE;

	ESCLINE ESCLine[3] = {};
	

	// プレイヤーの位置を取得
	CObject* pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MOTIONPLAYER, CObject::OBJECT_MOTIONPLAYER);

	D3DXVECTOR3 TargetPos = {};
	D3DXVECTOR3 TargetMove = {};

	if (pObj != nullptr)
	{
		CObjectMotionPlayer* pPlayer = static_cast<CObjectMotionPlayer*>(pObj);
		CObject::DATA EscData = pPlayer->GetClassData();

		TargetPos = EscData.Pos; // 注視点
		TargetMove = pPlayer->GetNowMove();
	}



	while (bOk == false)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&EscMtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, calculationRot, 0.0f, 0.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxRot);


		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, TANKFIRE_OFFSETPOS_Z);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

		//自分の親のマトリックス欠けてる
		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);


		D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//砲弾射出口	
		D3DXVECTOR3 SetOldPos = SetPos;

		bool bBulletUpdate = false;
		int UpdateLifeCnt = 0;
		D3DXVECTOR3 Min = D3DXVECTOR3(-BULLETSIZE, -BULLETSIZE, -BULLETSIZE);
		D3DXVECTOR3 Max = D3DXVECTOR3(BULLETSIZE, BULLETSIZE, BULLETSIZE);

		int EscReflect = CNewBullet::NEWMAXREFLECTION -1;

		// 現在の砲塔位置からの発射時砲弾moveベクトル
		D3DXVECTOR3 direction = SetPos - D3DXVECTOR3(classData.Pos.x, EscMtxWorld._42, classData.Pos.z);
		D3DXVec3Normalize(&direction, &direction); // 方向ベクトルを正規化

		// バレットの速さをかけてベクトルを修正
		D3DXVECTOR3 BulletMoveIF = direction * MOVESPEED2*6.5f;

		ESCLine[0].Pos1 = SetPos;
		
		bool bOk22 = false;

		while (bBulletUpdate==false)
		{//ballet製造中の仮処理

			SetOldPos = SetPos;
			SetPos += BulletMoveIF;

			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_NEWBULLET, SetPos, SetOldPos, Min, Max, OBJECT_HITBOX, LAYERINDEX_HITBOX, BulletMoveIF, NULL);

			if (m_HitData.bHit == false)
			{
				//当たり判定計算
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_NEWBULLET, SetPos, SetOldPos, Min, Max, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, BulletMoveIF, NULL);
			}

			if (m_HitData.bHit == true)
			{//接触
				BulletMoveIF = m_HitData.ReflectionVector;

				if (EscReflect == 2)
				{
					ESCLine[0].Pos2 = SetPos;
					ESCLine[1].Pos1 = SetPos;
				}

				if (EscReflect == 1)
				{
					ESCLine[1].Pos2 = SetPos;
					ESCLine[2].Pos1 = SetPos;
				}
			
				EscReflect--;
			}
			
			// 自分の方向に向かってくる場合の処理を追加
			D3DXVECTOR3 relativePos = SetPos - TargetPos;
			D3DXVECTOR3 relativeVel = BulletMoveIF - TargetMove;
			float timeToIntersection = -D3DXVec3Dot(&relativePos, &relativeVel) / D3DXVec3LengthSq(&relativeVel);

			// timeToIntersectionが負またはゼロの場合の修正
			if (timeToIntersection <= 0)
			{
				timeToIntersection = 0.01f; // 最小の正の時間を設定
			}

			// 相手の予測位置（交差点）を計算
			D3DXVECTOR3 predictedIntersection = TargetPos + TargetMove * timeToIntersection;

			//ここで壁に遮られてるか判断--------------------------------------
			CMathProc::CollisionData HitData = CMathProc::AdjustMyPosToCollision_Partner(SetPos, classData.MinLength, classData.MaxLength, predictedIntersection, 250.0f, CObject::OBJECT_OBSTACLE, CObject::LAYERINDEX_OBSTACLE);

			// 各成分の差を計算
			float dx = predictedIntersection.x - SetPos.x;
			float dy = predictedIntersection.y - SetPos.y;
			float dz = predictedIntersection.z - SetPos.z;

			// 距離を計算
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
			{//遮られてない
				if (GoodRength>= MaxLength)
				{
					GoodRength = MaxLength;//最小値更新
					//GoodFrame = UpdateLifeCnt;//この時のフレーム数
					GoodRot= calculationRot;//このときの角度

				}
			}

			if (EscReflect < 0)
			{
				bBulletUpdate = true;
				ESCLine[2].Pos2 = SetPos;
			}
			
			UpdateLifeCnt++;

			if (UpdateLifeCnt> BULLET_LINE_LENGTH)
			{
				ESCLine[2].Pos2 = SetPos;
				break;
			}
		}

		//次の角度に
		calculationRot += D3DX_PI*0.1f;

		if (D3DX_PI< calculationRot)
		{//計算から出る
			bOk = true;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		Cline::Create(ESCLine[i].Pos1, ESCLine[i].Pos2, D3DXCOLOR(0, 0, 1, 1));
	}

	DATA EscDATA;

	//とりあえずrotのみ渡す
	//フレーム周りは予測に使いたいが....。
	EscDATA.rot.y = GoodRot;

	return EscDATA;
}

//==================================
// 砲塔旋回
//==================================
void CObjectMotionEnemyNomal::TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	// クラスデータを取得
	DATA classData = GetClassData();
	DATA ChangeData = DataInit();

	// 目標方向を計算
	D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, 0.0f, TargetPos.z) - D3DXVECTOR3(classData.Pos.x, 0.0f, classData.Pos.z);

	// XZ平面上の目標角度を計算
	float targetAngleXZ = atan2f(enemyDirection.z, -enemyDirection.x) + (D3DX_PI*0.5f);

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

//==================================
// 牽制射撃
//==================================
void CObjectMotionEnemyNomal::ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	//動くモデルのデータ
	CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

	D3DXMATRIX pMat = pParts->GetMtxWorld();

	D3DXMATRIX EscMtxWorld;

	D3DXMATRIX mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&EscMtxWorld);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, TANKFIRE_OFFSETPOS_Z);

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

	//float speed = 12.0f;//速度(後々変更)
	//SetData.move = direction * speed;//速度をかける

	SetData.rot.x = 0.0f;
	SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
	SetData.rot.z = 0.0f;
	//----------------------------------------------------------------------------------

	D3DXVECTOR3 SetHitMin = D3DXVECTOR3(-BULLETSIZE, -BULLETSIZE, -BULLETSIZE);
	D3DXVECTOR3 SetHitMax = D3DXVECTOR3(BULLETSIZE, BULLETSIZE, BULLETSIZE);

	bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

	if (bNoShot == false)
	{
		bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SetData.Pos, SetHitMin, SetHitMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
	}

	if (bNoShot == false)
	{
		SetNowMotion_Sub(2);//攻撃motion
	//	CBullet3D::Create(SetData,0);//クリエイト
	}
}