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

	const float  BULLET_SHOT_POS_Y = 45.0f;//balletの高さY
	const  float DAMPING_RATIO = 0.5f;	   //減衰率
	static const int MAX_PARTS = 15;	   //最大parts数
	static const int MAX_WORD = 1000;	   //最大文字数
	static const int MAXKEY = 60;		   //最大キー数
	static const int MAX_MOTION = 5;	   //最大モーション数
	static const int MAX_TEXTURE = 10;	   //最大テクスチャ数
	static const int BRENDFLAME = 2;	   //モーションブレンド時のフレーム数


	//------------------------------------------------------------------------------------------------------------------------------
	typedef struct
	{
		//あくまで、OFFSETから見た補正値
		D3DXVECTOR3 CorrectionPos;	//位置補正量
		D3DXVECTOR3 CorrectionRot;	//向き補正量
	}PARTSDATA;//PARTSごとの補正データ

	typedef struct
	{
		int nSplitFrame;				//分割フレーム数
		PARTSDATA PartsData[MAX_PARTS];	//モーションの中でのパーツデータたち

	}KEYDATA;//キー単位-----------Key数で変動

	typedef struct
	{
		int Motiontype;			//MOTIONの種類//int型で仕様
		int nLoop;				//ループするか[0:ループしない1:ループする]
		int nNumKey;			//モーションのキーの数
		KEYDATA KeyData[MAXKEY];//キー単位

	}MOTION;//モーションのデータ--モーションの数ある

	typedef struct
	{
		//モーションの位置計算に運用、最後にMODELのDrawPosSに入れる
		D3DXVECTOR3 Pos;						//位置
		D3DXVECTOR3 Rot;						//向き
		int INDEX;								//自分の番号
		int PEARENT;							//自分の親

		D3DXMATRIX mtxWorld;					//ワールドマトリックス

		//はじめのTポーズ
		D3DXVECTOR3 StartPos;					//初めの位置
		D3DXVECTOR3 StartRot;					//初めの角度


		D3DXVECTOR3 CorrectCorrectionPosMove;	//モーションでの移動量pos
		D3DXVECTOR3 CorrectCorrectionRotMove;	//モーションでの移動量move
		bool calculationExecution;				//補正値計算したかbool
	
	}MODELPARTS;//現在のパーツのデータ

	typedef struct
	{
		int nMaxMotionCnt;						//最大モーション数
		int nMaxPartsCnt;						//最大パーツ数
		int nMaxLoadPartsCnt;					//読み込む最大パーツ数
		MOTION Motion[MAX_MOTION];				//五代モーションなど

	}MODEL;//モデル(という存在)

	//------------------------------------------------------------------------------------------------------------------------------

	CObjectMotion(int nPriority = CObject::LAYERINDEX_MOTIONMODEL);//コンストラクタ
	~CObjectMotion() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CObjectMotion* Create(const char* pfilePass,DATA SetData);//オブジェクト生成


	 void DataLoad();												//motion.txt読み込みとクリエイトを行う

	void SetFilePass(const char* FilePass);							//ファイルパス格納

	void Motion_Parent();											//motion本体
	void Motion_Sub();												//サブmotion

	void SetNowMotion_Parent(int nMotionNum);						//モーションセット
	void SetNowMotion_Sub(int nMotionNum);


	void SetClassData(DATA data);									//集合体と見てのDATA
	DATA GetClassData();											//集合体としてのDATA取得

	D3DXMATRIX GetMatrix();											//マトリックス取得
	void SetMatrix(D3DXMATRIX mtx);									//マトリックス格納

	void SetChangeDataInObjectMotion(DATA ChangeData);				//変更データをこのクラスを介してパーツにわたす
	
	CModelParts* GetModelParts(int index);							//パーツ取得
	
	int GetMaxLoadPartsNum();										//パーツ数取得

	int GetChangeDataPartsIndex();									//データ変更があるモデル番号取得(今回は砲塔)

	void SetOBBLength(float fLength[3]);							//OBBの大きさ入力

	COBB GetOBB();													//OBB取得

	int GetNowGRIDNum();											//GRID番号取得

	void HitCollisionToStageBlock();								//自機から障害物などへの当たり判定(player/enemy共通)

	D3DXVECTOR3 GetNowMove();										//このときのmove値取得

private:

	CMathProc::CollisionData m_HitData = {};						//当たり判定データ

	MODEL m_Model = {};												//モデルと言う存在

	const char* m_PartfilePass[MAX_PARTS] = {};						//各modelごとのpass

	LPD3DXMESH m_pMesh[MAX_PARTS] = {};								//Meshポインタ
	LPD3DXBUFFER m_pBuffMat[MAX_PARTS] = {};						//マテリアルへのポインタ
	DWORD m_dwNumMat[MAX_PARTS] = {};								//マテリアルの数
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_PARTS][MAX_TEXTURE] = {};		//テクスチャ

	DATA m_CrassData = {};											//一個体としてのデータ

	const char* m_FilePass=nullptr;									//motionのパス

	D3DXMATRIX m_mtxWorld = {};									    //マトリックス格納

	//motionで必要シリーズ-------------------------------
	int m_oldMotionIndex_Parent=0;		//前回のmotion
	int m_NowMotionIndex_Parent=0;		//今のmotion
	int m_NowKeyCnt_Parent=0;			//現在のmotionのキーCnt
	int m_NowFrameCnt_Parent=0;			//現在のmotionのフレームCnt
	int m_EscapeMotion_Parent=0;		//motionの退避用
	int m_BrendCnt_Parent=0;			//motionブレンド用Cnt
	bool m_MotionLoopStop_Parent=false;	//motionループを止めるかbool
	bool m_MotionBrend_Parent=false;	//motionブレンドをするかbool
	//----------------------------------------------------

	//motionで必要シリーズ------------------------------------------サブ
	int m_oldMotionIndex_Sub=0;			//前回のmotion
	int m_NowMotionIndex_Sub=0;			//今のmotion
	int m_NowKeyCnt_Sub=0;				//現在のmotionのキーCnt
	int m_NowFrameCnt_Sub=0;			//現在のmotionのフレームCnt
	int m_EscapeMotion_Sub=0;			//motionの退避用
	int m_BrendCnt_Sub=0;				//motionブレンド用Cnt
	bool m_MotionLoopStop_Sub=false;	//motionループを止めるかbool
	bool m_MotionBrend_Sub=false;		//motionブレンドをするかbool
	//---------------------------------------------------------------

	CModelParts* m_pModelParts[MAX_PARTS] = {};	//パーツ
	int m_ChangeDataModelIndex=0;				//データ変更のあるモデルのインデックス

	COBB m_Obb = {};							//OBBの当たり判定用

	int m_NowGridNum=0;							//現在の自分のいるGRIDの番号
	int m_RunCnt = 0;							//走行カウンタ
};

#endif