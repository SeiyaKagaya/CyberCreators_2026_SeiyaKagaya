//=========================================================
//
// player_motion.cppで使う関数[player_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONPLAYER_H

#define _MOTIONPLAYER_H//二重インクルード防止

#include "object_motion.h"



class CShield;//前方宣言

class CObjectMotionPlayer : public CObjectMotion
{
public:
	static const int START_PLAYER_NUM = 3;		//残基数
	static const int AABB_BOX_PLAYER = 90;		//AABBサイズ
	static const int RESET_CNT = 90;			//復活速度
	static const int  MOVESPEED = 9;			//移動速度
	static const int GRAVITY = 29;				//重力
	const float JoyStickDiff = 0.0004f;			//スティック倍率
	static const int BULLETSPEED = 35;			//砲弾速度
	static const int RANDINGTRIGGER_FARAME = 10;//着地判定フレーム
	static const int BOOST_FARAME = 4;			//Boostのフレーム
	static const int BOOST_RESTFARAME = 5;		//Boost後の余韻
	static const int BOOST_MAG = 3;				//ブースト時アフターバーナー倍率

	CObjectMotionPlayer(int nPriority = CObject::LAYERINDEX_MOTIONPLAYER);//コンストラクタ
	~CObjectMotionPlayer() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionPlayer* Create(const char* pfilePass, DATA SetData);//オブジェクト生成

	void Input();//入力系(static)
	void ControllerInput();//コントローラ入力

	static void SetPlayerNum(int SetNum);//残機格納
	static int GetPlayerNum();//残機取得

	void SetStartPos(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetTARGETPOS();

	void SetLinearInterpolation();

	void SetbGuard(bool bSet) { m_guard = bSet; };
	bool GetbGuard() { return m_guard; };

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
};

#endif