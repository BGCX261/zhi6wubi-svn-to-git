/*
* ============================================================================
*  Name     : CExampleMultiTapTimer from multitaptimer.h
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#ifndef FEPMULTITAPTIMER_H
#define FEPMULTITAPTIMER_H


// INCLUDES
#include <w32std.h>

/**
 * Class: CExampleFepMultiTapTimer
 *
 * Active object timer for MultiTap Engine
 */
class CExampleFepMultiTapTimer : public CTimer
{
	public:     // Constructors and destructors
		
        /**
         * Two-phase constructor
		 *
		 * @param aCallback callback object
		 * @param aDelay	timer timeout
		 *
         * @return initialized instance of the class		 
		 */
		static CExampleFepMultiTapTimer* NewL(TCallBack aCallback, TInt aDelay);
		
		/**
		 * Destructor
		 */
		~CExampleFepMultiTapTimer();
		
	protected:  // Constructors and destructors		
	
		/**
		 * Constructor
		 *
		 * @param aCallback callback object
		 * @param aDelay	timer timeout
		 */
		CExampleFepMultiTapTimer(TCallBack aCallback, TInt aDelay);

		/**
		 *  2nd phase construction
		 */
		void ConstructL();

	public: 
	
		/**
		 * Issue a request to an asynchronous service provider.
		 */
		void IssueRequest(); 
		
		/**
		 * From CActive, Implements cancellation of an outstanding request
		 */
		void DoCancel();
		
		/**
		 * From CActive, Handles an active object's request completion event
		 */
		void RunL();

	private:
		TCallBack	iCallback;
		TInt		iDelay;
};

#endif //FEPMULTITAPTIMER_H

// end of file
