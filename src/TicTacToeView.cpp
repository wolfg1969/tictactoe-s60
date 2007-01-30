// INCLUDE FILES
#include <aknviewappui.h>
#include <aknconsts.h>
#include <tictactoe.rsg>

#include "TicTacToeView.h"
#include "TicTacToeContainer.h"
#include "TicTacToeDocument.h"
#include "TicTacToeInfoAndSettings.h"
#include "TicTacToe.hrh"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CTicTacToeView::CTicTacToeView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CTicTacToeView::CTicTacToeView() : iContainer (NULL),
    iCursorRow (0), iCursorColumn (0)
    {
    }


// -----------------------------------------------------------------------------
// CTicTacToeView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTicTacToeView* CTicTacToeView::NewL()
    {
    CTicTacToeView* self = new ( ELeave ) CTicTacToeView();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CTicTacToeView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTicTacToeView::ConstructL()
    {
    BaseConstructL( R_TICTACTOE_GAME_VIEW );
    }

// -----------------------------------------------------------------------------
// CTicTacToeView::~CTicTacToeView()
// Destructor.
// -----------------------------------------------------------------------------
//
CTicTacToeView::~CTicTacToeView()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromViewStack (*this, iContainer);
        }
	
    delete iContainer;
    }

// -----------------------------------------------------------------------------
// CTicTacToeView::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CTicTacToeView::Id() const
    {
    return TUid::Uid( ETicTacToeGameViewId );
    }

// -----------------------------------------------------------------------------
// CTicTacToeView::HandleCommandL()
// Handles the commands.
// -----------------------------------------------------------------------------
//
void CTicTacToeView::HandleCommandL (TInt aCommand)
    {
    switch (aCommand)
        {
        case ETicTacToeCmdAppNewGame:
            {
            CTicTacToeDocument* document = static_cast<
                CTicTacToeDocument*> (AppUi()->Document());
            document->NewGame();			
            break;
            }

        case ETicTacToeCmdAppSetting:
            {
            AppUi()->ActivateLocalViewL (TUid::Uid (ETicTacToeSettingsViewId));
            break;
            }

        case ETicTacToeCmdAppStatistics:
            {
            TBuf<96> stats;
            TBuf<32> stats1;
            TBuf<32> stats2;            

            CTicTacToeDocument* document = static_cast<
                CTicTacToeDocument*> (AppUi()->Document());

			HBufC* formatBuf1 = CCoeEnv::Static()->AllocReadResourceLC(R_STRING_STATS_1);
            stats1.Format ( *formatBuf1, 
            	document->InfoAndSettings().HumanWins(),
            	document->InfoAndSettings().HumanLosses());
            CleanupStack::PopAndDestroy(formatBuf1);
            	
            HBufC* formatBuf2 = CCoeEnv::Static()->AllocReadResourceLC(R_STRING_STATS_2);
            stats2.Format ( *formatBuf2,	
            	document->InfoAndSettings().Stalemates());
            CleanupStack::PopAndDestroy(formatBuf2);
			
			stats = document->InfoAndSettings().PlayerName();
			stats.Append(stats1);
			static_cast<CEikonEnv*> (iCoeEnv)->InfoWinL (stats, stats2);            
            break;
            }

        default:
            AppUi()->HandleCommandL (aCommand);	
        }	
    }
    
// -----------------------------------------------------------------------------
// CTicTacToeView::DoActivateL()
// Activate an TicTacToeView
// -----------------------------------------------------------------------------
//
void CTicTacToeView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    if (!iContainer)
        {
        iContainer = CTicTacToeContainer::NewL (ClientRect(),
            *this, iCursorRow, iCursorColumn);
            
        iSoundPlayer = CTicTacToeSoundPlayer::NewL();
		
        CTicTacToeDocument* document = static_cast<
            CTicTacToeDocument*> (AppUi()->Document());

        document->SetBoardContainer (iContainer);
        document->SetSoundPlayer (iSoundPlayer);
        AppUi()->AddToStackL (*this, iContainer);
        }

    iContainer->MakeVisible (ETrue);
    }

// -----------------------------------------------------------------------------
// CTicTacToeView::DoDeactivate()
// DeActivate TicTacToeView
// -----------------------------------------------------------------------------
//
void CTicTacToeView::DoDeactivate()
    {
    CTicTacToeDocument* document = static_cast<
            CTicTacToeDocument*> (AppUi()->Document());		
        
    if (iContainer)
        {
        document->SetBoardContainer (NULL);        
        AppUi()->RemoveFromStack (iContainer);
        delete iContainer;
        iContainer = NULL;        
        }
    if (iSoundPlayer)
    	{
    	document->SetSoundPlayer (NULL);
        delete iSoundPlayer;
        iSoundPlayer = NULL;
    	}
    }

// End of File