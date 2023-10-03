//============================
//
//���[�V��������(motion.cpp)
//Author:���� �F�M
//
//============================
#include "main.h"
#include "model.h"
#include "renderer.h"
#include "motion.h"

//============================
//�R���X�g���N�^
//============================
CMotion::CMotion()
{
	m_nNumAll = 0;				//���̍ő吔
	m_nType = 0;			//���
	bLoop = false;							//�I�����邩�ǂ���
	m_nKey = 0;								//�L�[�̐�
	m_nCounter = 0;						//���[�V�����J�E���^�[
	m_bFinish = false;						//�I�����邩�ǂ���

	m_nNumModel = 0;						//���[�V�����̑���
}

//============================
//�f�X�g���N�^
//============================
CMotion::~CMotion()
{

}

//============================
//��������
//============================
CMotion *CMotion::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CMotion *pModel;

	//�I�u�W�F�N�g2D�̐���
	pModel = NEW_DBG CMotion;

	//����������
	pModel->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex, fWidth, fHeight);

	return pModel;
}

//====================
//���[�V�����̏�����
//====================
HRESULT CMotion::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	////�f�o�C�X�̎擾
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	fHeight = 0.0f;
	fWidth = 0.0f;
	nTex = 0;
	fRot = 0.0f;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================
//���[�V�����ݒ�
//=============================
void CMotion::Set(int nType)
{
	m_aInfo[MAX_PARTS];						//�p�[�c�̍ő吔
	m_nType = nType;						//���
	bLoop = true;							//�I�����邩�ǂ���
	m_nKey = 0;								//�L�[�̐�
	m_nCounter = 1;						//���[�V�����J�E���^�[
	m_bFinish = false;						//�I�����邩�ǂ���

	m_nNumAll = 0;				//���̍ő吔

	m_nNumModel = 2;						//���[�V�����̑���

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_aInfo[nCnt].nNumKey = 1;
		m_aInfo[nCnt].aKeyinfo[m_nKey].nFrame = 1;
	}

	//�S���[�V����(�p�[�c)�̏����ݒ�
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		D3DXVECTOR3 pos;
					   
		D3DXVECTOR3 rot;

		//�p�[�c�̈ʒu�E������ݒ�
		pos = D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fPosX,
			m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fPosY,
			m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fPosZ);

		rot = D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fRotX,
			m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fRotY,
			m_aInfo[m_nType].aKeyinfo[nCntModel].aKey[nCntModel].m_fRotZ);
	}
}

//���[�V�����̏I������
void CMotion::Uninit(void)
{
	
}

