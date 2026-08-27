#pragma once

#include <memory>

class IDisposable {
public:
    virtual void Dispose() = 0;
    virtual ~IDisposable() = default;
};

class CompositeDisposable : public IDisposable {
public:
    CompositeDisposable() = default;
    virtual ~CompositeDisposable() = default;

    void Add(std::shared_ptr<IDisposable> d) {
        this->_disposables.Emplace(d);
    }

    void Remove(std::shared_ptr<IDisposable> d) {
        this->_disposables.Remove(d);
    }

    virtual void Dispose() override {
        for (std::shared_ptr<IDisposable> d : this->_disposables) {
            d->Dispose();
        }
        this->_disposables.Empty();
    }

protected:
    TArray<std::shared_ptr<IDisposable>> _disposables;
};