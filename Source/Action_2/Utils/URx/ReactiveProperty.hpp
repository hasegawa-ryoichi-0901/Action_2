#pragma once

#include "Subject.hpp"

namespace URx {
    /**
     * @class ReactiveProperty
     * @function AsObservable() Subjectを取得して、Subscribe
     */
    template <class T>
    class ReactiveProperty {
    public:
        // 初期値あり
        ReactiveProperty() {
            _subject = new Subject<T>();
        }

        // 初期値あり
        ReactiveProperty(T value) {
            _subject = new Subject<T>();
            _value = value;
        }

        ~ReactiveProperty() {
            if (IsDisposed()) {
                return;
            }
            Dispose();
        }

        inline Subject<T>& AsObservable() const {
            return *this->_subject;
        }

        // //オペレータオーバーロード
        // T operator +=(T value)
        // {
        //     mValue += value;
        //     mSubject->OnNext(mValue);
        //     return mValue;
        // }

        void SetValue(T value) {
            checkf(!IsDisposed(), TEXT("No subject"));

            _value = value;
            _subject->OnNext(_value);
        }

        // 値を取得
        T GetValue() const {
            return _value;
        }

        // 破棄済み
        bool IsDisposed() const {
            return _subject == nullptr;
        }

        // 解放
        void Dispose() {
            if (IsDisposed()) {
                return;
            }
            auto del_subject = _subject;
            _subject = nullptr;
            del_subject->OnCompleted();
            delete del_subject;
        };

    private:
        Subject<T>* _subject;
        T _value;
    };
}
