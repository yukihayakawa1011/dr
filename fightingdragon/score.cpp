//============================
//
//�X�R�A����(score.cpp)
//Author:���� �F�M
//
//============================
#include "score.h"  
//#include "bullet.h"
#include "enemy.h"
#include "manager.h"
#include "object2D.h"
#include "renderer.h"
#include "debugproc.h"
//#include "sound.h"

LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;  //�e�N�X�`���̃|�C���^

//=============================
//�R���X�g���N�^
//=============================
CScore::CScore()
{
	m_nScore = 0;								//�X�R�A�̒l
	m_nWindth = 0.0f;							//���̒l
	m_nHeight = 0.0f;							//�����̒l
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_pNumber[nCnt] = NULL;
	}
}

//=============================
//�f�X�g���N�^
//=============================
CScore::~CScore()
{

}

//============================
//�e�N�X�`���̐���(�ǂݍ���)
//============================
HRESULT CScore::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\time.png",
		&m_pTexture);

	return S_OK;
}

//============================
//�e�N�X�`���̔j��
//============================
void CScore::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	
}

//============================
//��������
//============================
CScore *CScore::Create(D3DXVECTOR3 pos, float fRot, int nTex)
{
	CScore *pScore;

	nTex = 0;

	//�I�u�W�F�N�g2D�̐���
	pScore = NEW_DBG CScore;

	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		//����������
		pScore->Init(D3DXVECTOR3(100.0f * nCnt, pos.y, pos.z), fRot, nCnt);
	}

	return pScore;
}

//=============================
//  �X�R�A�̏�����
//=============================
HRESULT CScore::Init(D3DXVECTOR3 pos, float fRot, int nTex)
{
	if (m_pNumber[nTex] == NULL)
	{
		m_pNumber[nTex] = NEW_DBG CNumber;

		m_pNumber[nTex]->Init(pos, fRot, nTex);

		//��ނ�ݒ�
		SetType(CObject::TYPE_SCORE);

		//�e�N�X�`��������
		m_pNumber[nTex]->BindTexture(m_pTexture);

		m_nScore = 0;

		//VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

		///*���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾*/
		//m_pNumber[nTex]->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		////���_���W�̐ݒ�
		//pVtx[0].pos = D3DXVECTOR3(pos.x - 60.0f, pos.y - 60.0f, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(pos.x + 60.0f, pos.y - 60.0f, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(pos.x - 60.0f, pos.y + 60.0f, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(pos.x + 60.0f, pos.y + 60.0f, 0.0f);

		////rhw(�@��)�̐ݒ�
		//pVtx[0].rhw = 1.0f;
		//pVtx[1].rhw = 1.0f;
		//pVtx[2].rhw = 1.0f;
		//pVtx[3].rhw = 1.0f;

		////���_�J���[�̐ݒ�
		//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		////�e�N�X�`�����W�̐ݒ�
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//m_pNumber[nTex]->SetPosition(pos);

		////���_�o�b�t�@���A�����b�N����
		//m_pNumber[nTex]->GetBuff()->Unlock();
	}

	return S_OK;
}

//=====================
//�X�R�A�̏I������
//=====================
void CScore::Uninit(void)
{
	CNumber::Release();
}

//�X�R�A�̍X�V����
void  CScore::Update(void)
{
	//�f�o�b�O�\���̏���n��
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProck();

	SetPos(D3DXVECTOR3(1000.0f, 50.0f, 0.0f), 50.0f, 50.0f);

	int aTexU[NUM_PLACE];

	//�X�R�A�̏��
	if (m_nScore >= 9999)
	{
		m_nScore = 9999;
	}

	aTexU[0] = m_nScore % 10000 / 1000;
	aTexU[1] = m_nScore % 1000 / 100;
	aTexU[2] = m_nScore % 100 / 10;
	aTexU[3] = m_nScore % 10 / 1;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	for (int nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pNumber[nCntScore]->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);

		//���_�o�b�t�@���A�����b�N����
		m_pNumber[nCntScore]->GetBuff()->Unlock();
	}

#ifdef _DEBUG
	pDebug->Print("�X�R�A�̐��l : %d\n", m_nScore);
#endif
}

//�X�R�A�̕`�揈��
void  CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_pNumber[nCnt]->Draw();
	}
}

//===============================
//�X�R�A�̉��Z
//===============================
void CScore::Add(int nScore)
{
	int aTexU[NUM_PLACE];  //�e���̐������i�[
	//int nCntScore;

 	m_nScore += nScore;

	//�X�R�A�̏��
	if (m_nScore >= 9999)
	{
		m_nScore = 9999;
	}

	aTexU[0] = m_nScore % 10000 / 1000;
	aTexU[1] = m_nScore % 1000 / 100;
	aTexU[2] = m_nScore % 100 / 10;
	aTexU[3] = m_nScore % 10 / 1;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	for (int nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pNumber[nCntScore]->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aTexU[nCntScore] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aTexU[nCntScore] * 0.1f), 1.0f);

		//���_�o�b�t�@���A�����b�N����
		m_pNumber[nCntScore]->GetBuff()->Unlock();
	}
}

//================================
//�X�R�A���󂯎��
//===============================
int  CScore::Get(void)
{
	return m_nScore;
}

//==================================
//�X�R�A�̐ݒ�
//==================================
void  CScore::SetPos(D3DXVECTOR3 pos, float nWINDTH, float nHeight)
{
	SetPosition(pos);
	
	m_nWindth = nWINDTH;
	
	m_nHeight = nHeight;

	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	for (int nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pNumber[nCntScore]->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(pos.x - 50.0f + (nCntScore * POS_SCORE), pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + 50.0f + (nCntScore * POS_SCORE), pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - 50.0f + (nCntScore * POS_SCORE), pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + 50.0f + (nCntScore * POS_SCORE), pos.y + 50.0f, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		m_pNumber[nCntScore]->GetBuff()->Unlock();
	}
}

