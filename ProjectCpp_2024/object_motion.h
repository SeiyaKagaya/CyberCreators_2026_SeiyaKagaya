//=========================================================
//
// object_motion.cppで使う関数[object_motion.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _OBJECTMOTION_H

#define _OBJECTMOTION_H//二重インクルード防止

#include "object.h"
#include "objectX.h"

#include <Windows.h>
#include "d3dx9.h"//描写処理に使う
#include "MathUtilities.h"
#include <vector>
#include "ModelParts.h"

class CObjectMotion : public CObjectX
{
public:

	typedef enum
	{
		MOTIONTYPE_STANDBY = 0,
		MOTIONTYPE_MOVE_FRONT,
		MOTIONTYPE_MOVE_BACK,
		MOTIONTYPE_HIGH_MOVE_FRONT,
		MOTIONTYPE_HIGH_MOVE_BACK,
		MOTIONTYPE_HIGH_MOVE_LEFT,
		MOTIONTYPE_HIGH_MOVE_RIGHT,
		MOTIONTYPE_ATTACK,
		MOTIONTYPE_GUARD,
		MOTIONTYPE_JUMP,
		MOTIONTYPE_RANDING,
		MOTIONTYPE_BREND,
		MOTIONTYPE_MAX,
	}MOTIONTYPE;

	// 定数
	const int GROUND_COUNTER_THRESHOLD = 10; // 接地状態を維持するためのカウント閾値


	 const float  BULLET_SHOT_POS_Y = 45.0f;//balletの高さY

	const  float DAMPING_RATIO_LOAD_XZ = 0.3f;
	const  float DAMPING_RATIO_Y = 0.095f;


	static const int MAX_PARTS = 30;//最大parts数
	static const int MAX_WORD = 1000;
	static const int MAXKEY = 60;
	static const int MAX_MOTION = MOTIONTYPE_MAX;
	static const int MAX_TEXTURE = 10;
	static const int BRENDFLAME = 2;

	//------------------------------------------------------------------------
	typedef struct
	{
		//あくまで、OFFSETから見た補正値
		D3DXVECTOR3 CorrectionPos;	//位置補正量
		D3DXVECTOR3 CorrectionRot;	//向き補正量
	}PARTSDATA;//PARTSごとの補正データ

	typedef struct
	{
		int nSplitFrame;//分割フレーム数

		PARTSDATA PartsData[MAX_PARTS];//モーションの中でのパーツデータたち

	}KEYDATA;//キー単位-----------Key数で変動

	typedef struct
	{
		int Motiontype;//MOTIONの種類//int型で仕様
		int nLoop;//ループするか[0:ループしない1:ループする]
		int nNumKey;//モーションのキーの数

		KEYDATA KeyData[MAXKEY];
	}MOTION;//モーションのデータ--モーションの数ある

	typedef struct
	{
		//モーションの位置計算に運用、最後にMODELのDrawPosSに入れる
		D3DXVECTOR3 Pos;	//位置
		D3DXVECTOR3 Rot;	//向き
		int INDEX;//自分の番号
		int PEARENT;		//自分の親

		D3DXMATRIX mtxWorld;//ワールドマトリックス

		//はじめのTポーズ
		D3DXVECTOR3 StartPos;
		D3DXVECTOR3 StartRot;


		D3DXVECTOR3 CorrectCorrectionPosMove;//モーションでの移動量pos
		D3DXVECTOR3 CorrectCorrectionRotMove;//モーションでの移動量move
		bool calculationExecution;//補正値計算したかbool
	
	}MODELPARTS;//現在のパーツのデータ

	typedef struct
	{
		int nMaxMotionCnt;//最大モーション数

		int nMaxPartsCnt;//最大パーツ数
		int nMaxLoadPartsCnt;//読み込む最大パーツ数

	//	MODELPARTS ModelParts[MAX_PARTS];//運用する現在のParts--X
		MOTION Motion[MAX_MOTION];//五代モーションなど

	}MODEL;//モデル(という存在)
	//---------------------------------------------------------------------------

	CObjectMotion(int nPriority = CObject::LAYERINDEX_MOTIONMODEL);//コンストラクタ
	~CObjectMotion() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotion* Create(const char* pfilePass,DATA SetData);//オブジェクト生成


	 void DataLoad();//motion.txt読み込みとクリエイトを行う

	void SetFilePass(const char* FilePass);//ファイルパス格納


	//motion1系
	void Motion_Parent();//motion本体
	void Motion_Sub();//サブmotion

	void SetNowMotion_Parent(MOTIONTYPE nMotionNum);
	void SetNowMotion_Sub(MOTIONTYPE nMotionNum);
	
