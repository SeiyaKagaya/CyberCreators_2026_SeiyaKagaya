//=========================================================
//
// manager.cpp�Ŏg���֐�[manager.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MANAGER_H

#define _MANAGER_H//��d�C���N���[�h�h�~

//#include "main.h"
#include "renderer.h"

#include "input.h"
#include "all_texture.h"
#include "font.h"
#include "camera.h"
#include "light.h"

#include "scene.h"
#include "fade.h"
#include "score.h"
#include "sound.h"
#include "newbullet.h"

class CManager
{
private:
	CManager();//�R���X�g���N�^//�O�������s��
public:
	~CManager();//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	static CManager* GetInstance();
	static void SetMode(CScene::MODE mode);//�V�[���ݒ�

	CRenderer* GetRenderer();
	CInputKeyboard* GetKeyboard();
	CInputJoyPad* GetJoyPad();


	CCamera* GetCamera();
	CLight* GetLight();
	CScene* GetScene();
	CFade* GetFade();

	/*CNewBulletALL* GetNewBulletAll();
	void SetNewBulletAll(CNewBulletALL* GetNewBulletAll);*/

//	CScore* GetScore();

	static CAllTexture* GetTexture();
	
	//���͕����擾
	bool bGetInputState();

	void bSetInputState(bool InputState);

	void SetPauseState(bool Pause);
	bool GetPauseState();

	void SetStayState(bool Stay);
	bool GetStayState();


	void SetStayStatusState(bool Stay);
	bool GetStayStatusState();

	void SetEndStatusState(bool Stay);
	bool GetEndStatusState();



	CPause* GetPause();
	CStayUI* GetStayUI();
	CSound* GetSound();

//	CNewBullet* GetNewBullet();

	//3D���[�h���ǂ���
	void SetbNow3DMode(bool Set) { m_bNow3DMode = Set; };
	bool GetbNow3DMode() { return m_bNow3DMode; };

private:

	static CScene* m_pScene;//�V�[��

	CRenderer* m_pRenderer;//�����_���[
	CInputKeyboard* m_pKeyboard;
	CInputJoyPad* m_pjoyPad;

	static CAllTexture* m_allTexture;//�e�N�X�`���Ǘ�

	CFont* m_pFont;//�t�H���g�Ǘ�

	CCamera* m_pCamera;//�r���[���
	CLight* m_pLight;//���C�g���
	CFade* m_pFade;

	CPause* m_Pause;

	CStayUI* m_StayUI;

	CSound* m_Sound;

	//CNewBulletALL* m_NewBulletAll;

//	CNewBullet* m_NewBullet;

	//���̓^�C�vFalse�ŃL�[�}�E
	bool m_bInputState = true;

	bool m_bStopNow = false;

	bool m_bStaybool = false;
	

	//false�Ŕs��/true�ŏ���
	bool m_bStayStatus = false;

	//true�ŏ���
	bool m_EndState = false;

	bool m_bNow3DMode = false;//����3D���[�h��
};
#endif