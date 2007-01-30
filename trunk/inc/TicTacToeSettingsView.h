#ifndef TICTACTOESETTINGSVIEW_H_
#define TICTACTOESETTINGSVIEW_H_

// INCLUDES
#include <aknview.h>

// FORWARD DECLARATIONS
class CTicTacToeSettingsList;


// CLASS DECLARATION
/**
*  CTicTacToeSettingsView view class.
*
*/
class CTicTacToeSettingsView : public CAknView
    {
    public:

        /**
        * NewL.
        * Two-phased constructor.
        * Construct a CTicTacToeSettingsView using two phase construction,
        * and return a pointer to the created object
        * @return A pointer to the created instance of CTicTacToeSettingsView
        */
        static CTicTacToeSettingsView* NewL();

        /**
        * ~CNoughtsAndCrossesView
        * Virtual Destructor.
        */
        virtual ~CTicTacToeSettingsView();

    public: // Functions from base classes

        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        virtual TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * Handles the commands.
        * @param aCommand Command to be handled.
        */
        virtual void HandleCommandL (TInt aCommand);
	
    private: // Functions from base classes

        /**
        * From CAknView, DoActivateL.
        * Creates the Container class object.
        * @param aPrevViewId Specified TVwsViewId.
        * @param aCustomMessageId Specified TUid.
        * @param aCustomMessage Specified custom message.
        */
        virtual void DoActivateL (const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId, const TDesC8& aCustomMessage);

        /**
        * From CAknView, DoDeactivate.
        * Deletes the Container class object.
        */
        virtual void DoDeactivate();

    private:

        /**
        * CTicTacToeSettingsView.
        * C++ default constructor.
        */
        CTicTacToeSettingsView();

        /**
        * ConstructL.
        * 2nd phase constructor.
        */
        void ConstructL();

    private: // Data

       CTicTacToeSettingsList* iSettingsList;
    };

#endif /*TICTACTOESETTINGSVIEW_H_*/
