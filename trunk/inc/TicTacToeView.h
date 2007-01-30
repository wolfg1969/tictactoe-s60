#ifndef TICTACTOEVIEW_H_
#define TICTACTOEVIEW_H_

// INCLUDES
#include <aknview.h>
#include "TicTacToeGameEngine.h"
#include "TicTacToeSoundPlayer.h"

// FORWARD DECLARATIONS
class CTicTacToeContainer;
class  CTicTacToeSoundPlayer;

/**
* CTicTacToeView view class.
*/
class CTicTacToeView: public CAknView
	{
	public: // Constructors and destructor
	
		/**
        * NewL.
        * Two-phased constructor.
        * Construct a CTicTacToeView for the AVKON application aApp.
        * Using two phase construction,and return a pointer to the created object
        * @return a pointer to the created instance of CTicTacToeView
        */
        static CTicTacToeView* NewL();
        
        /**
        * ~CTicTacToeView.
        * Virtual Destructor.
        */
        virtual ~CTicTacToeView();
        
	public: // Functions from base classes from CAknView
		
		/**
        * Id
        * @return Id Uid value
        */
        TUid Id() const;

        /**
        * HandleCommandL
        * From CAknView, takes care of command handling.
        * @param aCommand Command to be handled
        */
        virtual void HandleCommandL( TInt aCommand );
    
    private:
        /**
        * DoActivateL
        * From CAknExView, activate an AknView.
        * @param aPrevViewId The id of the previous view
        * @param aCustomMessageId message identifier
        * @param aCustomMessage custom message provided when the view is changed
        */
        void DoActivateL( const TVwsViewId& aPrevViewId,
                          TUid aCustomMessageId,
                          const TDesC8& aCustomMessage );

        /**
        * DoDeactivate
        * From AknView, deactivate an AknView
        * Remove the container class instance from the App UI's stack and
        * deletes the instance
        */
        void DoDeactivate();

    private:   // Constructors and destructor

        /**
        * CTicTacToeView.
        * C++ default constructor.
        */
        CTicTacToeView();


        /**
        * ConstructL.
        * 2nd phase constructor.
        */
        void ConstructL();

    private: // New functions

        void CreateListBoxL (TInt aResourceId);

        void SwapContainerL();

    private: 

        friend class CTicTacToeContainer;

    private: // Data

        /**
        * iContainer, container for this view
        * Owned by CNoughtsAndCrossesView object.
        */
        CTicTacToeContainer* iContainer;
        
        CTicTacToeSoundPlayer* iSoundPlayer;

        TInt iCursorRow;
        TInt iCursorColumn;
	};

#endif /*TICTACTOEVIEW_H_*/
