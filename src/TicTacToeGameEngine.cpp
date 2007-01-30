
// INCLUDE FILES
#include <e32math.h>
#include "TicTacToeGameEngine.h"


// CONSTANTS
#define TIMEWAIT 500000

// ============================ MEMBER FUNCTIONS ===============================


CTicTacToeGameEngine* CTicTacToeGameEngine::NewLC(TPlayer aHumanPlayer)
	{
	CTicTacToeGameEngine* self = new(ELeave) CTicTacToeGameEngine (
		aHumanPlayer);
	CleanupStack::PushL (self);
	self->ConstructL();
	return self;
	}

CTicTacToeGameEngine* CTicTacToeGameEngine::NewL(TPlayer aHumanPlayer)
	{
	CTicTacToeGameEngine* self = CTicTacToeGameEngine::NewLC(
		aHumanPlayer);
	CleanupStack::Pop();
	return self;
	}

CTicTacToeGameEngine::~CTicTacToeGameEngine()
	{
	Cancel();
	}

void CTicTacToeGameEngine::SetBoardContainer(MObserver* aObserver)
	{
	iBoardContainer  = aObserver;
	}
	
void CTicTacToeGameEngine::SetSoundPlayer (MObserver* aObserver)
	{
	iSoundPlayer  = aObserver;
	}
	
void CTicTacToeGameEngine::EnableSound(TBool aEnableSound)
	{
	iEnableSound = aEnableSound;
	}

void CTicTacToeGameEngine::StartNewGame(TPlayer aHumanPlayer)
	{
	this->iHumanPlayer = aHumanPlayer;	
	
	iGameEnded = EFalse;
	
	ClearBoard();

	// Determine computer
	if(iHumanPlayer == ENought) // COM first
		{
		iComputerPlayer = ECross;
		iPlayerToGo = iComputerPlayer;
		ComputerMove();
		}
	else  // User first
		{
		iComputerPlayer = ENought;
		iPlayerToGo = iHumanPlayer;
		}
		
	if (iSoundPlayer && iEnableSound) 
		{
		iSoundPlayer->HandleBoardReset ();
		}
	if (iBoardContainer)
		{
		iBoardContainer->HandleBoardReset();
		}
	}
	
CTicTacToeGameEngine::TGameStatus CTicTacToeGameEngine::GameStatus()
	{
	if (iWonBoard[iPlayerCurrentBoard]) 
		{
		return EPlayerWin;
		}
	if (iWonBoard[iComCurrentBoard]) 
		{
		return EComWin;
		}
	if ((iPlayerCurrentBoard | iComCurrentBoard) == TOTAL_MOVES - 1) 
		{
		return EStalemate;
		}
	if (iComputerPlayer == ECross && (iPlayerCurrentBoard | iComCurrentBoard) == 0)
		{
		return ENotReady;
		}
	return EOk;
	}

TBool CTicTacToeGameEngine::MakeHumanMove (TUint aRow, TUint aColumn)
	{
	TInt move = aColumn + aRow * 3;
	if (((iPlayerCurrentBoard | iComCurrentBoard) & (1 << move)) != 0)
		{
		if (iSoundPlayer && iEnableSound) iSoundPlayer->HandleCannotMove ();
		return EFalse;
		}

	if (iPlayerToGo == iComputerPlayer) return EFalse;

	iPlayerCurrentBoard |= 1 << move;
	
	if (iSoundPlayer && iEnableSound) 
		iSoundPlayer->HandleMove ();
	if (iBoardContainer) 
		iBoardContainer->HandleMove ();
		
	iPlayerToGo = iComputerPlayer;	
	NotifyObserver();
	return ETrue;
	}

TBool CTicTacToeGameEngine::MakeComputerMove()
	{	
	if (!DetermineMove ())
		{
		return EFalse;
		}

	if (iBoardContainer)
		{
		After (TIMEWAIT);
		}
	else // when game first load 
		{
		ComputerMove();
		}

	return ETrue;
	}

CTicTacToeGameEngine::TBoard& CTicTacToeGameEngine::Board()
	{
	MakeCurrentBoard();
	return iBoard;
	}
	
TBool CTicTacToeGameEngine::GameEnded()
	{
	return iGameEnded;
	}
	
void CTicTacToeGameEngine::ComputerMove()
	{
	TInt pos = 0;
	if (iComCurrentBoard == 0 && iComputerPlayer == ECross)
		{
		pos = Math::Random() % 9;		
		}
	else
		{
		pos = BestMove(iPlayerCurrentBoard, iComCurrentBoard);
		}
	iComCurrentBoard |= 1 << pos;
		
	iPlayerToGo = iHumanPlayer;
	NotifyObserver();
	}	

void CTicTacToeGameEngine::RunL()
	{
	ComputerMove();
	}

