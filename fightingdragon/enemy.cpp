//============================
//
//�G����(enemy.cpp)
//Author:���� �F�M
//
//============================
#include "manager.h"
#include "bg.h"
//#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "renderer.h"
#include "debugproc.h"
#include "sound.h"
#include "particle.h"
#include "mode.h"
#include "player.h"

//============================
//�R���X�g���N�^
//============================
CEnemy::CEnemy()
{
	m_Enemystate = ENEMYSTATE_NONE;					//�G�̃X�e�[�g���N���A����

	m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//�G�̐F���N���A����

	m_nCntState = 0;									//�G�̐����N���A����

	
	m_bDeath = false;									//�G�����S�������ǂ������N���A����


	m_nCnt = 0;

	m_nLife[0] = 0;

	memset(&m_InitPartPos[0], NULL, sizeof(D3DXVECTOR3));

	memset(&m_aInfo[0], NULL, sizeof(m_aInfo));

	m_nFrameCnt = 0;

	m_bFinish = false;						//�I�����邩�ǂ���
	m_bAttack = false;						//�U����Ԃɓ����Ă��邩�ǂ������N���A

	m_nNumAll = 0;				//���̍ő吔
	m_nType = 0;			//���
	bLoop = false;							//�I�����邩�ǂ���
	m_nKey = 0;								//�L�[�̐�
	m_nCounter = 0;						//���[�V�����J�E���^�[
}

CEnemy::CEnemy(D3DXVECTOR3 pos)
{
	SetPosition(pos);
}

//============================
//�f�X�g���N�^
//============================
CEnemy::~CEnemy()
{
}

//============================
//�e�N�X�`���̐���(�ǂݍ���)
//============================
HRESULT CEnemy::Load(void)
{
	////�f�o�C�X�̎擾
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\g0OntK3S.jpg",
	//	&m_pTexture[0]);

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\lostwarm.png",
	//	&m_pTexture[1]);

	////�e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	"data\\TEXTURE\\raginee.png",
	//	&m_pTexture[2]);

	return S_OK;
}

//============================
//�e�N�X�`���̔j��
//============================
void CEnemy::Unload(void)
{
	//for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	//{
	//	//�e�N�X�`���̔j��
	//	if (m_pTexture[nCnt] != NULL)
	//	{
	//		m_pTexture[nCnt]->Release();
	//		m_pTexture[nCnt] = NULL;
	//	}
	//}
}


//============================
//��������
//============================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	CEnemy *pEnemy;

	//�I�u�W�F�N�g2D�̐���
	pEnemy = NEW_DBG CEnemy(pos);

	//����������
	pEnemy->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nTex,fWidth,fHeight);

	////�e�N�X�`���̊��蓖��
	//pEnemy->BindTexture(m_pTexture[nTex]);

	return pEnemy;
}

