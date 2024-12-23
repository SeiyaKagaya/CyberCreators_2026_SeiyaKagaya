//=========================================================
//
//���U���g��ʂŎg���ϐ��A�錾�A�\����[font.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _FONT_H_

#define _FONT_H_//��d�C���N���[�h�h�~

#include"main.h"
#include <d3d9.h>

class CFont
{
public:
	CFont();
	~CFont();

	// �t�H���g�̎��
		//--------------------�t�H���g�̃��x���I��
		typedef enum
	{
		FONT_DOKIDOKI = 0,//�ǂ��ǂ��t�@���^�W�A
		FONT_AKABARASINDELERA,//���K�N�V���f����
		FONT_KEIFONT,//�����ӂ����
		FONT_SOUKOUMINCHO,//���b����
		FONT_KIRARAJI04,//����玚04
		FONT_ONRYOU,//����t�H���g
		FONT_GENSIN,//���񂵂�
		FONT_DIGITAL,//DIGITAL
		FONT_MILITARY,
		FONT_GENKAI,
		FONT_MAX,
	}FONT;

		static const int MAXFONT = FONT_MAX;//---�t�H���g�̐�


		//�t�H���g�\����
		typedef struct
		{
			const char* pFilePass;	// �t�@�C���p�X
			const char* pFontName;	// �t�H���g�l�[��
		} FONTINFO;


		//�v���g�^�C�v�錾
		void InitText(void);
		void UninitText(void);
		//�e�L�X�g�����o������
		static void DrawTextSet(D3DXVECTOR3 DrawPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...);



		

private:

	static LPD3DXFONT m_pFont_Comment[MAXFONT];//�t�H���g�ւ̃|�C���^
	static LPD3DXFONT m_pFont_World[MAXFONT];//�t�H���g�ւ̃|�C���^

	// �t�H���g�̏��
//-------------------------------------------
//�@�@"�t�@�C���p�X","�t�H���g��"
//-------------------------------------------
	static FONTINFO m_FontInfo[FONT_MAX];
};






#endif // !_TEXT_H_