#pragma once


#include "CoreMinimal.h"
#include <concepts>
#include <iostream>

template <typename TO>
concept Integral = std::is_integral_v<TO>;

class GameUtils {
public:
    template <typename T>
    static T* FindObjectByName(TArray<T*> array, FName name)
        requires std::is_base_of_v<UObject, T> {

        for (T* o : array) {
            if (name == o->GetName()) {
                return o;
            }
        }
        return nullptr;
    }
    template <typename T>
    static TObjectPtr<T> FindObjectByName(TArray<TObjectPtr<T>> array, FName name)
        requires std::is_base_of_v<UObject, T> {

        for (T* o : array) {
            if (name == o->GetName()) {
                return o;
            }
        }
        return nullptr;
    }

    template <typename T, typename TR>
    static TArray<TR*> CastObjects(TArray<T*> array)
        requires std::is_base_of_v<UObject, T> && std::is_base_of_v<UObject, TR> {

        TArray<TR*> results;
        for (auto v : array) {
            if (v->IsA<TR>()) {
                results.Emplace(static_cast<TR*>(v));
            }
        }
        return results;
    }
};
