/*
* ============================================================================
*  Name     : CExampleFepPlugin from fepexampleplugin.h
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#ifndef FEPEXAMPLEPLUGIN_H
#define FEPEXAMPLEPLUGIN_H


#if !defined(__FEPPLUGIN_H__)
#include <fepplugin.h>
#endif

class CCoeFep;

class CExampleFepPlugin : public CCoeFepPlugIn
	{
	public:
		static CExampleFepPlugin* NewL();
		CExampleFepPlugin();

		// from CCoeFepPlugIn
		CCoeFep* NewFepL( CCoeEnv& aConeEnvironment, const CCoeFepParameters& aFepParameters );
		void SynchronouslyExecuteSettingsDialogL( CCoeEnv& aConeEnvironment );
	};

#endif

// End of file
