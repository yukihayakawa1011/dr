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

//�ÓI�����o�ϐ��錾
int CEnemy::m_nLife[MAX_ENEMY] = {};

//============================
//�R���X�g���N�^
//============================
CEnemy::CEnemy()
{
	m_Enemystate = ENEMYSTATE_STANBY;
	nCntEnemy = 0;										//���Ԗڂ̓G���m��

	m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	m_nCntState = 0;
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

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
		m_Enemystate = ENEMYSTATE_STANBY;

		SetState(m_Enemystate);

		m_nCntState = 60;

	//�S�Ẵp�[�c����������
	m_nNumModel = MAX_MODEL;

	//���f������
	m_apModel[0] = CModel::Create(D3DXVECTOR3(0.0f, 40.0f, 0.0f), fRot, 0, fWidth, fHeight);
	m_apModel[1] = CModel::Create(D3DXVECTOR3(0.0f, -1.0f, 0.0f), fRot, 1, fWidth, fHeight);
	m_apModel[2] = CModel::Create(D3DXVECTOR3(0.0f, 18.0f, 0.0f), fRot, 2, fWidth, fHeight);
	m_apModel[3] = CModel::Create(D3DXVECTOR3(4.0f, -10.0f, 0.0f), fRot, 3, fWidth, fHeight);
	m_apModel[4] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 0.0f), fRot, 4, fWidth, fHeight);
	m_apModel[5] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 5, fWidth, fHeight);
	m_apModel[6] = CModel::Create(D3DXVECTOR3(-4.0f, -10.0f, 0.0f), fRot, 6, fWidth, fHeight);
	m_apModel[7] = CModel::Create(D3DXVECTOR3(0.3f, -10.0f, 1.0f), fRot, 7, fWidth, fHeight);
	m_apModel[8] = CModel::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), fRot, 8, fWidth, fHeight);
	m_apModel[9] = CModel::Create(D3DXVECTOR3(5.0f, 15.0f, -1.0f), fRot, 9, fWidth, fHeight);
	m_apModel[10] = CModel::Create(D3DXVECTOR3(5.0f, 0.0f, 0.0f), fRot, 10, fWidth, fHeight);
	m_apModel[11] = CModel::Create(D3DXVECTOR3(5.7f, 0.0f, 0.0f), fRot, 11, fWidth, fHeight);
	m_apModel[12] = CModel::Create(D3DXVECTOR3(6.0f, 0.0f, 0.0f), fRot, 12, fWidth, fHeight);
	m_apModel[13] = CModel::Create(D3DXVECTOR3(-5.0f, 15.0f, -1.0f), fRot, 13, fWidth, fHeight);
	m_apModel[14] = CModel::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.5f), fRot, 14, fWidth, fHeight);
	m_apModel[15] = CModel::Create(D3DXVECTOR3(-5.7f, 0.0f, -0.5f), fRot, 15, fWidth, fHeight);
	m_apModel[16] = CModel::Create(D3DXVECTOR3(-6.0f, 0.0f, 0.0f), fRot, 16, fWidth, fHeight);

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

	if (nTex == 0)
	{
		m_nLife[0] = 5;

		SetLife(m_nLife[nTex], nTex);
	}

	if (nTex == 1)
	{
		m_nLife[1] = 5;

		SetLife(m_nLife[nTex], nTex);
	}

	if (nTex == 2)
	{
		m_nLife[2] = 5;

		SetLife(m_nLife[nTex], nTex);
	}

	m_ColEnemy = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	SetCol(m_ColEnemy);
	
	D3DXVECTOR3 move = GetMove();

	//�ړ��ʂ̏�����
	move.x = 3.0f;

	//�ړ��ʂ̃Z�b�g
	SetMove(move);

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

	//�I�u�W�F�N�g3d�̃f�[�^�����炤
	CObject3d *pobject3d = CGame::GetObject3d();
	bool bShowenemy = pobject3d->GetShowEnemy();

	D3DXVECTOR3 pos = GetPosition();

	m_posold = pos; //�O��̈ʒu���L�^

	D3DXVECTOR3 move = GetMove();

	D3DXVECTOR3 rot = GetRot();

	CPlayer *m_pPlayer = CGame::GetPlayer();

	if (pos.z <= 0.0f)
	{//�G�̈ʒu(Z)��0��������
		bShowenemy = true;

		pobject3d->SetShowEnemy(bShowenemy);

		m_Enemystate = ENEMYSTATE_ATTACK;

		SetState(m_Enemystate);

		if (move.x <= 0.0f)
		{
			rot.y = D3DX_PI * 0.5f;
		}
		else
		{
			rot.y = D3DX_PI * -0.5f;
		}

		//�d�͏���
		move.y -= 0.5f;

		if (move.y >= -1.0f)
		{
			m_bJump = true;

			SetJump(m_bJump);
		}

		//���̔���
		if (pos.y <= 1.0f)
		{
			m_bJump = false;
			move.y = 0.0f;
			pos.y = 1.0f;

			SetJump(m_bJump);
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

	else
	{//�G�̈ʒu(Z)��0�ȊO��������
		if (m_pPlayer->GetPosition().x - 100.0f <= pos.x + 200.0f
			&&m_pPlayer->GetPosition().x + 10.0f >= pos.x
			&& m_pPlayer->GetPosition().y + 5.0f >= pos.y)
		{
			bShowenemy = false;

			pobject3d->SetShowEnemy(bShowenemy);

			move.z = -8.0f;

			pos.z += move.z;

			if (pos.z <= 0.0f)
			{
				pos.z = 0.0f;
			}

			if (pos.z >= 8.0f && pos.z <= 11.0f)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_WINDOW);
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SCREAM);

				CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 2, 20.0f, 20.0f);

				/*SetState(ENEMYSTATE_NONE);*/
			}

			SetPosition(pos);

		}

		if (m_pPlayer->GetPosition().x + 50.0f <= pos.x
			&&m_pPlayer->GetPosition().x - 10.0f >= pos.x - 200.0f
			&& m_pPlayer->GetPosition().y + 5.0f >= pos.y)
		{
			bShowenemy = false;

			pobject3d->SetShowEnemy(bShowenemy);

			move.z = -8.0f;

			pos.z += move.z;

			if (pos.z <= 0.0f)
			{
				pos.z = 0.0f;
			}

			if (pos.z >= 8.0f && pos.z <= 11.0f)
			{
				CSound::PlaySound(CSound::SOUND_LABEL_SE_WINDOW);
				CSound::PlaySound(CSound::SOUND_LABEL_SE_SCREAM);

				CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 2, 20.0f, 20.0f);

				/*SetState(ENEMYSTATE_NONE);*/

				SetMove(D3DXVECTOR3(-3.0f, move.y, 0.0f));
			}

			SetPosition(pos);
		}
	}

	if (bShowenemy == false)
	{
		m_Enemystate = ENEMYSTATE_NONE;

		SetState(m_Enemystate);
	}

	if (bShowenemy == true && pos.z > 0.0f)
	{
		m_Enemystate = ENEMYSTATE_STANBY;

		SetState(m_Enemystate);
	}

	SetRot(rot);

	//�f�o�b�O�\���̏���n��
	CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("�G�̑��� : %d\n", m_nEnemy);

	//�G�̏ꏊ�f�o�b�N���
	pDebug->Print("�G�̏ꏊ X : %f Y : %f Z : %f\n", pos.x, pos.y, pos.z);

	pDebug->Print("�G�̈ړ��� X : %f Y : %f Z : %f\n", move.x, move.y, move.z);

	pDebug->Print("�G0�̗̑� : %d\n", m_nLife[0]);
	pDebug->Print("�G1�̗̑� : %d\n", m_nLife[1]);
	pDebug->Print("�G2�̗̑� : %d\n", m_nLife[2]);
