// INCLUDE FILES
#include <aknviewappui.h>
#include <AknUtils.h>
#include <aknnotewrappers.h>
#include <AknsDrawUtils.h>

#include "TicTacToeContainer.h"
#include "TicTacToeDocument.h"
#include "TicTacToeInfoAndSettings.h"
#include "TicTacToeView.h"
#include "tictactoe.mbg"
#include <TicTacToe.rsg>

// ========================= MEMBER FUNCTIONS ==================================


// -----------------------------------------------------------------------------
// CTicTacToeContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTicTacToeContainer* CTicTacToeContainer::NewL(
	const TRect& aRect, CTicTacToeView& aView, TInt aCursorRow, TInt aCursorColumn) 
    {
    CTicTacToeContainer* self = new ( ELeave ) CTicTacToeContainer(
    	aView, aCursorRow, aCursorColumn);
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    CleanupStack::Pop( self );
    return self;
    }
    
// ----------------------------------------------------------------------------
// CTicTacToeContainer::CTicTacToeContainer()
// Default constructor.
// ----------------------------------------------------------------------------
//
CTicTacToeContainer::CTicTacToeContainer(
    CTicTacToeView& aView, TInt aCursorRow, TInt aCursorColumn) :
    iView (aView), iCursorRow (aCursorRow), iCursorColumn (aCursorColumn)
    {
    }
    
// -----------------------------------------------------------------------------
// CTicTacToeContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    SetRect(aRect);
    
    iCrossImage = iEikonEnv->CreateBitmapL
								( KMultiBitmapFilename, EMbmTictactoeCross );
    iNotImage   = iEikonEnv->CreateBitmapL
								( KMultiBitmapFilename, EMbmTictactoeNot );
								
    ActivateL();
    HandleBoardReset();
    }
    
// -----------------------------------------------------------------------------
// CTicTacToeContainer::~CTicTacToeContainer()
// Destructor.
// -----------------------------------------------------------------------------
//
CTicTacToeContainer::~CTicTacToeContainer()
    {
    delete iCrossImage;
    iCrossImage = NULL;
    
    delete iNotImage;
    iNotImage = NULL;
    }
    
// -----------------------------------------------------------------------------
// CTicTacToeContainer::DisplayGameResult()
// -----------------------------------------------------------------------------
//    
void CTicTacToeContainer::DisplayGameResult( TGameStatus aStatus )
	{		
		TInt resId = R_STRING_A_CATS_GAME;
		if (aStatus == CTicTacToeGameEngine::EPlayerWin)
			{
			resId = R_STRING_PLAYER_WIN;
			}
		else if (aStatus == CTicTacToeGameEngine::EComWin)
			{
			resId = R_STRING_PLAYER_LOSS;
			}
		HBufC* msgBuf = CCoeEnv::Static()->AllocReadResourceLC(resId);
		CAknInformationNote* informationNote;
        informationNote = new ( ELeave ) CAknInformationNote;
        informationNote->ExecuteLD( *msgBuf ); 
        CleanupStack::PopAndDestroy(msgBuf);
	}
    
// -----------------------------------------------------------------------------
// CTicTacToeContainer::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::SizeChanged()
{
	
}
    
// ---------------------------------------------------------
// CTicTacToeContainer::HandleResourceChange()
// Called by framework when layout is changed.
// ---------------------------------------------------------
//
void CTicTacToeContainer::HandleResourceChange(TInt aType)
    {
    CCoeControl::HandleResourceChange(aType);

    // ADDED FOR SCALABLE UI SUPPORT
    // *****************************
    /*
    if ( aType==KEikDynamicLayoutVariantSwitch )
        {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
        SetRect(rect);
        }
    */
    }
    

// -----------------------------------------------------------------------------
// CTicTacToeContainer::CountComponentControls() const
// returns number of controls inside this container.
// -----------------------------------------------------------------------------
//
TInt CTicTacToeContainer::CountComponentControls() const
    {
    return 0;
    }


// -----------------------------------------------------------------------------
// CTicTacToeContainer::ComponentControl() const
// returns pointer of controls inside this container
// -----------------------------------------------------------------------------
//
CCoeControl* CTicTacToeContainer::ComponentControl( TInt /*aIndex*/ ) const
    {
    return NULL;
    }

