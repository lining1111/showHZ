//
// Created by lining on 6/11/24.
//

#ifndef SHOWHZ_UTILS_H
#define SHOWHZ_UTILS_H

#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))


/*
 * 一些基础类信息
 *
 */

/**
 * 获取字符数组中GBK编码的偏移
 * @param str GBK字符数组
 * @return 1 ASCII 2 HANZI
 */
int getGBKOffset(uint8_t *str);

void test_getGBKOffset();


/**
 * 获取单个字节的位值
 * @param data 原始字节数值
 * @param bit 要获取的位值 0-7
 * @return 1 该位为1 0 该位为0
 */
int isBitSet(uint8_t data, int bit);

void test_isBitSet();


/**
 * 设置单个字节的位值
 * @param data 原始字节数值
 * @param bit 要设置的位值 0-7
 * @param val 1 设置为1 0 设置为0
 */
void bitSet(uint8_t *data, int bit, int val);

void test_bitSet();

#endif //SHOWHZ_UTILS_H
