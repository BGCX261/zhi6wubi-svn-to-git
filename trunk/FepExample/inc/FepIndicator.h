/*
* ============================================================================
*  Name     : CFepIndicator from fepindicator.h
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#ifndef FEPINDICATOR_H
#define FEPINDICATOR_H

#include <e32base.h>
#include <AknEditStateIndicator.h>

class CAknNavigationDecorator;
class CAknNavigationControlContainer;
class CEikonEnv;
class CAknIndicatorContainer;

/**
 * Class: CFepIndicator
 *
 * Class for updating the UI status pane indicator
 */
class CFepIndicator : public CBase, public MAknEditingStateIndicator
    {
   	public: // Constructors and destructors
	
        /**
         * Two-phase constructor
		 *
         * @return initialized instance of the class		 
		 */
		static CFepIndicator* NewL();

		/**
		 * Destructor
		 */		
		~CFepIndicator();
		
	protected: // Constructors and destructors
			
		/**
		 * Constructor
		 */	
		CFepIndicator();

	public: // from MAknEditingStateIndicator
	
		virtual void SetState(TAknEditingState aState); 
		virtual CAknIndicatorContainer* IndicatorContainer();

	private: // new methods
	
		/**
		 * Create a new indicator container and push it to the navipane
		 *
		 * @param aNaviPane navipane to be used
		 */	
		void AddContainerL(CAknNavigationControlContainer* aNaviPane);

		/**
		 * Pop the indicator container from the navipane
		 */	
		void RemoveContainer();

		/**
		 * Set the indicator state to given mode
		 *
		 * @param aIndicator indicator to be set
		 * @param aMode mode to which the indicator is to be set
		 * @param aDrawNow whether to draw immediately after update
		 */	
		void SetIndicator(TInt aIndicator, TInt aMode, TBool aDrawNow = ETrue);
		
		/**
		 * Get the navipane used
		 *
		 * @return pointer to the default navipane
		 */
		CAknNavigationControlContainer* NaviPaneL();

	private: // Data
	
		CAknIndicatorContainer*     iIndicatorContainer;
		CAknNavigationDecorator*    iNaviDecorator;
		TAknEditingState  			iPreviousState;
		CEikonEnv&					iEikEnv;
		CAknNavigationControlContainer* iNaviPane;
		TBool						iNaviPaneChanged;
    };

#endif // FEPINDICATOR_H

// End of file
