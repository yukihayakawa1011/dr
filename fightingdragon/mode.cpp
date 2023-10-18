//============================
//
//���[�h����(mode.h)
//Author:���� �F�M
//
//============================
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
#include "pause.h"

CPlayer *CGame::m_pPlayer = NULL;					//�v���C���[����������
CPlayer *CGame::m_pPlayerMirror = NULL;					//�v���C���[����������
CExplosion *CGame::m_pExplosion = NULL;				//��������������
CEnemy *CGame::m_pEnemy = NULL;						//�G����������
CAbg *CGame::m_pAbg = NULL;							//���d�w�i��������
CEffect *CGame::m_pEffect = NULL;					//�G�t�F�N�g����������
CScore *CGame::m_pScore = NULL;						//�X�R�A����������
CTime *CGame::m_pTime = NULL;						//�^�C������������
CBlock *CGame::m_pBlock = NULL;						//�u���b�N����������
CCamera *CGame::m_pCamera = NULL;					//�J��������������
CLight *CGame::m_pLight = NULL;						//���C�g����������
CObjectx *CGame::m_pObjectx[USE_OBJECTX] = {};		//�I�u�W�F�N�gX����������
CModel *CGame::m_pModel = NULL;						//���f������������
CInfection *CGame::m_pInfection = NULL;				//����������������
CObject3d *CGame::m_pObject3d = NULL;				//����������������
CPause *CGame::m_pPause = NULL;				//����������������

//============================
//�^�C�g���R���X�g���N�^
//============================
CTitle::CTitle()
{
	m_pTexture = NULL;				//�e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
}

//============================
//�^�C�g���f�X�g���N�^
//============================
CTitle::~CTitle()
{

}

//===========================
//����
//===========================
CTitle *CTitle::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CTitle *pTitle;

	//�I�u�W�F�N�g2D�̐���
	pTitle = NEW_DBG CTitle;

	//����������
	pTitle->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pTitle;
}

//===========================
//�^�C�g��������
//===========================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\infection_title.png",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@��NULL��������
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//�e�N�X�`���̃|�C���^��NULL��������
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////�p�x�����߂�
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////�������Z�o����
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////���_���W�̐ݒ�
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(�@��)�̐ݒ�
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
//�^�C�g���I��
//===========================
void CTitle::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	
	CScene::Uninit();

	ReleaseAll();
}

//===========================
//�^�C�g���X�V
//===========================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		
		CManager::GetInstance()->SetMode(MODE_STORY);
			
		CSound::PlaySound(CSound::SOUND_LABEL_SE_TITLEENTER);

	}
	

//#ifdef _DEBUG
//
//	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
//	{
//		CManager::SetMode(MODE_GAME);
//	}
//
//#endif // DEBUG

}

//===========================
//�^�C�g���`��
//===========================
void CTitle::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��
}

//============================
//�X�g�[���[�R���X�g���N�^
//============================
CStory::CStory()
{
	m_pTexture = NULL;				//�e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
}

//============================
//�X�g�[���[�f�X�g���N�^
//============================
CStory::~CStory()
{

}

//===========================
//�X�g�[���[����
//===========================
CStory *CStory::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CStory *pStory;

	//�I�u�W�F�N�g2D�̐���
	pStory = NEW_DBG CStory;

	//����������
	pStory->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pStory;
}

//===========================
//�X�g�[���[������
//===========================
HRESULT CStory::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\story.png",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@��NULL��������
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//�e�N�X�`���̃|�C���^��NULL��������
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////�p�x�����߂�
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////�������Z�o����
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////���_���W�̐ݒ�
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(�@��)�̐ݒ�
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
//�X�g�[���[�I��
//===========================
void CStory::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//�X�g�[���[�X�V
//===========================
void CStory::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_TUTORIAL);

		CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTORIALENTER);
	}


	//#ifdef _DEBUG
	//
	//	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//	{
	//		CManager::SetMode(MODE_GAME);
	//	}
	//
	//#endif // DEBUG

}

//===========================
//�X�g�[���[�`��
//===========================
void CStory::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��
}

