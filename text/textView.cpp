
// textView.cpp: CtextView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "text.h"
#endif

#include "textDoc.h"
#include "textView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtextView

IMPLEMENT_DYNCREATE(CtextView, CView)

BEGIN_MESSAGE_MAP(CtextView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CtextView 构造/析构

CtextView::CtextView() noexcept
{
	// TODO: 在此处添加构造代码

}

CtextView::~CtextView()
{
}

BOOL CtextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CtextView 绘图

void CtextView::OnDraw(CDC* /*pDC*/)
{
	CtextDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CtextView 打印

BOOL CtextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CtextView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CtextView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CtextView 诊断

#ifdef _DEBUG
void CtextView::AssertValid() const
{
	CView::AssertValid();
}

void CtextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtextDoc* CtextView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtextDoc)));
	return (CtextDoc*)m_pDocument;
}
#endif //_DEBUG


// CtextView 消息处理程序


void CtextView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P0 = point;
	CView::OnLButtonDown(nFlags, point);
}


void CtextView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	P1 = point;
	CDC* pDC = GetDC();
	pDC->MoveTo(P0);
	pDC->LineTo(P1);
	ReleaseDC(pDC);
	CView::OnLButtonUp(nFlags, point);
}
