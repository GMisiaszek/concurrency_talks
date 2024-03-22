#pragma once
#include <stack>
#include <shared_mutex>
#include <memory>
#include <exception>

namespace concurrent {

    class empty_stack_exception: public std::exception {

            virtual const char* what() const throw() {

            return "Empty stack exception";
        
            }
    };

    template <typename T>
    class concurrent_stack {

        std::stack<T> data_;
        mutable std::shared_mutex shd_mutex_;

        public:
            concurrent_stack(std::stack<T> in_data) : data_(in_data) {};

            void push(const T& value);
            void push(T&& value);

            std::shared_ptr<T> pop();
            void modify_top(const T& value);
            void modify_top(T&& value);

            concurrent_stack<T>& operator=(const concurrent_stack<T>&) = delete;

    };

}