//============================
//�`���[�g���A���R���X�g���N�^
//============================
CTutorial::CTutorial()
{
	m_pTexture = NULL;				//�e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
}

//============================
//�`���[�g���A���f�X�g���N�^
//============================
CTutorial::~CTutorial()
{

}

//===========================
//�`���[�g���A������
//===========================
CTutorial *CTutorial::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CTutorial *pTutorial;

	//�I�u�W�F�N�g2D�̐���
	pTutorial = NEW_DBG CTutorial;

	//����������
	pTutorial->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pTutorial;
}

//===========================
//�`���[�g���A��������
//===========================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\tutorial0.png",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@��NULL��������
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//�e�N�X�`���̃|�C���^��NULL��������
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////�p�x�����߂�
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////�������Z�o����
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////���_���W�̐ݒ�
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(�@��)�̐ݒ�
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
//�`���[�g���A���I��
//===========================
void CTutorial::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//�`���[�g���A���X�V
//===========================
void CTutorial::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_GAME);

		CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTORIALENTER);
	}


	//#ifdef _DEBUG
	//
	//	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//	{
	//		CManager::SetMode(MODE_GAME);
	//	}
	//
	//#endif // DEBUG

}

//===========================
//�`���[�g���A���`��
//===========================
void CTutorial::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��
}

//============================
//�Q�[���R���X�g���N�^
//============================
CGame::CGame()
{
	m_pBlock = NULL;

	m_pEnemy = NULL;

	m_pTime = NULL;

	m_pInfection = NULL;

	m_pPlayer = NULL;

	m_pCamera = NULL;

	m_pLight = NULL;

	m_pObject3d = NULL;

	m_pPause = NULL;

	m_bPause = false;
}

//============================
//�Q�[���f�X�g���N�^
//============================
CGame::~CGame()
{

}

//===========================
//����
//===========================
CGame *CGame::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CGame *pGame;

	//�I�u�W�F�N�g2D�̐���
	pGame = NEW_DBG CGame;

	//����������
	pGame->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pGame;
}

//===========================
//�Q�[��������
//===========================
HRESULT CGame::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	nTex = 0;

	fRot = 0.0f;

	m_bPause = false;

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//CAbg::Load();			//���d�w�i�e�N�X�`�����[�h

	CScore::Load();			//�X�R�A�e�N�X�`�����[�h

	//CEffect::Load(0);		//�G�t�F�N�g�e�N�X�`�����[�h

							//CExplosion::Load();		//�����e�N�X�`�����[�h

							CBlock::Load();			//�u���b�N�e�N�X�`�����[�h

							//CEnemy::Load();			//�G�e�N�X�`�����[�h

							//CPlayer::Load();		//�v���C���[�e�N�X�`�����[�h

	CObject3d::Load();		//�I�u�W�F�N�g3d�e�N�X�`�����[�h

							//CBilboard::Load();		//�r���{�[�h�e�N�X�`�����[�h

							////�I�u�W�F�N�g�̐���(��������)
							//CBg::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 50.0f, 0);

							////���d�w�i�̐���
							//CAbg::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 0.0f, 0);

							////�A�j���[�V�����̐���
							//CAnim::Create(D3DXVECTOR3(800.0f, 500.0f, 0.0f), 50.0f, 0);

							/*InitShadow();*/


	if (m_pObject3d == NULL)
	{
		////�I�u�W�F�N�g3D�̐���
		m_pObject3d = CObject3d::Create(D3DXVECTOR3(-250.0f, 0.0f, 0.0f), 50.0f, 0, 50.0f, 50.0);
	}
	else
	{
		return -1;
	}

	if (m_pEnemy == NULL)
	{//�G�̐���
		m_pEnemy = CEnemy::Create(D3DXVECTOR3(-250.0f, 0.0f, 0.0f), D3DX_PI * -0.5f, 0, 50.0f, 50.0f);
	}
	else
	{
		return -1;
	}


	//NULL�`�F�b�N
	if (m_pPlayer == NULL)
	{
		//�v���C���[�̐���
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(300.0f, 2.0f, -10.0f), D3DX_PI * 0.5f, 1, 20.0f, 20.0f);
	}
	else
	{
		return -1;
	}

	//if (m_pScore == NULL)
	//{
	//	//�X�R�A�̐���
	//	m_pScore = CScore::Create(D3DXVECTOR3(300.0f, 700.0f, 0.0f), 0.0f, 0);
	//}
	////CBilboard::Create(D3DXVECTOR3(-400.0f, 0.0f, 0.0f), 0.0f, 0, 200.0f, 200.0f);

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = NEW_DBG CCamera;
		m_pCamera->Init();
	}

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = NEW_DBG CLight;
		m_pLight->Init();
	}

	////�|�[�Y�̐���
	//if (m_pPause == NULL);
	//{
	//	m_pPause = NEW_DBG CPause;
	//}

	return S_OK;
}

