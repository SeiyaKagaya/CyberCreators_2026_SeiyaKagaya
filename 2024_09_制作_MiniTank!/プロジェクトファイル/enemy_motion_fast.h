//=========================================================
//
// enemy_motion_fast.cppで使う関数[enemy_motion_fast.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYFAST_H
#define _MOTIONENEMYFAST_H//二重インクルード防止

#include "enemy_motion_base.h"


//これはCObjectMotionEnemyBaseの派生クラス

class CObjectMotionEnemyfast : public CObjectMotionEnemyBase
{
public:
	const float POSY = 4.0f;										 //固定の高さ
	const float MOVEROT = 0.065f;									 //旋回速度
	const float MOVESPEED = 4.8f;									 //砲弾速度1
	const float TARGETSPEED = 1500.0f;								 //相手の予測速度
	const float TANKFIRE_OFFSETPOS_Z = -190.0f;						 //砲塔の先端位置までのoffset
	const float BULLETSIZE = 30.0f;									 //砲弾予測サイズ
	const float OBB_LENGTH[3] = { 90.0f,90.0f,120.0f };				 //OBBの長さ
	static const int MOVESPEED2 = 15;								 //砲弾速度2
	static const int BULLETSHOTDELAY = 155;							 //発砲間隔
	static const int LIFE = 100;									 //寿命
	static const int DAMAGE = 100;									 //ダメージ
	static const int RADIUS = 110;									 //半径
	static const int BULLET_LINE_LENGTH = 80;						 //射線の長さ
	static const int STAMPCNT = 30;									 //履帯後カウント
	const D3DXCOLOR ENEMY_COLOR = D3DXCOLOR(0.3f, 0.1f, 0.3f, 1.0f); //敵の色
	const D3DXCOLOR BULLET_COLOR = D3DXCOLOR(0.7f, 0.3f, 0.3f, 1.0f);//弾の色

	
	
	CObjectMotionEnemyfast(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_FAST);//コンストラクタ

	~CObjectMotionEnemyfast() override;//デストラクタ

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionEnemyfast* Create(const char* pfilePass, DATA SetData);//オブジェクト生成

	void Attack();						//攻撃関係
	DATA phase1(D3DXVECTOR3 ShotPos);	//攻撃フェーズ1
	DATA phase2();						//攻撃フェーズ2

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//砲塔旋回
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);	//射撃系

private:

	CMathProc::CollisionData m_HitData = {}; //当たり判定データ
	D3DXVECTOR3 m_TargetPos = {};		  	 //現在の目標地点
	int m_nLife=0;							 //寿命
	int m_BulletDelay=0;					 //発砲間隔
	int m_nMoveCnt = 0;						 //移動カウンタ
	int m_OldTargetGRIDNum = -1;			 //相手の過去の位置番号
	int m_OldMyGRIDNum = -1;				 //自分の過去のいち番号
	int NowMoveGRIDNum = -1;				 //現在の移動先GRID
	bool bTurretRotationNow=false;			 //旋回中
	float fRotTurret=0.0f;					 //砲塔の角度
};
#endif