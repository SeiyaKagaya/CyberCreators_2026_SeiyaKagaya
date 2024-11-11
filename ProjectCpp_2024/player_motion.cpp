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
	fLength[0] = 90.0f;
	fLength[1] = 90.0f;
	fLength[2] = 120.0f;

	m_nMoveCnt = 0;

	SetOBBLength(fLength);//OBB長さ格納


	DATA classData = GetClassData();

	classData.Pos = m_RESTART_POS;

	SetClassData(classData);

	m_nLife = 300;
	//m_bDown = false;
	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	CInputKeyboard* keyboard = pManager->GetKeyboard();

	keyboard->GetMouseRayIntersection(*pManager->GetCamera());//マウス位置

//	m_TargetPos = keyboard->GetScreenPosRayIntersection(*pManager->GetCamera(), D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));//マウス位置
	m_TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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


	if (NowState == CScene::MODE_GAME || NowState == CScene::MODE_GAME2)
	{//ゲーム中

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

			//ショイパットの状態を取得
			DWORD dwResult = XInputGetState(0, &joykeystate);

			//Mouseで画面に指してる3D空間座標取得
			D3DXVECTOR3 TargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


			//操作方法--falseでキーマウ/trueはパッド
		//	pManager->bSetInputState(false);



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


			DATA classData = GetClassData();










			//2D
			//--------------------------------------
			//照準位置制限(自機より円形)

			if (pManager->bGetInputState() == true)
			{//操作方法--trueでコントローラー
				D3DXVECTOR3 PlayerPos = GetClassData().Pos;
				float fRadius = 600.0f;

				//m_TargetPosをこの円の中に収める

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
			//--------------------------------------



	


		

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

							m_nLife -= 100;
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

								m_nLife -= 100;
							}
						}

					}
				}
			}

						
			
			//for (int i = 0; i < GetMaxLoadPartsNum(); i++)
			//{//パーツもDEATH
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
				{//パーツもDEATH
					GetModelParts(i)->DrawOkBool(false);

					Explosion3D::Create(GetClassData().Pos);




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



			//重力
			if (!GetIsOnGroundBool())
			{//着地状態でない時

				//重力
				classData.move.y -= GRAVITY * 0.1f;
			}
			else
			{//着地
	//			classData.Pos.y = 0.0f;

			}
			SetClassData(classData);



			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
			//当たり判定本体

			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_HITBOX, LAYERINDEX_HITBOX, classData.move, this);

			if (m_HitData.HitAngle.y==1.0f)
			{
				bHit = true;
			}

			//当たり判定計算
			m_HitData = CMathProc::CheckBoxCollision_3D(OBJECT_MOTIONPLAYER, classData.Pos, classData.OldPos, classData.MinLength, classData.MaxLength, OBJECT_OBSTACLE, LAYERINDEX_OBSTACLE, classData.move, this);

			if (m_HitData.HitAngle.y == 1.0f)
			{
				bHit = true;
			}
			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

			classData = GetClassData();


			// 移動処理
			// moveでpos移動
			// 重力処理
			// 重力でpos移動
			
			// 地面接触の判定
			
			// 地面接触の判定
			
			// 地面接触の判定


			if (!GetIsLandingTriggerBool())
			{//着地している状態でない時
				// 接地判定
				if (bHit || classData.Pos.y <= 0.0f)
				{//接触
					/*if (classData.Pos.y <= 0.0f)
					{

					}*/


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
				// 接地状態の解除
				SetIsOnGroundBool(false);
			}

			// モーション再生処理
			// 空中モーションの処理
			if (!GetIsOnGroundBool() && !GetIsLandingTriggerBool())
			{//着地状態じゃないかつ着地瞬間じゃない
				SetNowMotion_Parent(MOTIONTYPE_JUMP); // 空中モーションの再生
			}

			// 着地モーションのトリガー
			if (GetIsLandingTriggerBool() && GetIsOnGroundBool())
			{//着地状態かつ着地瞬間
				SetNowMotion_Parent(MOTIONTYPE_RANDING); // 着地モーションの再生
				SetIsLandingTriggerBool(false); // 着地トリガーをリセット
			}








			SetClassData(classData);


















			classData = GetClassData();


			//ターゲットの方向に砲口を向ける
			  //----------------------------------------------------------------------------------

			DATA ChangeData = DataInit();

			float minYAngle = -0.1f; // 下側の角度の限界
			float maxYAngle = 0.1f;  // 上側の角度の限界


			//方向
			D3DXVECTOR3 enemyDirection = D3DXVECTOR3(TargetPos.x, TargetPos.y, TargetPos.z) - classData.Pos;

			// XZ平面上の角度
			float angleXZ = atan2f(enemyDirection.z, enemyDirection.x);

			ChangeData.rot.x = 0.0f; // よじりを防ぐために必要な調整
			ChangeData.rot.y = -(angleXZ + 1.57f); // 腰を向ける
			ChangeData.rot.z = 0.0f;

			//		 Y軸の角度
			float angleY = atan2f(enemyDirection.y, sqrtf(enemyDirection.x * enemyDirection.x + enemyDirection.z * enemyDirection.z));

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


			//線形補完地点
			SetLinearInterpolation();







			//// 親の向きを考慮して補正
			//float parentAngle = atan2f(g_Model.ModelParts[g_Model.ModelParts[1].PEARENT].mtxWorld._31, g_Model.ModelParts[g_Model.ModelParts[1].PEARENT].mtxWorld._11);
			//ESCROT.y -= parentAngle;

			//// 位置を反映
			//D3DXMatrixTranslation(&mtxTrans, g_Model.ModelParts[1].Pos.x, g_Model.ModelParts[1].Pos.y - 70.0f, g_Model.ModelParts[1].Pos.z);

			//D3DXMatrixMultiply(&g_Model.ModelParts[1].mtxWorld, &g_Model.ModelParts[1].mtxWorld, &mtxTrans);


			if (classData.Pos.y<=0)
			{
				classData.Pos.y = 0;
			}


			SetClassData(classData);




			CObjectMotion::Update();//------------------更新

			classData = GetClassData();
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

			
			}

		}
	}
	else if (NowState == CScene::MODE_TITLE)
	{//タイトル
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

		//基底クラスからパーツにデータを受け渡し
		SetChangeDataInObjectMotion(Head);

		CObjectMotion::Update();//------------------更新


		SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//移動motion
		SetNowMotion_Sub(MOTIONTYPE_MOVE_FRONT);//移動motion


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

		//基底クラスからパーツにデータを受け渡し
		SetChangeDataInObjectMotion(Head);

		CObjectMotion::Update();//------------------更新


		SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//移動motion
		SetNowMotion_Sub(MOTIONTYPE_MOVE_FRONT);//移動motion


	}



}

