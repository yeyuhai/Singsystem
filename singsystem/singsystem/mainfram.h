#pragma once
#include "afxdialogex.h"


// mainfram 对话框

class mainfram : public CDialogEx
{
	DECLARE_DYNAMIC(mainfram)

public:
	mainfram(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~mainfram();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	CListCtrl m_ctrList;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_List;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_name;
	CString m_score;
	CString m_song;
	CString m_gender;
	afx_msg void Ondelete();
	afx_msg void OnBnClickedButton4();
	afx_msg void Onchangedata();
	int m_listSelpos;
	afx_msg void OnBnClickedButton5();
	CString m_search;
	afx_msg void Onsearchdata();
	afx_msg void OnPaint();
};
