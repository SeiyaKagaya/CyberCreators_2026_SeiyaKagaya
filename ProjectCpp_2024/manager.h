//=========================================================
//
// manager.cppで使う関数[manager.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MANAGER_H

#define _MANAGER_H//二重インクルード防止

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
	CManager();//コンストラクタ//外部生成不可に
public:
	~CManager();//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit();
	void Update();
	void Draw();

	static CManager* GetInstance();
	static void SetMode(CScene::MODE mode);//シーン設定

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
	
	//入力方式取得
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

	//3Dモードかどうか
	void SetbNow3DMode(bool Set) { m_bNow3DMode = Set; };
	bool GetbNow3DMode() { return m_bNow3DMode; };

private:

	static CScene* m_pScene;//シーン

	CRenderer* m_pRenderer;//レンダラー
	CInputKeyboard* m_pKeyboard;
	CInputJoyPad* m_pjoyPad;

	static CAllTexture* m_allTexture;//テクスチャ管理

	CFont* m_pFont;//フォント管理

	CCamera* m_pCamera;//ビュー情報
	CLight* m_pLight;//ライト情報
	CFade* m_pFade;

	CPause* m_Pause;

	CStayUI* m_StayUI;

	CSound* m_Sound;

	//CNewBulletALL* m_NewBulletAll;

//	CNewBullet* m_NewBullet;

	//入力タイプFalseでキーマウ
	bool m_bInputState = true;

	bool m_bStopNow = false;

	bool m_bStaybool = false;
	

	//falseで敗退/trueで勝利
	bool m_bStayStatus = false;

	//trueで勝利
	bool m_EndState = false;

	bool m_bNow3DMode = false;//現在3Dモードか
};
#endif