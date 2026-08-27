#pragma once

#include <any>
#include "CoreMinimal.h"
#include "IDisposable.h"
#include "URx/URx.h"

namespace UFsm {
    struct FFsmModel {
    public:
        FFsmModel(): CurrentState(nullptr) {
        }

        URx::ReactiveProperty<IDisposable*> CurrentState;
    };

    template <typename TModel>
    concept IFsmModel = std::is_base_of<FFsmModel, TModel>::value;

    /**
     * StateMachine
     * @tparam TModel {FFsmModel} 共有モデル
     * @function Initialize(TModel)
     * @function ChangeState<TState>
     */
    template <IFsmModel TModel>
    class UFsm {
    public:
        class UBaseState : public IDisposable {
        public:
            UBaseState(): IDisposable(), _fsm(nullptr) {
            }

            virtual ~UBaseState() override {
                this->UBaseState::Dispose();
            }

            virtual std::shared_ptr<TModel> GetModel() {
                return this->_fsm->GetModel();
            }

            void SetFsm(UFsm* fsm) {
                this->_fsm = fsm;
            }

            virtual void Setup() {
            }

            virtual void Enter(UBaseState* prevState, std::any& param) {
            }

            virtual void Update(float deltaTime) {
            }

            virtual void Exit() {
            }

            virtual void Dispose() override {
                this->_fsm = nullptr;
            }

        protected:
            UFsm* _fsm;
        };

        template <typename... TStates>
        struct States {
            static TMap<FString, UBaseState*> Map() {
                TMap<FString, UBaseState*> result;
                CreateCore<TStates...>(result);
                return result;
            }

            template <typename First, typename... Rest>
            static void CreateCore(TMap<FString, UBaseState*>& map) {
                // クラス名をキーとして取得
                FString className = typeid(First).name();
                First* newInstance = new First();

                map.Add(className, newInstance);

                if constexpr (sizeof...(Rest) > 0) {
                    CreateCore<Rest...>(map); // 残りのクラスを再帰的に処理
                }
            }
        };

    public:
        UFsm(): _model(nullptr), _stateMap() {
        }

        virtual ~UFsm() {
            this->Dispose();
        }

        template <IFsmModel TModel, typename... TStates>
        void Initialize(std::shared_ptr<TModel> model) {
            this->Dispose();
            this->SetModel(model);
            this->_stateMap = States<TStates...>::Map();
            for (auto& [k, v] : this->_stateMap) {
                v->SetFsm(this);
                v->Setup();
            }
        }

        template <typename TState>
        TState* GetState() {
            static_assert(std::is_base_of_v<UBaseState, TState>, "TState must be derived from TBaseState");
            FString stateName = typeid(TState).name();
            auto find = this->_stateMap.Find(stateName);
            checkf(find, TEXT("Can't find state for %s"), *stateName);
            return static_cast<TState*>(*find);
        }

        UBaseState* GetCurrentState() {
            if (!this->_model || !this->_model->CurrentState.GetValue()) {
                return nullptr;
            }
            return static_cast<UBaseState*>(this->_model->CurrentState.GetValue());
        }

        virtual void SetModel(std::shared_ptr<TModel> model) {
            this->_model = model;
        }
        virtual std::shared_ptr<TModel> GetModel() {
            return this->_model;
        }
        template <typename TState>
        void ChangeState(std::any& param) {
            static_assert(std::is_base_of_v<UBaseState, TState>, "TModel must be derived from TBaseState");
            UBaseState* prevState = this->GetCurrentState();
            if (prevState != nullptr) {
                bool isChanged = false;
                auto obs = this->_model->CurrentState.AsObservable();
                auto sub = obs.Subscribe(
                    [&isChanged](auto _) {
                        isChanged = true;
                    },
                    nullptr, nullptr);
                prevState->Exit();
                sub->Dispose();
                if (isChanged) {
                    return;
                }
            }

            UBaseState* nextState = this->GetState<TState>();
            this->_model->CurrentState.SetValue(nextState);
            nextState->Enter(prevState, param);
        }

        void Update(float deltaTime) {
            UBaseState* currentState = this->GetCurrentState();
            if (!currentState) {
                return;
            }
            currentState->Update(deltaTime);
        }

        void Dispose() {
            for (auto& [k, v] : this->_stateMap) {
                delete v;
            }
            this->_stateMap.Empty();
            this->_model.reset();
        }

    protected:
        std::shared_ptr<TModel> _model;
        TMap<FString, UBaseState*> _stateMap;
    };
}
