#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "FTaggedInputAction.generated.h"

/*
キー入力のモデル構造体
今後ファイル移動する
*/
USTRUCT(BlueprintType)
struct ACTION_2_API FTaggedInputAction
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> InputAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (Categories = "Input"))
    FGameplayTag InputTag;
};