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

	void SetFade(CScene::MODE ModeNext);

	FADE GetFade(void);

	//���_�i�[
	void InputpVtx()override;

private:
	int m_nTime;//���������K�v
	FADE m_fade;
	CScene::MODE m_ModeNext;//���̃��[�h
	float m_ColorA;
	int m_fadeCnt;//�Ƃ肠����

	bool m_SetMode;//���[�h�ݒ肵����

	//���܂������Ȃ������Ƃ��p
	LPDIRECT3DTEXTURE9 m_pTexture2;//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff2;//���_�o�b�t�@
	//�e�N�X�`���Ⓒ�_���W�Ȃǂ̕ێ�
	VERTEX_2D m_pVtx2[BASE_INDEX];


	bool bBulletSet = false;
};




#endif