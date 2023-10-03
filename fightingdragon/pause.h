//============================
//
//�|�[�Y����(pause.h)
//Author:���� �F�M
//
//============================
#ifndef _PAUSE_H_   //���̃}�N����`������Ă��Ȃ�������
#define _PAUSE_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define NUM_PAUSE  (5)		//�|�[�Y���j���[�̐�
#define SPACE_DATA (200.0f) //�|�[�Y���j���[�̊Ԋu�̃f�[�^

class CPause
{
public:
	//�|�[�Y���j���[
	typedef enum
	{
		PAUSE_MENU_CONTINUE = 0,	//�Q�[���ɖ߂�
		PAUSE_MENU_RETRY,			//�Q�[������蒼��
		PAUSE_MENU_QUIT,			//�^�C�g����ʂɖ߂�
		PAUSE_MENU_MAX
	}PAUSE_MENU;

	CPause();
	~CPause();

	static CPause *Create(void);

	//�v���g�^�C�v�錾
	void InitPause(void);
	void UninitPause(void);
	void UpdatePause(void);
	void DrawPause(void);
	void ResetPause(void);

	void SetEnablePause(bool bPause);
	bool GetPause(void);

private:
	LPDIRECT3DTEXTURE9 m_apTexturePause[NUM_PAUSE] = {};		//�e�N�X�`��(3����)�ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPause = NULL;		 //���_�o�b�t�@�ւ̃|�C���^
	PAUSE_MENU m_PauseMenu;		//�|�[�Y���j���[
	bool m_Kecheck; //�L�[�������ꂽ���m�F����
	D3DXCOLOR acol[NUM_PAUSE];
	bool m_bPause;			//�|�[�Y��Ԃ�ON/OFF
	//VERTEX_2D g_aVertex[4];  //���_�����i�[
};
#endif