// -----------------------------------------------------------------------------
// CTicTacToeContainer::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();    
    
    gc.Clear( aRect );
    
    
    gc.SetBrushColor(KRgbWhite);
    gc.SetBrushStyle (CGraphicsContext::ESolidBrush);

    DrawGrid (aRect);
    
    CTicTacToeDocument* document = static_cast<
        CTicTacToeDocument*> (iView.AppUi()->Document());    
    
    if (!document->GameEnded())
    	{
    	DrawCursor (KRgbBlue, KRgbBlack, iCursorRow, iCursorColumn);
    	}
    
    const CTicTacToeDocument::TBoard& board = document->Board();

    for (TInt i = 0; i < BOARD_SIZE; ++i)
        {
        for (TInt j = 0; j < BOARD_SIZE; ++j)
            {
            if (board[i][j] == CTicTacToeGameEngine::ENought)
                {
                DrawNought (i, j);
                }
            else if (board[i][j] == CTicTacToeGameEngine::ECross)
                {
                DrawCross (i, j);
                }
            }
        }
    }

// ---------------------------------------------------------------------------
// CTicTacToeContainer::OfferKeyEventL()
// Handles keyevents.
// ---------------------------------------------------------------------------
//
TKeyResponse CTicTacToeContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    if (aType != EEventKey)
        {
        return EKeyWasNotConsumed;
        }
	CTicTacToeDocument* document = static_cast<
             CTicTacToeDocument*> (iView.AppUi()->Document());
             
    if (aKeyEvent.iCode == EKeyEnter || aKeyEvent.iCode == EKeyOK)
        {
        if (!document->CanMove())
            {
            return EKeyWasConsumed;
            }

        if (document->MakeHumanMove (iCursorRow, iCursorColumn))
            {
            if (document->CanMove())
                {
                document->MakeComputerMove();
                }
            }	
        return  EKeyWasConsumed;
        }
    else if (aKeyEvent.iCode == EKeyUpArrow && iCursorRow > 0)
        {
        if (document->CanMove())
        	{
        	--iCursorRow;
        	DrawDeferred();
        	}
        return EKeyWasNotConsumed;
        }
    else if (aKeyEvent.iCode == EKeyDownArrow && iCursorRow < (BOARD_SIZE-1))
        {
        if (document->CanMove())
        	{
        	++iCursorRow;
        	DrawDeferred();
        	}
        return EKeyWasNotConsumed;
        }
    else if (aKeyEvent.iCode == EKeyLeftArrow && iCursorColumn > 0)
        {
        if (document->CanMove())
        	{
        	--iCursorColumn;
        	DrawDeferred();
        	}
        return EKeyWasNotConsumed;
        }
    else if (aKeyEvent.iCode == EKeyRightArrow && iCursorColumn < (BOARD_SIZE-1))
        {
        if (document->CanMove())
        	{
        	++iCursorColumn;
        	DrawDeferred();
        	}
        return EKeyWasNotConsumed;
        }	

    return EKeyWasNotConsumed;
    }

// -----------------------------------------------------------------------------
// CTicTacToeContainer::HandleMove()
// 
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::HandleMove()
    {
    DrawDeferred();
    }
    
void CTicTacToeContainer::HandleCannotMove()
	{
	}

// -----------------------------------------------------------------------------
// CTicTacToeContainer::HandlePlayerWin()
// 
// -----------------------------------------------------------------------------
//    
void CTicTacToeContainer::HandlePlayerWin()
	{
	DrawDeferred(); 
    
    CTicTacToeDocument* document = static_cast<
         CTicTacToeDocument*> (iView.AppUi()->Document());

    document->InfoAndSettings().AddHumanWins();
    DisplayGameResult(CTicTacToeGameEngine::EPlayerWin); 
	
	document->SaveInfoAndSettingsL(); 
	}
	
// -----------------------------------------------------------------------------
// CTicTacToeContainer::HandleComWin()
// 
// -----------------------------------------------------------------------------
// 			
void CTicTacToeContainer::HandleComWin()
	{
	DrawDeferred(); 
    
    CTicTacToeDocument* document = static_cast<
         CTicTacToeDocument*> (iView.AppUi()->Document());

    document->InfoAndSettings().AddHumanLosses();
    DisplayGameResult(CTicTacToeGameEngine::EComWin);
	
	document->SaveInfoAndSettingsL(); 
	}
    
// -----------------------------------------------------------------------------
// CTicTacToeContainer::HandleStalemate()
// 
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::HandleStalemate()
    {	
    DrawDeferred();   
    DisplayGameResult(CTicTacToeGameEngine::EStalemate);
	
	CTicTacToeDocument* document = static_cast<
         CTicTacToeDocument*> (iView.AppUi()->Document());
    
	document->InfoAndSettings().AddStalemates();
    document->SaveInfoAndSettingsL();   	
    }

