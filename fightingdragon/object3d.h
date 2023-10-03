//============================
//
//3D�I�u�W�F�N�g����(object3d.h)
//Author:���� �F�M
//
//============================
#ifndef _OBJECT3D_H_   //���̃}�N����`������Ă��Ȃ�������
#define _OBJECT3D_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object.h"

class CObject3d : public CObject
{
public:
	CObject3d();
	~CObject3d();

	static HRESULT Load(void);
	static void Unload(void);
	static CObject3d *Create(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex, float fWidth, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	float GetHeight(D3DXVECTOR3 pos);

	D3DXCOLOR GetColor(void);
	void SetColor(D3DXCOLOR col);

	bool GetShowEnemy(void);
	void SetShowEnemy(bool ShowEnemy);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`�����
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ʒu
	D3DXVECTOR3 m_rot;		//�X��

	D3DXCOLOR m_objectcol;	//�I�u�W�F�N�g�̐F
	int m_TimeBlinking;		//�_�Ŏ���

	bool m_bShowEnemy;		//�G���ڂ����ǂ���

	static CObject3d *m_pObject[320];
};


#endif


