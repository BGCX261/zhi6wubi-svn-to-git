/*
* ============================================================================
*  Name     : CExampleFep from fepexample.cpp
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#include <eikappui.h>
#include <eikenv.h>

#include <FEPBASE.H>
#include <w32std.h> 
#include <bautils.h>
#include <frmtlay.h>

#include <aknedsts.h> 
#include "fepexample.h"
#include "fepcontrol.h"


#ifndef __SERIES60_3X__ // see fepexampleplugin.cpp for Series60 3.x

/**
 * Main Fep construction - defined in COEFEPU.DEF
 */
EXPORT_C CCoeFep* NewFepL( CCoeEnv& aConeEnvironment, 
						   const TDesC& /*aFullFileNameOfDll*/, 
						   const CCoeFepParameters& aFepParameters )
    {
	CExampleFep* const fep = new(ELeave) CExampleFep(aConeEnvironment);
    CleanupStack::PushL(fep);
    fep->ConstructL(aFepParameters);
    CleanupStack::Pop(); // fep

    return fep;
    }

/**
 * Export defined in COEFEPU.DEF - unused
 */

EXPORT_C void SynchronouslyExecuteSettingsDialogL( CCoeEnv& /*aConeEnvironment*/, 
												   const TDesC& /*aFullFileNameOfDll*/ )
    {
	}

/**
 * Reserved exports defined in COEFEPU.DEF - unused
 */
EXPORT_C void Reserved_1(){}
EXPORT_C void Reserved_2(){}
EXPORT_C void Reserved_3(){}
EXPORT_C void Reserved_4(){}
EXPORT_C void Reserved_5(){}
EXPORT_C void Reserved_6(){}
EXPORT_C void Reserved_7(){}
EXPORT_C void Reserved_8(){}

GLDEF_C TInt E32Dll(TDllReason)
	{
    return KErrNone;
    }

#endif


/////////////////////////////////////////////////////////////////////////////////
//
//Class CExampleFep
//
/////////////////////////////////////////////////////////////////////////////////

CExampleFep::CExampleFep(CCoeEnv& aConeEnvironment)
	:CCoeFep(aConeEnvironment)
	{	
	}

void CExampleFep::ConstructL(const CCoeFepParameters& aFepParameters)
	{
	BaseConstructL(aFepParameters);
	iFepControl = CExampleFepControl::NewL(*this);
	}

CExampleFep::~CExampleFep()
    {
    if( iFepControl )
    	{
    	delete iFepControl;
    	}
    }


TInt CExampleFep::NumberOfAttributes() const 
	{
	return 0;
	}

TUid CExampleFep::AttributeAtIndex(TInt /*aIndex*/) const 
	{
	return KNullUid;
	}

void CExampleFep::WriteAttributeDataToStreamL(TUid /*aAttributeUid*/, RWriteStream& /*aStream*/) const 
	{
	}

void CExampleFep::ReadAttributeDataFromStreamL(TUid /*aAttributeUid*/, RReadStream& /*aStream*/) 
	{
	}

void CExampleFep::OfferKeyEventL(TEventResponse& /*aEventResponse*/,const TKeyEvent& /*aKeyEvent*/, TEventCode /*aEventCode*/)
	{
	}

void CExampleFep::OfferPointerEventL(TEventResponse& /*aEventResponse*/,const TPointerEvent& /*aPointerEvent*/, const CCoeControl* /*aWindowOwningControl*/)
	{
	}

void CExampleFep::OfferPointerBufferReadyEventL(TEventResponse& /*aEventResponse*/, const CCoeControl* /*aWindowOwningControl*/)//wbase
	{
	}

void CExampleFep::HandleChangeInFocus()
    {
	if( iFepControl )
		{
		iFepControl->HandleChangeInFocus();
		}
	}

void CExampleFep::HandleDestructionOfFocusedItem()
	{
	}

void CExampleFep::HandleGainingForeground()
    {
    }

void CExampleFep::HandleLosingForeground()
    {
    }

void CExampleFep::CancelTransaction()
	{
	}

void CExampleFep::IsOnHasChangedState()
	{
	}

// end of file
