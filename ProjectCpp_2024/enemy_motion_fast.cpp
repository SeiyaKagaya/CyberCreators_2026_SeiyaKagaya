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

	//	LoadRouteTable();

	m_nLife = 100;

	float fLength[3];
	fLength[0] = 80.0f;
	fLength[1] = 80.0f;
	fLength[2] = 100.0f;

	SetOBBLength(fLength);//OBB長さ格納

	m_nMoveCnt = 0;
	fRotTurret = 0.0f;
	m_BulletDelay = BULLETSHOTDELAY;

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
	for (int i = 0; i < GetMaxLoadPartsNum(); i++)
	{//パーツもDEATH
		GetModelParts(i)->ChengeRGBAbool(true, D3DXCOLOR(0.3f, 0.1f, 0.3f, 1.0f));
	}

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();



	CObjectMotion::Update();//----------------



	DATA classData = GetClassData();


	//相手、自分のGRID番号がかわったか
	bool bChange = false;


	//----------------------------------------------------------------------------------
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

	if (m_OldMyGRIDNum != GetNowGRIDNum())
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
	//		SetNowMotion_Parent(1);//移動motion
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
	//	classData.move.x = direction.x * MoveSpeed;
	//	classData.move.z = direction.z * MoveSpeed;


		// 目標方向の計算
		float targetAngle = atan2f(direction.x, direction.z);

		//角度変動
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
		// ターゲット位置に近すぎる場合は移動を停止
		classData.move.x = 0.0f;
		classData.move.z = 0.0f;
	}





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






	//CMathProc::CollisionData HitData = CMathProc::CheckCircleCollision_Cancel(classData.Pos, classData.Radius, CObject::OBJECT_MOTIONPLAYER, LAYERINDEX_MOTIONPLAYER, this);

	//if (HitData.bHit == true)
	//{
	//	classData.Pos += HitData.ResultDistance;
	//}



	SetClassData(classData);

	//当たり判定計算
	m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

	//当たり判定計算
	m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONENEMY_NOMAL, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);


	classData = GetClassData();




	////被弾系
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
	//		{//弾が機能しているとき

	//			void* Test = pBullet->GetpCaller();

	//			if (Test != this)
	//			{//自身が発射した本人じゃない時

	//				if (pBullet->GetShotType() == CNewBulletALL::SHOTTYPE_PLAYER)
	//				{
	//					if (pBullet->GetHitEscapeTime() <= 0)
	//					{//自爆抑制以降の時

	//						COBB pObb2 = pBullet->GetOBB();
	//						COBB MyObb = GetOBB();

	//						D3DXVECTOR3 HitPos;
	//						bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//当たり判定

	//						if (btest == true)
	//						{
	//							//pBullet->SetDeath(true);
	//							pBullet->SetGoodby();

	//							m_nLife -= 100;
	//						}
	//					}
	//					else
	//					{//抑制期間
	//						if (pBullet->GetCaller() != this)
	//						{//発射した親が自身じゃないとき
	//							COBB pObb2 = pBullet->GetOBB();
	//							COBB MyObb = GetOBB();

	//							D3DXVECTOR3 HitPos;
	//							bool btest = CMathProc::ColOBBs(MyObb, pObb2, &HitPos);//当たり判定

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


	//敵射撃管制
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

	if (pManager->GetbNow3DMode() == false)
	{//2D
	}
	else
	{
	//	if (GetNormalLockOn())
	//	{
	////		m_LockOnUI->SetPos(D3DXVECTOR3(classData.Pos.x, classData.Pos.y + 75.0f, classData.Pos.z));
	//		//ロックオンされてたらこれを呼び出す
	//	//	m_LockOnUI->SetDrawOk(true);
	//	}
	//	else
	//	{
	////		m_LockOnUI->SetDrawOk(false);
	//	}
		//if (GetBulletLockOn())
		//{
		//	m_LockOnUI_Main->SetPos(D3DXVECTOR3(classData.Pos.x, classData.Pos.y + 75.0f, classData.Pos.z));
		//	//ロックオンされてたらこれを呼び出す
		//	m_LockOnUI_Main->SetDrawOk(true);
		//	////メインターゲットか
		//	//SetPriorityAttackTarget(true);
		//}
		//else
		//{
		//	//ロックオンされてたらこれを呼び出す
		//	m_LockOnUI_Main->SetDrawOk(false);
		//	////メインターゲットか
		//	//SetPriorityAttackTarget(false);
		//}
	}


	classData.move.x = 10.0f;

	SetClassData(classData);
}

//=============================
// 描画
//=============================
void CObjectMotionEnemyfast::Draw()
{
	CObjectMotion::Draw();

	//char cData2[100] = {};
	//snprintf(cData2, sizeof(cData2), "敵現在のGRID/%d移動先GRID%d", m_OldMyGRIDNum, NowMoveGRIDNum); // 数値を文字列に変換してCDataにコピー
	//// mousePos.x と mousePos.y がマウスの位置
	//CFont::DrawTextSet(D3DXVECTOR3(1000.0f, 320.0f, 0.0f), 20, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), cData2);

}

