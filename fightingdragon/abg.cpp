////============================
////
////�I�u�W�F�N�g2D���d�w�i(abg.cpp)
////Author:���� �F�M
////
////============================
//#include "abg.h"
//#include "manager.h"
//#include "renderer.h"
//
////�ÓI�����o�ϐ��錾
//LPDIRECT3DTEXTURE9  CAbg::m_pTexture[MAX_TEX] = {};  //�e�N�X�`���̃|�C���^���N���A
////============================
////�R���X�g���N�^
////============================
//CAbg::CAbg()
//{
//	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	{
//		m_apObject[nCnt].pObject2d = NULL;
//		m_apObject[nCnt].m_fMove = D3DXVECTOR2(0.0f, 0.0f);
//		m_apObject[nCnt].m_fTex = D3DXVECTOR2(0.0f,0.0f);
//	}
//}
//
////============================
////�f�X�g���N�^
////============================
//CAbg::~CAbg()
//{
//
//}
//
////============================
////�e�N�X�`���̐���(�ǂݍ���)
////============================
//HRESULT CAbg::Load(void)
//{
//	//�f�o�C�X�̎擾
//	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();
//	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
//
//	//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile(pDevice,
//		"data\\TEXTURE\\bg.jpg",
//		&m_pTexture[0]);
//	
//	//�e�N�X�`���̓ǂݍ���
//	//D3DXCreateTextureFromFile(pDevice,
//	//	"data\\TEXTURE\\bg2.png",
//	//	&m_pTexture[1]);
//	//
//	////�e�N�X�`���̓ǂݍ���
//	//D3DXCreateTextureFromFile(pDevice,
//	//	"data\\TEXTURE\\bg102.png",
//	//	&m_pTexture[2]);
//	//
//		
//	return S_OK;
//}
//
////============================
////�e�N�X�`���̔j��
////============================
//void CAbg::Unload(void)
//{
//	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	{
//		//�e�N�X�`���̔j��
//		if (m_pTexture[nCnt] != NULL)
//		{
//			m_pTexture[nCnt]->Release();
//			m_pTexture[nCnt] = NULL;
//		}
//	}
//}
//
////============================
////��������
////============================
//CAbg *CAbg::Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
//{
//	CAbg *pAbg = NULL;
//
//	if (pAbg == NULL)
//	{
//		//�I�u�W�F�N�g2D�̐���
//		pAbg = NEW_DBG CAbg;
//
//		for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//		{
//			//����������
//			pAbg->Init(D3DXVECTOR3(pos.x, pos.y, pos.z), fRot, nCnt,fWidth,fHeight);
//
//		/*	pAbg->m_apObject[0].m_fMove = D3DXVECTOR2(0.001f, 0.0f);
//			pAbg->m_apObject[1].m_fMove = D3DXVECTOR2(0.0005f, 0.0f);
//			pAbg->m_apObject[2].m_fMove = D3DXVECTOR2(0.0001f, 0.0f);*/
//		}
//	}
//
//	return pAbg;
//}
//
////============================
////�|���S���̏�����
////============================
//HRESULT CAbg::Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight)
//{
//	if (m_apObject[nTex].pObject2d == NULL)
//	{
//
//		m_apObject[nTex].pObject2d = CObject2D::Create(pos, fRot, nTex, fWidth, fHeight);
//
//		m_apObject[nTex].pObject2d->Init(pos, fRot, nTex,fWidth,fHeight);
//
//		//�e�N�X�`��������
//		m_apObject[nTex].pObject2d->BindTexture(m_pTexture[nTex]);
//
//			VERTEX_2D *pVtx;    //���_���ւ̃|�C���^
//
//			/*���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾*/
//			m_apObject[nTex].pObject2d->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
//
//			//���_���W�̐ݒ�
//			pVtx[0].pos = D3DXVECTOR3(pos.x - SCREEN_WIDTH, pos.y - SCREEN_HEIGHT, pos.z);
//			pVtx[1].pos = D3DXVECTOR3(pos.x + SCREEN_WIDTH, pos.y - SCREEN_HEIGHT, pos.z);
//			pVtx[2].pos = D3DXVECTOR3(pos.x - SCREEN_WIDTH, pos.y + SCREEN_HEIGHT, pos.z);
//			pVtx[3].pos = D3DXVECTOR3(pos.x + SCREEN_WIDTH, pos.y + SCREEN_HEIGHT, pos.z);
//
//			//rhw(�@��)�̐ݒ�
//			pVtx[0].rhw = 1.0f;
//			pVtx[1].rhw = 1.0f;
//			pVtx[2].rhw = 1.0f;
//			pVtx[3].rhw = 1.0f;
//
//			//���_�J���[�̐ݒ�
//			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//
//			//�e�N�X�`�����W�̐ݒ�
//			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//			m_apObject[nTex].pObject2d->SetPosition(pos);
//
//			//���_�o�b�t�@���A�����b�N����
//			m_apObject[nTex].pObject2d->GetBuff()->Unlock();
//		}
//
//	return S_OK;
//}
////============================
////�|���S���̏I��
////============================
//void CAbg::Uninit(void)
//{
//	//for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	//{
//	//	//�I������
//	//	m_apObject[nCnt].pObject2d->Uninit();
//	//}
//
//	//�I������
//	CObject::Release();
//}
////============================
////�|���S���̍X�V
////============================
//void CAbg::Update(void)
//{
//	//for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	//{
//	//	m_apObject[nCnt].m_fTex.x -= m_apObject[nCnt].m_fMove.x;
//	//	m_apObject[nCnt].m_fTex.y -= m_apObject[nCnt].m_fMove.y;
//
//	//	VERTEX_2D *pVtx;    //���_���ւ̃|�C���^
//
//	//	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
//	//	m_apObject[nCnt].pObject2d->GetBuff()->Lock(0, 0, (void**)&pVtx, 0);
//
//	//	//�e�N�X�`�����W�̍X�V
//	//	pVtx[0].tex = D3DXVECTOR2(m_apObject[nCnt].m_fTex.x, m_apObject[nCnt].m_fTex.y);
//	//	pVtx[1].tex = D3DXVECTOR2(m_apObject[nCnt].m_fTex.x + 1.0f, m_apObject[nCnt].m_fTex.y);
//	//	pVtx[2].tex = D3DXVECTOR2(m_apObject[nCnt].m_fTex.x, m_apObject[nCnt].m_fTex.y + 1.0f);
//	//	pVtx[3].tex = D3DXVECTOR2(m_apObject[nCnt].m_fTex.x + 1.0f, m_apObject[nCnt].m_fTex.y + 1.0f);
//	//	
//	//	//���_�o�b�t�@���A�����b�N����
//	//	m_apObject[nCnt].pObject2d->GetBuff()->Unlock();
//	//}
//}
////============================
////�|���S���̕`��
////============================
//void CAbg::Draw(void)
//{
//	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
//	{
//		m_apObject[nCnt].pObject2d->Draw();
//	}
//}
//
////============================
////�ʒu���Z�b�g����
////============================
//void CAbg::SetPosition(D3DXVECTOR3 pos)
//{
//	
//}
//
////============================
////�ʒu���Z�b�g����
////============================
//void CAbg::SetRot(D3DXVECTOR3 rot)
//{
//	
//}
//
////============================
//D3DXVECTOR3 CAbg::GetPosition(void)
//{
//	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//}
//
////============================
//D3DXVECTOR3 CAbg::GetMove(void)
//{
//	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//}
//
////============================
//D3DXVECTOR3 CAbg::GetRot(void)
//{
//	return D3DXVECTOR3(0.0f,0.0f,0.0f);
//}