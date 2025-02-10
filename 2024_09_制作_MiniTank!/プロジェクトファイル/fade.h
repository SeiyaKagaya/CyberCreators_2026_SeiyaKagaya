//============================================================================================
//
//�t�F�[�h�Ɋւ���錾��\����[fade.h]
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

	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,//�������Ă��Ȃ����
		FADE_IN,	//�t�F�[�h�C�����
		FADE_OUT,	//�t�F�[�h�A�E�g���
		FADE_MAX

	}FADE;

	//�v���g�^�C�v�錾
	HRESULT Init(CScene::MODE ModeNext);
	void Uninit()override;
	void Update()override;
	void Draw()override;

	void SetFade(CScene::MODE ModeNext);//�t�F�[�h�J�n(���̃��[�h�i�[)

	FADE GetFade(void);//�t�F�[�h�擾

	//���_�i�[
	void InputpVtx()override;

private:
	FADE m_fade = {};
	CScene::MODE m_ModeNext = {};	//���̃��[�h
	float m_ColorA = 0.0f;			//�F�̃A���t�@�l
	int m_fadeCnt = 0;				//���[�h�ȍ~�J�E���^
	bool m_SetMode = false;			//���[�h�ݒ肵����
};
#endif