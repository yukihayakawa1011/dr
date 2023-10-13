//============================
//
//�v���C���[����(player.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include "bg.h"
#include "input.h"
#include "player.h"
//#include "bullet.h"
#include "sound.h"
#include "score.h"
#include "block.h"
#include "renderer.h"
#include "bilboard.h"
#include "debugproc.h"
#include "enemy.h"
#include "particle.h"
#include "time.h"
#include "mode.h"

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9  CPlayer::m_pTexture;
//============================
//�R���X�g���N�^
//============================
CPlayer::CPlayer()
{
	m_fLength = 0.0f;
	m_movefLength = 0.0f;
	m_fAngle = 0.0f;
	m_posold = D3DXVECTOR3(0.0f,0.0f,0.0f);						//�Â��ʒu
	m_bJump = false;											//�W�����v�����ǂ���
	m_fWidth = 0.0f;											//�v���C���[�����N���A
	m_fHeight = 0.0f;											//�v���C���[�������N���A
	m_nNumModel = 0;											//���f���̍ő吔���N���A
	m_bDeath = false;											//�v���C���[�̐���������N���A
	m_ShotRot = 0.0f;											//�e�̕������N���A
	m_bRot = false;												//�v���C���[�̌������N���A
	m_bAim = false;												//�v���C���[���G�C�����Ă邩�ǂ������N���A
	m_nLife = 0;												//�v���C���[�̗̑͂��N���A
	m_PlayerState = PLAYER_NONE;								//�v���C���[�̏�Ԃ��N���A
	m_stateCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);				//�F���N���A
	m_nCntState = 0;											//�v���C���[��ԃJ�E���g���N���A

	m_nNumAll = 0;				//���̍ő吔
	m_nType = 0;			//���
	bLoop = false;							//�I�����邩�ǂ���
	m_nKey = 0;								//�L�[�̐�
	m_nCounter = 0;						//���[�V�����J�E���^�[
	m_bFinish = false;						//�I�����邩�ǂ���
	m_bAttack = false;						//�U����Ԃɓ����Ă��邩�ǂ������N���A

	m_nNumModel = 0;						//���[�V�����̑���

	nPunchSpeed = 0;						//�p���`�Ԋu

	/*for (int nCnt = 0; nCnt < MOTIONTYPE_MAX; nCnt++)
	{
		m_aInfo[nCnt].nNumKey = 0;
		m_aInfo[nCnt].aKeyinfo[nCnt + 1].nFrame = 0;
	}

	m_aInfo[m_nType].aKeyinfo[nNextKey].nFrame;*/

	memset(&m_InitPartPos[0], NULL, sizeof(D3DXVECTOR3));

	memset(&m_aInfo[0], NULL, sizeof(m_aInfo));

	m_nFrameCnt = 0;

	/*�v���C���[�ʏ�ϐ��̃N���A
	m_NoneMat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_NoneMat.MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_NoneMat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	�v���C���[��Ԃ�������ϐ��̃N���A
	m_RedMat.MatD3D.Ambient = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_RedMat.MatD3D.Diffuse = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_RedMat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	�v���C���[�𔖂�������ϐ��̃N���A
	m_InvincibleMat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_InvincibleMat.MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_InvincibleMat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);*/
	/*m_nldxShadow = 0;*/
}

//============================
//�f�X�g���N�^
//============================
CPlayer::~CPlayer()
{

}

////============================
////�e�N�X�`���̐���(�ǂݍ���)
////============================
//HRESULT CPlayer::Load(void)
//{
//	//�f�o�C�X�̎擾
//	CRenderer *pRenderer = CManager::GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	//�e�N�X�`���̓ǂݍ���
//			D3DXCreateTextureFromFile(pDevice,
//				"data\\TEXTURE\\raginee.png",
//				&m_pTexture);
//
//	return S_OK;
//}
//
////============================
////�e�N�X�`���̔j��
////============================
//void CPlayer::Unload(void)
//{
//	//�e�N�X�`���̔j��
//	if (m_pTexture != NULL)
//	{
//		m_pTexture->Release();
//		m_pTexture = NULL;
//	}
//}

//============================
//��������
//============================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CPlayer *pPlayer;

	//�I�u�W�F�N�g2D�̐���
	pPlayer = NEW_DBG CPlayer;

	//����������
	pPlayer->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex,fWidth,fHeight);

	////�e�N�X�`���̊��蓖��
	//pPlayer->BindTexture(m_pTexture);

	return pPlayer;
}

