//
// Created by lining on 6/11/24.
//

#include <stdio.h>
#include "utils.h"

int getGBKOffset(uint8_t *str) {
    if (((uint8_t) (*str)) > 0x7f) {
        return 2;
    } else {
        return 1;
    }

}

void test_getGBKOffset() {
    //GBK编码 兴1陆0科0技
    uint8_t str[] = {0xD0, 0xCB,
                     0x31,
                     0xC2, 0xBD,
                     0x30,
                     0xBF, 0xC6,
                     0x30,
                     0xBC, 0xBC};

    printf("offset\n");
    int offset = 0;
    do {
        int offset_t = getGBKOffset( (str + offset));
        printf("%d\n", offset_t);
        offset += offset_t;
    } while (offset < ARRAY_SIZE(str));

}


int isBitSet(uint8_t data, int bit) {
    if ((data >> bit) & 0x01) {
        return 1;
    } else {
        return 0;
    }
}

void test_isBitSet() {
    uint8_t val = 0x75;//b01110101
    for (int i = 0; i < 8; ++i) {
        printf("%d\n", isBitSet(val, i));
    }
}


void bitSet(uint8_t *data, int bit, int val) {
    if (val) {
        *data |= (1 << bit);
    } else {
        *data &= ~(1 << bit);
    }
}

void test_bitSet() {
    uint8_t val = 0x75;//b01110101
    bitSet(&val, 1, 1);
    printf("%02x\n", val);
}




