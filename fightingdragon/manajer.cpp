//============================
//
//�}�l�[�W���[����(manager.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include "xaudio2.h"					 //�T�E���h�����ɕK�v
#include "object2D.h"
#include "anim.h"
#include "bg.h"
//#include "bullet.h"
#include "object3d.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "abg.h"
#include "effect.h"
#include "sound.h"
#include "score.h"
#include "time.h"
#include "block.h"
#include "camera.h"
#include "light.h"
#include "bilboard.h"
#include "objectx.h"
//#include "shadow.h"
#include "debugproc.h"
//#include "infection.h"
#include "mode.h"

//�ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;				//�����_���[��������
CInputKeyboard *CManager::m_pInputKeyboard = NULL;		//�L�[�{�[�h����������
CDebugProc *CManager::m_pDebugProc = NULL;				//�f�o�b�O����������
CSound *CManager::m_pSound = NULL;						//�T�E���h����������
CScene *CManager::m_pScene = NULL;						//�V�[������������
CScene *CScene::m_pScene = NULL;						//�V�[������������
CInputGamePad *CManager::m_pInputGamePad = NULL;		//�Q�[���p�b�h����������

//============================
//�R���X�g���N�^
//============================
CScene::CScene()
{
	m_Mode = MODE_TITLE;

	m_nMode = 0;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


//============================
//�f�X�g���N�^
//============================
CScene::~CScene()
{

}

//============================
//���[�h�̐���
//============================
CScene *CScene::Create(MODE mode)
{
	switch (mode)
	{
	case CScene::MODE_TITLE:
		m_pScene = CTitle::Create(D3DXVECTOR3(640.0f,360.0f,0.0f),0.0f,0);
		break;

	case CScene::MODE_STORY:
		m_pScene = CStory::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);
		break;

	case CScene::MODE_TUTORIAL:
		m_pScene = CTutorial::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);
		break;

	case CScene::MODE_GAME:
		m_pScene = CGame::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0);

		break;

	case CScene::MODE_RESULT:
		m_pScene = CResult::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);
		break;

	case CScene::MODE_GAMEOVER:
		m_pScene = CGameOver::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);
		break;

	case CScene::MODE_MAX:
		break;
	}
	
	if (m_pScene == NULL)
	{
		return NULL;
	}

	return m_pScene;
}

//============================
//�V�[���̏�����
//============================
HRESULT CScene::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	m_Mode = MODE_TITLE;

	CManager::SetMode(m_Mode);

	return S_OK;
}

//============================
//�V�[���̏I��
//============================
void CScene::Uninit(void)
{
	Release();

	/*if (m_pScene != NULL)
	{
		delete m_pScene;
		m_pScene = NULL;
	}*/
	
}

//============================
//�V�[���̍X�V
//============================
void CScene::Update(void)
{
	
}

//============================
//�V�[���̕`��
//============================
void CScene::Draw(void)
{
	
}

//============================
//�ʒu���Z�b�g����
//============================
void CScene::SetPosition(D3DXVECTOR3 pos)
{
	
}

//============================
//�ʒu�̎擾
//============================
D3DXVECTOR3 CScene::GetPosition(void)
{
	return m_pos;
}

//============================
//�ړ��ʂ̎擾
//============================
D3DXVECTOR3 CScene::GetMove(void)
{
	return m_pos;
}

//============================
//�V�[�����Q�b�g
//============================
CScene::MODE CScene::GetMode(void)
{
	return m_Mode;
}

//�ȉ��}�l�[�W���[�̏���

//============================
//�R���X�g���N�^
//============================
CManager::CManager()
{

}


//============================
//�f�X�g���N�^
//============================
CManager::~CManager()
{

}

