/*
============================================================================
 Name        : TicTacToeDocument.h
 Author      : wolfg
 Copyright   : GPL
 Description : Declares document class for application.
============================================================================
*/

#ifndef TICTACTOEDOCUMENT_H
#define TICTACTOEDOCUMENT_H

// INCLUDES
#include <akndoc.h>
#include "TicTacToeGameEngine.h"
   
// CONSTANTS

// FORWARD DECLARATIONS
class  CEikAppUi;
class  CTicTacToeInfoAndSettings;

// CLASS DECLARATION

/**
*  CTicTacToeDocument application class.
*/
class CTicTacToeDocument : public CAknDocument
    {
    public: // Types
        typedef CTicTacToeGameEngine::TBoard TBoard;
        
    public: // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CTicTacToeDocument* NewL(CEikApplication& aApp);

        /**
        * Destructor.
        */
        virtual ~CTicTacToeDocument();

    public: // New functions
    	void SetBoardContainer(CTicTacToeGameEngine::MObserver* aObserver);
    	
    	void SetSoundPlayer(CTicTacToeGameEngine::MObserver* aObserver);
    	
    	void NewGame();
    	
    	TBool CanMove() const;
    	
    	TBool MakeHumanMove(TInt aRow, TInt aColumn);
    	
    	TBool MakeComputerMove();
    	
    	CTicTacToeInfoAndSettings& InfoAndSettings();
    	
    	const CTicTacToeInfoAndSettings& InfoAndSettings() const;
    	
    	void SaveInfoAndSettingsL();
    	
    	const TBoard& Board() const;
    	
    	TBool GameEnded() const;
    	
    private:

        /**
        * EPOC default constructor.
        */
        CTicTacToeDocument(CEikApplication& aApp);
        
        /**
        * ConstructL
        * 2nd phase constructor.
        */
        void ConstructL();

    private:

        /**
        * From CEikDocument, create CTicTacToeAppUi "App UI" object.
        */
        CEikAppUi* CreateAppUiL();
        
    private: // Data
        CTicTacToeInfoAndSettings* iSettings;
        CTicTacToeGameEngine* iEngine;
    };

#endif



