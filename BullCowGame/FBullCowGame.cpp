#pragma once
#include "FBullCowGame.h"
#include  <map>

// to make syntax Unreal  friendly 
#define TMap std::map; 

using int32 = int;
FBullCowGame::FBullCowGame(){ Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	std::map<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	//constexpr int32 MAX_TRIES = 8;
	const FString HIDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram;   
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if(Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
 
}

// receive a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	// incriment the return number
	MyCurrentTry++;

	// setup a return valiable
	FBullCowCount BullCowCount;
	 
	
	int32 WordLength = GetHiddenWordLength();
	int32 GuessLength = Guess.length();
	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++){
		// compare letters against the guess
		for (int32 GChar = 0; GChar < GuessLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				// if they're in the same place
				if (MHWChar == GChar){
					
					BullCowCount.Bulls++; // incriment bulls
				}else {
					BullCowCount.Cows++; // incriment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isgrams
	if (Word.length() <= 1) { return true;  }

	std::map<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word)  // for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		if(LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do NOT have an isogram
		}else{
			// add the letter to the map as seen
			LetterSeen[Letter] = true;
		}
	
	}

	return true; // for example in case where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter)) // if not a lowercase letter
		{
			return false;
		}
		
	}
	return true;
}