//============================
//�|���S���̏�����
//============================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
{
	////�f�o�C�X�̎擾
	//CRenderer *pRenderer = CManager::GetRenderer();
	//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_nKey = 5;								//�L�[�̐�

	m_nFrameCnt = 0;

	SetPosition(pos);

	nTex = 0;


	m_bAttack = false;				//�U����Ԃ��ǂ�����������


	for (int nCntInfo = 0; nCntInfo < MAX_PART; nCntInfo++)
	{
		m_aInfo[nCntInfo].nNumKey = 0;

		for (int nCnt = 0; nCnt < 5; nCnt++)
		{
			m_aInfo[nCntInfo].aKeyinfo[nCnt].nFrame = 120;
		}
	}

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
		m_Enemystate = ENEMYSTATE_NONE;

		SetState(m_Enemystate);

		m_nCntState = 30;

		m_bDeath = false;

		m_nLife[0] = 10;

	//�S�Ẵp�[�c����������
	m_nNumModel = MAX_MODEL;

	//���f������
	m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 32.0f, 0.0f), fRot, 0, fWidth, fHeight,0);
	m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, -1.0f, 0.0f), fRot, 1, fWidth, fHeight,0);
	m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 18.0f, 0.0f), fRot, 2, fWidth, fHeight,0);
	m_apModel[3] = CModel::Create(D3DXVECTOR3(4.0f, -10.0f, 0.0f), fRot, 3, fWidth, fHeight,0);
	m_apModel[4] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 0.0f), fRot, 4, fWidth, fHeight,0);
	m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 5, fWidth, fHeight,0);
	m_apModel[6] = CModel::Create(D3DXVECTOR3(-4.0f, -10.0f, 0.0f), fRot, 6, fWidth, fHeight, 0);
	m_apModel[7] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 1.0f), fRot, 7, fWidth, fHeight,0);
	m_apModel[8] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 8, fWidth, fHeight,0);
	m_apModel[9] = CModel::Create(D3DXVECTOR3(5.0f, 15.0f, -1.0f), fRot, 9, fWidth, fHeight,0);
	m_apModel[10] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), fRot, 10, fWidth, fHeight,0);
	m_apModel[11] = CModel::Create(D3DXVECTOR3(5.7f, 0.0f, 0.0f), fRot, 11, fWidth, fHeight,0);
	m_apModel[12] = CModel::Create(D3DXVECTOR3(6.0f, 0.0f, 0.0f), fRot, 12, fWidth, fHeight,0);
	m_apModel[13] = CModel::Create(D3DXVECTOR3(-5.0f, 15.0f, -1.0f), fRot, 13, fWidth, fHeight, 0);
	m_apModel[14] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.5f), fRot, 14, fWidth, fHeight, 0);
	m_apModel[15] = CModel::Create(D3DXVECTOR3(-5.7f, 0.0f, -0.5f), fRot, 15, fWidth, fHeight, 0);
	m_apModel[16] = CModel::Create(D3DXVECTOR3(-6.0f, 0.0f, 0.0f), fRot, 16, fWidth, fHeight, 0);

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
	
	//��ނ�ݒ�
	SetType(CObject::TYPE_ENEMY);

	m_nCnt = nTex;

	SetCnt(m_nCnt);

	m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

	SetCol(m_ColEnemy);
	
	D3DXVECTOR3 move = GetMove();

	//�ړ��ʂ̏�����
	move.x = 0.0f;

	//�ړ��ʂ̃Z�b�g
	SetMove(move);

	SetDeath(m_bDeath,nTex);

	SetLife(m_nLife[0], 0);

	SetMotionEnemy(MOTIONTYPE_NEUTRAL);

	return S_OK;
}
//============================
//�|���S���̏I��
//============================
void CEnemy::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			delete m_apModel[nCnt];

			m_apModel[nCnt] = NULL;
		}
	}

	CObjectx::Release();
}
//============================
//�|���S���̍X�V
//============================
void CEnemy::Update(void)
{
	//if()

	//�G�̍s�������߂鏈��
	int nMove;

	
		//���̈ʒu�������_���ɂ��鏈��
		nMove = rand() % 70 + 1;

	//�I�u�W�F�N�g3d�̃f�[�^�����炤
	/*CObject3d *pobject3d = CGame::GetObject3d();
	bool bShowenemy = pobject3d->GetShowEnemy();*/

	D3DXVECTOR3 pos = GetPosition();

	m_posold = pos; //�O��̈ʒu���L�^

	D3DXVECTOR3 move = GetMove();

	D3DXVECTOR3 rot = GetRot();

	CPlayer *pPlayer = CGame::GetPlayer();

	//�d�͏���
	move.y -= 1.0f;

	if (move.y >= -1.0f)
	{

	}

	if (m_Enemystate != ENEMYSTATE_DAMAGE)
	{
		if (pos.z <= 0.0f)
		{//�G�̈ʒu(Z)��0��������
			/*bShowenemy = true;

			pobject3d->SetShowEnemy(bShowenemy);*/
			if (nMove < 63 && nMove > 60)
			{
				move.x = 1.0f;

				if (m_nType != MOTIONTYPE_MOVE)
				{
					SetMotionEnemy(MOTIONTYPE_MOVE);
				}
			}
			if (nMove < 65 && nMove > 63)
			{
				move.x = -1.0f;

				if (m_nType != MOTIONTYPE_MOVE)
				{
					SetMotionEnemy(MOTIONTYPE_MOVE);
				}
			}
			if (nMove < 68 && nMove > 66)
			{
				m_bAttack = true;

				m_Enemystate = ENEMYSTATE_ATTACK;

				if (m_nType != MOTIONTYPE_PUNCH)
				{
					SetMotionEnemy(MOTIONTYPE_PUNCH);
				}
			}
			/*if (nMove < 68 && nMove > 66)
			{
				m_bAttack = true;

				m_Enemystate = ENEMYSTATE_ATTACK;

				if (m_nType != MOTIONTYPE_KICK)
				{
					SetMotionEnemy(MOTIONTYPE_KICK);
				}
			}*/
			if (nMove < 70 && nMove > 68)
			{
				m_Enemystate = ENEMYSTATE_GURD;

				if (m_nType != MOTIONTYPE_PUNCH)
				{
					SetMotionEnemy(MOTIONTYPE_PUNCH);
				}
			}
			else if (nMove < 60)
			{
				if (m_nType != MOTIONTYPE_NEUTRAL)
				{
					SetMotionEnemy(MOTIONTYPE_NEUTRAL);
				}
			}

			m_Enemystate = ENEMYSTATE_ATTACK;

			SetState(m_Enemystate);

			if (move.x <= 0.0f)
			{
				rot.y = D3DX_PI * -0.5f;
			}
			else
			{
				rot.y = D3DX_PI * -0.5f;
			}

			//���̔���
			if (pos.y <= 1.0f)
			{
				m_bJump = false;
				move.y = 0.0f;
				pos.y = 1.0f;

				SetJump(m_bJump);
			}

			if (pos.x >= pPlayer->GetPosition().x)
			{
				move.x = -2.0f;
			}

			pos += move;

			SetPosition(pos);

			//���ɓ���������ړ��ʂ𔽓]
			if (HitBlock() == true)
			{
				move.x *= -1;
			}

			SetMove(move);
		}
	}
	else if(m_Enemystate == ENEMYSTATE_DAMAGE)
	{
		m_nCntState--;

		move = GetMove();

		pos += move;

		SetPosition(pos);

		SetMotionEnemy(MOTIONTYPE_DAMAGE);

		if (m_nCntState == 0)
		{
			m_nCntState = 30;

			SetState(ENEMYSTATE_NONE);


		}
	}

	//
	//{//�G�̈ʒu(Z)��0�ȊO��������
	//	if (m_pPlayer->GetPosition().x - 100.0f <= pos.x + 200.0f
	//		&&m_pPlayer->GetPosition().x + 10.0f >= pos.x
	//		&& m_pPlayer->GetPosition().y + 5.0f >= pos.y)
	//	{
	//		/*bShowenemy = false;*/

	//	/*	pobject3d->SetShowEnemy(bShowenemy);*/

	//		move.z = -8.0f;

	//		pos.z += move.z;

	//		if (pos.z <= 0.0f)
	//		{
	//			pos.z = 0.0f;
	//		}

	//		if (pos.z >= 8.0f && pos.z <= 11.0f)
	//		{
	//			CSound::PlaySound(CSound::SOUND_LABEL_SE_WINDOW);
	//			CSound::PlaySound(CSound::SOUND_LABEL_SE_SCREAM);

	//			CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 2, 20.0f, 20.0f);

	//			/*SetState(ENEMYSTATE_NONE);*/
	//		}

	//		SetPosition(pos);

	//	}

	//	if (m_pPlayer->GetPosition().x + 50.0f <= pos.x
	//		&&m_pPlayer->GetPosition().x - 10.0f >= pos.x - 200.0f
	//		&& m_pPlayer->GetPosition().y + 5.0f >= pos.y)
	//	{
	//		/*bShowenemy = false;*/

	//		/*pobject3d->SetShowEnemy(bShowenemy);*/

	//		move.z = -8.0f;

	//		pos.z += move.z;

	//		if (pos.z <= 0.0f)
	//		{
	//			pos.z = 0.0f;
	//		}

	//		if (pos.z >= 8.0f && pos.z <= 11.0f)
	//		{
	//			CSound::PlaySound(CSound::SOUND_LABEL_SE_WINDOW);
	//			CSound::PlaySound(CSound::SOUND_LABEL_SE_SCREAM);

	//			CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 2, 20.0f, 20.0f);

	//			/*SetState(ENEMYSTATE_NONE);*/

	//			SetMove(D3DXVECTOR3(-3.0f, move.y, 0.0f));
	//		}

	//		SetPosition(pos);
	//	}
	//}

	/*if (bShowenemy == false)
	{
		m_Enemystate = ENEMYSTATE_NONE;

		SetState(m_Enemystate);
	}*/

	/*if (bShowenemy == true && pos.z > 0.0f)
	{
		m_Enemystate = ENEMYSTATE_STANBY;

		SetState(m_Enemystate);
	}*/

	SetRot(rot);

	//�f�o�b�O�\���̏���n��
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("�G�̑��� : %d\n", m_nEnemy);

	//�G�̏ꏊ�f�o�b�N���
	pDebug->Print("�G�̏ꏊ X : %f Y : %f Z : %f\n", pos.x, pos.y, pos.z);

	pDebug->Print("�G�̈ړ��� X : %f Y : %f Z : %f\n", move.x, move.y, move.z);

	pDebug->Print("�G0�̗̑� : %d\n", m_nLife[0]);
	pDebug->Print("�G1�̗̑� : %d\n", m_nLife[1]);
	pDebug->Print("�G2�̗̑� : %d\n", m_nLife[2]);
#endif


	////�����x��100�ɂȂ�Ǝ��ʏ���
	//if (pTime->Get() == 100)
	//{
	//	//�p�[�e�B�N���̐���
	//	CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 1, 1.0f, 1.0f);

	//	m_bDeath = true;

	//	SetDeath(m_bDeath);
	//}
	/*return;*/

	D3DXVECTOR3 PosDiff; //���[�V�����̍��������߂�
	D3DXVECTOR3 RotDiff; //���[�V�����̍��������߂�

						 //���[�V�������}���p
	D3DXVECTOR3 MotionPos;
	D3DXVECTOR3 MotionRot;

	//�t���[���J�E���g�����Z
	m_nFrameCnt++;

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

		case MOTIONTYPE_PUNCH:

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

			else if (m_nKey == 4)
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

				m_bAttack = false;

			}
			break;

			case MOTIONTYPE_KICK:
				//���[�V�����L�b�N
				if (m_nKey == 0)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.8f;

					//�ӂ��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = -0.2f;

					//�݂��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//����ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

					//���ڂ̃p�[�c(���r)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.3f;

					//�ނ��ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = -0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = -1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = 0.0f;

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
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.8f;

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

				else if (m_nKey == 1)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.8f;

					//�ӂ��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = -0.2f;

					//�݂��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//����ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

					//���ڂ̃p�[�c(���r)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.3f;

					//�ނ��ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = -0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = -1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = 0.0f;

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
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.8f;

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

				else if (m_nKey == 2)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.8f;

					//�ӂ��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = -0.2f;

					//�݂��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//����ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

					//���ڂ̃p�[�c(���r)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.3f;

					//�ނ��ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = -0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = -1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = 0.0f;

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
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.8f;

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

				else if (m_nKey == 3)
				{
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.8f;

					//�ӂ��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotX = 0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotY = 0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[1].m_fRotZ = -0.2f;

					//�݂��ڂ̃p�[�c(��)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = -0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = 0.0f;

					//����ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotX = 1.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotY = -0.9f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[3].m_fRotZ = 0.3f;

					//���ڂ̃p�[�c(���r)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotX = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotY = -0.2f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[4].m_fRotZ = -0.3f;

					//�ނ��ڂ̃p�[�c(����)
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotY = 1.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[5].m_fRotZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotY = 1.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotY = -0.4f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[7].m_fRotZ = -0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotX = -0.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotY = -1.1f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[8].m_fRotZ = 0.1f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosY = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fPosZ = 0.0f;

					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotX = 0.0f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotY = 0.3f;
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[9].m_fRotZ = 0.0f;

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
					m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[13].m_fRotZ = 0.8f;

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

				else if (m_nKey == 4)
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

					m_bAttack = false;
				}
				break;

				case MOTIONTYPE_DAMAGE:
					//���[�V�����ړ�
					if (m_nKey == 0)
					{
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosX = 0.0f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosY = 0.0f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fPosZ = 0.0f;

						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotX = -0.1f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotY = -1.3f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[0].m_fRotZ = -0.2f;

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

						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotX = 0.2f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotY = 0.1f;
						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[2].m_fRotZ = -0.3f;

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

						m_aInfo[m_nType].aKeyinfo[nNextKey].aKey[6].m_fRotX = 1.5f;
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
					break;
		}
	}

	//�Đ��t���[�����ɒB�����猻�݂̃L�[��1�i�߂�
	m_nCounter++;

	m_aInfo[m_nKey].nNumKey = 1;

	
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
		if (m_nFrameCnt > 60)
		{
			m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
			m_nCounter = 0;
			m_nFrameCnt = 0;
		}

		break;

	case MOTIONTYPE_PUNCH:
		if (m_nFrameCnt > 60)
		{
			m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
			m_nCounter = 0;
			m_nFrameCnt = 0;

			if (m_nKey == 1)
			{
				SetMotionEnemy(MOTIONTYPE_NEUTRAL);
			}
		}

		break;

	case MOTIONTYPE_KICK:
		if (m_nFrameCnt > 60)
		{
			m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
			m_nCounter = 0;
			m_nFrameCnt = 0;

			if (m_nKey == 1)
			{
				SetMotionEnemy(MOTIONTYPE_NEUTRAL);
			}
		}
		break;

	case MOTIONTYPE_DAMAGE:
		if (m_nFrameCnt > 60)
		{
			m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;
			m_nCounter = 0;
			m_nFrameCnt = 0;
		}

		if (m_nKey == 1)
		{
			SetMotionEnemy(MOTIONTYPE_NEUTRAL);
		}

		break;
	}

	//m_nKey = (m_nKey + 1) % m_aInfo[m_nKey].nNumKey;

	/*m_nKey = (m_nKey + 1) % m_nKey;*/
		}

