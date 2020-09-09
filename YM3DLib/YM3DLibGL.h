#pragma once
#include <functional>

#include <gl/glu.h>
#include <gl/gl.h>
// YM3DLibGL

class YM3DLibGL : public CWnd
{
	DECLARE_DYNAMIC(YM3DLibGL)

public:
	YM3DLibGL();
	virtual ~YM3DLibGL();


public:
	virtual void RenderGLScene();
	void Create(CRect rect, CWnd *parent);
	void PreSetpaintGL();

	// Generated message map functions
protected:
	CRect m_rect;
	CWnd* m_parent;
	DEVMODE m_DMsaved;

public:
	// 根据需要增、删
	BOOL m_bInit;

	HDC m_hDC;
	HGLRC m_hRC;

	// 读取数据
	int DrawXXX();
	int InitGL();
	void KillGLWindow();

	//{{AFX_MSG(COpenGL)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);


	//}}AFX_MSG

protected:
	DECLARE_MESSAGE_MAP()

private:
	CPoint GLlastPos;
	GLfloat rotationX = 0;
	GLfloat rotationY = 0;
	GLfloat rotationZ = 0;

	GLfloat translateX = 0;
	GLfloat translateY = 0;
	GLfloat translateZ = 0;

	GLfloat scaling = 1.0;
	bool bIsLeftButtonDown = false;
	bool bIsMButtonDown = false;


public:
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


