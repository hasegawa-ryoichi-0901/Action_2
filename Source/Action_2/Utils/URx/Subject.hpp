#pragma once

#include <iostream>
#include "../Utils/IDisposable.h"
#include "Observable.hpp"

namespace URx {
    template <class T>
    class SubjectItem final : public IDisposable {
    public:
        TFunction<void(T value)> onNextFunc;
        TFunction<void()> onCompleteFunc;
        TFunction<void(std::exception& e)> onErrorFunc;

        ObservableCollection<T> conditionFunc;

        virtual ~SubjectItem() override {
            this->Dispose();
        }

        virtual void Dispose() override {
            onNextFunc.Reset();
            onCompleteFunc.Reset();
            onErrorFunc.Reset();
            conditionFunc.Dispose();
        }
    };


    /**
     * イベント発火用クラス
     * @class Subject
     * @function Subscribe ラムダ用Subscribe
     * @function SubscribeIf 条件付きラムダ用Subscribe
     * @function SubscribeOn メンバ関数呼び出し用Subscribe
     * @function SubscribeOnIf 条件付きメンバ関数呼び出し用Subscribe
     */
    template <class T>
    class Subject {
    public:
        Subject() {
        };

        virtual ~Subject() {
        };

        void Dispose() {
            for (auto function : _functions) {
                function->Dispose();
            }
            _functions.Empty();
        }

        //受け取った値を登録されている関数に渡して実行
        virtual void OnNext(T value);
        //正常終了処理
        virtual void OnCompleted();
        //異常終了処理
        virtual void OnError(std::exception& e);

        ///
        /// @tparam O {class/struct}
        /// @tparam N {TFunction<void(T)>*}
        /// @param obj 呼び出すオブジェクト
        /// @param memNextFunc 呼び出されるメソッド
        /// @return
        /// @example subject->SubscribeOn(this, &CallClass::OnEvent);
        template <typename O, typename N>
        inline std::shared_ptr<SubjectItem<T>> SubscribeOn(
            O* obj,
            N memNextFunc) {
            checkf(obj, TEXT("obj is nullptr"));
            TFunction<void(T)> next = [obj, memNextFunc](T v) -> void {
                (obj->*memNextFunc)(v);
            };
            return Subscribe(next, nullptr, nullptr);
        }

        ///
        /// @tparam O {class/struct}
        /// @tparam N {TFunction<void(T)>*}
        /// @param obj 呼び出すオブジェクト
        /// @param condFunc OnNextで呼び出される条件式ラムダ
        /// @param memNextFunc OnNextで呼び出されるメソッド
        /// @return
        /// @example subject->SubscribeOn(this, [this](T v){ return true; }, &CallClass::OnEvent);
        template <typename O, typename N>
        inline std::shared_ptr<SubjectItem<T>> SubscribeOn(
            TFunction<bool(T)> condFunc,
            O* obj,
            N memNextFunc) {
            checkf(obj, TEXT("obj is nullptr"));
            TFunction<void(T)> next = [obj, memNextFunc](T v) -> void {
                (obj->*memNextFunc)(v);
            };
            return SubscribeIf(condFunc, next);
        }

        ///
        /// @tparam O {class/struct}
        /// @tparam N {O::TFunction<void(T)>*}
        /// @tparam COND {O::TFunction<bool(T)>*}
        /// @param obj 呼び出すオブジェクト
        /// @param memCondFunc OnNextで呼び出される条件式メソッド
        /// @param memNextFunc OnNextで呼び出されるメソッド
        /// @return
        /// @example subject->SubscribeOn(this, &CallClass::OnEvent);
        template <typename O, typename N, typename COND>
        inline std::shared_ptr<SubjectItem<T>> SubscribeOnIf(
            O* obj,
            COND memCondFunc,
            N memNextFunc) {
            checkf(obj, TEXT("obj is nullptr"));
            TFunction<void(T)> next = [obj, memNextFunc](T v) -> void {
                (obj->*memNextFunc)(v);
            };
            TFunction<bool(T)> cond = [obj, memCondFunc](T v) -> bool {
                return (obj->*memCondFunc)(v);
            };
            return SubscribeIf(cond, next);
        }

