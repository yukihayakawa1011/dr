//============================
//
//�w�i����(bg.h)
//Author:���� �F�M
//
//============================
#ifndef _BG_H_   //���̃}�N����`������Ă��Ȃ�������
#define _BG_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����
#include "main.h"
#include "object2D.h"

class CBg : public CObject2D
{
public:
	CBg();
	~CBg();

	static CBg *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);

	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	
	float m_fAngle;								//�Ίp���̊p�x
	float m_fLength;							//�Ίp���̒���

	float m_fTex;								//�e�N�X�`���̈ړ���
										
};


#endif

