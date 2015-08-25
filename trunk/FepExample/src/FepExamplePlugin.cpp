/*
* ============================================================================
*  Name     : CExampleFepPlugin from fepexampleplugin.cpp
*  Part of  : FepExample
*  Created  : 06/14/2006 by Forum Nokia 
*  Version  : 2.0
*  Copyright: Forum Nokia
* ============================================================================
*/

#include <fepbase.h>
#include <ecom/implementationproxy.h>

#include "fepexample.h"
#include "fepexampleplugin.h"

// Standard ECom factory code
const TInt KExampleFepImplementationValue = 0xE1002549;
const TImplementationProxy ImplementationTable[] =
  {
  IMPLEMENTATION_PROXY_ENTRY( KExampleFepImplementationValue, CExampleFepPlugin::NewL )
  };

EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
  {
  aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
  return ImplementationTable;
  }

// Implement class derived from CCoeFepPlugIn
CExampleFepPlugin* CExampleFepPlugin::NewL()
  { // static
  return new(ELeave) CExampleFepPlugin;
  }

CExampleFepPlugin::CExampleFepPlugin()
	{
	}

CCoeFep* CExampleFepPlugin::NewFepL( CCoeEnv& aConeEnvironment, const CCoeFepParameters& aFepParameters )
  {
  CExampleFep* const fep=new(ELeave) CExampleFep( aConeEnvironment );
  CleanupStack::PushL(fep);
  fep->ConstructL(aFepParameters);
  CleanupStack::Pop(fep);
  return fep;
  }

void CExampleFepPlugin::SynchronouslyExecuteSettingsDialogL( CCoeEnv& /*aConeEnvironment*/ )
  {
  // Add implementation for locating, loading and unloading the resource
  // files needed for executing the settings dialog, if applicable.
  }

// end of file
