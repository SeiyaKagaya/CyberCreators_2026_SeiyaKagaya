//=======================================================
//
//object�Ɋւ��鏈��[object.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "object.h"

int CObject::m_nNumAll = 0;

//CObject* CObject::m_apObject[CObject::LAYERINDEX_MAX][CObject::MAX_OBJECT] = {};

CObject* CObject::m_pTop[CObject::LAYERINDEX_MAX] = {};//�ŏ�
CObject* CObject::m_pCur[CObject::LAYERINDEX_MAX] = {};//�Ō�

CObject* CObject::m_pLastCreatedObject[CObject::LAYERINDEX_MAX] = {};//�Ō�ɍ��������

//=============================
//�R���X�g���N�^(�������g�̓o�^)
//=============================
CObject::CObject(int nPriority): m_nPriority(nPriority), m_pPrev(nullptr), m_pNext(nullptr),m_bDeath(false)
{
	m_bDeath = false;

	
	if (m_pTop[m_nPriority]==nullptr)
	{//���܂̃v���C�I���e�B�̐擪�����Ȃ��Ƃ�
		m_pTop[m_nPriority] = this;//�擪�������
		m_pPrev = nullptr;//�O�͑��݂��Ȃ�
	}
	else
	{//�O�͑��݂���
		m_pPrev = m_pLastCreatedObject[m_nPriority];//�O��Ō�ɐ�������ONJECT�ɐݒ�
		m_pPrev->m_pNext = this;//�Ō�ɐ�������OBJECT��NEXT�����g�ɐݒ�
	}
	//�Ō��̂��ߎ��͂��Ȃ�
	m_pNext = nullptr;

	m_nID = m_nNumAll;

	m_nNumAll++; // �����C���N�������g



	//�Ō�ɐ�������OBJECT���X�V
	m_pLastCreatedObject[m_nPriority] = this;
}
//=============================
//	�f�X�g���N�^
//=============================
CObject::~CObject()
{
}

//=============================
//	�S�I�u�W�F�N�g�J��
//=============================
void CObject::ReleaseAll()
{
	for (int nCnt2 = 0; nCnt2 < LAYERINDEX_MAX; nCnt2++)
	{
		CObject* pObj = m_pTop[nCnt2];//�擪�擾
		
		if (m_pTop[nCnt2] != nullptr)
		{//�擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�
		
		 //�ő吔�s���̂���while
			while (pObj != nullptr)
			{
				CObject* pNext = pObj->m_pNext;
				if (pObj->m_ObjectType != OBJECT_FADE)
				{
					pObj->m_bDeath = true;//�t���O���Ă�
					pObj->Release();//�J��
				}
				pObj = pNext;

			}
		}
	}
}
//=============================
//	�S�I�u�W�F�N�g�X�V
//=============================
void CObject::UpdateAll()
{
	for (int nCnt2 = 0; nCnt2 < LAYERINDEX_MAX; nCnt2++)
	{
		CObject* pObj = m_pTop[nCnt2];//�擪�擾
		//�ő吔�s���̂���while
	
		if (m_pTop[nCnt2] != nullptr)
		{//�擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�
			while (pObj != nullptr)
			{
				CObject* pNext = pObj->m_pNext;

				if (pObj->GetDeathNow() == false)
				{//���S���肶��Ȃ���

					if (nCnt2 == LAYERINDEX_BULLET3D)
					{
						int Test= pObj->GetNum();
					}
					pObj->Update();
				}
				pObj = pNext;
			}
		}
	}

	DelayDeath();//�x�点�������[�X��������

}
//=============================
//	�S�I�u�W�F�N�g�`��
//=============================
void CObject::DrawAll()
{
	for (int nCnt2 = 0; nCnt2 < LAYERINDEX_MAX; nCnt2++)
	{
		if (m_pTop[nCnt2] != nullptr)
		{
			CObject* pObj = m_pTop[nCnt2];//�擪�擾
			
			if (nCnt2 == (int)LAYERINDEX_LINE)
			{
				int test = 0;
			}
			if (m_pTop[nCnt2] != nullptr)
			{//�擪���Ȃ�==�v���C�I���e�B�܂���ƂȂ�

				//�ő吔�s���̂���while
				while (pObj != nullptr)
				{
					CObject* pNext = pObj->m_pNext;
					pObj->Draw();
					pObj = pNext;
				}
			}
		}
	}
}
//=============================
//	�x���J��
//=============================
void CObject::DelayDeath()
{
	for (int nCnt2 = 0; nCnt2 < LAYERINDEX_MAX; nCnt2++)
	{
		CObject* pObj = m_pTop[nCnt2];

		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;

			if (pObj->m_bDeath == true)
			{
				pObj->Release();
			}

			pObj = pNext;
		}
	}
}
//=============================
//	�G�����擾
//=============================
int CObject::GetnNumAll()
{
	return m_nNumAll;
}
//=============================
//	object�̃|�C���^���擾
//=============================
CObject* CObject::GetObjectPoint(int nPriority, OBJECTTYPE ObjectType)
{

	CObject* pObj = m_pTop[nPriority];//�擪�擾

	//�ő吔�s���̂���while
	while (pObj != nullptr)
	{
		CObject* pNext = pObj->m_pNext;

		if (ObjectType== pObj->m_ObjectType)
		{
			return pObj;
		}
	
		pObj = pNext;
	}

	return nullptr;
}
CObject* CObject::GetpTop(int nPriority)
{
	return m_pTop[nPriority];
}
//=============================
//	���̃|�C���^�擾
//=============================
CObject* CObject::GetNext()
{
	return m_pNext;
}

//=============================
//	�f�[�^������
//=============================
CObject::DATA CObject::DataInit()
{
	DATA data;
	data.MinLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.MaxLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.OldPos= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	data.Radius = 0.0f;
	data.rot= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return data;
}

int CObject::GetNum()
{
	return m_nNumAll;
}

//=============================
//	�������g���J��
//=============================
void CObject::Release()
{
	// �O����Ȃ���
	if (m_pPrev != nullptr)
	{//�������O�����鎞
		m_pPrev->m_pNext = m_pNext;//����O��
	}
	else
	{
		m_pTop[m_nPriority] = m_pNext;
	}

	if (m_pTop[m_nPriority] == this)
	{//���g���擪�̂Ƃ�
		m_pTop[m_nPriority] = m_pNext;//�擪��O��
	}

	if (m_pNext != nullptr)
	{//�������鎞
		m_pNext->m_pPrev = m_pPrev;//����"�O"�����g�̑O��
	}

	Uninit();

	m_nNumAll--;//�������f�N�������g

	delete this;

}

//=============================
// �I�u�W�F�N�g�^�C�v�ݒ�
//=============================
void CObject::SetObjectType(OBJECTTYPE ObjectType)
{
	m_ObjectType = ObjectType;
}
//=============================
// �I�u�W�F�N�g�^�C�v�擾
//=============================
CObject::OBJECTTYPE CObject::GetObjectType()
{
	return m_ObjectType;
}