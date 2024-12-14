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
#include "LockOnUI.h"
#include "LockOnUIMain.h"



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


	//スクリーンポジションを取得
	void SetSCREENPOS(D3DXVECTOR3 pos) { m_ScreenPosition = pos; };
	D3DXVECTOR3 GetScreenPos() { return m_ScreenPosition; };

	void SetDamage(int nDamage) { m_nLife -= nDamage; };

	////LOCK ON関係
	//void SetNormalLockOn(bool bSet) { m_bNormalLockOn = bSet; };
	//bool GetNormalLockOn() { return m_bNormalLockOn; };

	//void SetBulletLockOn(bool bSet) { m_bBulletLockOn = bSet; };
	//bool GetBulletLockOn() { return m_bBulletLockOn; };

	//void SetDiffTrue(bool bSet) { m_DiffTrue = bSet; };
	//bool GetDiffTrue() { return m_DiffTrue; };


	CLockOnUI* GetLockOnUI() { return m_LockOnUI; };
	CLockOnUIMain* GetLockOnUIMain() { return m_LockOnUI_Main;};

private:

	CMathProc::CollisionData m_HitData;//当たり判定データ

	bool btest = false;

	int m_nLife = 0;
	int m_BulletDelay = 0;

	D3DXVECTOR3 m_TargetPos;//現在の目標地点
	int m_OldTargetGRIDNum = -1;//相手の過去の位置番号
	int m_OldMyGRIDNum = -1;//自分の過去のいち番号

	D3DXVECTOR3 m_TargetMove;

	//現在の移動先GRID
	int NowMoveGRIDNum = -1;

	bool bTurretRotationNow;//旋回中
	float fRotTurret;//砲塔の角度

	int m_nMoveCnt = 0;

	//以下"基本は3D"のみ
	CLockOnUI* m_LockOnUI;	       //--ロックオン
	CLockOnUIMain* m_LockOnUI_Main;//---バレットロックオン

	D3DXVECTOR3 m_ScreenPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//	bool m_bNormalLockOn = false;//普通ロック
//	bool m_bBulletLockOn = false;//射撃ロック
	//bool m_DiffTrue = false;	 //ロック系計算有無
};

#endif