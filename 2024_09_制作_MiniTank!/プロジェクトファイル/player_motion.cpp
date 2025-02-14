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

int CObjectMotionPlayer::m_nNumPlayerAll = START_PLAYER_NUM;//初期値

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
	fLength[0] = OBB_LENGTH[0];
	fLength[1] = OBB_LENGTH[1];
	fLength[2] = OBB_LENGTH[2];

	m_nMoveCnt = 0;

	SetOBBLength(fLength);//OBB長さ格納

	DATA classData = GetClassData();

	SetClassData(classData);

	m_nLife = LIFE;

	CRenderer* pRenderer = nullptr;
	CManager* pManager = CManager::GetInstance();
	CInputKeyboard* keyboard = pManager->GetKeyboard();

	keyboard->GetMouseRayIntersection(*pManager->GetCamera());//マウス位置

	m_TargetPos = keyboard->GetScreenPosRayIntersection(*pManager->GetCamera(), D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));//マウス位置

	CScene::MODE NowState = CScene::GetNowScene();

	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_GAME4)
	{//ゲーム中
		m_pHPUI = CObjectHPLatterUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pHPGauge[0] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pHPGauge[1] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	else if (NowState == CScene::MODE_TITLE|| NowState == CScene::MODE_RESULT)
	{//タイトル		
	}
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


	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2 || NowState == CScene::MODE_GAME3 || NowState == CScene::MODE_GAME4)
	{//ゲーム中
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

			//ショイパットの状態を取得
			DWORD dwResult = XInputGetState(0, &joykeystate);

			//Mouseで画面に指してる3D空間座標取得
			D3DXVECTOR3 TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			m_TargetPos += m_BulletPosMove;

			//移動量を更新(疑似慣性で減衰)
			m_BulletPosMove.x += (0.0f - m_BulletPosMove.x) * (DAMPING_RATIO);
			m_BulletPosMove.y += (0.0f - m_BulletPosMove.y) * (DAMPING_RATIO);
			m_BulletPosMove.z += (0.0f - m_BulletPosMove.z) * (DAMPING_RATIO);
			
			if (dwResult == ERROR_SUCCESS)
			{//パッド接続あり
			}
			else
			{
				pManager->bSetInputState(false);
			}
			
			if (pManager->bGetInputState() == true)
			{//操作方法--trueでコントローラー
				//キーボード/コントローラー入力反映(移動)
				ControllerInput();
				TargetPos = m_TargetPos;
			}
			else
			{//キーボード入力反映(移動)
				Input();

				TargetPos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());//マウス位置

				m_TargetPos = TargetPos;
			}

			m_TargetPos += GetClassData().move;

			//--------------------------------------
			//照準位置制限(自機より円形)

			if (pManager->bGetInputState() == true)
			{//操作方法--trueでコントローラー
				D3DXVECTOR3 PlayerPos = GetClassData().Pos;
				
				//ベクトル計算
				D3DXVECTOR3 VEC = m_TargetPos - PlayerPos;

				//ベクトルの長さ
				float fDistance = D3DXVec3Length(&VEC);

				//長さが半径を超えた
				if (fDistance > STICK_RADIUS)
				{
					// ベクトルを正規化
					D3DXVec3Normalize(&VEC, &VEC);

					// ベクトルの方向に半径切りまで動かす
					m_TargetPos = PlayerPos + VEC * STICK_RADIUS;
				}
			}
			//--------------------------------------

			CObjectTargetUI::Create(m_TargetPos);
			CObjectTargetUI::Create(m_TargetPos);
			CObjectTargetUI::Create(m_TargetPos);

			CObjectMotion::Update();//更新

			DATA classData = GetClassData();

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
				{//パーツもDEATH
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
			}

			SetClassData(classData);

			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);

			classData = GetClassData();

			//ターゲットの方向に砲口を向ける
			  //----------------------------------------------------------------------------------

			DATA ChangeData = DataInit();

			//方向
			D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, TargetPos.y, TargetPos.z) - classData.Pos;

			// XZ平面上の角度
			float angleXZ = atan2f(enemyDirection.z, enemyDirection.x);

			ChangeData.rot.x = 0.0f; // よじりを防ぐために必要な調整
			ChangeData.rot.y = -(angleXZ + D3DX_PI*0.5f); // 腰を向ける
			ChangeData.rot.z = 0.0f;

			//		 Y軸の角度
			float angleY = atan2f(enemyDirection.y, sqrtf(enemyDirection.x * enemyDirection.x + enemyDirection.z * enemyDirection.z));

			// Y軸角度をクランプ
			if (angleY < MIN_ANGLE_Y)
			{
				angleY = MIN_ANGLE_Y;
			}
			else if (angleY > MAX_ANGLE_Y)
			{
				angleY = MAX_ANGLE_Y;
			}

			ChangeData.rot.x = angleY; // Y方向を向ける

			//基底クラスからパーツにデータを受け渡し
			SetChangeDataInObjectMotion(ChangeData);


			//線形補完地点
			SetLinearInterpolation();
			SetClassData(classData);

		}
		else
		{
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

				m_pHPUI = CObjectHPLatterUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pHPGauge[0] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pHPGauge[1] = CObjectHPGaugeUI::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				m_Resue->SetDeath(true);
			}
		}
	}
	else if (NowState == CScene::MODE_TITLE)
	{//タイトル
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

		//基底クラスからパーツにデータを受け渡し
		SetChangeDataInObjectMotion(Head);

		CObjectMotion::Update();//------------------更新

		SetNowMotion_Parent(1);//移動motion
		SetNowMotion_Sub(1);//移動motion

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

		//基底クラスからパーツにデータを受け渡し
		SetChangeDataInObjectMotion(Head);

		CObjectMotion::Update();//------------------更新

		SetNowMotion_Parent(1);//移動motion
		SetNowMotion_Sub(1);//移動motion
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
CObjectMotionPlayer* CObjectMotionPlayer::Create(const char* pfilePass, DATA SetData)
{
	CObjectMotionPlayer* pObstacle = new CObjectMotionPlayer;

	pObstacle->SetFilePass(pfilePass);//パス格納

	pObstacle->Init();

	// 取得
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)AABB_BOX_PLAYER, (float)AABB_BOX_PLAYER*2.0f, (float)AABB_BOX_PLAYER);
	SetData.MinLength = D3DXVECTOR3(-(float)AABB_BOX_PLAYER, 0.0f, -(float)AABB_BOX_PLAYER);
	pObstacle->SetClassData(SetData);

	pObstacle->SetStartPos(SetData.Pos);

	return pObstacle;
}

