#include "ActionButton.h"

ActionButton::ActionButton() {
    this->pressed_.SetValue(false);
}

void ActionButton::Dispose() {
    if (this->pressed_.IsDisposed()) {
        return;
    }
    this->pressed_.Dispose();
}

void ActionButton::Update(bool is_pressed) {
    auto is_changed = this->pressed_.GetValue() != is_pressed;
    if (!is_changed) {
        return;
    }
    this->pressed_.SetValue(is_pressed);
}