//============================
//������
//============================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	//NULL�`�F�b�N
	if (m_pSound == NULL)
	{
		//�T�E���h�̐���
		m_pSound = NEW_DBG CSound;
	}
	else
	{
		return -1;
	}

	if (m_pSound != NULL)
	{
		m_pSound->InitSound(hWnd);
	}

	//NULL�`�F�b�N
	if (m_pRenderer == NULL)
	{
		//�����_���[�̐���
		m_pRenderer = NEW_DBG CRenderer;

	}
	else
	{
		return -1;
	}

	//NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{
		//����������
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//���������������s�����ꍇ

			return -1;
		}
	}
	else
	{
		return -1;
	}

	//NULL�`�F�b�N
	if (m_pScene == NULL)
	{
		m_pScene = CScene::Create(CScene::MODE_TITLE);
	}
	else
	{
		return -1;
	}

	//NULL�`�F�b�N
	if (m_pDebugProc == NULL)
	{
		m_pDebugProc = NEW_DBG CDebugProc;

		m_pDebugProc->Init();
	}
	else
	{
		return -1;
	}

	//NULL�`�F�b�N
	if (m_pInputKeyboard == NULL)
	{
		//�L�[�{�[�h���͂̐���
		m_pInputKeyboard = NEW_DBG CInputKeyboard;
	}
	else
	{
		return -1;
	}

	
	//NULL�`�F�b�N
	if (m_pInputKeyboard != NULL)
	{
		//����������
		if (FAILED(m_pInputKeyboard->Init(hinstance, hWnd)))
		{//���������������s�����ꍇ

			return -1;
		}
	}
	else
	{
		return -1;
	}

	//NULL�`�F�b�N
	if (m_pInputGamePad == NULL)
	{
		//�Q�[���p�b�h���͂̐���
		m_pInputGamePad = NEW_DBG CInputGamePad;
	}
	else
	{
		return -1;
	}


	//NULL�`�F�b�N
	if (m_pInputGamePad != NULL)
	{
		//����������
		if (FAILED(m_pInputGamePad->Init(hWnd)))
		{//���������������s�����ꍇ

			return -1;
		}
	}
	else
	{
		return -1;
	}

	return S_OK;
}
//============================
//�I��
//============================
void CManager::Uninit(void)
{
	////�I�u�W�F�N�g�S�Ă̔j��
	//CObject::ReleaseAll();

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		
		m_pScene = NULL;
	}

	//�L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		//�I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;

		m_pInputKeyboard = NULL;
	}

	//�Q�[���p�b�h�j��
	if (m_pInputGamePad != NULL)
	{
		//�I������
		m_pInputGamePad->Uninit();

		delete m_pInputGamePad;

		m_pInputGamePad = NULL;
	}

	//�f�o�b�O�̔j��
	if (m_pDebugProc != NULL)
	{
		//�I������
		m_pDebugProc->Uninit();

		delete m_pDebugProc;

		m_pDebugProc = NULL;
	}

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		//�I������
		m_pRenderer->Uninit();

		delete m_pRenderer;

		m_pRenderer = NULL;
	}

	if (m_pSound != NULL)
	{
		//�T�E���h�̒�~
		m_pSound->StopSound();

		//�T�E���h�̏I������
		m_pSound->UninitSound();

		delete m_pSound;

		m_pSound = NULL;
	}
}
//============================
//�X�V
//============================
void CManager::Update(void)
{
	/*UpdateShadow();*/

	//�L�[�{�[�h�̍X�V
	m_pInputKeyboard->Update();

	//�Q�[���p�b�h�̍X�V
	m_pInputGamePad->Update();

	//�f�o�b�O�̍X�V
	m_pDebugProc->Update();

	//�����_���[�̍X�V
	m_pRenderer->Update();
}
//============================
//�`��
//============================
void CManager::Draw(void)
{//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)

	//DrawShadow();

	//�����_���[�̕`��
	m_pRenderer->Draw();
}

//============================
//�T�E���h�̏��擾
//============================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//============================
//�����_���[�̏��擾
//============================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//============================
//�L�[�{�[�h���擾
//============================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//============================
//�f�o�b�O�̏��擾
//============================
CDebugProc *CManager::GetDebugProck(void)
{
	return m_pDebugProc;
}

//============================
//�V�[���̏��Z�b�g
//============================
void CManager::SetMode(CScene::MODE mode)
{
	//�T�E���h�̒�~
	m_pSound->StopSound();

	if (m_pScene != NULL)
	{
		m_pScene->Uninit();
		
		m_pScene = NULL;
	}

	m_pScene = CScene::Create(mode);
}

//============================
//�Q�[���p�b�h���擾
//============================
CInputGamePad *CManager::GetGamePad(void)
{
	return m_pInputGamePad;
}



