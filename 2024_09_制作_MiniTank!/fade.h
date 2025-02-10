//============================================================================================
//
//フェードに関する宣言や構造体[fade.h]
// Author seiya kagaya
//
//============================================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "object2D.h"
#include "scene.h"

class CFade:public CObject2D
{
public:
	CFade(int nPriority = CObject::LAYERINDEX_FADE);
	~CFade();

	//フェードの状態
	typedef enum
	{
		FADE_NONE = 0,//何もしていない状態
		FADE_IN,	//フェードイン状態
		FADE_OUT,	//フェードアウト状態
		FADE_MAX

	}FADE;

	//プロトタイプ宣言
	HRESULT Init(CScene::MODE ModeNext);
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetFade(CScene::MODE ModeNext);//フェード開始(次のモード格納)

	FADE GetFade(void);//フェード取得

	//頂点格納
	void InputpVtx()override;

private:
	FADE m_fade = {};
	CScene::MODE m_ModeNext = {};	//次のモード
	float m_ColorA = 0.0f;			//色のアルファ値
	int m_fadeCnt = 0;				//モード以降カウンタ
	bool m_SetMode = false;			//モード設定したか
};
#endif