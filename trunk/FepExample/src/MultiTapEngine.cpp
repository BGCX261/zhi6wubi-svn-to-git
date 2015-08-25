/*
* ============================================================================
*  Name     : CExampleMultiTapEngine from multitapengine.cpp
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#include "multitapengine.h"
#include "multitaptimer.h"

const TInt KMaxNumOfKeys = 10;
const TInt KMultiTapTimeout = 1000000; // 1.0s

struct TKeymap
    {
    char*   iKeyString;
    TInt    iSize;
    };

// keys available for multitapping
const struct TKeymap KKeymap[KMaxNumOfKeys] = {
    { " 0",     2 },
    { "1+#.",   4 },
    { "abc2",   4 },
    { "def3",   4 },
    { "ghi4",   4 },
    { "jkl5",   4 },
    { "mno6",   4 },
    { "pqrs7",  5 },
    { "tuv8",   4 },
    { "wxyz9",  5 }
    };

//////////////////////////////////////////////////////////////////////
//
// Class CExampleFepMultiTapEngine
//
//////////////////////////////////////////////////////////////////////
CExampleFepMultiTapEngine* CExampleFepMultiTapEngine::NewL(CExampleFepControl& aControl)
    {
    CExampleFepMultiTapEngine* self = new(ELeave)CExampleFepMultiTapEngine(aControl);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();    // self
    return self;
    }

CExampleFepMultiTapEngine::CExampleFepMultiTapEngine(CExampleFepControl& aControl)
    : iFepControl(aControl),
    iBuffer(KNullDesC),
    iKeyPos(0),
    iPreviousMultiTapKeyCode(EKeyNull)
    {
    }

void CExampleFepMultiTapEngine::ConstructL()
    {
    TCallBack timerTimeout(TimerTimeout, this);
    iMultiTapTimer = CExampleFepMultiTapTimer::NewL(timerTimeout, KMultiTapTimeout);
    }

CExampleFepMultiTapEngine::~CExampleFepMultiTapEngine()
    {
    if(iMultiTapTimer)
        delete iMultiTapTimer;
    }

TInt CExampleFepMultiTapEngine::TimerTimeout(TAny* aPtr)
    {
    return REINTERPRET_CAST(CExampleFepMultiTapEngine*, aPtr)->DoTimerTimeout();
    }

TInt CExampleFepMultiTapEngine::DoTimerTimeout()
    {
    iMultiTapTimer->DoCancel();
    iPreviousMultiTapKeyCode = EKeyNull;
    return ETrue;
    }

TPtrC CExampleFepMultiTapEngine::AppendCharacter(TUint aKeyCode)
    {
    TInt offset = aKeyCode - '0';

    if (iMultiTapTimer->IsActive() && aKeyCode == iPreviousMultiTapKeyCode)
        {
        // Delete the previous letter in iBuffer
        DeleteCharacter();

        iKeyPos++;
        if ( iKeyPos >= KKeymap[offset].iSize )
            iKeyPos = 0;
        }
    else
        iKeyPos = 0;

    char ch = KKeymap[offset].iKeyString[iKeyPos];
    TBuf<1> buffer = KNullDesC();

    buffer.Append(ch);
    iBuffer += buffer;

    iPreviousMultiTapKeyCode = aKeyCode;

    // Start the multitap timer
    iMultiTapTimer->IssueRequest();

    return iBuffer.Ptr();
    }

TPtrC CExampleFepMultiTapEngine::DeleteCharacter(void)
    {
    TInt len = iBuffer.Length();
    iBuffer = iBuffer.Left (len - 1);
    return iBuffer.Ptr();
    }

void CExampleFepMultiTapEngine::ClearBuffer(void)
    {
    iBuffer.SetLength(0);
    }

TPtrC CExampleFepMultiTapEngine::Buffer(void)
    {
    return iBuffer.Ptr();
    }

TBool CExampleFepMultiTapEngine::IsActive()
    {
    return iMultiTapTimer->IsActive();
    }

void CExampleFepMultiTapEngine::Cancel()
    {
    iMultiTapTimer->Cancel();
    }

// end of file
