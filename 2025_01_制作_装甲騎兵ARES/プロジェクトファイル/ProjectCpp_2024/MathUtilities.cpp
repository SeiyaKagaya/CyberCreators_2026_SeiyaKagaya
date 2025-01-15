//=======================================================
//
//計算処理に関する処理[MathUtilities.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "object.h"
#include "MathUtilities.h"
#include "object.h"
//#include "player.h"
//#include "ballet.h"
//#include "enemy.h"
//#include "polygon.h"

//#include "item.h"
#include "block.h"
//#include "block3D.h"

#include <cmath> // std::absを使用するために必要
#include <vector>//OBB用
#include "line.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "ObstacleSet.h"
#include "enemy_motion_Nomal.h"
#include "StageCollisionBox.h"
#include "player_motion.h"
//#include "ballet3D.h"
//#include "Explosion_Bill.h"
//#include "enemy_motion_fast.h"
#include "Explosion3D.h"
#include "newbullet.h"
#include "renderer.h"
#include "manager.h"

#include"3D-2DhitObject.h"
#include "missile.h"
#include "enemy_motion_fast.h"


//算出用セル
CMathProc::Cell CMathProc::GRID[GRIDROW][GRIDCOL] = {};

//位置番号参照型経路テーブル
 int CMathProc::RouteTable[GRIDROW * GRIDCOL][GRIDROW * GRIDCOL];

 //視界不良時射撃位置
 D3DXVECTOR3 CMathProc::m_ShotPos[SHOTPOINUM];


//// GRID配列の定義
//Cell CMathProc::GRID[ROW][COL];

int CMathProc::dx[4] = { 0, 0, 1, -1 };
int CMathProc::dy[4] = { 1, -1, 0, 0 };

