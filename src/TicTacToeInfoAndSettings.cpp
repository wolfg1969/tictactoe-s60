// INCLUDE FILES
#include <s32file.h>

#include "TicTacToeInfoAndSettings.h"


// ============================ MEMBER FUNCTIONS ===============================

CTicTacToeInfoAndSettings::CTicTacToeInfoAndSettings() : 
	iPlayerName(_L("Player")), iPlayerFirst (ETrue), iSoundEnabled(ETrue)
	{
	}

void CTicTacToeInfoAndSettings::SetPlayerName (const TPlayerName& aPlayerName)
	{
	iPlayerName = aPlayerName;
	}

CTicTacToeInfoAndSettings::TPlayerName& CTicTacToeInfoAndSettings::PlayerName()
	{
	return iPlayerName;
	}

const CTicTacToeInfoAndSettings::TPlayerName& CTicTacToeInfoAndSettings::PlayerName() const
	{
	return iPlayerName;
	}

void CTicTacToeInfoAndSettings::SetPlayerFirst (TBool aPlayFirst)
	{
	iPlayerFirst = aPlayFirst;
	}

TBool& CTicTacToeInfoAndSettings::PlayerFirst()
	{
	return iPlayerFirst;
	}

TBool CTicTacToeInfoAndSettings::PlayerFirst() const
	{
	return iPlayerFirst;
	}
	
void CTicTacToeInfoAndSettings::SetSoundEnabled (TBool aSoundEnabled)
	{
	iSoundEnabled = aSoundEnabled;
	}

TBool& CTicTacToeInfoAndSettings::SoundEnabled()
	{
	return iSoundEnabled;
	}

TBool CTicTacToeInfoAndSettings::SoundEnabled() const
	{
	return iSoundEnabled;
	}

void CTicTacToeInfoAndSettings::AddHumanWins()
	{
	++iHumanWins;
	}

TInt CTicTacToeInfoAndSettings::HumanWins() const
	{
	return iHumanWins;
	}

void CTicTacToeInfoAndSettings::AddHumanLosses()
	{
	++iHumanLosses;
	}

TInt CTicTacToeInfoAndSettings::HumanLosses() const
	{
	return iHumanLosses;
	}
	
void CTicTacToeInfoAndSettings::AddStalemates()
	{
	++iStalemates;
	}
		
TInt CTicTacToeInfoAndSettings::Stalemates() const
	{
	return iStalemates;
	}
	
void CTicTacToeInfoAndSettings::ExternalizeL (RWriteStream& aStream) const
	{
	aStream << iPlayerName;
	aStream.WriteInt32L (iPlayerFirst);
	aStream.WriteInt32L (iSoundEnabled);
	aStream.WriteInt32L (iHumanWins);
	aStream.WriteInt32L (iHumanLosses);
	aStream.WriteInt32L (iStalemates);
	}
		
void CTicTacToeInfoAndSettings::InternalizeL (RReadStream& aStream)
	{
	aStream >> iPlayerName;
	iPlayerFirst = aStream.ReadInt32L();
	iSoundEnabled = aStream.ReadInt32L();
	iHumanWins = aStream.ReadInt32L();
	iHumanLosses = aStream.ReadInt32L();
	iStalemates = aStream.ReadInt32L();
	}

// End of File
