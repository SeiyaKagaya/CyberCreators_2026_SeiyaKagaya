//=========================================================
//
// scene.cpp�Ŏg���֐�[scene.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _SCENE_H
#define _SCENE_H//��d�C���N���[�h�h�~

#include "main.h"
#include "pause.h"
#include "Tutorial.h"
#include "GameStayUI.h"

class CScene
{
public:
	static const int STAYFRAME = 90; //�������Ɏg���ҋ@�t���[��
	static const int STAYFRAME2 = 70;
	static const int BUTTONCNT = 100;//�{�^���\���܂ł̑ҋ@�t���[��

	//�V�[���̎��
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

	CScene();//�R���X�g���N�^
	virtual ~CScene();//�f�X�g���N�^

	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CScene* Create(MODE mode);//����

	static MODE GetNowScene();			    //���݂̃V�[���̎�ނ��擾
	static void SetNowScene(MODE SetScene); //�V�[�����Z�b�g

	static void SetStageClear(bool bSet);   //�X�e�[�W�N���A���肩�i�[
	static bool GetStageClear();		    //�X�e�[�W�N���A���ǂ����擾

private:
	static  MODE m_NowState;	//���݂̃��[�h
	static bool m_bStageClear;	//�X�e�[�W�N���A��bool

protected:

	CPause* m_Pause = nullptr;		//�|�[�Y
	CStayUI* m_StayUI = nullptr;	//�ҋ@UI

	int m_StayTime = STAYFRAME;		//�ҋ@����
	int m_Stay2 = STAYFRAME2;		//�ҋ@����2
	int m_nbuttonCnt = 0;			//�{�^���\���܂ł̃t���[����
	bool m_StayPush = false;		//�ҋ@�{�^����������
	bool m_bStay2BOOL = false;		//�ҋ@��Ԃ�
	bool m_bNext = false;			//���̃X�e�[�W�ɐi�߂邩
	bool m_bButtonBool = false;		//�{�^������������
};

//++++++++++++++++++++++
// �Q�[��1
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
// �Q�[��2
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
// �Q�[��3
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
// �Q�[��4
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
// �^�C�g��
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
// ���U���g
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

	void ScoreLoad();	//�X�R�A�ǂݍ���
	void ScoreWrite();	//�X�R�A�`��

private:
	int m_ScoreNum[6];	//�X�R�A�ꗗ
	int m_NUM = 0;		//����̃X�R�A

};

//++++++++++++++++++++++
// �`���[�g���A��
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

	CTutorialUI * m_TutorialUI = nullptr; //�`���[�g���A��UI
};
#endif