//===================================
//コンスト
//===================================
COBB::COBB()
{

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);              // 位置

	m_Direct[0] = D3DXVECTOR3(1.0f, 0.0f, 0.0f);  // OBB1のX軸方向
	m_Direct[1] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // OBB1のY軸方向
	m_Direct[2] = D3DXVECTOR3(0.0f, 0.0f, 1.0f);  // OBB1のZ軸方向
	for (int i = 0; i < 3; i++)
	{
	//	m_NormaDirect[i] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 方向ベクトル
		m_fLength[i] = 0.0f;             // 各軸方向の長さ
	}
}
//===================================
//デストラクタ
//===================================
COBB::~COBB()
{
}
//===================================
// 指定軸番号の方向ベクトルを取得
//===================================
inline D3DXVECTOR3 COBB::GetDirect(int elem)
{
	return m_Direct[elem];
}
//===================================
// 指定軸方向の長さを取得
//===================================
inline FLOAT COBB::GetLen(int elem)
{
	return m_fLength[elem];
}
//===================================
// 位置を取得
//===================================
inline D3DXVECTOR3 COBB::GetPos()
{
	return m_Pos;
}
void COBB::SetPos(const D3DXVECTOR3& pos)
{
	m_Pos = pos;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

//===================================
//コンスト
//===================================
CMathProc::CMathProc()
{
}
//===================================
//デストラクタ
//===================================
CMathProc::~CMathProc()
{
}
//===================================
//円形あたり判定
//===================================
CMathProc::CollisionData CMathProc::CheckCircleCollision(D3DXVECTOR3 MyPos, float fMy_Radius, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer, void* pCaller, int nID)
{
	CollisionData HitData;

	HitData.bHit = false;
	HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HitData.targetIndex = -1;

	//相手のposと半径

	//とりあえずは処理完成まで仮の変数
//	D3DXVECTOR3 TargetPos = D3DXVECTOR3(500.0f, 500.0f, 0.0f);
//	float ftarget_Radius = 25.0;

	//if (TargetType == CObject::OBJECT_NEWBULLET)
	//{
	//	CRenderer* pRenderer = nullptr;

	//	CManager* pManager = CManager::GetInstance();


	//	for (int i = 0; i < CNewBulletALL::MAXBULLETALL; i++)
	//	{
	//		CNewBulletALL* pBulletAll = pManager->GetNewBulletAll();

	//		CNewBullet* pBullet = pBulletAll->GetBulletData(i);
	//		
	//		if (nID != i)
	//		{//自身じゃないとき
	//			if (pBullet->GetbUse() == true)
	//			{
	//				CObject::DATA EscData = pBullet->GetDATA();

	//				if (pBullet->GetDeathNow() == false)
	//				{//死亡判定じゃない時

	//					EscData.Pos;//相手座標
	//					EscData.Radius;//相手半径


	//					//ここで衝突判定
	//					//どれだけ食い込んでるかも計算

	//					D3DXVECTOR3 diff = MyPos - EscData.Pos; // 2点間の距離
	//					float Distance = D3DXVec3Length(&diff);       // 距離を絶対値に

	//					float HitDistance = fMy_Radius + EscData.Radius;//半径同士足したの長さ

	//					if (HitDistance > Distance)
	//					{//半径同士合算より現在の距離が近い時==接触

	//						HitData.bHit = true;

	//						pBullet->SetGoodby();
	//						//CObjectExplosionBill::Create(EscData.Pos);

	//						break;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
	//else
	//{
		//ここに円形当たり判定追加

		// 配置物プライオリティの先頭を取得
		CObject* pObject = CObject::GetpTop(TargetLayer);

		if (pObject != nullptr)
		{ // 先頭がない==プライオリティまるっとない

			int nIndex = 0;

			while (pObject != nullptr)
			{
				if (pObject->GetObjectType() == TargetType)
				{ // balletモデルのとき
					if (pCaller != pObject)
					{

						D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						CObject::DATA EscData;

						// ここで使用分宣言
						CNewBullet* pNewBullet = {};

						// ここで本来のデータ取得
						switch (TargetType)
						{

						
						case CObject::OBJECT_NEWBULLET:

							pNewBullet = (CNewBullet*)pObject;
							EscData = pNewBullet->GetDATA();

							if (pNewBullet->GetDeathNow() == false)
							{//死亡判定じゃない時

								EscData.Pos;//相手座標
								EscData.Radius;//相手半径


								//ここで衝突判定
								//どれだけ食い込んでるかも計算

								D3DXVECTOR3 diff = MyPos - EscData.Pos; // 2点間の距離
								float Distance = D3DXVec3Length(&diff);       // 距離を絶対値に

								float HitDistance = fMy_Radius + EscData.Radius;//半径同士足したの長さ

								if (HitDistance > Distance)
								{//半径同士合算より現在の距離が近い時==接触

									HitData.bHit = true;

									switch (TargetType)
									{

									
									case CObject::OBJECT_NEWBULLET:
										pNewBullet = (CNewBullet*)pObject;
										//pNewBullet->SetDeath(true);
										pNewBullet->SetGoodby();
								//		CObjectExplosionBill::Create(EscData.Pos);

									case CObject::OBJECT_MAX:
										break;
									}
									break;
								}

							}
							break;

						case CObject::OBJECT_MAX:
							break;
						}




					}
				}

				CObject* pNext = pObject->GetNext();
				pObject = pNext;
				nIndex++;
			}
		}
//	}

	return HitData;
}
//===================================
//箱型当たり判定--3D
//===================================
CMathProc::CollisionData CMathProc::CheckBoxCollision_3D(CObject::OBJECTTYPE MyType, D3DXVECTOR3 MyPos, D3DXVECTOR3 MyOldPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer, D3DXVECTOR3 Mymove, void* pCaller)
{
	//一度でも接触があればtrueに
	bool EscHit = false;

	// 必要に応じて改良、下記は試験運用段階
	CollisionData HitData;

	HitData.bHit = false;
	HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HitData.targetIndex = -1;

	// 自分
	// あたり判定用のHitBox
	D3DXVECTOR3 My_Collision_Min_Pos;
	My_Collision_Min_Pos.x = MyPos.x + MyMinLength.x;
	My_Collision_Min_Pos.y = MyPos.y + MyMinLength.y;
	My_Collision_Min_Pos.z = MyPos.z + MyMinLength.z;

	D3DXVECTOR3 My_Collision_Max_Pos = MyPos + MyMaxLength;

	bool bLandingHit = false;



	//
#if _DEBUG

	//Cline::Create(My_Collision_Max_Pos, D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Max_Pos.y, My_Collision_Max_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	//Cline::Create(My_Collision_Max_Pos, D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Max_Pos.y, My_Collision_Min_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	//Cline::Create(My_Collision_Max_Pos, D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Max_Pos.y, My_Collision_Min_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	///*Cline::Create(D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Max_Pos.y, My_Collision_Min_Pos.z), D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Max_Pos.y, My_Collision_Max_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	//Cline::Create(D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Max_Pos.y, My_Collision_Min_Pos.z), D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Max_Pos.y, My_Collision_Min_Pos.z), D3DXCOLOR(0, 0, 1, 1));


	//Cline::Create(D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Min_Pos.y, My_Collision_Max_Pos.z), D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Min_Pos.y, My_Collision_Max_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	//Cline::Create(D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Min_Pos.y, My_Collision_Max_Pos.z), D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Min_Pos.y, My_Collision_Min_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	//Cline::Create(D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Min_Pos.y, My_Collision_Max_Pos.z), D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Min_Pos.y, My_Collision_Min_Pos.z), D3DXCOLOR(0, 0, 1, 1));

	//Cline::Create(D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Min_Pos.y, My_Collision_Min_Pos.z), D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Min_Pos.y, My_Collision_Max_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	//Cline::Create(D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Min_Pos.y, My_Collision_Min_Pos.z), D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Min_Pos.y, My_Collision_Min_Pos.z), D3DXCOLOR(0, 0, 1, 1));*/

	//Cline::Create(D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Max_Pos.y, My_Collision_Max_Pos.z), D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Min_Pos.y, My_Collision_Max_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	//Cline::Create(D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Max_Pos.y, My_Collision_Min_Pos.z), D3DXVECTOR3(My_Collision_Max_Pos.x, My_Collision_Min_Pos.y, My_Collision_Min_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	//Cline::Create(D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Max_Pos.y, My_Collision_Max_Pos.z), D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Min_Pos.y, My_Collision_Max_Pos.z), D3DXCOLOR(0, 0, 1, 1));
	//Cline::Create(D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Max_Pos.y, My_Collision_Min_Pos.z), D3DXVECTOR3(My_Collision_Min_Pos.x, My_Collision_Min_Pos.y, My_Collision_Min_Pos.z), D3DXCOLOR(0, 0, 1, 1));

#else


#endif // _


	// 配置物プライオリティの先頭を取得
	CObject* pObject = CObject::GetpTop(TargetLayer);

	if (pObject != nullptr)
	{ // 先頭がない==プライオリティまるっとない

		int nIndex = 0;

		while (pObject != nullptr)
		{
			HitData.bHit = false;
			HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			HitData.targetIndex = -1;

			if (pObject->GetObjectType() == TargetType)
			{ // 対象のモデルのとき

				D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				CObject::DATA EscData;

				// ここで使用分宣言
				CNewBullet* pNewBullet = {};
				CMissile* pMissile = {};

				CObstacleSet* pObstacleObject;
				StageCollisionBox* pStageHitBox;
				CStageCollisionBox3D2D* pStageHitBox_2D3D;
				CObjectMotionEnemyNomal* pEnemyNomal;
				CObjectMotionPlayer* pMotionPlayer;
				bool bSkip = false;

				//switch (MyType)
				//{
				//case CObject::OBJECT_MOTIONPLAYER:

				//	EscData=((CObjectMotionPlayer*)pCaller)->GetClassData();
				//	MyPos = EscData.Pos;
				//	break;
				//case CObject::OBJECT_MOTIONENEMY_NOMAL:
				//	EscData=((CObjectMotionEnemyNomal*)pCaller)->GetClassData();
				//	MyPos = EscData.Pos;
				//	break;
				//	// 他の呼び出し元のケース
				//}

				My_Collision_Min_Pos = MyPos + MyMinLength;
				My_Collision_Max_Pos = MyPos + MyMaxLength;



				// ここで本来のデータ取得
				switch (TargetType)
				{
				case CObject::OBJECT_PARTICLE:
					break;

				case CObject::OBJECT_EXPLOSION:
					break;

				case CObject::OBJECT_NEWBULLET:
					pNewBullet = (CNewBullet*)pObject;
					EscData = pNewBullet->GetDATA();

					break;

				case CObject::OBJECT_MISSILE:
					pMissile = (CMissile*)pObject;
					EscData = pMissile->GetDATA();

					break;

				case CObject::OBJECT_OBSTACLE:
					pObstacleObject = (CObstacleSet*)pObject;

					EscData = pObstacleObject->GetDATA();
					break;

				case CObject::OBJECT_HITBOX:
					pStageHitBox = (StageCollisionBox*)pObject;

					EscData = pStageHitBox->GetDATA();
					break;

				case CObject::OBJECT_HITBOX_2D3D:
					pStageHitBox_2D3D = (CStageCollisionBox3D2D*)pObject;

					EscData = pStageHitBox_2D3D->GetDATA();
					break;

				case CObject::OBJECT_MOTIONPLAYER:
					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					EscData = pMotionPlayer->GetClassData();
					break;


				case CObject::OBJECT_MOTIONENEMY_NOMAL:
					pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;

					EscData = pEnemyNomal->GetClassData();
					break;


				case CObject::OBJECT_MAX:
					return HitData;


					break;
				}

				if (CObject::OBJECT_HITBOX_2D3D == TargetType)
				{
					pStageHitBox_2D3D = (CStageCollisionBox3D2D*)pObject;
					if (pStageHitBox_2D3D->GetHitBoxType() == CStageCollisionBox3D2D::TYPE_LEFTSLOPE)
					{
						bSkip = true;
					}
				}

				if (bSkip == false)
				{

					TarGet_Collision_Min_Pos = EscData.Pos + EscData.MinLength;
					TarGet_Collision_Max_Pos = EscData.Pos + EscData.MaxLength;

					D3DXVECTOR3 normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f); // 法線ベクトル

					//---------------------------------------X方向
					if (My_Collision_Min_Pos.z < TarGet_Collision_Max_Pos.z &&
						My_Collision_Max_Pos.z > TarGet_Collision_Min_Pos.z &&
						My_Collision_Max_Pos.x - MyPos.x + MyOldPos.x <= TarGet_Collision_Min_Pos.x &&
						My_Collision_Max_Pos.x > TarGet_Collision_Min_Pos.x &&
						My_Collision_Min_Pos.y < TarGet_Collision_Max_Pos.y &&
						My_Collision_Max_Pos.y > TarGet_Collision_Min_Pos.y)
					{
						MyPos.x = TarGet_Collision_Min_Pos.x + (My_Collision_Min_Pos.x - MyPos.x) - 0.1f; // 接触面押し返し

						HitData.bHit = true;

						HitData.HitAngle.x = -1;

						// 食い込んだ距離の差分(自分中心とあいて面)を計算
						HitData.ResultDistance.x = std::abs(My_Collision_Max_Pos.x - TarGet_Collision_Min_Pos.x);
						normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
					}

					if (My_Collision_Min_Pos.z < TarGet_Collision_Max_Pos.z &&
						My_Collision_Max_Pos.z > TarGet_Collision_Min_Pos.z &&
						My_Collision_Min_Pos.x - MyPos.x + MyOldPos.x >= TarGet_Collision_Max_Pos.x &&
						My_Collision_Min_Pos.x < TarGet_Collision_Max_Pos.x &&
						My_Collision_Min_Pos.y < TarGet_Collision_Max_Pos.y &&
						My_Collision_Max_Pos.y > TarGet_Collision_Min_Pos.y)
					{

						MyPos.x = TarGet_Collision_Max_Pos.x + (My_Collision_Max_Pos.x - MyPos.x) + 0.1f; // 接触面押し返し
						HitData.bHit = true;
						HitData.HitAngle.x = 1;

						// 食い込んだ距離の差分を計算
						HitData.ResultDistance.x = std::abs(TarGet_Collision_Max_Pos.x - My_Collision_Min_Pos.x);
						normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
					}

					//---------------------------------------Z方向
					if (My_Collision_Min_Pos.x < TarGet_Collision_Max_Pos.x &&
						My_Collision_Max_Pos.x > TarGet_Collision_Min_Pos.x &&
						My_Collision_Min_Pos.z - MyPos.z + MyOldPos.z >= TarGet_Collision_Max_Pos.z &&
						My_Collision_Min_Pos.z < TarGet_Collision_Max_Pos.z &&
						My_Collision_Min_Pos.y < TarGet_Collision_Max_Pos.y &&
						My_Collision_Max_Pos.y > TarGet_Collision_Min_Pos.y)
					{

						MyPos.z = TarGet_Collision_Max_Pos.z - (My_Collision_Min_Pos.z - MyPos.z) + 0.1f; // 接触面押し返し

						HitData.bHit = true;
						HitData.HitAngle.z = 1;
						// 食い込んだ距離の差分(自分中心とあいて面)を計算
						HitData.ResultDistance.z = std::abs(My_Collision_Min_Pos.z - TarGet_Collision_Max_Pos.z);
						normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
					}

					if (My_Collision_Min_Pos.x < TarGet_Collision_Max_Pos.x &&
						My_Collision_Max_Pos.x > TarGet_Collision_Min_Pos.x &&
						My_Collision_Max_Pos.z - MyPos.z + MyOldPos.z <= TarGet_Collision_Min_Pos.z &&
						My_Collision_Max_Pos.z > TarGet_Collision_Min_Pos.z &&
						My_Collision_Min_Pos.y < TarGet_Collision_Max_Pos.y &&
						My_Collision_Max_Pos.y > TarGet_Collision_Min_Pos.y)
					{
						MyPos.z = TarGet_Collision_Min_Pos.z - (My_Collision_Max_Pos.z - MyPos.z) - 0.1f; // 接触面押し返し
						HitData.bHit = true;
						HitData.HitAngle.z = -1;
						// 食い込んだ距離の差分(自分中心とあいて面)を計算
						HitData.ResultDistance.z = std::abs(My_Collision_Max_Pos.z - TarGet_Collision_Min_Pos.z);
						normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
					}

					//------------------------------------Y方向
					if (My_Collision_Min_Pos.x < TarGet_Collision_Max_Pos.x &&
						My_Collision_Max_Pos.x > TarGet_Collision_Min_Pos.x &&
						My_Collision_Min_Pos.z < TarGet_Collision_Max_Pos.z &&
						My_Collision_Max_Pos.z > TarGet_Collision_Min_Pos.z &&
						My_Collision_Min_Pos.y - MyPos.y + MyOldPos.y >= TarGet_Collision_Max_Pos.y &&
						My_Collision_Min_Pos.y < TarGet_Collision_Max_Pos.y)
					{

						MyPos.y = TarGet_Collision_Max_Pos.y + (My_Collision_Min_Pos.y - MyPos.y + 0.1f); // 接触面押し返し
						HitData.bHit = true;
						HitData.HitAngle.y = 1;

						// 食い込んだ距離の差分(自分中心とあいて面)を計算
						HitData.ResultDistance.y = std::abs(My_Collision_Min_Pos.y - TarGet_Collision_Max_Pos.y);
						normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

					}


					// -Y方向の当たり判定
					if (My_Collision_Min_Pos.x < TarGet_Collision_Max_Pos.x &&
						My_Collision_Max_Pos.x > TarGet_Collision_Min_Pos.x &&
						My_Collision_Min_Pos.z < TarGet_Collision_Max_Pos.z &&
						My_Collision_Max_Pos.z > TarGet_Collision_Min_Pos.z &&
						My_Collision_Max_Pos.y - MyPos.y + MyOldPos.y <= TarGet_Collision_Min_Pos.y &&
						My_Collision_Max_Pos.y > TarGet_Collision_Min_Pos.y)
					{
						MyPos.y = TarGet_Collision_Min_Pos.y - (My_Collision_Max_Pos.y - MyPos.y - 0.1f); // 接触面押し返し
						HitData.bHit = true;
						HitData.HitAngle.y = -1;
						// 食い込んだ距離の差分(自分中心とあいて面)を計算
						HitData.ResultDistance.y = std::abs(My_Collision_Max_Pos.y - TarGet_Collision_Min_Pos.y);
						normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
					}




					if (HitData.bHit == true)
					{ // 衝突時
						EscHit = true;


						HitData.targetIndex = nIndex;

						D3DXVECTOR3 moveVector;//ベクトル格納
						D3DXVECTOR3 reflectionVector;//反射ベクトル格納
						float dotProduct;//内積格納
						float moveVectorLength;//ベクトルの長さ
						bool bBreak = false;

						switch (MyType)
						{
						//case CObject::OBJECT_BULLET3D://砲弾


						//	// ここで本来のデータ取得
						//	switch (TargetType)
						//	{


						//	case CObject::OBJECT_NEWBULLET:
						//		pNewBullet = (CNewBullet*)pObject;
						//		EscData = pNewBullet->GetDATA();

						//		//pNewBullet->SetDeath(true);//相手砲弾破壊
						//		pNewBullet->SetGoodby();
						//		//	CObjectExplosionBill::Create(EscData.Pos);
						//		bBreak = true;
						//		break;
						//	case CObject::OBJECT_MISSILE:
						//		pMissile = (CMissile*)pObject;
						//		EscData = pMissile->GetDATA();

						//		//pNewBullet->SetDeath(true);//相手砲弾破壊
						//		pMissile->SetGoodby();
						//		//	CObjectExplosionBill::Create(EscData.Pos);
						//		bBreak = true;
						//		break;

						//	}

						//	if (bBreak == false)
						//	{
						//		//反射ベクトル生成して返す
						//		// 反射ベクトルの計算
						//		moveVector = Mymove;
						//		dotProduct = D3DXVec3Dot(&moveVector, &normal);//内積計算
						//		reflectionVector = moveVector - 2 * dotProduct * normal;//ベクトル

						//	   // 反射ベクトルの長さを元の移動ベクトルの長さで正規化
						//		moveVectorLength = D3DXVec3Length(&moveVector);
						//		D3DXVec3Normalize(&reflectionVector, &reflectionVector);
						//		reflectionVector *= 12.0f;

						//		HitData.ReflectionVector = reflectionVector; // 反射ベクトルを保存

						//		break;
						//	}
						//	else
						//	{//自弾も破壊

						//	}
						//	break;

						case CObject::OBJECT_NEWBULLET://砲弾


						// ここで本来のデータ取得
							switch (TargetType)
							{

							case CObject::OBJECT_NEWBULLET:
								pNewBullet = (CNewBullet*)pObject;
								EscData = pNewBullet->GetDATA();

								//pNewBullet->SetDeath(true);//相手砲弾破壊
								pNewBullet->SetGoodby();
								//	CObjectExplosionBill::Create(EscData.Pos);
								bBreak = true;
								break;

							}

							if (bBreak == false)
							{
								//反射ベクトル生成して返す
								// 反射ベクトルの計算
								moveVector = Mymove;
								dotProduct = D3DXVec3Dot(&moveVector, &normal);//内積計算
								reflectionVector = moveVector - 2 * dotProduct * normal;//ベクトル

							   // 反射ベクトルの長さを元の移動ベクトルの長さで正規化
								moveVectorLength = D3DXVec3Length(&moveVector);
								D3DXVec3Normalize(&reflectionVector, &reflectionVector);
								reflectionVector *= 12.0f;

								HitData.ReflectionVector = reflectionVector; // 反射ベクトルを保存

								break;
							}
							else
							{//自弾も破壊

							}
							break;

						case CObject::OBJECT_MISSILE://砲弾

							break;

						case CObject::OBJECT_MOTIONMODEL://player/enemy

							//押し返すだけ
							break;

						case CObject::OBJECT_HITBOX://player/enemy
						//押し返すだけ
							break;
						}



						//data格納
						CObject::DATA EscData2 = CObject::DataInit();


						EscData2.Pos = MyPos;

						if (HitData.HitAngle.x == 1)
						{//+x
							EscData2.Pos.x += HitData.ResultDistance.x;

							EscData2.move.x = 0.0f;
						}
						else if (HitData.HitAngle.x == -1)
						{//-x

							EscData2.Pos.x -= HitData.ResultDistance.x;
							EscData2.move.x = 0.0f;
						}
						else if (HitData.HitAngle.y == 1)
						{//+y
							EscData2.Pos.y += (HitData.ResultDistance.y);
							//				EscData2.Pos.y = TarGet_Collision_Max_Pos.y + (My_Collision_Min_Pos.y - MyPos.y + 15.1f);
							EscData2.move.y = 0.0f;
						}
						else if (HitData.HitAngle.y == -1)
						{//-y
							EscData2.Pos.y -= HitData.ResultDistance.y;
							EscData2.move.y = 0.0f;
						}
						else if (HitData.HitAngle.z == 1)
						{//+z
							EscData2.Pos.z += HitData.ResultDistance.z;

							EscData2.move.z = 0.0f;
						}
						else if (HitData.HitAngle.z == -1)
						{//-z
							EscData2.Pos.z -= HitData.ResultDistance.z;
							EscData2.move.z = 0.0f;
						}


						//-------------------------------------------ここをなんとか自身のポインタにする

						//ここでこの関数を呼んだ元のクラスの値にデータを代入する

						CObject::DATA SETDATA = CObject::DataInit();

						switch (MyType)
						{
						case CObject::OBJECT_MOTIONPLAYER:

							SETDATA = ((CObjectMotionPlayer*)pCaller)->GetClassData();

							SETDATA.Pos = EscData2.Pos;

							//SETDATA.move

							if (HitData.HitAngle.x == 1)
							{//+x
								SETDATA.move.x = 0.0f;
							}
							else if (HitData.HitAngle.x == -1)
							{//-x

								SETDATA.move.x = 0.0f;
							}
							else if (HitData.HitAngle.y == 1)
							{//+y
								SETDATA.move.y = 0.0f;
							}
							else if (HitData.HitAngle.y == -1)
							{//-y
								SETDATA.move.y = 0.0f;
							}
							else if (HitData.HitAngle.z == 1)
							{//+z

								SETDATA.move.z = 0.0f;
							}
							else if (HitData.HitAngle.z == -1)
							{//-z
								SETDATA.move.z = 0.0f;
							}

							//	SETDATA.move = EscData2.move;

							((CObjectMotionPlayer*)pCaller)->SetClassData(SETDATA);

							if (HitData.HitAngle.y == 1)
							{//ヒットアングルが上(着地)の時
								bLandingHit = true;
							}



							break;
						case CObject::OBJECT_MOTIONENEMY_NOMAL:

							SETDATA = ((CObjectMotionEnemyNomal*)pCaller)->GetClassData();

							SETDATA.Pos = EscData2.Pos;
							SETDATA.move = EscData2.move;

							((CObjectMotionEnemyNomal*)pCaller)->SetClassData(SETDATA);
							break;
							// 他の呼び出し元のケース
						}


					}

					CObject* pNext = pObject->GetNext();
					pObject = pNext;
					nIndex++;

					//		break;


				}
				else
				{
					CObject* pNext = pObject->GetNext();
					pObject = pNext;
					nIndex++;
				}


			}
		}
	}


	if (EscHit == true)
	{
		HitData.bHit = true;
	}
	else
	{
		switch (MyType)
		{
		case CObject::OBJECT_MOTIONPLAYER:

			int test = 0;
			break;
		}
	}

	if (bLandingHit == true)
	{
		HitData.HitAngle.y = 1;
	}
	else
	{
		switch (MyType)
		{
		case CObject::OBJECT_MOTIONPLAYER:

			int test = 0;
			break;
		}
	}

	return HitData;
}
//===================================
//箱型当たり判定--2D
//===================================
CMathProc::CollisionData CMathProc::CheckBoxCollision_2D(D3DXVECTOR3 MyPos, D3DXVECTOR3 MyOldPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength, CObject::OBJECTTYPE TargetType)
{

	float nEscapeDistance = 0.0f;//修正距離の格納

	bool bIsLanding = false;//接地しているかどうか

	CollisionData HitData;

	//HitData.bHit = false;
	//HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	//HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//HitData.targetIndex = -1;



	////自分
	////あたり判定用のHitBox
	//D3DXVECTOR3 My_Collision_Min_Pos = MyPos + MyMinLength;
	//D3DXVECTOR3 My_Collision_Max_Pos = MyPos + MyMaxLength;

	//for (int nPriority = 0; nPriority < CObject::LAYERINDEX_MAX; nPriority++)
	//{
	//	for (int nCnt = 0; nCnt < CObject::GetnNumAll(); nCnt++)
	//	{//全object周回

	//		CObject* pObject = CObject::GetObjectData(nCnt,(CObject::LAYERINDEX)nPriority);//オブジェクトデータ取得

	//		if (pObject != nullptr)
	//		{
	//			CObject::OBJECTTYPE type = pObject->GetObjectType();//タイプ取得
	//			if (type == TargetType)
	//			{//探しているタイプと一致


	//				D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//				D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//				CObject::DATA EscData;

	//				//ここで使用分宣言
	//				CPlayer* pPlayer;
	//				CBullet* pBullet;
	//				CEnemy* pCEnemy;
	//				CPolygon* pCPolygon;
	//				CItem* pItem;
	//				CBlock* pBlock;

	//				//ここで本来のデータ取得
	//				switch (TargetType)
	//				{
	//				case  CObject::OBJECT_PLAYER:
	//					pPlayer = (CPlayer*)pObject;

	//					EscData = pPlayer->GetDATA();

	//					break;

	//				case  CObject::OBJECT_BULLET:
	//					pBullet = (CBullet*)pObject;

	//					EscData = pBullet->GetDATA();
	//					break;

	//				case  CObject::OBJECT_PARTICLE:
	//					break;

	//				case  CObject::OBJECT_EXPLOSION:
	//					break;


	//				case  CObject::OBJECT_ENEMY:
	//					pCEnemy = (CEnemy*)pObject;

	//					EscData = pCEnemy->GetDATA();

	//					break;
	//				case  CObject::OBJECT_POLYGON:
	//					pCPolygon = (CPolygon*)pObject;

	//					EscData = pCPolygon->GetDATA();

	//					break;
	//				case  CObject::OBJECT_BLOCK:
	//					pBlock = (CBlock*)pObject;

	//					EscData = pBlock->GetDATA();

	//					break;

	//				case  CObject::OBJECT_ITEM:
	//					pItem = (CItem*)pObject;

	//					EscData = pItem->GetDATA();

	//					break;


	//				case  CObject::OBJECT_MAX:
	//					break;
	//				}
	//				TarGet_Collision_Min_Pos = EscData.Pos + EscData.MinLength;
	//				TarGet_Collision_Max_Pos = EscData.Pos + EscData.MaxLength;


	//				bool bHit = false;

	//				if ((My_Collision_Max_Pos.y) > TarGet_Collision_Min_Pos.y &&
	//					(My_Collision_Min_Pos.y) < TarGet_Collision_Max_Pos.y)
	//				{//上下判別(共通)

	//					if ((MyOldPos.x + MyMinLength.x) >= TarGet_Collision_Max_Pos.x &&
	//						(My_Collision_Min_Pos.x) < TarGet_Collision_Max_Pos.x)
	//					{//右
	//						HitData.bHit = true;
	//						//食い込んだ距離の差分を計算
	//					//	HitData.ResultDistance.x = (TarGet_Collision_Max_Pos.x) - MyPos.x;

	//						// 食い込んだ距離の差分を計算
	//						HitData.ResultDistance.x= std::abs(TarGet_Collision_Max_Pos.x - My_Collision_Min_Pos.x);

	//						HitData.HitAngle.x = 1;

	//						bHit = true;
	//					}
	//					else if (My_Collision_Max_Pos.x > TarGet_Collision_Min_Pos.x &&
	//						(MyOldPos.x + MyMaxLength.x) <= TarGet_Collision_Min_Pos.x)
	//					{//左
	//						HitData.bHit = true;

	//						//食い込んだ距離の差分(自分中心とあいて面)を計算
	//						//HitData.ResultDistance.x = MyPos.x - (TarGet_Collision_Min_Pos.x);

	//						// 食い込んだ距離の差分(自分中心とあいて面)を計算
	//						HitData.ResultDistance.x = std::abs(My_Collision_Max_Pos.x - TarGet_Collision_Min_Pos.x);


	//						HitData.HitAngle.x = -1;
	//						bHit = true;
	//					}
	//				}

	//				//こっちが大事----------------------------------------------------------------------
	//				if ((My_Collision_Max_Pos.x) > TarGet_Collision_Min_Pos.x &&
	//					(My_Collision_Min_Pos.x) < TarGet_Collision_Max_Pos.x)
	//				{//左右判別(共通)

	//					if ((MyOldPos.y + MyMaxLength.y) <= TarGet_Collision_Max_Pos.y &&
	//						(My_Collision_Max_Pos.y) >= TarGet_Collision_Min_Pos.y)
	//					{//床上
	//						HitData.bHit = true;
	//						//食い込んだ距離の差分(自分中心とあいて面)を計算
	//						//HitData.ResultDistance.y = MyPos.y - (TarGet_Collision_Min_Pos.y);

	//						// 食い込んだ距離の差分(自分中心とあいて面)を計算
	//						HitData.ResultDistance.y = std::abs(My_Collision_Max_Pos.y - TarGet_Collision_Min_Pos.y);


	//						bIsLanding = true;

	//						HitData.HitAngle.y = -1;
	//						bHit = true;

	//					}
	//					else if ((MyOldPos.y + MyMinLength.y) >= TarGet_Collision_Min_Pos.y &&
	//						(My_Collision_Min_Pos.y) < TarGet_Collision_Max_Pos.y)
	//					{//床下

	//						HitData.bHit = true;
	//						//食い込んだ距離の差分を計算
	//					//	HitData.ResultDistance.y = (TarGet_Collision_Max_Pos.y)-MyPos.y;

	//						// 食い込んだ距離の差分を計算
	//						HitData.ResultDistance.y = std::abs(TarGet_Collision_Max_Pos.y - My_Collision_Min_Pos.y);


	//						HitData.HitAngle.y = 1;
	//						bHit = true;
	//					}


	//					if (bHit == true)
	//					{

	//						HitData.targetIndex = nCnt;
	//					}


	//				}
	//			}
	//		}

	//	}
	//}
	return HitData;
}



