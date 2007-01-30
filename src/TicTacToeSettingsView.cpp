// INCLUDE FILES
#include <aknviewappui.h>

#include "TicTacToeSettingsList.h"
#include "TicTacToeSettingsView.h"
#include "TicTacToeDocument.h"

#include "TicTacToe.hrh"
#include <TicTacToe.rsg>


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTicTacToeSettingsView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTicTacToeSettingsView* CTicTacToeSettingsView::NewL()
    {
    CTicTacToeSettingsView* self = new (ELeave) CTicTacToeSettingsView;
    CleanupStack::PushL (self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// CTicTacToeSettingsView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTicTacToeSettingsView::ConstructL()
    {
    BaseConstructL (R_TICTACTOE_SETTINGS_VIEW);
    }

// -----------------------------------------------------------------------------
// CTicTacToeSettingsView::CTicTacToeSettingsView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CTicTacToeSettingsView::CTicTacToeSettingsView() : iSettingsList (NULL)
    {
    }

// -----------------------------------------------------------------------------
// CAknExGridContainerAsMenu::~CAknExGridView()
// Destructor.
// -----------------------------------------------------------------------------
//
CTicTacToeSettingsView::~CTicTacToeSettingsView()
    {
    if (iSettingsList)
        {
        AppUi()->RemoveFromStack (iSettingsList);
        }
    delete iSettingsList;
    }

// -----------------------------------------------------------------------------
// TUid CTicTacToeSettingsView::Id()
// Returns the View Id.
// -----------------------------------------------------------------------------
//
TUid CTicTacToeSettingsView::Id() const
    {
    return TUid::Uid (ETicTacToeSettingsViewId);
    }

// -----------------------------------------------------------------------------
// CAknExGridView::HandleCommandL()
// Handles the commands.
// -----------------------------------------------------------------------------
//
void CTicTacToeSettingsView::HandleCommandL (TInt aCommand)
    {
    switch (aCommand)
        {
        case EAknSoftkeyOk:
            {
            CTicTacToeDocument* document = static_cast<
                CTicTacToeDocument*> (AppUi()->Document());
            iSettingsList->StoreSettingsL();
            document->SaveInfoAndSettingsL();
            //document->NewGame();
            AppUi()->ActivateLocalViewL (TUid::Uid (ETicTacToeGameViewId));
            break;
            }

        case EAknSoftkeyCancel:
            {
            AppUi()->ActivateLocalViewL (TUid::Uid (ETicTacToeGameViewId));
            break;
            }

        default:
            AppUi()->HandleCommandL (aCommand);	
        }
    }

// -----------------------------------------------------------------------------
// CTicTacToeSettingsView::DoActivateL()
// Creates the Container class object.
// -----------------------------------------------------------------------------
//
void CTicTacToeSettingsView::DoActivateL (const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/)
    {
    if (!iSettingsList)
        {
        CTicTacToeDocument* document = static_cast<
            CTicTacToeDocument*> (AppUi()->Document());

        iSettingsList = new (ELeave) CTicTacToeSettingsList (document->InfoAndSettings());

        iSettingsList->SetMopParent (this);
        iSettingsList->ConstructFromResourceL (R_TICTACTOE_SETTINGS_LIST);
        AppUi()->AddToStackL (*this, iSettingsList);
        }

    iSettingsList->MakeVisible (ETrue);
    iSettingsList->SetRect(ClientRect());
    iSettingsList->ActivateL();
    iSettingsList->DrawNow();
    }

// -----------------------------------------------------------------------------
// CTicTacToeSettingsView::DoDeactivate()
// Deletes the Container class object.
// -----------------------------------------------------------------------------
//
void CTicTacToeSettingsView::DoDeactivate()
    {
    if (iSettingsList)
        {
        iSettingsList->MakeVisible (EFalse);
        }
    }

// End of File