//=============================
// 描画
//=============================
void CObjectMotionPlayer::Draw()
{
//	if (m_bDown == false)
////	{
//		for (int i = 0; i < GetMaxLoadPartsNum(); i++)
//		{//パーツもDEATH
//			GetModelParts(i)->SetColorChangeBool(true);
//			GetModelParts(i)->SetChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
//		}
//
//		CObjectMotion::Draw();
//	}
//	else
//	{
//		for (int i = 0; i < GetMaxLoadPartsNum(); i++)
//		{//パーツもDEATH
//			GetModelParts(i)->SetColorChangeBool(true);
//			GetModelParts(i)->SetChangeColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
//
//		}

		CObjectMotion::Draw();
//	}

#if _DEBUG

	/*if (btest == true)
	{
		const char* aData = "接触";


		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);
	}
	else if (btest == false)
	{
		const char* aData = "みす";

		CFont::DrawTextSet(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 50, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), aData);
	}*/

	
	char cData2[100] = {};
	snprintf(cData2, sizeof(cData2), "現在のGRID/%d", (int)GetNowGRIDNum()); // 数値を文字列に変換してCDataにコピー
	// mousePos.x と mousePos.y がマウスの位置
	CFont::DrawTextSet(D3DXVECTOR3(1000.0f, 550.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), cData2);

#endif // 

	//char cData3[100] = {};
	//snprintf(cData3, sizeof(cData3), "現在のtama/%d", CBullet3D::GetNumBuulet()); // 数値を文字列に変換してCDataにコピー
	//// mousePos.x と mousePos.y がマウスの位置
	//CFont::DrawTextSet(D3DXVECTOR3(1000.0f, 550.0f, 0.0f), 40, CFont::FONT_DIGITAL, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), cData3);


	
}

