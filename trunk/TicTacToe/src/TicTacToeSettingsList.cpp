// INCLUDE FILES
#include "TicTacToeInfoAndSettings.h"
#include "TicTacToeSettingsList.h"
#include "TicTacToe.hrh"


// ============================ MEMBER FUNCTIONS ===============================

// ----------------------------------------------------------------------------
// CNoughtsAndCrossesSettingListbox::CNoughtsAndCrossesSettingListbox()
// Default constructor.
// ----------------------------------------------------------------------------
//
CTicTacToeSettingsList::CTicTacToeSettingsList(
    CTicTacToeInfoAndSettings& aSettings) : iSettings (aSettings)
    {
    }

// ----------------------------------------------------------------------------
// CTicTacToeSettingsList::CreateSettingItemL()
// Framework method to create a setting item based upon the user id aSettingId.
// ----------------------------------------------------------------------------
//
CAknSettingItem* CTicTacToeSettingsList::CreateSettingItemL(TInt aIdentifier)
    {
    switch (aIdentifier)
        {
        case ETicTacToePlayerNameText:
            return new (ELeave) CAknTextSettingItem(
                aIdentifier, iSettings.PlayerName());

        case ETicTacToePlayerFirstBinary:
            return new (ELeave) CAknBinaryPopupSettingItem(
                aIdentifier, iSettings.PlayerFirst());

        case ETicTacToeGameSoundEnabledBinary:
            return new (ELeave) CAknBinaryPopupSettingItem(
                aIdentifier, iSettings.SoundEnabled());

    default:
        return NULL;
        }
    }

// ---------------------------------------------------------
// CTicTacToeSettingsList::HandleResourceChange()
// Called by framework when layout is changed.
// ---------------------------------------------------------
//
void CTicTacToeSettingsList::HandleResourceChange(TInt aType)
    {
    CCoeControl::HandleResourceChange(aType);

    // ADDED FOR SCALABLE UI SUPPORT
    // *****************************
    /*if ( aType==KEikDynamicLayoutVariantSwitch )
        {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
        SetRect(rect);
        }*/
    }

// ---------------------------------------------------------
// CTicTacToeSettingsList::SizeChanged()
// Called by framework when the view size is changed.
// ---------------------------------------------------------
//
void CTicTacToeSettingsList::SizeChanged()
    {
    if (ListBox()) 
        {
        ListBox()->SetRect(Rect());
        }
    }

// End of File