//=============================
//変換処理2D--------------------------めちゃ大事
//=============================
float CMathProc::ConversionRot2(float NowRot,float fTargetRot)
{
	//ケツにf
	//fmodfとは+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//fmod関数は主に浮動小数点数の誤差を考慮しつつ、剰余を計算するために使用されます。
	//通常、整数での剰余演算子% と同じような働きをしますが、
	//整数の剰余演算子は整数同士の演算に特化しており、浮動小数点数には対応していません。
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//fabsfとは+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//浮動小数点数の絶対値を計算するために使用されます。
	//ここでは、EscapeRotDiff2 の絶対値が D3DX_PI を超えているかどうかを判定しています
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// 角度を範囲内に収める
	fTargetRot = fmodf(fTargetRot + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

	// 角度の差分
	float rotDiff = fTargetRot - NowRot;

	// 差分が範囲外なら補正---------------------------------------------------------------近いうちちゃんと内容調べる
	if (fabsf(rotDiff) > D3DX_PI)
	{
		rotDiff = (rotDiff < 0) ? (rotDiff + 2 * D3DX_PI) : (rotDiff - 2 * D3DX_PI);
	}

	NowRot += rotDiff * 0.1f;

	if (NowRot> D3DX_PI)
	{
		NowRot-= (2.0f * D3DX_PI);
	}
	else if (NowRot< -D3DX_PI)
	{
		NowRot+= (2.0f * D3DX_PI);
	}
	return NowRot;
}


//=============================
//変換処理3D--------------------------めちゃ大事
//=============================
D3DXVECTOR3 CMathProc::ConversionXfireRot3(D3DXVECTOR3 fRot)
{

	//ケツにf
	//fmodfとは+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//fmod関数は主に浮動小数点数の誤差を考慮しつつ、剰余を計算するために使用されます。
	//通常、整数での剰余演算子% と同じような働きをしますが、
	//整数の剰余演算子は整数同士の演算に特化しており、浮動小数点数には対応していません。
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	//fabsfとは+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//浮動小数点数の絶対値を計算するために使用されます。
	//ここでは、EscapeRotDiff2 の絶対値が D3DX_PI を超えているかどうかを判定しています
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	// 角度を範囲内に収める
	fRot.x = fmodf(fRot.x + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;
	fRot.y = fmodf(fRot.y + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;
	fRot.z = fmodf(fRot.z + D3DX_PI, 2 * D3DX_PI) - D3DX_PI;

	float rotDiff = fRot.x;
	float rotDiff2 = fRot.y;
	float rotDiff3 = fRot.z;

	//関数の外でで角度補正

	return D3DXVECTOR3(rotDiff, rotDiff2, rotDiff3);

}








//=============================
// OBB同士あたり判定関数
//=============================
bool CMathProc::ColOBBs(COBB& obb1, COBB& obb2, D3DXVECTOR3* contactPoint)
{
	// 各方向ベクトルの確保
 // （N***:標準化方向ベクトル）
	D3DXVECTOR3 NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen(0);
	D3DXVECTOR3 NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen(1);
	D3DXVECTOR3 NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen(2);
	D3DXVECTOR3 NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen(0);
	D3DXVECTOR3 NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen(1);
	D3DXVECTOR3 NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen(2);

	D3DXVECTOR3 EscPos = obb1.GetPos();
	D3DXVECTOR3 EscPos2 = obb2.GetPos();

	obb1.SetPos(D3DXVECTOR3(obb1.GetPos().x, obb1.GetPos().y + obb1.GetLen(1), obb1.GetPos().z));
	obb2.SetPos(D3DXVECTOR3(obb2.GetPos().x, obb2.GetPos().y + obb2.GetLen(1), obb2.GetPos().z));

	D3DXVECTOR3 Interval = obb1.GetPos() - obb2.GetPos();





	//--------------------------------------------------------------------------------当たり判定ライン
	// OBB1の頂点を計算
	D3DXVECTOR3 obb1Vertices[8];
	obb1Vertices[0] = obb1.m_Pos + obb1.m_Direct[0] * obb1.m_fLength[0] + obb1.m_Direct[1] * obb1.m_fLength[1] + obb1.m_Direct[2] * obb1.m_fLength[2];
	obb1Vertices[1] = obb1.m_Pos + obb1.m_Direct[0] * obb1.m_fLength[0] + obb1.m_Direct[1] * obb1.m_fLength[1] - obb1.m_Direct[2] * obb1.m_fLength[2];
	obb1Vertices[2] = obb1.m_Pos + obb1.m_Direct[0] * obb1.m_fLength[0] - obb1.m_Direct[1] * obb1.m_fLength[1] + obb1.m_Direct[2] * obb1.m_fLength[2];
	obb1Vertices[3] = obb1.m_Pos + obb1.m_Direct[0] * obb1.m_fLength[0] - obb1.m_Direct[1] * obb1.m_fLength[1] - obb1.m_Direct[2] * obb1.m_fLength[2];
	obb1Vertices[4] = obb1.m_Pos - obb1.m_Direct[0] * obb1.m_fLength[0] + obb1.m_Direct[1] * obb1.m_fLength[1] + obb1.m_Direct[2] * obb1.m_fLength[2];
	obb1Vertices[5] = obb1.m_Pos - obb1.m_Direct[0] * obb1.m_fLength[0] + obb1.m_Direct[1] * obb1.m_fLength[1] - obb1.m_Direct[2] * obb1.m_fLength[2];
	obb1Vertices[6] = obb1.m_Pos - obb1.m_Direct[0] * obb1.m_fLength[0] - obb1.m_Direct[1] * obb1.m_fLength[1] + obb1.m_Direct[2] * obb1.m_fLength[2];
	obb1Vertices[7] = obb1.m_Pos - obb1.m_Direct[0] * obb1.m_fLength[0] - obb1.m_Direct[1] * obb1.m_fLength[1] - obb1.m_Direct[2] * obb1.m_fLength[2];

	// OBB2の頂点を計算
	D3DXVECTOR3 obb2Vertices[8];
	obb2Vertices[0] = obb2.m_Pos + obb2.m_Direct[0] * obb2.m_fLength[0] + obb2.m_Direct[1] * obb2.m_fLength[1] + obb2.m_Direct[2] * obb2.m_fLength[2];
	obb2Vertices[1] = obb2.m_Pos + obb2.m_Direct[0] * obb2.m_fLength[0] + obb2.m_Direct[1] * obb2.m_fLength[1] - obb2.m_Direct[2] * obb2.m_fLength[2];
	obb2Vertices[2] = obb2.m_Pos + obb2.m_Direct[0] * obb2.m_fLength[0] - obb2.m_Direct[1] * obb2.m_fLength[1] + obb2.m_Direct[2] * obb2.m_fLength[2];
	obb2Vertices[3] = obb2.m_Pos + obb2.m_Direct[0] * obb2.m_fLength[0] - obb2.m_Direct[1] * obb2.m_fLength[1] - obb2.m_Direct[2] * obb2.m_fLength[2];
	obb2Vertices[4] = obb2.m_Pos - obb2.m_Direct[0] * obb2.m_fLength[0] + obb2.m_Direct[1] * obb2.m_fLength[1] + obb2.m_Direct[2] * obb2.m_fLength[2];
	obb2Vertices[5] = obb2.m_Pos - obb2.m_Direct[0] * obb2.m_fLength[0] + obb2.m_Direct[1] * obb2.m_fLength[1] - obb2.m_Direct[2] * obb2.m_fLength[2];
	obb2Vertices[6] = obb2.m_Pos - obb2.m_Direct[0] * obb2.m_fLength[0] - obb2.m_Direct[1] * obb2.m_fLength[1] + obb2.m_Direct[2] * obb2.m_fLength[2];
	obb2Vertices[7] = obb2.m_Pos - obb2.m_Direct[0] * obb2.m_fLength[0] - obb2.m_Direct[1] * obb2.m_fLength[1] - obb2.m_Direct[2] * obb2.m_fLength[2];

	obb1.SetPos(EscPos);
	obb2.SetPos(EscPos2);


#if _DEBUG
	// 
	////OBBの頂点間にラインを引く
	//
	//for (int i = 0; i < 4; ++i)
	//{
	//	for (int j = 4; j < 8; ++j)
	//	{
	//		if (i != j)
	//		{
	//			Cline::Create(obb1Vertices[i], obb1Vertices[j], D3DXCOLOR(1, 0, 0, 1));
	//			Cline::Create(obb2Vertices[i], obb2Vertices[j], D3DXCOLOR(0, 1, 0, 1));
	//		}
	//	}
	//}

	//Cline::Create(obb1Vertices[0], obb1Vertices[1], D3DXCOLOR(1, 0, 0, 1));
	//Cline::Create(obb2Vertices[0], obb2Vertices[1], D3DXCOLOR(0, 1, 0, 1));

	//Cline::Create(obb1Vertices[0], obb1Vertices[4], D3DXCOLOR(1, 0, 0, 1));
	//Cline::Create(obb2Vertices[0], obb2Vertices[4], D3DXCOLOR(0, 1, 0, 1));

	//Cline::Create(obb1Vertices[1], obb1Vertices[5], D3DXCOLOR(1, 0, 0, 1));
	//Cline::Create(obb2Vertices[1], obb2Vertices[5], D3DXCOLOR(0, 1, 0, 1));

	//Cline::Create(obb1Vertices[5], obb1Vertices[4], D3DXCOLOR(1, 0, 0, 1));
	//Cline::Create(obb2Vertices[5], obb2Vertices[4], D3DXCOLOR(0, 1, 0, 1));

	//--------------------------------------------------------------------------------
#else

#endif // !DEBUG



	//分離軸計算
	//--------------------------------------------------------------------------------------------------------------------------------------

	 // 分離軸の最小食い込み深さとその軸を初期化
	float minPenetration = FLT_MAX;
	D3DXVECTOR3 minSepAxis;

	// 分離軸 : Ae1
	FLOAT rA = D3DXVec3Length(&Ae1);//OBB1のAe方向の半径
	FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);//OBB2のNAe1の方向の投影長
	FLOAT L = fabs(D3DXVec3Dot(&Interval, &NAe1));//OBB1とOBB2の距離

	if (L > rA + rB)
	{//衝突していない
		return false;
	}

	if (rA + rB - L < minPenetration)
	{
		//最小食い込み更新
		minPenetration = rA + rB - L;
		minSepAxis = NAe1;
	}

	// 分離軸 : Ae2
	rA = D3DXVec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe2));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = NAe2;
	}

	// 分離軸 : Ae3
	rA = D3DXVec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NAe3));//OBB1とOBB2の距離
	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = NAe3;
	}

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be1);
	L = fabs(D3DXVec3Dot(&Interval, &NBe1));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = NBe1;
	}

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be2);
	L = fabs(D3DXVec3Dot(&Interval, &NBe2));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration)
	{
		minPenetration = rA + rB - L;
		minSepAxis = NBe2;
	}

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = D3DXVec3Length(&Be3);
	L = fabs(D3DXVec3Dot(&Interval, &NBe3));//OBB1とOBB2の距離
	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = NBe3;
	}

	// 分離軸 : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = Cross;
	}

	// 分離軸 : C12
	D3DXVec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration)
	{
		minPenetration = rA + rB - L;
		minSepAxis = Cross;
	}

	// 分離軸 : C13
	D3DXVec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = Cross;
	}

	// 分離軸 : C21
	D3DXVec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = Cross;
	}

	// 分離軸 : C22
	D3DXVec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = Cross;
	}

	// 分離軸 : C23
	D3DXVec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = Cross;
	}

	// 分離軸 : C31
	D3DXVec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = Cross;
	}

	// 分離軸 : C32
	D3DXVec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));//OBB1とOBB2の距離
	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = Cross;
	}

	// 分離軸 : C33
	D3DXVec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabs(D3DXVec3Dot(&Interval, &Cross));//OBB1とOBB2の距離

	if (L > rA + rB)
	{
		return false;
	}
	if (rA + rB - L < minPenetration) 
	{
		minPenetration = rA + rB - L;
		minSepAxis = Cross;
	}


