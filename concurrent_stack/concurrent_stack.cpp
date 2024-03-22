#include "concurrent_stack.hpp"

namespace concurrent {

    template <typename T>
    void concurrent_stack<T>::push(const T& value) {

        std::unique_lock lock(shd_mutex_);
        data_.push(value);
    }

    template <typename T>
    void concurrent_stack<T>::push(T&& value) {

        std::unique_lock lock(shd_mutex_);
        data_.push(std::forward<T>(value));
    }

    template <typename T>
    std::shared_ptr<T> concurrent_stack<T>::pop() {

        std::unique_lock lock(shd_mutex_);

        if(!data_.empty()) {
            std::shared_ptr<T> stack_top = std::make_shared<T>(data_.top());
            data_.pop();
            return stack_top;
        };
        throw empty_stack_exception();           
    }
}
