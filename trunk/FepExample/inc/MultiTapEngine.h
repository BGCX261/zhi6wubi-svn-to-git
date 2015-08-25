/*
* ============================================================================
*  Name     : CExampleMultiTapEngine from multitapengine.h
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#ifndef FEPMULTITAPENGINE_H
#define FEPMULTITAPENGINE_H

// INCLUDES
#include <e32base.h>
#include <e32std.h>

// Forward declarations
class CExampleFepMultiTapTimer;
class CExampleFepControl;

/**
 * Class: CExampleFepMultiTapEngine
 *
 * An example implementation of an alternative multitap
 * key handling engine.
 */
class CExampleFepMultiTapEngine : public CBase
{
	public:     // Constructors and destructors
	
        /**
         * Two-phase constructor
		 *
		 * @param aControl UI control owning this engine
		 *
         * @return initialized instance of the class		 
		 */
		static CExampleFepMultiTapEngine* NewL (CExampleFepControl& aControl);
		
		/**
		 * Destructor
		 */		
		~CExampleFepMultiTapEngine();

	protected:     // Constructors and destructors
	
		/**
		 * Constructor
		 *
		 * @param aControl UI control owning this engine
		 */	
		CExampleFepMultiTapEngine(CExampleFepControl& aControl);

		/**
		 *  2nd phase construction
		 */
		void ConstructL();

	public: // New methods
	
        /**
         * Append a character to buffer
		 *
		 * @param aKeyCode character to be added to buffer
		 *
         * @return buffer after the operation
		 */
		TPtrC AppendCharacter(TUint aKeyCode);

        /**
         * Delete the last character from buffer
		 *
         * @return buffer after the operation
		 */
		TPtrC DeleteCharacter();

        /**
         * Clear the buffer
		 */
		void ClearBuffer();

        /**
         * Get the buffer
         *
         * @return current buffer
		 */
		TPtrC Buffer();

        /**
         * Check whether multitap timer is active
		 *
         * @return ETrue if multitap timer is active, otherwise EFalse
		 */
		TBool IsActive();

        /**
         * Cancel multitap timer
		 */
		void Cancel();
	
	private: // New methods
	
        /**
         * Callback method for timer
		 *
		 * @param aPtr Pointer to this object
		 *
         * @return TCallback return value
		 */
		static TInt TimerTimeout(TAny* aPtr);

        /**
         * Callback target method, manually timeouts timer 
		 *
         * @return TCallback return value
		 */
		TInt DoTimerTimeout();

	private: // Data
	
		CExampleFepControl&			iFepControl;	// not owned
		TBuf<128>					iBuffer;
		TInt						iKeyPos;
		TUint						iPreviousMultiTapKeyCode;
		CExampleFepMultiTapTimer*	iMultiTapTimer;
};

#endif // FEPMULTITAPENGINE_H

// end of file