//--------------------------------------------------------------------------------------------------------------------------------------
//ここまで来ればあたっている


	//ここで、あたったものがどれだけ食い込んでいる(押し返す量)を計算

	if (contactPoint != nullptr)
	{//接触点計算----------------------------------------食い込んでる軸--食い込み深さ
		*contactPoint = CalculateContactPoint(obb1, obb2, minSepAxis, minPenetration);
	}

	// 衝突後の反発処理を追加
	ResolveCollision(obb1, obb2, minSepAxis, minPenetration);

	// 分離平面が存在しないので「衝突している」
	return true;
}
//=============================
// 分離軸に投影された軸成分から投影線分長を算出
//=============================
FLOAT CMathProc::LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
  // 分離軸Sepは標準化されていること
	FLOAT r1 = fabs(D3DXVec3Dot(Sep, e1));
	FLOAT r2 = fabs(D3DXVec3Dot(Sep, e2));
	FLOAT r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}
//=============================
// 最小分離軸と最小食い込み深さを使用して接触点を計算
//=============================
D3DXVECTOR3 CMathProc::CalculateContactPoint(COBB& obb1, COBB& obb2, D3DXVECTOR3& minSepAxis, float minPenetration) 
{
	//------------------------------------------------------------食い込んでる軸--食い込み深さ
	D3DXVECTOR3 contactPoint = (obb1.GetPos() + obb2.GetPos()) / 2 - minSepAxis * (minPenetration / 2);
	return contactPoint;
}
//=============================
// OBBの押し戻し処理
//=============================
void CMathProc::ResolveCollision(COBB& obb1, COBB& obb2, const D3DXVECTOR3& minSepAxis, float minPenetration)
{
	// 接触点を基に、双方のOBBを押し戻す量を計算
	float penetrationHalf = minPenetration * 0.5f;

	// 分離軸を正規化
	D3DXVECTOR3 normalizedAxis = minSepAxis;
	D3DXVec3Normalize(&normalizedAxis, &normalizedAxis);

	// OBB1とOBB2の中心位置を取得
	D3DXVECTOR3 center1 = obb1.GetPos();
	D3DXVECTOR3 center2 = obb2.GetPos();

	// 各OBBを押し戻す方向を計算
	D3DXVECTOR3 pushVector1 = normalizedAxis * penetrationHalf;
	D3DXVECTOR3 pushVector2 = -pushVector1;

	// OBBの中心位置を更新（均等に押し戻す）
	obb1.SetPos(center1 + pushVector1);
	obb2.SetPos(center2 + pushVector2);
}
//=============================
// 双方押し戻し
//=============================
CMathProc::CollisionData CMathProc::CheckCircleCollision_Cancel(/*CObject::OBJECTTYPE MyType,*/ D3DXVECTOR3 MyPos, float fMy_Radius, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer, void* pCaller)
{
	CollisionData HitData;

	HitData.bHit = false;
	HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HitData.targetIndex = -1;

	//相手のposと半径

	//とりあえずは処理完成まで仮の変数
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(500.0f, 500.0f, 0.0f);
	float ftarget_Radius = 25.0;


	//ここに円形当たり判定追加

	// 配置物プライオリティの先頭を取得
	CObject* pObject = CObject::GetpTop(TargetLayer);

	if (pObject != nullptr)
	{ // 先頭がない==プライオリティまるっとない

		int nIndex = 0;

		while (pObject != nullptr)
		{
			if (pObject->GetObjectType() == TargetType)
			{ // balletモデルのとき

				D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				CObject::DATA EscData;


				// ここで使用分宣言
				/*CPlayer* pPlayer;
				CBullet* pBullet;
				CEnemy* pCEnemy;
				CBlock3D* pBlock3D;
				CBullet3D* pBullet3D;*/
				CNewBullet* pNewBullet = {};
				CObstacleSet* pObstacleObject;
				StageCollisionBox* pStageHitBox;
				CObjectMotionEnemyNomal* pEnemyNomal;
				//CObjectMotionEnemyfast* pEnemyfast;
				CObjectMotionPlayer* pMotionPlayer;


				//switch (MyType)
				//{
				//case CObject::OBJECT_MOTIONPLAYER:

				//	EscData=((CObjectMotionPlayer*)pCaller)->GetClassData();
				//	MyPos = EscData.Pos;
				//	break;
				//case CObject::OBJECT_MOTIONENEMY_NOMAL:
				//	EscData=((CObjectMotionEnemyNomal*)pCaller)->GetClassData();
				//	MyPos = EscData.Pos;
				//	break;
				//	// 他の呼び出し元のケース
				//}

				CObject::DATA MYDATA = CObject::DataInit();

				bool bSame = false;

				// ここで本来のデータ取得
				switch (TargetType)
				{
				case CObject::OBJECT_PARTICLE:
					break;

				case CObject::OBJECT_EXPLOSION:
					break;

				case CObject::OBJECT_NEWBULLET:
					pNewBullet = (CNewBullet*)pObject;
					EscData = pNewBullet->GetDATA();
					break;

				case CObject::OBJECT_OBSTACLE:
					pObstacleObject = (CObstacleSet*)pObject;

					EscData = pObstacleObject->GetDATA();
					break;

				case CObject::OBJECT_HITBOX:
					pStageHitBox = (StageCollisionBox*)pObject;

					EscData = pStageHitBox->GetDATA();
					break;

				case CObject::OBJECT_MOTIONPLAYER:
					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					EscData = pMotionPlayer->GetClassData();


					break;


				case CObject::OBJECT_MOTIONENEMY_NOMAL:
					pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;

					EscData = pEnemyNomal->GetClassData();

					MYDATA = ((CObjectMotionPlayer*)pCaller)->GetClassData();


					if ((CObjectMotionPlayer*)pObject == (CObjectMotionPlayer*)pCaller)
					{//ゲキヤバ
						bSame = true;
					}

					break;

				case CObject::OBJECT_MAX:
					return HitData;


					break;
				}

				//EscData.Pos;//相手座標
				//EscData.Radius;//相手半径



				if (bSame == true)
				{//自身を相手にした時

				}
				else
				{



					//ここで衝突判定
					//どれだけ食い込んでるかも計算

					D3DXVECTOR3 diff = MyPos - EscData.Pos; // 2点間の距離
					float Distance = D3DXVec3Length(&diff);       // 距離を絶対値に

					float HitDistance = fMy_Radius + EscData.Radius;//半径同士足したの長さ


					CollisionData EscHitData;
					CollisionData EscHitData2;

					if (HitDistance > Distance)
					{//半径同士合算より現在の距離が近い時==接触

						HitData.bHit = true;


						// 接触直前まで戻す
						float overlap = HitDistance - Distance;//食い込み量

						D3DXVECTOR3 direction = diff / Distance; // 正規化された方向ベクトル

						//第三者への当たり判定
						//------------------------------------------------------------------------------------

						//まず先に相手を動かす
						EscData.OldPos = EscData.Pos;
						EscData.Pos -= direction * (overlap / 2);//均等

						//移動量を仮設定
						D3DXVECTOR3 EscMove = -(direction * (overlap / 2));

						bool bNextHit = false;

						switch (TargetType)
						{//各対象が第三者への当たり判定がある者の時


						case CObject::OBJECT_MOTIONENEMY_NOMAL:

							//当たり判定計算
							EscHitData = CMathProc::CheckBoxCollision_3D(TargetType, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject::OBJECT_HITBOX, CObject::LAYERINDEX_HITBOX, EscMove, (CObjectMotionEnemyNomal*)pObject);

							EscHitData2 = CMathProc::CheckBoxCollision_3D(TargetType, EscData.Pos, EscData.OldPos, EscData.MinLength, EscData.MaxLength, CObject::OBJECT_OBSTACLE, CObject::LAYERINDEX_OBSTACLE, EscMove, (CObjectMotionEnemyNomal*)pObject);

							break;
						}

						if (EscHitData.bHit == true || EscHitData2.bHit == true)
						{//あたった場合
						//相手データに更新あり、変動の必要性あり

							// データ取得再取得
							switch (TargetType)
							{
						

							case CObject::OBJECT_OBSTACLE:
								pObstacleObject = (CObstacleSet*)pObject;

								EscData = pObstacleObject->GetDATA();
								break;

							case CObject::OBJECT_MOTIONENEMY_NOMAL:
								pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;

								EscData = pEnemyNomal->GetClassData();
								break;

							case CObject::OBJECT_MAX:
								break;
							}

							//上記での接触移動を踏まえて再計算(相手が最優先)
							// 
							//ここで衝突判定
							//どれだけ食い込んでるかも計算

							diff = MyPos - EscData.Pos;				// 2点間の距離
							Distance = D3DXVec3Length(&diff);       // 距離を絶対値に

							HitDistance = fMy_Radius + EscData.Radius;//半径同士足したの長さ

							CollisionData EscHitData2;

							if (HitDistance > Distance)
							{//半径同士合算より現在の距離が近い時==接触

								HitData.bHit = true;


								// 接触直前まで戻す
								float overlap = HitDistance - Distance;//食い込み量

								D3DXVECTOR3 direction = diff / Distance; // 正規化された方向ベクトル

								//第三者への当たり判定
								//------------------------------------------------------------------------------------

								//まず先に相手を動かす
							//	EscData.Pos -= direction * (overlap / 2);//均等
								// 自分を移動
								MyPos += direction * (overlap * 1.1f);//全面

								switch (TargetType)
								{//各対象に押し戻しを適応する

								case CObject::OBJECT_MOTIONENEMY_NOMAL:
									pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;

									/*	EscData = pEnemyNomal->GetClassData();*/

									pEnemyNomal->SetClassData(EscData);

									break;

								
								}

			

								HitData.ResultDistance = direction * (overlap * 1.1f);

								break;//ここで処理を抜ける
							}

						}


						//第三者への当たり判定ここまで
						//------------------------------------------------------------------------------------

						// 自分を移動
						MyPos += direction * (overlap / 2);//均等


						switch (TargetType)
						{//各対象に押し戻しを適応する

						case CObject::OBJECT_MOTIONENEMY_NOMAL:
							pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;

							/*	EscData = pEnemyNomal->GetClassData();*/

							pEnemyNomal->SetClassData(EscData);

							break;
						}


						//CObject::DATA SETDATA;

						//switch (MyType)
						//{
						//case CObject::OBJECT_MOTIONPLAYER:

						//	SETDATA = ((CObjectMotionPlayer*)pCaller)->GetClassData();

						//	SETDATA.Pos = MyPos;

						//	((CObjectMotionPlayer*)pCaller)->SetClassData(SETDATA);
						//	break;
						//case CObject::OBJECT_MOTIONENEMY_NOMAL:

						//	SETDATA = ((CObjectMotionEnemyNomal*)pCaller)->GetClassData();

						//	SETDATA.Pos = MyPos;

						//	((CObjectMotionEnemyNomal*)pCaller)->SetClassData(EscData2);
						//	break;
						//	// 他の呼び出し元のケース
						//}



						HitData.ResultDistance = direction * (overlap / 2.0f);

						break;
					}
				}
			}

			CObject* pNext = pObject->GetNext();
			pObject = pNext;
			nIndex++;
		}
	}

	return HitData;
}


