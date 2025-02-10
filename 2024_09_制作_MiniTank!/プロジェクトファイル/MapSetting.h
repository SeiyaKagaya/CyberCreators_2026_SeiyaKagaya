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
	static CScene* Create(MODE mode);//����

	void Input();//���͌n
	
	void HitDeleteCircle();//�폜�������蔻��(�Ȉ�)

private:
	int m_NowSetModelIndex;//�ݒu����^�C�v
};



#endif