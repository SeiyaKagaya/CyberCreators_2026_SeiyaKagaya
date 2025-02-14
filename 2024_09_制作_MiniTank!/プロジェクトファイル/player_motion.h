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
	static const int FOOTPRINT = 10;					//履帯後のスタンプ
	static const int BULLETSHOTDELAY = 20;							 //発砲間隔
	static const int POINTER_NUM = 7;					//線形補間ポインターの数

	const float BULLETSIZE = 10.0f;						//砲弾予測サイズ
	const float TANKFIRE_OFFSETPOS_Z = -190.0f;			//砲塔の先端位置までのoffset
	const float OBB_LENGTH[3] = { 90.0f,90.0f,120.0f };	//OBBの長さ
	const float STICK_RADIUS = 500.0f;					//照準半径
	const float MOVESPEED = 8.1f;						//移動速度
	const float BULLETMOVE = 14.0f;						//弾丸速度
	const float STICK_MAG = 0.0015f;					//スティック倍率
	const float STICK_SUB = 6000.0f;					//デッドゾーンから
	const float MIN_ANGLE_Y = -0.1f;					//砲塔旋回時の上下の限界アングル
	const float MAX_ANGLE_Y = 0.1f;
	const float POSY = 4.0f;							//固定の高さ

	const D3DXCOLOR BULLET_COLOR = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);//弾の色

	const D3DXVECTOR3 UI_POS[4] = {						//UI用座標
		D3DXVECTOR3(-150.0f,400.0f,100.0f),
		D3DXVECTOR3(-100.0f,400.0f,100.0f) ,
		D3DXVECTOR3(-95.0f,400.0f,100.0f),
		D3DXVECTOR3(-70.0f,400.0f,100.0f)
	};

	const D3DXVECTOR3 UI_SIZE[2] = {					//HPUI用サイズ
	D3DXVECTOR3(320.0f, 18.0f, 0.0f),
	D3DXVECTOR3(-9999.9f, 14.0f, 0.0f) ,
	};

	const D3DXCOLOR HP_UI_COLOR[2] = {					//HPUI用カラー
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f),
		D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.9f)
	}; //敵の色


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