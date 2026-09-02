#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DebugMenuTypes.h"
#include "DebugMenuListItemObject.generated.h"

/** UObject adapter required by UListView. It contains data, never an entry widget. */
UCLASS()
class REUSABLEDEBUGMENU_API UDebugMenuListItemObject : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(const FDebugMenuNodeDefinition& InDefinition)
	{
		Definition = InDefinition;
	}

	const FDebugMenuNodeDefinition& GetDefinition() const { return Definition; }

private:
	UPROPERTY(Transient)
	FDebugMenuNodeDefinition Definition;
};