//============================
//�|���S���̏�����
//============================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	/*m_nldxShadow = SetShadow();

	m_pMotion = NEW_DBG CMotion;

	m_pMotion->Init(pos, fRot, nTex, fWidth, fHeight);*/

	//fHeight = 0.0f;
	//fWidth = 0.0f;
	//nTex = 0;
	//fRot = 0.0f;
	//pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	nPunchSpeed = PLAYER_PUNCH_SPEED;

	m_nKey = 0;								//�L�[�̐�

	m_nFrameCnt = 0;

	m_stateCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	SetPosition(pos);

	nTex = 0;

	m_bDeath = false;	//�v���C���[�����񂾂��ǂ���������

	m_bRot = false;		//�v���C���[�̌�������������

	m_bJump = false;	//�v���C���[�̃W�����v����������

	SetJump(m_bJump);

	m_ShotRot = 50.0f;   //�e�̕�����������

	m_nLife = 3;		 //���C�t��������

	m_PlayerState = PLAYER_NONE;	//�v���C���[�̏�Ԃ�������

	m_nCntState = 120;				//�v���C���[��ԃJ�E���g��������

	m_bAttack = false;				//�U����Ԃ��ǂ�����������

	for (int nCntInfo = 0; nCntInfo < MAX_PART; nCntInfo++)
	{
		m_aInfo[nCntInfo].nNumKey = 0;

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			m_aInfo[nCntInfo].aKeyinfo[nCnt].nFrame = 60;
		}
	}

	/*SetRot(D3DXVECTOR3(0.0f,0.0f,0.0f));*/

	//�S�Ẵp�[�c����������
	m_nNumModel = MAX_PART;

	/*if (m_player_mode[nTex] == PLAYER_PLAYER)
	{*/
		//���f������
		m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 32.0f, 0.0f), fRot, 0, fWidth, fHeight,0);
		m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), fRot, 1, fWidth, fHeight, 0);
		m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 18.0f, 0.0f), fRot, 2, fWidth, fHeight, 0);
		m_apModel[3] = CModel::Create(D3DXVECTOR3(2.0f, -9.0f, -0.9f), fRot, 3, fWidth, fHeight, 0);
		m_apModel[4] = CModel::Create(D3DXVECTOR3(0.3f, -12.0f, 0.0f), fRot, 4, fWidth, fHeight, 0);
		m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 5, fWidth, fHeight, 0);
		m_apModel[6] = CModel::Create(D3DXVECTOR3(-2.0f, -9.0f, -0.9f), fRot, 6, fWidth, fHeight, 0);
		m_apModel[7] = CModel::Create(D3DXVECTOR3(0.3f, -12.0f, 0.0f), fRot, 7, fWidth, fHeight,0);
		m_apModel[8] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 8, fWidth, fHeight,0);
		m_apModel[9] = CModel::Create(D3DXVECTOR3(5.0f, 15.0f, -1.0f), fRot, 9, fWidth, fHeight,0);
		m_apModel[10] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), fRot, 10, fWidth, fHeight,0);
		m_apModel[11] = CModel::Create(D3DXVECTOR3(5.7f, 0.0f, 0.0f), fRot, 11, fWidth, fHeight,0);
		m_apModel[12] = CModel::Create(D3DXVECTOR3(6.0f, 0.0f, 0.0f), fRot, 12, fWidth, fHeight,0);
		m_apModel[13] = CModel::Create(D3DXVECTOR3(-5.0f, 15.0f, -1.0f), fRot, 13, fWidth, fHeight, 0);
		m_apModel[14] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.5f), fRot, 14, fWidth, fHeight, 0);
		m_apModel[15] = CModel::Create(D3DXVECTOR3(-5.7f, 0.0f, -0.5f), fRot, 15, fWidth, fHeight, 0);
		m_apModel[16] = CModel::Create(D3DXVECTOR3(-6.0f, 0.0f, 0.0f), fRot, 16, fWidth, fHeight, 0);
		/*m_apModel[17] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), fRot, 17, fWidth, fHeight);*/
	//}

	//if (m_player_mode[nTex] == PLAYER_MIRROR)
	//{
	//	//���f������
	//	m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 38.0f, 0.0f), fRot, 0, fWidth, fHeight);
	//	m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, -1.0f, 0.0f), fRot, 1, fWidth, fHeight);
	//	m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 18.0f, 0.0f), fRot, 2, fWidth, fHeight);
	//	m_apModel[3] = CModel::Create(D3DXVECTOR3(4.0f, -10.0f, 0.0f), fRot, 3, fWidth, fHeight);
	//	m_apModel[4] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 0.0f), fRot, 4, fWidth, fHeight);
	//	m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 5, fWidth, fHeight);
	//	m_apModel[6] = CModel::Create(D3DXVECTOR3(-4.0f, -10.0f, 0.0f), fRot, 6, fWidth, fHeight);
	//	m_apModel[7] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 1.0f), fRot, 7, fWidth, fHeight);
	//	m_apModel[8] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 8, fWidth, fHeight);
	//	m_apModel[9] = CModel::Create(D3DXVECTOR3(5.0f, 15.0f, -1.0f), fRot, 9, fWidth, fHeight);
	//	m_apModel[10] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), fRot, 10, fWidth, fHeight);
	//	m_apModel[11] = CModel::Create(D3DXVECTOR3(5.7f, 0.0f, 0.0f), fRot, 11, fWidth, fHeight);
	//	m_apModel[12] = CModel::Create(D3DXVECTOR3(6.0f, 0.0f, 0.0f), fRot, 12, fWidth, fHeight);
	//	m_apModel[13] = CModel::Create(D3DXVECTOR3(-5.0f, 15.0f, -1.0f), fRot, 13, fWidth, fHeight);
	//	m_apModel[14] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.5f), fRot, 14, fWidth, fHeight);
	//	m_apModel[15] = CModel::Create(D3DXVECTOR3(-5.7f, 0.0f, -0.5f), fRot, 15, fWidth, fHeight);
	//	m_apModel[16] = CModel::Create(D3DXVECTOR3(-6.0f, 0.0f, 0.0f), fRot, 16, fWidth, fHeight);
	//	m_apModel[17] = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), fRot, 17, fWidth, fHeight);
	//}

		for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
		{
			m_InitPartPos[nCnt] = m_apModel[nCnt]->GetPos();
		}

	//�e���f���̐ݒ�(�S�p�[�c��)
	m_apModel[0]->SetParent(NULL);
	m_apModel[1]->SetParent(m_apModel[0]);
	m_apModel[2]->SetParent(m_apModel[1]);
	m_apModel[3]->SetParent(m_apModel[0]);
	m_apModel[4]->SetParent(m_apModel[3]);
	m_apModel[5]->SetParent(m_apModel[4]);
	m_apModel[6]->SetParent(m_apModel[0]);
	m_apModel[7]->SetParent(m_apModel[6]);
	m_apModel[8]->SetParent(m_apModel[7]);
	m_apModel[9]->SetParent(m_apModel[1]);
	m_apModel[10]->SetParent(m_apModel[9]);
	m_apModel[11]->SetParent(m_apModel[10]);
	m_apModel[12]->SetParent(m_apModel[11]);
	m_apModel[13]->SetParent(m_apModel[1]);
	m_apModel[14]->SetParent(m_apModel[13]);
	m_apModel[15]->SetParent(m_apModel[14]);
	m_apModel[16]->SetParent(m_apModel[15]);
	//m_apModel[17]->SetParent(m_apModel[16]);

	/*CObjectx::Init(pos, fRot, nTex, fWidth, fHeight);*/

	//��ނ̐ݒ�
	SetType(CObject::TYPE_PLAYER);

	////�Ίp���̒������Z�o����
	//m_fLength = sqrtf(fWidth * fWidth + fHeight * fHeight) * 0.5f;

	////�Ίp���̊p�x���Z�o����
	//m_fAngle = atan2f(fWidth, fHeight);

	////���_�o�b�t�@�̐���
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&m_pVtxBuff,
	//	NULL);

	////���_�o�b�t�@��NULL��������
	//if (m_pVtxBuff == NULL)
	//{
	//	return E_FAIL;
	//}

	////�e�N�X�`���̃|�C���^��NULL��������
	//if (m_pTexture == NULL)
	//{
	//	return E_FAIL;
	//}

	//VERTEX_3D *pVtx;    //���_���ւ̃|�C���^

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y, 0.0f);


	////////�p�x�����߂�
	//////m_fAngle = atan2f(pos.x * 2, pos.y * 2);

	////////�������Z�o����
	//////m_fLength = sqrtf(pos.x * pos.x * 4 + pos.y * pos.y * 4) * 0.5f;

	////////���_���W�̐ݒ�
	//////pVtx[0].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//////pVtx[0].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//////pVtx[0].pos.z = 0.0f;			   

	//////pVtx[1].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//////pVtx[1].pos.y = pos.y - cosf(fRot + m_fAngle) * m_fLength;
	//////pVtx[1].pos.z = 0.0f;			    

	//////pVtx[2].pos.x = pos.x - sinf(fRot + m_fAngle) * m_fLength;
	//////pVtx[2].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//////pVtx[2].pos.z = 0.0f;			    

	//////pVtx[3].pos.x = pos.x + sinf(fRot + m_fAngle) * m_fLength;
	//////pVtx[3].pos.y = pos.y + cosf(fRot + m_fAngle) * m_fLength;
	//////pVtx[3].pos.z = 0.0f;

	//// �@���x�N�g���̐ݒ�
	//pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();

	SetPosition(pos);

	SetRot(D3DXVECTOR3(0.0f,fRot,0.0f));

	SetDeath(m_bDeath);

	m_fWidth = fWidth;

	m_fHeight = fHeight;

	SetLife(m_nLife);

	SetState(m_PlayerState);

	SetMotionPlayer(MOTIONTYPE_NEUTRAL);

	return S_OK;
}
//============================
//�|���S���̏I��
//============================
void CPlayer::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PART; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			delete m_apModel[nCnt];

			m_apModel[nCnt] = NULL;
		}
	}

	/*if (m_pMotion != NULL)
	{
		delete m_pMotion;

		m_pMotion = NULL;
	}*/

	this->Release();
}
//============================
//�|���S���̍X�V
//============================
void CPlayer::Update(void)
{
	if (m_bDeath == false)
	{
		//////�������擾
		////m_fHeight = CObject3d::get

		//�f�o�b�O�\���̏���n��
		CDebugProc *pDebug = CManager::GetDebugProck();

		D3DXVECTOR3 pos = GetPosition();

		m_posold = pos; //�O��̈ʒu���L�^

		D3DXVECTOR3 rot = GetRot();

		CInputKeyboard *pInputKeyboard;
		CInputGamePad *pInputGamepad;

		CScore *pScore;

		//�X�R�A�̎擾
		pScore = CGame::GetScore();

		//�L�[�{�[�h�̎擾
		pInputKeyboard = CManager::GetInputKeyboard();

		pInputGamepad = CManager::GetGamePad();

		D3DXVECTOR3 move = GetMove();

		////��{�j���[�g�����ɐݒ�
		//m_pMotion->Set(0);

		////���[�V�����̍X�V
		//m_pMotion->Update();

		int nState = 0;
		m_PlayerState = GetState();
		if (m_bDeath == false)
		{
			if(m_PlayerState == PLAYER_NONE || m_PlayerState == PLAYER_GURD)
			{ 
				if (m_PlayerState != PLAYER_GURD)
				{
					if (pInputKeyboard->GetPless(DIK_A) == true || pInputGamepad->GetGameStickL_X_Press(pInputGamepad->BUTTON_STICK_LX, 0) <= -1)
					{//A�L�[�������ꂽ

						move.x = -1.0f;

						m_bRot = false;

						if (m_nType != MOTIONTYPE_MOVE)
						{
							SetMotionPlayer(MOTIONTYPE_MOVE);
						}
					}

					else if (pInputKeyboard->GetPless(DIK_D) == true || pInputGamepad->GetGameStickL_X_Press(pInputGamepad->BUTTON_STICK_LX, 0) >= 1)
					{//D�L�[�������ꂽ
						move.x = 1.0f;

						m_bRot = true;

						if (m_nType != MOTIONTYPE_MOVE)
						{
							SetMotionPlayer(MOTIONTYPE_MOVE);
						}
					}

					//�v���C���[�̃p���`���������ǂ���
					else if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_A, 0) == true)
					{
						/*for (int nCnt = 0; nCnt <= PLAYER_PUNCH_SPEED; nCnt++)
						{
							nPunchSpeed--;*/

						if (m_nType != MOTIONTYPE_PUNCH0)
						{
							HitEnemyPunch0(m_bDeath);
							SetMotionPlayer(MOTIONTYPE_PUNCH0);

							m_bAttack = true;
						}

						/*if (nPunchSpeed <= 0)
						{
							nPunchSpeed = PLAYER_PUNCH_SPEED;
						}*/
						/*}*/
					}
					else
					{
						m_bAttack = false;
					}
				}

				else if (m_bAttack == false)
				{
					if (m_nType != MOTIONTYPE_NEUTRAL)
					{
						SetMotionPlayer(MOTIONTYPE_NEUTRAL);
					}
				}
		
			//�K�[�h����
			if (pInputKeyboard->GetPless(DIK_G) == true || pInputGamepad->GetTrigger(pInputGamepad->BUTTON_X, 0) == true)
			{
				m_PlayerState = PLAYER_GURD;
			}
			else
			{
				m_PlayerState = PLAYER_NONE;
			}

			if (pos.y > 2000.0f)
			{
				pos.y = 2000.0f;
				move.y = 0;
			}

			else if (pos.y < 1.0f)
			{
				pos.y = 0.0f;
				move.y = 1.0f;
			}


		//�ǂ̓����蔻��
		if (pos.x + 50.0f > 620)
		{
			pos.x = 620.0f - 50.0f;
			move.x = 0;
		}

		else if (pos.x - 50.0f < -3000.0f)
		{
			pos.x = -3000.0f + 50.0f;
			move.x = 0;
		}

		////���_���̎󂯎��
		//LPDIRECT3DVERTEXBUFFER9 Buff = CBilboard::GetBuff();

		//VERTEX_3D *pVtx;    //���_���ւ̃|�C���^

		///*���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾*/
		//Buff->Lock(0, 0, (void**)&pVtx, 0);

		//�d�͏���
		move.y -= 1.0f;

		if (move.y >= -1.0f)
		{
			m_bJump = true;

			SetJump(m_bJump);
		}

		////�ʒu���X�V
		//m_fLength += m_movefLength;

		//�ړ��ʂ��X�V
		move.x += (0.0f - move.x) * 0.2f;

		//�ړ��ʂ��ʒu�ɑ��
		pos += move;

		//�����Z�b�g
		SetPosition(pos);
		SetMove(move);
		SetRot(rot);

		//�u���b�N�̓����蔻��
		HitBlock(m_bJump);

		SetJump(m_bJump);

		if (m_PlayerState != PLAYER_GURD)
		{
			//�G�Ƃ̓����蔻��
			m_bDeath = HitPlayer(m_bDeath);
		}

		//���̔���
		if (pos.y <= 1.0f)
		{
			m_bJump = false;
			move.y = 0.0f;
			pos.y = 1.0f;

			SetJump(m_bJump);
		}

		//////�e�̐ݒ�
		////SetPositionShadow(m_nldxShadow, D3DXVECTOR3(pos.x, 0.0f, pos.z));

		//////���_���W�̐ݒ�
		////pVtx[0].pos = D3DXVECTOR3(- m_fWidth,+ m_fHeight, 0.0f);
		////pVtx[1].pos = D3DXVECTOR3(+ m_fWidth,+ m_fHeight, 0.0f);
		////pVtx[2].pos = D3DXVECTOR3(- m_fWidth, pos.y, 0.0f);
		////pVtx[3].pos = D3DXVECTOR3(+ m_fWidth, pos.y, 0.0f);

		////// �@���x�N�g���̐ݒ�
		////pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		////pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		////pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		////pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//////���_�J���[�̐ݒ�
		////pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		////pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		////pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		////pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		//////�e�N�X�`�����W�̐ݒ�
		////pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		////pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		////pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		////pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//////���_�o�b�t�@���A�����b�N����
		////Buff->Unlock();

		///*SetBuff(Buff);*/


		////�����x��100�ɂȂ�Ǝ��ʏ���
		//if (pTime->Get() == 100)
		//{
		//	//�p�[�e�B�N���̐���
		//	CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 1, 1.0f, 1.0f);

		//	m_bDeath = true;

		//	SetDeath(m_bDeath);
		//}

#ifdef _DEBUG
		int nAttack = 0;
		if (m_bAttack == true)
		{
			nAttack = 1;
		}
		else
		{
			nAttack = 0;
		}

		int nState = 0;
		if (m_nType == MOTIONTYPE_MOVE)
		{
			nState = 1;
		}
		if (m_nType == MOTIONTYPE_PUNCH0)
		{
			nState = 2;
		}
		else
		{
			nState = 0;
		}

		pDebug->Print("�v���C���[�̃��[�V������� : %d\n", nState);

//�v���C���[�̏ꏊ�f�o�b�N���
		pDebug->Print("�v���C���[�̏ꏊ X : %f Y : %f Z : %f\n", pos.x, pos.y, pos.z);

		//�v���C���[�̏ꏊ�f�o�b�N���
		pDebug->Print("�v���C���[�̈ړ��� X : %f Y : %f Z : %f\n", move.x, move.y, move.z);

		//�v���C���[�̏ꏊ�f�o�b�N���
		pDebug->Print("�v���C���[�̌��� X : %f Y : %f Z : %f\n", rot.x, rot.y, rot.z);

		//�v���C���[�̏�ԃf�o�b�N���
		pDebug->Print("�v���C���[��� : %d\n", nState);

		//�v���C���[�̍U�����Ă邩�ǂ����`�F�b�N
		pDebug->Print("�v���C���[���U�����Ă��邩�ǂ��� : %d\n", nAttack);

		//�f�o�b�O�\���p
		int nJump;

		if (m_bJump == false)
		{
			nJump = 0;
		}
		else
		{
			nJump = 1;
		}


		//�v���C���[�̃W�����v�f�o�b�N���
		pDebug->Print("�v���C���[�̃W�����v : %d\n", nJump);

		pDebug->Print("�v���C���[�̗̑� :: %d\n", m_nLife);
#endif

		SetPlayerRot(m_bRot);

		////�����x��100�ɂȂ�Ǝ��ʏ���
		//if (pTime->Get() == 100)
		//{
		//	//�p�[�e�B�N���̐���
		//	CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 1, 1.0f, 1.0f);

		//	m_bDeath = true;

		//	SetDeath(m_bDeath);
		//}

#ifdef _DEBUG
//�v���C���[�̏ꏊ�f�o�b�N���
		pDebug->Print("�v���C���[�~���[�̈ړ��� X : %f Y : %f Z : %f\n", move.x, move.y, move.z);
#endif

		/*return;*/
	}
		SetState(m_PlayerState);

		D3DXVECTOR3 PosDiff; //���[�V�����̍��������߂�
		D3DXVECTOR3 RotDiff; //���[�V�����̍��������߂�

		//���[�V�������}���p
		D3DXVECTOR3 MotionPos;
		D3DXVECTOR3 MotionRot;

		//�t���[���J�E���g�����Z
		m_nFrameCnt++;

		//���݂̃L�[�̐��𒲂ׂ�
		pDebug->Print("\n���Ԃ߂̃L�[�� : %d\n", m_nKey);

		//�S���f���̍X�V(�p�[�c)�̍X�V
		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{

			int nNextKey = m_nKey + 1;

			if (nNextKey > m_aInfo[m_nType].nNumKey)
			{
				nNextKey = 0;
			}

			//�ʒu
			//�L�[�̍��������߂�x
			PosDiff.x = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosX;

			//�L�[�̍��������߂�y
			PosDiff.y = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosY;

			//�L�[�̍��������߂�z
			PosDiff.z = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosZ;

			//����
			//�L�[�̍��������߂�x
			RotDiff.x = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotX;

			//�L�[�̍��������߂�y
			RotDiff.y = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotY;

			//�L�[�̍��������߂�z
			RotDiff.z = m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ
				- m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotZ;

			//�����̐��K��
			//�ڕW�̌���X���R.�P�S�𒴂�����
			if (RotDiff.x > D3DX_PI)
			{
				RotDiff.x -= D3DX_PI * 2;
			}
			else if (RotDiff.x < -D3DX_PI)
			{//�ڕW�̌���X��-�R.�P�S�𒴂�����
				RotDiff.x += D3DX_PI * 2;
			}

			//�ڕW�̌���Y���R.�P�S�𒴂�����
			if (RotDiff.y > D3DX_PI)
			{
				RotDiff.y -= D3DX_PI * 2;
			}
			else if (RotDiff.y < -D3DX_PI)
			{//�ڕW�̌���Y��-�R.�P�S�𒴂�����
				RotDiff.y += D3DX_PI * 2;
			}

			//�ڕW�̌���Z���R.�P�S�𒴂�����
			if (RotDiff.z > D3DX_PI)
			{
				RotDiff.z -= D3DX_PI * 2;
			}
			else if (RotDiff.z < -D3DX_PI)
			{//�ڕW�̌���Z��-�R.�P�S�𒴂�����
				RotDiff.z += D3DX_PI * 2;
			}

			////�p�[�c�̈ʒu�⍷�����v�Z����
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX = (float)m_nKey + PosDiff.x * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY = (float)m_nKey + PosDiff.y * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ = (float)m_nKey + PosDiff.z * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX = (float)m_nKey + RotDiff.x * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY = (float)m_nKey + RotDiff.y * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			//m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ = (float)m_nKey + RotDiff.z * (m_nCounter / m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);

			m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame = 60;

			//�p�[�c�̈ʒu�⍷�����v�Z����
			MotionPos.x = m_InitPartPos[nCntModel].x;/* + m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosX + PosDiff.x * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);*/
			MotionPos.y = m_InitPartPos[nCntModel].y;/* + m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosY + PosDiff.y * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);*/
			MotionPos.z = m_InitPartPos[nCntModel].z; /*+ m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fPosZ + PosDiff.z * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);*/
			MotionRot.x = m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotX + RotDiff.x * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			MotionRot.y = m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotY + RotDiff.y * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);
			MotionRot.z = m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[nCntModel].m_fRotZ + RotDiff.z * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyinfo[m_nKey].nFrame);

			//�����̐��K��
			//�ڕW�̌���X���R.�P�S�𒴂�����
			if (MotionRot.x > D3DX_PI)
			{
				MotionRot.x -= D3DX_PI * 2;
			}
			else if (MotionRot.x < -D3DX_PI)
			{//�ڕW�̌���X��-�R.�P�S�𒴂�����
				MotionRot.x += D3DX_PI * 2;
			}

			//�ڕW�̌���Y���R.�P�S�𒴂�����
			if (MotionRot.y > D3DX_PI)
			{
				MotionRot.y -= D3DX_PI * 2;
			}
			else if (MotionRot.y < -D3DX_PI)
			{//�ڕW�̌���Y��-�R.�P�S�𒴂�����
				MotionRot.y += D3DX_PI * 2;
			}

			//�ڕW�̌���Z���R.�P�S�𒴂�����
			if (MotionRot.z > D3DX_PI)
			{
				MotionRot.z -= D3DX_PI * 2;
			}
			else if (MotionRot.z < -D3DX_PI)
			{//�ڕW�̌���Z��-�R.�P�S�𒴂�����
				MotionRot.z += D3DX_PI * 2;
			}

			////�p�[�c�̈ʒu�E������ݒ�
			//m_apModel[nCntModel]->SetPos(D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosX,
			//	m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosY, m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fPosZ));

			//m_apModel[nCntModel]->SetRot(D3DXVECTOR3(m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotX,
			//	m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotY, m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[nCntModel].m_fRotZ));

			//�p�[�c�̈ʒu�E������ݒ�
			m_apModel[nCntModel]->SetPos(MotionPos);

			m_apModel[nCntModel]->SetRot(MotionRot);

			switch (m_nType)
			{
			case MOTIONTYPE_NEUTRAL:

				if (m_nKey == 0)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

					//�ӂ��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//�݂��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//����ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//���ڂ̃p�[�c(���r)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//�ނ��ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
				}

				else if (m_nKey == 1)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

					//�ӂ��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//�݂��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//����ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//���ڂ̃p�[�c(���r)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//�ނ��ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -1.5f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;

				}

				else if (m_nKey == 2)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

					//�ӂ��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//�݂��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//����ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//���ڂ̃p�[�c(���r)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//�ނ��ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.5f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = -0.5f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.6f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -7.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
				}

				else if (m_nKey == 3)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.0f;

					//�ӂ��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//�݂��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//����ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//���ڂ̃p�[�c(���r)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//�ނ��ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
				}

				if (m_nKey == 4)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

					//�ӂ��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

					//�݂��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//����ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

					//���ڂ̃p�[�c(���r)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

					//�ނ��ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
				}

				break;

		

