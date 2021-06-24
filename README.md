# HSC
*Jay's not-very-efficient implementation of Haskell's functional programming, in C++ (C upcoming).*

## C implementation
Very much todo. C++ has priority for now.

## C++ implementation
*For documentation, see [c++/docs.md](./c%2B%2B/docs.md).*  
HSC++ uses GNU Make/G++ for compilation and compiles down to a shared library (`c++/lib/libhsc++.so`).  

**Features:**
 - Basic data type wrappers (in namespace `hscpp`):
   - `hsInt` (for C/C++'s `int`, Haskell's `Int`)
   - `hsInteger` (for C/C++'s `long`, Haskell's `Integer`)
   - `hsBool` (for C/C++'s `bool`, Haskell's `Bool`)
   - `hsFloat` (for C/C++'s `float`, Haskell's `Float`)
   - `hsDouble` (for C/C++'s `double`, Haskell's `Double`)
   - `hsChar` (for C/C++'s `char`, Haskell's `Char`)
 - Show and Read type classes.
   - Limitation: due to circular dependencies, the basic data types are not Show. There exists, however, a `show` method that takes any of them and returns a `hsString` (string).
 - Functor, Applicative and Monad type classes.
 - Monadic List (and String wrapper)
   - Limitation: due to circular dependencies (partial classes), `List<a>` is not Show, even if `a` is.
 - Maybe monad (which is conditionally Show: if `a : Show`, then `Maybe<a> : Show`).
 - Either monad (which is conditionally Show: if `a : Show` and `e : Show`, then `Either<a, e> : Show`)
   - Limitation: `a` and `e` can't name the same type (due to the use of unions).

**Makefile targets:**  
 - In `c++/Makefile`:
   - `all`: builds the shared library.
   - `empty`: shows all source files, the generated object files and their dependency files.
   - `examples`: compiles/links the examples; binaries will be in `c++/ex/bin/`.
   - `tests`: compiles/links the tests; executable will be `c++/bin/all`.
   - `runtests`: compiles/links the tests, then runs it.
   - `clean`: cleans up the make environment (only for the library, doesn't clean `c++/ex/` or `c++/test/`).
   - `install`: builds the shared library, installs it under ``/usr/lib/`` and installs the header files (`c++/inc/`) under ``/usr/include/hsc/`` (requires `sudo`).
 - In `c++/ex/Makefile`:
   - `all`: builds all examples; binaries will be in `c++/ex/bin/`.
   - `clean`: cleans the examples up.
 - In `c++/test/Makefile`: tests aren't set up yet.

**Examples:**
 - `c++/ex/bin/list`: Simple example showing the monadic List.
