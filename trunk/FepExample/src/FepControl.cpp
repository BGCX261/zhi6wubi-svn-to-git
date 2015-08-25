/*
* ============================================================================
*  Name     : CExampleFepControl from fepcontrol.cpp
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#include <eikappui.h>
#include <eikenv.h>         //CEikEnv
#include <bautils.h>    // for BaflUtils
#include <aknedsts.h> // for CAknEdwinState
#include <aknenv.h>                 //CAknEnv
#include <aknindicatorcontainer.h>  //CAknIndicatorContainer
#include <coeutils.h>               // for ConeUtils::FileExists

#include "fepexample.h"
#include "fepcontrol.h"
#include "multitapengine.h"
#include "fepindicator.h"

#ifdef __SERIES60_3X__
_LIT( KAknFepResourceFileName, "z:\\resource\\fep\\aknfep.rsc" );
#else
_LIT( KT9FepResourceFileName, "z:\\system\\fep\\t9fep.rsc" );
_LIT( KAknFepResourceFileName, "z:\\system\\fep\\aknfep.rsc" );
#endif
/////////////////////////////////////////////////////////////////////////////////
//
//Class CExampleFepControl
//
/////////////////////////////////////////////////////////////////////////////////
/**
 * Two phase construction
 */
CExampleFepControl* CExampleFepControl::NewL(CExampleFep& aFep)
    {
    CExampleFepControl* self=new(ELeave) CExampleFepControl(aFep);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); //self
    return self;
    }

CExampleFepControl::CExampleFepControl(CExampleFep& aFep)
    :iFep(aFep),
    iInputCapabilities(TCoeInputCapabilities::ENone),
    iInputMode(EAknEditorNullInputMode),
    iPreviousMultiTapKeyCode(EKeyNull),
    iInsideInlineEditingTransaction(EFalse)
    {
    }

void CExampleFepControl::ConstructL()
    {
    // Set up fep key catching control - front window, null size, non-focusing
    CreateWindowL();
    SetNonFocusing();

    RWindow& window = Window();
    window.SetOrdinalPosition(0, ECoeWinPriorityFep);
    TPoint fepControlPos(0, 0);

    SetExtent(fepControlPos, TSize(0,0));
    window.SetExtent(fepControlPos, TSize(0,0));
    window.SetNonFading(ETrue);

    // Create multi-tap input engine
    iMultiTapEngine = CExampleFepMultiTapEngine::NewL(*this);

    // Create status pane indicator
    iIndicator = CFepIndicator::NewL();

    // Needed by UI library
    iPreviousIndicator = CAknEnv::Static()->SwapEditingStateIndicator(iIndicator);

    // The reason why we need to set up the T9/aknfep resource is that, Series 60 platform integrates the
    // T9/aknfep engine into the system, and some on-board applications expect this resource to be
    // present, if not, those applications will not work. The T9/aknfep resource is loaded when
    // the T9/aknfep FEP start up.
    //
    // As a workaround solution, we load the T9/aknfep resource in our own FEP.
#ifdef __SERIES60_3X__
        TFileName resourceName( KAknFepResourceFileName );
        BaflUtils::NearestLanguageFile( iEikonEnv->FsSession(), resourceName );
        iResId = iEikonEnv->AddResourceFileL( resourceName );
#else
    TFileName resourceName( KAknFepResourceFileName );
    BaflUtils::NearestLanguageFile( iEikonEnv->FsSession(), resourceName );
    if( ConeUtils::FileExists( resourceName )) // 2ndfp2 platform and newer use aknfep
        {
        iResId = iEikonEnv->AddResourceFileL( resourceName );
        }
    else
        {
        TFileName T9resourceName( KT9FepResourceFileName );
        BaflUtils::NearestLanguageFile( iEikonEnv->FsSession(), T9resourceName );
        iResId = iEikonEnv->AddResourceFileL( T9resourceName );
        }
#endif
    ((CCoeAppUi*)iEikonEnv->AppUi())->AddToStackL(this,
        ECoeStackPriorityFep, ECoeStackFlagSharable|ECoeStackFlagRefusesFocus);
    }

CExampleFepControl::~CExampleFepControl()
    {
    // Needed by UI library
    CAknEnv::Static()->SwapEditingStateIndicator(iPreviousIndicator);

    if (iMultiTapEngine)
        {
        delete iMultiTapEngine;
        iMultiTapEngine = NULL;
        }

    if (iIndicator)
        {
        delete iIndicator;
        iIndicator = NULL;
        }

    iEikonEnv->DeleteResourceFile(iResId);

    ((CCoeAppUi*)iEikonEnv->AppUi())->RemoveFromStack(this);
    }

