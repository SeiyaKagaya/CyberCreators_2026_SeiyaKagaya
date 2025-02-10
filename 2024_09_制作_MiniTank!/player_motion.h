//=========================================================
//
// player_motion.cppで使う関数[player_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MOTIONPLAYER_H
#define _MOTIONPLAYER_H//二重インクルード防止

#include "object_motion.h"
#include "HpLatter.h"
#include "HP_gauge.h"
#include "resuscitation.h"

class CObjectMotionPlayer : public CObjectMotion
{
public:
	static const int START_PLAYER_NUM = 3;				//残機
	static const int AABB_BOX_PLAYER = 75;				//AABB用サイズ
	static const int RESET_CNT = 90;					//リスタートカウンタ
	static const int DAMAGE = 100;						//ダメージ
	static const int LIFE = 300;						//寿命
	const float OBB_LENGTH[3] = { 90.0f,90.0f,120.0f };	//OBBの長さ

	CObjectMotionPlayer(int nPriority = CObject::LAYERINDEX_MOTIONPLAYER);//コンストラクタ
	~CObjectMotionPlayer() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotionPlayer* Create(const char* pfilePass, DATA SetData);//オブジェクト生成

	void Input();						  //入力系(static)
	void ControllerInput();				  //コントローラ入力

	static void SetPlayerNum(int SetNum); //残機格納
	static int GetPlayerNum();			  //残機取得

	void SetStartPos(D3DXVECTOR3 pos);	  //スタート地点格納
	D3DXVECTOR3 GetTARGETPOS();			  //目標地点取得

	void SetLinearInterpolation();		  //線形補間地点描画

private:

	static int m_nNumPlayerAll;					//総数
	 bool m_bDown=false;						//ダウンしたか

	 CMathProc::CollisionData m_HitData = {};	//当たり判定データ

	int m_nLife=0;								//寿命
	int m_nMoveCnt=0;							//移動カウンタ
	int m_ResetCnt = 0;							//リセットカウンタ
	int ShotDelay = 0;							//発砲delay
	int EscCntFootPrint=0;						//足跡カウンタ

	D3DXVECTOR3 m_RESTART_POS = {};				//リスタート地点
	D3DXVECTOR3 m_TargetPos = {};				//照準位置
	D3DXVECTOR3 m_BulletPosMove = {};			//照準位置用move値
	CObjectHPLatterUI* m_pHPUI = nullptr;		//HP用UI
	CObjectHPGaugeUI* m_pHPGauge[2] = {};		//HPゲージ用UI
	CRescue* m_Resue = nullptr;					//蘇生用UI
};

#endif