//============================
//�|���S���̕`��
//============================
void CEnemy::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRot();

	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X

	//D3DMATERIAL9 matDef;  //���݂̃}�e���A���ۑ��p

	//D3DXMATERIAL *pMat;	  //�}�e���A���f�[�^�ւ̃|�C���^
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

		if (m_bDeath == false)
		{
			for (int nCntMat = 0; nCntMat < m_nNumModel; nCntMat++)
			{
				if (m_Enemystate == ENEMYSTATE_NONE)
				{
					m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

					//���f��(�p�[�c)�̕`��
					m_apModel[nCntMat]->DrawCol(m_ColEnemy);
				}
				if (m_Enemystate == ENEMYSTATE_ATTACK)
				{
					//���f��(�p�[�c)�̕`��
					m_apModel[nCntMat]->Draw();
				}
				if (m_Enemystate == ENEMYSTATE_DAMAGE)
				{
					m_ColEnemy = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

					//���f��(�p�[�c)�̕`��
					m_apModel[nCntMat]->DrawCol(m_ColEnemy);
				}

				////���݂̃}�e���A�����擾
				//pDevice->GetMaterial(&matDef);

				////�}�e���A���f�[�^�ւ̃|�C���^���擾
				//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

			}
		}
		/*�ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);*/
}