// Please consult SDK for more information on Inline Editing transaction
void CExampleFepControl::StartInlineEditL( MCoeFepAwareTextEditor& aFepAwareTextEditor,
                                           const TDesC& aInitialInlineText,
                                           TInt aPositionOfInsertionPointInInlineText,
                                           TBool aCursorVisibility)
    {
    aFepAwareTextEditor.StartFepInlineEditL( aInitialInlineText,
                                             aPositionOfInsertionPointInInlineText,
                                             aCursorVisibility,
                                             NULL,
                                             *this,
                                             *this );
    iInsideInlineEditingTransaction = ETrue;
    }

// Please consult SDK for more information on Inline Editing transaction
void CExampleFepControl::UpdateInlineEditL( const TDesC& aNewInlineText,
                                            TInt aPositionOfInsertionPointInInlineText )
    {
    iInputCapabilities.FepAwareTextEditor()->UpdateFepInlineTextL( aNewInlineText,
                                                                   aPositionOfInsertionPointInInlineText );
    }

// Please consult SDK for more information on Inline Editing transaction
void CExampleFepControl::CancelInlineEdit(MCoeFepAwareTextEditor& aFepAwareTextEditor)
    {
    aFepAwareTextEditor.CancelFepInlineEdit();
    iInsideInlineEditingTransaction = EFalse;

    ClearBuffer();
    }

// Please consult SDK for more information on Inline Editing transaction
void CExampleFepControl::CommitInlineEditL( MCoeFepAwareTextEditor& aFepAwareTextEditor,
                                            TBool aCursorVisibility )
    {
    aFepAwareTextEditor.SetInlineEditingCursorVisibilityL(aCursorVisibility);
    iInsideInlineEditingTransaction = EFalse;
    aFepAwareTextEditor.CommitFepInlineEditL(*iCoeEnv);
    aFepAwareTextEditor.GetCursorSelectionForFep(iUncommittedText);

    ClearBuffer();
    }


void CExampleFepControl::GetFormatOfFepInlineText( TCharFormat& /*aFormat*/,
                                                   TInt& /*aNumberOfCharactersWithSameFormat*/,
                                                   TInt /*aPositionOfCharacter*/ ) const
    {
    // No implementation
    }


void CExampleFepControl::HandlePointerEventInInlineTextL( TPointerEvent::TType /*aType*/,
                                                          TUint /*aModifiers*/,
                                                          TInt /*aPositionInInlineText*/ )
    {
    // No implementation
    }

TKeyResponse CExampleFepControl::OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                                 TEventCode aEventCode )
    {
    TInt keyCode = aKeyEvent.iCode;
    if (aEventCode != EEventKey)
        {
        return EKeyWasNotConsumed;
        }

    if (((keyCode == EKeyCBA1) || (keyCode == EKeyCBA2)) || (keyCode == EKeyMenu))
        {
        if (iInsideInlineEditingTransaction)
            {
            // If we're in inline editing transaction, just commit it and return
            CommitInlineEditL(*(iInputCapabilities.FepAwareTextEditor()), ETrue);
            }
        return EKeyWasNotConsumed;
        }

    if (iFep.IsTurnedOnByL(aKeyEvent) || iFep.IsTurnedOffByL(aKeyEvent))
        {
        return EKeyWasConsumed;
        }

    if (!iFep.IsOn())
        return EKeyWasNotConsumed;

    TKeyResponse response = EKeyWasNotConsumed;
    switch (iInputMode)
        {
        case EAknEditorTextInputMode:
            response = OfferKeyEventInMultiTapModeL(aKeyEvent, aEventCode);
            break;

        case EAknEditorNumericInputMode:
            response = OfferKeyEventInNumericModeL(aKeyEvent, aEventCode);
            break;

        case EAknEditorSecretAlphaInputMode:
            response = OfferKeyEventInSecretAlphaModeL(aKeyEvent, aEventCode);
            break;

        default:
            break;
        }
    return response;
    }

/**
 * Handles keypresses when the fep is in numeric mode
 */
TKeyResponse CExampleFepControl::OfferKeyEventInNumericModeL( const TKeyEvent& aKeyEvent,
                                                              TEventCode /*aEventCode*/ )
    {
    TKeyResponse response = EKeyWasNotConsumed;

    if (aKeyEvent.iCode == '*')
        {
        // Just place a key event ('+') to the application underneath the FEP
        SimulateKeyEventL('+');
        response = EKeyWasConsumed;
        }
    return response;
    }

/**
 * Handles keypresses when the fep is in multitap mode
 */
