
// MazeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Maze.h"
#include "MazeDlg.h"
#include "afxdialogex.h"
#include "PublicResources_Header.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

LinkList FeasibleList;                                                       //��ʾ�������ߵĵ���
TreeMaze LabyrinthTree;                                                      //����·����
Point CavalierPoint;                                                         //��ʿ���ڵ�λ��
Point PrincessPoint;                                                         //�������ڵ�λ��
TreeMaze FindPrincess;                                                       //�ҵ������ķ���

CString walkWay;
int ARRAY_SIZE = 10;                                                   //�����ͼ�Ĵ�С
char** MAP;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMazeDlg �Ի���



CMazeDlg::CMazeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAZE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMazeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMazeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CMazeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMazeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMazeDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMazeDlg::OnBnClickedButton4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CMazeDlg::OnDeltaposSpin1)
	ON_EN_CHANGE(IDC_EDIT2, &CMazeDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMazeDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMazeDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CMazeDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CMazeDlg::OnEnChangeEdit6)	
END_MESSAGE_MAP()


// CMazeDlg ��Ϣ�������

BOOL CMazeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->repaint = true;

	MAP = new char*[ARRAY_SIZE];
	for (int i = 0; i < ARRAY_SIZE; ++i) {
		MAP[i] = new char[ARRAY_SIZE];
	}
	char initMAP[10][10] = {                                   //�����ͼ������
		{ '1','1','1','1','1','1','1','1','1','1' },
		{ '1','0','0','1','0','0','0','1','0','#' },
		{ '1','0','0','1','0','0','0','1','0','1' },
		{ '1','0','0','0','0','1','1','0','0','1' },
		{ '1','0','1','1','1','0','0','0','0','1' },
		{ '1','0','0','P','1','0','0','0','0','1' },
		{ '1','0','1','0','0','0','1','0','0','1' },
		{ '1','0','1','1','1','0','1','1','0','1' },
		{ '1','1','0','0','0','0','0','0','0','1' },
		{ '1','1','1','1','1','1','1','1','1','1' },
	};
	for (int i = 0; i < ARRAY_SIZE; ++i) {
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			MAP[i][j] = initMAP[i][j];
		}
	}

	DoMaze();
	CString str;
	GetDlgItem(IDC_EDIT1)->SetWindowText(walkWay);
	GetDlgItem(IDC_EDIT2)->SetWindowText(_T("10"));

	str.Format(_T("%d"), CavalierPoint.GetX());
	GetDlgItem(IDC_EDIT3)->SetWindowText(str);
	str.Format(_T("%d"), CavalierPoint.GetY());
	GetDlgItem(IDC_EDIT4)->SetWindowText(str);
	str.Format(_T("%d"), PrincessPoint.GetX());
	GetDlgItem(IDC_EDIT5)->SetWindowText(str);
	str.Format(_T("%d"), PrincessPoint.GetY());
	GetDlgItem(IDC_EDIT6)->SetWindowText(str);

	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMazeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMazeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	if (repaint) {                                                           //repaint��Ϊ�ػ��ʶ�����״�ִ��ʱ�ػ津����ʧ�ܣ��ȿ�ʼ�ػ�ʱ�����ػ�
		Repaint();                                                           //�ػ�����Ҫ�Ĳ���
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMazeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMazeDlg::OnLButtonDown(UINT nID, CPoint point)
{
	CWnd* pWnd;
	CRect rc;
	CDC* pdc;
	pWnd = GetDlgItem(IDC_STATIC1);
	pWnd->GetWindowRect(rc);
	pdc = pWnd->GetDC();
	int width = rc.Width();
	int height = rc.Height();
	int rectWidth = (width - 5) / ARRAY_SIZE;
	int rectHeight = (height - 17) / ARRAY_SIZE;

	if (point.x < 9 || point.x>9 + width || point.y < 10 || point.y>10 + height) {
		return;
	}
	else {
		int tempX = point.x - 9 - 5;
		int tempY = point.y - 10 - 17;
		tempX /= rectWidth;
		tempY /= rectHeight;
		if (MAP[tempY][tempX] == '1') {
			MAP[tempY][tempX] = '0';
		}
		else if (MAP[tempY][tempX] == '0') {
			MAP[tempY][tempX] = '1';
		}
		repaint = true;
		walkWay = "";
		DoMaze();
		GetDlgItem(IDC_EDIT1)->SetWindowText(walkWay);
		InvalidateRect(NULL, true);                                                //���ô�����Ч
		UpdateWindow();                                                            //�����ػ棬����WM_PAINT
	}

}

void CMazeDlg::Repaint()
{
	CPaintDC dc(this);                                                       //׼������
	CWnd* pWnd;
	CRect rc;
	CDC* pdc;
	CPen newPen;                                                               //���ڴ����»���   
	CPen *pOldPen;                                                             //���ڴ�žɻ���   

	pWnd = GetDlgItem(IDC_STATIC1);
	pWnd->GetWindowRect(rc);
	pdc = pWnd->GetDC();
	int width = rc.Width();
	int height = rc.Height();

	CDC MemDC;                                                                 //���ȶ���һ����ʾ�豸����   
	CBitmap MemBitmap;                                                         //����һ��λͼ����
	MemDC.CreateCompatibleDC(NULL);                                            //���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	MemBitmap.CreateCompatibleBitmap(pdc, width, height);                      //���潨��һ������Ļ��ʾ���ݵ�λͼ
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);                         //��λͼѡ�뵽�ڴ���ʾ�豸��//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
	MemDC.FillSolidRect(0, 0, width, height, RGB(240, 240, 240));              //���ñ���ɫ��λͼ����ɾ�
	MemDC.Rectangle(5, 17, width - 5, height - 5);

	int rectWidth = (width - 5) / ARRAY_SIZE;
	int rectHeight = (height - 17) / ARRAY_SIZE;


	for (int i = 0; i < ARRAY_SIZE; ++i) {
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			int tempX = 5 + j*rectWidth;
			int tempY = 17 + i*rectHeight;
			rc.SetRect(tempX, tempY, tempX + rectWidth, tempY + rectHeight);
			if (MAP[i][j] == '1') {
				MemDC.FillSolidRect(&rc, RGB(140, 80, 30));
			}
			else if (MAP[i][j] == '0') {
				MemDC.FillSolidRect(&rc, RGB(170, 170, 170));
			}
			else if (MAP[i][j] == 'P') {
				this->SetBMPfile(&MemDC, rc, 'P');
			}
			else {
				this->SetBMPfile(&MemDC, rc, '#');
			}
		}
	}

	newPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));                               //����ʵ�Ļ��ʣ��ֶ�Ϊ1����ɫΪ��ɫ
	pOldPen = MemDC.SelectObject(&newPen);                                     //ѡ���»��ʣ������ɻ��ʵ�ָ�뱣�浽pOldPen

	for (int i = 1; i < ARRAY_SIZE; ++i) {
		MemDC.MoveTo(5 + i*rectWidth, 17);
		MemDC.LineTo(5 + i*rectWidth, 17 + ARRAY_SIZE*rectHeight);

		MemDC.MoveTo(5, 17 + i*rectHeight);
		MemDC.LineTo(5 + ARRAY_SIZE*rectWidth, 17 + i*rectHeight);
	}

	pdc->BitBlt(0, 0, width, height, &MemDC, 0, 0, SRCCOPY);                   //���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ

	MemBitmap.DeleteObject();                                                  //��ͼ��ɺ������
	MemDC.DeleteDC();
}

