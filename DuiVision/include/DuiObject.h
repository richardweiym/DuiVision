#pragma once

//////////////////////////////////////////////////////////////////////////////////
// DuiVision Class Name Declaration
#define DUIOBJ_DECLARE_CLASS_NAME(theclass, classname)   \
public:                                                 \
    static CControlBase* CheckAndNew(LPCSTR lpszName, HWND hWnd, CDuiObject* pDuiObject)       \
    {                                                   \
        if (strcmp(GetClassName(), lpszName)  == 0)     \
		{\
			CControlBase* pControl = new theclass(hWnd, pDuiObject);							\
			return pControl;                        \
		}\
        else                                            \
            return NULL;                                \
    }                                                   \
                                                        \
    static LPCSTR GetClassName()                        \
    {                                                   \
        return classname;                               \
    }                                                   \
                                                        \
    virtual LPCSTR GetObjectClass()                     \
    {                                                   \
        return classname;                               \
    }                                                   \
                                                        \
    virtual BOOL IsClass(LPCSTR lpszName)               \
    {                                                   \
        if(strcmp(GetClassName(), lpszName)  == 0) return TRUE;  \
		return __super::IsClass(lpszName);				\
    }                                                   \
														\
	virtual LPCSTR BaseObjectClassName()				\
	{													\
		return __super::GetObjectClass();				\
	}													\


//////////////////////////////////////////////////////////////////////////
// Xml Attributes Declaration Map

// Attribute Declaration
#define DUI_DECLARE_ATTRIBUTES_BEGIN()                            \
public:                                                             \
    virtual HRESULT SetAttribute(                                   \
        CStringA strAttribName,                                     \
        CStringA strValue,                                          \
        BOOL     bLoading)                                          \
    {                                                               \
        HRESULT hRet = __super::SetAttribute(                       \
            strAttribName,                                          \
            strValue,                                               \
            bLoading                                                \
            );                                                      \
        if (SUCCEEDED(hRet))                                        \
            return hRet;                                            \

#define DUI_DECLARE_ATTRIBUTES_END()                              \
            return E_FAIL;                                          \
                                                                    \
        return hRet;                                                \
    }                                                               \

#define DUI_CHAIN_ATTRIBUTE(varname, allredraw)                   \
        if (SUCCEEDED(hRet = varname.SetAttribute(strAttribName, strValue, bLoading)))   \
        {                                                           \
            return hRet;                                            \
        }                                                           \
        else                                                        \

// Custom Attribute
// HRESULT OnAttributeChange(CStringA& strValue, BOOL bLoading)
#define DUI_CUSTOM_ATTRIBUTE(attribname, func)                    \
        if (attribname == strAttribName)                            \
        {                                                           \
            hRet = func(strValue, bLoading);                        \
        }                                                           \
        else                                                        \

