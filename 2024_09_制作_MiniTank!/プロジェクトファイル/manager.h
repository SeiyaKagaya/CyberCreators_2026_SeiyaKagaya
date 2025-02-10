//=========================================================
//
// manager.cppで使う関数[manager.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MANAGER_H
#define _MANAGER_H//二重インクルード防止

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

	//各系統取得系
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
	
	//入力方式取得
	bool bGetInputState();
	void bSetInputState(bool InputState);

	//ポーズか
	void SetPauseState(bool Pause);
	bool GetPauseState();

	//待機か
	void SetStayState(bool Stay);
	bool GetStayState();

	//ステートの状態格納
	void SetStayStatusState(bool Stay);
	bool GetStayStatusState();

	//終了状態か格納
	void SetEndStatusState(bool Stay);
	bool GetEndStatusState();

private:

	static CScene* m_pScene;//シーン
	static CAllTexture* m_allTexture;//テクスチャ管理

	CRenderer* m_pRenderer = nullptr;//レンダラー
	CInputKeyboard* m_pKeyboard = nullptr;
	CInputJoyPad* m_pjoyPad = nullptr;
	CFont* m_pFont = nullptr;//フォント管理
	CCamera* m_pCamera = nullptr;//ビュー情報
	CLight* m_pLight = nullptr;//ライト情報
	CFade* m_pFade = nullptr;
	CPause* m_Pause = nullptr;
	CStayUI* m_StayUI = nullptr;
	CSound* m_Sound = nullptr;
	CNewBulletALL* m_NewBulletAll = nullptr;

	//入力タイプFalseでキーマウ
	bool m_bInputState = false;
	
	//停止状態か
	bool m_bStopNow = false;

	//待機状態か
	bool m_bStaybool = false;

	//falseで敗退/trueで勝利
	bool m_bStayStatus = false;

	//trueで勝利
	bool m_EndState = false;
};
#endif