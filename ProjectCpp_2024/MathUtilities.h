//=========================================================
//
// あまたの数値計算を行う関数[MathUtilities.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MATH_H

#define _MATH_H//二重インクルード防止
#include <Windows.h>
#include <d3dx9.h>
#include "object.h"

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <queue>

class  COBB//OBB用
{
public:
	 COBB();
	~ COBB();
protected:
	
public:
	D3DXVECTOR3 m_Direct[3];   // 方向ベクトル
	D3DXVECTOR3 m_Pos;              // 位置
	float m_fLength[3];             // 各軸方向の長さ

	D3DXVECTOR3 GetDirect(int elem);   // 指定軸番号の方向ベクトルを取得
	float GetLen(int elem);          // 指定軸方向の長さを取得
	D3DXVECTOR3 GetPos();             // 位置を取得
	void SetPos(const D3DXVECTOR3& pos);

};

class CMathProc//計算クラス
{
public:
	CMathProc();
	~CMathProc();

	//当たり判定データ
	typedef struct
	{
		bool bHit;//あたったか
		int targetIndex;//相手のインデックス(プライオリティからの番号)
	//	bool SpecialHit;


		//任意
		D3DXVECTOR3 ResultDistance;//当たり判定に読み移動が生じたときに値が入る
		D3DXVECTOR3 HitAngle;//X.Y.zを1.-1で判別
		D3DXVECTOR3 ContactPoint; // 接触点の座標
		D3DXVECTOR3 ReflectionVector;//反射ベクトル格納
	}CollisionData;


	//計算処理ばかりなのでクラスをあえて使わない

	//円形当たり判定
	static	CollisionData CheckCircleCollision(D3DXVECTOR3 MyPos, float fMy_Radius, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer, void* pCaller,int nID);//当たり判定結果とインデックスを返す

		//箱型当たり判定3D
	static	CollisionData CheckBoxCollision_3D(CObject::OBJECTTYPE MyType, D3DXVECTOR3 MyPos, D3DXVECTOR3 MyOldPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength, CObject::OBJECTTYPE TargetType,CObject::LAYERINDEX TargetLayer,D3DXVECTOR3 Mymove,void* pCaller);//当たり判定結果とインデックスを返す

		//箱型当たり判定2D
	static	CollisionData CheckBoxCollision_2D(D3DXVECTOR3 MyPos, D3DXVECTOR3 MyOldPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength, CObject::OBJECTTYPE TargetType);//当たり判定結果とインデックスを返す

	//回転
	static D3DXVECTOR3 ConversionXfireRot3(D3DXVECTOR3 fRot);

	static float ConversionRot2(float NowRot, float fTargetRot);
	

	// OBBとOBBの当たり判定
	static bool ColOBBs(COBB& obb1, COBB& obb2, D3DXVECTOR3* contactPoint);

	// 分離軸に投影された軸成分から投影線分長を算出
	static FLOAT LenSegOnSeparateAxis(D3DXVECTOR3* Sep, D3DXVECTOR3* e1, D3DXVECTOR3* e2, D3DXVECTOR3* e3 = 0);

	// 最小分離軸と最小食い込み深さを使用して接触点を計算
	static D3DXVECTOR3 CalculateContactPoint(COBB& obb1, COBB& obb2, D3DXVECTOR3& minSepAxis, float minPenetration);

	// 衝突後の反発処理を追加
	static void ResolveCollision(COBB& obb1, COBB& obb2, const D3DXVECTOR3& minSepAxis, float minPenetration);

	static CollisionData CheckCircleCollision_Cancel(D3DXVECTOR3 MyPos, float fMy_Radius, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer, void* pCaller);

	static bool AvoidInternalSpawn_3D_BoxCollision(CObject::OBJECTTYPE MyType, D3DXVECTOR3 MyPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer);
	

	//球同士当たり判定(player/enemy均等反発)
//	static CollisionData CheckCircleCollision_Cancel(D3DXVECTOR3 MyPos, float fMy_Radius, CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer);

	//3Dobject内生成防止判定//trueで内部にいる判定
	//static bool AvoidInternalSpawn_3D_BoxCollision(CObject::OBJECTTYPE MyType, D3DXVECTOR3 MyPos, D3DXVECTOR3 MyMinLength, D3DXVECTOR3 MyMaxLength,CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer, void* pCaller);



//	static void 


