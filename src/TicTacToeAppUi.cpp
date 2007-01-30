/*
============================================================================
 Name        : TicTacToeAppUi.cpp
 Author      : wolfg
 Copyright   : GPL
 Description : CTicTacToeAppUi implementation
============================================================================
*/

// INCLUDE FILES
#include "TicTacToeAppUi.h"
#include "TicTacToeView.h"
#include "TicTacToeSettingsView.h"
#include <TicTacToe.rsg>
#include "TicTacToe.hrh"

#include <avkon.hrh>

// ================= MEMBER FUNCTIONS =======================
//
// ----------------------------------------------------------
// CTicTacToeAppUi::ConstructL()
// 
// ----------------------------------------------------------
//
void CTicTacToeAppUi::ConstructL()
	{
    BaseConstructL(EAknEnableSkin);

    iGameView = CTicTacToeView::NewL();
    iSettingsView = CTicTacToeSettingsView::NewL();

    // Transfer ownership to base class
    AddViewL( iGameView );
    AddViewL( iSettingsView );

    SetDefaultViewL( *iGameView );

    }

// ----------------------------------------------------
// CTicTacToeAppUi::HandleCommandL(TInt aCommand)
// takes care of command handling
// ----------------------------------------------------
//
void CTicTacToeAppUi::HandleCommandL(TInt aCommand)
    {
    switch ( aCommand )
        {
        case EAknSoftkeyExit:
        case EEikCmdExit:
            {
            Exit();
            break;
            }

        default:
            break;      
        }
    } 