/*
============================================================================
 Name        : TicTacToeAppUi.h
 Author      : wolfg
 Copyright   : GPL
 Description : Declares UI class for application.
============================================================================
*/

#ifndef TICTACTOEAPPUI_H
#define TICTACTOEAPPUI_H

// INCLUDES
#include <aknviewappui.h>

// FORWARD DECLARATIONS
class CTicTacToeView;
class CTicTacToeSettingsView;


// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
* 
*/
class CTicTacToeAppUi : public CAknViewAppUi	
    {
    public: // // Constructors and destructor

        /**
        * EPOC default constructor.
        */      
        void ConstructL();        
        
    public: // Functions from base classes
		virtual void HandleCommandL(TInt aCommand);		 
    
    private: //Data
    
    	CTicTacToeView* iGameView;
		CTicTacToeSettingsView* iSettingsView;
        
    };

#endif


