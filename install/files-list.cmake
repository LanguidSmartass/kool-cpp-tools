# MIT License
#
# Copyright (c) 2019 Ivan Novoselov
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

set(
    headers-list-template
    
    PREFIX_DIR/allocators/beefy.hpp

    PREFIX_DIR/io/common/builtin.hpp
    PREFIX_DIR/io/common/conversion.hpp
    PREFIX_DIR/io/common/conversion_table.hpp
    PREFIX_DIR/io/common/fmt.hpp
    
    PREFIX_DIR/io/printf/str_and_int.hpp
    PREFIX_DIR/io/out_str_and_int.hpp

    PREFIX_DIR/bitwise.hpp
    PREFIX_DIR/byte.hpp
    PREFIX_DIR/c_array.hpp
    PREFIX_DIR/debug.hpp
    PREFIX_DIR/endian.hpp
    PREFIX_DIR/log2.hpp
    PREFIX_DIR/pow2.hpp
    PREFIX_DIR/range.hpp
    PREFIX_DIR/sequence.hpp
    PREFIX_DIR/traits.hpp
    PREFIX_DIR/util.hpp
)
