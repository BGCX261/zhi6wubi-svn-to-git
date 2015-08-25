/*
* ============================================================================
*  Name     : CExampleFepControl from fepcontrol.h
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#ifndef FEPCONTROL_H
#define FEPCONTROL_H

#if !defined(__E32BASE_H__)
#include <E32BASE.H>
#endif

#if !defined(__W32STD_H__)
#include <W32STD.H>
#endif

#if !defined(__FRMTLAY_H__)
#include <FRMTLAY.H>
#endif

#if !defined(__COEMAIN_H__)
#include <COEMAIN.H>
#endif

#if !defined(__COECNTRL_H__)
#include <COECNTRL.H>
#endif

#if !defined(__FEPBASE_H__)
#include <FEPBASE.H>
#endif

#if !defined(__FEPITFR_H__)
#include <FEPITFR.H>
#endif

#if !defined(__EIKDIALG_H__)
#include <EIKDIALG.H>
#endif

#if !defined(__AKNLISTS_H__)
#include <AKNLISTS.H>
#endif

#if !defined(__EIKMOBS_H__)
#include <EIKMOBS.H>
#endif

#if !defined(__AKNEDSTSOBS_H__)
#include <AKNEDSTSOBS.H>
#endif

// Forward declarations
class CExampleFep;
class CAknEdwinState;
class CExampleFepMultiTapEngine;
class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class CFepIndicator;
class MAknEditingStateIndicator;

/**
 * Class: CExampleFepControl
 *
 * UI Control implementation of the FEP 
 */

class CExampleFepControl : public CCoeControl, 
//						   protected MFepInlineTextFormatRetriever, 
//						   MFepPointerEventHandlerDuringInlineEdit
						   public MFepInlineTextFormatRetriever, 
						   public MFepPointerEventHandlerDuringInlineEdit
{
	public: // Constructors and destructors
	
        /**
         * Two-phase constructor
		 *
		 * @param aFep handle to the actual fep class
		 *
         * @return initialized instance of the class		 
		 */	
		static CExampleFepControl* NewL( CExampleFep& aFep );

		/**
		 * Destructor
		 */		
		~CExampleFepControl();
		
	protected: // Constructors and destructors
	
		/**
		 * Constructor
		 *
		 * @param aFep handle to the actual fep class
		 */	
		CExampleFepControl( CExampleFep& aFep );

		/**
		 *  2nd phase construction
		 */
		void ConstructL();

	public: // from base classes
	
		//From CCoeControl
		TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

		// from MFepInlineTextFormatRetriever
		virtual void GetFormatOfFepInlineText( TCharFormat& aFormat, 
											   TInt& aNumberOfCharactersWithSameFormat, 
											   TInt aPositionOfCharacter) const;

		// from MFepPointerEventHandlerDuringInlineEdit
		virtual void HandlePointerEventInInlineTextL( TPointerEvent::TType aType, 
													  TUint aModifiers, 
													  TInt aPositionInInlineText);
        
	public:	// New methods
	
		/**
		 * Handles keypresses when the fep is in multitap mode
		 *
		 * @param aKeyEvent	key event details
		 * @param aType standard event type
		 *
		 * @return EKeyWasConsumed if key was consumed, other wise EKeyWasNotConsumed
		 */
		TKeyResponse OfferKeyEventInMultiTapModeL( const TKeyEvent& aKeyEvent, 
												   TEventCode aType);

		/**
		 * Handles keypresses when the fep is in numeric mode
		 *
		 * @param aKeyEvent	key event details
		 * @param aType standard event type
		 *
		 * @return EKeyWasConsumed if key was consumed, other wise EKeyWasNotConsumed
		 */
		TKeyResponse OfferKeyEventInNumericModeL( const TKeyEvent& aKeyEvent, 
												  TEventCode aType);

		/**
		 * Handles keypresses when the fep is in secret alpha mode
		 *
		 * @param aKeyEvent	key event details
		 * @param aType standard event type
		 *
		 * @return EKeyWasConsumed if key was consumed, other wise EKeyWasNotConsumed
		 */
		TKeyResponse OfferKeyEventInSecretAlphaModeL( const TKeyEvent& aKeyEvent, 
		            								  TEventCode aType);

		/**
		 * Handles the given keycode when the fep is in multitap mode
		 *
		 * @param aKeyECode	key code to be handled
		 */
		void HandleMultiTapModeKeyCodeL(TUint aKeyCode);

		/**
		 * Places one key event defined by aKeyCode onto the control
	 	 * stack to be handled as normal.
 		 *
		 * @param aKeyCode key event to be simulated 
		 */
		void SimulateKeyEventL(TUint aKeyCode);

		/**
		 * Handle change of focus -situations
		 */
		void HandleChangeInFocus();

		/**
		 * Handle change of focus -situations
		 */
		void HandleChangeInFocusL();
		
		/**
		 * Start a FEP inline editing transaction
		 *
		 * @param aFepAwareTextEditor text editor to be used in edit
		 * @param aInitialInlineText The inline text to insert into the text editor.
		 * @param aPositionOfInsertionPointInInlineText An insertion position within the inline text
		 * @param aCursorVisibility ETrue for visible text cursor, EFalse for invisible 
	     *        text cursor in the text editor.
		 */
		void StartInlineEditL( MCoeFepAwareTextEditor& aFepAwareTextEditor, 
							   const TDesC& aInitialInlineText, 
							   TInt aPositionOfInsertionPointInInlineText, 
							   TBool aCursorVisibility);
		
		/**
		 * Cancel the inline editing transaction 
		 *
		 * @param aFepAwareTextEditor text editor to be used in edit
		 */
		void CancelInlineEdit(MCoeFepAwareTextEditor& aFepAwareTextEditor);
		
		/**
		 * Update the inline text
		 *
		 * @param aNewInlineText Descriptor which holds the entire new inline text string
		 * @param aPositionOfInsertionPointInInlineText The position of the insertion 
		 *     	  point (i.e. the cursor) within the inline text string aNewInlineText. This 
	     *        is an offset from the start of the string
		 */
		void UpdateInlineEditL( const TDesC& aNewInlineText, 
							    TInt aPositionOfInsertionPointInInlineText);
		
		/**
		 * Commit the FEP inline editing transaction 
		 *
		 * @param aFepAwareTextEditor text editor to be used in edit
		 * @param aCursorVisibility   ETrue for visible text cursor, EFalse for invisible text cursor
		 */
		void CommitInlineEditL( MCoeFepAwareTextEditor& aFepAwareTextEditor, 
							    TBool aCursorVisibility);

		/**
		 * Clear the multitap engine buffer
		 */
		void ClearBuffer();

		/**
		 * Switch and set the input mode of the Avkon editor state
		 * 
		 * @param aInputMode the input mode to be set
		 */
		void SwitchInputModeL(TUint aInputMode);
		
		/**
		 * Get current Avkon editor state
		 *
		 * @return the current state
		 */
		CAknEdwinState* EditorState() const;

	private: // Data
	
		CExampleFep&					iFep;
		TCoeInputCapabilities			iInputCapabilities;
		TUint							iInputMode;
		TUint							iPreviousMultiTapKeyCode;
		TInt							iInsideInlineEditingTransaction; // Flag for editor inline editing 

		CExampleFepMultiTapEngine*		iMultiTapEngine;
		TCursorSelection				iUncommittedText;

		CFepIndicator*					iIndicator;
	
		TInt							iResId;	// For containing the T9 resource ID
		
		MAknEditingStateIndicator*		iPreviousIndicator;
	 };

#endif

// End of file
