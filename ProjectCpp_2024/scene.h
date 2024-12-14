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
	static CScene* Create(MODE mode);//����


	static MODE GetNowScene();

	static void SetNowScene(MODE SetScene);

	static void SetStageClear(bool bSet);
	static bool GetStageClear();



private:
	static  MODE m_NowState;
	static bool m_bStageClear;
	//static bool m_bNow3DMode;//����3D���[�h��


	MODE m_Mode;	//���݂̃��[�h


protected:

	CPause* m_Pause;

	CStayUI* m_StayUI;

	CGameUI* m_CGameUI;

	CTextWindow* m_CTextWindow;

	int m_StayTime = STAYFRAME;//�Q�[���I����UI�ł�܂őҋ@

	bool m_StayPush = false;//�{�^�����͑ҋ@

	int m_Stay2 = STAYFRAME2;//�኱�L�΂��I������

	bool m_bStay2BOOL = false;//�I�����኱�L�΂�

	bool m_bNext = false;//���ɂ����߂邩

	//�{�^���_�Ŋ֌W
	int m_nbuttonCnt=0;
	bool m_bButtonBool = false;

	bool m_bSetTextWindow=false;//�e�L�X�g�E�B���h�E���`�悳��Ă�����
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