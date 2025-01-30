//=========================================================
//
// scene.cpp�Ŏg���֐�[scene.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SCENE_H

#define _SCENE_H//��d�C���N���[�h�h�~

#include "main.h"

//#include <Windows.h>
//#include "d3dx9.h"//�`�ʏ����Ɏg��


//Obstacle�̒��ɂ��ꂠ��BRelease��������
//[DIK_F3]-->�z�u���Z�[�u
//[DIK_F6]-->�o�H�}�b�s���O

#include "pause.h"

#include "Tutorial.h"
#include "GameStayUI.h"

#include "Game_UI.h"
#include "textwindow.h"
#include "LongPush.h"

class CScene
{
public:
	static const int STAYFRAME = 90;
	static const int STAYFRAME2 = 45;//���E���኱�L�΂�
	static const int BUTTONCNT = 100;
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_GAME2,
		MODE_GAME3,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_OP,
		MODE_MOVIE,
		MODE_MOVIE2,
		MODE_MAX,
	}MODE;

	CScene();
	virtual ~CScene();

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CScene* Create(MODE mode);//����


	static MODE GetNowScene();

	static void SetNowScene(MODE SetScene);

	static void SetStageClear(bool bSet);
	static bool GetStageClear();


	static void SetStayNextStage(bool bSet) { m_bNextStageStay = bSet; };
	static bool GetStayNextStage() {return m_bNextStageStay;};
	static void AddClearNum(int nNum) { m_ClearNum += nNum; };
	static void ResetClearNum() { m_ClearNum = 0; };
	static int GetClearNum() { return m_ClearNum; };

private:
	static  MODE m_NowState;
	static bool m_bStageClear;
	static bool m_bNextStageStay;

	static int m_ClearNum;
	//static bool m_bNow3DMode;//����3D���[�h��


	MODE m_Mode;	//���݂̃��[�h


protected:

	CPause* m_Pause;

	CStayUI* m_StayUI;

	CGameUI* m_CGameUI;

	CTextWindow* m_CTextWindow;
	CTextWindow* m_CTextWindowSub;
	CLongPush* m_pLongPush;

	int m_StayTime = STAYFRAME;//�Q�[���I����UI�ł�܂őҋ@

	bool m_StayPush = false;//�{�^�����͑ҋ@

	int m_Stay2 = STAYFRAME2;//�኱�L�΂��I������

	bool m_bStay2BOOL = false;//�I�����኱�L�΂�

	bool m_bNext = false;//���ɂ����߂邩

	//�{�^���_�Ŋ֌W
	int m_nbuttonCnt=0;
	bool m_bButtonBool = false;

	//bool m_bSetTextWindow=false;//�e�L�X�g�E�B���h�E���`�悳��Ă�����

	int m_nCnt = 0;



};












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

	CTutorialUI* m_TutorialUI;

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


class CGame:public CScene
{
public:
	CGame();
	~CGame() override; 

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

private:
//	bool m_bNextStay = false;
	int m_nCnt = 0;

	bool m_bTextSet[3] = { false,false,false };		//�e�L�X�g��`��J�n��
	bool m_bTextSetEnd[3] = { false,false,false };	//�e�L�X�g�`��ς݂�
	int m_nTextEndCnt = 0;
};

class CMovie :public CScene
{

public:
	CMovie();
	~CMovie() override;

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

	int m_nTextEndCnt = 0;
};


class CMovie2 :public CScene
{

public:
	CMovie2();
	~CMovie2() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

};

//
class CGame3 :public CScene
{
public:
	CGame3();
	~CGame3() override;

	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

private:
	//void* m_EnemyBoss[3];


};
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




#endif