#pragma once

#include "URx/URx.h"

class ActionButton {
public:
    ActionButton();
    ~ActionButton() {
        this->Dispose();
    };
    
    void Update(bool is_pressed);
    void Dispose();

    URx::Subject<bool>& AsObservable() const {
        return this->pressed_.AsObservable();
    }
private:
    URx::ReactiveProperty<bool> pressed_;

};