//========================
//�G�̃_���[�W
//========================
void CEnemy::AddDamage(int nDamage,int nEnemy)
{
	m_nLife[nEnemy] = m_nLife[nEnemy] - nDamage;

	SetLife(m_nLife[nEnemy],nEnemy);

	m_Enemystate = ENEMYSTATE_DAMAGE;

	SetState(m_Enemystate);

	SetMotionEnemy(MOTIONTYPE_DAMAGE);

	//�f�o�b�O�\���̏���n��
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProck();
}

//==============================
//�u���b�N�Ƃ̓����蔻��(3D)
//==============================
bool CEnemy::HitBlock(void)
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
					if (GetPosition().z + ENEMY_MIN_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z
						&& GetPosition().z + ENEMY_MIN_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z)
					{
						if (GetPosition().y + ENEMY_MIN_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y
							&& GetPosition().y + ENEMY_MIN_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y)
						{
							//������̓����蔻��
							if (GetPosition().x + ENEMY_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x
								&& m_posold.x + ENEMY_MAX_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
							{//�v���C���[�ƃu���b�N���������� 

							 //�ʒu�������ɌŒ�
								SetPosition(D3DXVECTOR3(pObjectx->GetPosition().x + pObjectx->GetVtxMin().x - ENEMY_MAX_X, GetPosition().y, GetPosition().z));

								/*move.x = 0.0f;*/

								//�W�����v���ł���悤��
								SetJump(false);

								return true;
							}

							//�E����̓����蔻��
							if (GetPosition().x + ENEMY_MIN_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
								&& m_posold.x + ENEMY_MIN_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x)
							{//�v���C���[�ƃu���b�N���������� 

							 //�v���C���[���E���ɌŒ�
								SetPosition(D3DXVECTOR3(pObjectx->GetPosition().x + pObjectx->GetVtxMax().x - ENEMY_MIN_X, GetPosition().y, GetPosition().z));

								move.x = 0.0f;

								//�W�����v���ł���悤��
								SetJump(false);

								return true;

								////�W�����v���ł���悤��
								//SetJump(false);

							}
						}
					}

					if (GetPosition().x + ENEMY_MAX_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
						&& GetPosition().x + ENEMY_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
					{
						//��O����̓����蔻��
						if (GetPosition().z + ENEMY_MAX_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z
							&& m_posold.z + ENEMY_MAX_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMin().z)
						{//�v���C���[�ƃu���b�N���������� 

						 //�v���C���[�������ɌŒ�
							SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, pObjectx->GetPosition().z + pObjectx->GetVtxMin().z - ENEMY_MAX_Z));

							/*move.x = 0.0f;*/

							////�W�����v���ł���悤��
							//SetJump(false);

						}

						//������̓����蔻��
						if (GetPosition().z + ENEMY_MIN_Z <= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z
							&& m_posold.z + ENEMY_MIN_Z >= pObjectx->GetPosition().z + pObjectx->GetVtxMax().z)
						{//�v���C���[�ƃu���b�N���������� 

						 //�v���C���[����O���ɌŒ�
							SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, pObjectx->GetPosition().z + pObjectx->GetVtxMax().z - ENEMY_MIN_Z));

							move.x = 0.0f;

							////�W�����v���ł���悤��
							//SetJump(false);

						}
					}

					if (GetPosition().x + ENEMY_MIN_X <= pObjectx->GetPosition().x + pObjectx->GetVtxMax().x
						&& GetPosition().x + ENEMY_MAX_X >= pObjectx->GetPosition().x + pObjectx->GetVtxMin().x)
					{
						//��O����̓����蔻��
						if (GetPosition().y + ENEMY_MAX_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y
							&& m_posold.y + ENEMY_MAX_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMin().y)
						{//�v���C���[�ƃu���b�N���������� 

						 //�v���C���[�������ɌŒ�
							SetPosition(D3DXVECTOR3(GetPosition().x, pObjectx->GetPosition().y - pObjectx->GetVtxMin().y - ENEMY_MAX_Y, GetPosition().z));

							move.y = 0.0f;

							//�W�����v���ł���悤��
							SetJump(false);

							////�W�����v���ł���悤��
							//SetJump(false);

						}

						//������̓����蔻��
						if (GetPosition().y + ENEMY_MIN_Y <= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y
							&& m_posold.y + ENEMY_MIN_Y >= pObjectx->GetPosition().y + pObjectx->GetVtxMax().y)
						{//�v���C���[�ƃu���b�N���������� 

						 //�v���C���[�������ɌŒ�
							SetPosition(D3DXVECTOR3(GetPosition().x, pObjectx->GetPosition().y + pObjectx->GetVtxMax().y + ENEMY_MIN_Y, GetPosition().z));

							move.y = 0.0f;

							//�W�����v���ł���悤��
							SetJump(false);

							////�W�����v���ł���悤��
							//SetJump(false);

						}
					}

				}
			}

			//�ʒu�ƈړ������Z�b�g
			SetPosition(GetPosition());
			SetMove(move);
		}
	}
	return false;
}