        ///
        /// @tparam O {class/struct}
        /// @tparam N {TFunction<void(T)>*}
        /// @tparam C {TFunction<void()>*}
        /// @param obj 呼び出すオブジェクト
        /// @param memNextFunc OnNextで呼び出されるメソッド
        /// @param memCompFunc OnCompleteで呼び出されるメソッド
        /// @return
        /// @example subject->SubscribeOn(this, &CallClass::OnEvent);
        template <typename O, typename N, typename C>
        inline std::shared_ptr<SubjectItem<T>> SubscribeOn(
            O* obj,
            N memNextFunc,
            C memCompFunc) {
            checkf(obj, TEXT("obj is nullptr"));
            TFunction<void(T)> next = [obj, memNextFunc](T v) -> void {
                (obj->*memNextFunc)(v);
            };
            TFunction<void()> comp = [obj, memCompFunc]() -> void {
                (obj->*memCompFunc)();
            };
            return Subscribe(next, comp, nullptr);
        }

        ///
        /// @tparam O {class/struct}
        /// @tparam N {TFunction<void(T)>*}
        /// @tparam C {TFunction<void()>*}
        /// @tparam COND {O::TFunction<bool(T)>*}
        /// @param obj 呼び出すオブジェクト
        /// @param memCondFunc OnNextで呼び出される条件式メソッド
        /// @param memNextFunc OnNextで呼び出されるメソッド
        /// @param memCompFunc OnCompleteで呼び出されるメソッド
        /// @return
        /// @example subject->SubscribeOnIf(this, &CallClass::Condition, &CallClass::OnEvent, &CallClass::OnComplete);
        template <typename O, typename N, typename C, typename COND>
        inline std::shared_ptr<SubjectItem<T>> SubscribeOnIf(
            O* obj,
            COND memCondFunc,
            N memNextFunc,
            C memCompFunc) {
            checkf(obj, TEXT("obj is nullptr"));
            TFunction<void(T)> next = [obj, memNextFunc](T v) -> void {
                (obj->*memNextFunc)(v);
            };
            TFunction<void()> comp = [obj, memCompFunc]() -> void {
                (obj->*memCompFunc)();
            };
            TFunction<bool(T)> cond = [obj, memCondFunc](T v) -> bool {
                return (obj->*memCondFunc)(v);
            };
            return SubscribeIf(cond, next, comp);
        }

        ///
        /// @tparam O {class/struct}
        /// @tparam N {TFunction<void(T)>*}
        /// @tparam C {TFunction<void()>*}
        /// @param condFunc OnNextで呼び出される条件式ラムダ
        /// @param obj 呼び出すオブジェクト
        /// @param memNextFunc OnNextで呼び出されるメソッド
        /// @param memCompFunc OnCompleteで呼び出されるメソッド
        /// @return
        /// @example subject->SubscribeOnIf(this, [this](T v) { return true; }, &CallClass::OnComplete);
        template <typename O, typename N, typename C>
        inline std::shared_ptr<SubjectItem<T>> SubscribeOnIf(
            TFunction<bool(T)> condFunc,
            O* obj,
            N memNextFunc,
            C memCompFunc) {
            checkf(obj, TEXT("obj is nullptr"));
            TFunction<void(T)> next = [obj, memNextFunc](T v) -> void {
                (obj->*memNextFunc)(v);
            };
            TFunction<void()> comp = [obj, memCompFunc]() -> void {
                (obj->*memCompFunc)();
            };
            return SubscribeIf(condFunc, next, comp);
        }
        ///
        /// @tparam O {class/struct}
        /// @tparam N {TFunction<void(T)>*}
        /// @tparam C {TFunction<void()>*}
        /// @tparam E {TFunction<void(std::exception)>*}
        /// @param obj 呼び出すオブジェクト
        /// @param memNextFunc OnNextで呼び出されるメソッド
        /// @param memCompFunc OnCompleteで呼び出されるメソッド
        /// @param memErrFunc OnErrorで呼び出されるメソッド
        /// @return
        /// @example subject->SubscribeOnIf(this, [this](T v) { return true; }, &CallClass::OnComplete, &CallClass::OnError);
        template <typename O, typename N, typename C, typename E>
        inline std::shared_ptr<SubjectItem<T>> SubscribeOn(
            O* obj,
            N memNextFunc,
            C memCompFunc,
            E memErrFunc) {
            checkf(obj, TEXT("obj is nullptr"));
            TFunction<void(T)> next = [obj, memNextFunc](T v) -> void {
                (obj->*memNextFunc)(v);
            };
            TFunction<void()> comp = [obj, memCompFunc]() -> void {
                (obj->*memCompFunc)();
            };
            TFunction<void(std::exception&)> err = [obj, memErrFunc](std::exception& e) -> void {
                (obj->*memErrFunc)(e);
            };
            return Subscribe(next, comp, err);
        }

