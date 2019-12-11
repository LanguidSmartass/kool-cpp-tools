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

list(
    APPEND
    
    headers-list-template
    
    allocators/beefy.hpp

    io/common/builtin.hpp
    io/common/conversion.hpp
    io/common/conversion_table.hpp
    io/common/fmt.hpp
    
    io/printf/str_and_int.hpp
    io/out_str_and_int.hpp

    serial/serial.hpp
    
    align.hpp
    bitwise.hpp
    bitset.hpp
    byte.hpp
    c_array.hpp
    c_file.hpp
    c_string.hpp
    contiguous_array.hpp
    debug.hpp
    endian.hpp
    functional.hpp
    ioreg.hpp
    log2.hpp
    loop_if.hpp
    loop_switch.hpp
    mathrel.hpp
    pow2.hpp
    range.hpp
    rate.hpp
    regular_obj.hpp
    sequence.hpp
    smart_enum.hpp
    std_array_nd.hpp
    traits.hpp
    util.hpp
)