case MOTIONTYPE_MOVE:

	if (m_nKey == 0)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

		//�ӂ��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//�݂��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//����ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//���ڂ̃p�[�c(���r)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//�ނ��ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
	}

	else if (m_nKey == 1)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

		//�ӂ��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//�݂��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//����ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//���ڂ̃p�[�c(���r)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//�ނ��ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;

	}

	else if (m_nKey == 2)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

		//�ӂ��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//�݂��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//����ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//���ڂ̃p�[�c(���r)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//�ނ��ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -7.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
	}

	else if (m_nKey == 3)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.0f;

		//�ӂ��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//�݂��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//����ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//���ڂ̃p�[�c(���r)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//�ނ��ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
	}

	if (m_nKey == 4)
	{
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

		//�ӂ��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

		//�݂��ڂ̃p�[�c(��)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

		//����ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.5f;

		//���ڂ̃p�[�c(���r)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

		//�ނ��ڂ̃p�[�c(����)
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = -0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.7f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.9f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.2f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.8f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
		m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
	}

	break;

	case MOTIONTYPE_PUNCH0:

		if (m_nKey == 0)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//�ӂ��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//�݂��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//����ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//���ڂ̃p�[�c(���r)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//�ނ��ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
		}

		else if (m_nKey == 1)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//�ӂ��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//�݂��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//����ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//���ڂ̃p�[�c(���r)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//�ނ��ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
		}

		else if (m_nKey == 2)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//�ӂ��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//�݂��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//����ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//���ڂ̃p�[�c(���r)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//�ނ��ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
		}

		else if (m_nKey == 3)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//�ӂ��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//�݂��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//����ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//���ڂ̃p�[�c(���r)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//�ނ��ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;
		}

		else if (m_nKey == 4)
		{
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = 0.0f;

			//�ӂ��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = 0.0f;

			//�݂��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

			//����ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

			//���ڂ̃p�[�c(���r)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.2f;

			//�ނ��ڂ̃p�[�c(����)
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[10].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[11].m_fRotZ = 0.0f;


			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[14].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[15].m_fRotZ = -0.1f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[16].m_fRotZ = 0.0f;

			m_bAttack = false;

		}
				break;
			}
		}

		//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�
		m_nCounter++;

		m_aInfo[m_nKey].nNumKey = 5;

		switch (m_nType)
		{
		case MOTIONTYPE_NEUTRAL:
			if (m_nFrameCnt > 60)
			{
				m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
				m_nCounter = 0;
				m_nFrameCnt = 0;
			}

			break;

		case MOTIONTYPE_MOVE:
			if (m_nFrameCnt > 50)
			{
				m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
				m_nCounter = 0;
				m_nFrameCnt = 0;
			}

			break;

		case MOTIONTYPE_PUNCH0:
			if (m_nFrameCnt > 20)
			{
				m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
				m_nCounter = 0;
				m_nFrameCnt = 0;

				if (m_nKey == 4)
				{
					SetMotionPlayer(MOTIONTYPE_NEUTRAL);
				}
			}

			break;
		}

		//m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;

		/*m_nKey = (m_nKey + 1) % m_nKey;*/
		}

	}
}
	


