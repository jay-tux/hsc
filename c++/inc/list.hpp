#ifndef _HSCPP_LIST
#define _HSCPP_LIST

#include "monad.hpp"
#include <optional>
#include <functional>

namespace hscpp {
  template <typename a, typename = void>
  class List : public Monad<List, a> {
  public:
    List() : value{std::nullopt}, next{nullptr} {}
    List(const a value, const List<a> next) : value{value}, next{new List<a>(next)} {}
    List(const List<a> &other) : value{other.value}, next{other.next == nullptr ? nullptr : new List<a>(*other.next)} {}
    List<a> &operator=(const List<a> &other) = delete;

    static List<a> append(const List<a> one, const List<a> other) {
      return one.value ? List(one.value.value(), append(List(*one.next), other)) : other;
    }

    template <typename b>
    List<b> fmap_impl(const std::function<b(a)> f) const {
      if(!value) return List<b>();
      return List<b>(f(value.value()), next->fmap_impl(f));
    }

    template <typename b>
    List<b> ap_impl(const List<std::function<b(a)>> &func) const {
      return func.value ? append(fmap_impl(*func.value), ap_impl(*func.next)) : List<b>();
    }

    template <typename b>
    List<b> bind_impl(const std::function<List<b>(a)> f) const {
      return value ? append(f(*value), next->bind_impl(f)) : List<b>();
    }

    static List<a> pure(a val) { return List<a>(val, List<a>()); }

    ~List() { delete next; }

    const std::optional<a> value;
    const List<a> *next;
  };
}

#endif

/*
data List a = Empty | Cons a (List a)

append :: List a -> List a -> List a
append Empty         l = l
append (Cons a rest) l = Cons a $ rest +++ l

instance Functor List where
  fmap _ Empty         = Empty
  fmap f (Cons a rest) = Cons (f a) $ fmap f rest

instance Applicative List where
  pure a             = Cons a Empty
  ap   Empty       _ = Empty
  ap   (Cons f fs) l = append (fmap f l) $ ap fs l

instance Monad List where
  return a             = Cons a Empty
  bind Empty         _ = Empty
  bind (Cons a rest) f = append (f a) $ bind rest f
*/