        ///
        /// @tparam O {class/struct}
        /// @tparam N {TFunction<void(T)>*}
        /// @tparam C {TFunction<void()>*}
        /// @tparam E {TFunction<void(std::exception)>*}
        /// @tparam COND {O::TFunction<bool(T)>*}
        /// @param obj 呼び出すオブジェクト
        /// @param memCondFunc OnNextで呼び出される条件式メソッド
        /// @param memNextFunc OnNextで呼び出されるメソッド
        /// @param memCompFunc OnCompleteで呼び出されるメソッド
        /// @param memErrFunc OnErrorで呼び出されるメソッド
        /// @return
        /// @example subject->SubscribeOnIf(this, &CallClass::Condition, &CallClass::OnComplete, &CallClass::OnError);
        template <typename O, typename N, typename C, typename E, typename COND>
        inline std::shared_ptr<SubjectItem<T>> SubscribeOnIf(
            O* obj,
            COND memCondFunc,
            N memNextFunc,
            C memCompFunc,
            E memErrFunc) {
            checkf(obj, TEXT("obj is nullptr"));
            TFunction<void(T)> next = [obj, memNextFunc](T v) -> void {
                (obj->*memNextFunc)(v);
            };
            TFunction<void()> comp = [obj, memCompFunc]() -> void {
                (obj->*memCompFunc)();
            };
            TFunction<void(std::exception&)> err = [obj, memErrFunc](std::exception& e) -> void {
                (obj->*memErrFunc)(e);
            };
            TFunction<bool(T)> cond = [obj, memCondFunc](T v) -> bool {
                return (obj->*memCondFunc)(v);
            };
            return SubscribeIf(cond, next, comp, err);
        }

        ///
        /// @tparam O {class/struct}
        /// @tparam N {TFunction<void(T)>*}
        /// @tparam C {TFunction<void()>*}
        /// @tparam E {TFunction<void(std::exception)>*}
        /// @param condFunc {TFunction<bool(T)>} OnNextで呼び出される条件式メソッド
        /// @param obj 呼び出すオブジェクト
        /// @param memNextFunc OnNextで呼び出されるメソッド
        /// @param memCompFunc OnCompleteで呼び出されるメソッド
        /// @param memErrFunc OnErrorで呼び出されるメソッド
        /// @return
        /// @example subject->SubscribeOnIf([this](T v) { return true; }, this, &CallClass::OnComplete, &CallClass::OnError);
        template <typename O, typename N, typename C, typename E>
        inline std::shared_ptr<SubjectItem<T>> SubscribeOnIf(
            TFunction<bool(T)> condFunc,
            O* obj,
            N memNextFunc,
            C memCompFunc = nullptr,
            E memErrFunc = nullptr) {
            checkf(obj, TEXT("obj is nullptr"));

            TFunction<void(T)> next = [obj, memNextFunc](T v) -> void {
                (obj->*memNextFunc)(v);
            };
            TFunction<void()> comp = [obj, memCompFunc]() -> void {
                (obj->*memCompFunc)();
            };
            TFunction<void(std::exception&)> err = [obj, memErrFunc](std::exception& e) -> void {
                (obj->*memErrFunc)(e);
            };
            return SubscribeIf(condFunc, next, comp, err);
        }
        ///
        /// @param next {TFunction<void(T)>} OnNextで呼び出されるラムダ
        /// @param completed {TFunction<void()>} OnCompleteで呼び出されるラムダ
        /// @param error {TFunction<void(std::exception)>} OnErrorで呼び出されるラムダ
        /// @return
        /// @example subject->Subscribe([this](T v) { // }, [this]() { // }, [this](std::exception e) { // });
        std::shared_ptr<SubjectItem<T>> Subscribe(TFunction<void(T value)> next,
                                  TFunction<void()> completed = nullptr,
                                  TFunction<void(std::exception& e)> error = nullptr);