//���[�V�����̍X�V����
void CMotion::Update(void)
{
	float fDiff; //���[�V�����̍��������߂�

	//�S���f���̍X�V(�p�[�c)�̍X�V
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		int nNextKey = m_nKey + 1;

		if (nNextKey > m_aInfo[m_nType].nNumKey)
		{
			nNextKey = 0;
		}

		//�L�[�̍��������߂�
		fDiff = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_frotDestX
			- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_frotDestX;

		//�p�[�c�̈ʒu�⍷�����v�Z����
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = (float)m_nKey + fDiff * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
																										  
		//�p�[�c�̈ʒu�E������ݒ�
		m_ppModel[nCntModel]->SetPos(D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX,
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY, m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ));

		m_ppModel[nCntModel]->SetRot(D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX,
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY, m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ));

		switch (m_nType)
		{
		case MOTIONTYPE_NEUTRAL:

			if (m_nKey == 0)
			{
				//�ЂƂڂ̃p�[�c(�X�J�[�g)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ӂ��ڂ̃p�[�c(��)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�݂��ڂ̃p�[�c(��)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(����)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���ڂ̃p�[�c(���r)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ނ��ڂ̃p�[�c(����)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ȂȂڂ̃p�[�c(�E��)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -1.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(�E�r)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.8f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�����̂ڂ̃p�[�c(�E��)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//��������ڂ̃p�[�c(���r)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�������ڂ̃p�[�c(����)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�ɖڂ̃p�[�c(�E�r)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ����ڂ̃p�[�c(�E��)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 180)
				{
					m_nKey = 1;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 1)
			{
				//�ЂƂڂ̃p�[�c(�X�J�[�g)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ӂ��ڂ̃p�[�c(��)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�݂��ڂ̃p�[�c(��)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(����)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���ڂ̃p�[�c(���r)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ނ��ڂ̃p�[�c(����)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ȂȂڂ̃p�[�c(�E��)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -1.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(�E�r)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.8f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�����̂ڂ̃p�[�c(�E��)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//��������ڂ̃p�[�c(���r)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�������ڂ̃p�[�c(����)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�ɖڂ̃p�[�c(�E�r)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ����ڂ̃p�[�c(�E��)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 180)
				{
					m_nKey = 2;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 2)
			{
				//�ЂƂڂ̃p�[�c(�X�J�[�g)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ӂ��ڂ̃p�[�c(��)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�݂��ڂ̃p�[�c(��)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(����)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���ڂ̃p�[�c(���r)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ނ��ڂ̃p�[�c(����)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ȂȂڂ̃p�[�c(�E��)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -1.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(�E�r)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;
						
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.8f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�����̂ڂ̃p�[�c(�E��)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//��������ڂ̃p�[�c(���r)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�������ڂ̃p�[�c(����)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�ɖڂ̃p�[�c(�E�r)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ����ڂ̃p�[�c(�E��)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						 
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 180)
				{
					m_nKey = 3;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 3)
			{
				//�ЂƂڂ̃p�[�c(�X�J�[�g)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ӂ��ڂ̃p�[�c(��)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�݂��ڂ̃p�[�c(��)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.5f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(����)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���ڂ̃p�[�c(���r)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ނ��ڂ̃p�[�c(����)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ȂȂڂ̃p�[�c(�E��)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -1.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(�E�r)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = -0.8f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�����̂ڂ̃p�[�c(�E��)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//��������ڂ̃p�[�c(���r)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�������ڂ̃p�[�c(����)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.5f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�ɖڂ̃p�[�c(�E�r)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ����ڂ̃p�[�c(�E��)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						 
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;
			}

			break;

		case MOTIONTYPE_MOVE:

			if (m_nKey == 0)
			{
				//�ЂƂڂ̃p�[�c(�X�J�[�g)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ӂ��ڂ̃p�[�c(��)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�݂��ڂ̃p�[�c(��)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(����)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���ڂ̃p�[�c(���r)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 2.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ނ��ڂ̃p�[�c(����)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ȂȂڂ̃p�[�c(�E��)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(�E�r)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;
						
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;
				
				//�����̂ڂ̃p�[�c(�E��)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//��������ڂ̃p�[�c(���r)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�������ڂ̃p�[�c(����)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�ɖڂ̃p�[�c(�E�r)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						 
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = -1.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ����ڂ̃p�[�c(�E��)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;
						 
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 60)
				{
					m_nKey = 1;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 1)
			{
				//�ЂƂڂ̃p�[�c(�X�J�[�g)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				//�ӂ��ڂ̃p�[�c(��)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�݂��ڂ̃p�[�c(��)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(����)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���ڂ̃p�[�c(���r)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 2.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ނ��ڂ̃p�[�c(����)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ȂȂڂ̃p�[�c(�E��)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(�E�r)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�����̂ڂ̃p�[�c(�E��)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//��������ڂ̃p�[�c(���r)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�������ڂ̃p�[�c(����)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�ɖڂ̃p�[�c(�E�r)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = -1.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ����ڂ̃p�[�c(�E��)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 60)
				{
					m_nKey = 2;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 2)
			{
				//�ЂƂڂ̃p�[�c(�X�J�[�g)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				//�ӂ��ڂ̃p�[�c(��)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�݂��ڂ̃p�[�c(��)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(����)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���ڂ̃p�[�c(���r)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 2.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ނ��ڂ̃p�[�c(����)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ȂȂڂ̃p�[�c(�E��)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(�E�r)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�����̂ڂ̃p�[�c(�E��)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//��������ڂ̃p�[�c(���r)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�������ڂ̃p�[�c(����)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�ɖڂ̃p�[�c(�E�r)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = -1.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 1.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ����ڂ̃p�[�c(�E��)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame++;

				if (m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame > 60)
				{
					m_nKey = 3;

					m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
				}
			}

			else if (m_nKey == 3)
			{
				//�ЂƂڂ̃p�[�c(�X�J�[�g)
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 8.0f;
				m_aInfo[0].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				//�ӂ��ڂ̃p�[�c(��)
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 15.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[1].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�݂��ڂ̃p�[�c(��)
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 20.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[2].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(����)
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 4.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[3].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���ڂ̃p�[�c(���r)
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 2.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[4].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ނ��ڂ̃p�[�c(����)
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 6.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[5].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�ȂȂڂ̃p�[�c(�E��)
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -4.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 3.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[6].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//����ڂ̃p�[�c(�E�r)
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -5.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 1.0f;

				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[7].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//�����̂ڂ̃p�[�c(�E��)
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -6.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[8].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//��������ڂ̃p�[�c(���r)
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 2.5f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 1.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[9].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�������ڂ̃p�[�c(����)
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[10].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ�ɖڂ̃p�[�c(�E�r)
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = -2.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = -1.5f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[11].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				//���イ����ڂ̃p�[�c(�E��)
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = -5.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = 0.0f;

				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = 0.0f;
				m_aInfo[12].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = 0.0f;

				m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame = 1;
			}
			break;
		}

	}

	//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�
	m_nCounter++;

	m_nKey = 0;

	m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
}

//==========================
//���[�V�����̎�ނ��擾
//==========================
int CMotion::GetType(void)
{
	return m_nType;
}

//==========================
//���[�V�����I�����邩�ǂ���
//==========================
bool CMotion::IsFinish(void)
{
	return m_bFinish;
}

//==========================
//Info�ݒ�
//==========================
void CMotion::SetInfo(INFO info)
{
	m_aInfo[0] = info;
}
