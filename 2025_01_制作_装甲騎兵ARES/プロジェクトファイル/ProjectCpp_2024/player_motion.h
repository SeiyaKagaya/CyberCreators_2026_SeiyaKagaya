//=========================================================
//
// player_motion.cppで使う関数[player_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONPLAYER_H

#define _MOTIONPLAYER_H//二重インクルード防止

#include "object_motion.h"
#include "newbullet.h"


class CShield;//前方宣言
class CBulletLine;

class CObjectMotionPlayer : public CObjectMotion
{
public:
	static const int START_LIFE = 500;
	static const int BOOST_LIFE = 250;
	static const int START_PLAYER_NUM = 3;		//残基数
	static const int AABB_BOX_PLAYER = 90;		//AABBサイズ
	static const int RESET_CNT = 90;			//復活速度
	static const int  MOVESPEED = 9;			//移動速度
	static const int GRAVITY = 29;				//重力
	const float JoyStickDiff = 0.0004f;			//スティック倍率
	static const int BULLETSPEED = 100;			//砲弾速度
	static const int RANDINGTRIGGER_FARAME = 10;//着地判定フレーム
	static const int BOOST_FARAME = 4;			//Boostのフレーム
	static const int BOOST_RESTFARAME = 5;		//Boost後の余韻
	static const int BOOST_MAG = 3;				//ブースト時アフターバーナー倍率
	
	static const int MISSILEMAX = 6;			//ミサイルのストック最大値
	static const int RECOVERY_MISSILE = 45;		//記載フレームで1回復

	static const int RECOVERY_Boost = 2;		//記載フレームで1回復
	static const int BOOSTJUMP_USE = 8;
	static const int BOOSTMOVE_USE = 40;
	static const int DAMAGEFRAME = 3;

	const float SHIELD_SET_ADDPOS = 130.0f;
	const float TARGET_SET_ADDPOS = 150.0f;
	const float SHOTPOS_Y = 70.0f;
	const float SHOTPOS_Z = -190.0f;



	CObjectMotionPlayer(int nPriority = CObject::LAYERINDEX_MOTIONPLAYER);//コンストラクタ
	~CObjectMotionPlayer() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionPlayer* Create(std::string pfilePass, DATA SetData);//オブジェクト生成


	void ControllerInput2D();//コントローラ入力--2D
	void ControllerInput3D();//コントローラ入力--3D

	static void SetPlayerNum(int SetNum);//残機格納
	static int GetPlayerNum();//残機取得

	void SetStartPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetTARGETPOS();

	void SetLinearInterpolation();

	void SetbGuard(bool bSet) { m_guard = bSet; };
	bool GetbGuard() { return m_guard; };

	int GetLife() { return m_nLife; };

	//敵ロックオン処理
	void LockOnEnemy();

//	bool IsInScreen(D3DXVECTOR3 screenPosition);

	void SetDamage(int nDamage) { m_nLife -= nDamage; m_bDamageRedNow = true; m_DamageFrameCnt = DAMAGEFRAME; };

	int GetNowMissileNum() { return m_nMissileStock; };
	int GetNowRecoveryMissileNum() { return m_nMissileRecoveryCnt;};

	int GetNowBoostLife() { return m_nBoostLife; };

private:

	static int m_nNumPlayerAll;//総数
	 bool m_bDown;//ダウンしたか

	CMathProc::CollisionData m_HitData;//当たり判定データ

	bool m_btest = false;

	int m_nLife;//体力


	int m_nMoveCnt;//足跡

	int m_ResetCnt = 0;//Resetフレーム

	int m_ShotDelay = 0;//発砲delay

	D3DXVECTOR3 m_RESTART_POS;//リスタート地点

	D3DXVECTOR3 m_TargetPos;//照準位置

	int m_EscCntFootPrint=0;//足跡カウンター(タイトル)

	MOTIONTYPE m_OldInputMotionParent = MOTIONTYPE_STANDBY;//古いモーション

	bool m_GameStart = false;//ゲームスタートした直後か
	int m_RandingCutCnt = 0;//着地カウンター


	int m_nBoostCnt = 0;//ブースト期間
	int m_BoostRestCnt = 0;//ブースト終了後期間

	//GUARD状態
	bool m_guard = false;
	
	CShield* m_pShield;//シールドを格納
	CBulletLine* m_pBulletLine;

	bool m_bBuletLockOn = false;//

	int m_nMissileStock = MISSILEMAX;//ミサイルストック数
	int m_nMissileRecoveryCnt = 0;	 //ミサイルの回復カウント //RECOVERY_MISSILE

	int m_nBoostLife = BOOST_LIFE;//Boost用ライフ
	int m_nBoostRecoveryCnt = 0;	 //ミサイルの回復カウント //RECOVERY_Boost

	bool m_bDamageRedNow = false;
	int m_DamageFrameCnt = 0;
};

#endif