//============================
//
//�A�j���[�V�����I�u�W�F�N�g����(anim.h)
//Author:���� �F�M
//
//============================
#ifndef _ANIM_H_   //���̃}�N����`������Ă��Ȃ�������
#define _ANIM_H_   //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object2D.h"

class CAnim : public CObject2D
{
public:
	CAnim();
	~CAnim();

	static CAnim *Create(D3DXVECTOR3 pos, float fRot, int nTex);
	HRESULT Init(D3DXVECTOR3 pos, float fRot, int nTex);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DrawAnim(void);

private:
	int m_nCounterAnim;							//�A�j���[�V�����J�E���^�[�����Z
	int m_nPatternAnim;							//�A�j���[�V�����p�^�[��

	float m_fAngle;								//�Ίp���̊p�x
	float m_fLength;							//�Ίp���̒���

	float m_pos;
	float m_move;

};


#endif