//=============================
// 生成
//=============================
CObjectMotionEnemyfast* CObjectMotionEnemyfast::Create(const char* pfilePass, DATA SetData)
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

	if (m_BulletDelay <= 0)
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

		//食い込み防止
		bool bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SETDATA.Pos, BulletMim, BulletMax, OBJECT_HITBOX, LAYERINDEX_HITBOX);

		if (bNoShot == false)
		{
			bNoShot = CMathProc::AvoidInternalSpawn_3D_BoxCollision(OBJECT_MOTIONPLAYER, SETDATA.Pos, BulletMim, BulletMax, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE);
		}

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
// フェーズ１
//=============================
CObject::DATA CObjectMotionEnemyfast::phase1(D3DXVECTOR3 ShotPos)
{
	// クラスデータを取得
	DATA classData = GetClassData();

	// 砲弾射出口の初期位置
	D3DXVECTOR3 SetPos = ShotPos;

	// 現在の砲塔位置からの発射時砲弾moveベクトル
	D3DXVECTOR3 direction = SetPos - D3DXVECTOR3(classData.Pos.x, 50.0f, classData.Pos.z);
	D3DXVec3Normalize(&direction, &direction); // 方向ベクトルを正規化

	// バレットの速さをかけてベクトルを修正
	D3DXVECTOR3 BulletMoveIF = direction * BULLETMOVESPEED_NOMAL;

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
	BulletMoveIF = direction * BULLETMOVESPEED_NOMAL;

	// 照準位置とバレットの移動ベクトルを返す
	CObject::DATA EscDATA;
	EscDATA.Pos = predictedIntersection;
	EscDATA.move = BulletMoveIF;

	return EscDATA;
}

//=============================
// フェーズ2
//=============================
CObject::DATA CObjectMotionEnemyfast::phase2()
{
	//-3.14から3.14までの方角に一定間隔で仮説で打ち込み弾の寿命までに一番近かったものを保存しておき発泡する
	//跳弾はn回/弾の速度はBULLETMOVESPEED_NOMAL/寿命は跳弾限界時

	float calculationRot = D3DX_PI * 0.999f;

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
	int GoodFrame = 999;

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
		D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

		//自分の親のマトリックス欠けてる
		D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);


		D3DXVECTOR3 SetPos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);//砲弾射出口	
		D3DXVECTOR3 SetOldPos = SetPos;

		bool bBulletUpdate = false;
		int UpdateLifeCnt = 0;
		D3DXVECTOR3 Min = D3DXVECTOR3(-30.0f, -30.0f, -30.0f);
		D3DXVECTOR3 Max = D3DXVECTOR3(30.0f, 30.0f, 30.0f);

//		int EscReflect = CBullet3D::MAXREFLECTION - 1;




		// 現在の砲塔位置からの発射時砲弾moveベクトル
		D3DXVECTOR3 direction = SetPos - D3DXVECTOR3(classData.Pos.x, EscMtxWorld._42, classData.Pos.z);
		D3DXVec3Normalize(&direction, &direction); // 方向ベクトルを正規化

		// バレットの速さをかけてベクトルを修正
		D3DXVECTOR3 BulletMoveIF = direction * BULLETMOVESPEED_NOMAL * 6.5f;


		ESCLine[0].Pos1 = SetPos;

		bool bOk22 = false;

		while (bBulletUpdate == false)
		{//ballet製造中の仮処理

			SetOldPos = SetPos;
			SetPos += BulletMoveIF;






			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_BULLET3D, SetPos, SetOldPos, Min, Max, OBJECT_HITBOX, LAYERINDEX_HITBOX, BulletMoveIF, NULL);

			if (m_HitData.bHit == false)
			{
				//当たり判定計算
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_BULLET3D, SetPos, SetOldPos, Min, Max, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, BulletMoveIF, NULL);
			}

			if (m_HitData.bHit == true)
			{//接触
				BulletMoveIF = m_HitData.ReflectionVector;

				

			//	EscReflect--;
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
				if (GoodRength >= MaxLength)
				{
					GoodRength = MaxLength;//最小値更新
					GoodFrame = UpdateLifeCnt;//この時のフレーム数
					GoodRot = calculationRot;//このときの角度

				}
			}


		

			UpdateLifeCnt++;

			if (UpdateLifeCnt > 80)
			{
				ESCLine[2].Pos2 = SetPos;
				break;
			}
		}

		//次の角度に
		calculationRot += D3DX_PI * 0.1f;

		if (D3DX_PI < calculationRot)
		{//計算から出る
			bOk = true;
		}
	}


	//終了後外部保存した方向に発砲準備
	//float GoodRot = 0.0f;			角度
	//float GoodRength = 99999.0f;	//対象との距離(遮るもの無し)
	//float GoodFrame = 999.0f;		//一番近かったフレーム数



	for (int i = 0; i < 3; i++)
	{
		Cline::Create(ESCLine[i].Pos1, ESCLine[i].Pos2, D3DXCOLOR(0, 0, 1, 1));
	}


	DATA EscDATA;

	//とりあえずrotのみ渡す
	//フレーム周りは予測に使いたいが....。
	EscDATA.rot.y = GoodRot;

	//	GoodRength = MaxLength;//最小値更新
	//	GoodFrame = UpdateLifeCnt;//この時のフレーム数
	//	GoodRot = calculationRot;//このときの角度





	return EscDATA;
}
//==================================
// 砲塔旋回
//==================================
void CObjectMotionEnemyfast::TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove)
{
	//// クラスデータを取得
	//DATA classData = GetClassData();
	//DATA ChangeData = DataInit();




	//// 変更データを反映
	//SetChangeDataInObjectMotion(ChangeData);

	DATA ChangeData = DataInit(); 
	DATA classData = GetClassData();


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
