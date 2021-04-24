// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");

    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, 
    [](const FString& Word)
    { 
        return Word.Len() >= 3 && Word.Len() <= 8 && IsIsogram(Word);
    });

    SetUpGame();

    GameIntroduction();
}

void UBullCowCartridge::SetUpGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    PlayerLives = FGenericPlatformMath::RoundToInt(HiddenWord.Len() * 2.5);
    bGameOver = false;
}

void UBullCowCartridge::GameIntroduction()
{
    PrintLine(TEXT("Welcome to Bull Cows Game!"));
    PrintLine(TEXT("Guess the %i letter word..."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), PlayerLives);
    
    // Debug
    //PrintLine(TEXT("The hidden word is: %s"), *HiddenWord);
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
        GameIntroduction();
        return;
    }
    
    ProcessGuess(PlayerInput);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("\nPress ENTER to play again..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You Guessed Correctly!"));
        EndGame();
        return;
    }
    
    --PlayerLives;

    PrintLine(TEXT("Wrong guess... You lost a life!"));

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("The word has NO repeating letters!"));
    }    
    else if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i characters long."), HiddenWord.Len());
    }
    else
    {
        FBullCowCount Counter = GetBullsCows(Guess);
        PrintLine(TEXT("You have %i Bulls and %i Cows."), Counter.BullCount, Counter.CowCount);
    }
    
    if (PlayerLives > 0)
    {
        PrintLine(TEXT("You have %i lives remaining."), PlayerLives);
    }
    else
    {
        ClearScreen();
        PrintLine(TEXT("GAME OVER - you have no lives remaining!"));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
        EndGame();
    }    
}

bool UBullCowCartridge::IsIsogram(const FString& Word)
{
   for (int32 i = 0; i < Word.Len() - 1; i++)
   {
       for (int32 j = i + 1; j < Word.Len(); j++)
       {
           if (Word[i] == Word[j])
           {
               return false;
           }
       }
   }

    return true;
}

FBullCowCount UBullCowCartridge::GetBullsCows(const FString& Guess) const
{
    FBullCowCount Counter;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Counter.BullCount++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Counter.CowCount++;
                break;
            }
        }
    }

    return Counter;
}