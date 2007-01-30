#include <eikapp.h>
#include <eikappui.h>
#include <aknenv.h>
#include "TicTacToeSoundPlayer.h"

CTicTacToeSoundPlayer* CTicTacToeSoundPlayer::NewL()
	{
    CTicTacToeSoundPlayer* self = NewLC();
    CleanupStack::Pop(self);
    return self;
	}

    
CTicTacToeSoundPlayer* CTicTacToeSoundPlayer::NewLC()
	{
    CTicTacToeSoundPlayer* self = new (ELeave) CTicTacToeSoundPlayer();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
	}

CTicTacToeSoundPlayer::CTicTacToeSoundPlayer()
	{
	}


CTicTacToeSoundPlayer::~CTicTacToeSoundPlayer()
	{
    if (iMdaPlayer) 
    	{
    	delete iMdaPlayer;    
    	iMdaPlayer = NULL;
    	}
	}


void CTicTacToeSoundPlayer::ConstructL()
	{
	}

void CTicTacToeSoundPlayer::PlayFile(const TDesC& aFileName)
	{
	if (iMdaPlayer) 
		{
		delete iMdaPlayer;
		iMdaPlayer = NULL;
		}	
	#ifdef __WINS__
        // on emulator, the sound files used by application 
        // are deployed onto c: drive
        _LIT( tFullPath,"c:\\system\\apps\\TicTacToe\\" );
        TParse parse;

    #else
        // on real phone, application can be installed to the 
        // memory card ( non-"C:" drive ), this part of code evaluates
        // current application path:
        
        // find the instance of EikonEnv
        CEikonEnv& ee = *CEikonEnv::Static();
        
        // derive the instance of EikonAppUi
        CEikAppUi& ea = *( ee.EikAppUi() ); 
        
        // fetch the application full filename
        TFileName tAppFullName = ea.Application()->AppFullName();
		
		TParse parse;
        
        // form parse object containing full app name
        parse.Set( tAppFullName, NULL, NULL );
        
        // get application path with drive letter
        TFileName tFullPath = parse.DriveAndPath();
    #endif

    // use tparse to get the full path to sound file
    parse.Set( tFullPath, &aFileName,  NULL );
    TFileName tFullFileName = parse.FullName();
	
	iMdaPlayer = CMdaAudioPlayerUtility::NewFilePlayerL(tFullFileName, *this); 
	}

// from MMdaAudioPlayerCallback
void CTicTacToeSoundPlayer::MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/)
	{
    iState = aError ? ENotReady : EReady;
    if(iState==EReady)
    	{
        iState=EPlaying;
        iMdaPlayer->Play();
    	}
	}


void CTicTacToeSoundPlayer::MapcPlayComplete(TInt aError)
	{
    iState = aError ? ENotReady : EReady;    
	}

void CTicTacToeSoundPlayer::HandleMove ()
	{
	PlayFile(KDingSoundFilename);
	}

void CTicTacToeSoundPlayer::HandleCannotMove()
	{
	PlayFile(KBeepSoundFilename);
	}

void CTicTacToeSoundPlayer::HandlePlayerWin()
	{
	PlayFile(KYahoo2SoundFilename); 
	}
				
void CTicTacToeSoundPlayer::HandleComWin()
	{
	PlayFile(KYahoo1SoundFilename); 
	}
        
void CTicTacToeSoundPlayer::HandleStalemate()
	{
	PlayFile(KReturnSoundFilename);
	}

void CTicTacToeSoundPlayer::HandleBoardReset()
	{
	}