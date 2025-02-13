//=========================================================
//
// enemy_motion_Nomal.cppで使う関数[enemy_motion_Nomal.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONENEMYBOSS_H

#define _MOTIONENEMYBOSS_H//二重インクルード防止

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
#include "shield.h"

//これはCObjectMotionEnemyBaseの派生クラス

class CObjectMotionEnemyBoss : public CObjectMotionEnemyBase
{
public:
	const float MOVEROT = 0.065f;				//旋回速度
	const float MOVESPEED = 3.2f;				//移動速度
	static const int LIFE = 1000;				//体力
	static const int BULLETMOVESPEED_NOMAL = 25;//砲弾速度
	static const int BULLETSHOTDELAY = 175;		//発砲間隔
	static const int  reflectNum = 0;			//反射回数
	static const int DAMAGEFRAME = 3;			//被弾時フレーム数
	static const int LOCKDIFF = 200;			//ロックオン用差分
	static const int EMNEMY_DROPCOUNT = 300;	//敵出現カウント

	CObjectMotionEnemyBoss(int nPriority = CObject::LAYERINDEX_MOTIONENEMY_BOSS);//コンストラクタ


	~CObjectMotionEnemyBoss() override;//デストラクタ

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionEnemyBoss* Create(std::string pfilePass, DATA SetData);//オブジェクト生成

	//スクリーンポジションを取得
	void SetSCREENPOS(D3DXVECTOR3 pos) { m_ScreenPosition = pos; };
	D3DXVECTOR3 GetScreenPos() { return m_ScreenPosition; };

	//ロックオンUI取得
	CLockOnUI* GetLockOnUI() { return m_LockOnUI; };
	//メインロックオンUI取得
	CLockOnUIMain* GetLockOnUIMain() { return m_LockOnUI_Main; };

	//被弾
	void SetDamage(int nDamage) { m_nLife -= nDamage; m_bDamageRedNow = true; m_nDamageFrameCnt = DAMAGEFRAME; };

	//敵総数取得
	static int GetEnemyAllNum() { return m_nNumENemyAll; };

private:

	CMathProc::CollisionData m_HitData = {};//当たり判定データ

	int m_nLife = LIFE;
	int m_nBulletDelay = 0;//発砲Delay

	D3DXVECTOR3 m_TargetPos = {};//現在の目標地点
	int m_nOldTargetGRIDNum = -1;//相手の過去の位置番号
	int m_nOldMyGRIDNum = -1;//自分の過去のいち番号

	D3DXVECTOR3 m_TargetMove = {};

	//現在の移動先GRID
	int nNowMoveGRIDNum = -1;


	bool bTurretRotationNow = false;//旋回中
	float fRotTurret = 0.0f;//砲塔の角度

	int m_nMoveCnt = 0;

	//以下"基本は3D"のみ
	CLockOnUI* m_LockOnUI = {};
	CLockOnUIMain* m_LockOnUI_Main = {};

	D3DXVECTOR3 m_ScreenPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bool m_bDamageRedNow = false;
	int m_nDamageFrameCnt = 0;

	int m_nEscCnt = 60;

	CShield* m_pShield;//シールドを格納

	int m_nMovieCnt = 0;
	static int m_nNumENemyAll;//敵総数

	int m_nEnemyCreateCnt = 0;

};

#endif