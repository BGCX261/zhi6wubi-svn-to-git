/*
* ============================================================================
*  Name     : CExampleFep from fepexample.h
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#ifndef FEPEXAMPLE_H
#define FEPEXAMPLE_H

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


class CExampleFepControl;

class CExampleFep : public CCoeFep
    {
	public:
		CExampleFep(CCoeEnv& aConeEnvironment);
		void ConstructL(const CCoeFepParameters& aFepParameters);
		virtual ~CExampleFep();

		// from CCoeFep
		inline void SimulateKeyEventsL(const TArray<TUint>& aArrayOfCharacters) {CCoeFep::SimulateKeyEventsL(aArrayOfCharacters);}
		inline TBool IsTurnedOnByL(const TKeyEvent& aKeyEvent) const {return CCoeFep::IsTurnedOnByL(aKeyEvent);}
		inline TBool IsTurnedOffByL(const TKeyEvent& aKeyEvent) const {return CCoeFep::IsTurnedOffByL(aKeyEvent);}
		inline TBool IsOn() const {return CCoeFep::IsOn();}
	private:
		// from CCoeFep
		virtual void CancelTransaction();
		virtual void IsOnHasChangedState();
		virtual void OfferPointerEventL(TEventResponse& aEventResponse,const TPointerEvent& aPointerEvent, const CCoeControl* aWindowOwningControl);
		virtual void OfferKeyEventL(TEventResponse& aEventResponse,const TKeyEvent& aKeyEvent, TEventCode aEventCode);
		virtual void OfferPointerBufferReadyEventL(TEventResponse& aEventResponse, const CCoeControl* /*aWindowOwningControl*/);
		
		// from MCoeFocusObserver
		virtual void HandleChangeInFocus();
		virtual void HandleDestructionOfFocusedItem();

		// from MCoeForegroundObserver
		virtual void HandleGainingForeground();
		virtual void HandleLosingForeground();
		
		// from MFepAttributeStorer (via CCoeFep)
		virtual TInt NumberOfAttributes() const;
		virtual TUid AttributeAtIndex(TInt aIndex) const;
		virtual void WriteAttributeDataToStreamL(TUid aAttributeUid, RWriteStream& aStream) const;
		virtual void ReadAttributeDataFromStreamL(TUid aAttributeUid, RReadStream& aStream);

	private:
		CExampleFepControl* iFepControl;
	};

#endif

// End of file
