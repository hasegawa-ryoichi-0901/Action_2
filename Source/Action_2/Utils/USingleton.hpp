#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <memory>
#include <mutex>
#include <type_traits>
#include "Engine/Engine.h"

/**
 * UObject継承したクラスをシングルトン化
 * @class USingleton
 * 
 * @example
 * シングルトン化するクラス定義にフレンドクラスとして登録
 * class MySingleton: public UObject {
 *   friend class USingleton<MySingleton, UObject>;
 * @example MySingleton& s = USingleton<MySingleton>::GetInstance()
 */
template <typename T, typename = std::enable_if_t<std::is_base_of_v<UObject, T>>>
class USingleton {
public:
    static T& GetInstance() {
        std::call_once(s_init_instance_flag_, &USingleton::InitSingleton);
        return *s_instance_;
    }

    // コピーコンストラクタと代入演算子を削除
    // USingleton(const USingleton&) = delete;
    // USingleton& operator=(const USingleton&) = delete;

protected:
    USingleton() = default;
    virtual ~USingleton() = default;

private:
    static T* s_instance_;
    static std::once_flag s_init_instance_flag_;

    static void InitSingleton() {
        if (GEngine) {
            FWorldContext* context = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport);
            s_instance_ = Cast<T>(context->OwningGameInstance);
        }
        // s_instance_ = NewObject<T>();
        // check(s_instance_);
        // // ↓ UObjectの基底型の UObjectBaseUtility のメンバー関数
        // s_instance_->AddToRoot();
    }
};

template <typename T, typename U>
T* USingleton<T, U>::s_instance_ = nullptr;

template <typename T, typename U>
std::once_flag USingleton<T, U>::s_init_instance_flag_;
