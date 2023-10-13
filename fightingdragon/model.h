//============================
//
//���f������(model.h)
//Author:���� �F�M
//
//============================
#ifndef _MODEL_H_   //���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "manager.h"
#include "main.h"
#include "object.h"

#define MAX_PART		  (17)		//�p�[�c�ő吔

class CModel 
{
public:

	typedef enum
	{
		MODELTYPE_PLAYER = 0,		//�v���C���[�̃��f��
		MODELTYPE_ENEMY0,			//�U�R�G�̃��f��
		MODELTYPE_ENEMY1,			//���{�X�̃��f��
		MODELTYPE_ENEMY2,			//�{�X�̃��f��
		MODELTYPE_MAX
	}MODELTYPE;

	typedef struct 
	{
		LPD3DXMESH m_pMesh;										//���b�V��
		LPD3DXBUFFER m_pBuffMat;						//���_���̃}�e���A��
		DWORD m_dwNumMat;								//�}�e���A��
		D3DXMATRIX m_mtxWorld;									//���[���h�}�g���b�N�X
		D3DXMATRIX m_mtxParent;									//�e�̃}�g���b�N�X
		LPDIRECT3DTEXTURE9 m_apTexture[10] = {};		//�e�N�X�`���ւ̃|�C���^
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
	}SET_MODEL;

	CModel();
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight,int nType);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawCol(D3DXCOLOR col);

	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void);

	void SetPos(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetVtxMax(D3DXVECTOR3 VtxMax);
	void SetVtxMin(D3DXVECTOR3 VtxMin);
	void SetBuffMat(LPD3DXBUFFER Mat);
	void SetModelType(MODELTYPE type);

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetVtxMax(void);
	D3DXVECTOR3 GetVtxMin(void);
	LPD3DXBUFFER GetBuffMat();
	SET_MODEL *GetModel(void);

private:
	
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//�X��

	CModel *m_pParent;		//�e���f���ւ̃|�C���^

	int nModel;		//���ڂ̃��f�����m�鏈��

	SET_MODEL Model;		//���f���̏��

	static SET_MODEL pModels[MAX_PART];		//���f���̏��

	int m_nIdx;								//���Ԗڂ̃p�[�c

	MODELTYPE m_Type;
};


#endif