//===========================
//�Q�[���I��
//===========================
void CGame::Uninit(void)
{
	//�J�����̔j��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	//���C�g�̔j��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();

		delete  m_pLight;
		m_pLight = NULL;
	}

	////���d�w�i�̃e�N�X�`���j��
	//CAbg::Unload();

	//�X�R�A�e�N�X�`���̃e�N�X�`���j��
	CScore::Unload();

	////�^�C���e�N�X�`���̃e�N�X�`���j��
	//CTime::Unload();

	////�e�̃e�N�X�`���j��
	//CBullet::Unload();

	//�G�t�F�N�g�̃e�N�X�`���j��
	CEffect::Unload();

	//�G�̃e�N�X�`���j��
	CEnemy::Unload();

	////�����̃e�N�X�`���j��
	//CExplosion::Unload();

	////�v���C���[�̃e�N�X�`���j��
	//CPlayer::Unload();

	//�u���b�N�̃e�N�X�`���j��
	CBlock::Unload();

	//�I�u�W�F�N�g3d�e�N�X�`���j��
	CObject3d::Unload();

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//�Q�[���X�V
//===========================
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	/*if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_START, 0) == true)
	{
		m_bPause = m_bPause ? false : true;
	}*/

	if (m_bPause == true)
	{//P�L�[��������Ă��Ȃ���
	 //�|�[�Y��ʂ̍X�V����

		/*m_pPause->Update();*/
	}

	if (m_bPause == false)
	{
		//�J�����̍X�V
		m_pCamera->Update();

		m_pLight->Update();

		CInputKeyboard *pInputKeyboard;

		//�L�[�{�[�h�̎擾
		pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

		D3DXVECTOR3 pos = m_pPlayer->GetPosition();

		if (pos.x <= -300.0f)
		{
			CManager::GetInstance()->SetMode(MODE_RESULT);
		}

		bool bDeath = m_pPlayer->GetDeath();

		if (bDeath == true)
		{
			CManager::GetInstance()->SetMode(MODE_GAMEOVER);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_RESULT);

		CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTORIALENTER);
	}
}

//===========================
//�Q�[���`��
//===========================
void CGame::Draw(void)
{
	//�J�������擾
	CCamera *pCamera = CGame::GetCamera();

	//�J�����̐ݒ�
	pCamera->SetCamera();
}

//============================
//���U���g�R���X�g���N�^
//============================
CResult::CResult()
{
	m_pTexture = NULL;				//�e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
}

//============================
//���U���g�f�X�g���N�^
//============================
CResult::~CResult()
{

}

//===========================
//����
//===========================
CResult *CResult::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CResult *pResult;

	//�I�u�W�F�N�g2D�̐���
	pResult = NEW_DBG CResult;

	//����������
	pResult->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pResult;
}

//===========================
//���U���g������
//===========================
HRESULT CResult::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\clear.jpg",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@��NULL��������
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//�e�N�X�`���̃|�C���^��NULL��������
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////�p�x�����߂�
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////�������Z�o����
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////���_���W�̐ݒ�
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(�@��)�̐ݒ�
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===========================
//���U���g�I��
//===========================
void CResult::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//���U���g�X�V
//===========================
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_TITLE);

		CSound::PlaySound(CSound::SOUND_LABEL_SE_TUTORIALENTER);
	}
}

//===========================
//���U���g�`��
//===========================
void CResult::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��
}

