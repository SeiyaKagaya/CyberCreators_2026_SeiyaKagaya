//=========================================================
//
// player_motion.cppで使う関数[player_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONPLAYER_H

#define _MOTIONPLAYER_H//二重インクルード防止

#include "object_motion.h"

class CObjectMotionPlayer : public CObjectMotion
{
public:
	static const int START_PLAYER_NUM = 3;
	static const int AABB_BOX_PLAYER = 90;
	static const int RESET_CNT = 90;
	static const int  MOVESPEED = 9;
	static const int GRAVITY = 99;//重力

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

private:

	static int m_nNumPlayerAll;//総数
	 bool m_bDown;//ダウンしたか

	CMathProc::CollisionData m_HitData;//当たり判定データ

	bool btest = false;

	int m_nLife;
	int m_nMoveCnt;

	int m_ResetCnt = 0;

	int ShotDelay = 0;//発砲delay

	D3DXVECTOR3 m_RESTART_POS;//リスタート地点

	D3DXVECTOR3 m_TargetPos;//照準位置

	int EscCntFootPrint=0;

	D3DXVECTOR3 m_BulletPosMove=D3DXVECTOR3(0.0f,0.0f,0.0f);

	MOTIONTYPE m_OldInputMotionParent = MOTIONTYPE_STANDBY;


	bool m_GameStart = false;
};

#endif