// Int = %d StringA
#define DUI_INT_ATTRIBUTE(attribname, varname, allredraw)         \
        if (attribname == strAttribName)                            \
        {                                                           \
			    varname = ::StrToIntA(strValue);                    \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// bool = %d StringA
#define DUI_BOOL_ATTRIBUTE(attribname, varname, allredraw)         \
        if (attribname == strAttribName)                            \
        {                                                           \
		    varname = ::StrToIntA(strValue) > 0 ? true : false;     \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// UInt = %u StringA
#define DUI_UINT_ATTRIBUTE(attribname, varname, allredraw)        \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = (UINT)::StrToIntA(strValue);                  \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// DWORD = %u StringA
#define DUI_DWORD_ATTRIBUTE(attribname, varname, allredraw)       \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = (DWORD)::StrToIntA(strValue);                 \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// StringA = StringA
#define DUI_STRING_ATTRIBUTE(attribname, varname, allredraw)      \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = strValue;                                     \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// StringT = StringA
#define DUI_TSTRING_ATTRIBUTE(attribname, varname, allredraw)     \
        if (attribname == strAttribName)                            \
        {                                                           \
			ParseDuiString(strValue);	\
            varname = CA2T(strValue, CP_UTF8);                      \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// DWORD = %X StringA
#define DUI_HEX_ATTRIBUTE(attribname, varname, allredraw)         \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = CDuiObject::HexStringToULong(strValue);        \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// Color = %08X StringA
#define DUI_COLOR_ATTRIBUTE(attribname, varname, allredraw)       \
        if (attribname == strAttribName)                            \
        {                                                           \
			if(strValue.Find(",") == -1)	\
			{	\
				varname = CDuiObject::HexStringToColor(strValue);        \
			}else	\
			{	\
				varname = CDuiObject::StringToColor(strValue);        \
			}	\
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// COLORREF = %08X StringA
#define DUI_RGBCOLOR_ATTRIBUTE(attribname, varname, allredraw)       \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = CDuiObject::HexStringToRGBColor(strValue);        \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// HFONT = %04X StringA
#define DUI_FONT_ATTRIBUTE(attribname, varname, allredraw)        \
        if (attribname == strAttribName)                            \
        {                                                           \
            DWORD dwValue = CDuiObject::HexStringToULong(strValue);  \
            varname = DuiSystem::GetFont(LOWORD(dwValue));         \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// Value In {String1 : Value1, String2 : Value2 ...}
#define DUI_ENUM_ATTRIBUTE(attribname, vartype, allredraw)        \
        if (attribname == strAttribName)                            \
        {                                                           \
            vartype varTemp;                                        \
                                                                    \
            hRet = allredraw ? S_OK : S_FALSE;                      \

#define DUI_ENUM_VALUE(enumstring, enumvalue)                     \
            if (strValue == enumstring)                             \
                varTemp = enumvalue;                                \
            else                                                    \

#define DUI_ENUM_END(varname)                                     \
                return E_FAIL;                                      \
                                                                    \
            varname = varTemp;                                      \
        }                                                           \
        else                                                        \

// BkStyle From StringA Key
#define DUI_STYLE_ATTRIBUTE(attribname, varname, allredraw)       \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = DuiSystem::GetStyle(strValue);                  \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else                                                        \

// BkSkin From StringA Key
#define DUI_SKIN_ATTRIBUTE(attribname, varname, allredraw)        \
        if (attribname == strAttribName)                            \
        {                                                           \
            varname = DuiSystem::GetSkin(strValue);                    \
            hRet = allredraw ? S_OK : S_FALSE;                      \
        }                                                           \
        else   


//////////////////////////////////////////////////////////////////////////
// 图片属性的定义和实现代码宏,用于简化图片属性的相似代码实现
// 头文件中的定义,定义图片对象和图片大小对象,并定义设置图片和图片属性映射函数
#define DUI_IMAGE_ATTRIBUTE_DEFINE(imgName)	\
	Image*	m_pImage##imgName;	\
	CSize	m_size##imgName;	\
	BOOL Set##imgName##Bitmap(UINT nResourceID = 0, CString strType= TEXT("PNG"));	\
	BOOL Set##imgName##Bitmap(CString strImage = TEXT(""));	\
	HRESULT OnAttributeImage##imgName(const CStringA& strValue, BOOL bLoading);	\

// CPP代码中的设置图片和图片属性映射函数实现,图片对象和图片大小对象的初始化和析构需要自己写代码
#define DUI_IMAGE_ATTRIBUTE_IMPLEMENT(theclass, imgName, imgCount)	\
	BOOL theclass::Set##imgName##Bitmap(UINT nResourceID, CString strType)	\
	{	\
		if(m_pImage##imgName != NULL)	\
		{	\
			delete m_pImage##imgName;	\
			m_pImage##imgName = NULL;	\
		}	\
		\
		if(ImageFromIDResource(nResourceID, strType, m_pImage##imgName))	\
		{	\
			m_size##imgName.SetSize(m_pImage##imgName->GetWidth() / imgCount, m_pImage##imgName->GetHeight());	\
			return true;	\
		}	\
		return false;	\
	}	\
	BOOL theclass::Set##imgName##Bitmap(CString strImage)	\
	{	\
		if(m_pImage##imgName != NULL)	\
		{	\
			delete m_pImage##imgName;	\
			m_pImage##imgName = NULL;	\
		}	\
		\
		if(DuiSystem::Instance()->LoadImageFile(strImage, m_bImageUseECM, m_pImage##imgName))	\
		{	\
			m_size##imgName.SetSize(m_pImage##imgName->GetWidth() / imgCount, m_pImage##imgName->GetHeight());	\
			return true;	\
		}	\
		return false;	\
	}	\
	HRESULT theclass::OnAttributeImage##imgName(const CStringA& strValue, BOOL bLoading)	\
	{	\
		if (strValue.IsEmpty()) return E_FAIL;	\
		\
		CStringA strSkin = "";	\
		if(strValue.Find("skin:") == 0)	\
		{	\
			strSkin = DuiSystem::Instance()->GetSkin(strValue);	\
			if (strSkin.IsEmpty()) return E_FAIL;	\
		}else	\
		{	\
			strSkin = strValue;	\
		}	\
		\
		if(strSkin.Find(".") != -1)	\
		{	\
			CString strImgFile = CA2T(strSkin, CP_UTF8);	\
			if(strSkin.Find(":") != -1)	\
			{	\
				strImgFile = CA2T(strSkin, CP_UTF8);	\
			}	\
			if(!Set##imgName##Bitmap(strImgFile))	\
			{	\
				return E_FAIL;	\
			}	\
		}else	\
		{	\
			UINT nResourceID = atoi(strSkin);	\
			if(!Set##imgName##Bitmap(nResourceID, TEXT("PNG")))	\
			{	\
				if(!Set##imgName##Bitmap(nResourceID, TEXT("BMP")))	\
				{	\
					return E_FAIL;	\
				}	\
			}	\
		}	\
		\
		return bLoading?S_FALSE:S_OK;	\
	}	\


//////////////////////////////////////////////////////////////////////////
// 对齐方式设置宏
// 设置水平对齐方式和垂直对齐方式
#define DUI_STRING_ALIGN_DEFINE()	\
	StringFormat strFormat;	\
	if(m_uAlignment == Align_Left)	\
	{	\
		strFormat.SetAlignment(StringAlignmentNear);	\
	}else	\
	if(m_uAlignment == Align_Center)	\
	{	\
		strFormat.SetAlignment(StringAlignmentCenter);	\
	}else	\
	if(m_uAlignment == Align_Right)	\
	{	\
		strFormat.SetAlignment(StringAlignmentFar);	\
	}	\
	\
	if(m_uVAlignment == VAlign_Top)	\
	{	\
		strFormat.SetLineAlignment(StringAlignmentNear);	\
	}else	\
	if(m_uVAlignment == VAlign_Middle)	\
	{	\
		strFormat.SetLineAlignment(StringAlignmentCenter);	\
	}else	\
	if(m_uVAlignment == VAlign_Bottom)	\
	{	\
		strFormat.SetLineAlignment(StringAlignmentFar);	\
	}	\



class CControlBase;
class CDuiHandler;

// DUI基类
class CDuiObject
{
public:
	CDuiObject(void);
	virtual ~CDuiObject(void);

	virtual BOOL IsClass(LPCSTR lpszName) { return FALSE; }	// 是否此类
	virtual LPCSTR GetObjectClass() { return NULL; }		// 获取类名
	virtual LPCSTR BaseObjectClassName() { return NULL; }	// 获取基类名

	UINT GetID() {return m_uID;};							// 获取DUI对象ID
	void SetName(CString strName) { m_strName = strName; }	// 设置DUI对象名字
	CString GetName() {return m_strName;};					// 获取DUI对象名字
	BOOL IsThisObject(UINT uID, CString strName);			// 判断是否此对象

	BOOL RegisterHandler(CDuiHandler* pDuiHandler);			// 注册事件处理对象
	void SetDuiHandler(CDuiHandler* pDuiHandler) { m_pDuiHandler = pDuiHandler;	}	// 仅设置事件处理对象
	CDuiHandler* GetDuiHandler() { return m_pDuiHandler; }	// 获取事件处理对象

	virtual LRESULT OnBaseMessage(UINT	uID, UINT Msg, WPARAM wParam, LPARAM lParam) { return 0L; };
	virtual LRESULT OnControlUpdate(CRect rcUpdate, BOOL bUpdate = false, CControlBase *pControlBase = NULL) { return 0L; };
	
	virtual HRESULT SetAttribute(CStringA strAttribName, CStringA strValue, BOOL bLoading);
	virtual BOOL Load(TiXmlElement* pXmlElem, BOOL bLoadSubControl = TRUE);

	virtual void SetRect(CRect rc) { m_rc = rc;};
	virtual CRect GetRect() { return m_rc;};

	static void ParseDuiString(CStringA& strString);
	static ULONG HexStringToULong(LPCSTR lpszValue, int nSize = -1);
    static Color HexStringToColor(LPCSTR lpszValue);
	static Color StringToColor(LPCSTR lpszValue);
	static COLORREF HexStringToRGBColor(LPCSTR lpszValue);
	static void ParseKeyCode(LPCSTR lpszValue, UINT& nChar, UINT& nFlag);

protected:
	UINT	m_uID;					// DUI对象ID
	CString	m_strName;				// DUI对象名字
	CRect	m_rc;					// 区域
	CDuiHandler* m_pDuiHandler;		// 事件处理对象
};
