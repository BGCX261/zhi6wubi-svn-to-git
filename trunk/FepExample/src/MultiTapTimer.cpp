/*
* ============================================================================
*  Name     : CExampleMultiTapTimer from multitaptimer.cpp
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#include "multitaptimer.h"

//////////////////////////////////////////////////////////////////////
//
// Class CExampleFepMultiTapTimer
//
//////////////////////////////////////////////////////////////////////
CExampleFepMultiTapTimer* CExampleFepMultiTapTimer::NewL(TCallBack aCallback, TInt aDelay)
	{
	CExampleFepMultiTapTimer* self = new(ELeave)CExampleFepMultiTapTimer(aCallback, aDelay);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();	// self
	return self;
	}

CExampleFepMultiTapTimer::CExampleFepMultiTapTimer(TCallBack aCallback, TInt aDelay)
	:CTimer(EPriorityStandard), iCallback(aCallback), iDelay(aDelay)
	{
	}

void CExampleFepMultiTapTimer::ConstructL()
	{
	CTimer::ConstructL();
	CActiveScheduler::Add(this);
	}

void CExampleFepMultiTapTimer::IssueRequest()
	{
	if (IsActive())
		{
		Cancel();
		}
	CTimer::After(iDelay);
	}


void CExampleFepMultiTapTimer::RunL()
	{
	iCallback.CallBack();
	}

CExampleFepMultiTapTimer::~CExampleFepMultiTapTimer()
	{
	Cancel();
	}

void CExampleFepMultiTapTimer::DoCancel()
	{
	CTimer::DoCancel();
	}


// end of file
