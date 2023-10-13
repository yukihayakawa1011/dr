//============================
//
//X�t�@�C������(objectx.h)
//Author:���� �F�M
//
//============================
#ifndef _OBJECTX_H_   //���̃}�N����`������Ă��Ȃ�������
#define _OBJECTX_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "manager.h"
#include "main.h"
#include "object.h"

//�}�N����`
#define MAX_OBJECTX  (5)		//�I�u�W�F�N�gX�̍ő吔

class CObjectx : public CObject
{
public:

	typedef struct
	{
		LPD3DXMESH m_pMesh;										//���b�V��
		LPD3DXBUFFER m_pBuffMat;						//���_���̃}�e���A��
		DWORD m_dwNumMat;								//�}�e���A��
		D3DXMATRIX m_mtxWorld;									//���[���h�}�g���b�N�X
		LPDIRECT3DTEXTURE9 m_apTexture[10] = {};		//�e�N�X�`���ւ̃|�C���^
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
	}SET_OBJECTX;

	CObjectx();
	~CObjectx();

	static CObjectx *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetCol(D3DXCOLOR col);
	/*void SetBuff(LPDIRECT3DVERTEXBUFFER9 Buff);*/
	void SetLife(int nLife);
	void SetVtxMax(D3DXVECTOR3 VtxMax);
	void SetVtxMin(D3DXVECTOR3 VtxMin);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);
	D3DXCOLOR GetCol(void);
	/*LPDIRECT3DVERTEXBUFFER9 GetBuff(void);*/
	int GetLife(void);
	D3DXVECTOR3 GetVtxMax(void);
	D3DXVECTOR3 GetVtxMin(void);

private:

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ʒu
	D3DXVECTOR3 m_rot;		//�X��
	D3DXCOLOR m_col;							//�F
	int m_nLife;								//�̗�

	SET_OBJECTX m_Objectx;		//���f���̏��

	static SET_OBJECTX Objectx[MAX_OBJECTX];		//���f���̏��

	int m_nTexCnt;		//�e�N�X�`�����̔ԍ�
	
};


#endif


