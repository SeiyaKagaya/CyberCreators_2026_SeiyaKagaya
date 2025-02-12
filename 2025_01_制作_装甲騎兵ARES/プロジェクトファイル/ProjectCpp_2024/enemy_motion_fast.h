//=========================================================
//
// enemy_motion_fast.cppで使う関数[enemy_motion_fast.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYFAST_H
#define _MOTIONENEMYFAST_H//二重インクルード防止

#include "enemy_motion_base.h"
#include "LockOnUI.h"
#include "LockOnUIMain.h"



//これはCObjectMotionEnemyBaseの派生クラス

class CObjectMotionEnemyfast : public CObjectMotionEnemyBase
{
public:
	const float MOVEROT = 0.065f;//旋回速度
	static const int BULLETMOVESPEED_NOMAL = 25;//砲弾速度
	static const int BULLETSHOTDELAY = 75;
	const float MOVESPEED = 4.8f;
	static const int  reflectNum = 0;
	static const int DAMAGEFRAME = 3;
	static const int LOCKDIFF = 40;

	CObjectMotionEnemyfast(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_FAST);//コンストラクタ


	~CObjectMotionEnemyfast() override;//デストラクタ

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionEnemyfast* Create(std::string pfilePass, DATA SetData);//オブジェクト生成

	void Attack();

	void TurretRotation(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);
	void ShotBullet(D3DXVECTOR3 ShotPos, D3DXVECTOR3 TargetPos, D3DXVECTOR3 BulletMove);//砲塔旋回と射撃を統括


	//スクリーンポジションを取得
	void SetSCREENPOS(D3DXVECTOR3 pos) { m_ScreenPosition = pos; };
	D3DXVECTOR3 GetScreenPos() { return m_ScreenPosition; };

	void SetDamage(int nDamage) { m_nLife -= nDamage; m_bDamageRedNow = true; m_nDamageFrameCnt = DAMAGEFRAME; };

	CLockOnUI* GetLockOnUI() { return m_LockOnUI; };
	CLockOnUIMain* GetLockOnUIMain() { return m_LockOnUI_Main;};

private:

	CMathProc::CollisionData m_HitData;//当たり判定データ

	int m_nLife = 0;
	int m_BulletDelay = 0;

	D3DXVECTOR3 m_TargetPos;//現在の目標地点
	int m_nOldTargetGRIDNum = -1;//相手の過去の位置番号
	int m_nOldMyGRIDNum = -1;//自分の過去のいち番号

	D3DXVECTOR3 m_TargetMove;

	//現在の移動先GRID
	int m_nNowMoveGRIDNum = -1;

	bool m_bTurretRotationNow=false;//旋回中
	float m_fRotTurret=false;//砲塔の角度

	int m_nMoveCnt = 0;

	//以下"基本は3D"のみ
	CLockOnUI* m_LockOnUI;	       //--ロックオン
	CLockOnUIMain* m_LockOnUI_Main;//---バレットロックオン

	D3DXVECTOR3 m_ScreenPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bool m_bDamageRedNow = false;
	int m_nDamageFrameCnt = 0;
};

#endif