//============================
//�|���S���̕`��
//============================
void CPlayer::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRot();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//D3DMATERIAL9 matDef;  //���݂̃}�e���A���ۑ��p

	//D3DXMATERIAL *pMat;	  //�}�e���A���f�[�^�ւ̃|�C���^

	/*CModel *pModel;

	CModel::SET_MODEL *pModelMat;

	pModel = pModel->GetModel();*/

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	////���݂̃}�e���A�����擾
	//pDevice->GetMaterial(&matDef);

	////�}�e���A���f�[�^�ւ̃|�C���^���擾
	//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	/*pModelMat = pModelMat->m_pBuffMat*/

	/*pMat = (D3DXMATERIAL*)pModelMat->m_pBuffMat->GetBufferPointer();*/

	if (m_bDeath == false)
	{
		for (int nCntMat = 0; nCntMat < m_nNumModel; nCntMat++)
		{
			switch (m_PlayerState)
			{
			case PLAYER_NONE:

				//�}�e���A���̐ݒ�
				m_stateCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;

			case PLAYER_DAMAGE:

				//�}�e���A���̐ݒ�
				m_stateCol = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				break;

			case PLAYER_INVINCIBLE:
				m_stateCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f);
				break;

			case PLAYER_GURD:
				m_stateCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}

			if (m_PlayerState == PLAYER_NONE || m_PlayerState == PLAYER_GURD)
			{
				//���f��(�p�[�c)�̕`��
				m_apModel[nCntMat]->Draw();
			}
			else
			{
				//���f��(�p�[�c)�̕`��
				m_apModel[nCntMat]->DrawCol(m_stateCol);
			}
		}
	}

	/*�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);*/
}

