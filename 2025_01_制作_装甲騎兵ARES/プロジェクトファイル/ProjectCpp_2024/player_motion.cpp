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

int CObjectMotionPlayer::m_nNumPlayerAll = START_PLAYER_NUM;//初期値３



//=============================
// コンストラクタ
//=============================
CObjectMotionPlayer::CObjectMotionPlayer(int nPriority) :CObjectMotion(nPriority)
{
}

//=============================
// デストラクタ
//=============================
CObjectMotionPlayer::~CObjectMotionPlayer()
{
	m_nNumPlayerAll--;
}

//=============================
// 初期化
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

	SetOBBLength(fLength);//OBB長さ格納


	DATA classData = GetClassData();

	classData.Pos = m_RESTART_POS;

	SetClassData(classData);

	m_nLife = START_LIFE;
	m_bDown = false;
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	keyboard->GetMouseRayIntersection(*pManager->GetCamera());//マウス位置

//	m_TargetPos = keyboard->GetScreenPosRayIntersection(*pManager->GetCamera(), D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));//マウス位置
	m_TargetPos = D3DXVECTOR3(-4000.0f, 3200.0f,0.0f);

	CScene::MODE NowState = CScene::GetNowScene();



	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 /*|| NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_GAME4*/)
	{//ゲーム中
		//m_pHPUI = CObjectHPLatterUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//m_pHPGauge[0] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		//m_pHPGauge[1] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	}
	else if (NowState == CScene::MODE_TITLE|| NowState == CScene::MODE_RESULT)
	{//タイトル
	
		
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
// 破棄
//=============================
void CObjectMotionPlayer::Uninit()
{
	CObjectMotion::Uninit();
}

//=============================
// 更新
//=============================
void CObjectMotionPlayer::Update()
{
	CScene::MODE NowState = CScene::GetNowScene();

	if (CScene::GetStayNextStage() == false)
	{//待機状態か
		if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3)
		{//ゲーム中
	
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
	
				//ショイパットの状態を取得
				DWORD dwResult = XInputGetState(0, &joykeystate);
	
	
	
				
	
	
	
	
				if (pManager->GetbNow3DMode() == false)
				{//2D
				}
				else
				{//3D
	
					if (m_nMissileStock < MISSILEMAX)
					{//ミサイル不足
						m_nMissileRecoveryCnt++;
						if (m_nMissileRecoveryCnt > RECOVERY_MISSILE)
						{//ミサイル回復フレーム到達
							m_nMissileRecoveryCnt = 0;//リセット
							m_nMissileStock++;//ミサイル増加
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
	
				//	シールド周り
				//----------------------------------------------------------------------------------
				// 中心座標 DirectionPos を設定
					D3DXVECTOR3 DirectionPos = classData.Pos;
					DirectionPos.y += SHIELD_SET_ADDPOS;
	
					// 方向ベクトルを計算
					D3DXVECTOR3 direction = m_TargetPos - DirectionPos;
	
					// XZ 平面での角度を計算 (上方向を基準とする円周角度)
					float angleRadians = atan2f(direction.x, -direction.y); // -direction.x で基準を上方向に変更
	
					// 回転データを設定 (X 軸回転として渡す場合)
					D3DXVECTOR3 SetRot = D3DXVECTOR3(angleRadians + (-D3DX_PI * 0.5f), (-D3DX_PI * 0.5f), 0.0f);
	
					// シールドの回転を設定
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
					//	シールド周り
				//----------------------------------------------------------------------------------
	
					D3DXVECTOR3 ESCDATA = D3DXVECTOR3(classData.Pos.x, classData.Pos.y + 150.0f, classData.Pos.z);
	
					m_pShield->SetPos(ESCDATA);
	
				}
	
				if (pManager->GetbNow3DMode() == false)
				{//2D
	
					//線形補完地点
					SetLinearInterpolation();
				}
				else
				{//3D
				}
	
				if (dwResult != ERROR_SUCCESS)
				{//パッド接続あり
					pManager->bSetInputState(true);
				}
	
				if (pManager->GetbNow3DMode() == false)
				{//2D
					if (pManager->bGetInputState() == true)
					{//操作方法--trueでコントローラー
						//キーボード/コントローラー入力反映(移動)
						ControllerInput2D();
					}
	
				}
				else
				{//3D
					if (pManager->bGetInputState() == true)
					{//操作方法--trueでコントローラー
						//キーボード/コントローラー入力反映(移動)
						ControllerInput3D();
					}
				}
	
	
				//-----------------------------逆走防止
				
				if (NowState == CScene::MODE_GAME2 )
				{//ゲーム中
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

						classData.Pos.x = TarGet_Collision_Max_Pos.x + (My_Collision_Max_Pos.x - classData.Pos.x) + 0.1f; // 接触面押し返し
						SetClassData(classData);
					}
				}
				else if (NowState == CScene::MODE_GAME3)
				{//ゲーム中
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

						classData.Pos.x = TarGet_Collision_Max_Pos.x + (My_Collision_Max_Pos.x - classData.Pos.x) + 0.1f; // 接触面押し返し
						SetClassData(classData);
					}
					//-------------------------
				}
	
	
	
	
	
	
				//GUARD描画するか
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
				//照準位置制限(自機より円形)
				if (pManager->GetbNow3DMode() == false)
				{//2D
	
	
	
					if (pManager->bGetInputState() == true)
					{//操作方法--trueでコントローラー
						D3DXVECTOR3 PlayerPos = GetClassData().Pos;
						float fRadius = TARGET_SET_ADDPOS * 2.0f;
	
						//m_TargetPosをこの円の中に収める
						PlayerPos.y += TARGET_SET_ADDPOS;
	
						//ベクトル計算
						D3DXVECTOR3 VEC = m_TargetPos - PlayerPos;
	
						//ベクトルの長さ
						float fDistance = D3DXVec3Length(&VEC);
	
						//長さが半径を超えた
						if (fDistance > fRadius)
						{
							// ベクトルを正規化
							D3DXVec3Normalize(&VEC, &VEC);
	
							// ベクトルの方向に半径切りまで動かす
							m_TargetPos = PlayerPos + VEC * fRadius;
	
						}
					}
	
	
					//体向き変動(2D)
					if (m_TargetPos.x >= classData.Pos.x)
					{//右正面
						SetFrontMove(true);//右正面かboolをset
						classData.rot.y = -D3DX_PI * 0.5f;
					}
					else
					{//左正面
						SetFrontMove(false);
						classData.rot.y = D3DX_PI * 0.5f;
					}
	
				}
				else
				{//3D
	
				}
	
				SetClassData(classData);
				classData = GetClassData();
	
				//体力--------------------------------------------------------
				if (m_nLife <= 0)
				{
					m_bDown = true;
	
					CScore::AddScore(-(CScore::DETH_PENALTY));
	
					m_nLife = START_LIFE;
	
					m_ResetCnt = 0;
	
					m_nNumPlayerAll--;
	
					for (int i = 0; i < GetMaxLoadPartsNum(); i++)
					{//パーツもDEATH
						GetModelParts(i)->DrawOkBool(false);
	
						Explosion3D::Create(GetClassData().Pos);
	
					}
				}
	
				//衝突相殺--敵と-------------------------------------------------------
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
	
	
				bool bHit = false;//着地判定
	
				SetClassData(classData);
	
	
				//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
				//落下に転じたか検証部
				float fTestGravity = -60.0f;
	
				DATA TestData = GetClassData();
	
				D3DXVECTOR3 TestPos = TestData.Pos;//位置保存
				TestPos.y += fTestGravity;
	
				//当たり判定計算
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, TestPos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
					SetClassData(TestData);//テスト判定なので、結果を戻す
				}
	
				//当たり判定計算
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, TestPos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
					SetClassData(TestData);//テスト判定なので、結果を戻す
				}
	
				D3DXVECTOR3 rayDirection = D3DXVECTOR3(0, -1, 0); // 下方向のレイ
	
				m_HitData = CStageCollisionBox3D2D::bHitColision(TestPos, rayDirection, OBJECT_MOTIONPLAYER, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
					SetClassData(TestData);//テスト判定なので、結果を戻す
				}
	
				//当たり判定計算
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, TestPos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
					SetClassData(TestData);//テスト判定なので、結果を戻す
				}
	
	
				if (bHit == false)
				{//接触が生じてない時==設置状態継続してはいけない
	
					if (classData.Pos.y > 0.0f)
					{
						SetIsOnGroundBool(false);//着地状態解除
					}
				}
				//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	
	
				//重力--------------------------------------------------------
				if (!GetIsOnGroundBool())
				{//着地状態でない時
	
					//重力
					classData.move.y -= GRAVITY * 0.1f;
				}
				else
				{//着地
	
				}
				SetClassData(classData);
				//------------------------------------------------------------
	
	
	
				//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
				//当たり判定本体（着地系）
	
				//当たり判定計算
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
				}
	
				//当たり判定計算
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX_2D3D, LAYERINDEX_HITBOX_2D3D, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
	
				}
	
				//当たり判定計算
				m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);
	
				if (m_HitData.HitAngle.y == 1.0f)
				{
					bHit = true;
				}
	
				classData = GetClassData();
	
				if (!GetIsLandingTriggerBool())
				{//着地している状態でない時
					// 接地判定
					if (bHit || classData.Pos.y <= 0.0f)
					{//接触
	
						if (classData.move.y <= 0.0f)
						{
							classData.move.y = 0.0f;
						}
	
						if (!GetIsOnGroundBool())
						{// 現在接地している状態でない
							SetIsLandingTriggerBool(true); // 着地トリガーを発動
						}
	
						SetIsOnGroundBool(true);  // 接地状態に設定
					}
				}
	
				// 位置変化による接地状態の解除
				float POSY = std::floor(GetOldPosY());
				float NOWPOSY = std::floor(classData.Pos.y);
	
				if (NOWPOSY != POSY)
				{
					m_RandingCutCnt++;
	
					if (m_RandingCutCnt >= RANDINGTRIGGER_FARAME)
					{
						// 接地状態の解除
						SetIsOnGroundBool(false);
					}
				}
				else
				{
					m_RandingCutCnt = 0;
				}
	
	
				// モーション再生処理
				// 空中モーションの処理
				if (!GetIsOnGroundBool() && !GetIsLandingTriggerBool())
				{//着地状態じゃないかつ着地瞬間じゃない
	
	
					if (/*GetNowMotionParent() != MOTIONTYPE_HIGH_MOVE_FRONT &&*/
						GetNowMotionParent() != MOTIONTYPE_HIGH_MOVE_LEFT &&
						GetNowMotionParent() != MOTIONTYPE_HIGH_MOVE_RIGHT &&
						GetNowMotionParent() != MOTIONTYPE_HIGH_MOVE_BACK)
					{
	
						SetNowMotion_Parent(MOTIONTYPE_JUMP); // 空中モーションの再生
	
						// モーション変動
					//	SetNowMotion_Parent(MOTIONTYPE_STANDBY); // 待機
	
					//	m_OldInputMotionParent = MOTIONTYPE_STANDBY; // 移動系入力を保持
					}
				}
	
				// 着地モーションのトリガー
				if (GetIsLandingTriggerBool() && GetIsOnGroundBool())
				{//着地状態かつ着地瞬間
					SetNowMotion_Parent(MOTIONTYPE_RANDING); // 着地モーションの再生
					SetIsLandingTriggerBool(false); // 着地トリガーをリセット
				}
	
				SetClassData(classData);
	
				//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	
				classData = GetClassData();
	
				//ターゲットの方向に砲口を向ける(腰)
				if (pManager->GetbNow3DMode() == false)
				{//2D
	
				  //ターゲットの方向に砲口を向ける(腰)2D
				  //----------------------------------------------------------------------------------
	
					DATA ChangeData = DataInit();
	
					float minYAngle = -1.1f; // 下側の角度の限界
					float maxYAngle = 1.1f;  // 上側の角度の限界
	
					//方向
					D3DXVECTOR3 enemyDirection = D3DXVECTOR3(m_TargetPos.x, m_TargetPos.y, m_TargetPos.z) - classData.Pos;
	
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
		
					//基底クラスからパーツにデータを受け渡し
					SetChangeDataInObjectMotion(ChangeData);


					//	シールド周り
					//----------------------------------------------------------------------------------
					// 中心座標 DirectionPos を設定
					D3DXVECTOR3 DirectionPos = classData.Pos;
					DirectionPos.y += SHIELD_SET_ADDPOS;

					// 方向ベクトルを計算
					D3DXVECTOR3 direction = m_TargetPos - DirectionPos;

					// XZ 平面での角度を計算 (上方向を基準とする円周角度)
					float angleRadians = atan2f(direction.x, -direction.y); // -direction.x で基準を上方向に変更

					// 回転データを設定 (X 軸回転として渡す場合)
					D3DXVECTOR3 SetRot /*= D3DXVECTOR3(angleY + (-D3DX_PI * 0.5f), (-D3DX_PI * 0.5f), 0.0f)*/;

					float Diff = -0.065f;

					//体向き変動(2D)
					if (m_TargetPos.x >= classData.Pos.x)
					{//右正面
						SetRot = D3DXVECTOR3(angleY + Diff, (-D3DX_PI * 0.5f), 0.0f);
					}
					else
					{//左正面
						SetRot = D3DXVECTOR3(angleY + Diff, (D3DX_PI * 0.5f), 0.0f);
					}

					m_pBulletLine->SetRot(SetRot);

					D3DXVECTOR3 SETPOS = m_TargetPos;

					D3DXVec3Normalize(&direction, &direction);


					//体向き変動(2D)
					if (m_TargetPos.x >= classData.Pos.x)
					{//右正面
						SETPOS -= direction * 180.0f;
					}
					else
					{//左正面
						SETPOS -= direction * 180.0f;
					}
					SETPOS.y += 100.0f;


					//					m_pShield->SetPos(SETPOS);
					m_pBulletLine->SetPos(SETPOS);
					//----------------------------------------------------------------------------------
				}
				else
				{//3D
					//ターゲットの方向に砲口を向ける(腰)3D
				  //----------------------------------------------------------------------------------
					bool bLockOn = false;
	
					DATA ChangeData = DataInit();
	
					// 配置物プライオリティの先頭を取得
					CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_FAST);
	
					if (pObject != nullptr)
					{ // 先頭がない==プライオリティまるっとない
	
						CObjectMotionEnemyfast* pEnemyFast;
						pEnemyFast = (CObjectMotionEnemyfast*)pObject;
	
						while (pObject != nullptr)
						{
							CObject::DATA EscEnemyData = pEnemyFast->GetClassData();
	
							if (pEnemyFast->GetLockOnUIMain()->bGetDrawOk() == true)
							{//バレットロックオンが描画状態
								bLockOn = true;
	
								float minYAngle = -1.1f; // 下側の角度の限界
								float maxYAngle = 1.1f;  // 上側の角度の限界
	
								//方向
								D3DXVECTOR3 enemyDirection = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 600.0f, EscEnemyData.Pos.z) - classData.Pos;
	
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
					{//まだロックオンがない
					// 配置物プライオリティの先頭を取得
						CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_NOMAL);
	
						if (pObject != nullptr)
						{ // 先頭がない==プライオリティまるっとない
	
							CObjectMotionEnemyNomal* pEnemyNomal;
							pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;
	
							while (pObject != nullptr)
							{
								CObject::DATA EscEnemyData = pEnemyNomal->GetClassData();
	
								if (pEnemyNomal->GetLockOnUIMain()->bGetDrawOk() == true)
								{//バレットロックオンが描画状態
									bLockOn = true;
	
									float minYAngle = -1.1f; // 下側の角度の限界
									float maxYAngle = 1.1f;  // 上側の角度の限界
	
									//方向
									D3DXVECTOR3 enemyDirection = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 600.0f, EscEnemyData.Pos.z) - classData.Pos;
	
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
					{//まだロックオンがない
					// 配置物プライオリティの先頭を取得
						CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS);
	
						if (pObject != nullptr)
						{ // 先頭がない==プライオリティまるっとない
	
							CObjectMotionEnemyBoss* pEnemyBoss;
							pEnemyBoss = (CObjectMotionEnemyBoss*)pObject;
	
							while (pObject != nullptr)
							{
								CObject::DATA EscEnemyData = pEnemyBoss->GetClassData();
	
								if (pEnemyBoss->GetLockOnUIMain()->bGetDrawOk() == true)
								{//バレットロックオンが描画状態
									bLockOn = true;
	
									float minYAngle = -1.1f; // 下側の角度の限界
									float maxYAngle = 1.1f;  // 上側の角度の限界
	
									//方向
									D3DXVECTOR3 enemyDirection = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 600.0f, EscEnemyData.Pos.z) - classData.Pos;
	
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
					{//まだロックオンがない
					// 配置物プライオリティの先頭を取得
						CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS_GUARD);
	
						if (pObject != nullptr)
						{ // 先頭がない==プライオリティまるっとない
	
							CObjectMotionEnemyGuard* pEnemyGuard;
							pEnemyGuard = (CObjectMotionEnemyGuard*)pObject;
	
							while (pObject != nullptr)
							{
								CObject::DATA EscEnemyData = pEnemyGuard->GetClassData();
	
								if (pEnemyGuard->GetLockOnUIMain()->bGetDrawOk() == true)
								{//バレットロックオンが描画状態
									bLockOn = true;
	
									float minYAngle = -1.1f; // 下側の角度の限界
									float maxYAngle = 1.1f;  // 上側の角度の限界
	
									//方向
									D3DXVECTOR3 enemyDirection = D3DXVECTOR3(EscEnemyData.Pos.x, EscEnemyData.Pos.y + 600.0f, EscEnemyData.Pos.z) - classData.Pos;
	
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
					{//まだロックオンがない
					 //対象がいない
						ChangeData.rot.y = classData.rot.y;
					}
	
	
					//基底クラスからパーツにデータを受け渡し(だれも対象じゃないときは初期値が入る)
					SetChangeDataInObjectMotion(ChangeData);
				}
	
	
				//底抜け対策
				if (classData.Pos.y <= 0)
				{
					classData.Pos.y = 0;
				}
	
	
				SetClassData(classData);
	
	
				if (m_guard == true)
				{
					SetNowMotion_Sub(MOTIONTYPE_GUARD);
				}
	
	
				//慣性
				//----------------------------------------------------------------------------
				if (!GetIsOnGroundBool() && !GetIsLandingTriggerBool())
				{//着地状態じゃないかつ着地瞬間じゃない
					if (GetBoostNow() == true)
					{
						classData = GetClassData();
	
						//移動量を更新(疑似慣性で減衰)
						classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_BOOST_XZ);
						classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_BOOST_Y);
						classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_BOOST_XZ);
	
						SetClassData(classData);
	
						CObjectMotion::Update();//------------------更新
					}
					else
					{
						if (m_BoostRestCnt > 0)
						{
							m_BoostRestCnt--;
	
							classData = GetClassData();
	
							//移動量を更新(疑似慣性で減衰)
							classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_BOOST_XZ * 0.5f);
							classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_BOOST_Y * 0.5f);
							classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_BOOST_XZ * 0.5f);
						}
						else
						{
							classData = GetClassData();
	
							//移動量を更新(疑似慣性で減衰)
							classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_LOAD_XZ * 0.5f);
							classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_Y * 0.5f);
							classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_LOAD_XZ * 0.5f);
						}
	
	
						SetClassData(classData);
	
						CObjectMotion::Update();//------------------更新
					}
				}
				else
				{//地上
					if (GetBoostNow() == true)
					{
						classData = GetClassData();
	
						//移動量を更新(疑似慣性で減衰)
						classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_BOOST_XZ);
						classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_BOOST_Y);
						classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_BOOST_XZ);
	
						SetClassData(classData);
	
						CObjectMotion::Update();//------------------更新
					}
					else
					{
						if (m_BoostRestCnt > 0)
						{
							m_BoostRestCnt--;
	
							classData = GetClassData();
	
							//移動量を更新(疑似慣性で減衰)
							classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_BOOST_XZ);
							classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_BOOST_Y);
							classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_BOOST_XZ);
						}
						else
						{
							classData = GetClassData();
	
							//移動量を更新(疑似慣性で減衰)
							classData.move.x += (0.0f - classData.move.x) * (DAMPING_RATIO_LOAD_XZ);
							classData.move.y += (0.0f - classData.move.y) * (DAMPING_RATIO_Y);
							classData.move.z += (0.0f - classData.move.z) * (DAMPING_RATIO_LOAD_XZ);
						}
	
	
						SetClassData(classData);
	
						CObjectMotion::Update();//------------------更新
					}
				}
	
				if (!GetIsOnGroundBool() && !GetIsLandingTriggerBool())
				{//着地状態じゃないかつ着地瞬間じゃない
	
	
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
				{//着地
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
			{//Restartまで
				m_ResetCnt++;
	
				if (m_ResetCnt >= RESET_CNT)
				{
					DATA SETDATA = GetClassData();
	
					SETDATA.Pos = m_RESTART_POS;//座標更新
					SetClassData(SETDATA);
	
					m_ResetCnt = 0;
					m_bDown = false;
					for (int i = 0; i < GetMaxLoadPartsNum(); i++)
					{//パーツもDEATH
						GetModelParts(i)->DrawOkBool(true);
	
					}
				}
			}
	
		}
		else if (NowState == CScene::MODE_TITLE)
		{//タイトル
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
	
			//基底クラスからパーツにデータを受け渡し
			SetChangeDataInObjectMotion(Head);
	
			CObjectMotion::Update();//------------------更新
	
	
			SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//移動motion
			SetNowMotion_Sub(MOTIONTYPE_MOVE_FRONT);//移動motion
	
	
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
	
			//基底クラスからパーツにデータを受け渡し
			SetChangeDataInObjectMotion(Head);
	
			CObjectMotion::Update();//------------------更新
	
	
			SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//移動motion
			SetNowMotion_Sub(MOTIONTYPE_MOVE_FRONT);//移動motion
	
	
		}
		else if (NowState == CScene::MODE_OP)
		{//
	
			DATA classData = GetClassData();
	
			//ここではこれをmove進行フレームカウントとして利用
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
	
			//基底クラスからパーツにデータを受け渡し
			SetChangeDataInObjectMotion(Head);
	
			CObjectMotion::Update();//------------------更新
	
	
			SetNowMotion_Parent(MOTIONTYPE_OP0);//移動motion
			SetNowMotion_Sub(MOTIONTYPE_OP0);//移動motion
	
	
		}
		else if (NowState == CScene::MODE_MOVIE)
		{//
	
			DATA classData = GetClassData();
	
			classData.rot.y = -1.57f;

			DATA ChangeData = DataInit();
			ChangeData.rot.y = classData.rot.y;

			//基底クラスからパーツにデータを受け渡し(だれも対象じゃないときは初期値が入る)
			SetChangeDataInObjectMotion(ChangeData);
			
			SetClassData(classData);
	
			CObjectMotion::Update();//------------------更新
	
	
			SetNowMotion_Parent(MOTIONTYPE_STANDBY);
			SetNowMotion_Sub(MOTIONTYPE_STANDBY);
		}
		else if (NowState == CScene::MODE_MOVIE2)
		{//

		DATA classData = GetClassData();

		classData.rot.y = -2.5824623f;

		DATA ChangeData = DataInit();
		ChangeData.rot.y = classData.rot.y;

		//基底クラスからパーツにデータを受け渡し(だれも対象じゃないときは初期値が入る)
		SetChangeDataInObjectMotion(ChangeData);

		SetClassData(classData);

		CObjectMotion::Update();//------------------更新


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
	{//待機状態
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
void CObjectMotionPlayer::Draw()
{


		CObjectMotion::Draw();
}

//=============================
// 生成
//=============================
CObjectMotionPlayer* CObjectMotionPlayer::Create(std::string pfilePass, DATA SetData)
{
	CObjectMotionPlayer* pObstacle = new CObjectMotionPlayer;

	pObstacle->SetFilePass(pfilePass);//パス格納
	pObstacle->SetStartPos(SetData.Pos);
	pObstacle->Init();

	// 取得
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)AABB_BOX_PLAYER, (float)AABB_BOX_PLAYER*3.0f, (float)AABB_BOX_PLAYER);
	SetData.MinLength = D3DXVECTOR3(-(float)AABB_BOX_PLAYER, +53.0f, -(float)AABB_BOX_PLAYER);
	pObstacle->SetClassData(SetData);


	return pObstacle;
}


//=============================
// Controller入力--2D
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

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);

	//中間点までの距離
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//差分を半分に

	//中間点をたしてデッドゾーンと最大点の中間点を算出(通常入力、微入力の判別分岐点)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;