//=============================
//キーボード入力
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

	//球を生成してよいかを検索
	bool bNoShot = false;
	bool bShot = false;
	//----------------------------------------------------------------------------------------------------------キーボード
	//キーボード
	if (keyboard->GetPress(DIK_A) == true)
	{//Aがおされた(左)
		Xdate =	1;
		bMoveNow = true;
	}
	else if (keyboard->GetPress(DIK_D) == true)
	{//Dがおされた(右)
		Xdate = -1;
		bMoveNow = true;
	}

	if (keyboard->GetPress(DIK_W) == true)
	{//Wがおされた(上)
		Zdate = -1.0f;
		bMoveNow = true;
	}
	else if (keyboard->GetPress(DIK_S) == true)
	{//Sがおされた(下)
		Zdate = 1.0f;
		bMoveNow = true;
	}

	//移動する状態の時
	if (bMoveNow == true)
	{
		m_nMoveCnt++;

		SetNowMotion_Parent(1);//移動motion

		float Angle = atan2f(Xdate, Zdate);//これが方角

		CCamera* pCamera = pManager->GetCamera();

		D3DXVECTOR3 CameraRot = pCamera->GetRot();

		//------これは差分
		fRotDest = (Angle - CameraRot.y - (1.0f * D3DX_PI));
		
		classData.move.x = sinf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//三角関数利用して移動の長さを代入
		classData.move.z = cosf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//三角関数利用して移動の長さを代入
		
		//変換
		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
	}