//============================
//�W�����v���Ă邩�ǂ������Z�b�g����
//============================
void CPlayer::SetJump(bool jump)
{
	m_bJump = jump;
}

//============================
//�W�����v���Ă邩�ǂ����̎擾
//============================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//==============================
//�u���b�N�Ƃ̓����蔻��(3D)
//==============================
void CPlayer::HitBlock(bool bJump)
{
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		CObject *pObj = NULL;

		CObjectx *pObjectx = NULL;

		//�I�u�W�F�N�g���擾
		pObj = GetObject(nCnt);

		//NULL�`�F�b�N
		if (pObj != NULL)
		{
			TYPE type;

			//��ނ��擾
			type = pObj->GetType();

			D3DXVECTOR3 move = GetMove();

			////�ʒu�擾
			//D3DXVECTOR3 posBlock = pObj->GetPosition();

			if (type == TYPE_BLOCK || type == TYPE_FLOOR || type == TYPE_LONGFLOOR)
			{
				pObjectx = dynamic_cast<CObjectx*>(pObj);

				if (pObjectx != NULL)
				{
					if (GetPosition().z + PLAYER_MIN_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z
						&& GetPosition().z + PLAYER_MIN_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z)
					{
						if (GetPosition().y + PLAYER_MIN_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y
							&& GetPosition().y + PLAYER_MIN_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y)
						{
							//������̓����蔻��
							if (GetPosition().x + PLAYER_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x
								&& m_posold.x + PLAYER_MAX_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
							{//�v���C���[�ƃu���b�N���������� 

								//�ʒu�������ɌŒ�
								SetPosition(D3DXVECTOR3(pObjectx->GetPosition().x + pObjectx->GetVtxMin().x - PLAYER_MAX_X, GetPosition().y, GetPosition().z));

								move.x = 0.0f;

								//�W�����v���ł���悤��
								bJump = false;
								SetJump(bJump);

							}
							
							//�E����̓����蔻��
							if (GetPosition().x + PLAYER_MIN_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
								&& m_posold.x + PLAYER_MIN_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x)
							{//�v���C���[�ƃu���b�N���������� 

								//�v���C���[���E���ɌŒ�
								SetPosition(D3DXVECTOR3(pObjectx->GetPosition().x + pObjectx->GetVtxMax().x - PLAYER_MIN_X, GetPosition().y, GetPosition().z));

								move.x = 0.0f;

								//�W�����v���ł���悤��
								SetJump(false);

							}
						}
					}

					if (GetPosition().x + PLAYER_MAX_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
						&& GetPosition().x + PLAYER_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
					{
						//��O����̓����蔻��
						if (GetPosition().z + PLAYER_MAX_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z
							&& m_posold.z + PLAYER_MAX_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z)
						{//�v���C���[�ƃu���b�N���������� 

							//�v���C���[�������ɌŒ�
							SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, pObjectx->GetPosition().z + pObjectx->GetVtxMin().z - PLAYER_MAX_Z));

							move.x = 0.0f;

							//�W�����v���ł���悤��
							SetJump(false);

						}

						//������̓����蔻��
						if (GetPosition().z + PLAYER_MIN_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z
							&& m_posold.z + PLAYER_MIN_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z)
						{//�v���C���[�ƃu���b�N���������� 

							//�v���C���[����O���ɌŒ�
							SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, pObjectx->GetPosition().z + pObjectx->GetVtxMax().z - PLAYER_MIN_Z));

							move.x = 0.0f;

							//�W�����v���ł���悤��
							SetJump(false);

						}
					}

					if (GetPosition().x + PLAYER_MIN_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
						&& GetPosition().x + PLAYER_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
					{
						//��O����̓����蔻��
						if (GetPosition().y + PLAYER_MAX_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y
							&& m_posold.y + PLAYER_MAX_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y)
						{//�v���C���[�ƃu���b�N���������� 

							//�v���C���[�������ɌŒ�
							SetPosition(D3DXVECTOR3(GetPosition().x, pObjectx->GetPosition().y - pObjectx->GetVtxMin().y - PLAYER_MAX_Y - 10.0f, GetPosition().z));

							move.y = 0.0f;

							//�W�����v���ł���悤��
							SetJump(false);

						}

						//������̓����蔻��
						if (GetPosition().y + PLAYER_MIN_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y
							&& m_posold.y + PLAYER_MIN_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y)
						{//�v���C���[�ƃu���b�N���������� 

							//�v���C���[�������ɌŒ�
							SetPosition(D3DXVECTOR3(GetPosition().x, pObjectx->GetPosition().y + pObjectx->GetVtxMax().y + PLAYER_MIN_Y, GetPosition().z));

							move.y = 0.0f;

							//�W�����v���ł���悤��
							SetJump(false);
						}
					}
				}
			}

			//�ʒu�ƈړ������Z�b�g
			SetPosition(GetPosition());
			SetMove(move);
		}
	}
}

