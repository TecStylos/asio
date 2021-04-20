//
// stoppable_token_callback.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_STOPPABLE_TOKEN_CALLBACK_HPP
#define ASIO_STOPPABLE_TOKEN_CALLBACK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include <stop_token>

#include "asio/detail/push_options.hpp"

namespace asio {

/// The stoppable_token_callback class is a traits class that may be used to determine
/// the callback type associated with a stoppable token.
template <typename T, typename Callback>
struct stoppable_token_callback;

template <typename Callback>
struct stoppable_token_callback<std::stop_token, Callback>
{
  typedef std::stop_callback<Callback> type;
};

} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_STOPPABLE_TOKEN_CALLBACK_HPP
