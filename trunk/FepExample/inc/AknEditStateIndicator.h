/*
* ============================================================================
*  Name     : AknEditStateIndicator.h
*  Part of  : Avkon
*
*  Description:
*	Avkon Editing State Indicator Interface
*
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*/

#ifndef AKNEDITSTATEINDICATOR_H
#define AKNEDITSTATEINDICATOR_H

#include <coemop.h>

class CAknIndicatorContainer;

enum TAknEditingState
	{
	// No input mode
	EStateNone,
	// Predictive upper case input mode
	ET9Upper,
	// Predictive lower case input mode
	ET9Lower,
	// Predictive shifted input mode
	ET9Shifted,
	// Numeric input mode
	ENumeric,
	// Multitap upper case input mode
	EMultitapUpper,
	// Multitap lower case input mode
	EMultitapLower,
	// Multitap shifted input mode	
	EMultitapShifted,
	// Predictive Arabic input mode
    ET9Arabic,
	// Predictive Hebrew input mode
    ET9Hebrew,
	// Multitap Arabic input mode
    EMultitapArabic, 
	// Multitap Hebrew input mode    
    EMultitapHebrew,
	// Arabic-Indic numeric input mode
    EArabicIndicNumeric,
    // Multitap Thai input mode
    EMultitapThai,
    // Predictive Thai input mode
    ET9Thai,
    // QWERTY shifted input mode
    EQwertyShift,
    // Predictive Farsi and Urdu input mode
    ET9FarsiAndUrdu,
    // Multitap Farsi and Urdu input mode    
    EMultitapFarsiAndUrdu,
	
	//
	// Chinese states
	//
	// Pinyin input mode
	EIndicatorStatePinyin =20,
	// Zhuyin inout mode
	EIndicatorStateZhuyin,	
	// Stroke input mode
	EIndicatorStateStroke,
	// Zhuyin find input mode	
	EIndicatorStateZhuyinFind,
	// Stroke find input mode    
    EIndicatorStateStrokeFind,
	// Stroke trad input mode    
    EIndicatorStateStrokeTrad,
	// Cang Jie input mode        
    EIndicatorStateCangJie,
    
    //
    // Japanese states
	//
	// Kanji and Hiragana input mode 
    EIndicatorStateHiraganaKanji = 40,  
    // Hiragana input mode
    EIndicatorStateHiragana,        
    // Half-width Katakana input mode
    EIndicatorStateHalfKatakana,    
    // Full-width Katakana input mode
    EIndicatorStateFullKatakana,    
    // Full-width LatinUpper input mode
    EIndicatorStateFullLatinUpper,  
    // Full-width LatinLower input mode
    EIndicatorStateFullLatinLower,  
    // Full-width LatinText input mode
    EIndicatorStateFullLatinText,   
    // Numeric input mode
    EIndicatorStateFullNumeric,     
    // japanese predictive mode
    EIndicatorStateJapanesePredictive,	
    
    //
    // Vietnamese
    //
    // Predictive Vietnamese upper case input mode
    ET9UpperVietnamese = 60,
    // Predictive Vietnamese lower case input mode
    ET9LowerVietnamese,
    // Predictive Vietnamese shifted input mode
    ET9ShiftedVietnamese,        
    // Multitap Vietnamese upper case input mode
    EMultitapUpperVietnamese,
    // Multitap Vietnamese lower case input mode
    EMultitapLowerVietnamese,
    // Multitap Vietnamese shifted input mode
    EMultitapShiftedVietnamese,
    
    //
    // Hindi
    //
    // Multitap Hindi input mode
    EIndicatorStateMultitapHindi= 80,
    // Predictive Hindi input mode
    EIndicatorStatePredictiveHindi,
    // Devangari Indic numeric input mode
    EDevanagariIndicNumeric
	};

/**
 * An abstact class of which virtual methods implementation should be provided for FEP component.
 */
class MAknEditingStateIndicator
	{
public:

	DECLARE_TYPE_ID(0x101F4108)

    /**
    * Sets editing state indicator state. 
    *
    * @param aState State of the editing indicator. 
    */
	virtual void SetState(TAknEditingState aState) = 0; 
	
    /**
    * Gets pointer to indicator container that contains
    * the editing state indicators.
    *
    * @return Indicator container of the editing indicators.
    */
	virtual CAknIndicatorContainer* IndicatorContainer() = 0;
	};

/**
 * This function should be called from MopSupplyObject() of those 
 * components that supply MAknEditingStateIndicator interface for FEP.
 *
 * Retrieves an object of the same type as that encapsulated in aId.
 *
 * This function is used to allow controls to ask their owners for 
 * access to other objects that they own.
 *
 * Other than in the case where NULL is returned, the object returned 
 * must be of the same object type - that is, the @c ETypeId member of 
 * the object pointed to by the pointer returned by this function must
 * be equal to the @c iUid member of @c aId.
 *
 * @param aId An encapsulated object type ID. 
 * @return Encapsulated pointer to the provided object.
 *         Note that the encapsulated pointer may be NULL. 
 */
inline TTypeUid::Ptr SupplyMopObject( TTypeUid aId,
                                  MAknEditingStateIndicator* aIndicator )
	{
    if ( aIndicator && aId.iUid == MAknEditingStateIndicator::ETypeId )
        {
        return aId.MakePtr( aIndicator );
        }

    return TTypeUid::Null();
	}

#endif