CTicTacToeGameEngine::CTicTacToeGameEngine (TPlayer aHumanPlayer) :
	CTimer (CActive::EPriorityStandard), iBoardContainer (NULL), 
	iSoundPlayer(NULL), iEnableSound(ETrue), iGameEnded(EFalse),
	iHumanPlayer (aHumanPlayer)
	{
	ClearBoard();
	CActiveScheduler::Add (this);
	
	iMoveOrders.Copy(&moves[0], BOARD_GRID);
	// Initialize all winning positions.
	SetWonPosition((1 << 0) | (1 << 1) | (1 << 2));
	SetWonPosition((1 << 3) | (1 << 4) | (1 << 5));
	SetWonPosition((1 << 6) | (1 << 7) | (1 << 8));
	SetWonPosition((1 << 0) | (1 << 3) | (1 << 6));
	SetWonPosition((1 << 1) | (1 << 4) | (1 << 7));
	SetWonPosition((1 << 2) | (1 << 5) | (1 << 8));
	SetWonPosition((1 << 0) | (1 << 4) | (1 << 8));
	SetWonPosition((1 << 2) | (1 << 4) | (1 << 6));
	
	// Determine computer player
	if(iHumanPlayer == ENought) // COM first
		{
		iComputerPlayer = ECross;
		iPlayerToGo = iComputerPlayer;
		ComputerMove();
		}
	else  // User first
		{
		iComputerPlayer = ENought;
		iPlayerToGo = iHumanPlayer;
		}
	}

void CTicTacToeGameEngine::ConstructL()
	{
	CTimer::ConstructL();
	}

void CTicTacToeGameEngine::ClearBoard()
	{
	// for new game engine
	iComCurrentBoard = 0;
	iPlayerCurrentBoard = 0;	
	}

TBool CTicTacToeGameEngine::DetermineMove ()
	{
	if ((iPlayerCurrentBoard | iComCurrentBoard) == TOTAL_MOVES - 1) 
		{
		return EFalse;
		}
	
	return ETrue;
	}
	
void CTicTacToeGameEngine::NotifyObserver()
	{
	iGameEnded = ETrue;
	switch (GameStatus())
		{
		case EPlayerWin:
			{
			if (iSoundPlayer && iEnableSound) 
			{
				iSoundPlayer->HandlePlayerWin ();
			}
			else
			{
				if (iBoardContainer) iBoardContainer->HandlePlayerWin ();	
			}
			break;
			}
		case EComWin:
			{
			if (iBoardContainer)
				iBoardContainer->HandleMove ();
			if (iSoundPlayer && iEnableSound) 
			{
				iSoundPlayer->HandleComWin ();
			}
			else
			{
				if (iBoardContainer)
					iBoardContainer->HandleComWin ();
			}
			break;
			}
		case EStalemate:
			{
			if (iBoardContainer)
				iBoardContainer->HandleMove ();
			
			if (iSoundPlayer && iEnableSound) 
			{
				iSoundPlayer->HandleStalemate ();
			}
			else
			{
				if (iBoardContainer) iBoardContainer->HandleStalemate ();	
			}		
			break;
			}
		case EOk:
			{
			if (iBoardContainer) iBoardContainer->HandleMove ();
			iGameEnded = EFalse;
			break;
			}	
		case ENotReady:
			{
			iGameEnded = EFalse;
			break;		
			}
		}
		
	}
    
void CTicTacToeGameEngine::SetWonPosition(TInt pos)
	{
	for (TInt i = 0; i < TOTAL_MOVES - 1; i++) 
		{
		if ((i & pos) == pos) 
			{
			iWonBoard[i] = ETrue;
			}
		}
	}
	
void CTicTacToeGameEngine::MakeCurrentBoard()
	{
	TInt i, j, m = 0;
	for (i = 0; i < BOARD_SIZE; i++)
		{
		for (j = 0; j < BOARD_SIZE; j++, m++)
			{
			if ((iComCurrentBoard & (1 << m)) != 0) 
				{
				iBoard[i][j] = iComputerPlayer;
				}
			else if ((iPlayerCurrentBoard & (1 << m)) != 0) 
				{
				iBoard[i][j] = iHumanPlayer;
				}
			else 
				{
				iBoard[i][j] = ENone;
				}
			}			
		}
	}
	
TInt CTicTacToeGameEngine::BestMove
	(TInt aPlayerCurrentBoard, TInt aComCurrentBoard)
	{
	TInt bestmove = -1;
	for (TInt i = 0; i < 9; i++) 
		{
		TBool playerWin = EFalse;
		TInt comMove = iMoveOrders[i];
		if (((aComCurrentBoard & (1 << comMove)) == 0) && ((aPlayerCurrentBoard & (1 << comMove)) == 0)) 
			{
			TInt comPos = aComCurrentBoard | (1 << comMove);
			if (iWonBoard[comPos]) 
				{
				// white wins, take it!
				return comMove;
				}
				for (TInt playerMove = 0; playerMove < 9; playerMove++) 
					{
					if (((comPos & (1 << playerMove)) == 0) && ((aPlayerCurrentBoard & (1 << playerMove)) == 0)) 
						{
						int playerPos = aPlayerCurrentBoard | (1 << playerMove);
						if (iWonBoard[playerPos]) 
							{
							// black wins, take another
							playerWin = ETrue;
							break;
							}
						}
					}
				if (playerWin) continue;
				// Neither white nor black can win in one move, this will do.
				if (bestmove == -1) 
					{
					bestmove = comMove;
					}
				}
			}
		if (bestmove != -1) 
			{
			return bestmove;
			}

		// No move is totally satisfactory, try the first one that is open
		for (TInt i = 0; i < 9; i++) 
			{
			TInt comMove = iMoveOrders[i];
			if (((aComCurrentBoard & (1 << comMove)) == 0) && ((aPlayerCurrentBoard & (1 << comMove)) == 0)) 
				{
				return comMove;
				}
			}

		// No more moves
		return -1;
	}

// End of File