#endif

	//VERTEX_2D *pVtx;    //���_���ւ̃|�C���^

	//					/*���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾*/
	//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y - 10.0f + move.y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y - 10.0f + move.y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - 10.0f, pos.y + 10.0f + move.y, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + 10.0f, pos.y + 10.0f + move.y, 0.0f);

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

	////���_�o�b�t�@���A�����b�N����
	//m_pVtxBuff->Unlock();

	/*if (m_nLife < 0)
	{
		CExplosion::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), 0.0f, 0);

		Release();
	}*/

	

}
//============================
//�|���S���̕`��
//============================
void CEnemy::Draw(void)
{
	//�f�o�C�X�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
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

		for (int nCntMat = 0; nCntMat < m_nNumModel; nCntMat++)
		{
			if (m_Enemystate == ENEMYSTATE_STANBY)
			{
				m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

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

			if (m_Enemystate == ENEMYSTATE_NONE)
			{
				m_ColEnemy = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

				//���f��(�p�[�c)�̕`��
				m_apModel[nCntMat]->DrawCol(m_ColEnemy);
			}

			////���݂̃}�e���A�����擾
			//pDevice->GetMaterial(&matDef);

			////�}�e���A���f�[�^�ւ̃|�C���^���擾
			//pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

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

	//�f�o�b�O�\���̏���n��
	CDebugProc *pDebug = CManager::GetDebugProck();

#ifdef _DEBUG
	pDebug->Print("�G%d�̗̑� : %d\n",nEnemy, m_nLife[0]);
	pDebug->Print("�G%d�̗̑� : %d\n",nEnemy + 1, m_nLife[1]);
	pDebug->Print("�G%d�̗̑� : %d\n",nEnemy + 2, m_nLife[2]);
#endif
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
	case ENEMYSTATE_STANBY:

		

		break;

	case ENEMYSTATE_ATTACK:

		m_nCntState = 60;

		break;

	case ENEMYSTATE_DAMAGE:

		m_nCntState--;

		if (m_nCntState == 0)
		{
			m_Enemystate = ENEMYSTATE_ATTACK;
		}

		break;

	case ENEMYSTATE_NONE:

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

////======================
////�G�̈ʒu�擾
////======================
//CEnemy CEnemy::GetPos(void)
//{
//	return m_pos;
//}
//
////======================
////�G�̈ʒu�ݒ�
////======================
//void CEnemy::SetPos(D3DXVECTOR3 pos)
//{
//	m_pos = pos;
//}
