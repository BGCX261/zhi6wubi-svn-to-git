/*
* ============================================================================
*  Name     : CFepIndicator from fepindicator.cpp
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#include <eikenv.h>         //CEikEnv
#include <eikspane.h>       //CEikStatusPane
#include <avkon.hrh>
#include <aknnavi.h>        //CAknNavigationControlContainer
#include <aknnavide.h>      //CAknNavigationDecorator
#include <aknindicatorcontainer.h>  //CAknIndicatorContainer
#include <aknutils.h>
#include <aknenv.h>

#include "FepIndicator.h"

_LIT(KNaviPaneTextAbc, "abc");
_LIT(KNaviPaneText123, "123");

/**
 *
 */ 
CFepIndicator* CFepIndicator::NewL()
    {
    CFepIndicator* self = new(ELeave)CFepIndicator();
    return self;
    }


/**
 *
 */
CFepIndicator::CFepIndicator()
    :iPreviousState(EStateNone), 
	iEikEnv(*CEikonEnv::Static())
    {
    }
    
/**
 *
 */
CFepIndicator::~CFepIndicator()
    {
    RemoveContainer();
    }

void CFepIndicator::SetState(TAknEditingState aState)
    {
    CAknNavigationControlContainer* naviPane = 0;

    TRAPD(err, naviPane = NaviPaneL());

    // If the navi pane has been changed, clean up and start again.
   if (iNaviPane != naviPane)
        {
        RemoveContainer();
        iNaviPane = naviPane;
        iNaviPaneChanged = ETrue;
        }
    
    if ((iPreviousState == aState) && !iNaviPaneChanged )
        {
        // The required state already exists and navi pane has not been changed 
        // by launching embedded application. Leave the contents alone.
        return;
        }
        
    if (aState == EStateNone) 
		{
        if ( iNaviDecorator && naviPane )
            {
            naviPane->Pop(iNaviDecorator);
            }
        iPreviousState = aState;
        iNaviPaneChanged = EFalse;
        return;
        }
   
     if ( err == KErrNone )
        {
        iNaviPaneChanged = EFalse;
        TRAP(err,AddContainerL(naviPane));

		// Workaround solution to keep SMS editor from crashing on some platforms
		CAknEnv::Static()->SwapEditingStateIndicator(NULL);    
		
		if (aState == EMultitapLower)
			{
			if (iNaviDecorator)
				{
				delete iNaviDecorator;
				iNaviDecorator = NULL;
				}
		
			TRAPD( ignore, iNaviDecorator = 
			               iNaviPane->CreateMessageLabelL( KNaviPaneTextAbc ));
		
	        // Push the state to the navi-pane
		   	if (naviPane)
				{
				TRAPD(ignore, naviPane->PushL(*iNaviDecorator));
				} 
            }          		
		else if (aState == ENumeric)
			{
			if (iNaviDecorator)
				{
				delete iNaviDecorator;
				iNaviDecorator = NULL;
				}
		
			TRAPD( ignore, iNaviDecorator = 
						   iNaviPane->CreateMessageLabelL( KNaviPaneText123 ));
		
        	// Push the state to the navi-pane
			if (naviPane)
				{
				TRAPD(ignore, naviPane->PushL(*iNaviDecorator));
				}      
			}
        }
    iPreviousState = aState;    
    }


CAknIndicatorContainer* CFepIndicator::IndicatorContainer()
    {
    CAknNavigationControlContainer* naviPane = 0;
    TRAPD(err, naviPane = NaviPaneL());

    // If the navi pane have changed, clean up and start again
    if ( naviPane != iNaviPane )
        {
        RemoveContainer();
        iNaviPane = naviPane;
        iNaviPaneChanged = ETrue;
        }
    if ( !iIndicatorContainer )
        {
        TRAP(err, AddContainerL(naviPane));        
        }
    return iIndicatorContainer;
    }


/**
 *  Create a new indicator container and push it to the navi-pane
 */
void CFepIndicator::AddContainerL(CAknNavigationControlContainer* aNaviPane)
    {
    // Create a new indicator container and push it to the navi-pane
    if (!iIndicatorContainer && aNaviPane)
        {
        iNaviDecorator = aNaviPane->CreateEditorIndicatorContainerL();
        iIndicatorContainer = STATIC_CAST( CAknIndicatorContainer*, 
        								   iNaviDecorator->DecoratedControl());
        }
    }

/**
 * Pop the indicator container from the navi-pane
 */
void CFepIndicator::RemoveContainer()
    {
    // Pop the indicator container from the navi-pane
    if (iIndicatorContainer)
        {
        delete iNaviDecorator;
        iNaviDecorator = NULL;
        iIndicatorContainer = NULL;
        }
    }

void CFepIndicator::SetIndicator(TInt aIndicator, TInt aMode, TBool aDrawNow)
    {
    iIndicatorContainer->SetIndicatorState(TUid::Uid(aIndicator), aMode, aDrawNow);
    }

/**
 *  get a handle to the Navi Pane
 */
CAknNavigationControlContainer* CFepIndicator::NaviPaneL()
    {
    CEikStatusPane *sp = iEikEnv.AppUiFactory()->StatusPane();
    User::LeaveIfNull(sp);
    
    // Fetch pointer to the default navi pane control
    return (CAknNavigationControlContainer *)sp->ControlL(TUid::Uid(EEikStatusPaneUidNavi));
    }

// End of file
