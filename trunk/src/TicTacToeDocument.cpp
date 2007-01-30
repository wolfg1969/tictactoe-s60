/*
============================================================================
 Name        : TicTacToeDocument.cpp
 Author      : wolfg
 Copyright   : GPL
 Description : CTicTacToeDocument implementation
============================================================================
*/

// INCLUDE FILES
#include "TicTacToeDocument.h"
#include "TicTacToeAppui.h"
#include "TicTacToeInfoAndSettings.h"

// ================= MEMBER FUNCTIONS =======================

// constructor
CTicTacToeDocument::CTicTacToeDocument(CEikApplication& aApp)
: CAknDocument(aApp)    
    {
    }

// destructor
CTicTacToeDocument::~CTicTacToeDocument()
    {
    delete iEngine;
    delete iSettings;
    }

// EPOC default constructor can leave.
void CTicTacToeDocument::ConstructL()
    {
    iSettings = new (ELeave) CTicTacToeInfoAndSettings;

    CDictionaryStore* iniFile = Application()->OpenIniFileLC (CEikonEnv::Static()->FsSession());
	
    if (iniFile->IsPresentL (Application()->AppDllUid()))
        {
        RDictionaryReadStream stream;
        stream.OpenLC (*iniFile, Application()->AppDllUid());	
        stream >> *iSettings;
        CleanupStack::PopAndDestroy();
        }

    CleanupStack::PopAndDestroy (iniFile);

    if (!iSettings->PlayerFirst())
        {
        iEngine = CTicTacToeGameEngine::NewL (CTicTacToeGameEngine::ENought);
        //MakeComputerMove();
        }
    else 
    	{
    	iEngine = CTicTacToeGameEngine::NewL (CTicTacToeGameEngine::ECross);
    	}
    iEngine->EnableSound(iSettings->SoundEnabled());	
    
    }

// Two-phased constructor.
CTicTacToeDocument* CTicTacToeDocument::NewL(
        CEikApplication& aApp)     // CTicTacToeApp reference
    {
    CTicTacToeDocument* self = new (ELeave) CTicTacToeDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }
    
// ----------------------------------------------------
// CTicTacToeDocument::CreateAppUiL()
// constructs CTicTacToeAppUi
// ----------------------------------------------------
//
CEikAppUi* CTicTacToeDocument::CreateAppUiL()
    {
    return new (ELeave) CTicTacToeAppUi;
    }
   
    
// ---------------------------------------------------------------------------
// CTicTacToeDocument::SetObserver()
// 
// ---------------------------------------------------------------------------
//
void CTicTacToeDocument::SetBoardContainer (
    CTicTacToeGameEngine::MObserver* aObserver)
    {
    iEngine->SetBoardContainer (aObserver);
    }
    
void CTicTacToeDocument::SetSoundPlayer(
	CTicTacToeGameEngine::MObserver* aObserver)
	{
	iEngine->SetSoundPlayer (aObserver);
	}

// ---------------------------------------------------------------------------
// CTicTacToeDocument::NewGame()
// 
// ---------------------------------------------------------------------------
//
void CTicTacToeDocument::NewGame()
    {
    iEngine->EnableSound(iSettings->SoundEnabled());
    if (!iSettings->PlayerFirst())
        {
        iEngine->StartNewGame(CTicTacToeGameEngine::ENought);
        }
    else 
    	{
    	iEngine->StartNewGame(CTicTacToeGameEngine::ECross);
    	}
    
    }

// ---------------------------------------------------------------------------
// CTicTacToeDocument::CanMove()
// 
// ---------------------------------------------------------------------------
//
TBool CTicTacToeDocument::CanMove() const
    {
    //return iEngine->CanMove();
    return iEngine->GameStatus() == CTicTacToeGameEngine::EOk;
    }

// ---------------------------------------------------------------------------
// CTicTacToeDocument::MakeHumanMove()
// 
// ---------------------------------------------------------------------------
//
TBool CTicTacToeDocument::MakeHumanMove(TInt aRow, TInt aColumn)
    {
    return iEngine->MakeHumanMove (aRow, aColumn);
    }

// ---------------------------------------------------------------------------
// CTicTacToeDocument::MakeComputerMove()
// 
// ---------------------------------------------------------------------------
//
TBool CTicTacToeDocument::MakeComputerMove()
    {
    return iEngine->MakeComputerMove();
    }

// ---------------------------------------------------------------------------
// CTicTacToeDocument::InfoAndSettings()
// 
// ---------------------------------------------------------------------------
//
CTicTacToeInfoAndSettings& 
    CTicTacToeDocument::InfoAndSettings()
    {
    return *iSettings;
    }

// ---------------------------------------------------------------------------
// CTicTacToeDocument::InfoAndSettings()
// 
// ---------------------------------------------------------------------------
//
const CTicTacToeInfoAndSettings& 
    CTicTacToeDocument::InfoAndSettings() const
    {
    return *iSettings;
    }

// ---------------------------------------------------------------------------
// CTicTacToeDocument::SaveInfoAndSettingsL()
// 
// ---------------------------------------------------------------------------
//
void CTicTacToeDocument::SaveInfoAndSettingsL()
    {
    iEngine->EnableSound(iSettings->SoundEnabled());
    
    CDictionaryStore* iniFile = Application()->OpenIniFileLC (CEikonEnv::Static()->FsSession());
	
    iniFile->RemoveL (Application()->AppDllUid());

    RDictionaryWriteStream stream;

    stream.AssignLC (*iniFile, Application()->AppDllUid());
    stream << *iSettings;
    stream.CommitL();
    CleanupStack::PopAndDestroy(); // stream

    iniFile->Commit();

    CleanupStack::PopAndDestroy (iniFile);
    }

// ---------------------------------------------------------------------------
// CTicTacToeDocument::Board()
// 
// ---------------------------------------------------------------------------
//
const CTicTacToeDocument::TBoard& CTicTacToeDocument::Board() const
    {
    return iEngine->Board();
    }
    
TBool CTicTacToeDocument::GameEnded() const
	{
	return iEngine->GameEnded();
	}
    
// End of File

  
