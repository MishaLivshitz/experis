import sys

def reverse_bits(num):
    mask_begin  = 1
    mask_end  = 1 << 31
    print("{0:b}".format(num))

    while mask_begin < mask_end:

        if num&mask_begin and ~(num&mask_end):
            num^=mask_begin
            num^=mask_end

        mask_begin <<=1
        mask_end >>=1
    print("{0:b}".format(num))


def is_bit_on(num, begin, end):

    


reverse_bits(37)