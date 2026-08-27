#pragma once

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "UFsm.hpp"
#include "Blueprint/UserWidget.h"
#include "UObject/ObjectMacros.h"
#include "UObject/UObjectBaseUtility.h"
#include "UObject/Object.h"
#include "EngineUtils.h"

namespace USam {
    // UObject縛り
    template <typename TViewObject>
    concept IViewObject = std::is_base_of_v<UObject, TViewObject>;

    /**
     * StateActionModel interface
     */
    class ISamContext {
    public:
        virtual void InitializeContext(std::any param) = 0;
        virtual void ChangeToInitializeState(std::any& param) = 0;
        virtual void Update(float deltaTime) = 0;

        template <IViewObject TViewObject>
        TObjectPtr<TViewObject> GetView() {
            return TObjectPtr<TViewObject>(static_cast<TViewObject*>(this->GetView_Impl().Get()));
        };
        virtual TObjectPtr<UObject> GetView_Impl() = 0;

    protected:
    };

    // Model
    struct SamContextModel : public UFsm::FFsmModel {
    public:
        ISamContext* _context;

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<ISamContext, T>>>
        T* GetContext() {
            return (T*)(_context);
        }

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<ISamContext, T>>>
        void SetContext(T* context) {
            this->_context = context;
        }
    };

    // SamContextModel継承縛り
    template <typename TModel>
    concept IFsmModel = std::is_base_of_v<SamContextModel, TModel>;

    // Action
    template <IFsmModel TModel>
    struct USamAction {
    public:
        template <typename TChangeState>
        static void ChangeState(UFsm::UFsm<TModel>* fsm, std::any param = nullptr) {
            fsm->template ChangeState<TChangeState>(param);
        }
        
        void SetContext(ISamContext* context) {
            this->_context = context;
        }
        template <typename TContext, typename = std::enable_if_t<std::is_base_of_v<ISamContext, TContext>>>
        TContext* GetContext() {
            return static_cast<TContext*>(this->_context);
        }
    protected:
        ISamContext* _context;
    };
    /**
     * 何もしないView用
     */
    class UNopView : public UObject {
    public:
        UNopView(const FObjectInitializer& objectInitializer)
            : UObject(objectInitializer) {
        };

        virtual ~UNopView() override {
        };
    };

    /**
     * StateからViewを取得出来るように拡張
     * @tparam TViewObject {IViewObject} View
     * @tparam TModel {SamContextModel} Model
     */
    template <IViewObject TViewObject, IFsmModel TModel>
    class USamBaseState : public UFsm::UFsm<TModel>::UBaseState {
    public:
        FORCEINLINE virtual TObjectPtr<TViewObject> GetView() {
            std::shared_ptr<SamContextModel> model = this->GetModel();
            ISamContext* context = model->GetContext<ISamContext>();
            return context->GetView<TViewObject>();
        }
        virtual ~USamBaseState() override {
            this->_subscriptions.Dispose();
        }
    protected:
        CompositeDisposable _subscriptions;
    };

    /**
     * SAMパターンContext
     * override必須：LoadView, LoadModel
     * @tparam {UObject} TViewObject Model
     * @tparam {FFsmModel} TModel Model
     * @tparam {USamAction} TAction Action
     * @tparam {UBaseState<FFSModel>[]} TStates States
     * @example class SamContext : public USam::USamSwitch<TViewObject, SamModel, SamAction, SamOff, SamOn> { }
     */
    template <IViewObject TViewObject, IFsmModel TModel, typename TAction, typename... TStates>
    class USamContext : public ISamContext {

        using TBaseState = UFsm::UFsm<TModel>::UBaseState;
        static_assert(std::is_base_of_v<USamAction<TModel>, TAction>,
                      "TAction must be derived from USamAction<TModel>");

        template <typename First, typename... Rest>
        struct FirstType {
            static_assert(std::is_base_of_v<USamBaseState<TViewObject, TModel>, First>,
                          "TStates must be derived from USamBaseState<TViewObject, TModel>, First>, Check to USam::USamBaseState<~>")
            ;
            using type = First;
        };

        using TInitialState = typename FirstType<TStates...>::type;

    public:
        USamContext() : _view(), _action(), _fsm() {
        }

        virtual ~USamContext() {
            this->USamContext::DestroyView();
            this->USamContext::ResetModel();
            this->_fsm.Dispose();
        }

        /**
         * Samの持つModelの取得、Stateの初期化
         * @param param  
         */
        virtual void InitializeContext(std::any param = nullptr) override {
            this->ResetModel();
            this->_action.SetContext(this);
            this->_model = this->LoadModel(param);
            this->_model->SetContext(this);
            this->_fsm.template Initialize<TModel, TStates...>(this->_model);
            this->ChangeToInitializeState(param);
        }

        /**
         * フレーム処理が必要ならContextのTickで呼ぶ
         * @param deltaTime
         */
        virtual void Update(float deltaTime) override {
            this->_fsm.Update(deltaTime);
        }

        /**
         * Viewをロードする純粋仮想関数
         * override必須にして、Viewの要/不要に関わらず忘れないように
         * @param param ロード時の何かのパラメータ、TViewObjectを渡してそのままセットしても良い
         * @return {TViewObject*} UObject派生
         */
        virtual TViewObject* LoadView(std::any param) = 0;

    protected:
        TObjectPtr<TViewObject> _view;
        std::shared_ptr<TModel> _model;
        TAction _action;
        UFsm::UFsm<TModel> _fsm;