#if 1

	if (ShotDelay <= 0)
	{
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left))
		{//左ボタンが押された

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

			//Mouseの方向にballetを飛ばす
			//----------------------------------------------------------------------------------

			DATA SetData;
			SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

			D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41,/* pMat._42*/BULLET_SHOT_POS_Y, pMat._43);

			//Mouseで画面に指してる3D空間座標取得
			D3DXVECTOR3 TargetPos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

			TargetPos.y = BULLET_SHOT_POS_Y;

			// TargetPos から SetData.Pos への方向ベクトルを計算
			D3DXVECTOR3 direction = TargetPos - DirectionPos;

			// 方向ベクトルを正規化（単位ベクトルにする）
			D3DXVec3Normalize(&direction, &direction);

			SetData.move = direction * BULLETMOVE;//速度をかける

			// SetData.rot.y をターゲットの方向に合わせる
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
				SetNowMotion_Sub(2);//攻撃motion

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
// Controller入力
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

		//ショイパットの状態を取得
		DWORD dwResult = XInputGetState(0, &joykeystate);


	bool bMoveNow = false;

	float Xdate = 0.0f;
	float Zdate = 0.0f;

	float fRotDest = 0.0f;

	bool MoveNow = false;//移動入力できてるか


	DATA classData = GetClassData();

	//球を生成してよいかを検索
	bool bNoShot = false;
	bool bShot = false;
	bool bNomalMove = false;

	//----------------------------------------------------------------------------------------------------------キーボード
	//キーボード
	if (keyboard->GetPress(DIK_A) == true)
	{//Aがおされた(左)
		Xdate = 1;
		bMoveNow = true;
		bNomalMove = true;//通常移動状態にする
	}
	else if (keyboard->GetPress(DIK_D) == true)
	{//Dがおされた(右)
		Xdate = -1;
		bMoveNow = true;
		bNomalMove = true;//通常移動状態にする
	}

	if (keyboard->GetPress(DIK_W) == true)
	{//Wがおされた(上)
		Zdate = -1.0f;
		bMoveNow = true;
		bNomalMove = true;//通常移動状態にする
	}
	else if (keyboard->GetPress(DIK_S) == true)
	{//Sがおされた(下)
		Zdate = 1.0f;
		bMoveNow = true;
		bNomalMove = true;//通常移動状態にする
	}

	//移動する状態の時
	if (bMoveNow == true)
	{
		m_nMoveCnt++;

		SetNowMotion_Parent(1);//移動motion

		float Angle = atan2f(Xdate, Zdate);//これが方角

		CCamera* pCamera = pManager->GetCamera();

		D3DXVECTOR3 CameraRot = pCamera->GetRot();

		//------これは差分
		fRotDest = (Angle - CameraRot.y - (1.0f * D3DX_PI));

		classData.move.x = sinf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//三角関数利用して移動の長さを代入
		classData.move.z = cosf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//三角関数利用して移動の長さを代入

	//変換
		classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);

	}