//=============================
// 生成
//=============================
CObjectMotionPlayer* CObjectMotionPlayer::Create(const char* pfilePass, DATA SetData)
{
	CObjectMotionPlayer* pObstacle = new CObjectMotionPlayer;

	pObstacle->SetFilePass(pfilePass);//パス格納
	pObstacle->SetStartPos(SetData.Pos);
	pObstacle->Init();

	// 取得
	DATA EscData = pObstacle->GetClassData();
	SetData.Radius = 110.0f;
	SetData.MaxLength = D3DXVECTOR3((float)AABB_BOX_PLAYER, (float)AABB_BOX_PLAYER*2.5f, (float)AABB_BOX_PLAYER);
	SetData.MinLength = D3DXVECTOR3(-(float)AABB_BOX_PLAYER, 0.0f, -(float)AABB_BOX_PLAYER);
	pObstacle->SetClassData(SetData);



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



	//中間点までの距離
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//差分を半分に

	//中間点をたしてデッドゾーンと最大点の中間点を算出(通常入力、微入力の判別分岐点)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;

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



	if (keyboard->GetPress(DIK_LSHIFT)==true)
	{//左ボタンが押された
		classData.move.y += 35.0f;
	}

	if (keyboard->GetPress(DIK_LCONTROL) == true)
	{//左ボタンが押された
		classData.move.y -= 3.0f;
	}


	//移動する状態の時
	if (bMoveNow == true)
	{
		m_nMoveCnt++;


		SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//移動motion
		m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//移動系入力を保持

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
	else
	{//移動入力なし

		int Test = GetNowMotionParent();

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
		{//左ボタンが押された

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


			float speed = 14.0f;//速度(後々変更)
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

			SetNowMotion_Sub(MOTIONTYPE_ATTACK);//攻撃motion
			
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


	//中間点までの距離
	float fEscape = (32000 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000) / 2.0f;//差分を半分に

	//中間点をたしてデッドゾーンと最大点の中間点を算出(通常入力、微入力の判別分岐点)
	float BranchPoint = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 6000 + fEscape;


	bool bMoveNow = false;

	float Xdate = 0.0f;
	float Zdate = 0.0f;

	float fRotDest = 0.0f;

	bool MoveNow = false;//移動入力できてるか


//	float MoveSpeed = 4.5f * 1.8f;

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


		SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//移動motion

		m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//移動系入力を保持

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
	else
	{//移動入力なし

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
			D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &mtxTrans);

			//自分の親のマトリックス欠けてる
			D3DXMatrixMultiply(&EscMtxWorld, &EscMtxWorld, &pMat);


			//Mouseの方向にballetを飛ばす
			//----------------------------------------------------------------------------------

			DATA SetData;
			SetData.Pos = D3DXVECTOR3(EscMtxWorld._41, EscMtxWorld._42, EscMtxWorld._43);

			D3DXVECTOR3 DirectionPos = D3DXVECTOR3(pMat._41, pMat._42/*BULLET_SHOT_POS_Y*/, /*pMat._43*/0.0f);


			//Mouseで画面に指してる3D空間座標取得
			D3DXVECTOR3 TargetPos = m_TargetPos;
		//	SetData.Pos = classData.Pos;
		///	SetData.Pos.y = 150.0f;//test---------------------------------------------------------------------

			// TargetPos から SetData.Pos への方向ベクトルを計算
			D3DXVECTOR3 direction = TargetPos - DirectionPos;

			// 方向ベクトルを正規化（単位ベクトルにする）
			D3DXVec3Normalize(&direction, &direction);


			float speed = 14.0f;//速度(後々変更)
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
				SetNowMotion_Sub(MOTIONTYPE_ATTACK);//攻撃motion

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
	























	
	






	////----------------------------------------------------------------------------------------------------------コントローラー


	
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
		SetNowMotion_Parent(MOTIONTYPE_MOVE_FRONT);//移動
		m_OldInputMotionParent = MOTIONTYPE_MOVE_FRONT;//移動系入力を保持

		m_nMoveCnt++;


		if (m_nMoveCnt >= CObjectFootPrint::STANPFLAME)
		{
			m_nMoveCnt = 0;
			CObjectFootPrint::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z), classData.rot);
		//	CMoveSmoke::Create(D3DXVECTOR3(classData.Pos.x, 3.0f, classData.Pos.z));
		}

		//float DDIIFF = 12000.0f;

		////通常入力まで倒していか
		//if (BranchPoint + DDIIFF <= joykeystate.Gamepad.sThumbLY  || -BranchPoint - DDIIFF >= joykeystate.Gamepad.sThumbLY )
		//{
		//	bNomalMove = true;//通常移動状態にする
		//}
		//if (BranchPoint + DDIIFF <= joykeystate.Gamepad.sThumbLX  || -BranchPoint - DDIIFF >= joykeystate.Gamepad.sThumbLX )
		//{
		//	bNomalMove = true;//通常移動状態にする
		//}

		//if (bNomalMove == true)
		//{//通常移動時
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
		m_TargetPos.x = classData.Pos.x + vecX * 500.0f; // X方向に一定距離進む
		m_TargetPos.y = (classData.Pos.y + 150.0f) + vecY * 500.0f; // Y方向に一定距離進む
		m_TargetPos.z = 0;

	}
	else 
	{
		// スティックが中央の場合はベクトルを0に
		vecX = 0.0f;
		vecY = 0.0f;
	}

	








//	D3DXVECTOR3 BulletMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float MoveSpeed2 = MOVESPEED*2.0f;

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

		//変換
		//	classData.rot.y = CMathProc::ConversionRot2(classData.rot.y, fRotDest + D3DX_PI);
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
		//float DDIIFF = 12000.0f;

		////通常入力まで倒していか
		//if (BranchPoint + DDIIFF <= joykeystate.Gamepad.sThumbRY || -BranchPoint - DDIIFF >= joykeystate.Gamepad.sThumbRY )
		//{
		//	bNomalMove = true;//通常移動状態にする
		//}
		//if (BranchPoint + DDIIFF <= joykeystate.Gamepad.sThumbRX || -BranchPoint - DDIIFF >= joykeystate.Gamepad.sThumbRX )
		//{
		//	bNomalMove = true;//通常移動状態にする
		//}

		m_BulletPosMove = D3DXVECTOR3(joykeystate.Gamepad.sThumbRX * 0.0015f, 0.0f, joykeystate.Gamepad.sThumbRY * 0.0015f);

		//if (bNomalMove == true)
		//{//通常移動時
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
void CObjectMotionPlayer::SetStartPos(D3DXVECTOR3 pos)
{
	m_RESTART_POS = pos;
}
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
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, -190.0f);

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


	float speed = 14.0f;//速度(後々変更)
	SetData.move = direction * speed;//速度をかける


	// SetData.rot.y をターゲットの方向に合わせる
	SetData.rot.x = 0.0f;
	SetData.rot.y = (float)atan2(direction.x, direction.z) + D3DX_PI;
	SetData.rot.z = 0.0f;



	D3DXVECTOR3 Pos[7];

	// 発射地点（SetData.Pos）と照準地点（m_TargetPos）を使って5つの中間地点を計算
	D3DXVECTOR3 startPos = SetData.Pos;  // 発射地点
	D3DXVECTOR3 targetPos = m_TargetPos; // 照準地点

	// 発射地点から照準地点までの方向ベクトルを計算
	direction = targetPos - startPos;

	// 方向ベクトルを5等分する
	float step = 1.0f / 6.0f; // 5箇所の中間地点を計算するためのステップ（0, 0.25, 0.5, 0.75, 1.0）

	// 5箇所の中間地点を格納
	for (int i = 0; i < 7; ++i) 
	{
		float t = i * step; // 線形補間の割合
		Pos[i] = startPos + direction * t; // 線形補間により中間地点を計算
	}


	for (int i = 1; i < 10; ++i)
	{
	//	CObjectLINEUI::Create(Pos[i]);
	}
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

