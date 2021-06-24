# HSC - C++ documentation
*Documentation to go along with the header files (`hpp` files) in the `inc/` directory.*  
**Everything is in the `hscpp` namespace, and all headers can be included at once using `#include <hsc/hscpp>`.**

## Quick links
 - [Quick links](./docs.md#quick-links)
 - [Types](./docs.md#types)
   - [Basic data type wrappers](./docs.md#basic-data-type-wrappers)
   - [Monadic types](./docs.md#monadic-types)
     - [List types](./docs.md#list-types)
 - [Type classes](./docs.md#type-classes)
 - [Free functions](./docs.md#free-functions)

## Types
### Basic data type wrappers
*`struct hsInt`:* ![types.hpp]
- Constructors:
 - `hsInt(int value)`: wraps an `int`.
- Member functions: none
- Member fields:
 - `int value`: the wrapped value.
- Member types: none
- Static functions: none
- Operators:
 - `hsInt &operator=(int v)`: changes the wrapped value [candidate for removal].
 - `operator int() const`: extracts the wrapped value.

*`struct hsInteger`:* ![types.hpp]
- Constructors:
  - `hsInt(long value)`: wraps a `long`.
- Member functions: none
- Member fields:
  - `long value`: the wrapped value.
- Member types: none
- Static functions: none
- Operators:
  - `hsInteger &operator=(long v)`: changes the wrapped value [candidate for removal].
  - `operator long() const`: extracts the wrapped value.

*`struct hsBool`:* ![types.hpp]
- Constructors:
 - `hsBool(bool value)`: wraps a `bool`.
- Member functions: none
- Member fields:
 - `bool value`: the wrapped value.
- Member types: none
- Static functions: none
- Operators:
 - `hsBool &operator=(bool v)`: changes the wrapped value [candidate for removal].
 - `operator bool() const`: extracts the wrapped value.

*`struct hsFloat`:* ![types.hpp]
- Constructors:
  - `hsFloat(float value)`: wraps a `float`.
- Member functions: none
- Member fields:
  - `float value`: the wrapped value.
- Member types: none
- Static functions: none
- Operators:
  - `hsFloat &operator=(float v)`: changes the wrapped value [candidate for removal].
  - `operator float() const`: extracts the wrapped value.

*`struct hsDouble`:* ![types.hpp]
- Constructors:
  - `hsDouble(double value)`: wraps a `double`.
- Member functions: none
- Member fields:
  - `double value`: the wrapped value.
- Member types: none
- Static functions: none
- Operators:
  - `hsDouble &operator=(double v)`: changes the wrapped value [candidate for removal].
  - `operator double() const`: extracts the wrapped value.

*`struct hsChar`:* ![types.hpp]
- Constructors:
  - `hsChar(char value)`: wraps a `char`.
- Member functions: none
- Member fields:
  - `char value`: the wrapped value.
- Member types: none
- Static functions: none
- Operators:
  - `hsChar &operator=(char v)`: changes the wrapped value [candidate for removal].
  - `operator char() const`: extracts the wrapped value.

### Monadic types
*`class Maybe : public Monad<Maybe, a>`* (monadic maybe/std::optional type) ![maybe.hpp]
- Constructors:
  - `Maybe()`: constructs a `Maybe` without value (equivalent to Haskell's `Nothing`).
  - `Maybe(const a value)`: constructs a `Maybe` with the given value (equivalent to Haskell's `Just`).
- Member functions:
  - `Maybe<b> fmap_impl(const std::function<b(a)> f) const`: if there is a value, applies the function to it (requirement from `Functor<Maybe, a>`).
  - `Maybe<b> ap_impl(const Maybe<std::function<b(a)>> &func) const`: if there is a function given, `fmap` that function over this `Maybe` (requirement from `Applicative<Maybe, a>`).
  - `Maybe<b> bind_impl(const std::function<Maybe<b>(a)> f) const`: if there is a value, returns the function's return value (requirement from `Monad<Maybe, a>`).
- Member fields:
  - `const std::optional<a> value`: the value, if any.
- Member types: none
- Static functions:
  - `static Maybe<a> pure(a val)`: wraps the given value in a `Maybe` (requirement from `Applicative<Maybe, a>`).
- Alternative version: `class Maybe : public Monad<Maybe, a>, public Show` when `std::enable_if_t<std::is_base_of_v<Show, a>>`
  - `hsString show() const override`: converts this `Maybe` value to a string representation.

*`class Either : public Monad<Either, a, e>`:* (monadic either/union type) ![either.hpp]
- Constructors:
  - `Either(a value)`: initialize with the "success" value (equivalent to Haskell's `Right`).
  - `Either(e error)`: initialize with the "error" value (equivalent to Haskell's `Left`).
  - `Either(const Either<a, e> &other)`: copy another `Either<a, e>` value.
- Member functions:
  - `Either<b, e> fmap_impl(const std::function<b(a)> f) const`: if the value is a success value, applies the given function to it (requirement from `Functor<Either, a, e>`).
  - `Either<b, e> ap_impl(const Either<std::function<b(a)>, e> &func) const`: if the function is not an error value, `fmap` that value over this `Either` (requirement from `Applicative<Either, a, e>`).
  - `Either<b, e> bind_impl(const std::function<Either<b, e>(a)> f) const`: if the value is a success value, returns the function's return value (requirement from `Monad<Either, a, e>`).
- Member fields:
  - `const union v_type { const a val; const e err; }`: the "success"/"error" union.
  - `const bool isError`: `true` if the value is an "error" value, otherwise `false`.
- Member types:
  - `union v_type`: the value/error union type. Usage outside of the `Either<a, e>` class is undefined behavior.
- Static functions:
  - `static Either<a, e> pure(a val)`: wraps the given value as a "success" in an `Either` (requirement from `Applicative<Either, a, e>`).
- Alternative version: `class Either : public Monad<Either, a, e>, public Show` when `std::enable_if_t<std::conjunction_v<std::is_base_of_v<Show, a>, std::is_base_of_v<Show, e>>>`
  - `hsString show() const override`: converts this `Either` value to a string representation.

#### List types
*`class List : public Monad<List, a>`:* (monadic list type) ![list.hpp]
- Constructors:
  - `List()`: constructs an empty `List` (equivalent to Haskell's `[]`).
  - `List(const a value, const List<a> next)`: constructs a `List` by pre-pending a value to a copy of another `List` (equivalent to Haskell's `:`).
  - `List(const List<a> &other)`: copies another `List`
- Member functions:
  - `List<b> fmap_impl(const std::function<b(a)> f) const`: applies the given function to each element of the list (requirement from `Functor<List, a>`).
  - `List<b> ap_impl(const List<std::function<b(a)>> &func) const`: applies each of the functions to each of the elements of the list (requirement from `Applicative<List, a>`).
  - `List<b> bind_impl(const std::function<List<b>(a)> &f) const`: flattens the result of `fmap` over this list, using the supplied function.
- Member fields:
  - `const std::optional<a> value`: the value of this node.
  - `cosnt List<a> *next`: the next node in the list.
- Member types: none
- Static functions:
  - `static List<a> append(const List<a> one, const List<a> other)`: appends two lists, creating a new one.
  - `static List<a> pure(a val)`: creates a singleton `List` from the given value (requirement from `Applicative<List, a>`).
- Operators: none

*`class hsString : public List<hsChar>, public Show`* (monadic string type) ![string.hpp]
- Constructors:
  - `hsString()`: constructs an empty `hsString` (equivalent to Haskell's `""`).
  - `hsString(cosnt hsChar chr, const List<hsChar> next)`: constructs a `hsString` by pre-pending a value to a copy of another `hsString` (equivalent to Haskell's `:`).
- Member functions:
  - `hsString show() const override`: returns (a copy of) the same object (requirement from `Show`).
- Member fields: none
- Member types: none
- Static functions:
  - `static hsString fromString(std::string str)`: converts a C++-string to a `hsString`.
  - `static hsString fromList(const List<hsChar> lst)`: specializes a `List<hsChar>`.
- Operators:
  - `std::ostream &operator<<(std::ostream &strm, const hsString string)`: writes a `hsString` to an `ostream` [candidate for removal].

## Type classes
All the type classes are simply abstract classes. Many type classes use the CRTP pattern to enforce templated methods or static methods on derived classes. The inheritance requirements imply that the type class derives from another type class.

*`class Show`* ![showread.hpp]
- Implementation requirements:
  - Override `virtual hsString show() const`. Converts a `Show` type to its string representation.
- Own functions: none

*`template <typename Self> class Read<Self>`* ![showread.hpp]
- Implementation requirements:
  - `Self` should contain `static Self read(hsString value)`.
- Own functions:
  - `static Self read(const hsString &value)`: Converts a string back to the original type.

*`template <template <typename, typename ...> typename Self, typename a, typename ... rest> class Functor<Self, a>`* ![functor.hpp]
- Implementation requirements:
  - `Self<a, rest ...>` should contain `Self<b rest ...> fmap_impl(const std::function<b(a)> f)`.
- Own functions:
  - `Self<b, rest ...> fmap(const std::function<b(a)> f)`: Maps over a functor.

*`template <template <typename, typename ...> typename Self, typename a, typename ... rest> class Applicative<Self, a>`* ![applicative.hpp]
- Implementation requirements:
  - `Self<a, rest ...>` should inherit from `Functor<Self, a, rest ...>`.
  - `Self<a, rest ...>` should contain `static Self<a, rest ...> pure(a val)`.
  - `Self<a, rest ...>` should contain `Self<b, rest ...> ap_impl(const Self<std::function<b(a)>, rest ...> func)`.
- Own functions:
  - `static Self<a, rest ...> pure(a val)`: Wraps a value in the Applicative.
  - `Self<b, rest ...> ap(const Self<std::function<b(a)>, rest ...> func)`: Applies sequentially.

*`template <template <typename, typename ...> typename Self, typename a, typename ... rest> class Monad<Self, a>`* ![monad.hpp]
- Implementation requirements:
  - `Self<a, rest ...>` should inherit from `Applicative<Self, a, rest ...>`.
  - `Self<a, rest ...>` should contain `Self<b, rest ...> bind_impl(const std::function<Self<b, rest ...>(a)> f)`.
- Own functions:
  - `static Self<a, rest ...> ret(a val)`: Wraps a value in the Monad.
  - `Self<b, rest ...> bind(const std::function<Self<b, rest ...>(a)> f)`: Composes two actions

## Free functions
*`hsString show(hsInt val):`* ![_show_basic.hpp]  
Converts the given `hsInt` to a `hsString`.

*`hsString show(hsInteger val):`* ![_show_basic.hpp]  
Converts the given `hsInteger` to a `hsString`.

*`hsString show(hsBool val):`* ![_show_basic.hpp]  
Converts the given `hsBool` to a `hsString`.

*`hsString show(hsFloat val):`* ![_show_basic.hpp]  
Converts the given `hsFloat` to a `hsString`.

*`hsString show(hsDouble val):`* ![_show_basic.hpp]  
Converts the given `hsDouble` to a `hsString`.

*`hsString show(hsChar val):`* ![_show_basic.hpp]  
Converts the given `hsChar` to a `hsString`.

[//]: # (Links)
[types.hpp]: https://img.shields.io/badge/header-types.hpp-informational
[showread.hpp]: https://img.shields.io/badge/header-showread.hpp-informational
[functor.hpp]: https://img.shields.io/badge/header-functor.hpp-informational
[applicative.hpp]: https://img.shields.io/badge/header-applicative.hpp-informational
[monad.hpp]: https://img.shields.io/badge/header-monad.hpp-informational
[list.hpp]: https://img.shields.io/badge/header-list.hpp-informational
[string.hpp]: https://img.shields.io/badge/header-string.hpp-informational
[_show_basic.hpp]: https://img.shields.io/badge/header-__show__basic.hpp-informational
[maybe.hpp]: https://img.shields.io/badge/header-maybe.hpp-informational
[either.hpp]: https://img.shields.io/badge/header-either.hpp-informational