//=============================
// 3DBoxCollisionによる3Dobject内生成防止
//=============================
bool CMathProc::AvoidInternalSpawn_3D_BoxCollision(CObject::OBJECTTYPE MyType, D3DXVECTOR3 MyPos,  D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer)
{
	bool bHit = false;

	// 配置物プライオリティの先頭を取得
	CObject* pObject = CObject::GetpTop(TargetLayer);

	D3DXVECTOR3 My_Collision_Min_Pos = MyPos + MyMinLength;
	D3DXVECTOR3 My_Collision_Max_Pos = MyPos + MyMaxLength;

	D3DXVECTOR3 HitDotPos[9] = {};

	for (int i = 0; i < 9; i++)
	{
		HitDotPos[i] = MyPos;
	}

	HitDotPos[0] += D3DXVECTOR3(MyMinLength.x, MyMinLength.y, MyMinLength.z);
	HitDotPos[1] += D3DXVECTOR3(MyMaxLength.x, MyMinLength.y, MyMinLength.z);
	HitDotPos[2] += D3DXVECTOR3(MyMinLength.x, MyMaxLength.y, MyMinLength.z);
	HitDotPos[3] += D3DXVECTOR3(MyMinLength.x, MyMinLength.y, MyMaxLength.z);

	HitDotPos[4] += D3DXVECTOR3(MyMaxLength.x, MyMaxLength.y, MyMinLength.z);
	HitDotPos[7] += D3DXVECTOR3(MyMinLength.x, MyMaxLength.y, MyMaxLength.z);
	HitDotPos[6] += D3DXVECTOR3(MyMaxLength.x, MyMinLength.y, MyMaxLength.z);
	HitDotPos[7] += D3DXVECTOR3(MyMaxLength.x, MyMaxLength.y, MyMaxLength.z);
	HitDotPos[8] += D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	if (pObject != nullptr)
	{ // 先頭がない==プライオリティまるっとない

		int nIndex = 0;

		while (pObject != nullptr)
		{

			if (pObject->GetObjectType() == TargetType)
			{ // 対象のモデルのとき

				D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				CObject::DATA EscData;

				// ここで使用分宣言
			//	CBlock3D* pBlock3D;
				CObstacleSet* pObstacleObject;
				StageCollisionBox* pStageHitBox;

				CStageCollisionBox3D2D* pStageHitBox_2D3D;

				// ここで本来のデータ取得
				switch (TargetType)
				{

				

				case CObject::OBJECT_OBSTACLE:
					pObstacleObject = (CObstacleSet*)pObject;

					EscData = pObstacleObject->GetDATA();
					break;

				case CObject::OBJECT_HITBOX:
					pStageHitBox = (StageCollisionBox*)pObject;

					EscData = pStageHitBox->GetDATA();
					break;
				case CObject::OBJECT_HITBOX_2D3D:
					pStageHitBox_2D3D = (CStageCollisionBox3D2D*)pObject;

					EscData = pStageHitBox_2D3D->GetDATA();
					break;





				case CObject::OBJECT_MAX:

					break;
				}


				TarGet_Collision_Min_Pos = EscData.Pos + EscData.MinLength;
				TarGet_Collision_Max_Pos = EscData.Pos + EscData.MaxLength;


				for (int i = 0; i < 9; i++)
				{//9個の頂点地点のいずれかが内部に入るとアウト
					if (TarGet_Collision_Min_Pos.x <= HitDotPos[i].x && TarGet_Collision_Max_Pos.x >= HitDotPos[i].x)
					{
						if (TarGet_Collision_Min_Pos.y <= HitDotPos[i].y && TarGet_Collision_Max_Pos.y >= HitDotPos[i].y)
						{
							if (TarGet_Collision_Min_Pos.z <= HitDotPos[i].z && TarGet_Collision_Max_Pos.z >= HitDotPos[i].z)
							{
								bHit = true;
								break;
							}
						}

					}

				}
				if (bHit == true)
				{
					break;
				}
				else
				{
					CObject* pNext = pObject->GetNext();
					pObject = pNext;
					nIndex++;
				}


			}
		}
	}



	return bHit;
}
//=============================
// 射撃位置設定処理
//=============================
D3DXVECTOR3 CMathProc::SetPositionldPredictedImpactPoint(D3DXVECTOR3 BulletPos, D3DXVECTOR3 BulletMove, D3DXVECTOR3 TargetPos, D3DXVECTOR3 TargetMove, float BULLETSPEED)
{
	int random = ((rand() % 200) - 100);//(25~-25)までの乱数

	float random2 = random * 1.0f;//

	//誤差を入れる
	D3DXVECTOR3 randomPosError = D3DXVECTOR3(random2, random2, random2);


	// 初期化
	D3DXVECTOR3 impactPoint(0, 0, 0);

	// 弾の速度がゼロの場合、計算不可
	float bulletSpeedSquared = D3DXVec3Dot(&BulletMove, &BulletMove);
	if (bulletSpeedSquared < 1e-6f)
	{
		return impactPoint; // 初期値（ゼロ）を返す
	}

	// ターゲットとの相対位置
	D3DXVECTOR3 relativePos = (TargetPos + randomPosError) - BulletPos;

	// 弾の速度ベクトルを正規化（速度方向を抽出）
	D3DXVec3Normalize(&BulletMove, &BulletMove);
	BulletMove *= BULLETSPEED; // 弾の速度ベクトルを反映

	// ターゲットとの相対速度
	D3DXVECTOR3 relativeVelocity = TargetMove - BulletMove;

	// 相対速度の大きさの二乗
	float relativeSpeedSquared = D3DXVec3Dot(&relativeVelocity, &relativeVelocity);
	if (relativeSpeedSquared < 1e-6f)
	{
		return  (TargetPos + randomPosError); // 移動速度がない場合、現在のターゲット位置を返す
	}

	// ターゲットへの相対位置と相対速度の内積
	float t = -D3DXVec3Dot(&relativePos, &relativeVelocity) / relativeSpeedSquared;

	// tが負の場合、ターゲットに到達する前に通過
	if (t < 0.0f)
	{
		return  (TargetPos + randomPosError); // 現在のターゲット位置を返す
	}

	// 命中点を計算
	impactPoint = (TargetPos + randomPosError) + TargetMove * t;

	return impactPoint;
}
//---------------------------------------------------------------------------------------------------------------------------------------------
//=============================
// 有効な座標かどうかを確認する関数
//=============================
bool CMathProc::isValid(int x, int y)
{
	if (x >= 0 && x < GRIDCOL && y >= 0 && y < GRIDROW && !GRID[y][x].bBlock)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//=============================
// 幅優先探索（BFS）を実行する関数
//=============================
void CMathProc::bfs(Point start, Point goal)
{
	 
	//************************************************************ 
	//初めてのキューのため理解が乏しい。要勉強。
	//************************************************************


	// 初期化
	int ObjectNum = 0;

	for (int i = 0; i < GRIDROW; i++)
	{
		for (int j = 0; j < GRIDCOL; j++)
		{
			GRID[i][j].Num = INT_MAX; // 距離を無限大で初期化
			GRID[i][j].ObjectNum = ObjectNum;
			ObjectNum++;
		}
	}

	std::queue<Point> q;//キュー作成
	GRID[start.y][start.x].Num = 0;//スタート位置を０に
	q.push(start);//キューにpush

	while (!q.empty()) 
	{//キューが空じゃないとループ

		Point p = q.front();//キューの一番最初を取得
		q.pop();//データを取り出す

		if (p.x == goal.x && p.y == goal.y) 
		{
			break; // ゴールに到達したら終了
		}

		for (int i = 0; i < 4; i++) 
		{//4方向
			//移動
			int nx = p.x + dx[i];
			int ny = p.y + dy[i];

			if (isValid(nx, ny)==true && GRID[ny][nx].Num == INT_MAX) 
			{//有効な座標かつ初期値時
				GRID[ny][nx].Num = GRID[p.y][p.x].Num + 1;
			
				//親の位置を保存
				GRID[ny][nx].ParemtPoint.x = p.x;
				GRID[ny][nx].ParemtPoint.y = p.y;

				//直接 Point 構造体を初期化して push
				Point nextPoint = { nx, ny };
				q.push(nextPoint);//キューにpush
			}
		}
	}
}
//=============================
// CSVファイルに書き出す関数
//=============================
void CMathProc::writeToCSV(const char* filename)
{
	FILE* file = fopen(filename, "w");
	if (file == NULL) 
	{//エラー
		return;
	}


	
	for (int i = 0; i < GRIDROW; i++)
	{
		for (int j = 0; j < GRIDCOL; j++)
		{
			if (GRID[i][j].Num>= INT_MAX|| GRID[i][j].Num<=-1)
			{
				fprintf(file, "	X");//障害物
			}
			else
			{
				fprintf(file, "%d", GRID[i][j].Num);//深度を記載
			}

			if (j < GRIDCOL - 1)
			{
				fprintf(file, ",");//セルの区切り
			}
		}
		fprintf(file, "\n");
	}

	fclose(file);
}
//=============================
//セル状態格納
//=============================
void CMathProc::SetCell(Cell pCell[GRIDROW][GRIDCOL])
{
	memcpy(GRID, pCell, sizeof GRID);
}
//=============================
//Routeテーブル作成
//=============================
void CMathProc::RouteTableSet(Point StartPoint, Point GoalPoint)
{


	//------------------------------------------------
	//
	//++そもそも縦８横11のマスの時点で
	//88地点から88地点までの経路
	//　　7744ルートを算出する
	//ルートをそのまま使用は無理(重い)ので経路テーブル化する
	//
	//++深度を元にゴールからスタートまでたどり、その間の地点を経路テーブルに打ち込んでゆく

	//------------------------------------------------------------------------------------------------------------------------------------------
	//						   地点名(仮)
	// テーブルの例　　スタート1-3-4-2-5ゴール
	// 
	// 
	// 
	//        現在の地点側　　　　　　　　     現在の地点側              　　     現在の地点側                  　    現在の地点側
	//										   ３に移動した			       	      4に移動した				   	       2に移動した
	//         							       							        								       
	//	      --❶②③④⑤				     --①②❸④⑤			  	     --①②➂❹⑤					         --①❷➂④⑤
	//	 ゴ  ①							ゴ  ①						    ゴ  ①								  ゴ  ①
	//	 ｜  ②							｜  ②						    ｜  ②								  ｜  ②
	//	 ル  ③							ル  ③						    ル  ③								  ル  ③
	//	 側  ④							側  ④						    側  ④								  側  ④
	//	     ❺ 3						    ❺     4					    ❺       2						      ❺      5
	// 
	//      1から5に向かうには			     3から5に向かうには			      4から5に向かうには				     2から5に向かうには
	//      まずは3に向かう					 次に4に向かう			   	      次に2に向かう					  	      次に5に向かう
	//                                                                                                               向かったらゴール！
	//-----------------------------------------------------------------------------------------------------------------------------------------
	//   　   上をくっつけてこんな感じ
	//  	  
	//			スタート側
	// 　　　　　　　　　　　　　　　　　　　　　　　                        [自分番号][ゴール番号]＝次に進むべき地点
	//        --①➁➂④⑤　　　　これを今回88*88で作る　　					MyPoint[88][88]=NextPoint;
	//   ゴ  ①
	//   ｜  ②
	//   ル  ③
	//   側  ④
	//       ➄  3 5 4 2 -
	// //-------------------------------------------------------------------------------------------------------------------------------
	// 地点番号早見
	// 
	// 
	//			これが地点番号					
	//    ７・・・・・・・・・・87              
	//    ・・・・・・・・・・・・				
	//    ❺・・・・・・・・・・・				
	//    ❹㊹・・・・・・・・・・				
	//    ❸㉝㉞・・・・・・・・・				
	// 　 ❷㉒㉓㉔・・・・・・・㉜				
	//    ❶⑪⑫⑬⑭・・・・・・㉑				
	//	   O 0①➁➂④・・・・・⑩				
	//    -- O❶❷❸❹❺・・・・10				
	// 
	// 
	//-------------------------------------------------------------------------------------------------------------------------------------------

	//ここではテーブル作成を地点分回ることで、一つの配列が出来上がる想定で作られている

	//ゴール地点を回避
	Point EscGoalPoint = GoalPoint;

	//ここに各地点の深度が入っている
	GRID[GRIDROW-1][GRIDCOL-1];
	
	//Routeを仮格納
	Point EscRoutePoint[GRIDCOL * GRIDROW];
	//位置を仮格納
	int EscapeObjectNum[GRIDCOL * GRIDROW];

	for (int i = 0; i < GRIDCOL * GRIDROW; i++)
	{//初期化
		EscRoutePoint[i].x = -1;
		EscRoutePoint[i].y = -1;
		EscapeObjectNum[i] = -1;
	}



	int RouteCnt = 0;

	//今回のゴール座標から遡り最短算出
	while (true)
	{
		///親番号取得
		GRID[GoalPoint.y][GoalPoint.x].ParemtPoint;


		//0から順に位置を格納
		EscRoutePoint[RouteCnt].x = GRID[GoalPoint.y][GoalPoint.x].ParemtPoint.x;
		EscRoutePoint[RouteCnt].y = GRID[GoalPoint.y][GoalPoint.x].ParemtPoint.y;
	
	

		if (GoalPoint.y== StartPoint.y&& GoalPoint.x == StartPoint.x)
		{//現在のGRIDがSTART地点にだった時
			break;
		}
		else
		{
			//次のゴールを一つ前に
			GoalPoint.x = EscRoutePoint[RouteCnt].x;
			GoalPoint.y = EscRoutePoint[RouteCnt].y;
			
			if (GoalPoint.y == StartPoint.y && GoalPoint.x == StartPoint.x)
			{//現在のGRIDがSTART地点にだった時
				break;
			}

			RouteCnt++;
		}
	}


	//------------------------------------------------------------

	RouteCnt--;

	//格納した(たどる順)に
	//int nNumCnt = 0;
	for (int nCnt = 0; nCnt <= RouteCnt; nCnt++)
	{//最短移動分
		EscapeObjectNum[nCnt]=GetObjectNumfromPoint(EscRoutePoint[nCnt]);//経路に順番に物体番号で格納
	}


	//避難先
	int ESCRoute[GRIDROW * GRIDCOL][GRIDROW * GRIDCOL];

	for (int i = 0; i < GRIDCOL * GRIDROW; i++)
	{//初期化
		for (int j = 0; j < GRIDCOL * GRIDROW; j++)
		{//初期化
			ESCRoute[i][j] = -1;
		}
	}

	//これで順番に最短を一時格納した
	//--------------------------------------------------------------------------------------------
	int BackMove = RouteCnt;//----------------------最初の０を消し次に行くべき番号を入れる

	for (int nCnt = 0; nCnt <= RouteCnt; nCnt++)
	{//最短移動分
	//----------------自身の番号----------------------ゴールの座標------------------向かうべき位置
		ESCRoute[GetObjectNumfromPoint(StartPoint)][nCnt] = EscapeObjectNum[BackMove];
		BackMove--;
	}
	//最後にゴールポイントを入れる
	ESCRoute[GetObjectNumfromPoint(StartPoint)][RouteCnt + 1] = GetObjectNumfromPoint(EscGoalPoint);
	//-------------------------------------------------------------------------------------------


	//ここでRouteTable[自分のobject番号][ゴール地点]での経路テーブルを作成

	int nCnt=0;
	int StartNum = GetObjectNumfromPoint(StartPoint);
	int GoalNum = GetObjectNumfromPoint(EscGoalPoint);

	while (true)
	{
		//避難させてた最短Route
		int nRouteCnt = ESCRoute[GetObjectNumfromPoint(StartPoint)][nCnt];//向かう先の地点番号を向かう順に取り出す


		if (nRouteCnt != -1)
		{
			//-出発(現在)の番号-------------ゴールの座標---------------次に向かうべき位置
			RouteTable[StartNum][GetObjectNumfromPoint(EscGoalPoint)] = nRouteCnt;

			StartNum = nRouteCnt;//STARTを向かった先に(インデックスなのでそのまま)

			nCnt++;
		}
		else
		{
			break;
		}

	}
	//最後に自分から自分の参照地点に-100を入れる
	RouteTable[GetObjectNumfromPoint(EscGoalPoint)][GetObjectNumfromPoint(EscGoalPoint)] = -100;


	//ここまででひとつのスタートから一つのゴールまでの最短算出テーブル化の手順である







}
//=============================
//Point座標から物体番号取得
//=============================
int CMathProc::GetObjectNumfromPoint(Point point)
{
	int EscY = point.y;
	EscY *= GRIDCOL;

	return (point.x + EscY);
}
//=============================
//物体番号からpoint座標取得
//=============================
CMathProc::Point CMathProc::GetPointfromObjectNum(int ObjectNum)
{
	Point EscPoint;

	EscPoint.y = ObjectNum / GRIDCOL;
	EscPoint.x = ObjectNum % GRIDCOL;

	return EscPoint;

}
//=============================
// CSV描画
//=============================
void CMathProc::DRAWCSV( const char* filename)
{
	std::ofstream file(filename);
	
		if (!file.is_open()) 
		{
			std::cerr << "ファイルを開けませんでした: " << filename << std::endl;
			return;
		}
	
		for (int y = 0; y < GRIDROW * GRIDCOL; ++y)
		{
			for (int x = 0; x < GRIDROW * GRIDCOL; ++x)
			{
				file << RouteTable[x][y];
				if (x < (GRIDROW * GRIDCOL)-1)
				{
					file << ",";
				}
			}
			file << "\n";
		}
	
		file.close();
}
//=============================
// Routeテーブル取得
//=============================
int CMathProc::GetNextMoveGridNum(int PartnerGridNum, int MyGridNum)
{
	//次に向かう位置---------------自身-------相手の位置
	return RouteTable[MyGridNum][PartnerGridNum];
}
//=============================
// 視界不良時射撃位置
//=============================
void CMathProc::LoadShotPoint(const char* filename)
{
	FILE* pFile;//ファイルポインタを宣言

	char aString[2000]; // 読み込む最大文字数


	pFile = fopen(filename, "r");

	if (pFile != NULL)
	{//ファイルが開いたら
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);

			if (strcmp(&aString[0], "END_SCRIPT") == 0)
			{//最後にきたら
				fclose(pFile);
				break;
			}
			else if (strcmp(&aString[0], "SHOTPOINT_1") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%f %f %f", &m_ShotPos[0].x, &m_ShotPos[0].y, &m_ShotPos[0].z);

			}
			else if (strcmp(&aString[0], "SHOTPOINT_2") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%f %f %f", &m_ShotPos[1].x, &m_ShotPos[1].y, &m_ShotPos[1].z);

			}
			else if (strcmp(&aString[0], "SHOTPOINT_3") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%f %f %f", &m_ShotPos[2].x, &m_ShotPos[2].y, &m_ShotPos[2].z);

			}
			else if (strcmp(&aString[0], "SHOTPOINT_4") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%f %f %f", &m_ShotPos[3].x, &m_ShotPos[3].y, &m_ShotPos[3].z);

			}
			else if (strcmp(&aString[0], "SHOTPOINT_5") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%f %f %f", &m_ShotPos[4].x, &m_ShotPos[4].y, &m_ShotPos[4].z);

			}
			else if (strcmp(&aString[0], "SHOTPOINT_6") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%f %f %f", &m_ShotPos[5].x, &m_ShotPos[5].y, &m_ShotPos[5].z);

			}
			else if (strcmp(&aString[0], "SHOTPOINT_7") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%f %f %f", &m_ShotPos[6].x, &m_ShotPos[6].y, &m_ShotPos[6].z);

			}
			else if (strcmp(&aString[0], "SHOTPOINT_8") == 0)
			{//モデル数が来たら
				fscanf(pFile, "%s", &aString[0]);
				fscanf(pFile, "%f %f %f", &m_ShotPos[7].x, &m_ShotPos[7].y, &m_ShotPos[7].z);

			}
		}
	}
}

