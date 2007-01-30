/*
============================================================================
 Name        : TicTacToeApp.cpp
 Author      : wolfg
 Copyright   : GPL
 Description : Main application class
============================================================================
*/

// INCLUDE FILES
#include    "TicTacToeApp.h"
#include    "TicTacToeDocument.h"

// ================= MEMBER FUNCTIONS =======================

// -----------------------------------------------------------------------------
// CTicTacToeApp::OpenIniFileLC(RFs& aFs)
// Returns the .ini file associated with the application.
// -----------------------------------------------------------------------------
//
CDictionaryStore* CTicTacToeApp::OpenIniFileLC(RFs& aFs) const
    {
    return CEikApplication::OpenIniFileLC(aFs);
    }

// ---------------------------------------------------------
// CTicTacToeApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CTicTacToeApp::AppDllUid() const
    {
    return KUidTicTacToe;
    }

   
// ---------------------------------------------------------
// CTicTacToeApp::CreateDocumentL()
// Creates CTicTacToeDocument object
// ---------------------------------------------------------
//
CApaDocument* CTicTacToeApp::CreateDocumentL()
    {
    return CTicTacToeDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CTicTacToeApp
// Returns: created application object
// ---------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return new CTicTacToeApp;
    }

// ---------------------------------------------------------
// E32Dll(TDllReason) 
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ---------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
    {
    return KErrNone;
    }

  