void CMazeDlg::SetBMPfile(CDC *MemDC, CRect rc, char people)
{
	BITMAPINFO *pBmpInfo;                                                      //��¼ͼ��ϸ��
	BYTE *pBmpData;                                                            //ͼ������
	BITMAPFILEHEADER bmpHeader;                                                //�ļ�ͷ
	BITMAPINFOHEADER bmpInfo;                                                  //��Ϣͷ
	CFile bmpFile;                                                             //��¼���ļ�

	if (people == 'P') {
		if (!bmpFile.Open(_T("res//Cavalier.bmp"), CFile::modeRead | CFile::typeBinary))
			return;
	}
	else if (people == '#') {
		if (!bmpFile.Open(_T("res//Princess.bmp"), CFile::modeRead | CFile::typeBinary))
			return;
	}
	if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
	//Ϊͼ����������ռ�
	memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
	DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
	pBmpData = (BYTE*)new char[dataBytes];
	bmpFile.Read(pBmpData, dataBytes);
	bmpFile.Close();

	//��ʾͼ��
	StretchDIBits(*MemDC, rc.TopLeft().x, rc.TopLeft().y, rc.Width(), rc.Height(), 0, 0,
		bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
}



void CMazeDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	int array_size = _ttoi(str);

	array_size = array_size < 5 ? 5 : array_size;
	array_size = array_size > 30 ? 30 : array_size;

	srand((unsigned)time(NULL));
	if (ARRAY_SIZE != array_size) {
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			delete MAP[i];
		}
		delete MAP;
		ARRAY_SIZE = array_size;
		MAP = new char*[ARRAY_SIZE];
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			MAP[i] = new char[ARRAY_SIZE];
		}
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			for (int j = 0; j < ARRAY_SIZE; ++j) {
				MAP[i][j] = (rand() % 100 <= 50) ? '1' : '0';
			}
		}

		Point cavalierPoint;                                                         //��ʿ���ڵ�λ��
		Point princessPoint;                                                         //�������ڵ�λ��
		do{
			cavalierPoint.InsertData(rand() % ARRAY_SIZE, rand() % ARRAY_SIZE);
			princessPoint.InsertData(rand() % ARRAY_SIZE, rand() % ARRAY_SIZE);
		} while (cavalierPoint == princessPoint);
		MAP[cavalierPoint.GetX()][cavalierPoint.GetY()] = 'P';
		MAP[princessPoint.GetX()][princessPoint.GetY()] = '#';
	}
	
	if (ARRAY_SIZE == 10) {
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			delete MAP[i];
		}
		delete MAP;
		MAP = new char*[ARRAY_SIZE];
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			MAP[i] = new char[ARRAY_SIZE];
		}
		char initMAP[10][10] = {                                   //�����ͼ������
			{ '1','1','1','1','1','1','1','1','1','1' },
			{ '1','0','0','1','0','0','0','1','0','#' },
			{ '1','0','0','1','0','0','0','1','0','1' },
			{ '1','0','0','0','0','1','1','0','0','1' },
			{ '1','0','1','1','1','0','0','0','0','1' },
			{ '1','0','0','P','1','0','0','0','0','1' },
			{ '1','0','1','0','0','0','1','0','0','1' },
			{ '1','0','1','1','1','0','1','1','0','1' },
			{ '1','1','0','0','0','0','0','0','0','1' },
			{ '1','1','1','1','1','1','1','1','1','1' },
		};
		for (int i = 0; i < ARRAY_SIZE; ++i) {
			for (int j = 0; j < ARRAY_SIZE; ++j) {
				MAP[i][j] = initMAP[i][j];
			}
		}
	}

	DoMaze();
	str.Format(_T("%d"), ARRAY_SIZE);
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	InvalidateRect(NULL, true);                                                //���ô�����Ч
	UpdateWindow();                                                            //�����ػ棬����WM_PAINT
}


void CMazeDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	str.Format(_T("%d"), ARRAY_SIZE);
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}


void CMazeDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}


void CMazeDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	int array_size = _ttoi(str);


	if (pNMUpDown->iDelta == -1){                                              //�����ֵΪ-1 , ˵�������Spin�����µļ�ͷ
		array_size -= 1;
	}else if (pNMUpDown->iDelta == 1){                                         //�����ֵΪ1, ˵�������Spin�����ϵļ�ͷ
		array_size += 1;
	}
	array_size = array_size < 5 ? 5 : array_size;
	array_size = array_size > 30 ? 30 : array_size;
	*pResult = 0;

	ARRAY_SIZE = array_size;
	str.Format(_T("%d"), ARRAY_SIZE);
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
}


void CMazeDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT3)->GetWindowText(str);
	int cavalierPoint_X = _ttoi(str);

	if (cavalierPoint_X < 0 || cavalierPoint_X >= ARRAY_SIZE) {
		cavalierPoint_X = 0;
		str.Format(_T("%d"), cavalierPoint_X);
		GetDlgItem(IDC_EDIT3)->SetWindowText(str);
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}


void CMazeDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT4)->GetWindowText(str);
	int cavalierPoint_Y = _ttoi(str);

	if (cavalierPoint_Y < 0 || cavalierPoint_Y >= ARRAY_SIZE) {
		cavalierPoint_Y = 0;
		str.Format(_T("%d"), cavalierPoint_Y);
		GetDlgItem(IDC_EDIT4)->SetWindowText(str);
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}