#if 1

	if (ShotDelay <= 0)
	{
		if (keyboard->GetMouseButtonTrigger(CInputKeyboard::MouseKey_Left) || joykeystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{//左ボタンが押された

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


			//Mouseの方向にballetを飛ばす
			//----------------------------------------------------------------------------------

			DATA SetData;
			SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

			D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41,/* pMat._42*/BULLET_SHOT_POS_Y, pMat._43);

			//Mouseで画面に指してる3D空間座標取得
			D3DXVECTOR3 TargetPos = m_TargetPos;

			TargetPos.y = BULLET_SHOT_POS_Y;

			// TargetPos から SetData.Pos への方向ベクトルを計算
			D3DXVECTOR3 direction = TargetPos - DirectionPos;

			// 方向ベクトルを正規化（単位ベクトルにする）
			D3DXVec3Normalize(&direction, &direction);

			SetData.move = direction * BULLETMOVE;//速度をかける

			// SetData.rot.y をターゲットの方向に合わせる
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
				SetNowMotion_Sub(2);//攻撃motion

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
	
	////----------------------------------------------------------------------------------------------------------コントローラー	
	bool MoveNowCom = false;//入力の有無(コントローラ)

	if (joykeystate.Gamepad.sThumbLX <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - STICK_SUB))
	{//Aがおされた(左)
	//	Xdate = 1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLX >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - STICK_SUB))
	{//Dがおされた(右)
	//	Xdate = -1;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY >= (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - STICK_SUB))
	{//Wがおされた(上)
		//Zdate = -1.0f;
		MoveNowCom = true;
	}
	else if (joykeystate.Gamepad.sThumbLY <= -(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - STICK_SUB))
	{//Sがおされた(下)
		//Zdate = 1.0f;
		MoveNowCom = true;
	}

	if (MoveNowCom == false)
	{
		//移動する状態の時
		if (bMoveNow == true)
		{
			float Angle = atan2f(Xdate, Zdate);//これが方角

			//------これは差分
			fRotDest = (Angle - CameraRot.y - (1.0f * D3DX_PI));

			classData.move.x = sinf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//三角関数利用して移動の長さを代入
			classData.move.z = cosf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//三角関数利用して移動の長さを代入

		//変換
			classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
			MoveNow = true;
		}
	}
	else
	{//Controller

		//Controller移動

		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbLX, (float)-joykeystate.Gamepad.sThumbLY);//これが方角

		fRotDest = (Angle2 - CameraRot.y - (1.0f * D3DX_PI));

		classData.move.x = sinf(Angle2 - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//三角関数利用して移動の長さを代入
		classData.move.z = cosf(Angle2 - CameraRot.y - (1.0f * D3DX_PI)) * MOVESPEED;//三角関数利用して移動の長さを代入
		MoveNow = true;
	}

	//移動する状態の時
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
	//右スティック

	 bool MoveNowCom2 = false;//入力の有無(コントローラ)

	if (joykeystate.Gamepad.sThumbRX <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - STICK_SUB))
	{//Aがおされた(左)
	//	Xdate = 1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRX >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - STICK_SUB))
	{//Dがおされた(右)
	//	Xdate = -1;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY >= (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - STICK_SUB))
	{//Wがおされた(上)
		//Zdate = -1.0f;
		MoveNowCom2 = true;
	}
	else if (joykeystate.Gamepad.sThumbRY <= -(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - STICK_SUB))
	{//Sがおされた(下)
		//Zdate = 1.0f;
		MoveNowCom2 = true;
	}

	float MoveSpeed2 = 40.0f;

	if (MoveNowCom2 == false)
	{
		//移動する状態の時
		if (bMoveNow == true)
		{
			float Angle = atan2f(Xdate, Zdate);//これが方角

			//------これは差分
			fRotDest = (Angle - CameraRot.y - (1.0f * D3DX_PI));

			m_BulletPosMove.x = sinf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MoveSpeed2;//三角関数利用して移動の長さを代入
			m_BulletPosMove.z = cosf(Angle - CameraRot.y - (1.0f * D3DX_PI)) * MoveSpeed2;//三角関数利用して移動の長さを代入

			MoveNow = true;
		}
	}
	else
	{//Controller
		//Controller移動

		float Angle2 = atan2f((float)-joykeystate.Gamepad.sThumbRX, (float)-joykeystate.Gamepad.sThumbRY);//これが方角

		fRotDest = (Angle2 - CameraRot.y - (1.0f * D3DX_PI));

		m_BulletPosMove.x = sinf(Angle2 - CameraRot.y - (1.0f * D3DX_PI)) * MoveSpeed2;//三角関数利用して移動の長さを代入
		m_BulletPosMove.z = cosf(Angle2 - CameraRot.y - (1.0f * D3DX_PI)) * MoveSpeed2;//三角関数利用して移動の長さを代入
		MoveNow = true;
	}



	//移動する状態の時
	if (MoveNow == true)
	{
		m_BulletPosMove = D3DXVECTOR3(joykeystate.Gamepad.sThumbRX * STICK_MAG, 0.0f, joykeystate.Gamepad.sThumbRY * STICK_MAG);
	}
	//-------------------------------------------------------------------------------------------------------------------------

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
// 初期位置格納
//=============================
void CObjectMotionPlayer::SetStartPos(D3DXVECTOR3 pos)
{
	m_RESTART_POS = pos;
}

//=============================
// 目標地点取得
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

	D3DXMATRIX EscMtxWorld;

	D3DXMATRIX mtxTrans;//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&EscMtxWorld);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, TANKFIRE_OFFSETPOS_Z);

	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

	//自分の親のマトリックス欠けてる
	D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);

	//Mouseの方向にballetを飛ばす
	//----------------------------------------------------------------------------------

	DATA SetData;
	SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

	D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41,/* pMat._42*/BULLET_SHOT_POS_Y, pMat._43);


	//Mouseで画面に指してる3D空間座標取得
	D3DXVECTOR3 TargetPos = keyboard->GetMouseRayIntersection(*pManager->GetCamera());

	TargetPos.y = BULLET_SHOT_POS_Y;

	// TargetPos から SetData.Pos への方向ベクトルを計算
	D3DXVECTOR3 direction = TargetPos - DirectionPos;

	// 方向ベクトルを正規化（単位ベクトルにする）
	D3DXVec3Normalize(&direction, &direction);

	SetData.move = direction * BULLETMOVE;//速度をかける

	// SetData.rot.y をターゲットの方向に合わせる
	SetData.rot.x = 0.0f;
	SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
	SetData.rot.z = 0.0f;

	D3DXVECTOR3 Pos[POINTER_NUM];

	// 発射地点（SetData.Pos）と照準地点（m_TargetPos）を使って5つの中間地点を計算
	D3DXVECTOR3 startPos = SetData.Pos;  // 発射地点
	D3DXVECTOR3 targetPos = m_TargetPos; // 照準地点

	// 発射地点から照準地点までの方向ベクトルを計算
	direction = targetPos - startPos;

	// 方向ベクトルを5等分する
	float step = 1.0f / (float)(POINTER_NUM-1); // 5箇所の中間地点を計算するためのステップ（0, 0.25, 0.5, 0.75, 1.0）

	// 5箇所の中間地点を格納
	for (int i = 0; i < POINTER_NUM; ++i)
	{
		float t = i * step; // 線形補間の割合
		Pos[i] = startPos + direction * t; // 線形補間により中間地点を計算
	}

	for (int i = 1; i < POINTER_NUM; ++i)
	{
		CObjectLINEUI::Create(Pos[i]);
	}
}