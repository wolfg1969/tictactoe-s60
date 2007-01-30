#ifndef TICTACTOEMAINCONTAINER_H_
#define TICTACTOEMAINCONTAINER_H_

// INCLUDES
#include <aknview.h>
#include "TicTacToeGameEngine.h"

// CONSTANTS
#define LINE_WIDTH 				1
#define GRID_WIDTH 				44
#define LEFT_MARGIN 			21
#define TOP_MARGIN 				5
#define IMG_LEFT_MARGIN 		LEFT_MARGIN + 4
#define IMG_TOP_MARGIN 			TOP_MARGIN  + 4
#define CURSOR_LEFT_MARGIN		LEFT_MARGIN + 2
#define CURSOR_TOP_MARGIN		TOP_MARGIN + 2
#define CURSOR_WIDTH			5
#define CURSOR_LENGTH			40

_LIT ( KMultiBitmapFilename, "\\system\\apps\\TicTacToe\\tictactoe.mbm" );

// CLASS DECLARATION
class CTicTacToeView;

/**
*  CTicTacToeContainer container control class.
*  An instance of CTicTacToeContainer contains the view drawn to the screen
*  for CMultiViewsView1
*/
class CTicTacToeContainer : public CCoeControl,
	public CTicTacToeGameEngine::MObserver
    {
    public: // TYPES
        typedef CTicTacToeGameEngine::TGameStatus TGameStatus;
        
    public: // Constructors and destructor

        /**
        * NewL.
        * Two-phased constructor.
        * @param aRect The rectangle this container will be drawn to.
        * @return Pointer to the created instance of CNoughtsAndCrossesContainer.
        */
        static CTicTacToeContainer* NewL(const TRect& aRect,
            CTicTacToeView& view, TInt aCursorRow, TInt aCursorColumn);

        /**
        * ~CNoughtsAndCrossesContainer.
        * Destructor.
        */
        virtual ~CTicTacToeContainer();        
      
    public: // New functions
    	void DisplayGameResult( TGameStatus aStatus );
	
        
    private: // Constructors

        CTicTacToeContainer (CTicTacToeView& aView, 
            TInt aCursorRow, TInt aCursorColumn);

        /**
        * ConstructL.
        * 2nd phase constructor.
        * @param aRect The rectangle this container will be drawn to.
        */
        void ConstructL (const TRect& aRect);

    private: // Functions from base classes

        /**
        * From CoeControl, SizeChanged.
        * Called by framework when the view size is changed.
        */
        virtual void SizeChanged();

        /**
        * From CoeControl, CountComponentControls.
        * Returns the number of components owned by this container.
        * @return Number of component controls
        */
        virtual TInt CountComponentControls() const;

        /**
        * From CCoeControl, ComponentControl.
        * Returns pointer to a particular control.
        * @param aIndex Index of wanted control
        * @return Pointer to component control
        */
        virtual CCoeControl* ComponentControl (TInt aIndex) const;

        
        /**
        * From CCoeControl, Draw.
        * Draws this container to the screen
        * @param aRect The region of the control to be redrawn.
        */
        virtual void Draw (const TRect& aRect) const;

        /**
        * From CCoeControl, OfferKeyEventL.
        * Handles the key events.
        * @return if key-event is consumed, EKeyWasConsumed. Else EKeyWasNotConsumed
        * @param aKeyEvent Key event
        * @param aType Type of key event ( EEventKey, EEventKeyUp or EEventKeyDown )
        */
        virtual TKeyResponse OfferKeyEventL (const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * From CoeControl, HandleResourceChange.
        * Called by framework when the view layout is changed.
        */
        virtual void HandleResourceChange(TInt aType);
        
    private: // CTicTacToeGameEngine::MObserver

        virtual void HandleMove ();

		virtual void HandleCannotMove();
		
        virtual void HandlePlayerWin();
				
		virtual void HandleComWin();
        
        virtual void HandleStalemate();

        virtual void HandleBoardReset();
    
    private: // New functions

        void DrawGrid (const TRect& aRect) const;
		
        void DrawNought (TInt aRow, TInt aColumn) const;

        void DrawCross (TInt aRow, TInt aColumn) const;

        void DrawCursor (const TRgb& aCursorColour, const TRgb& aReturnColour, 
            TInt aRow, TInt aColumn) const;
        
    private: // Data

        CTicTacToeView& iView;
        TUint iCursorRow;
        TUint iCursorColumn;
        
        CFbsBitmap* iCrossImage;
        CFbsBitmap* iNotImage;       
    };

#endif /*TICTACTOEMAINCONTAINER_H_*/
