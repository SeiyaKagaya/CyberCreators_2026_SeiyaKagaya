//=========================================================
//
// time.cpp�Ŏg���֐�[time.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _TIME_H

#define _TIME_H//��d�C���N���[�h�h�~

#include "object.h"
#include "main.h"

#include <cstdio> // snprintf
#include <cstring> // memset


class CTime : public CObject
{
public:

	static const int MAXWORD_TIME = 1000;


	CTime(int nPriority = CObject::LAYERINDEX_TIME);
	~CTime() override;//�f�X�g���N�^


	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	static void AddTime();

	static CTime* Create();//�I�u�W�F�N�g����

	static int GetTime();
private:
	char m_cData[MAXWORD_TIME];

	DATA m_Data;
	static int m_LimitTime;
	static int m_flame;
	int m_StartLimitTime;//��Ɏg�p
};

#endif