void CMazeDlg::OnEnChangeEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT5)->GetWindowText(str);
	int PrincessPoint_X = _ttoi(str);

	if (PrincessPoint_X < 0 || PrincessPoint_X >= ARRAY_SIZE) {
		PrincessPoint_X = ARRAY_SIZE - 1;
		str.Format(_T("%d"), PrincessPoint_X);
		GetDlgItem(IDC_EDIT5)->SetWindowText(str);
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}

void CMazeDlg::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_EDIT5)->GetWindowText(str);
	int PrincessPoint_Y = _ttoi(str);

	if (PrincessPoint_Y < 0 || PrincessPoint_Y >= ARRAY_SIZE) {
		PrincessPoint_Y = ARRAY_SIZE - 1;
		str.Format(_T("%d"), PrincessPoint_Y);
		GetDlgItem(IDC_EDIT5)->SetWindowText(str);
	}
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}


void CMazeDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	Point cavalierPoint;                                                         //��ʿ���ڵ�λ��
	Point princessPoint;                                                         //�������ڵ�λ��
	
	CString str_x,str_y;
	GetDlgItem(IDC_EDIT3)->GetWindowText(str_x);
	GetDlgItem(IDC_EDIT4)->GetWindowText(str_y);
	cavalierPoint.InsertData(_ttoi(str_x), _ttoi(str_y));
	GetDlgItem(IDC_EDIT5)->GetWindowText(str_x);
	GetDlgItem(IDC_EDIT6)->GetWindowText(str_y);
	princessPoint.InsertData(_ttoi(str_x), _ttoi(str_y));

	if (cavalierPoint == princessPoint) {
	}
	else {
		MAP[CavalierPoint.GetX()][CavalierPoint.GetY()] = MAP[PrincessPoint.GetX()][PrincessPoint.GetY()] = '0';
		CavalierPoint = cavalierPoint;
		PrincessPoint = princessPoint;
		MAP[CavalierPoint.GetX()][CavalierPoint.GetY()] = 'P';
		MAP[PrincessPoint.GetX()][PrincessPoint.GetY()] = '#';
	}
	this->OnBnClickedButton4();
	InvalidateRect(NULL, true);                                                //���ô�����Ч
	UpdateWindow();                                                            //�����ػ棬����WM_PAINT
}


void CMazeDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;
	str.Format(_T("%d"), CavalierPoint.GetX());
	GetDlgItem(IDC_EDIT3)->SetWindowText(str);
	str.Format(_T("%d"), CavalierPoint.GetY());
	GetDlgItem(IDC_EDIT4)->SetWindowText(str);
	str.Format(_T("%d"), PrincessPoint.GetX());
	GetDlgItem(IDC_EDIT5)->SetWindowText(str);
	str.Format(_T("%d"), PrincessPoint.GetY());
	GetDlgItem(IDC_EDIT6)->SetWindowText(str);

	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}