TKeyResponse CExampleFepControl::OfferKeyEventInMultiTapModeL( const TKeyEvent& aKeyEvent,
                                                               TEventCode aEventCode )
    {
    TKeyResponse response = EKeyWasNotConsumed;
    TUint keyCode = aKeyEvent.iCode;

    TBool shortKeyPress=(aEventCode==EEventKey && aKeyEvent.iRepeats==0);
    TBool longKeyPress=(aEventCode==EEventKey && aKeyEvent.iRepeats==1 );

    if (iPreviousMultiTapKeyCode != keyCode)
        {
        // New key press, cancel multi-tap timer
        iMultiTapEngine->Cancel();
        }

    switch (keyCode)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            {
            if (shortKeyPress)
                {
                // insert a letter
                HandleMultiTapModeKeyCodeL(keyCode);
                response=EKeyWasConsumed;
                }
            else if (longKeyPress)
                {
                if (iInsideInlineEditingTransaction)
                    {// insert a digit

                    // Set the new cursor position
                    TInt newCursorPos = 0;
                    TCursorSelection currentEditorSelection;

                    // Gets the range of characters in the text editor which are selected
                    iInputCapabilities.FepAwareTextEditor()->GetCursorSelectionForFep(currentEditorSelection);

                    // If the number of characters in the current editor is greater than, move the cursor
                    // position of the uncommitted text to the end.
                    if (currentEditorSelection.Length())
                        {
                        // Gets the greater of the cursor and anchor positions
                        newCursorPos = currentEditorSelection.HigherPos();

                        // Sets the cursor and anchor positions for the uncommitted text
                        iUncommittedText.SetSelection(newCursorPos, newCursorPos);

                        // Sets the range of characters in the text editor which should be selected
                        iInputCapabilities.FepAwareTextEditor()->SetCursorSelectionForFepL(iUncommittedText);
                        }

                    // Our implementation:
                    // Treat all the long key press key as digit character. Therefore,
                    // we delete the previous character and replace it with a "keyCode"
                    iMultiTapEngine->DeleteCharacter();
                    TBuf<1> buffer = KNullDesC();
                    buffer.Append(keyCode);
                    UpdateInlineEditL(buffer, 1);
                    CommitInlineEditL(*(iInputCapabilities.FepAwareTextEditor()), ETrue);
                    response = EKeyWasConsumed;
                    }
                else // have received long keyprss without initial short keypress so just consume
                    response = EKeyWasConsumed;
                }
            else
                response = EKeyWasConsumed;
            }
            break;

        case EKeyBackspace:
            response = EKeyWasNotConsumed;
            if (iInsideInlineEditingTransaction)
                {
                // If we're in inline editing transaction, just commit it and return
                CommitInlineEditL(*(iInputCapabilities.FepAwareTextEditor()), ETrue);
                }

            break;

        case EKeyLeftArrow:
        case EKeyRightArrow:
        case EKeyUpArrow:
        case EKeyDownArrow:
            if (iInsideInlineEditingTransaction)
                {
                // If we're in inline editing transaction, just commit it and return
                CommitInlineEditL(*(iInputCapabilities.FepAwareTextEditor()), ETrue);
                response = EKeyWasConsumed;
                }
            else
                response = EKeyWasNotConsumed;
            break;

        default:

            if (iInsideInlineEditingTransaction)
                {
                // If we're in inline editing transaction, just commit it and return
                CommitInlineEditL(*(iInputCapabilities.FepAwareTextEditor()), ETrue);
                //response = EKeyWasConsumed;

                response = EKeyWasNotConsumed;
                }

            break;
        }

    iPreviousMultiTapKeyCode = keyCode;
    return response;
    }

/**
 * Handles keypresses when the fep is in secret alpha mode
 */
TKeyResponse CExampleFepControl::OfferKeyEventInSecretAlphaModeL( const TKeyEvent& /*aKeyEvent*/,
                                                                  TEventCode /*aEventCode*/ )
    {
    // No implementation yet, so just return key not consumed
    return EKeyWasNotConsumed;
    }

/**
 *
 */
void CExampleFepControl::HandleMultiTapModeKeyCodeL(TUint aKeyCode)
    {
    if (!iMultiTapEngine->IsActive())
        {
        // timer timeout, treats this as new key press
        iPreviousMultiTapKeyCode = EKeyNull;
        }

    if ((aKeyCode != iPreviousMultiTapKeyCode) && iInsideInlineEditingTransaction)
        {
        // new key press
        CommitInlineEditL(*(iInputCapabilities.FepAwareTextEditor()), EFalse);
        }

    if (!iInsideInlineEditingTransaction)
        {
        // Previous transaction is not inline editor editing, so start it.
        if (iMultiTapEngine->IsActive())
            StartInlineEditL(*(iInputCapabilities.FepAwareTextEditor()), KNullDesC, 0, EFalse); // Don't show cursor
        else
            StartInlineEditL(*(iInputCapabilities.FepAwareTextEditor()), KNullDesC, 0, ETrue); // Show cursor
        }

    if (iInsideInlineEditingTransaction)
        {
        // Update a new character and get a pointer to the engine buffer
        TPtrC ptr = iMultiTapEngine->AppendCharacter(aKeyCode);
        UpdateInlineEditL(ptr, 1); // Single character
        }
    }