//==============================
//�G�̓����蔻��(3D)
//==============================
bool CPlayer::HitEnemyPunch0(bool bDeath)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();

	pInputGamepad = CManager::GetGamePad();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		CObject *pObj = NULL;

		CObjectx *pObjectx = NULL;

		//�I�u�W�F�N�g���擾
		pObj = GetObject(nCnt);

		//NULL�`�F�b�N
		if (pObj != NULL)
		{
			TYPE type;

			//��ނ��擾
			type = pObj->GetType();

			////�ʒu�擾
			//D3DXVECTOR3 posBlock = pObj->GetPosition();

			if (type == TYPE_ENEMY)
			{

				pObjectx = dynamic_cast<CObjectx*>(pObj);

				if (GetPosition().x + 12.0f >= pObjectx->GetPosition().x - 15.0f
					&& GetPosition().x - 12.0f <= pObjectx->GetPosition().x + 15.0f
					&& GetPosition().y + 10.0f >= pObjectx->GetPosition().y - 20.0f
					&& GetPosition().y - 10.0f <= pObjectx->GetPosition().y + 40.0f
					&& GetPosition().z + 5.0f >= pObjectx->GetPosition().z - 5.0f
					&& GetPosition().z - 5.0f <= pObjectx->GetPosition().z + 5.0f)
				{
					CEnemy *pEnemy = CGame::GetEnemy();

					//�p�[�e�B�N���̐���
					CParticle::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y + 20.0f, GetPosition().z), GetRot().y, 1, 10.0f, 10.0f);

					/*CSound::PlaySound(CSound::SOUND_LABEL_SE_BLOOD);
					CSound::PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);*/

					int nEnemyLife = pEnemy->GetLife(0);

					if (nEnemyLife <= 0)
					{
						//���񂾂��Ƃɂ���
						bDeath = true;

						

						pEnemy->SetDeath(bDeath,0);

						return true;
					}
					else
					{
						pEnemy->AddDamage(1, 0);

						D3DXVECTOR3 move = GetMove();

						/*move = D3DXVECTOR3(20.0f, 10.0f, 0.0f);

						SetMove(move);*/
					}
				}
			}
		}
	}
	return false;
}

