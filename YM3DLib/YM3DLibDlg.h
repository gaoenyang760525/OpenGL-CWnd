
// YM3DLibDlg.h : 头文件
//

#pragma once

#include "YM3DLibGL.h"


// CYM3DLibDlg 对话框
class CYM3DLibDlg : public CDialogEx
{
// 构造
public:
	CYM3DLibDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YM3DLIB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持



	YM3DLibGL *yM3DLibGL;
	void InitOpenGL();


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
