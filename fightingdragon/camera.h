//============================
//
//カメラ処理(camera.h)
//Author:早川 友貴
//
//============================
#ifndef _CAMERA_H_   //このマクロ定義がされていなかったら
#define _CAMERA_H_   //2重インクルード防止のマクロを定義する
#include "manager.h"
#include "main.h"
//#include "object.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
private:
	D3DXMATRIX m_mtxView;			//マトリックスのビュー
	D3DXMATRIX m_mtxProjection;		//マトリックスのプロジェクション

	D3DXVECTOR3 m_posV;				//視点
	D3DXVECTOR3 m_posR;				//注視点
	D3DXVECTOR3 m_vecU;				//方向ベクトル
	D3DXVECTOR3 m_rot;				//傾き

	float m_fAngle;					//角度
	float m_Length;					//距離
};


#endif

