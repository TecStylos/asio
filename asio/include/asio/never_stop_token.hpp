//
// never_stop_token.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_NEVER_STOP_TOKEN_HPP
#define ASIO_NEVER_STOP_TOKEN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/stoppable_token_callback.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {

class never_stop_token
{
public:
  template <typename Callback>
  struct callback_type
  {
    template <typename C>
    explicit callback_type(never_stop_token, ASIO_MOVE_ARG(C)) ASIO_NOEXCEPT
    {
    }
  };

  static ASIO_CONSTEXPR bool stop_requested() ASIO_NOEXCEPT
  {
    return false;
  }

  static ASIO_CONSTEXPR bool stop_possible() ASIO_NOEXCEPT
  {
    return false;
  }
};

template <typename Callback>
struct stoppable_token_callback<never_stop_token, Callback>
{
  typedef never_stop_token::callback_type<Callback> type;
};

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_NEVER_STOP_TOKEN_HPP
