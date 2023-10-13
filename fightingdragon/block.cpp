//============================
//
//�u���b�N����(block.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include "bg.h"
//#include "bullet.h"
//#include "explosion.h"
#include "block.h"
#include "renderer.h"
#include "player.h"
#include "mode.h"

//�}�N��
#define BLOCK_X (200.0f)
#define BLOCK_Y (20.0f)
#define BLOCK_HEIGHT (20.0f)

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9  CBlock::m_pTexture = {};

//CObject2D *CBlock::m_apBlock = NULL;
//============================
//�R���X�g���N�^
//============================
CBlock::CBlock()
{
	
}

CBlock::CBlock(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//�f�X�g���N�^
//============================
CBlock::~CBlock()
{

}

//============================
//�e�N�X�`���̐���(�ǂݍ���)
//============================
HRESULT CBlock::Load(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\images.jpg",
		&m_pTexture);

	return S_OK;
}

//============================
//�e�N�X�`���̔j��
//============================
void CBlock::Unload(void)
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
CBlock *CBlock::Create(D3DXVECTOR3 pos, float fRot, int nTex,float fWidth, float fHeight)
{
	CBlock *pBlock;

	//�I�u�W�F�N�g2D�̐���
	pBlock = NEW_DBG CBlock(pos);

	//����������
	pBlock->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex,fWidth,fHeight);

	////�e�N�X�`���̊��蓖��
	//pBlock->BindTexture(m_pTexture);

	return pBlock;
}

//============================
//�|���S���̏�����
//============================
HRESULT CBlock::Init(D3DXVECTOR3 pos, float fRot, int nTex,float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	CObjectx::Init(pos, fRot, nTex,fWidth,fHeight);

	if (nTex == 0)
	{
		//��ނ�ݒ�
		SetType(CObject::TYPE_BLOCK);
	}
	if (nTex == 1)
	{
		//��ނ�ݒ�
		SetType(CObject::TYPE_FLOOR);
	}

	if (nTex == 2)
	{
		//��ނ�ݒ�
		SetType(CObject::TYPE_LONGFLOOR);
	}

	//m_nLife = 100;


	SetPosition(pos);

	return S_OK;
}
//============================
//�|���S���̏I��
//============================
void CBlock::Uninit(void)
{
	CObjectx::Uninit();
}
//============================
//�|���S���̍X�V
//============================
void CBlock::Update(void)
{

}
//============================
//�|���S���̕`��
//============================
void CBlock::Draw(void)
{
	CObjectx::Draw();
}


//===============================
//�u���b�N�̓����蔻��
//===============================
bool CBlock::colision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, bool bJump)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	/*int nCntBlock;*/
	bool bLand = false; //���n�������ǂ���

	/*for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{*/
     	D3DXVECTOR3 pos = GetPosition();

	bJump = pPlayer->GetJump();

	if (bJump == true)
	{//�W�����v���g�p����Ă�����
		if (pPos->y >= pos.y - BLOCK_Y
			&& pPos->y - fHeight <= pos.y + BLOCK_Y)
		{//�u���b�N��Y�͈͓̔��̎�,���̓����蔻��
			if (pPosOld->x + fWidth <= pos.x - BLOCK_X
				&&pPos->x + fWidth >= pos.x - BLOCK_X)
			{
				pPos->x = pos.x - BLOCK_X - fWidth;
				pMove->x = 0.0f; //�ړ��ʂ�0�ɂ���
			}

			if (pPosOld->x - fWidth >= pos.x + BLOCK_X
				&& pPos->x - fWidth < pos.x + BLOCK_X)
			{
				pPos->x = pos.x + BLOCK_X + fWidth;
				pMove->x = 0.0f; //�ړ��ʂ�0�ɂ���
			}
		}

		if (pPos->x - fWidth <= pos.x + BLOCK_X
			&& pPos->x + fWidth >= pos.x - BLOCK_X)
		{//�u���b�N�͈͓̔��̎�,�c�̓����蔻��
			if (pPosOld->y <= pos.y - BLOCK_Y
				&& pPos->y > pos.y - BLOCK_Y )
			{
				bJump = false;
				pPlayer->SetJump(bJump);
				bLand = true;
				pPos->y = pos.y - BLOCK_Y; //�u���b�N�̏�ɗ�������
				pMove->y = 0.0f; //�ړ��ʂ�0�ɂ���
			}

			if (pPosOld->y - fHeight >= pos.y + BLOCK_Y + 30
				&& pPos->y - fHeight <= pos.y + BLOCK_Y + 30)
			{//�u���b�N��艺�Ŕ͈͓��̎�
				pPos->y = +pos.y + BLOCK_Y + fHeight + 30;
				pMove->y = 0.0f; //�ړ��ʂ�0�ɂ���
			}
		}
	}

	else
	{//�W�����v���g�p����Ă��Ȃ�������
		if (pPos->x - fWidth <= pos.x + BLOCK_X
			&& pPos->x + fWidth >= pos.x - BLOCK_X)
		{//�u���b�N�͈͓̔��̎�,�c�̓����蔻��
			if (pPosOld->y <= pos.y - BLOCK_Y
				&& pPos->y >= pos.y - BLOCK_Y)
			{
				bJump = false;
				pPlayer->SetJump(bJump);
				bLand = true;
				pPos->y = pos.y - BLOCK_Y; //�u���b�N�̏�ɗ�������
				pMove->y = 0.0f; //�ړ��ʂ�0�ɂ���
			}

			if (pPosOld->y - fHeight >= pos.y + BLOCK_Y + 30
				&& pPos->y - fHeight <= pos.y + BLOCK_Y + 30)
			{//�u���b�N��艺�Ŕ͈͓��̎�
				pPos->y = pos.y + BLOCK_Y + fHeight + 30;
				pMove->y = 0.0f; //�ړ��ʂ�0�ɂ���
			}
		}

		if (pPos->y >= pos.y - BLOCK_Y
			&& pPos->y - fHeight <= pos.y + BLOCK_Y)
		{//�u���b�N��Y�͈͓̔��̎�,���̓����蔻��
			if (pPosOld->x + fWidth <= pos.x - BLOCK_X
				&&pPos->x + fWidth > pos.x - BLOCK_X)
			{
				pPos->x = pos.x - BLOCK_X - fWidth;
				pMove->x = 0.0f; //�ړ��ʂ�0�ɂ���
			}

			if (pPosOld->x - fWidth > pos.x + BLOCK_X
				&& pPos->x - fWidth <= pos.x + BLOCK_X)
			{
				pPos->x = pos.x + BLOCK_X + fWidth;
				pMove->x = 0.0f; //�ړ��ʂ�0�ɂ���
			}
		}
	}

	/*SetPosition(pos);*/
//}
	/*}*/
	return bLand;
}
