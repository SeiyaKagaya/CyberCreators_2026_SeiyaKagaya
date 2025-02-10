//=========================================================
//
// enemy_motion_Nomal.cppで使う関数[enemy_motion_Nomal.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYNOMAL_H
#define _MOTIONENEMYNOMAL_H//二重インクルード防止

#include "enemy_motion_base.h"

//これはCObjectMotionEnemyBaseの派生クラス

class CObjectMotionEnemyNomal : public CObjectMotionEnemyBase
{
public:
	const float MOVEROT = 0.065f;						//旋回速度
	const float MOVESPEED = 3.2f;						//砲弾速度1
	static const int MOVESPEED2 = 12;					//砲弾速度2
	static const int BULLETSHOTDELAY = 175;				//発砲間隔
	static const int LIFE = 100;						//寿命
	static const int DAMAGE = 100;						//ダメージ
	static const int RADIUS = 110;						//半径
	const float OBB_LENGTH[3] = { 90.0f,90.0f,120.0f }; //OBBの長さ

	CObjectMotionEnemyNomal(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_NOMAL);//コンストラクタ
	 ~CObjectMotionEnemyNomal() override;//デストラクタ

	 HRESULT Init()override;
	 void Uninit()override;
	 void Update()override;
	 void Draw()override;

	static CObjectMotionEnemyNomal* Create(const char* pfilePass, DATA SetData);//オブジェクト生成

	void Attack();						//攻撃関係
	DATA phase1(D3DXVECTOR3 ShotPos);	//攻撃フェーズ1
	DATA phase2();						//攻撃フェーズ2

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//砲塔旋回
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);	 //射撃系

private:

	CMathProc::CollisionData m_HitData = {};//当たり判定データ
	D3DXVECTOR3 m_TargetPos = {};			//現在の目標地点
	int m_nLife=0;							//寿命
	int m_BulletDelay=0;					//発砲間隔
	int m_OldTargetGRIDNum = -1;			//相手の過去の位置番号
	int m_OldMyGRIDNum = -1;				//自分の過去のいち番号
	int NowMoveGRIDNum = -1;				//現在の移動先GRID
	int m_nMoveCnt = 0;						//移動カウンタ
	bool bTurretRotationNow=false;			//旋回中
	float fRotTurret=false;					//砲塔の角度
};

#endif