//============================
//�̗͂��Z�b�g����
//============================
void CEnemy::SetLife(int nLife,int nEnemy)
{
	if (nEnemy == 0)
	{
		nEnemy = 0;
	}

	if (nEnemy == 1)
	{
		nEnemy = 1;
	}

	if (nEnemy == 2)
	{
		nEnemy = 2;
	}

	m_nLife[nEnemy] = nLife;
}

//============================
//�̗͎擾
//============================
int CEnemy::GetLife(int nEnemy)
{
	return m_nLife[nEnemy];
}

//============================
//��Ԃ��Z�b�g����
//============================
void CEnemy::SetState(EnemyState state)
{
	/*if (nEnemy == 0)
	{
		nEnemy = 0;
	}

	if (nEnemy == 1)
	{
		nEnemy = 1;
	}

	if (nEnemy == 2)
	{
		nEnemy = 2;
	}
*/
	m_Enemystate = state;

	switch (m_Enemystate)
	{
	case ENEMYSTATE_NONE:

		

		break;

	case ENEMYSTATE_ATTACK:

		break;

	case ENEMYSTATE_DAMAGE:

			break;
		

	case ENEMYSTATE_GURD:

		break;
	}
}

//============================
//��Ԃ��擾
//============================
CEnemy::EnemyState CEnemy::GetState(int nEnemy)
{
	return m_Enemystate;
}