	//-----------------------------------------------------------------------------------------------------------------
	static const int GRIDROW = 8;//たて
	static const int GRIDCOL = 11;//よこ
	static const int  GRIDLEGTH = 300;//GRIDの辺の長さ
	static const int SHOTPOINUM = 8;

	typedef struct
	{
		int x, y;
	} Point;

	typedef struct
	{
		bool bBlock; // 障害物の有無
		int Num;     // スタートからの距離
		int ObjectNum;//存在番号
		Point ParemtPoint;//親の位置
	} Cell;

	
	static int dx[4]; // 上下左右の移動
	static int dy[4];
	
	// 有効な座標かどうかを確認する関数
	static bool isValid(int x, int y);

	// 幅優先探索（BFS）を実行する関数
	static void bfs(Point start, Point goal);

	// CSVファイルに書き出す関数
	static void writeToCSV(const char* filename);

	//セル状態格納
	static void SetCell(Cell pCell[GRIDROW][GRIDCOL]);


	//--------------------------------------------------
	//Point座標から物体番号取得
	static int GetObjectNumfromPoint(Point point);
	//物体番号からpoint座標取得
	static Point GetPointfromObjectNum(int ObjectNum);
	//--------------------------------------------------

	//セルの状態
	static Cell GRID[GRIDROW][GRIDCOL];

	static int RouteTable[GRIDROW* GRIDCOL][GRIDROW * GRIDCOL];

	static D3DXVECTOR3 m_ShotPos[SHOTPOINUM];//視界不良時射撃位置、最大4箇所



	//------------------------------------------------
	//
	//++そもそも縦８横11のマスの時点で
	//88地点から88地点までの経路
	//　　7744ルートを算出する
	//ルートをそのまま使用は無理(重い)ので経路テーブル化する
	//
	//++深度を元にゴールからスタートまでたどり、その間の地点を経路テーブルに打ち込んでゆく

	//最短ルート算出
	static void RouteTableSet(Point StartPoint, Point GoalPoint);
	

	//CSV書き込み
	static void DRAWCSV( const char* filename);

	//CSV書き込み
	static void LoadRouteCSV(const char* filename);


	//相手の位置番号と自分の位置番号を送り、次に進む位置番号を返す処理。(-100のときはゴールにもう到達していることになる)
	static int GetNextMoveGridNum(int PartnerGridNum, int MyGridNum);

	//objectに現在の位置番号を常に保持させ、それを参照し移動の有無を敵cppに判断させる

	//視界不良時射撃位置
	static void LoadShotPoint(const char* filename);

	////視界不良時射撃取得--自分から一番近い地点のランダムにズレた位置を渡す
	static D3DXVECTOR3 GetShotPos(D3DXVECTOR3 MyPos);


	// 予測交差点を計算する計算
	//static D3DXVECTOR3 PredictIntersection(D3DXVECTOR3 MyPos, D3DXVECTOR3 MyMove, D3DXVECTOR3 TargetPos, D3DXVECTOR3 TargetMove);

	
	//弾道予測照準
	static CObject::DATA FCS_TrajectoryPredictionAiming(D3DXVECTOR3 MyPos, float BulletSpeed, D3DXVECTOR3 TargetPos, D3DXVECTOR3 TargetMove);
	
	//自分と相手の間の障害物判定
	static CollisionData AdjustMyPosToCollision_Partner(D3DXVECTOR3 MyPos, D3DXVECTOR3 MyMin, D3DXVECTOR3 MyMax,D3DXVECTOR3 TargetPos,float MaxLength,CObject::OBJECTTYPE TargetType, CObject::LAYERINDEX TargetLayer);


private:  
	

};

#endif



//当たり判定メモ
// 
//    ballet-->player/enemy                   OBB同士衝突　済

//    ballet-->StageWall/StageBlock          AABB同士衝突  済
 
//　　player<-->enemy                        　球同士衝突  済

//　  player/enemy-->StageWall/StageBlock    AABB同士衝突  済    更に連続で置かさった時用に当たり判定限定箱を設置
