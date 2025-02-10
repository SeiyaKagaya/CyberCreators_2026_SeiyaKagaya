//=========================================================
//
// manager.cpp�Ŏg���֐�[manager.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MANAGER_H
#define _MANAGER_H//��d�C���N���[�h�h�~

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

	//�e�n���擾�n
	CRenderer* GetRenderer();
	CInputKeyboard* GetKeyboard();
	CInputJoyPad* GetJoyPad();
	CCamera* GetCamera();
	CLight* GetLight();
	CScene* GetScene();
	CFade* GetFade();
	CNewBulletALL* GetNewBulletAll();
	void SetNewBulletAll(CNewBulletALL* GetNewBulletAll);
	CPause* GetPause();
	CStayUI* GetStayUI();
	CSound* GetSound();


	static CAllTexture* GetTexture();
	
	//���͕����擾
	bool bGetInputState();
	void bSetInputState(bool InputState);

	//�|�[�Y��
	void SetPauseState(bool Pause);
	bool GetPauseState();

	//�ҋ@��
	void SetStayState(bool Stay);
	bool GetStayState();

	//�X�e�[�g�̏�Ԋi�[
	void SetStayStatusState(bool Stay);
	bool GetStayStatusState();

	//�I����Ԃ��i�[
	void SetEndStatusState(bool Stay);
	bool GetEndStatusState();

private:

	static CScene* m_pScene;//�V�[��
	static CAllTexture* m_allTexture;//�e�N�X�`���Ǘ�

	CRenderer* m_pRenderer = nullptr;//�����_���[
	CInputKeyboard* m_pKeyboard = nullptr;
	CInputJoyPad* m_pjoyPad = nullptr;
	CFont* m_pFont = nullptr;//�t�H���g�Ǘ�
	CCamera* m_pCamera = nullptr;//�r���[���
	CLight* m_pLight = nullptr;//���C�g���
	CFade* m_pFade = nullptr;
	CPause* m_Pause = nullptr;
	CStayUI* m_StayUI = nullptr;
	CSound* m_Sound = nullptr;
	CNewBulletALL* m_NewBulletAll = nullptr;

	//���̓^�C�vFalse�ŃL�[�}�E
	bool m_bInputState = false;
	
	//��~��Ԃ�
	bool m_bStopNow = false;

	//�ҋ@��Ԃ�
	bool m_bStaybool = false;

	//false�Ŕs��/true�ŏ���
	bool m_bStayStatus = false;

	//true�ŏ���
	bool m_EndState = false;
};
#endif