#pragma once

#include <vector>

namespace URx {
    template <class T>
    struct IObservable {
    public:
        virtual ~IObservable() = default;
        virtual bool Execute(T value) = 0;
        virtual void Dispose() = 0;
    };

    template <class T>
    class Observable;

    namespace iternal {
    };

    namespace {
        namespace internal // この名前空間内はprivate化される
        {
            template <class T>
            class ObservableWhere : public URx::Observable<T> {
            public:
                virtual bool Execute(T value) override {
                    if (this == nullptr || _cond == nullptr) {
                        return false;
                    }
                    return _cond(value);
                }

                static Observable<T>* Create(TFunction<bool(T)> cond) {
                    return new ObservableWhere(cond);
                }

                ObservableWhere(TFunction<bool(T)> cond): _cond(cond) {
                }

                virtual ~ObservableWhere() override {
                    _cond.Reset();
                }

            protected:
                TFunction<bool(T)> _cond;
            };

            template <class T>
            class ObservableFirst : public URx::Observable<T> {
            public:
                virtual bool Execute(T value) override {
                    if (this == nullptr) {
                        return false;
                    }
                    if (_counter++ == 0) {
                        return true;
                    }
                    return false;
                };

            private:
                ObservableFirst() {
                }

                virtual ~ObservableFirst() override {
                }

                int _counter = 0;
            };

            template <class T>
            class ObservableSkip : public URx::Observable<T> {
            public:
                virtual bool Execute(T value) override {
                    if (this == nullptr) {
                        return false;
                    }
                    if (_counter++ == 0) {
                        return true;
                    }
                    return false;
                };

            private:
                ObservableSkip(int skipCount): _skip(skipCount) {
                }

                virtual ~ObservableSkip() override {
                }

                int _counter = 0;
                int _skip = 0;
            };
        }
    }


    template <class T>
    class Observable : public IObservable<T> {
    public:
        virtual ~Observable() override {

        }

        virtual bool Execute(T value) override {
            return true;
        };

        virtual void Dispose() override {
            delete this;
        };

    public: // Factory
        static Observable* Where(TFunction<bool(T)> cond) {
            return internal::ObservableWhere<T>::Create(cond);
        }

        static Observable* First() {
            return new internal::ObservableFirst<T>();
        }

        static Observable* Skip(int skipCount) {
            return new internal::ObservableSkip<T>(skipCount);
        }
    };

    template <class T>
    class ObservableCollection : public IObservable<T> {
    public:
        ObservableCollection() {
        }

        virtual ~ObservableCollection() override {
        }

        ObservableCollection(TArray<Observable<T>*> observables): _observables(observables) {
        }

        ObservableCollection(Observable<T>* observable) {
            this->Add(observable);
        }

        void Add(Observable<T>* observable) {
            this->_observables.Add(observable);
        }

        void Assign(TArray<Observable<T>*> observables) {
            this->_observables.Append(observables);
        }

        virtual bool Execute(T value) override {
            for (auto observable : this->_observables) {
                if (!observable->Execute(value)) {
                    return false;
                }
            }
            return true;
        }

        virtual void Dispose() override {
            for (auto observable : this->_observables) {
                observable->Dispose();
            }
            this->_observables.Empty();
        };

    protected:
        TArray<Observable<T>*> _observables;
    };
}