//==============================
//�G�̓����蔻��(3D)
//==============================
bool CPlayer::HitPlayer(bool bDeath)
{
	CInputKeyboard *pInputKeyboard;
	CInputGamePad *pInputGamepad;

	//�L�[�{�[�h�̎擾
	pInputKeyboard = CManager::GetInputKeyboard();

	pInputGamepad = CManager::GetGamePad();

	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		CObject *pObj = NULL;

		CObjectx *pObjectx = NULL;

		//�I�u�W�F�N�g���擾
		pObj = GetObject(nCnt);

		//NULL�`�F�b�N
		if (pObj != NULL)
		{
			TYPE type;

			//��ނ��擾
			type = pObj->GetType();

			////�ʒu�擾
			//D3DXVECTOR3 posBlock = pObj->GetPosition();

			if (type == TYPE_ENEMY)
			{

				pObjectx = dynamic_cast<CObjectx*>(pObj);

				if (GetPosition().x + 10.0f >= pObjectx->GetPosition().x - 0.0f
					&& GetPosition().x - 10.0f <= pObjectx->GetPosition().x + 0.0f
					&& GetPosition().y + 10.0f >= pObjectx->GetPosition().y - 20.0f
					&& GetPosition().y - 10.0f <= pObjectx->GetPosition().y + 40.0f
					&& GetPosition().z + 5.0f >= pObjectx->GetPosition().z - 5.0f
					&& GetPosition().z - 5.0f <= pObjectx->GetPosition().z + 5.0f)
				{
						//�p�[�e�B�N���̐���
						CParticle::Create(D3DXVECTOR3(GetPosition().x, GetPosition().y + 20.0f, GetPosition().z), GetRot().y, 1, 10.0f, 10.0f);

						CSound::PlaySound(CSound::SOUND_LABEL_SE_BLOOD);
						CSound::PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

						if (m_nLife <= 0)
						{
							//���񂾂��Ƃɂ���
							bDeath = true;

							SetDeath(bDeath);

							return true;
						}
						else
						{
							AddDamage(1);

							D3DXVECTOR3 move = GetMove();

							move = D3DXVECTOR3(20.0f, 10.0f, 0.0f);

							SetMove(move);

							if (m_nType != MOTIONTYPE_NEUTRAL)
							{
								SetMotionPlayer(MOTIONTYPE_NEUTRAL);
							}
						}
				}
			}
		}
	}
	return false;
}

////============================
//�v���C���[�̎��S���Z�b�g
////============================
void CPlayer::SetDeath(bool bDeath)
{
	m_bDeath = bDeath;
}

////============================
//�v���C���[�̎��S�����󂯓n��
////============================
bool CPlayer::GetDeath(void)
{
	return m_bDeath;
}

////============================
//�v���C���[�̌������Z�b�g
////============================
void CPlayer::SetPlayerRot(bool bRot)
{
	m_bRot = bRot;
}

////============================
//�v���C���[�̌������󂯓n��
////============================
bool CPlayer::GetPlayerRot(void)
{
	return m_bRot;
}

////============================
//�v���C���[�̌������Z�b�g
////============================
void CPlayer::SetPlayerAim(bool bAim)
{
	m_bAim = bAim;
}

////============================
//�v���C���[�̏�ԃZ�b�g
////============================
void CPlayer::SetState(PLAYER_STATE state)
{
	m_PlayerState = state;

	switch (m_PlayerState)
	{
	case PLAYER_NONE:
		
		m_nCntState = 120;

		break;

	case PLAYER_DAMAGE:

		m_nCntState--;
	
		if (m_nCntState == 60)
		{
			m_PlayerState = PLAYER_INVINCIBLE;
		}
			
		break;

	case PLAYER_INVINCIBLE:

		m_nCntState--;

		if (m_nCntState == 0)
		{
			m_PlayerState = PLAYER_NONE;
		}
			
		break;
	}
}

////============================
//�v���C���[�̌������󂯓n��
////============================
bool CPlayer::GetPlayerAim(void)
{
	return m_bAim;
}

