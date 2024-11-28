//=========================================================
//
// enemy_motion_fast.cppで使う関数[enemy_motion_fast.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYFAST_H

#define _MOTIONENEMYFAST_H//二重インクルード防止

//#include "object.h"
//#include "objectX.h"
//
//#include <Windows.h>
//#include "d3dx9.h"//描写処理に使う
//#include "MathUtilities.h"
//#include <vector>
//#include "object_motion.h"

#include "enemy_motion_base.h"



//これはCObjectMotionEnemyBaseの派生クラス

class CObjectMotionEnemyfast : public CObjectMotionEnemyBase
{
public:
	const float MOVEROT = 0.065f;//旋回速度
	static const int BULLETMOVESPEED_NOMAL = 15;//砲弾速度
	static const int BULLETSHOTDELAY = 75;
	const float MOVESPEED = 4.8f;
	static const int  reflectNum = 0;


	CObjectMotionEnemyfast(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_FAST);//コンストラクタ


	~CObjectMotionEnemyfast() override;//デストラクタ

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionEnemyfast* Create(const char* pfilePass, DATA SetData);//オブジェクト生成

//	virtual void LoadRouteTable()override;

	void Attack();
	DATA phase1(D3DXVECTOR3 ShotPos);
	DATA phase2();

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//砲塔旋回と射撃を統括

private:

	CMathProc::CollisionData m_HitData;//当たり判定データ

//	COBB m_Obb;

	bool btest = false;

	int m_nLife;
	int m_BulletDelay;


	D3DXVECTOR3 m_TargetPos;//現在の目標地点
	int m_OldTargetGRIDNum = -1;//相手の過去の位置番号
	int m_OldMyGRIDNum = -1;//自分の過去のいち番号

	D3DXVECTOR3 m_TargetMove;

	//現在の移動先GRID
	int NowMoveGRIDNum = -1;



	bool bTurretRotationNow;//旋回中
	float fRotTurret;//砲塔の角度

//	int nTurretRotationCnt;//目標角までの分割フレーム数//ある一定の差分まで角度の差異が縮めば射撃開始
	int m_nMoveCnt;
};

#endif