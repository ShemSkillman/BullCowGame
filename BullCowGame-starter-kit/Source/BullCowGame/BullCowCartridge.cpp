// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetUpGame(); 

    // Debug
    // PrintLine(TEXT("The hidden word is: %s"), *HiddenWord);

    GameIntroduction();
}

void UBullCowCartridge::GameIntroduction()
{
    PrintLine(TEXT("Welcome to Bull Cows Game!"));
    PrintLine(TEXT("Guess the %i letter word..."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), PlayerLives);
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
        GameIntroduction();
    }
    else
    {
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You Guessed Correctly!"));
            EndGame();
        }
        else
        {
            --PlayerLives;

            PrintLine(TEXT("Wrong guess... You lost a life!"));

            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("The Hidden Word is %i characters long."), HiddenWord.Len());
            }

            if (PlayerLives > 0)
            {
                PrintLine(TEXT("You have %i lives remaining."), PlayerLives);
            }
            else
            {
                PrintLine(TEXT("GAME OVER - you have no lives remaining!"));
                EndGame();
            }        
        }
    }    

    // Check if isogram + right number of characters
    // If no then subtract life

    // Process bulls and cows to display
    
    // If lives < 1 then print game over + hidden word
    // Prompt to play again
    // Otherwise guess again
}

void UBullCowCartridge::SetUpGame()
{
    HiddenWord = TEXT("greatly");
    PlayerLives = HiddenWord.Len();
    bGameOver = false;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("Press ENTER to play again..."));
}