	//motion
	MOTIONTYPE GetNowMotionParent() { return m_NowMotionIndex_Parent;};
	MOTIONTYPE GetNowMotionSub() { return m_NowMotionIndex_Sub; };
	



	void SetClassData(DATA data);//集合体と見てのDATA
	DATA GetClassData();//集合体としてのDATA取得


	D3DXMATRIX GetMatrix();
	void SetMatrix(D3DXMATRIX mtx);

	//変更データをこのクラスを介してパーツにわたす
	void SetChangeDataInObjectMotion(DATA ChangeData);
	
	//パーツ取得
	CModelParts* GetModelParts(int index);
	//パーツ数取得
	int GetMaxLoadPartsNum();

	//データ変更があるモデル番号取得(今回は砲塔)
	int GetChangeDataPartsIndex();

	//OBBの大きさ入力
	void SetOBBLength(float fLength[3]);

	//OBB取得
	COBB GetOBB();

	//GRID番号取得
	int GetNowGRIDNum();

	//自機から障害物などへの当たり判定(player/enemy共通)
	void HitCollisionToStageBlock();

	//このときのmove値取得
	D3DXVECTOR3 GetNowMove();

	//着地状態か
	void SetIsOnGroundBool(bool bSet);
	bool GetIsOnGroundBool();// { return m_isOnGround; };

	////空中状態か
	//void SetIsInAirBool(bool bSet);
	//bool GetIsInAirBool();// { return m_isInAir; };

	//着地motion発動したかか
	void SetIsLandingTriggerBool(bool bSet);
	bool GetIsLandingTriggerBool();// { return m_isLandingTriggered; };

	//着地motion発動したかか
	void SetOldPosY(float OldPosY);
	float GetOldPosY();




	int GetGroundFrame();
	void SetGroundFrame(int cnt);

private:

	CMathProc::CollisionData m_HitData;//当たり判定データ

	MODEL m_Model;//モデルと言う存在

	const char* m_PartfilePass[MAX_PARTS];					//各modelごとのpass

	 LPD3DXMESH m_pMesh[MAX_PARTS];							//Meshポインタ
	 LPD3DXBUFFER m_pBuffMat[MAX_PARTS*3];					//マテリアルへのポインタ
	 DWORD m_dwNumMat[MAX_PARTS*3];							//マテリアルの数
	 LPDIRECT3DTEXTURE9 m_pTexture[MAX_PARTS][MAX_TEXTURE];//テクスチャ

	 DATA m_CrassData;		//一個体としてのデータ

	const char* m_FilePass;	//motionのパス

	D3DXMATRIX m_mtxWorld;	//マトリックス格納


	//motionで必要シリーズ-------------------------------
	MOTIONTYPE m_oldMotionIndex_Parent;	//前回のmotion
	MOTIONTYPE m_NowMotionIndex_Parent;	//今のmotion
	int m_NowKeyCnt_Parent;	//現在のmotionのキーCnt
	int m_NowFrameCnt_Parent;	//現在のmotionのフレームCnt
	int m_EscapeMotion_Parent;		//motionの退避用
	int m_BrendCnt_Parent;			//motionブレンド用Cnt
	bool m_MotionLoopStop_Parent;	//motionループを止めるかbool
	bool m_MotionBrend_Parent;		//motionブレンドをするかbool
	//----------------------------------------------------

	//motionで必要シリーズ------------------------------------------サブ
	MOTIONTYPE m_oldMotionIndex_Sub;	//前回のmotion
	MOTIONTYPE m_NowMotionIndex_Sub;	//今のmotion

	int m_NowKeyCnt_Sub;	//現在のmotionのキーCnt
	int m_NowFrameCnt_Sub;	//現在のmotionのフレームCnt
	int m_EscapeMotion_Sub;		//motionの退避用
	int m_BrendCnt_Sub;			//motionブレンド用Cnt
	bool m_MotionLoopStop_Sub;	//motionループを止めるかbool
	bool m_MotionBrend_Sub;		//motionブレンドをするかbool
	//---------------------------------------------------------------













	CModelParts* m_pModelParts[MAX_PARTS];
	int m_ChangeDataModelIndex;//データ変更のあるモデルのインデックス


	//OBBの当たり判定用
	COBB m_Obb;

	//
	int m_NowGridNum;//現在の自分のいるGRIDの番号
	int m_RunCnt = 0;




//	bool m_isInAir=true;//空中にいるかどうか
	bool m_isLandingTriggered=false;//着地モーションが発動したかどうか
	bool m_isOnGround=false;//地面に接触しているかどうか
	// 接地状態を保持するための変数
	int m_groundCounter; // 接地状態のカウンター

	float m_OldPosY = 0.0f;
};

#endif