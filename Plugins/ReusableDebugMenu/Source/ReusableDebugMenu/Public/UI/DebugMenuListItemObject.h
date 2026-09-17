#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DebugMenuTypes.h"
#include "DebugMenuListItemObject.generated.h"

/**
 * @brief UListViewが1つのMenu Nodeを扱うためのUObject Data Adapterです。
 *
 * List Binding用のNode Definitionを保持しますが、Row Widgetの表示や
 * Command実行は所有しません。
 */
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
