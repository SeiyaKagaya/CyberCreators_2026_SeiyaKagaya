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

class CScene
{
public:

	typedef enum
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX,
	}MODE;

	CScene();
	 ~CScene();

	 HRESULT Init();
	 void Uninit();
	 void Update();
	 void Draw();
	static CScene* Create(MODE mode);//生成

	void Input();//入力系
	
	void HitDeleteCircle();//削除時当たり判定(簡易)

private:
	int m_NowSetModelIndex;//設置するタイプ
};



#endif