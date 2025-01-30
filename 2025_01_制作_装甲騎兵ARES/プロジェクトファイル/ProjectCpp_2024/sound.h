//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : SEIYA KAGAYA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

#include <xaudio2.h>

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �^�C�g��BGM
	SOUND_LABEL_BGM001,			// �퓬BGM
	SOUND_LABEL_BGM002,			// �{�XBGM
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// �^�C�g��BGM
		SOUND_LABEL_BGM001,			// �퓬BGM
		SOUND_LABEL_BGM002,			// �{�X�퓬BGM
		SOUND_LABEL_SE_SHOT,		// �e���ˉ�
		SOUND_LABEL_SE_JET,		// �W�F�b�g�ʉ�
		SOUND_LABEL_SE_ENTER1,		// �I���P
		SOUND_LABEL_SE_ENTER2,		// �I���Q
		SOUND_LABEL_SE_EXPLOSION,		// ����
		SOUND_LABEL_SE_SHOTFIRE,		// ���C
		SOUND_LABEL_SE_RUN,		// �ړ���
		SOUND_LABEL_SE_CURSOR,		//CURSOR
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDINFO;


	CSound();
	~CSound();

	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	
	static CSound* Create(HWND hWnd);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �T�E���h�̏��
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"DATA/SOUND/BGM/tank_title_bgm_001.wav", -1},	 // �^�C�g��BGM//-1�����[�v/0����񂫂�
		{"DATA/SOUND/BGM/firstBattle000.wav", -1},	 // �ʏ�퓬BGM
		{"DATA/SOUND/BGM/BossBattle000.wav", -1},	 // �{�X��BGM
		{"DATA/SOUND/SE/Bullet002.wav", 0},		 // �e���ˉ�
		{"DATA/SOUND/SE/JET.wav", 0},			 // �W�F�b�g�ʉ�
		{"DATA/SOUND/SE/Enter001.wav", 0},		 // �I���P
		{"DATA/SOUND/SE/Enter002.wav", 0},		 // �I���Q
		{"DATA/SOUND/SE/explosion000.wav", 0},	 //����
		{"DATA/SOUND/SE/ShotFire.wav", 0},		 //���C
		{"DATA/SOUND/SE/running-tank-2.wav", 0}, //�����҂�
		{"DATA/SOUND/SE/cursor.wav", 0},		 //�I����
		
	};
};
#endif