//	bool bMoveNow = false;

	float Xdate = 0.0f;
	float Zdate = 0.0f;
	float fRotDest = 0.0f;

//	bool MoveNow = false;//移動入力できてるか

	DATA classData = GetClassData();

	//球を生成してよいかを検索
	bool bNoShot = false;
	bool bShot = false;
	bool bNomalMove = false;

	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_L1))
	{
		SetNowMotion_Sub(MOTIONTYPE_GUARD);//防御
		SetbGuard(true);
	}

	if (GetbGuard() == false)
	{//GUARDしてない
		//----------------------------------------------------------------射撃
		if (m_ShotDelay <= 0)
		{
			if (joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{//
					//動くモデルのデータ
				CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

				D3DXMATRIX pMat = pParts->GetMtxWorld();

				D3DXMATRIX pMat2 = pParts->GetMtxWorld();
				
				D3DXMATRIX EscMtxWorld;
				D3DXMATRIX EscMtxWorld2;

				D3DXMATRIX mtxTrans;//計算用マトリックス

				D3DXMATRIX mtxTrans2;//計算用マトリックス

				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&EscMtxWorld);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, 0.0f, SHOTPOS_Y, SHOTPOS_Z);

				D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

				//自分の親のマトリックス欠けてる
				D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);



				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&EscMtxWorld2);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans2, 0.0f, 0.0f, SHOTPOS_Z-100.0f);

				D3DXMatrixMultiply(&EscMtxWorld2, &EscMtxWorld2, &mtxTrans2);

				//自分の親のマトリックス欠けてる
				D3DXMatrixMultiply(&EscMtxWorld2, &EscMtxWorld2, &pMat2);

				//Mouseの方向にballetを飛ばす
				//----------------------------------------------------------------------------------

				DATA SetData;
				SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

				D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41, pMat._42/*BULLET_SHOT_POS_Y*/, /*pMat._43*/0.0f);

				//Mouseで画面に指してる3D空間座標取得
				D3DXVECTOR3 TargetPos = D3DXVECTOR3(EscMtxWorld2._41, EscMtxWorld2._42, 0.0f);

				float fX = (float)((rand() % 40) - 20);
				float fY = (float)((rand() % 40) - 20);

				TargetPos += D3DXVECTOR3(fX, fY, 0.0f);



				// TargetPos から SetData.Pos への方向ベクトルを計算
				D3DXVECTOR3 direction = TargetPos - DirectionPos;

				// 方向ベクトルを正規化（単位ベクトルにする）
				D3DXVec3Normalize(&direction, &direction);


				float speed = (int)BULLETSPEED;//速度(後々変更)
				SetData.move = direction * speed;//速度をかける

				// SetData.rot.y をターゲットの方向に合わせる
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
					SetNowMotion_Sub(MOTIONTYPE_ATTACK);//攻撃motion

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
		//----------------------------------------------------------------射撃
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
	
	////-----------------------------------------------------------コントローラー左
	bool MoveNowCom = false;//入力の有無(コントローラ)

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)
	//	Xdate = 1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Dがおされた(右)
	//	Xdate = -1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Wがおされた(上)
		//Zdate = -1.0f;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Sがおされた(下)
		//Zdate = 1.0f;
		MoveNowCom = true;
	}



	//移動する状態の時
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
			{//序盤
				classData.move.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 1.8f;
//				classData.move.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 1.3f;

			}
			else
			{//終盤
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
		{//右正面

			if (classData.move.x>=0)
			{//前進
				if (GetBoostNow() == true)
				{
					SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_FRONT);//移動
					m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_FRONT;//移動系入力を保持

				}
				else
				{
					SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//移動
					m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//移動系入力を保持
				}
			
				classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
			}
			else
			{//後退
				classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest);

				if (GetBoostNow() == true)
				{
					SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_BACK);//移動
					m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_BACK;//移動系入力を保持

				}
				else
				{
					SetNowMotion_Parent(MOTIONTYPE_MOVE_BACK);//移動
					m_OldInputMotionParent = MOTIONTYPE_MOVE_BACK;//移動系入力を保持
				}
				
			}
		}
		else
		{//左正面
			if (classData.move.x < 0)
			{//前進
				classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
			
				if (GetBoostNow() == true)
				{
					SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_FRONT);//移動
					m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_FRONT;//移動系入力を保持

				}
				else
				{
					SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//移動
					m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//移動系入力を保持
				}
			}
			else
			{//後退
				classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest);
			
				if (GetBoostNow() == true)
				{
					SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_BACK);//移動
					m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_BACK;//移動系入力を保持
				}
				else
				{
					SetNowMotion_Parent(MOTIONTYPE_MOVE_BACK);//移動
					m_OldInputMotionParent = MOTIONTYPE_MOVE_BACK;//移動系入力を保持
				}
			}
		}
		
	}
	else
	{//移動がなかった場合

		if (GetNowMotionParent() != MOTIONTYPE_STANDBY &&
			GetNowMotionParent() != MOTIONTYPE_JUMP &&
			GetNowMotionParent() != MOTIONTYPE_RANDING &&
			GetNowMotionParent() != MOTIONTYPE_ATTACK)
		{
			// モーション変動
			SetNowMotion_Parent(MOTIONTYPE_STANDBY); // 待機

			m_OldInputMotionParent = MOTIONTYPE_STANDBY; // 移動系入力を保持
		}

		if (GetNowMotionSub() != MOTIONTYPE_ATTACK)
		{//モーション変動
			SetNowMotion_Sub(MOTIONTYPE_STANDBY);//待機

			m_OldInputMotionParent = MOTIONTYPE_STANDBY;//移動系入力を保持
		}

	}
	//-------------------------------------------------------------------------------------------------------------------------
	//右スティック

	 bool MoveNowCom2 = false;//入力の有無(コントローラ)

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)
	//	Xdate = 1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2000))
	{//Dがおされた(右)
	//	Xdate = -1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2000))
	{//Wがおされた(上)
		//Zdate = -1.0f;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 2000))
	{//Sがおされた(下)
		//Zdate = 1.0f;
		MoveNowCom2 = true;
	}

	int sThumbRX = joykeystate.Gamepad.sThumbRX;
	int sThumbRY = joykeystate.Gamepad.sThumbRY;

	// スティックの入力値からベクトルの大きさを計算
	float magnitude = std::sqrt(static_cast<float>(sThumbRX * sThumbRX) + static_cast<float>(sThumbRY * sThumbRY));

	float vecX, vecY;

	if (magnitude > 3000)
	{
		// 値を正規化（単位ベクトルを計算）
		vecX = sThumbRX / magnitude;
		vecY = sThumbRY / magnitude;
		//// ターゲットの位置を計算
		m_TargetPos.x = classData.Pos.x + vecX * 500.0f; // X方向に一定距離進む
		m_TargetPos.y = (classData.Pos.y + 150.0f) + vecY * 500.0f; // Y方向に一定距離進む
		m_TargetPos.z = 0;

	}
	else 
	{
		// スティックが中央の場合はベクトルを0に
		vecX = 0.0f;
		vecY = 0.0f;


		//ここで正面との差分を角度で足しいれる

	}

	float MoveSpeed2 = MOVESPEED;

	if (MoveNowCom2 == false)
	{

	}
	else
	{//Controller

		//Controller移動

		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbRX, (float)-joykeystate.Gamepad.sThumbRY);//これが方角

		fRotDest = (Angle2 - CameraRot.y - (1.0f * D3DX_PI));

		D3DXVECTOR3 ESCTargetMove= D3DXVECTOR3(0.0f,0.0f,0.0f);

		if (GetBoostNow() == true)
		{
			if (m_nBoostCnt <= BOOST_FARAME && m_nBoostCnt > BOOST_FARAME * 0.5f)
			{//序盤
				ESCTargetMove.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 4.0f;//三角関数利用して移動の長さを代入
				ESCTargetMove.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 4.0f;//三角関数利用して移動の長さを代入

			}
			else
			{//終盤

				ESCTargetMove.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 3.0f;//三角関数利用して移動の長さを代入
				ESCTargetMove.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 3.0f;//三角関数利用して移動の長さを代入
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
		//飛翔
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
// Controller入力--3D
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

	
		

	//ショイパットの状態を取得
	DWORD dwResult = XInputGetState(0, &joykeystate);

	//中間点までの距離
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//差分を半分に

	//中間点をたしてデッドゾーンと最大点の中間点を算出(通常入力、微入力の判別分岐点)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;

	
	float Xdata = 0.0f;
	float Zdata = 0.0f;
	float fRotDest = 0.0f;

//	bool MoveNow = false;//移動入力できてるか

	DATA classData = GetClassData();

	//球を生成してよいかを検索
	bool bNoShot = false;
	bool bShot = false;
	bool bNomalMove = false;

	if (JoyPad->GetPress(CInputJoyPad::JOYKEY_L1))
	{
		SetNowMotion_Sub(MOTIONTYPE_GUARD);//防御
		SetbGuard(true);
	}

	if (GetbGuard() == false)
	{//GUARDしてない

		if (JoyPad->GetTrigger(CInputJoyPad::JOYKEY_R1))
		{
			CRenderer* pRenderer = nullptr;

			CManager* pManager = CManager::GetInstance();

			CObject* pObj = nullptr;
			pObj = CObject::GetObjectPoint(CObject::LAYERINDEX_MISSILE_MNG, CObject::OBJECT_MISSILE_MNG);


			//動くモデルのデータ
			CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

			D3DXMATRIX pMat = pParts->GetMtxWorld();

			D3DXMATRIX EscMtxWorld;

			D3DXMATRIX mtxTrans;//計算用マトリックス

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&EscMtxWorld);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, 0.0f, SHOTPOS_Y, 0.0f);

			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

			//自分の親のマトリックス欠けてる
			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

			//Mouseの方向にballetを飛ばす
			//----------------------------------------------------------------------------------

			DATA SetData=DataInit();
			SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

//			SetData.move.x = -80.0f;
			SetData.move.y = +160.0f;
			SetData.move.z = -80.0f;




		  //----------------------------------------------------------------------------------
			bool bLockOn = false;

			DATA ChangeData = DataInit();

			// 配置物プライオリティの先頭を取得
			CObject* pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_FAST);

			if (pObject != nullptr)
			{ // 先頭がない==プライオリティまるっとない

				CObjectMotionEnemyfast* pEnemyFast;
				pEnemyFast = (CObjectMotionEnemyfast*)pObject;

				while (pObject != nullptr)
				{
					if (m_nMissileStock > 0)
					{
						CObject::DATA EscEnemyData = pEnemyFast->GetClassData();

						if (pEnemyFast->GetLockOnUI()->bGetDrawOk() == true)
						{//ロックオンが描画状態
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

			// 配置物プライオリティの先頭を取得
			 pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_NOMAL);

			if (pObject != nullptr)
			{ // 先頭がない==プライオリティまるっとない

				CObjectMotionEnemyNomal* pEnemyNomal;
				pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;

				while (pObject != nullptr)
				{
					if (m_nMissileStock > 0)
					{
						CObject::DATA EscEnemyData = pEnemyNomal->GetClassData();

						if (pEnemyNomal->GetLockOnUI()->bGetDrawOk() == true)
						{//バレットロックオンが描画状態
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




			// 配置物プライオリティの先頭を取得
			pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS);

			if (pObject != nullptr)
			{ // 先頭がない==プライオリティまるっとない

				CObjectMotionEnemyBoss* pEnemyBoss;
				pEnemyBoss = (CObjectMotionEnemyBoss*)pObject;

				while (pObject != nullptr)
				{
					if (m_nMissileStock > 0)
					{
						CObject::DATA EscEnemyData = pEnemyBoss->GetClassData();

						if (pEnemyBoss->GetLockOnUI()->bGetDrawOk() == true)
						{//バレットロックオンが描画状態
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




			// 配置物プライオリティの先頭を取得
			pObject = CObject::GetpTop(LAYERINDEX_MOTIONENEMY_BOSS_GUARD);

			if (pObject != nullptr)
			{ // 先頭がない==プライオリティまるっとない

				CObjectMotionEnemyGuard* pEnemyGuard;
				pEnemyGuard = (CObjectMotionEnemyGuard*)pObject;

				while (pObject != nullptr)
				{
					if (m_nMissileStock > 0)
					{
						CObject::DATA EscEnemyData = pEnemyGuard->GetClassData();

						if (pEnemyGuard->GetLockOnUI()->bGetDrawOk() == true)
						{//バレットロックオンが描画状態
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

		//----------------------------------------------------------------射撃
		if (m_ShotDelay <= 0)
		{
			if (joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			{//
					//動くモデルのデータ
				CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

				D3DXMATRIX pMat = pParts->GetMtxWorld();

				D3DXMATRIX EscMtxWorld;

				D3DXMATRIX mtxTrans;//計算用マトリックス

				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&EscMtxWorld);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, 0.0f, SHOTPOS_Y, SHOTPOS_Z);

				D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

				//自分の親のマトリックス欠けてる
				D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

				//Mouseの方向にballetを飛ばす
				//----------------------------------------------------------------------------------

				DATA SetData;
				SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

				D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41, pMat._42, pMat._43);
				//上記は静止時のみ、移動有りはのちほど



				
				D3DXVECTOR3 TargetPos;

				if (m_bBuletLockOn == false)
				{//バレットロックオンがない
					TargetPos = SetData.Pos;
				}
				else
				{
					TargetPos = m_TargetPos;
				}



				// TargetPos から SetData.Pos への方向ベクトルを計算
				D3DXVECTOR3 direction = TargetPos - DirectionPos;

			
				float speed = (int)BULLETSPEED;//速度(後々変更)
				D3DXVec3Normalize(&direction, &direction);

				SetData.move = direction * speed;//速度をかける

		//		CMathProc::SetPositionldPredictedImpactPoint(SetData.Pos, SetData.move, TargetPos,)

				// SetData.rot.y をターゲットの方向に合わせる
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
					SetNowMotion_Sub(MOTIONTYPE_ATTACK);//攻撃motion

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
		//----------------------------------------------------------------射撃
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

	////-----------------------------------------------------------コントローラー左
	bool MoveNowCom = false;//入力の有無(コントローラ)

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)
		Xdata = 1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Dがおされた(右)
		Xdata = -1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Wがおされた(上)
		Zdata = -1.0f;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000))
	{//Sがおされた(下)
		Zdata = 1.0f;
		MoveNowCom = true;
	}









	//移動する状態の時
	if (MoveNowCom == true)
	{
		m_nMoveCnt++;

		if (m_nMoveCnt >= CObjectFootPrint::STANPFLAME)
		{
			m_nMoveCnt = 0;
			//CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z), classData.rot);
		}


		//カメラの角度取得
		D3DXVECTOR3 SETROT = pManager->GetCamera()->GetRot();

		// 移動ベクトル
		float moveX = joykeystate.Gamepad.sThumbLX * JoyStickDiff;
		float moveZ = joykeystate.Gamepad.sThumbLY * JoyStickDiff;

		// もしブースト中なら、移動量を調整
		if (GetBoostNow() == true)
		{
			if (m_nBoostCnt <= BOOST_FARAME && m_nBoostCnt < BOOST_FARAME * 0.4f)
			{//序盤
				moveX *= 1.3f;
				moveZ *= 1.3f;
			}
			else
			{//終盤
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

		// カメラの角度に合わせて移動ベクトルを回転
		float rotatedX = moveX * cos(SETROT.y) - moveZ * sin(SETROT.y);
		float rotatedZ = moveX * sin(SETROT.y) + moveZ * cos(SETROT.y);

		fRotDest = -SETROT.y + D3DX_PI;

		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest);


		// 最終的な移動量
		classData.move.x += rotatedX;
		classData.move.z += rotatedZ;


		//先頭移動rotとmoveの方向の差異を元に足運びを変動させる
		//----------------------------------------------------
		//classData.move.zとclassData.move.xの方角(移動方向をrotとする)とfRotDest(目標角度)の差異で変動
		//float FrontLineR = -(D3DX_PI * 0.5f - 0.57f);
		//float FrontLine2R = -(D3DX_PI * 0.5f + 0.57f);
		//float FrontLineL = (D3DX_PI * 0.5f - 0.57f);
		//float FrontLine2L = (D3DX_PI * 0.5f + 0.57f);



	

		int sThumbLX = joykeystate.Gamepad.sThumbLX;
		int sThumbLY = joykeystate.Gamepad.sThumbLY;

		// スティックの方向を角度で計算
		float angle = std::atan2(static_cast<float>(sThumbLY), static_cast<float>(sThumbLX)) - D3DX_PI * 0.5f;

		// 角度を正規化 
		if (angle < -D3DX_PI) angle += 2 * D3DX_PI;
		if (angle > D3DX_PI) angle -= 2 * D3DX_PI;

		// Boost状態かを判定
//		if (GetBoostNow() == true)
//		{
		if (!GetIsOnGroundBool())
		{//着地状態でない時
			// 前方
			if (angle >= -D3DX_PI / 4 && angle <= D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_FRONT); // 前移動
				m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_FRONT;
			}
			// 左方向
			else if (angle > D3DX_PI / 4 && angle <= 3 * D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_LEFT); // 左移動
				m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_LEFT;
			}
			// 右方向
			else if (angle < -D3DX_PI / 4 && angle >= -3 * D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_RIGHT); // 右移動
				m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_RIGHT;
			}
			// 後方
			else
			{
				SetNowMotion_Parent(MOTIONTYPE_HIGH_MOVE_BACK); // 後移動
				m_OldInputMotionParent = MOTIONTYPE_HIGH_MOVE_BACK;
			}
		}
		else
		{
			// 前方
			if (angle >= -D3DX_PI / 4 && angle <= D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT); // 前移動
				m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;
			}
			// 右方向
			else if (angle > D3DX_PI / 4 && angle <= 2 * D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT); // 右移動
				m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;
			}
			// 左方向
			else if (angle < -D3DX_PI / 4 && angle >= -2 * D3DX_PI / 4)
			{
				SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT); // 左移動
				m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;
			}
			// 後方
			else
			{
				SetNowMotion_Parent(MOTIONTYPE_MOVE_BACK); // 後移動
				m_OldInputMotionParent = MOTIONTYPE_MOVE_BACK;
			}
		}
	}
	else
	{//移動がなかった場合

		if (GetNowMotionParent() != MOTIONTYPE_STANDBY &&
			GetNowMotionParent() != MOTIONTYPE_JUMP &&
			GetNowMotionParent() != MOTIONTYPE_RANDING &&
			GetNowMotionParent() != MOTIONTYPE_ATTACK)
		{
			// モーション変動
			SetNowMotion_Parent(MOTIONTYPE_STANDBY); // 待機

			m_OldInputMotionParent = MOTIONTYPE_STANDBY; // 移動系入力を保持
		}

		if (GetNowMotionSub() != MOTIONTYPE_ATTACK)
		{//モーション変動
			SetNowMotion_Sub(MOTIONTYPE_STANDBY);//待機

			m_OldInputMotionParent = MOTIONTYPE_STANDBY;//移動系入力を保持
		}

	}














	//-------------------------------------------------------------------------------------------------------------------------
	//右スティック

	bool MoveNowCom2 = false;//入力の有無(コントローラ)

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Aがおされた(左)
	//	Xdate = 1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Dがおされた(右)
	//	Xdate = -1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Wがおされた(上)
		//Zdate = -1.0f;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 6000))
	{//Sがおされた(下)
		//Zdate = 1.0f;
		MoveNowCom2 = true;
	}

	int sThumbRX = joykeystate.Gamepad.sThumbRX;
	int sThumbRY = joykeystate.Gamepad.sThumbRY;

	// スティックの入力値からベクトルの大きさを計算
	float magnitude = std::sqrt(static_cast<float>(sThumbRX * sThumbRX) + static_cast<float>(sThumbRY * sThumbRY));

	float vecX, vecY;

	if (magnitude > 0)
	{
		// 値を正規化（単位ベクトルを計算）
		vecX = sThumbRX / magnitude;
		vecY = sThumbRY / magnitude;
		// ターゲットの位置を計算
//		m_TargetPos.x = classData.Pos.x + vecX * 500.0f; // X方向に一定距離進む
	//	m_TargetPos.y = (classData.Pos.y + 150.0f) + vecY * 500.0f; // Y方向に一定距離進む
	//	m_TargetPos.z = 0;

	}
	else
	{
		// スティックが中央の場合はベクトルを0に
		vecX = 0.0f;
		vecY = 0.0f;
	}

	float MoveSpeed2 = MOVESPEED;

	//if (MoveNowCom2 == false)
	//{

	//}
	//else
	//{//Controller

	//	//Controller移動

	//	float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbRX, (float)-joykeystate.Gamepad.sThumbRY);//これが方角

	//	fRotDest = (Angle2 - CameraRot.y - (1.0f * D3DX_PI));

	//	D3DXVECTOR3 ESCTargetMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	if (GetBoostNow() == true)
	//	{
	//		if (m_nBoostCnt <= BOOST_FARAME && m_nBoostCnt > BOOST_FARAME * 0.5f)
	//		{//序盤
	//			ESCTargetMove.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 4.0f;//三角関数利用して移動の長さを代入
	//			ESCTargetMove.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 4.0f;//三角関数利用して移動の長さを代入

	//		}
	//		else
	//		{//終盤

	//			ESCTargetMove.x += (joykeystate.Gamepad.sThumbLX * JoyStickDiff) * 3.0f;//三角関数利用して移動の長さを代入
	//			ESCTargetMove.z += (joykeystate.Gamepad.sThumbLY * JoyStickDiff) * 3.0f;//三角関数利用して移動の長さを代入
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


	//飛翔
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
// 残機格納
//=============================
void CObjectMotionPlayer::SetPlayerNum(int SetNum)
{
	m_nNumPlayerAll = SetNum;
}
//=============================
// 残機取得
//=============================
int CObjectMotionPlayer::GetPlayerNum()
{
	return m_nNumPlayerAll;
}
//=============================
// Restart地点格納
//=============================
void CObjectMotionPlayer::SetStartPos(D3DXVECTOR3 pos)
{
	m_RESTART_POS = pos;
}
//=============================
// 射撃位置取得
//=============================
D3DXVECTOR3 CObjectMotionPlayer::GetTARGETPOS()
{
	return m_TargetPos;
}

//=============================
// 線形補完地点描画
//=============================
void CObjectMotionPlayer::SetLinearInterpolation()
{

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();



				//動くモデルのデータ
	CModelParts* pParts = GetModelParts(GetChangeDataPartsIndex());

	D3DXMATRIX pMat = pParts->GetMtxWorld();

	D3DXMATRIX pMat2 = pParts->GetMtxWorld();

	D3DXMATRIX EscMtxWorld;
	D3DXMATRIX EscMtxWorld2;

	D3DXMATRIX mtxTrans;//計算用マトリックス

	D3DXMATRIX mtxTrans2;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&EscMtxWorld);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, 0.0f, SHOTPOS_Y, SHOTPOS_Z);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//自分の親のマトリックス欠けてる
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);



	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&EscMtxWorld2);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans2, 0.0f, 0.0f, SHOTPOS_Z - 100.0f);

	D3DXMatrixMultiply(&EscMtxWorld2, &EscMtxWorld2, &mtxTrans2);

	//自分の親のマトリックス欠けてる
	D3DXMatrixMultiply(&EscMtxWorld2, &EscMtxWorld2, &pMat2);

	//Mouseの方向にballetを飛ばす
	//----------------------------------------------------------------------------------

	DATA SetData;
	SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

	D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41, pMat._42/*BULLET_SHOT_POS_Y*/, /*pMat._43*/0.0f);

	//Mouseで画面に指してる3D空間座標取得
//			D3DXVECTOR3 TargetPos = m_TargetPos;
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(EscMtxWorld2._41, EscMtxWorld2._42, 0.0f);


	// TargetPos から SetData.Pos への方向ベクトルを計算
	D3DXVECTOR3 direction = TargetPos - DirectionPos;

	// 方向ベクトルを正規化（単位ベクトルにする）
	D3DXVec3Normalize(&direction, &direction);


	float speed = (int)BULLETSPEED;//速度(後々変更)
	SetData.move = direction * (speed*0.7f);//速度をかける

	// 5箇所の中間地点を格納
	for (int i = 0; i < 7; ++i) 
	{
		
		SetData.Pos +=  SetData.move ; // 線形補間により中間地点を計算
	//	CObjectLINEUI::Create(SetData.Pos);
	}

}
//=============================
// 敵ロックオン処理
//=============================
void CObjectMotionPlayer::LockOnEnemy()
{
}
//=============================
// スクリーン座標が画面内にあるかどうかを判定
//=============================
bool IsInScreen(D3DXVECTOR3 screenPosition)
{
	return (screenPosition.x >= 0 && screenPosition.x <= SCREEN_WIDTH &&
		screenPosition.y >= 0 && screenPosition.y <= SCREEN_HEIGHT &&
		screenPosition.z >= 0 && screenPosition.z <= 1);
}


////=============================
//// ダウン状態格納
////=============================
//void CObjectMotionPlayer::SetDawn(bool Dawn)
//{
//	m_bDown = Dawn;
//}
////=============================
//// ダウン状態取得
////=============================
//bool CObjectMotionPlayer::GetDawn()
//{
//	return m_bDown;
//}

