// Copyright (c) 2013-2021 mogemimi. Distributed under the MIT license.

#pragma once

#include "pomdog/basic/conditional_compilation.hpp"
#include "pomdog/experimental/Reactive/Observable.hpp"
#include "pomdog/experimental/Reactive/Observer.hpp"
#include "pomdog/utility/assert.hpp"

POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_BEGIN
#include <functional>
#include <memory>
#include <utility>
POMDOG_SUPPRESS_WARNINGS_GENERATED_BY_STD_HEADERS_END

namespace Pomdog::Reactive::Detail {

template <class T>
class MergeOperator final
    : public Observer<T>
    , public Observable<T> {
public:
    MergeOperator()
        : isStopped(false)
    {
    }

    void Subscribe(const std::shared_ptr<Observer<T>>& observerIn) override
    {
        POMDOG_ASSERT(observerIn);
        observer = observerIn;
    }

    void OnNext(T value) override
    {
        if (isStopped) {
            return;
        }
        if (observer) {
            observer->OnNext(std::move(value));
        }
    }

    void OnError() override
    {
        if (isStopped) {
            return;
        }
        if (observer) {
            observer->OnError();
        }
        isStopped = true;
    }

    void OnCompleted() override
    {
        if (isStopped) {
            return;
        }
        if (observer) {
            observer->OnCompleted();
        }
        isStopped = true;
    }

private:
    std::shared_ptr<Observer<T>> observer;
    bool isStopped;
};

} // namespace Pomdog::Reactive::Detail