////============================
//�v���C���[�̃��C�t�Z�b�g
////============================
void CPlayer::SetLife(int nLife)
{
	m_nLife = nLife;
}

////============================
//�v���C���[�̃��C�t�󂯓n��
////============================
int CPlayer::GetLife(void)
{
	return m_nLife;
}

////============================
//�v���C���[�̏�Ԏ󂯓n��
////============================
CPlayer::PLAYER_STATE CPlayer::GetState(void)
{
	return m_PlayerState;
}

//============================
//���[�V�����̐ݒ�
//============================
void CPlayer::SetMotionPlayer(MOTIONTYPE nType)
{
	m_nType = nType;		 //���[�V�����̃^�C�v
	m_nKey = 0;				 //���݂̃L�[NO
	m_nCounter = 0;	 //���[�V�����J�E���^�[

	switch (m_nType)
	{
	case MOTIONTYPE_NEUTRAL:

		if (m_nKey == 0)
		{
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotY = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotZ = 0.0f;

			//�ӂ��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotY = 0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotZ = 0.0f;

			//�݂��ڂ̃p�[�c(��)	 m_nKey
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotY = 0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotZ = 0.0f;

			//����ڂ̃p�[�c(����)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotZ = 0.5f;

			//���ڂ̃p�[�c(���r)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotZ = -0.2f;

			//�ނ��ڂ̃p�[�c(����)	m_nKey
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotX = 1.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotZ = -0.2f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotX = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotZ = 0.1f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotZ = -0.7f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotZ = 0.9f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotZ = 0.2f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotY = -0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotZ = 0.0f;
		}

		break;

	case MOTIONTYPE_MOVE:

		if (m_nKey == 0)
		{
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosZ = 0.0f;

			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotY = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotZ = 0.0f;

			//�ӂ��ڂ̃p�[�c(��)
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotY = 0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotZ = 0.0f;
			
			//�݂��ڂ̃p�[�c(��)	 
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotY = 0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotZ = 0.0f;
			
			//����ڂ̃p�[�c(����)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotZ = 0.5f;
			
			//���ڂ̃p�[�c(���r)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotZ = -0.2f;
			
			//�ނ��ڂ̃p�[�c(����)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotX = 1.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotZ = -0.2f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotX = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotZ = 0.1f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotZ = -0.7f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotZ = 0.0f;
			
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotZ = 0.9f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotZ = 0.2f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotY = -0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotZ = 0.0f;
		}
		break;

	case MOTIONTYPE_PUNCH0:

		if (m_nKey == 0)
		{
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotX = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotY = -1.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotZ = 0.0f;
		
			//�ӂ��ڂ̃p�[�c(��)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotX = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[1].m_fRotZ = 0.0f;
			
			//�݂��ڂ̃p�[�c(��)	 
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotY = 0.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotZ = 0.0f;
			
			//����ڂ̃p�[�c(����)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotX = 1.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotY = -0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[3].m_fRotZ = 0.3f;
			
			//���ڂ̃p�[�c(���r)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotX = -0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[4].m_fRotZ = -0.2f;
			
			//�ނ��ڂ̃p�[�c(����)	
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotY = 0.9f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[5].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotX = 0.7f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotY = 0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[7].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotX = -0.4f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotY = 0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[8].m_fRotZ = 0.1f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotY = 0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[9].m_fRotZ = -0.7f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotY = 1.6f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[10].m_fRotZ = 0.0f;
		
				
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotY = 0.8f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[11].m_fRotZ = 0.0f;
			
				
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[12].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotY = -0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[13].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotX = -0.3f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotY = -0.2f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[14].m_fRotZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fPosZ = 0.0f;
		
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotY = -0.1f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotZ = -0.1f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosZ = 0.0f;
			
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotX = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotY = 0.0f;
			m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotZ = 0.0f;
		}
		break;
	}
				
}

//========================
//�v���C���[�̃_���[�W
//========================
void CPlayer::AddDamage(int nDamage)
{
	m_nLife = m_nLife - nDamage;

	m_PlayerState = PLAYER_DAMAGE;

	SetLife(m_nLife);

	SetState(m_PlayerState);
}

////============================
////�ʒu���Z�b�g����
////============================
//void CPlayer::SetPosition(D3DXVECTOR3 pos)
//{
//	m_pos = pos;
//}
//
////============================
////�ړ��ʂ��Z�b�g����
////============================
//void CPlayer::SetMove(D3DXVECTOR3 move)
//{
//	m_move = move;
//}
//
////============================
////�X�����Z�b�g����
////============================
//void CPlayer::SetRot(D3DXVECTOR3 rot)
//{
//	m_rot = rot;
//}
//
////============================
////�F���Z�b�g����
////============================
//void CPlayer::SetCol(D3DXCOLOR col)
//{
//	m_col = col;
//
//	//VERTEX_2D *pVtx;    //���_���ւ̃|�C���^
//
//	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//
//	////���_�J���[�̐ݒ�
//	//pVtx[0].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
//	//pVtx[1].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
//	//pVtx[2].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
//	//pVtx[3].col = D3DXCOLOR(m_col.r,m_col.g,m_col.b,m_col.a);
//
//	////���_�o�b�t�@���A�����b�N����
//	//m_pVtxBuff->Unlock();
//}
//
////============================
////���_�����Z�b�g����
////============================
//void CPlayer::SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff)
//{
//	m_pVtxBuff = Buff;
//}
//
////============================
////�̗͂��Z�b�g����
////============================
//void CPlayer::SetLife(int nLife)
//{
//	m_nLife = nLife;
//}
//
////============================
////�ʒu�̎擾
////============================
//D3DXVECTOR3 CPlayer::GetPosition(void)
//{
//	return m_pos;
//}
//
////============================
////�ړ��ʂ̎擾
////============================
//D3DXVECTOR3 CPlayer::GetMove(void)
//{
//	return m_move;
//}
//
////============================
////�X���̎擾
////============================
//D3DXVECTOR3 CPlayer::GetRot(void)
//{
//	return m_rot;
//}
//
////============================
////�F�̎擾
////============================
//D3DXCOLOR CPlayer::GetCol(void)
//{
//	return m_col;
//}
//
////============================
////���_�̎擾
////============================
//LPDIRECT3DVERTEXBUFFER9 CPlayer::GetBuff(void)
//{
//	return m_pVtxBuff;
//}
//
////============================
////�̗͎擾
////============================
//int CPlayer::GetLife(void)
//{
//	return m_nLife;
//}
