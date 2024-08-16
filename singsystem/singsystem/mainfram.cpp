// mainfram.cpp: 实现文件
//

#include "pch.h"
#include "singsystem.h"
#include "afxdialogex.h"
#include "mainfram.h"

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<windows.h>
#include<cstdio>
// mainfram 对话框
#define NAME 40
#define ID 20
#define LEN sizeof(struct PupllStudent)
#define FORMAT "%-10s%-10s%-15s%-20s%\n"
#define DATA addrinfo[i].name,addrinfo[i].gender,addrinfo[i].song,addrinfo[i].score
using namespace std;

IMPLEMENT_DYNAMIC(mainfram, CDialogEx)
typedef struct Singer
{
	char name[NAME];
	char gender[10];
	char song[NAME];
	char score[ID];
}Singer;
Singer singer;

mainfram::mainfram(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_name(_T(""))
	, m_score(_T(""))
	, m_song(_T(""))
	, m_gender(_T(""))
	, m_search(_T(""))
{

	m_listSelpos = 0;
}

mainfram::~mainfram()
{
}

void mainfram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, m_ctrList);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_SCORE, m_score);
	DDX_Text(pDX, IDC_SONG, m_song);
	DDX_Text(pDX, IDC_GENDER, m_gender);
	DDX_Text(pDX, IDC_SEARCH, m_search);
}


BEGIN_MESSAGE_MAP(mainfram, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &mainfram::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &mainfram::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &mainfram::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &mainfram::Ondelete)
	ON_BN_CLICKED(IDC_BUTTON4, &mainfram::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &mainfram::Onchangedata)
	ON_BN_CLICKED(IDC_BUTTON5, &mainfram::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &mainfram::Onsearchdata)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// mainfram 消息处理程序


BOOL mainfram::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.InsertColumn(0, _T("歌手名字"), LVCFMT_LEFT, 220);
	m_List.InsertColumn(1, _T("性别"), LVCFMT_LEFT, 220);
	m_List.InsertColumn(2, _T("歌曲"), LVCFMT_LEFT, 220);
	m_List.InsertColumn(3, _T("评分"), LVCFMT_LEFT, 220);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void mainfram::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_List.InsertItem(0, m_name);
	m_List.SetItemText(0,1, m_gender);
	m_List.SetItemText(0,2, m_song);
	m_List.SetItemText(0,3, m_score);
	string filename = "data.txt";
	ofstream file;
	file.open("data.txt", ios::app);
	if (file.is_open())
	{
		file << m_name << " " << m_gender << " " << m_song << " " << m_score << endl;
		file.close();
	}
}


void mainfram::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void mainfram::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void mainfram::Ondelete()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listSelpos=0;
	m_listSelpos = m_List.GetSelectionMark();
	m_name = m_List.GetItemText(m_listSelpos, 0);
	m_List.DeleteItem(m_listSelpos);

	
	ifstream ff;
	ofstream fp;
	ff.open("data.txt");
	fp.open("datal.txt");
	if (ff.is_open())
	{
		while (ff >> singer.name >> singer.gender >> singer.song >> singer.score)
		{
			if (singer.name == m_name)
			{
				continue;
			}
			else
			{
				fp << singer.name << " " << singer.gender << " " << singer.song << " " << singer.score << endl;
			}
		}
	}
	ff.close();
	fp.close();
	ofstream f1;
	ifstream f2;
	f1.open("data.txt");
	f2.open("datal.txt");
	while (f2 >> singer.name >> singer.gender >> singer.song >> singer.score)
	{
		f1 << singer.name << " " << singer.gender << " " << singer.song << " " << singer.score << endl;
	}
	f1.close();
	f2.close();

}


void mainfram::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	m_listSelpos = 0;
	m_listSelpos = m_List.GetSelectionMark();
	m_name = m_List.GetItemText(m_listSelpos, 0);
	m_gender = m_List.GetItemText(m_listSelpos, 1);
	m_song = m_List.GetItemText(m_listSelpos, 2);
	m_score = m_List.GetItemText(m_listSelpos, 3);
	UpdateData(FALSE);
	
}


void mainfram::Onchangedata()
{
	
	Ondelete();
	OnBnClickedButton1();
}


void mainfram::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_List.DeleteAllItems();
	ifstream ff;
	ff.open("data.txt");

	if (ff.is_open())
	{
		while (ff >> singer.name >> singer.gender >> singer.song >> singer.score)
		{
			m_List.InsertItem(0, singer.name);
			m_List.SetItemText(0, 1, singer.gender);
			m_List.SetItemText(0, 2, singer.song);
			m_List.SetItemText(0, 3, singer.score);
		}
	}
	ff.close();
}


void mainfram::Onsearchdata()
{
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码
	ifstream ff;
	ff.open("data.txt");
	m_List.DeleteAllItems();
	if (ff.is_open())
	{
		while (ff >> singer.name >> singer.gender >> singer.song >> singer.score)
		{
			if (singer.name == m_search)
			{
				m_name = singer.name;
				m_gender = singer.gender;
				m_song = singer.song;
				m_score = singer.score;
				UpdateData(FALSE);
				m_List.InsertItem(0, m_name);
				m_List.SetItemText(0, 1, m_gender);
				m_List.SetItemText(0, 2, m_song);
				m_List.SetItemText(0, 3, m_score);
				break;
			}
			else
			{
				continue;
			}
		}
	}
	ff.close();
	
}


void mainfram::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CDialogEx::OnPaint();
		CBitmap   bitmap;                            //定义位图
	bitmap.LoadBitmap(IDB_BITMAP2);    //这个IDB_BITMAP1要自己添加
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 1590, 1250);                  //前两个为图片起始位置，后两个为图片终点位置，实际为图片的像素大小
	dc.SelectObject(pOldBrush);
}
