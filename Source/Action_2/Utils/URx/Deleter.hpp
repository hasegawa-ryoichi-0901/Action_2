#pragma once

namespace URx
{
    // 関数オブジェクト
    template <class T>
    struct Deleter
    {
        void operator()(T* value)
        {
            value->Dispose();
        }
    };
}
