
// learningMFC2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// ClearningMFC2App:
// See learningMFC2.cpp for the implementation of this class
//

class ClearningMFC2App : public CWinApp
{
public:
	ClearningMFC2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern ClearningMFC2App theApp;