//============================
//�W�����v���Ă邩�ǂ������Z�b�g����
//============================
void CEnemy::SetJump(bool jump)
{
	m_bJump = jump;
}

//============================
//�W�����v���Ă邩�ǂ����̎擾
//============================
bool CEnemy::GetJump(void)
{
	return m_bJump;
}

//============================
//���S���Ă邩�ǂ����̎擾
//============================
bool CEnemy::GetDeath(void)
{
	return m_bDeath;
}

//============================
//���S���Ă邩�ǂ������Z�b�g����
//============================
void CEnemy::SetDeath(bool bDeath,int nEnemy)
{
	m_bDeath = bDeath;
}

//============================
//�G�����Ԃ߂��̎擾
//============================
int CEnemy::GetCnt(void)
{
	return m_nCnt;
}

//============================
//�G�����Ԃ߂��Z�b�g����
//============================
void CEnemy::SetCnt(int nCnt)
{
	m_nCnt = nCnt;
}

//============================
//���[�V�����̐ݒ�
//============================
void CEnemy::SetMotionEnemy(MOTIONTYPE nType)
{
	m_nType = nType;		 //���[�V�����̃^�C�v
	m_nKey = 0;				 //���݂̃L�[NO
	m_nCounter = 0;	 //���[�V�����J�E���^�[

	switch (m_nType)
	{
	case MOTIONTYPE_NEUTRAL:

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

		break;

	case MOTIONTYPE_MOVE:
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
	
		break;

	case MOTIONTYPE_PUNCH:
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
		
		break;

		case MOTIONTYPE_DAMAGE:
			//���[�V�����_���[�W
		
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosX = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosY = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fPosZ = 0.0f;
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotX = -0.1f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotY = -1.3f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[0].m_fRotZ = -0.2f;
										
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
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotX = 0.2f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotY = 0.1f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[2].m_fRotZ = -0.3f;
										  
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
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[6].m_fRotX = 1.5f;
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
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotY = -0.7f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[15].m_fRotZ = 0.0f;
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosX = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosY = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fPosZ = 0.0f;
										  
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotX = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotY = 0.0f;
				m_aInfo[m_nType].aKeyinfo[m_nKey].aKey[16].m_fRotZ = 0.0f;
			
			break;
	}

}