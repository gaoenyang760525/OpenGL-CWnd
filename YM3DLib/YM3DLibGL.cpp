// YM3DLibGL.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YM3DLib.h"
#include "YM3DLibGL.h"

#include  <conio.h>//Ϊ�˵���������

// YM3DLibGL

IMPLEMENT_DYNAMIC(YM3DLibGL, CWnd)

YM3DLibGL::YM3DLibGL():m_bInit(FALSE), m_hDC(NULL), m_hRC(NULL), m_parent(NULL)
{

}

YM3DLibGL::~YM3DLibGL()
{
	KillGLWindow(); // Shutdown
}


BEGIN_MESSAGE_MAP(YM3DLibGL, CWnd)
	//{{AFX_MSG_MAP(COpenGL)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// YM3DLibGL ��Ϣ�������

void YM3DLibGL::Create(CRect rect, CWnd *parent)
{
	if (m_bInit) return;
	ASSERT(rect);
	ASSERT(parent);
	m_rect = rect;
	m_parent = parent;

	CString className = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL, (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);

	CreateEx(WS_EX_CLIENTEDGE, className, _T("YM3DLibGL"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

}


int YM3DLibGL::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &m_DMsaved);

	GLuint PixelFormat; // Holds The Results After Searching For A Match
	static PIXELFORMATDESCRIPTOR pfd = // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
		1, // Version Number
		PFD_DRAW_TO_WINDOW | // Format Must Support Window
		PFD_SUPPORT_OPENGL | // Format Must Support OpenGL
		PFD_DOUBLEBUFFER, // Must Support Double Buffering
		PFD_TYPE_RGBA, // Request An RGBA Format
		m_DMsaved.dmBitsPerPel, // Select Our Color Depth
		0, 0, 0, 0, 0, 0, // Color Bits Ignored
		0, // No Alpha Buffer
		0, // Shift Bit Ignored
		0, // No Accumulation Buffer
		0, 0, 0, 0, // Accumulation Bits Ignored
		16, // 16Bit Z-Buffer (Depth Buffer) 
		0, // No Stencil Buffer
		0, // No Auxiliary Buffer
		PFD_MAIN_PLANE, // Main Drawing Layer
		0, // Reserved
		0, 0, 0 // Layer Masks Ignored
	};

	if (!(m_hDC = ::GetDC(m_hWnd)))
	{ // Did We Get A Device Context? 
		KillGLWindow(); // Reset The Display
		TRACE("Can't Create A GL Device Context.");
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(m_hDC, &pfd)))
	{ // Did Windows Find A Matching Pixel Format? 
		KillGLWindow(); // Reset The Display
		TRACE("Can't Find A Suitable PixelFormat.");
		return FALSE;
	}

	if (!SetPixelFormat(m_hDC, PixelFormat, &pfd))
	{ // Are We Able To Set The Pixel Format? 
		KillGLWindow(); // Reset The Display
		TRACE("Can't Set The PixelFormat.");
		return FALSE;
	}

	if (!(m_hRC = wglCreateContext(m_hDC)))
	{ // Are We Able To Get A Rendering Context? 
		KillGLWindow(); // Reset The Display
		TRACE(" Can't Create A GL Rendering Context.");
		return FALSE;
	}


	if (!wglMakeCurrent(m_hDC, m_hRC)) { // Try To Activate The Rendering Context 
		KillGLWindow(); // Reset The Display
		TRACE("Can't Activate The GL Rendering Context.");
		return FALSE;
	}

	if (!InitGL())
	{ // Initialize Our Newly Created GL Window 
		KillGLWindow(); // Reset The Display
		TRACE("Initialization Failed.");
		return FALSE;
	}

	m_bInit = TRUE;
	return 0;
}

void YM3DLibGL::KillGLWindow()
{
	if (m_hRC)
	{ // Do We Have A Rendering Context? 
		if (!wglMakeCurrent(NULL, NULL))
		{ // Are We Able To Release The DC And RC Contexts?
			TRACE("Release Of DC And RC Failed.");
		}

		if (!wglDeleteContext(m_hRC))
		{ // Are We Able To Delete The RC?
			TRACE("Release Rendering Context Failed.");
		}
		m_hRC = NULL; // Set RC To NULL
	}

	if (m_hDC && !::ReleaseDC(m_hWnd, m_hDC))
	{ // Are We Able To Release The DC
		TRACE("Release Device Context Failed.");
		m_hDC = NULL; // Set DC To NULL
	}

	if (m_hWnd && !::DestroyWindow(m_hWnd))
	{ // Are We Able To Destroy The Window?
		TRACE("Could Not Release m_hWnd.");
		m_hWnd = NULL; // Set m_hWnd To NULL
	}
}

int YM3DLibGL::InitGL()
{
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f); // Black Background

	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D); // Enable Texture Mapping

	return TRUE; // Initialization Went OK 
}

void YM3DLibGL::RenderGLScene()
{


	if (!m_bInit)return;

	/*
		
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//��ģ��
	DrawXXX();

	SwapBuffers(m_hDC);

	*/


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear Screen And Depth Buffer
	glLoadIdentity();


	// EXAMPLE OPENGL CODE START
	//
	static GLfloat xrot;             // X Rotation
	static GLfloat yrot;             // Y Rotation
	static GLfloat zrot;             // Z Rotation

	glPushMatrix();               // Push Matrix Onto Stack (Copy The Current Matrix)
	glLoadIdentity();             // Reset The Current Modelview Matrix
	glTranslatef(0.0f, 0.0f, -6.0f);          // Move Left 1.5 Units And Into The Screen 6.0

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
	// Front Face
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Back Face
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Top Face
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Bottom Face
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Right face
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Left Face
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glEnd();
	glPopMatrix();              // Pop Matrix Off The Stack

	xrot += 1.3f;
	yrot += 1.2f;
	zrot += 1.4f;                // Decrease The Rotation Variable For The Quad
	//
	// EXAMPLE OPENGL CODE END //

	// Swap our scene to the front

	SwapBuffers(m_hDC);

	Invalidate(FALSE);
}