//=============================
//視界不良時射撃取得
//=============================
D3DXVECTOR3 CMathProc::GetShotPos(D3DXVECTOR3 MyPos)
{
	//ここで4地点から一番近い地点のランダムにズレた位置を渡す

	
	D3DXVECTOR3 diff[SHOTPOINUM] = {};//差分
	float fDiff[SHOTPOINUM] = {};//距離

	for (int i = 0; i < SHOTPOINUM; i++)
	{
		diff[i] = MyPos - m_ShotPos[i];
		fDiff[i] = D3DXVec3Length(&diff[i]);
	}

	float fMinLength = 99999.9f;//初期値を巨大に
	
	int nMinNum = 0;
	
	for (int i = 0; i < SHOTPOINUM; i++)
	{
		if (fDiff[i]<= fMinLength)
		{//最小を更新
			fMinLength = fDiff[i];
			nMinNum = i;//インデックスを格納
		}
	}
	
	int nMinNum2 = nMinNum;

	fMinLength = 99999.9f;//初期値を巨大に
	
	for (int i = 0; i < SHOTPOINUM; i++)
	{
		if (i != nMinNum2)
		{
			if (fDiff[i] <= fMinLength)
			{//最小を更新
				fMinLength = fDiff[i];
				nMinNum = i;//インデックスを格納
			}
		}
	}

	//二番目を狙わせる



	//目標地点をここにズレも含めて
	//-30から30
	float fX = (float)((rand() % 60) - 30);
//	float fY = (float)((rand() % 60) - 30);
	float fZ = (float)((rand() % 60) - 30);

	D3DXVECTOR3 TargetPos = D3DXVECTOR3(m_ShotPos[nMinNum].x + fX, 0.0f, m_ShotPos[nMinNum].z + fZ);
	
	//Y座標は射手に指定させる
	



	return TargetPos;
}

