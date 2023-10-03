//============================
//
//�|�[�Y����(pause.cpp)
//Author:���� �F�M
//
//============================
#include "mode.h"
#include "pause.h"
#include "input.h"
#include "time.h"
#include "manager.h"
#include "renderer.h"

//========================
//�|�[�Y��ʂ̃R���X�g���N�^
//========================
CPause::CPause()
{
	for (int nCnt = 0; nCnt < NUM_PAUSE; nCnt++)
	{
		m_apTexturePause[nCnt] = NULL;		//�e�N�X�`��(3����)�ւ̃|�C���^
		acol[nCnt] = nCnt;
	}

	 m_pVtxBuffPause = NULL;		 //���_�o�b�t�@�ւ̃|�C���^
	 m_PauseMenu;		//�|�[�Y���j���[
	 m_Kecheck; //�L�[�������ꂽ���m�F����

	 m_bPause = false;
}

//========================
//�|�[�Y��ʂ̃f�X�g���N�^
//========================
CPause::~CPause()
{
	
}

//============================
//���[�h�̐���
//============================
CPause *CPause::Create(void)
{
	CPause *pPause;

	pPause = new CPause;


	if (pPause == NULL)
	{
		return NULL;
	}

	pPause->InitPause();

	return pPause;
}

//========================
//�|�[�Y��ʂ̏���������
//========================
void CPause::InitPause(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	int nCntPause;

	m_bPause = false;

	//�J���[��������
	 acol[0] = D3DXCOLOR(1.0f,1.0f,1.0f, 1.0f);
	 acol[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	 acol[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	 acol[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	 acol[4] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�L�[�`�F�b�N��������
	m_Kecheck = false;

	//�|�[�Y���j���[��������
	m_PauseMenu = PAUSE_MENU_CONTINUE;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\continue.png",
		&m_apTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\retry.png",
	&m_apTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\exitgame.png",
		&m_apTexturePause[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enter.png",
		&m_apTexturePause[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\pausecon.png",
		&m_apTexturePause[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPause,
		NULL);

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(150.0f , 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(500.0f , 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(150.0f , 300.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(500.0f , 300.0f, 0.0f);

		if(nCntPause == 3)
		{
			pVtx[0].pos = D3DXVECTOR3(600.0f, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(800.0f, 400.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(600.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, 600.0f, 0.0f);
		}

		if (nCntPause == 4)
		{
			pVtx[0].pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(700.0f, 400.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(500.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(700.0f, 600.0f, 0.0f);
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + 1.0f);

		pVtx += 4;   //���_�f�[�^�̃|�C���^��4���i�߂�

	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuffPause->Unlock();

}

//======================
//�|�[�Y�̏I������
//======================
void CPause::UninitPause(void)
{
	int nCntPause;

	//3���ڂ̃e�N�X�`���̔j��
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		if (m_apTexturePause[nCntPause] != NULL)
		{
			m_apTexturePause[nCntPause]->Release();
			m_apTexturePause[nCntPause] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffPause != NULL)
	{
		m_pVtxBuffPause->Release();
		m_pVtxBuffPause = NULL;
	}
}

//=========================
//�|�[�Y�̍X�V����
//=========================
void CPause::UpdatePause(void)
{
	int nCntPause;
	bool bPause;
	bPause = GetPause();

	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	pInputGamepad = CManager::GetGamePad();

	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	for (nCntPause = 0; nCntPause < 3; nCntPause++)
	{
		if (m_PauseMenu == nCntPause)
		{
			acol[nCntPause] = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		}

		else if (nCntPause != m_PauseMenu)
		{
			acol[nCntPause] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_UP, 0) == true)
	{//�㑀�삪�s��ꂽ�ꍇ


	 //�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_TUTORIAL);

		switch (m_PauseMenu)
		{
		case PAUSE_MENU_CONTINUE:

			m_PauseMenu = PAUSE_MENU_QUIT;

			break;

		case PAUSE_MENU_QUIT:

			m_PauseMenu = PAUSE_MENU_RETRY;

			break;

		case PAUSE_MENU_RETRY:

			m_PauseMenu = PAUSE_MENU_CONTINUE;

			break;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_S) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_DOWN, 0) == true)
	{//�����삪�s��ꂽ�ꍇ


	 //�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_TUTORIAL);

		switch (m_PauseMenu)
		{
		case PAUSE_MENU_CONTINUE:

			m_PauseMenu = PAUSE_MENU_RETRY;

			break;

		case PAUSE_MENU_RETRY:

			m_PauseMenu = PAUSE_MENU_QUIT;

			break;

		case PAUSE_MENU_QUIT:

			m_PauseMenu = PAUSE_MENU_CONTINUE;

			break;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{//����L�[(ENTER)�������ꂽ

		//PlaySound(SOUND_LABEL_ENTER);

		if (m_Kecheck == false)
		{

			switch (m_PauseMenu)
			{
			case PAUSE_MENU_CONTINUE:

				SetEnablePause(bPause = false);

				break;

			case PAUSE_MENU_RETRY:

				m_Kecheck = true;

				/*SetFade(MODE_GAME);*/

				

				break;

			case PAUSE_MENU_QUIT:

				m_Kecheck = true;

				/*SetFade(MODE_TITLE);*/

				/*ResetTime();*/

				break;
			}
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	if (bPause == true)
	{
		for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(500.0f, 100.0f + (nCntPause * SPACE_DATA), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(800.0f, 100.0f + (nCntPause * SPACE_DATA), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(500.0f, 200.0f + (nCntPause * SPACE_DATA), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800.0f, 200.0f + (nCntPause * SPACE_DATA), 0.0f);

			if (nCntPause == 3)
			{
				pVtx[0].pos = D3DXVECTOR3(1050.0f, 620.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(1250.0f, 620.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(1050.0f, 720.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(1250.0f, 720.0f, 0.0f);
			}

			if (nCntPause == 4)
			{
				pVtx[0].pos = D3DXVECTOR3(800.0f, 620.0f, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(1000.0f,620.0f, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(800.0f, 720.0f, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(1000.0f,720.0f, 0.0f);
			}

			pVtx[0].col = acol[nCntPause];
			pVtx[1].col = acol[nCntPause];
			pVtx[2].col = acol[nCntPause];
			pVtx[3].col = acol[nCntPause];

			//�e�N�X�`�����W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;   //���_�f�[�^�̃|�C���^��4���i�߂�
		}

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuffPause->Unlock();
	}
}

//======================
//�|�[�Y�̕`�揈��
//======================
void CPause::DrawPause(void)
{
	int nCntPause;

	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (nCntPause = 0; nCntPause < NUM_PAUSE; nCntPause++)
	{
		pDevice->SetTexture(0, m_apTexturePause[nCntPause]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2); //�v���~�e�B�u�̎��

	}
}

//=======================
//�|�[�Y���j���[�̃��Z�b�g
//=======================
void CPause::ResetPause(void)
{
	//�|�[�Y���j���[��������
	m_PauseMenu = PAUSE_MENU_CONTINUE;
}

//===================================
//�|�[�Y��Ԃ̎擾
//===================================
void CPause::SetEnablePause(bool bPause)
{
	m_bPause = bPause;
}

//========================
//�|�[�Y��Ԃ̎擾
//========================
bool CPause::GetPause(void)
{
	return m_bPause;
}