/**
 * This method will place one key event defined by aKeyCode onto the control
 * stack to be handled as normal.
 */
void CExampleFepControl::SimulateKeyEventL(TUint aKeyCode)
    {
    CArrayFix<TUint>* simCharArray=new(ELeave) CArrayFixFlat<TUint>(1);
    CleanupStack::PushL(simCharArray);
    simCharArray->AppendL(aKeyCode);
    iFep.SimulateKeyEventsL(simCharArray->Array());
    CleanupStack::PopAndDestroy(); // simCharArray
    }


void CExampleFepControl::HandleChangeInFocus()
    {
    TRAPD(err, HandleChangeInFocusL());
    if (err != KErrNone)
        {
        ClearBuffer();
        iMultiTapEngine->Cancel();
        }
    }

void CExampleFepControl::HandleChangeInFocusL()
    {
    // Commit the uncommitted inline editing, if any
    if ((iInputMode == EAknEditorTextInputMode || iInputMode == EAknEditorNumericInputMode ||
        iInputMode == EAknEditorSecretAlphaInputMode) && iInsideInlineEditingTransaction)
        {
        CommitInlineEditL(*(iInputCapabilities.FepAwareTextEditor()), EFalse);
        // Next key is a new key press
        iPreviousMultiTapKeyCode = EKeyNull;
        }

    // Get the newly focused control capability
    iInputCapabilities = STATIC_CAST(const CCoeAppUi*, iCoeEnv->AppUi())->InputCapabilities();

    // check & process the current capability underneath
    if (iInputCapabilities.FepAwareTextEditor())
        {
        // Not all text editors are "fep aware". Fep somehow needs help from the editor window
        // to determine the current editor capabilities.
        CAknEdwinState* editorState = EditorState();
        TUint editorMode = editorState->CurrentInputMode();
        if (editorMode == EAknEditorNullInputMode)
            editorMode = editorState->DefaultInputMode();

        SwitchInputModeL(editorMode);
        }
    else // no FepAwareTextEditor
        { // Check for non Edwin derived editors (eg mfne, tel no editor etc)
        if (iInputCapabilities.SupportsWesternNumericIntegerPositive() || iInputCapabilities.SupportsWesternNumericIntegerNegative())
            {
            SwitchInputModeL(EAknEditorNumericInputMode);
            }
        else if (iInputCapabilities.SupportsSecretText())
            {
            SwitchInputModeL(EAknEditorSecretAlphaInputMode);
            }
        else if (iInputCapabilities.SupportsWesternAlphabetic())
            {
            SwitchInputModeL(EAknEditorTextInputMode);
            }
        else
            {
            SwitchInputModeL(EAknEditorNullInputMode);
            }
        }
    }

CAknEdwinState* CExampleFepControl::EditorState() const
    {
    return STATIC_CAST(CAknEdwinState*, iInputCapabilities.FepAwareTextEditor()->Extension1()->State(KNullUid));
    }

/*
 * This method switch and set the input mode of the Avkon editor state
 */
void CExampleFepControl::SwitchInputModeL(TUint aInputMode)
    {
    iInputMode = aInputMode;
    switch(aInputMode)
        {
        case EAknEditorTextInputMode:           // Fall through
        case EAknEditorSecretAlphaInputMode:
            iIndicator->SetState( EMultitapLower ); // Update indicator on status pane
            break;

        case EAknEditorNumericInputMode:
            iIndicator->SetState( ENumeric );
            break;

        case EAknEditorNullInputMode:
            iIndicator->SetState( EStateNone );
            // Newly focused control is null input mode, reset flag
            iInsideInlineEditingTransaction = EFalse;           // Update indicator on status pane
            break;

        default:
            break;
        }
    ClearBuffer();

    // ensure editor is aware of new fep mode
    if (iInputCapabilities.FepAwareTextEditor())
        EditorState()->SetCurrentInputMode(aInputMode);
    }

void CExampleFepControl::ClearBuffer(void)
    {
    iUncommittedText.iCursorPos = 0;
    iUncommittedText.iAnchorPos = 0;

    iMultiTapEngine->ClearBuffer();
    }

// end of file
