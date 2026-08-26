#pragma once

#include "CoreMinimal.h"
#include "../Debug/EDebugMenuCategory.h"
#include "DebugMenuParam.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct ACTION_2_API FDebugMenuParam
{
	GENERATED_BODY()
public:
	void Setup();
	/* data */
private:
	FDebugMenuParam();
};
