//=========================================================
//
// scene.cppで使う関数[scene.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SCENE_H
#define _SCENE_H//二重インクルード防止

#include "main.h"
#include "pause.h"
#include "Tutorial.h"
#include "GameStayUI.h"

class CScene
{
public:
	static const int STAYFRAME = 90; //何等かに使う待機フレーム
	static const int STAYFRAME2 = 70;
	static const int BUTTONCNT = 100;//ボタン表示までの待機フレーム

	//シーンの種類
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_GAME2,
		MODE_GAME3,
		MODE_GAME4,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_MAX,
	}MODE;

	CScene();//コンストラクタ
	virtual ~CScene();//デストラクタ

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CScene* Create(MODE mode);//生成

	static MODE GetNowScene();			    //現在のシーンの種類を取得
	static void SetNowScene(MODE SetScene); //シーンをセット

	static void SetStageClear(bool bSet);   //ステージクリア判定か格納
	static bool GetStageClear();		    //ステージクリアかどうか取得

private:
	static  MODE m_NowState;	//現在のモード
	static bool m_bStageClear;	//ステージクリアかbool

protected:

	CPause* m_Pause = nullptr;		//ポーズ
	CStayUI* m_StayUI = nullptr;	//待機UI

	int m_StayTime = STAYFRAME;		//待機時間
	int m_Stay2 = STAYFRAME2;		//待機時間2
	int m_nbuttonCnt = 0;			//ボタン表示までのフレーム数
	bool m_StayPush = false;		//待機ボタン押したか
	bool m_bStay2BOOL = false;		//待機状態か
	bool m_bNext = false;			//次のステージに進めるか
	bool m_bButtonBool = false;		//ボタンを押したか
};

//++++++++++++++++++++++
// ゲーム1
//++++++++++++++++++++++
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

//++++++++++++++++++++++
// ゲーム2
//++++++++++++++++++++++
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

//++++++++++++++++++++++
// ゲーム3
//++++++++++++++++++++++
class CGame3 :public CScene
{
public:
	CGame3();
	~CGame3() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

//++++++++++++++++++++++
// ゲーム4
//++++++++++++++++++++++
class CGame4 :public CScene
{
public:
	CGame4();
	~CGame4() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};

//++++++++++++++++++++++
// タイトル
//++++++++++++++++++++++
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

//++++++++++++++++++++++
// リザルト
//++++++++++++++++++++++
class CResult :public CScene
{
public:
	CResult();
	~CResult() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void ScoreLoad();	//スコア読み込み
	void ScoreWrite();	//スコア描画

private:
	int m_ScoreNum[6];	//スコア一覧
	int m_NUM = 0;		//今回のスコア

};

//++++++++++++++++++++++
// チュートリアル
//++++++++++++++++++++++
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

	CTutorialUI * m_TutorialUI = nullptr; //チュートリアルUI
};
#endif