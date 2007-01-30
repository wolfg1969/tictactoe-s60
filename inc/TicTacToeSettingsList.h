#ifndef TICTACTOESETTINGSLIST_H_
#define TICTACTOESETTINGSLIST_H_

// INCLUDES
#include <AknSettingItemList.h>


// FORWARD DECLARATIONS
class CTicTacToeInfoAndSettings;


// CLASS DECLARATION

/**
*  CTicTacToeInfoAndSettingsList.
*  
*/
class CTicTacToeSettingsList : public CAknSettingItemList 
    {
    public: // Constructors and destructor
	
        /**
        * CTicTacToeInfoAndSettingsList
        * C++ default constructor.
        */
        CTicTacToeSettingsList(
            CTicTacToeInfoAndSettings& aSettings);

    public: // Functions from base classes

        /**
        * From CAknSettingItemList, CreateSettingItemL.
        */
        virtual CAknSettingItem* CreateSettingItemL(TInt identifier);

    private: // Functions from base classes

        /**
        * From CoeControl, HandleResourceChange.
        */
        virtual void HandleResourceChange(TInt aType);

        /**
        * From CoeControl, SizeChanged.
        */
        virtual void SizeChanged();

    private: // Data

        CTicTacToeInfoAndSettings& iSettings;

        TBool iPlayerType;
    };


#endif /*TICTACTOESETTINGSLIST_H_*/