void YM3DLibGL::OnPaint()
{

	PreSetpaintGL();
	//CPaintDC dc(this); // device context for painting

	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);
	glRotatef(rotationZ, 0.0, 0.0, 1.0);
	glTranslatef(translateX, translateY, translateZ);
	glScalef(scaling, scaling, scaling);


	// TODO: Add your message handler code here
	::ValidateRect(m_hWnd, NULL);
	RenderGLScene();


	// Do not call CWnd::OnPaint() for painting messages
}
void YM3DLibGL::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (cy == 0)
	{ // Prevent A Divide By Zero By 
		cy = 1; // Making Height Equal One
	}

	glViewport(0, 0, cx, cy); // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION); //����ͶӰ����
	glLoadIdentity(); // ��ʼ��

	gluPerspective(45.0f, (GLfloat)cx / (GLfloat)cy, 0.1f, 100.0f); //�����ӵ�

	glMatrixMode(GL_MODELVIEW); //����ģ�;���
	glLoadIdentity(); // ��ʼ��

}


void YM3DLibGL::PreSetpaintGL()//Ԥ������opengl�Ļ�������
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //�����ɫ�������Ȼ��棬ÿ�λ�ͼǰ��������ջ�����
	glMatrixMode(GL_PROJECTION);//ͶӰ����
	glLoadIdentity();//Ȼ��Ѿ�������Ϊ��λ���󣬣��ڵ��ù�glMatrixMode()���������Ҫ���ø�����

	glOrtho(-2, 2, -2 * this->m_rect.Height() / this->m_rect.Width(), 2 * this->m_rect.Height() / this->m_rect.Width(), -10, 20);//ʹ������ͶӰ


	glMatrixMode(GL_MODELVIEW);//ģ�;�������
	glLoadIdentity();//���ڳ�������glGetFloatv()�����������õ�ǰ�������������һ�£��ڵ��ù�glMatrixMode()���������Ҫ���ø�����
	gluLookAt(0, 0, -15, 0, 0, 0, 0, 1, 0);//

	//    //���û��
	//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //ָ����Ϻ���
	//    glEnable(GL_BLEND);        //���û��״̬


}




int YM3DLibGL::DrawXXX()
{
	//����Ļ���

	_cprintf("DrawXXX");



	//���Ʋ�����
	glColor3f(0.0f, 1.0f, 255.0f);
	glBegin(GL_TRIANGLES); // Drawing Using Triangles
	glVertex3f(0.0f, 100.0f, 100.0f);     // Top
	glVertex3f(-100.0f, 0.0f, 100.0f);     // Bottom Left
	glVertex3f(100.0f, 100.0f, 100.0f);     // Bottom Right
	glEnd();           // Finished Drawing The Triangle

	return 1;
}



void YM3DLibGL::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();//Ϊ�˷�ֹ����û���㡣

	bIsLeftButtonDown = true;
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//_cprintf("OnLButtonDown ");
	GLlastPos = point;//Ϊ��openglƽ�����ŷ����� ���λ�ü�¼

	CWnd::OnLButtonDown(nFlags, point);
}


void YM3DLibGL::OnMouseMove(UINT nFlags, CPoint point)
{
	SetFocus();//Ϊ�˷�ֹ����û���㡣

	

	if (bIsLeftButtonDown)
	{	
		GLfloat dx = GLfloat(point.x - GLlastPos.x) / this->m_rect.Width();
		GLfloat dy = GLfloat(point.y - GLlastPos.y) / this->m_rect.Height();

		rotationX += 180 * dy;
		rotationY += 180 * dx;

		GLlastPos =point;
		Invalidate();


	}

	if (bIsMButtonDown)
	{		
		GLfloat dx = GLfloat(point.x - GLlastPos.x) / this->m_rect.Width();
		GLfloat dy = GLfloat(point.y - GLlastPos.y) / this->m_rect.Height();

		translateX += dx * 3;
		translateY -= dy * 3;

		GLlastPos =point;
		Invalidate();

	}


	CWnd::OnMouseMove(nFlags, point);
}


void YM3DLibGL::OnLButtonUp(UINT nFlags, CPoint point)
{
	SetFocus();//Ϊ�˷�ֹ����û���㡣

	bIsLeftButtonDown = false;
	

	CWnd::OnLButtonUp(nFlags, point);
}


void YM3DLibGL::OnMButtonUp(UINT nFlags, CPoint point)
{
	SetFocus();//Ϊ�˷�ֹ����û���㡣

	bIsMButtonDown = false;
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CWnd::OnMButtonUp(nFlags, point);
}


void YM3DLibGL::OnMButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();//Ϊ�˷�ֹ����û���㡣

	bIsMButtonDown = true;
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CWnd::OnMButtonDown(nFlags, point);
}


BOOL YM3DLibGL::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	_cprintf("OnMouseWheel ");

	double numDegrees = -zDelta / 8.0;
	double numSteps = numDegrees / 15.0;
	scaling *= std::pow(1.125, numSteps);

	Invalidate();






	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
