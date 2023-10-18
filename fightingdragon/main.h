//============================
//
//�|���S���`��(main.h)
//Author:���� �F�M
//
//============================

#ifndef _MAIN_H_   //���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION  (0x0800)    //�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"
#include <assert.h>		//�A�T�[�g����

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")     //�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")    //[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")   //DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")    //�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")  //���͏����ɕK�v


//�}�N����`
#define SCREEN_WIDTH  (1280)              //�E�C���h�E�̕�
#define SCREEN_HEIGHT  (720)               //�E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)  //���_�t�H�[�}�b�g[2D]
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) //���_�t�H�[�}�b�g[3D]

//���_���[2D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;   //���_���W
	float rhw;         //���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;      //���_�J���[
	D3DXVECTOR2 tex;   //�e�N�X�`�����W
}VERTEX_2D;

//���_���[3D]�̍\����
typedef struct
{
	D3DXVECTOR3 pos; //���_���
	D3DXVECTOR3 nor; //�@���x�N�g��(�����ƕ���)
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_3D;

//void DrawFPS(void);

//���������[�N�o�͗p�}�N��
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>  //���������[�N���o�ɕK�v

#ifdef _DEBUG
#define NEW_DBG new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define NEW_DBG new
#endif

#endif // 



