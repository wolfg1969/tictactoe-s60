/*
============================================================================
 Name        : TicTacToeApp.h
 Author      : wolfg
 Copyright   : GPL
 Description : Declares main application class.
============================================================================
*/

#ifndef TICTACTOEAPP_H
#define TICTACTOEAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidTicTacToe = { 0x200096D6 };

// CLASS DECLARATION

/**
* CTicTacToeApp application class.
* Provides factory to create concrete document object.
* 
*/
class CTicTacToeApp : public CAknApplication
    {
    
    public: // Functions from base classes
    	/**
        * From CApaApplication, OpenIniFileLC.
        * @return the .ini file associated with the application.
        */
        CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
        
        /**
        * From CApaApplication, returns application's UID (KUidTicTacToe).
        * @return The value of KUidTicTacToe.
        */
        TUid AppDllUid() const;
        
    private:

        /**
        * From CApaApplication, creates CTicTacToeDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();        
        
    };

#endif



