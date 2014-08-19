#include "StdAfx.h"
#include "HideButton.h"

CHideButton::CHideButton(HWND hWnd, CDuiObject* pDuiObject)
						 : CControlBaseFont(hWnd, pDuiObject)
{
	m_enButtonState = enBSNormal;
	m_clrTextNormal = Color(39, 134, 230);
	m_clrTextHover = Color(93, 169, 242);
	m_clrTextDown = Color(21, 112, 235);
	m_clrTextDisable = Color(128, 128, 128);
	m_clrTip = Color(56, 56, 56);
	m_bDown = FALSE;
	m_bShowButton = false;

	m_strTip = _T("");
}

CHideButton::CHideButton(HWND hWnd, CDuiObject* pDuiObject, UINT uControlID, CRect rc, CString strTip, CString strTitle, Color clrTip,
						 Color clrTextNormal, Color clrTextHover, Color clrTextDown ,Color clrTextDisable,
						 BOOL bIsVisible, BOOL bIsDisable)
						 : CControlBaseFont(hWnd, pDuiObject, uControlID, rc, strTitle, bIsVisible, bIsDisable)
{
	m_enButtonState = enBSNormal;
	m_clrTextNormal = clrTextNormal;
	m_clrTextHover = clrTextHover;
	m_clrTextDown = clrTextDown;
	m_clrTextDisable = clrTextDisable;
	m_clrTip = clrTip;
	m_bDown = FALSE;
	m_bShowButton = false;

	m_strTip = strTip;
}

CHideButton::~CHideButton(void)
{

}

BOOL CHideButton::OnControlMouseMove(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_enButtonState;
	BOOL bOldShowBitton = m_bShowButton;
	if (!m_bIsDisable && m_enButtonState != enBSDown)
	{
		if(m_rc.PtInRect(point))
		{
			m_bShowButton = true;
			if(m_rcText.PtInRect(point))
			{
				m_enButtonState = enBSHover;
			}
			else
			{
				m_enButtonState = enBSNormal;
			}
		}
		else
		{
			m_bShowButton = false;
			m_enButtonState = enBSNormal;
		}
	}

	if(buttonState != m_enButtonState ||  bOldShowBitton != m_bShowButton)
	{
		UpdateControl();
		return true;
	}
	else
	{
		return false;
	}
}

BOOL CHideButton::OnControlLButtonDown(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_enButtonState;
	if (!m_bIsDisable)
	{
		if(m_rcText.PtInRect(point))
		{
			m_enButtonState = enBSDown;
			SendMessage(BUTTOM_DOWN, 0, 0);
		}
	}
	
	if(buttonState != m_enButtonState)
	{
		UpdateControl();
		return true;
	}
	else
	{
		return false;
	}
}

BOOL CHideButton::OnControlLButtonUp(UINT nFlags, CPoint point)
{
	enumButtonState buttonState = m_enButtonState;
	if (!m_bIsDisable)
	{
		if(m_rcText.PtInRect(point))
		{
			if(m_enButtonState == enBSDown)
			{
				SendMessage(BUTTOM_UP, 0, 0);
			}
			m_enButtonState = enBSHover;			
		}
		else
		{
			m_enButtonState = enBSNormal;
			if(!m_rc.PtInRect(point))
			{
				m_bShowButton = false;
			}
		}
	}
	
	if(buttonState != m_enButtonState)
	{
		UpdateControl();
		return true;
	}
	else
	{
		return false;
	}
}

void CHideButton::DrawControl(CDC &dc, CRect rcUpdate)
{
	int nWidth = m_rc.Width();
	int nHeight = m_rc.Height();

	if(!m_bUpdate)
	{		
		UpdateMemDC(dc, nWidth * 5, nHeight);
		
		for(int i = 0; i < 4; i++)
		{
			m_memDC.BitBlt(i * nWidth, 0, nWidth, nHeight, &dc, m_rc.left ,m_rc.top, SRCCOPY);
		}
		
		Color clrText[4] = {m_clrTextNormal, m_clrTextHover, m_clrTextDown, m_clrTextDisable};

		Graphics graphics(m_memDC);
		FontFamily fontFamily(m_strFont.AllocSysString());
		Font font(&fontFamily, (REAL)m_nFontWidth, m_fontStyle, UnitPixel);
		graphics.SetTextRenderingHint( TextRenderingHintClearTypeGridFit );

		// 设置水平和垂直对齐方式
		DUI_STRING_ALIGN_DEFINE();

		strFormat.SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsMeasureTrailingSpaces);
		Size sizeTip = GetTextBounds(font, strFormat, m_strTip);
		Size sizeText = GetTextBounds(font, strFormat, m_strTitle);
		CPoint point = GetOriginPoint(nWidth, nHeight, sizeText.Width, sizeText.Height, m_uAlignment, m_uVAlignment);
		
		m_rcText.SetRect(m_rc.left + sizeTip.Width + 10, m_rc.top + point.y, m_rc.left + sizeTip.Width + 10 + sizeText.Width, m_rc.top + point.y + sizeText.Height);
		
		SolidBrush solidBrushTip(m_clrTip);

		for(int i = 0; i < 4; i++)
		{
			RectF rect((Gdiplus::REAL)(i * nWidth), (Gdiplus::REAL)point.y, (Gdiplus::REAL)(sizeTip.Width + 10), (Gdiplus::REAL)sizeTip.Height);

			graphics.DrawString(m_strTip.AllocSysString(), (INT)wcslen(m_strTip.AllocSysString()), &font, 
				rect, &strFormat, &solidBrushTip);	

			if(i > 0)
			{
				SolidBrush solidBrush(clrText[i - 1]);	
				RectF rect((Gdiplus::REAL)(sizeTip.Width + 10 + i * nWidth), (Gdiplus::REAL)point.y, (Gdiplus::REAL)(nWidth - (sizeTip.Width + 10)), (Gdiplus::REAL)sizeText.Height);
				graphics.DrawString(m_strTitle.AllocSysString(), (INT)wcslen(m_strTitle.AllocSysString()), &font, 
					rect, &strFormat, &solidBrush);	
			}
		}
	}

	dc.BitBlt(m_rc.left,m_rc.top, m_rc.Width(), m_rc.Height(), &m_memDC, m_bShowButton ? (1 + m_enButtonState) * nWidth : 0, 0, SRCCOPY);
}