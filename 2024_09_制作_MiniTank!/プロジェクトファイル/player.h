//=========================================================
//
// player.cppで使う関数[player.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _PLAYER_H
#define _PLAYER_H//二重インクルード防止

#include "object.h"
#include "object2D.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
#include "MathUtilities.h"

//
class CPlayer : public CObject2D
{
public:

	static const int MAXSHOTDERAY = 7;		//発砲ディレイ値
	static const int PLAYER_WIDE = 75;		//幅
	static const int PLAYER_HEIGHT = 100;	//高さ
	static const int DISTANCE = 2;					//調整幅

	CPlayer(int nPriority=CObject::LAYERINDEX_PLAYER);//コンストラクタ
	~CPlayer() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CPlayer* Create();//オブジェクト生成

	//頂点格納
	void InputpVtx()override;

private:

	 void Action_Keyboard();	//操作受付Keyboard
	 void Action_JoyPad();		//操作受付ジョイパッド
	 void HitCollision();		//当たり判定まとめ

	 int m_nCounterAnim = 0;	//アニメCounter
	int m_nDirectionMove = 0;	//向き//0が右向き1が左
	int m_nPatternAnim = 0;		//パターン番号
	int m_BulletShotDelay = 0;	//発砲間隔カウント
	
	float m_MAG = 0.0f;			//倍率
	float m_fLength = 0.0f;		//長さ
	float m_fAngle = 0.0f;		//角度

	bool m_bLandingNow = false; //着地

	CMathProc::CollisionData m_HitData = {};//当たり判定データ
};

#endif