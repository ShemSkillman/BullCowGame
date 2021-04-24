// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 BullCount = 0;
	int32 CowCount = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	public:
	static bool IsIsogram(const FString& Word);

	private:
	void SetUpGame();
	void EndGame();
	void GameIntroduction();
	void ProcessGuess(const FString& Guess);	
	FBullCowCount GetBullsCows(const FString& Guess) const;

	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 PlayerLives;
	bool bGameOver;
	TArray<FString> Isograms;
};