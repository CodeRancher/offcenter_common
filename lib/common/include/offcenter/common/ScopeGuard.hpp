/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an  BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   ScopeGuard.hpp
 * @author Scott Brauer
 * @date   01-28-2019
 */

#ifndef SCOPEGUARD_HPP
#define SCOPEGUARD_HPP

//***************************************************************************
// https://stackoverflow.com/questions/10270328/the-simplest-and-neatest-c11-scopeguard
//
// scope_guard scope_exit, scope_fail(scope_guard::execution::exception);
//
// action1();
// scope_exit += [](){ cleanup1(); };
// scope_fail += [](){ rollback1(); };
//
// action2();
// scope_exit += [](){ cleanup2(); };
// scope_fail += [](){ rollback2(); };
//
//***************************************************************************

#include <functional>
#include <deque>

class ScopeGuard {
public:
    enum execution { always, no_exception, exception };

    ScopeGuard(ScopeGuard &&) = default;
    explicit ScopeGuard(execution policy = always) : policy(policy) {}

    template<class Callable>
    ScopeGuard(Callable && func, execution policy = always) : policy(policy) {
        this->operator += <Callable>(std::forward<Callable>(func));
    }

    template<class Callable>
    ScopeGuard& operator += (Callable && func) try {
        handlers.emplace_front(std::forward<Callable>(func));
        return *this;
    } catch(...) {
        if(policy != no_exception) func();
        throw;
    }

    ~ScopeGuard() {
        if(policy == always || (std::uncaught_exception() == (policy == exception))) {
            for(auto &f : handlers) try {
                f(); // must not throw
            } catch(...) { /* std::terminate(); ? */ }
        }
    }

    void dismiss() noexcept {
        handlers.clear();
    }

private:
    ScopeGuard(const ScopeGuard&) = delete;
    void operator = (const ScopeGuard&) = delete;

    std::deque<std::function<void()>> handlers;
    execution policy = always;
};
#endif // SCOPEGUARD_HPP