// -----------------------------------------------------------------------------
// CTicTacToeContainer::HandleBoardReset()
// 
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::HandleBoardReset()
    {
    iCursorRow = 0;
    iCursorColumn = 0;
    DrawDeferred();
    }

// -----------------------------------------------------------------------------
// CTicTacToeContainer::DrawGrid()
// 
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::DrawGrid(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.Clear(aRect);
    
    gc.SetPenSize(TSize(LINE_WIDTH, LINE_WIDTH));
    
    TPoint point1;
    TPoint point2;

    TUint i;
    
    for (i=1 ; i<BOARD_SIZE ; ++i)
        {
        // Draw horizontal lines
        TUint pY = TOP_MARGIN  + GRID_WIDTH * i + LINE_WIDTH * (i - 1);
        point1.SetXY (LEFT_MARGIN, pY);
        point2.SetXY (aRect.Width() - LEFT_MARGIN, pY);	
        gc.DrawLine (point1, point2);
        
        // Draw vertical lines
        TUint pX = LEFT_MARGIN  + GRID_WIDTH * i + LINE_WIDTH * (i - 1);
        point1.SetXY (pX, TOP_MARGIN);
        point2.SetXY (pX, aRect.Height() - TOP_MARGIN);	
        gc.DrawLine (point1, point2);
        }

    }

// -----------------------------------------------------------------------------
// CTicTacToeContainer::DrawNought()
// 
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::DrawNought(TInt aRow, TInt aColumn) const
    {
    CWindowGc& gc = SystemGc();
    gc.BitBlt(TPoint( IMG_LEFT_MARGIN + aColumn * (GRID_WIDTH + LINE_WIDTH),
    	 IMG_TOP_MARGIN + aRow * (GRID_WIDTH + LINE_WIDTH)), iNotImage);
    }

// -----------------------------------------------------------------------------
// CTicTacToeContainer::DrawCross()
// 
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::DrawCross(TInt aRow, TInt aColumn) const
    {
    CWindowGc& gc = SystemGc();
    gc.BitBlt(TPoint( IMG_LEFT_MARGIN + aColumn * (GRID_WIDTH + LINE_WIDTH),
    	 IMG_TOP_MARGIN + aRow * (GRID_WIDTH + LINE_WIDTH)), iCrossImage);
    }

// -----------------------------------------------------------------------------
// CTicTacToeContainer::DrawCursor()
// 
// -----------------------------------------------------------------------------
//
void CTicTacToeContainer::DrawCursor(const TRgb& aCursorColour,
    const TRgb& aReturnColour, TInt aRow, TInt aColumn) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenSize(TSize(1, 1));
    
    TPoint point1;
    TPoint point2;

    gc.SetPenColor (aCursorColour);
    
    TUint gridWidth = GRID_WIDTH + LINE_WIDTH;    
    
    // Top left
    TUint pX = CURSOR_LEFT_MARGIN + aColumn * gridWidth;
    TUint pY = CURSOR_TOP_MARGIN + aRow * gridWidth;
    
    point1.SetXY (pX, pY);
    point2.SetXY (pX + CURSOR_WIDTH, pY);
    	
    gc.DrawLine (point1, point2);

    point2.SetXY (pX, pY + CURSOR_WIDTH);

    gc.DrawLine (point1, point2); 

    // Top right
    
    point1.SetXY (pX + CURSOR_LENGTH, pY);
    point2.SetXY (pX + CURSOR_LENGTH - CURSOR_WIDTH, pY);

    gc.DrawLine (point1, point2);

    point2.SetXY (pX + CURSOR_LENGTH, pY + CURSOR_WIDTH );
    
    gc.DrawLine (point1, point2);

    // Bottom left
    point1.SetXY (pX, pY + CURSOR_LENGTH);
    point2.SetXY (pX + CURSOR_WIDTH, pY + 40);

    gc.DrawLine (point1, point2);

    point2.SetXY (pX, pY + CURSOR_LENGTH - CURSOR_WIDTH);

    gc.DrawLine (point1, point2);

    // Bottom right
    point1.SetXY (pX + CURSOR_LENGTH, pY + CURSOR_LENGTH);
    point2.SetXY (pX + CURSOR_LENGTH, pY + CURSOR_LENGTH - CURSOR_WIDTH);

    gc.DrawLine (point1, point2);

    point2.SetXY (pX + CURSOR_LENGTH - CURSOR_WIDTH, pY + CURSOR_LENGTH);

    gc.DrawLine (point1, point2);

    gc.SetPenColor (aReturnColour);
    }
    


// End of File
