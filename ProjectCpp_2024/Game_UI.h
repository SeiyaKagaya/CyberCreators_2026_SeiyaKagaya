//=========================================================
//
// Game_UI.cppで使う関数[Game_UI.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _GAMEUI_H

#define _GAMEUI_H//二重インクルード防止

#include "object.h"
#include "d3dx9.h"//描写処理に使う
#include "main.h"

#include "object.h"

//
class CGameUI : public CObject
{
public:

	typedef enum
	{
		UI_NOMAL=0,
		UI_NOMAL2,
		UI_MAP_BACK,
		UI_MAP,

		UI_WEPON1_BACK,//一番初めに起動/
		UI_WEPON1,
		UI_LOAD_GAUGE_BACK_WEPON,
		UI_LOAD_GAUGE_WEPON,

		UI_WEPON2_BACK,//一番初めに起動/
		UI_WEPON2,
		UI_LOAD_GAUGE_BACK_WEPON2,
		UI_LOAD_GAUGE_WEPON2,

		UI_WEPON3_BACK,//一番初めに起動/
		UI_WEPON3,
		UI_LOAD_GAUGE_BACK_WEPON3,
		UI_LOAD_GAUGE_WEPON3,
		UI_LOAD_GAUGE_WEPON3_2,

		UI_ACTION,
		UI_PLAYERPIN,

		UI_TEXTWINDOW,
		UI_TEXTIMAGE,

		UI_HP_BACK,
		UI_HP_MAIN,

		UI_BOOST_BACK,
		UI_BOOST_MAIN,

		UI_MAX,
	}UITYPE;


	typedef enum
	{
		UISTATE_OFFLINE_TRIGGER,
		UISTATE_OFFLINE_NOW,
		UISTATE_ONLINE_TRIGGER,
		UISTATE_ONLINE_NOW,
	}UISTATE;


	static const int TEXNUM = 7;
	static const int MAXFRAME = 60;
	
	static const int BACKGROUND_A = 155;
	static const int BACKGROUND_B = 250;

	static const int PHASE1RAME = 10;
	static const int DELAYRAME1 = 4;
	static const int PHASE2RAME = 30;
	static const int PHASE3RAME = 50;
	static const int PHASE4RAME = 15;

	static const int DELAY_UI_TO_UI =10;//UI起動時ラグ


	CGameUI(int nPriority = CObject::LAYERINDEX_GAMEUI);//コンストラクタ
	~CGameUI() override;//デストラクタ
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static CGameUI* Create();//object生成

	void InputpVtx();

	//UIの状態格納
	void SetStateChangeUi(bool bSet ,UITYPE Uitype);//　UI_Weponなど直接指名(枠とゲージはないないでやる)

	//UIのモーション
	void OnlineTrigger(int nCnt);
	void OfflineTrigger(int nCnt);

	void UIDrawReset(int nCnt);//描画を一からにx

	void AllUiRestart();//全UIRestart開始
	bool GetAllUiRestartNow();//Restart中かどうか

	//体力バー変動
	void SetLifeBar(int nCnt);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff[UI_MAX];//頂点バッファ
	
	int m_nTexIdx[UI_MAX];

	LPDIRECT3DTEXTURE9 m_pTexture[UI_MAX];
	
	int m_MapNum = 0;

	//タイプ格納
	UITYPE m_UiType[UI_MAX];

	UISTATE m_UiState[UI_MAX];

	D3DXVECTOR3 m_Pos[UI_MAX];
	D3DXVECTOR3 m_Size[UI_MAX];

	int m_nMotionCnt[UI_MAX];//モーション初め

	int m_nMotionDelayCnt[UI_MAX];//遅れて追走

	int m_nMotionDalay[UI_MAX];

	float m_fLength[UI_MAX];//ゲージのみの利用

	int m_nWeponUIDrawA[UI_MAX];//武器用UIのアルファ値

	bool m_bFirst[UI_MAX];

	bool m_bNowRestart = false;
	int m_NowUiCount = 0;//現在のUI階層
	int m_NowUiFrameCnt = 0;//現在のカウント

};

#endif