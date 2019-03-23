# kool-cpp-tools
A set of useful templates, constexpr functions and other tricks that I use all the time in embedded development. C++17 and upwards, header-only, structured as a CMake package.

Aside from some headers that contain implementation, the main is usable things are:

## Allocators
Runtime memory allocation
* _beefy_

   Static allocator with 2logN allocation and 3logN deallocation speed, done with heaps.
   Storages sizes and their variability are selected by the user at compile time.
   Has substantial overhead per one unique block of memory (5 to 17 bytes, depending on your system bitness), therefore larger blocks are more preferable.
  
## IO
Overhead-malleable user/string input/output
* _str_and_int_

    Type-safe ASCII-only capable class that formats the input data (chars, c-strings, ints in udec, sdec, oct, hex and HEX) and sends it
    via the provided lambda char by char. Supports padding numbers. 
    Uses custom light printf implementation which is also provided in this library.
    
## Miscellaneous
Unsorted but useful
* _bitwise_

    Common bit operations on integral types, such as masking, l/r shifting with count, etc (the list will grow).
    
* _byte_

    An implementation of an arithmetic type 'byte'. It is not just a
    enum class as the C++17 std::byte. A byte occupies 8 bits and 
    aligned as 1 byte in memory. It is not a char, nor a signed or
    unsigned char. Can be used in operations with native integral types
    (signed/unsigned short/int/long/long long. Has a single member that
    is a plain unscoped enum member with an underlying type of either
    'int8_t or uint8_t'
    
    Use this one when you want to ensure that the '8-bit' container you are using is by no means a 'character'.
    Or when you really tired of declaring a uint8_t and see the character '0' instead of a number 0x30 during the debugging.
    
    
* _c_array_

    Provides a more convenient c-array type template, as well as tools
    to determine the size, element type and a signature of an arbitrary
    c-array at compile time.

* _debug_

    Debugging tools, right now only has compile-time type display (Scott
    Meyers' trick)

* _endian_

    A union class that can be used to determine the endianness of your
    system at compile time.

* _log2_

    Logarithm of base 2 arithmetic on integral types

* _pow2_

    Power of 2 arithmetic on integral types

* _range_

    Imitate Python range() expression in a C++ range-based for loop. In
    addition contains a class 'indices' that extracts the available
    indices of any iterable container, used the same way as 'range'.

* _sequence_

    type-container of sequences (parameter packs)

* _traits_

    Often used compile-time boolean expressions 'is_something_v'.

* _util_
    
    Often used 'enable_if_something_t' and other utilities like compile
    time array slicing/concatenation.
    