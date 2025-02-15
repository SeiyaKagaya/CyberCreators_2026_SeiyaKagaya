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

	static const int MAXWORD_TIME = 1000;//�ő啶����

	CTime(int nPriority = CObject::LAYERINDEX_TIME);
	~CTime() override;//�f�X�g���N�^
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	static void AddTime();	//�^�C���i�s
	static CTime* Create(); //�I�u�W�F�N�g����
	static int GetTime();	//�^�C���擾

private:

	static int m_LimitTime;
	static int m_flame;
	char m_cData[MAXWORD_TIME] = {};//������i�[
	DATA m_Data = DataInit();
	int m_StartLimitTime = 0;//��Ɏg�p
};

#endif