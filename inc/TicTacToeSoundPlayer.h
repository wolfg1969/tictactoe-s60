#ifndef TICTACTOESOUNDPLAYER_H_
#define TICTACTOESOUNDPLAYER_H_

// INCLUDES
#include <MdaAudioSamplePlayer.h>
#include "TicTacToeGameEngine.h"

// CONSTANTS
_LIT ( KBeepSoundFilename, "beep.au");
_LIT ( KDingSoundFilename, "ding.au");
_LIT ( KReturnSoundFilename, "return.au");
_LIT ( KYahoo1SoundFilename, "yahoo1.au");
_LIT ( KYahoo2SoundFilename, "yahoo2.au");

class CTicTacToeSoundPlayer: public CBase, 
	public MMdaAudioPlayerCallback, 
	public CTicTacToeGameEngine::MObserver
{
public:
	typedef CTicTacToeGameEngine::TPlayer TPlayer;
public:
    static CTicTacToeSoundPlayer* NewL();
    static CTicTacToeSoundPlayer* NewLC();
    ~CTicTacToeSoundPlayer();   
	
private:

    CTicTacToeSoundPlayer();
    void ConstructL();
    
private:
	//
    // from CTicTacToeGameEngine::MObserver
    //
    virtual void HandleCannotMove();
    
    virtual void HandleMove ();
    
    virtual void HandlePlayerWin();
				
	virtual void HandleComWin();
        
    virtual void HandleStalemate();

    virtual void HandleBoardReset();   
    
private:
    //
    // from MMdaAudioPlayerCallback
    //
    void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
    void MapcPlayComplete(TInt aError);   
    
private: // New functions
	void PlayFile(const TDesC& aFileName);

private:
    enum TState
    {
        ENotReady,
        EReady,
        EPlaying
    };
    
    TState iState;
    CMdaAudioPlayerUtility* iMdaPlayer;
};

#endif /*TICTACTOESOUNDPLAYER_H_*/

