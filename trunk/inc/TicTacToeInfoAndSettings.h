#ifndef TICTACTOEINFOANDSETTINGS_H_
#define TICTACTOEINFOANDSETTINGS_H_

// INCLUDES
#include <s32std.h>


// CONSTANTS
#define USERNAME_SIZE 16

// CLASS DECLARATION
class CTicTacToeInfoAndSettings : public CBase
	{
	public:
		typedef TBuf<USERNAME_SIZE> TPlayerName;

	public:
		CTicTacToeInfoAndSettings();

		void SetPlayerName (const TPlayerName& aPlayerName);

		TPlayerName& PlayerName();

		const TPlayerName& PlayerName() const;

		void SetPlayerFirst (TBool aPlayFirst);

		TBool& PlayerFirst();

		TBool PlayerFirst() const;
		
		void SetSoundEnabled (TBool aSoundEnabled);
		
		TBool& SoundEnabled();
		
		TBool SoundEnabled() const;
		
		void AddHumanWins();

		TInt HumanWins() const ;

		void AddHumanLosses();

		TInt HumanLosses() const;
		
		void AddStalemates();
		
		TInt Stalemates() const;

		void ExternalizeL (RWriteStream& aStream) const;
		
		void InternalizeL (RReadStream& aStream);

	private:
		CTicTacToeInfoAndSettings (
			const CTicTacToeInfoAndSettings& aCopy);

		CTicTacToeInfoAndSettings& operator= (
			const CTicTacToeInfoAndSettings& aOther);

	private:
		TPlayerName iPlayerName;
		TBool iPlayerFirst;
		TBool iSoundEnabled;
		TInt iHumanWins;
		TInt iHumanLosses;
		TInt iStalemates;
	};

#endif /*TICTACTOEINFOANDSETTINGS_H_*/
