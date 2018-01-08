/* This is the console excutalbe, that makes use of theBullCow class
This  actis as the view in  a MVC pattern, and is responible for all 
user interaction. For game logic see the FBullComGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly 
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, wich we re-use across plays

// the entry point for our application
int32 main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0; // exit the application
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	 
	// loop asking  for guesses while the game 
	// us NOT won and there are still trues remaining
	while(!BCGame.IsGameWon() &&  BCGame.GetCurrentTry() <= MaxTries)
	{

		FText Guess = GetValidGuess();  

		// Submit valid guess to the game , and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
	}
 
	PrintGameSummary();
	return;

}

// introduce the game
void PrintIntro()
{
		constexpr int32 WORLD_LENGTH = 9;
		std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
		std::cout << "Can  you guess the " << BCGame.GetHiddenWordLength();
		std::cout << " letter isgrem I'm thinking of ?\n";
		std::cout << std::endl;
		return;
}

// loop continually until the user glves a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			return Guess;
			break;
		}
		std::cout << std::endl; 
	} while (Status == EGuessStatus::OK);  // keep looping untile we no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)?";
	FText Response = "";
	std::getline(std::cin, Response);
 
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {

		std::cout << "WELL DONE - YOU WON!\n";
	}
	else
	{
		std::cout << "Better lunch next time!\n";
	}
}