//============================
//�Q�[���I�[�o�[�R���X�g���N�^
//============================
CGameOver::CGameOver()
{
	m_pTexture = NULL;				//�e�N�X�`���̃|�C���^
	m_pVtxBuff = NULL;				//���_�o�b�t�@�ւ̃|�C���^
}

//============================
//�Q�[���I�[�o�[�f�X�g���N�^
//============================
CGameOver::~CGameOver()
{

}

//===========================
//�Q�[���I�[�o�[����
//===========================
CGameOver *CGameOver::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CGameOver *pGameOver;

	//�I�u�W�F�N�g2D�̐���
	pGameOver = NEW_DBG CGameOver;

	//����������
	pGameOver->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex);

	return pGameOver;
}

//===========================
//�Q�[���I�[�o�[������
//===========================
HRESULT CGameOver::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fRot = 0.0f;

	if (nTex == 0)
	{//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\gameover.png",
			&m_pTexture);
	}

	if (pDevice == NULL)
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_�o�b�t�@��NULL��������
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//�e�N�X�`���̃|�C���^��NULL��������
	if (m_pTexture == NULL)
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y - 360.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - 640.0f, pos.y + 360.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + 640.0f, pos.y + 360.0f, 0.0f);


	////�p�x�����߂�
	//m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////�������Z�o����
	//m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////���_���W�̐ݒ�
	//pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[0].pos.z = 0.0f;			   

	//pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[1].pos.z = 0.0f;			    

	//pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[2].pos.z = 0.0f;			    

	//pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//pVtx[3].pos.z = 0.0f;

	//rhw(�@��)�̐ݒ�
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	CSound::PlaySound(CSound::SOUND_LABEL_SE_DEATH);

	return S_OK;
}

//===========================
//�Q�[���I�[�o�[�I��
//===========================
void CGameOver::Uninit(void)
{
	CSound::StopSound();

	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_���̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CScene::Uninit();

	ReleaseAll();
}

//===========================
//�Q�[���I�[�o�[�X�V
//===========================
void CGameOver::Update(void)
{
	CInputKeyboard *pInputKeyboard;

	CInputGamePad *pInputGamepad;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	pInputGamepad = CManager::GetInstance()->GetGamePad();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetMode(MODE_TITLE);
	}
}

//===========================
//�Q�[���I�[�o�[�`��
//===========================
void CGameOver::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); //�v���~�e�B�u�̎��
}

//============================
//�v���C���[���擾
//============================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//============================
//�v���C���[�~���[���擾
//============================
CPlayer *CGame::GetPlayerMirror(void)
{
	return m_pPlayerMirror;
}

//============================
//�����̏��擾
//============================
CExplosion *CGame::GetExplosion(void)
{
	return m_pExplosion;
}

//============================
//�G�̏��擾
//============================
CEnemy *CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//============================
//�G�̏��擾
//============================
CAbg *CGame::GetAbg(void)
{
	return m_pAbg;
}

//============================
//�G�t�F�N�g�̏��擾
//============================
CEffect *CGame::GetEffect(void)
{
	return m_pEffect;
}

//============================
//�X�R�A�̏��擾
//============================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//============================
//�^�C���̏��擾
//============================
CTime *CGame::GetTime(void)
{
	return m_pTime;
}

//============================
//�u���b�N�̏��擾
//============================
CBlock *CGame::GetBlock(void)
{
	return m_pBlock;
}

//============================
//�J�����̏��擾
//============================
CCamera *CGame::GetCamera(void)
{
	return m_pCamera;
}

//============================
//���C�g�̏��擾
//============================
CLight *CGame::GetLight(void)
{
	return m_pLight;
}



//============================
//�I�u�W�F�N�gX�̏��擾
//============================
CObjectx *CGame::GetObjectx(void)
{
	return m_pObjectx[0];
}

//============================
//���f���̏��擾
//============================
CModel *CGame::GetModel(void)
{
	return m_pModel;
}

//============================
//�������̏��擾
//============================
CInfection *CGame::GetInfection(void)
{
	return m_pInfection;
}

//============================
//�I�u�W�F�N�g3D���̏��擾
//============================
CObject3d *CGame::GetObject3d(void)
{
	return m_pObject3d;
}



