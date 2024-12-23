//=========================================================
//
// main.cpp�Ŏg���֐�[main.h]
// Author seiya kagaya
//
//=========================================================
#ifndef _MAIN_H

#define _MAIN_H//��d�C���N���[�h�h�~


#include <Windows.h>
#include "d3dx9.h"//�`�ʏ����Ɏg��
#include <cmath>
#include <vector>
#define DIRECTINPUT_VERSION (0x0800)//�x���΍�

#include "dinput.h"//����

#include "xinput.h"
#include <iostream>



#pragma comment(lib,"xinput.lib")//�W���C�p�b�h�����ɕK�v


//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")	//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")//�R���|�[�l�b�g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v




//�}�N����`
#define CLASS_NAME		("WindowsClass")
#define WINDOW_NAME		("Mini-Tank!")
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//���_����ݒ�
#define FVF_VERTEX_3D	(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//3D�p���_���W(���_���W{3D},�@���A���_�t�H�[�}�b�g�Q��)

#define GAME_FPS		(60)

//��{4���_
#define BASE_INDEX	(4)




//���_���W�\���̂̒�`
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
};

//���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;			//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;



//�E�B���h�E�v���V�[
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int GetFPS(void);

// �E�B���h�E�̕��ƍ������擾����֐�

void GetWindowSize(HWND hWnd, int& width, int& height);

#endif