        ///
        /// @param condition {TFunction<bool(T)>} OnNextで呼び出されるラムダ
        /// @param next {TFunction<void(T)>} OnNextで呼び出されるラムダ
        /// @param completed {TFunction<void()>} OnCompleteで呼び出されるラムダ
        /// @param error {TFunction<void(std::exception)>} OnErrorで呼び出されるラムダ
        /// @return
        /// @example subject->Subscribe([this](T v) { return true; }, [this](T v) { // }, [this]() { // }, [this](std::exception e) { // });
        std::shared_ptr<SubjectItem<T>> SubscribeIf(
            TFunction<bool(T)> condition,
            TFunction<void(T value)> next,
            TFunction<void()> completed = nullptr,
            TFunction<void(std::exception& e)> error = nullptr);

        ///
        /// @param conditions {TArray<IObservable<T>*>} OnNextで呼び出されるObservable配列
        /// @param next {TFunction<void(T)>} OnNextで呼び出されるラムダ
        /// @param completed {TFunction<void()>} OnCompleteで呼び出されるラムダ
        /// @param error {TFunction<void(std::exception)>} OnErrorで呼び出されるラムダ
        /// @return
        /// @example subject->SubscribeIf({IObservable::Where([this](T v){ return true; }}, [this](T v) { // }, [this]() { // }, [this](std::exception e) { // });
        std::shared_ptr<SubjectItem<T>> SubscribeIf(
            TArray<IObservable<T>*> conditions,
            TFunction<void(T value)> next,
            TFunction<void()> completed = nullptr,
            TFunction<void(std::exception& e)> error = nullptr);

    private:
        TArray<std::shared_ptr<SubjectItem<T>>> _functions;
    };

    template <class T>
    inline void Subject<T>::OnNext(T value) {
        for (auto i = _functions.Num() - 1; i >= 0; --i) {
            if (_functions[i]->onNextFunc) {
                if (_functions[i]->conditionFunc.Execute(value)) {
                    _functions[i]->onNextFunc(value);
                }
            } else {
                _functions[i]->Dispose();
                _functions.RemoveAt(i, EAllowShrinking::No);
            }
        }
    }

    template <class T>
    inline void Subject<T>::OnCompleted() {
        for (auto function : _functions) {
            if (function->onCompleteFunc) {
                function->onCompleteFunc();
            }
        }
        this->Dispose();
    }

    template <class T>
    inline void Subject<T>::OnError(std::exception& e) {
        for (auto function : _functions) {
            if (function->onErrorFunc) {
                function->onErrorFunc(e);
            }
        }
        delete this;
    }

    template <class T>
    std::shared_ptr<SubjectItem<T>> Subject<T>::Subscribe(
        TFunction<void(T value)> next,
        TFunction<void()> completed,
        TFunction<void(std::exception& e)> error) {

        std::shared_ptr<SubjectItem<T>> item = std::make_shared<SubjectItem<T>>();
        item->onNextFunc = next;
        item->onCompleteFunc = completed;
        item->onErrorFunc = error;
        _functions.Add(item);
        return item;
    }

    template <class T>
    std::shared_ptr<SubjectItem<T>> Subject<T>::SubscribeIf(
        TFunction<bool(T)> condition,
        TFunction<void(T value)> next,
        TFunction<void()> completed,
        TFunction<void(std::exception& e)> error) {

        std::shared_ptr<SubjectItem<T>> item = std::make_shared<SubjectItem<T>>();
        item->onNextFunc = next;
        item->onCompleteFunc = completed;
        item->onErrorFunc = error;
        item->conditionFunc.Add(Observable<T>::Where(condition));
        _functions.Add(item);
        return item;
    }

    ///
    /// @example SubscribeIf(std::vector(Observable::Where(`
    /// @param conditions
    /// @param next
    /// @param completed
    /// @param error
    /// @return
    template <class T>
    std::shared_ptr<SubjectItem<T>> Subject<T>::SubscribeIf(
        TArray<IObservable<T>*> conditions,
        TFunction<void(T value)> next,
        TFunction<void()> completed,
        TFunction<void(std::exception& e)> error) {

        std::shared_ptr<SubjectItem<T>> item = std::make_shared<SubjectItem<T>>();
        item->onNextFunc = next;
        item->onCompleteFunc = completed;
        item->onErrorFunc = error;
        item->conditionFunc.Assign(conditions);
        _functions.Add(item);
        return item;
    }

}
