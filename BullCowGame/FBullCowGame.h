/* The game logic  (no view code or  direct  interaction)
The gamer is a simple guess the word game based on Matermind
*/
#pragma once
#include <string>

// to make syntax Unreal friendly 
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EResetStatus
{
	No_Hidden_Word,
	OK
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString Guess) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString Guess);


	// Please try and igrone  and focis on the interface above.
private:
	// see constrictor for initialisation
	int32 MyCurrentTry = 0;
	FString MyHiddenWord = "";
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};