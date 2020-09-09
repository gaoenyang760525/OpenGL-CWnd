
// YM3DLibDlg.h : ͷ�ļ�
//

#pragma once

#include "YM3DLibGL.h"


// CYM3DLibDlg �Ի���
class CYM3DLibDlg : public CDialogEx
{
// ����
public:
	CYM3DLibDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YM3DLIB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��



	YM3DLibGL *yM3DLibGL;
	void InitOpenGL();


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
