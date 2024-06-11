//
// Created by lining on 6/11/24.
//

#ifndef SHOWHZ_GPU_H
#define SHOWHZ_GPU_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t height;//显存高度
    uint32_t width;//显存宽度
    uint32_t bpp;//每像素位数
    uint32_t pitch;//显存每行字节数
    uint32_t size;//显存大小
    uint8_t *buf = NULL;//显存空间
}GPU;

extern GPU  gpu;

/**
 * 初始化显存
 * @param gpu 显存变量
 * @param width 显存宽度
 * @param height 显存高度
 * @param bpp 每个像素点的位数
 * @return 0 成功 其他失败
 */
int gpuInit(GPU *gpu, uint32_t width, uint32_t height, uint32_t bpp);


int gpuFree();

/**
 * 显存清空
 * @param gpu
 * @return 0 成功 其他失败
 */
int gpuClear(GPU *gpu);

/**
 * 显存填充
 * @param gpu 显存变量
 * @param data 要填充的数据
 * @param dataWidth 数据宽度
 * @param dataHeight 数据高度
 * @param start_x 显示的起始坐标
 * @param start_y 显示的起始坐标
 * @return 0 成功 其他失败
 */
int gpuFill(GPU *gpu, uint8_t *data, uint32_t dataWidth, uint32_t dataHeight, uint32_t start_x, uint32_t start_y);


void test_gpu();

#endif //SHOWHZ_GPU_H
