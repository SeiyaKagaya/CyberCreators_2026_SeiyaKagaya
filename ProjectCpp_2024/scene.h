//=========================================================
//
// scene.cppで使う関数[scene.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SCENE_H

#define _SCENE_H//二重インクルード防止

#include "main.h"

//#include <Windows.h>
//#include "d3dx9.h"//描写処理に使う


//Obstacleの中にこれある。Release時無効化
//[DIK_F3]-->配置物セーブ
//[DIK_F6]-->経路マッピング

#include "pause.h"

#include "Tutorial.h"
#include "GameStayUI.h"

#include "Game_UI.h"
#include "textwindow.h"

class CScene
{
public:
	static const int STAYFRAME = 90;
	static const int STAYFRAME2 = 45;//世界を若干伸ばす
	static const int BUTTONCNT = 100;
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_GAME2,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_OP,
		MODE_MAX,
	}MODE;

	CScene();
	virtual ~CScene();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CScene* Create(MODE mode);//生成


	static MODE GetNowScene();

	static void SetNowScene(MODE SetScene);

	static void SetStageClear(bool bSet);
	static bool GetStageClear();



private:
	static  MODE m_NowState;
	static bool m_bStageClear;
	//static bool m_bNow3DMode;//現在3Dモードか


	MODE m_Mode;	//現在のモード


protected:

	CPause* m_Pause;

	CStayUI* m_StayUI;

	CGameUI* m_CGameUI;

	CTextWindow* m_CTextWindow;

	int m_StayTime = STAYFRAME;//ゲーム終了後UIでるまで待機

	bool m_StayPush = false;//ボタン入力待機

	int m_Stay2 = STAYFRAME2;//若干伸ばす終了時間

	bool m_bStay2BOOL = false;//終了を若干伸ばす

	bool m_bNext = false;//次にすすめるか

	//ボタン点滅関係
	int m_nbuttonCnt=0;
	bool m_bButtonBool = false;

	bool m_bSetTextWindow=false;//テキストウィンドウが描画されていたか
};


class CGame:public CScene
{
public:
	CGame();
	~CGame() override; 

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

class CGame2 :public CScene
{
public:
	CGame2();
	~CGame2() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
//
//class CGame3 :public CScene
//{
//public:
//	CGame3();
//	~CGame3() override;
//
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//};
//
//class CGame4 :public CScene
//{
//public:
//	CGame4();
//	~CGame4() override;
//
//	HRESULT Init()override;
//	void Uninit()override;
//	void Update()override;
//	void Draw()override;
//};








class CTitle :public CScene
{
public:
	CTitle();
	~CTitle() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};


class CResult :public CScene
{
public:
	CResult();
	~CResult() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void ScoreLoad();
	void ScoreWrite();

private:
	int m_ScoreNum[6];
	int m_NUM = 0;

};

class CTutorial :public CScene
{

public:
	CTutorial();
	~CTutorial() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;



private:

	CTutorialUI * m_TutorialUI;

};


class COP :public CScene
{

public:
	COP();
	~COP() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;




};
#endif