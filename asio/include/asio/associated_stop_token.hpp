//
// associated_stop_token.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_ASSOCIATED_STOP_TOKEN_HPP
#define ASIO_ASSOCIATED_STOP_TOKEN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/config.hpp"
#include "asio/associator.hpp"
#include "asio/detail/type_traits.hpp"
#include "asio/never_stop_token.hpp"

#include "asio/detail/push_options.hpp"

namespace asio {

template <typename T, typename StoppableToken>
struct associated_stop_token;

namespace detail {

template <typename T, typename = void>
struct has_stop_token_type : false_type
{
};

template <typename T>
struct has_stop_token_type<T,
  typename void_type<typename T::stop_token_type>::type>
    : true_type
{
};

template <typename T, typename E, typename = void, typename = void>
struct associated_stop_token_impl
{
  typedef void asio_associated_stop_token_is_unspecialised;

  typedef E type;

  static type get(const T&, const E& e = E()) ASIO_NOEXCEPT
  {
    return e;
  }
};

template <typename T, typename E>
struct associated_stop_token_impl<T, E,
  typename void_type<typename T::stop_token_type>::type>
{
  typedef typename T::stop_token_type type;

  static type get(const T& t, const E& = E()) ASIO_NOEXCEPT
  {
    return t.get_stop_token();
  }
};

template <typename T, typename E>
struct associated_stop_token_impl<T, E,
  typename void_type<
    typename associator<associated_stop_token, T, E>::type
  >::type> : associator<associated_stop_token, T, E>
{
};

} // namespace detail

/// Traits type used to obtain the stop_token associated with an object.
/**
 * A program may specialise this traits type if the @c T template parameter in
 * the specialisation is a user-defined type. The template parameter @c
 * StoppableToken shall be a type meeting the StoppableToken requirements.
 *
 * Specialisations shall meet the following requirements, where @c t is a const
 * reference to an object of type @c T, and @c e is an object of type @c
 * StoppableToken.
 *
 * @li Provide a nested typedef @c type that identifies a type meeting the
 * StoppableToken requirements.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t) and with return type @c type.
 *
 * @li Provide a noexcept static member function named @c get, callable as @c
 * get(t,e) and with return type @c type.
 */
template <typename T, typename StoppableToken = never_stop_token>
struct associated_stop_token
#if !defined(GENERATING_DOCUMENTATION)
  : detail::associated_stop_token_impl<T, StoppableToken>
#endif // !defined(GENERATING_DOCUMENTATION)
{
#if defined(GENERATING_DOCUMENTATION)
  /// If @c T has a nested type @c stop_token_type, <tt>T::stop_token_type</tt>.
  /// Otherwise @c StoppableToken.
  typedef see_below type;

  /// If @c T has a nested type @c stop_token_type, returns
  /// <tt>t.get_stop_token()</tt>. Otherwise returns @c ex.
  static type get(const T& t,
      const StoppableToken& ex = StoppableToken()) ASIO_NOEXCEPT;
#endif // defined(GENERATING_DOCUMENTATION)
};

/// Helper function to obtain an object's associated stop_token.
/**
 * @returns <tt>associated_stop_token<T>::get(t)</tt>
 */
template <typename T>
inline typename associated_stop_token<T>::type
get_associated_stop_token(const T& t) ASIO_NOEXCEPT
{
  return associated_stop_token<T>::get(t);
}

/// Helper function to obtain an object's associated stop_token.
/**
 * @returns <tt>associated_stop_token<T, StoppableToken>::get(t, st)</tt>
 */
template <typename T, typename StoppableToken>
inline typename associated_stop_token<T, StoppableToken>::type
get_associated_stop_token(const T& t, const StoppableToken& st) ASIO_NOEXCEPT
{
  return associated_stop_token<T, StoppableToken>::get(t, st);
}

#if defined(ASIO_HAS_ALIAS_TEMPLATES)

template <typename T, typename StoppableToken = never_stop_token>
using associated_stop_token_t = typename associated_stop_token<T, StoppableToken>::type;

#endif // defined(ASIO_HAS_ALIAS_TEMPLATES)

namespace detail {

template <typename T, typename E, typename = void>
struct associated_stop_token_forwarding_base
{
};

template <typename T, typename E>
struct associated_stop_token_forwarding_base<T, E,
    typename enable_if<
      is_same<
        typename associated_stop_token<T,
          E>::asio_associated_stop_token_is_unspecialised,
        void
      >::value
    >::type>
{
  typedef void asio_associated_stop_token_is_unspecialised;
};

} // namespace detail
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_ASSOCIATED_STOP_TOKEN_HPP
