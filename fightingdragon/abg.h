//============================
//
//�I�u�W�F�N�g2D���d�w�i(abg.h)
//Author:���� �F�M
//
//============================
#ifndef _ABG_H_   //���̃}�N����`������Ă��Ȃ�������
#define _ABG_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object2D.h"

//�O���N���X�錾
class CObject;


//�}�N����`
#define MAX_TEX (3)	//�w�i�̍ő吔

class CAbg : public CObject
{
public:

	//�e�N�X�`���̍\���̒�`
	typedef struct
	{
		D3DXVECTOR2 m_fTex;		//�e�N�X�`��
		D3DXVECTOR2 m_fMove;	//�ړ���
		CObject2D	*pObject2d;  //�I�u�W�F�N�g�̍쐬
	}SBG;

	CAbg();
	~CAbg();

	static HRESULT Load(void);
	static void Unload(void);
	
	static CAbg *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEX];				//�e�N�X�`���̃|�C���^

private:
	SBG m_apObject[MAX_TEX];						//�I�u�W�F�N�g2D�̕ϐ�
};


#endif

