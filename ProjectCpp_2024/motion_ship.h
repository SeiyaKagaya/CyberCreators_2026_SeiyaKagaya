//=========================================================
//
// player_motion.cppで使う関数[player_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECT_SHIP_H

#define _OBJECT_SHIP_H//二重インクルード防止

#include "object_motion.h"
#include "newbullet.h"


//class CShield;//前方宣言

class CObjectShip : public CObjectMotion
{
public:
	//static const int START_LIFE = 500;
	static const int START_PLAYER_NUM = 3;		//残基数
	static const int AABB_BOX_PLAYER = 90;		//AABBサイズ
	//static const int RESET_CNT = 90;			//復活速度
	//static const int  MOVESPEED = 9;			//移動速度
	//static const int GRAVITY = 29;				//重力
	//const float JoyStickDiff = 0.0004f;			//スティック倍率
	//static const int BULLETSPEED = 125;			//砲弾速度
	//static const int RANDINGTRIGGER_FARAME = 10;//着地判定フレーム
	//static const int BOOST_FARAME = 4;			//Boostのフレーム
	//static const int BOOST_RESTFARAME = 5;		//Boost後の余韻
	//static const int BOOST_MAG = 3;				//ブースト時アフターバーナー倍率

	//static const int MISSILEMAX = 6;			//ミサイルのストック最大値
	//static const int RECOVERY_MISSILE = 45;		//記載フレームで1回復

	//const float SHIELD_SET_ADDPOS = 130.0f;
	//const float TARGET_SET_ADDPOS = 150.0f;
	//const float SHOTPOS_Y = 70.0f;
	//const float SHOTPOS_Z = -190.0f;



	CObjectShip(int nPriority = CObject::LAYERINDEX_MOTIONB2);//コンストラクタ
	~CObjectShip() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectShip* Create(std::string pfilePass, DATA SetData);//オブジェクト生成




private:

	static int m_nNumPlayerAll;//総数
//	bool m_bDown;//ダウンしたか

	CMathProc::CollisionData m_HitData;//当たり判定データ

//	bool m_btest = false;

//	int m_nLife;//体力


//	int m_nMoveCnt;//足跡

//	int m_ResetCnt = 0;//Resetフレーム

//	int m_ShotDelay = 0;//発砲delay

//	D3DXVECTOR3 m_RESTART_POS;//リスタート地点

//	D3DXVECTOR3 m_TargetPos;//照準位置

//	int m_EscCntFootPrint = 0;//足跡カウンター(タイトル)

	MOTIONTYPE m_OldInputMotionParent = MOTIONTYPE_STANDBY;//古いモーション

///	bool m_GameStart = false;//ゲームスタートした直後か
//	int m_RandingCutCnt = 0;//着地カウンター


//	int m_nBoostCnt = 0;//ブースト期間
	//int m_BoostRestCnt = 0;//ブースト終了後期間

	//GUARD状態
//	bool m_guard = false;

//	CShield* m_pShield;//シールドを格納

//	bool m_bBuletLockOn = false;//





//	int m_nMissileStock = MISSILEMAX;//ミサイルストック数
//	int m_nMissileRecoveryCnt = 0;	 //ミサイルの回復カウント
	int m_nCntFrame = 0;
};

#endif