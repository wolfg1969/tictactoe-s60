
#ifndef __TICTACTOEGAMEENGINE_H__
#define __TICTACTOEGAMEENGINE_H__

// INCLUDES
#include <e32base.h>

// CONSTANTS
#define BOARD_SIZE 	3
#define BOARD_GRID  9
#define TOTAL_MOVES 512

// The squares in order of importance...
const TInt moves[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

// CLASS DECLARATION
class CTicTacToeGameEngine : public CTimer
	{
	public:
		enum TPlayer
			{
			ENone = -1,
			ENought,
			ECross
			};
			
		enum TGameStatus
			{
			EPlayerWin = 0,
			EComWin,
			EStalemate,
			EOk,
			ENotReady
			};

	public:
		typedef TFixedArray<TPlayer, BOARD_SIZE> TCellContainer;
		typedef TFixedArray<TCellContainer, BOARD_SIZE> TBoard;
		
		// for new engine
		typedef TFixedArray<TBool, TOTAL_MOVES> TWonBoard;
		typedef TFixedArray<TInt, BOARD_GRID> TComMoveOrder;

	public:
		class MObserver
			{
			public:
				virtual void HandleMove () = 0;
					
				virtual void HandleCannotMove() = 0;
				
				virtual void HandlePlayerWin() = 0;
				
				virtual void HandleComWin() = 0;
				
				virtual void HandleStalemate () = 0;

				virtual void HandleBoardReset() = 0;				
		};

	public:
		static CTicTacToeGameEngine* NewLC (TPlayer aHumanPlayer = ECross);

		static CTicTacToeGameEngine* NewL (TPlayer aHumanPlayer = ECross);

		virtual ~CTicTacToeGameEngine();

	public:
		void SetBoardContainer (MObserver* aObserver);
		
		void SetSoundPlayer (MObserver* aObserver);
		
		void EnableSound(TBool aEnableSound);

		void StartNewGame (TPlayer aHumanPlayer);
		
		TGameStatus GameStatus();
		
		TBool MakeHumanMove (TUint aRow, TUint aColumn);

		TBool MakeComputerMove();

		TBoard& Board();
		
		TBool GameEnded();
		
		TBool PlayerMove(TInt move);
		
		TBool ComMove(TInt move);

	protected: // CTimer
		virtual void RunL();

	private:
		CTicTacToeGameEngine (TPlayer aHumanPlayer);

		void ConstructL();

		void ClearBoard();

		TBool DetermineMove ();
		
		void ComputerMove();

		void NotifyObserver();
		
		void SetWonPosition(TInt pos);
		
		TInt BestMove(TInt aPlayCurrentBoard, TInt aComCurrentBoard);
		
		void MakeCurrentBoard();
		
	private:
		TBoard iBoard;	
		
		MObserver* iBoardContainer;
		MObserver* iSoundPlayer;
		
		TBool iEnableSound;
		TBool iGameEnded;
		
		TPlayer iHumanPlayer;
		TPlayer iComputerPlayer;
		TPlayer iPlayerToGo;	
		
		// for new game engine
		TComMoveOrder iMoveOrders;
		TWonBoard iWonBoard;		
		TInt iPlayerCurrentBoard;
		TInt iComCurrentBoard;
	};

#endif // __TICTACTOEGAMEENGINE_H__

// End of File
