/**
 * @file defer.hpp
 * @author Novichu (https://github.com/Novichu)
 * @brief defer
 * @version 0.1
 * @date 2022-07-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _SRC_COMMON_DEFER_HPP_
#define _SRC_COMMON_DEFER_HPP_

#include <functional>

namespace Novichu {

class defer_invoke_t final {
 public:
  template <typename F>
  requires std::is_invocable_v<F> defer_invoke_t(F&& f)
  noexcept : f_{std::forward<F>(f)} {}
  ~defer_invoke_t() { f_ ? f_() : void(); };
  defer_invoke_t(const defer_invoke_t& other) = delete;
  defer_invoke_t(defer_invoke_t&& other) noexcept : f_{std::move(other.f_)} {};
  defer_invoke_t& operator=(const defer_invoke_t& other) = delete;
  defer_invoke_t& operator=(defer_invoke_t&& other) noexcept {
    f_ = std::move(other.f_);
    return *this;
  };

 private:
  std::function<void()> f_;
};

class defer_maker_t {
 public:
  template <typename F>
  requires std::is_invocable_v<F> defer_invoke_t operator+(F&& f) {
    return defer_invoke_t{std::forward<F>(f)};
  }
};

#define DEFER_CONCAT_NAME(l, r) l##r
#define DEFER_CREATE_NAME(l, r) DEFER_CONCAT_NAME(l, r)
#define defer auto DEFER_CREATE_NAME(defer_, __COUNTER__) = defer_maker_t{} +
#define defer_scope defer[&]

}  // namespace Novichu
#endif  // _SRC_COMMON_DEFER_HPP_
