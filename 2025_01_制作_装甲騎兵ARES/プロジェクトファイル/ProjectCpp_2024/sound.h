//=============================================================================
//
// サウンド処理 [sound.h]
// Author : SEIYA KAGAYA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

#include <xaudio2.h>

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// タイトルBGM
	SOUND_LABEL_BGM001,			// 戦闘BGM
	SOUND_LABEL_BGM002,			// ボスBGM
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
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
		SOUND_LABEL_BGM000 = 0,		// タイトルBGM
		SOUND_LABEL_BGM001,			// 戦闘BGM
		SOUND_LABEL_BGM002,			// ボス戦闘BGM
		SOUND_LABEL_SE_SHOT,		// 弾発射音
		SOUND_LABEL_SE_JET,		// ジェット通過
		SOUND_LABEL_SE_ENTER1,		// 選択１
		SOUND_LABEL_SE_ENTER2,		// 選択２
		SOUND_LABEL_SE_EXPLOSION,		// 爆発
		SOUND_LABEL_SE_SHOTFIRE,		// 発砲
		SOUND_LABEL_SE_RUN,		// 移動音
		SOUND_LABEL_SE_CURSOR,		//CURSOR
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
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
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

	// サウンドの情報
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"DATA/SOUND/BGM/tank_title_bgm_001.wav", -1},	 // タイトルBGM//-1がループ/0が一回きり
		{"DATA/SOUND/BGM/firstBattle000.wav", -1},	 // 通常戦闘BGM
		{"DATA/SOUND/BGM/BossBattle000.wav", -1},	 // ボス戦BGM
		{"DATA/SOUND/SE/Bullet002.wav", 0},		 // 弾発射音
		{"DATA/SOUND/SE/JET.wav", 0},			 // ジェット通過
		{"DATA/SOUND/SE/Enter001.wav", 0},		 // 選択１
		{"DATA/SOUND/SE/Enter002.wav", 0},		 // 選択２
		{"DATA/SOUND/SE/explosion000.wav", 0},	 //爆発
		{"DATA/SOUND/SE/ShotFire.wav", 0},		 //発砲
		{"DATA/SOUND/SE/running-tank-2.wav", 0}, //きゃらぴら
		{"DATA/SOUND/SE/cursor.wav", 0},		 //選択音
		
	};
};
#endif
