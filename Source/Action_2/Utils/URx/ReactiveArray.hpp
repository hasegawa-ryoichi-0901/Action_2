#pragma once

#include "CoreMinimal.h"
#include "Subject.hpp"

namespace URx {
    template <typename T>
    struct ReactiveArrayEventData {
        int32 index;
        T* data;
    };

    template <typename ElementType, typename SizeType = TSizedDefaultAllocator<32>>
    class ReactiveArray {
    public:
        /**
         * Constructor, initializes element number counters.
         */
        ReactiveArray() {
            _arrayPtr = std::make_unique<TArray<ElementType>>();
            _addSubject = new Subject<ReactiveArrayEventData<ElementType>>();
            _removeSubject = new Subject<ReactiveArrayEventData<ElementType>>();
            _clearSubject = new Subject<ReactiveArray<ElementType>*>();
        };

        FORCEINLINE void Push(ElementType& item) {
            checkf(!IsDisposed(), TEXT("ReactiveArray::Push"));

            auto array_index = this->_arrayPtr->Num();
            this->_arrayPtr->Push(item);
            std::unique_ptr<ReactiveArrayEventData<ElementType>> param =
                std::make_unique<ReactiveArrayEventData<ElementType>>();
            param->index = array_index;
            param->data = *item;
            this->_addSubject->OnNext(param);
            param.release();
        }

        FORCEINLINE void Push(const ElementType& item) {
            checkf(!IsDisposed(), TEXT("ReactiveArray::Push"));

            auto array_index = this->_arrayPtr->Num();
            this->_arrayPtr->Push(item);
            std::unique_ptr<ReactiveArrayEventData<ElementType>> param = std::make_unique<ReactiveArrayEventData<
                ElementType>>();
            param->index = array_index;
            param->data = *item;
            this->_addSubject->OnNext(param);
            param.release();
        }

        /**
         * @param item removeItem
         * @return RemoveCount
         */
        SizeType Remove(ElementType& item) {
            checkf(!IsDisposed(), TEXT("ReactiveArray::Remove"));

            auto array_index = this->_arrayPtr->Num();
            const ElementType c_item = item;
            std::unique_ptr<ReactiveArrayEventData<ElementType>> param = std::make_unique<ReactiveArrayEventData<
                ElementType>>();
            int32 remove_count = 0;
            while (SizeType index = this->_arrayPtr->Find(c_item) != INDEX_NONE) {
                this->_arrayPtr->RemoveAt(index);
                param->index = array_index;
                param->data = *item;
                this->_removeSubject->OnNext(param);
                ++remove_count;
            }
            param.release();
            return remove_count;
        }

        /**
         * @param item removeItem
         * @return RemoveCount
         */
        SizeType Remove(const ElementType& item) {
            checkf(!IsDisposed(), TEXT("ReactiveArray::Remove"));

            auto array_index = this->_arrayPtr->Num();
            std::unique_ptr<ReactiveArrayEventData<ElementType>> param = std::make_unique<ReactiveArrayEventData<
                ElementType>>();
            int32 remove_count = 0;
            while (SizeType index = this->_arrayPtr->Find(item) != INDEX_NONE) {
                this->_arrayPtr->RemoveAt(index);
                param->index = array_index;
                param->data = *item;
                this->_removeSubject->OnNext(param);
                ++remove_count;
            }
            param.release();
            return remove_count;
        }

        void Clear() {
            checkf(!IsDisposed(), TEXT("ReactiveArray::Clear"));

            this->_arrayPtr->Clear();
            this->_clearSubject->OnNext(this);
        }

        bool IsDisposed() const { return _arrayPtr == nullptr; }
        // 解放
        void Dispose() {
            if (IsDisposed()) {
                UE_LOG(LogBlueprint, Error, TEXT("ReactiveArray::Disposed"));
                return;
            }
            _addSubject->OnCompleted();
            _removeSubject->OnCompleted();
            _clearSubject->OnCompleted();
            _arrayPtr.release();
            _addSubject = nullptr;
            _removeSubject = nullptr;
            _clearSubject = nullptr;
            _arrayPtr = nullptr;
            delete this;
        }

        Subject<ReactiveArrayEventData<ElementType>>& OnAddAsObservable() const {
            return _addSubject->AsObservable();
        }
        Subject<ReactiveArrayEventData<ElementType>>& OnRemoveAsObservable() const {
            return _removeSubject->AsObservable();
        }
        Subject<ReactiveArray<ElementType>*>& OnClearAsObservable() const {
            return _clearSubject->AsObservable();
        }

    private:
        std::unique_ptr<TArray<ElementType>> _arrayPtr;
        Subject<ReactiveArrayEventData<ElementType>>* _addSubject;
        Subject<ReactiveArrayEventData<ElementType>>* _removeSubject;
        Subject<ReactiveArray<ElementType>*>* _clearSubject;

        ~ReactiveArray() {
        };
    };
}