        virtual void ResetModel() {
            this->_model.reset();
        }

        virtual void SetView(std::any param = nullptr) {
            this->_view = TObjectPtr<TViewObject>(this->LoadView(param));
        }

        virtual TObjectPtr<UObject> GetView_Impl() override {
            return this->_view;
        }

        virtual void DestroyView() {
            if (!IsValid(this->_view)) {
                this->_view = nullptr;
                return;
            }
            // デストラクタで呼ばれるので、自身がviewの場合は破棄不要
            if (this->_view != this) {
                this->_view->ConditionalBeginDestroy();
            }
            this->_view = nullptr;
        }

        /**
         * @param param ロード時の何かのパラメータ、TViewObjectを渡してそのままセットしても良い
         * @return {TModel}
         * @example 内部で生成サンプル
         * virtual std::shared_ptr<TModel> LoadModel(std::any param) override {
         *    return std::make_shared<TModel>();
         * }
         */
        virtual std::shared_ptr<TModel> LoadModel(std::any param) = 0;

        virtual void ChangeToInitializeState(std::any& param) override {
            USamAction<TModel>::template ChangeState<TInitialState>(&this->_fsm, param);
        }

    public:
        /**
         * USam関連のUtils
         */
        struct Utils {
            static ConstructorHelpers::FClassFinder<TViewObject> GetViewClass(const FString& viewPath) {
                ConstructorHelpers::FClassFinder<TViewObject> viewClass(*viewPath);
                return viewClass;
            }
            /**
             * View用ブループリントを渡してparentに追加する
             * @tparam {UWorld|AActor|UActorComponent} TParent 
             * @param parent
             * @param viewClass
             * @return {TViewObject}
            */
            template <typename TParent, typename = std::enable_if_t<std::is_base_of_v<UObject, TParent>>>
            static TViewObject* AddView(TParent* parent, const TSubclassOf<TViewObject> viewClass) {
                checkf(viewClass, TEXT("viewClass"));
                if constexpr (std::is_base_of_v<UUserWidget, TViewObject>) {
                    // ウィジェットのブループリント（BP_MyWidget）を指定
                    // ウィジェットを作成
                    UUserWidget* myWidget = CreateWidget<TViewObject>(parent, viewClass.Class);
                    checkf(myWidget, TEXT("Failed to create UUserWidget instance"));
                    myWidget->AddToViewport(); // 画面に表示
                    return myWidget;
                }
                if constexpr (std::is_base_of_v<AActor, TViewObject>) {
                    // Actor をスポーン
                    TViewObject* spawnedActor = parent->SpawnActor<TViewObject>(viewClass.Class);
                    checkf(spawnedActor, TEXT("Failed to create TViewObject instance"));
                    return spawnedActor;
                }
                if constexpr (std::is_base_of_v<UActorComponent, TViewObject>) {
                    NewObject<TViewObject>(parent, viewClass.Class);
                    // `UActorComponent` をこの `Actor` に追加
                    TViewObject* newComponent = parent->AddComponentByClass(
                        viewClass.Class,
                        true,
                        FTransform::Identity,
                        false);
                    checkf(newComponent, TEXT("Failed to create TViewObject instance"));
                    newComponent->RegisterComponent(); // UE のシステムに登録
                }

                checkf(false, TEXT("Failed type of TViewObject to AddView"));
                return nullptr;
            }
            
            /**
             * View用ブループリントのパスを渡してparentに追加する
             * @tparam {UWorld|AActor|UActorComponent} TParent 
             * @param parent
             * @param viewPath
             * @return {TViewObject}
            */
            template <typename TParent, typename = std::enable_if_t<std::is_base_of_v<UObject, TParent>>>
            static TViewObject* AddView(TParent* parent, const FString& viewPath) {
                ConstructorHelpers::FClassFinder<TViewObject> viewClass = GetViewClass(*viewPath);
                return AddView(parent, viewClass);
            }

            /**
             * WorldにActorを作ってコンポーネントにContextを追加する
             * @tparam {USamContext} TContext 
             * @param world 親
             * @param contextName ラベル名
             * @return {std::tuple<AActor*, TContext*>}
             */
            template <
                typename TContext,
                typename = std::enable_if_t<std::is_base_of_v<USamContext, TContext>>,
                typename = std::enable_if_t<std::is_base_of_v<UActorComponent, TContext>>>
            static std::tuple<AActor*, TContext*> CreateContextComponent(UWorld* world, const FString& contextName) {
                AActor* actor = nullptr;
                for (TActorIterator<AActor> it(world, AActor::StaticClass()); it; ++it) {
                    AActor* itActor = *it;
                    if (!itActor) {
                        continue;
                    }
                    if (contextName == itActor->GetName()) {
                        actor = itActor;
                        break;;
                    }
                }
                if (!actor) {
                    actor = world->SpawnActor<AActor>(
                        FVector::ZeroVector,
                        FRotator::ZeroRotator);
                    actor->SetActorLabel(*contextName);
                }
                for (auto it : actor->GetComponents()) {
                    if (it->GetClass()->GetName() == contextName) {
                        return std::tuple(actor, Cast<TContext*>(it));
                    }
                }
                TContext* context = Cast<TContext*>(actor->AddComponentByClass(
                    TContext::StaticClass(),
                    true,
                    FTransform::Identity,
                    false));
                UActorComponent* component = Cast<UActorComponent>(context);
                component->RegisterComponent();
                return std::tuple(actor, context);
            }
        };
    };
}