//=============================
//  FCS火器管制　予測照準
//=============================
CObject::DATA CMathProc::FCS_TrajectoryPredictionAiming(D3DXVECTOR3 FirePos, float BulletSpeed, D3DXVECTOR3 TargetPos, D3DXVECTOR3 TargetMove)
{
	CObject::DATA IFDATA = CObject::DataInit();

	// 乱数で誤差を導入する
	int random = ((rand() % 20) - 10); // (-10 ~ 10)の乱数
	float random2 = random * 0.1f;
	D3DXVECTOR3 randomPosError = D3DXVECTOR3(random2, random2 * -1.0f, random2);

	// ターゲットが静止している場合、予測交差点はターゲットの現在位置
	if (D3DXVec3LengthSq(&TargetMove) == 0.0f)
	{
		IFDATA.Pos = TargetPos + randomPosError;

		// 方向ベクトルを計算（発射位置から静止ターゲットへのベクトルを正規化）
		D3DXVECTOR3 directionVec = IFDATA.Pos - FirePos;
		D3DXVec3Normalize(&IFDATA.rot, &directionVec);  // 方向ベクトルを正規化

		return IFDATA;
	}
	else
	{
		// 自弾と敵の相対位置ベクトル
		D3DXVECTOR3 relativePos = FirePos - (TargetPos + randomPosError);

		// 自弾と敵の相対速度ベクトル
		D3DXVECTOR3 relativeVel = TargetMove;

		// 自弾と敵の最短交差時間
		float timeToIntersection = -D3DXVec3Dot(&relativePos, &relativeVel) / D3DXVec3LengthSq(&relativeVel);

		// 交差時間が正の値のみ考慮する
		if (timeToIntersection < 0)
		{
			timeToIntersection = 0;
		}

		// 敵の予測位置（交差点）を計算
		IFDATA.Pos = TargetPos + TargetMove * timeToIntersection;

		// 発射位置から予測交差点までのベクトルを方向ベクトルとして計算
		D3DXVECTOR3 directionVec = IFDATA.Pos - FirePos;
		D3DXVec3Normalize(&IFDATA.rot, &directionVec);  // 方向ベクトルを正規化

		// 予測交差点と方向ベクトルを返す
		return IFDATA;
	}
}
//===================================
//相手と自分の間の障害物判定
//===================================
CMathProc::CollisionData CMathProc::AdjustMyPosToCollision_Partner(D3DXVECTOR3 MyPos, D3DXVECTOR3 MyMin, D3DXVECTOR3 MyMax, D3DXVECTOR3 TargetPos,float MaxLength, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer)
{

	
	// 必要に応じて改良、下記は試験運用段階
	CollisionData HitData;

	HitData.bHit = false;
	HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HitData.targetIndex = -1;

	// 自分
	MyPos.y = MyMax.y/4;//少し上げておく
	TargetPos.y = 50;
	// あたり判定用のHitBox
	D3DXVECTOR3 My_Collision_Min_Pos = MyPos + MyMin;
	D3DXVECTOR3 My_Collision_Max_Pos = MyPos + MyMax;


	// 配置物プライオリティの先頭を取得
	CObject* pObject = CObject::GetpTop(TargetLayer);

	if (pObject != nullptr)
	{ // 先頭がない==プライオリティまるっとない

		int nIndex = 0;

		while (pObject != nullptr)
		{
			HitData.bHit = false;
			HitData.HitAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			HitData.ResultDistance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			HitData.targetIndex = -1;

			if (pObject->GetObjectType() == TargetType)
			{ // 対象のモデルのとき

				D3DXVECTOR3 TarGet_Collision_Min_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 TarGet_Collision_Max_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				CObject::DATA EscData;

				// ここで使用分宣言
				//CBlock3D* pBlock3D;
				CObstacleSet* pObstacleObject;
				StageCollisionBox* pStageHitBox;
				CObjectMotionEnemyNomal* pEnemyNomal;
				CObjectMotionPlayer* pMotionPlayer;
				//CObjectMotionEnemyfast* pEnemyfast;

				My_Collision_Min_Pos = MyPos + MyMin;
				My_Collision_Max_Pos = MyPos + MyMax;


				// ここで本来のデータ取得
				switch (TargetType)
				{
				case CObject::OBJECT_PARTICLE:
					break;

				case CObject::OBJECT_EXPLOSION:
					break;

			
			

				case CObject::OBJECT_OBSTACLE:
					pObstacleObject = (CObstacleSet*)pObject;

					EscData = pObstacleObject->GetDATA();
					break;

				case CObject::OBJECT_HITBOX:
					pStageHitBox = (StageCollisionBox*)pObject;

					EscData = pStageHitBox->GetDATA();
					break;

				case CObject::OBJECT_MOTIONPLAYER:
					pMotionPlayer = (CObjectMotionPlayer*)pObject;

					EscData = pMotionPlayer->GetClassData();
					break;


				case CObject::OBJECT_MOTIONENEMY_NOMAL:
					pEnemyNomal = (CObjectMotionEnemyNomal*)pObject;

					EscData = pEnemyNomal->GetClassData();
					break;

				

				case CObject::OBJECT_MAX:
					return HitData;


					break;
				}


				TarGet_Collision_Min_Pos = EscData.Pos + EscData.MinLength;
				TarGet_Collision_Max_Pos = EscData.Pos + EscData.MaxLength;



				D3DXVECTOR3 direction = TargetPos-MyPos;//相手と自機の位置の差分でベクトル作成
				D3DXVECTOR3 normalizedDir;
				D3DXVec3Normalize(&normalizedDir, &direction);

				// 当たり判定の結果を保存する変数
				bool collision = false;
				float collisionDistance = 0.0f;//衝突した距離

				D3DXVECTOR3 rayPos;

				// プレイヤーからカメラに向かう方向にレイを飛ばして、障害物との当たり判定を行う
				while (collision == false)
				{
					 rayPos = MyPos + normalizedDir * collisionDistance;

					if (rayPos.x < TarGet_Collision_Max_Pos.x && rayPos.x > TarGet_Collision_Min_Pos.x &&
						rayPos.y < TarGet_Collision_Max_Pos.y && rayPos.y > TarGet_Collision_Min_Pos.y &&
						rayPos.z < TarGet_Collision_Max_Pos.z && rayPos.z > TarGet_Collision_Min_Pos.z)
					{
						// 衝突が検知された場合、collisionDistanceを調整して再度判定
						collision = true;
					}

					// レイの移動距離を増やして再度判定
					collisionDistance += 0.5f;

					// レイが一定距離(相手とプレイヤーの距離)以上伸びた場合、無限ループを防ぐために抜ける
					if (MaxLength < collisionDistance)
					{
						break;
					}
				}



				// 衝突時にカメラの位置を調整
				if (collision == true)
				{
					HitData.ContactPoint = rayPos -(normalizedDir * 0.98f);
					HitData.bHit = true;
					
					return HitData;
				}






				CObject* pNext = pObject->GetNext();
				pObject = pNext;
				nIndex++;
			}
		}
	}

	return HitData;
}
//=============================
// mesh
//=============================
D3DXVECTOR3 CMathProc::GetMeshNormal(ID3DXMesh* pMesh, DWORD faceIndex)
{
	if (pMesh == nullptr) return D3DXVECTOR3(0, 0, 0);

	struct Vertex {
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
	};

	// 頂点バッファをロック
	Vertex* vertices;
	if (FAILED(pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&vertices))) {
		return D3DXVECTOR3(0, 0, 0);  // ロックに失敗した場合、エラーハンドリング
	}

	// インデックスバッファをロック
	DWORD* indices;
	if (FAILED(pMesh->LockIndexBuffer(D3DLOCK_READONLY, (void**)&indices))) {
		pMesh->UnlockVertexBuffer();  // インデックスのロックに失敗したら、頂点バッファをアンロック
		return D3DXVECTOR3(0, 0, 0);  // エラーハンドリング
	}

	DWORD numFaces = pMesh->GetNumFaces();
	if (faceIndex >= numFaces) {
		pMesh->UnlockVertexBuffer();  // 範囲外のインデックスは無効
		pMesh->UnlockIndexBuffer();
		return D3DXVECTOR3(0, 0, 0);
	}

	DWORD index1 = indices[faceIndex * 3];
	DWORD index2 = indices[faceIndex * 3 + 1];
	DWORD index3 = indices[faceIndex * 3 + 2];

	D3DXVECTOR3 normal = (vertices[index1].normal + vertices[index2].normal + vertices[index3].normal) / 3.0f;

	pMesh->UnlockVertexBuffer();
	pMesh->UnlockIndexBuffer();

	return normal;
}
//=============================
// Routeテーブル取得
//=============================
void CMathProc::LoadRouteCSV(const char* filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "ファイルを開けませんでした: " << filename << std::endl;
		return;
	}

	try
	{
		std::string line;
		int y = 0;

		while (std::getline(file, line) && y < GRIDROW)
		{
			std::istringstream lineStream(line);
			std::string cell;
			int x = 0;

			while (std::getline(lineStream, cell, ',') && x < GRIDCOL)
			{
				try
				{
					RouteTable[x][y] = std::stoi(cell);
				}
				catch (const std::invalid_argument&)
				{
					std::cerr << "数値変換エラー: " << cell << std::endl;
					RouteTable[x][y] = -1; // エラー時のデフォルト値
				}
				x++;
			}
			y++;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "読み込み中にエラーが発生しました: " << e.what() << std::endl;
	}

	file.close(); // 明示的な close（不要だが記述しても問題ない）
}




