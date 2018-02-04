#include "stdafx.h"
#include "ListCtrlEx.h"

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx()
{
	//��ʼ����ɫ
	m_theme_color.original_color = GRAY(180);
	CColorConvert::ConvertColor(m_theme_color);
}


CListCtrlEx::~CListCtrlEx()
{
}


void CListCtrlEx::SetColor(const ColorTable & colors)
{
	m_theme_color = colors;
	if (m_hWnd != NULL)
		Invalidate();
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CListCtrlEx::OnNMCustomdraw)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


void CListCtrlEx::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	LPNMLVCUSTOMDRAW lplvdr = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	NMCUSTOMDRAW& nmcd = lplvdr->nmcd;
	switch (lplvdr->nmcd.dwDrawStage)	//�ж�״̬   
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:			//���Ϊ��ITEM֮ǰ��Ҫ������ɫ�ĸı�
		if (IsWindowEnabled())
		{
			//��ѡ�������Ǹ�����ʱ������ɫ
			if (GetItemState(nmcd.dwItemSpec, LVIS_SELECTED) == LVIS_SELECTED && nmcd.dwItemSpec == m_highlight_item)
			{
				SetItemState(nmcd.dwItemSpec, 0, LVIS_SELECTED);
				lplvdr->clrText = m_theme_color.light3;
				lplvdr->clrTextBk = m_theme_color.dark1;
			}
			//����ѡ���е���ɫ
			else if (GetItemState(nmcd.dwItemSpec, LVIS_SELECTED) == LVIS_SELECTED)
			{
				SetItemState(nmcd.dwItemSpec, 0, LVIS_SELECTED);
				lplvdr->clrText = m_theme_color.dark3;
				lplvdr->clrTextBk = m_theme_color.light2;
			}
			//���ø����е���ɫ
			else if (nmcd.dwItemSpec == m_highlight_item)
			{
				lplvdr->clrText = m_theme_color.dark2;
				//lplvdr->clrText = 0;
				lplvdr->clrTextBk = m_theme_color.light3;
			}
			//����ż���е���ɫ
			else if (nmcd.dwItemSpec % 2 == 0)
			{
				lplvdr->clrText = CColorConvert::m_gray_color.dark3;
				lplvdr->clrTextBk = CColorConvert::m_gray_color.light3;
			}
			//���������е���ɫ
			else
			{
				lplvdr->clrText = CColorConvert::m_gray_color.dark3;
				lplvdr->clrTextBk = CColorConvert::m_gray_color.light4;
			}
		}
		else		//���ؼ�������ʱ����ʾ�ı���Ϊ��ɫ
		{
			lplvdr->clrText = GRAY(140);
			lplvdr->clrTextBk = GRAY(240);
		}
		*pResult = CDRF_DODEFAULT;
		break;
	}
}


void CListCtrlEx::PreSubclassWindow()
{
	// TODO: �ڴ�����ר�ô����/����û���
	SetBkColor(m_background_color);
	SetHightItem(-1);

	CListCtrl::PreSubclassWindow();
}


void CListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	this->SetFocus();
	CListCtrl::OnLButtonDown(nFlags, point);
}


void CListCtrlEx::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	this->SetFocus();
	CListCtrl::OnRButtonDown(nFlags, point);
}