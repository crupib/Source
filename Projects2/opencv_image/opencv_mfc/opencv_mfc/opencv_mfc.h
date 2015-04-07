
// opencv_mfc.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Copencv_mfcApp:
// See opencv_mfc.cpp for the implementation of this class
//

class Copencv_mfcApp : public CWinApp
{
public:
	Copencv_mfcApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Copencv_mfcApp theApp;