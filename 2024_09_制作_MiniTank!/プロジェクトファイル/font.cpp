//============================================================================================
//
//�e�L�X�g�\�����鏈��[font.cpp]
// Author seiya kagaya
//
//============================================================================================
#include <stdarg.h>  // �ϒ������֘A�̃w�b�_
#include "font.h"
#include <stdio.h>
#include "renderer.h"
#include "manager.h"

LPD3DXFONT CFont::m_pFont_Comment[MAXFONT] = {};//�t�H���g�ւ̃|�C���^
LPD3DXFONT CFont::m_pFont_World[MAXFONT] = {};//�t�H���g�ւ̃|�C���^

// �t�H���g�̏��
//-------------------------------------------
//�@�@"�t�@�C���p�X","�t�H���g��"
//-------------------------------------------
// �t�H���g�̏��
CFont::FONTINFO CFont::m_FontInfo[CFont::FONT_MAX] = 
{
	{"DATA\\FONT\\DokiDokiFantasia.otf", "�ǂ��ǂ��t�@���^�W�A"},
	{"DATA\\FONT\\akabara-cinderella.ttf", "���K�N�V���f����"},
	{"DATA\\FONT\\keifont.ttf", "�����ӂ����"},
	{"DATA\\FONT\\SoukouMincho.ttf", "���b����"},
	{"DATA\\FONT\\kiraraji04.ttf", "����玚04"},
	{"DATA\\FONT\\onryou.TTF", "����"},
	{"DATA\\FONT\\ZH-CN.TTF", "SDK_SC_Web Heavy"},
	{"DATA\\FONT\\DS-DIGI.TTF", "DS-Digital"},
	{"DATA\\FONT\\rycsminStencily.ttf", "�������������X�e���V����"},
	{"DATA\\FONT\\genkai-mincho.ttf", "���E����"},
	
	
};

//=============================
//�R���X�g���N�^
//=============================
CFont::CFont()
{
}
//=============================
//�f�X�g���N�^
//=============================
CFont::~CFont()
{
}

//=============================
//����������
//=============================
void CFont::InitText(void)
{
	UninitText();

	//�t�H���g�̓ǂݍ��݃e�X�g//
	for (int i = 0; i < FONT_MAX; i++)
	{
		LPCSTR font_path = m_FontInfo[i].pFilePass; // �����Ŋe�t�H���g���g�p�\��

		if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
		{
		}
		else
		{
			// �t�H���g�Ǎ��G���[����
			MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
		}
	}
}
//=============================
//�I������
//=============================
void CFont::UninitText(void)
{
	for (int i = 0; i < MAXFONT; i++)
	{
		//UIComment�\���p�t�H���g�̔j��
		if (m_pFont_Comment[i] != nullptr)
		{
			m_pFont_Comment[i]->Release();
			m_pFont_Comment[i] = nullptr;
		}
		//UIComment�\���p�t�H���g�̔j��
		if (m_pFont_World[i] != nullptr)
		{
			m_pFont_World[i]->Release();
			m_pFont_World[i] = nullptr;
		}
	}
}
//=============================
//UI�R�����g�\������
//=============================
void CFont::DrawTextSet(D3DXVECTOR3 DrawPos, int FontSize, FONT Font, D3DXCOLOR RGBA, const char* Text, ...)
{//...�͉ϒ������iVariable Arguments�j
	
	 //�������厖
	if (m_pFont_Comment[Font] != nullptr)
	{
		m_pFont_Comment[Font]->Release();
		m_pFont_Comment[Font] = nullptr;
	}

	CRenderer* pRenderer = nullptr;

	CManager* pManager = CManager::GetInstance();

	pRenderer = pManager->GetRenderer();


	LPDIRECT3DDEVICE9 EscDevice = pRenderer->GetDevice();

	// RECT�̍��W��LONG�ɃL���X�g
	RECT rect = { static_cast<LONG>(DrawPos.x), static_cast<LONG>(DrawPos.y), SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[1024];

	D3DXCreateFont(EscDevice, FontSize, 0, FW_HEAVY, 1,
		FALSE,
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		TEXT(m_FontInfo[Font].pFontName),//--�ǂݍ��񂾃t�H���g�̖��O(�v���p�e�B�̃^�C�g���ŕ�����)
		&m_pFont_Comment[Font]);

	//D3DXCreateFont�̈����̈Ӗ�

	//D3DXCreateFont(EscDevice,                /* �f�o�C�X */
	//	16,                            /* �����̍��� */
	//	0,                            /* ������ */
	//	FW_NORMAL,                    /* �t�H���g�̑��� */
	//	1,                            /* MIPMAP�̃��x�� */
	//	FALSE,                        /* �C�^���b�N���H */
	//	DEFAULT_CHARSET,            /* �����Z�b�g */
	//	OUT_DEFAULT_PRECIS,            /* �o�͐��x */
	//	DEFAULT_QUALITY,            /* �o�͕i�� */
	//	DEFAULT_PITCH | FF_SWISS,    /* �t�H���g�s�b�`�ƃt�@�~�� */
	//	L"�l�r �o�S�V�b�N",                    /* �t�H���g�� */
	//	&lpFont)         /* Direct3D�t�H���g�ւ̃|�C���^�ւ̃A�h���X */




	// �ϒ������̏���-------
	va_list args;				 //�ϒ������̈������X�g���w�肷��
	va_start(args, Text);		 //va_list ��������--��//�ϒ������̈�O�̈������w��
	vsprintf_s(aStr, Text, args);//�����w�蕶������g�p���ĉϒ��������當����𐶐����邽�߂̈��S�Ȋ֐�
	va_end(args);				 //va_start �}�N���ɂ���ĊJ�n���ꂽ�ϒ��������X�g���I�����邽�߂Ɏg�p

	// �e�L�X�g�̕`��
	m_pFont_Comment[Font]->DrawText(NULL, aStr, -1, &rect, DT_LEFT/* | DT_WORDBREAK*/, RGBA);



	//�g�p��I�I

	//	DrawTextSet(�@���W�@, �t�H���g�T�C�Y�@, �t�H���g���i��.�ō�������x���I�ȁj, �J���[, "�ł���������(�C�ӂ�%d.%f,%s)",(�C�ӂŕϐ�));
}
