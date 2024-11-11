//=======================================================
//
//all_texture�Ɋւ��鏈��[all_texture.cpp]
// Auther seiya kagaya
//
//=======================================================
#include "all_texture.h"
#include "renderer.h"
#include "manager.h"



//�䗬�̂��ߒ��ӁA











//=============================
// �R���X�g���N�^
//=============================
CAllTexture::CAllTexture()
{
	m_nNumAll = 0;
	for (int i = 0; i < m_nMaxTexture; i++)
	{
		m_pTexture[i] = nullptr;
		m_pFilePass[i] = nullptr;
	}
}
//=============================
// �f�X�g���N�^
//=============================
CAllTexture::~CAllTexture()
{
}
//=============================
// ������
//=============================
void CAllTexture::Init()
{
	//CRenderer* g_pRenderer = nullptr;
	//g_pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 EscDevice = g_pRenderer->GetDevice();

	//// �e�N�X�`���̓ǂݍ���
	//for (int nCnt = 0; nCnt < OBJECT_MAX; nCnt++)
	//{
	//	m_TextureInfo[nCnt].m_pTexture = nullptr;
	//	// �e�N�X�`���̓ǂݍ���
	//	D3DXCreateTextureFromFile(EscDevice, m_TextureInfo[nCnt].pFilePass, &m_TextureInfo[nCnt].m_pTexture); // �ʏ펞
	//}
}
//=============================
// �j������
//=============================
void CAllTexture::Uninit()
{
	Unload();//�e�N�X�`���j��
}
//=============================
// �e�N�X�`���j������
//=============================
void CAllTexture::Unload()
{
	for (int nCnt = 0; nCnt < m_nMaxTexture; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();//-------------------------���[��厖
			m_pTexture[nCnt] = nullptr;
		}
		if (m_pFilePass[nCnt] != nullptr)
		{//���������m�ۂ��Ă��邽��
			delete[] m_pFilePass[nCnt];
			m_pFilePass[nCnt] = nullptr;
		}
	}
}
//=============================
// �e�N�X�`���o�^����
//=============================
int CAllTexture::Regist(const char* pTextureName, LPDIRECT3DDEVICE9 pDevice)
{
	int nIdx = 0;
	for (int nCnt = 0; nCnt < m_nMaxTexture; nCnt++)
	{
		if (m_pTexture[nCnt] == nullptr)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, pTextureName, &m_pTexture[nCnt]); // �ʏ펞
			nIdx = nCnt; // Id�ݒ�
			m_nNumAll++;

			// ������̃��������m�ۂ��ăR�s�[
			m_pFilePass[nCnt] = new char[strlen(pTextureName) + 1];
			strcpy(m_pFilePass[nCnt], pTextureName);

			break;
		}
		else if (strcmp(pTextureName, m_pFilePass[nCnt]) == 0)
		{//���łɂ���p�X�ƈ�v
			nIdx = nCnt;
			break;
		}
	}
	return nIdx;
}
//=============================
// �e�N�X�`���擾
//=============================
LPDIRECT3DTEXTURE9 CAllTexture::GetAddress(int nIdx)
{
	//���S�ȃR�s�[��������ۂ�
	m_pTexture[nIdx]->AddRef();//����K�{�H�H�H

	return m_pTexture[nIdx];
}
////=============================
//// �e�N�X�`���擾
////=============================
//LPDIRECT3DTEXTURE9 CAllTexture::GetTexture(CObject::OBJECTTYPE ObjectType, LPDIRECT3DDEVICE9 pDevice)
//{
//	for (int nCnt = 0; nCnt < CObject::OBJECT_MAX; nCnt++)
//	{
//		if (m_TextureInfo[nCnt].objectType == ObjectType)
//		{
//			if (m_TextureInfo[nCnt].m_pTexture == nullptr)
//			{ // �e�N�X�`�����܂��ǂݍ��܂�Ă��Ȃ��ꍇ
//			
//			    // �e�N�X�`���̓ǂݍ���
//				D3DXCreateTextureFromFile(pDevice, m_TextureInfo[nCnt].pFilePass, &m_TextureInfo[nCnt].m_pTexture); // �ʏ펞
//			}
//
//			return m_TextureInfo[nCnt].m_pTexture;
//		}
//	}
//
//	// �Y������e�N�X�`����������Ȃ��ꍇ�̓f�t�H���g�̃e�N�X�`����Ԃ�
//	return m_TextureInfo[0].m_pTexture;
//}
//
//
//
//






