//
// Created by lining on 6/11/24.
//

#include "gpu.h"
#include <string.h>
#include <stdlib.h>
#include "font.h"
#include "utils.h"

GPU gpu;

int gpuInit(GPU *gpu, uint32_t width, uint32_t height, uint32_t bpp) {
    gpu->width = width;
    gpu->height = height;
    gpu->bpp = bpp;
    gpu->pitch = width * bpp / 8;
    gpu->size = height * gpu->pitch;
    gpu->buf = (uint8_t *) malloc(gpu->size);

    return 0;
}

int gpuFree() {
    if (gpu.buf != NULL) {
        free(gpu.buf);
        gpu.buf = NULL;
    }

    return 0;
}


int gpuClear(GPU *gpu) {
    memset(gpu->buf, 0, gpu->size);

    return 0;
}

int gpuFill(GPU *gpu, uint8_t *data, uint32_t dataWidth, uint32_t dataHeight, uint32_t start_x, uint32_t start_y) {
    uint32_t realDataWidth = dataWidth * gpu->bpp / 8;
    uint32_t realDataHeight = dataHeight;
    uint32_t realStartX = start_x * gpu->bpp / 8;
    uint32_t realStartY = start_y;
    uint32_t realGPUWidth = gpu->width * gpu->bpp / 8;
    uint32_t realGPUHeight = gpu->height;

    //1.判断开始的位置是否在显存内，如果越界则直接退出
    if (start_x > gpu->width || start_y > gpu->height) {
        return -1;
    }
    //2.判断要显示的区域在显存内是否越界，如果越界则取交集
    uint32_t width = (realDataWidth + realStartX) > realGPUWidth ? (realGPUWidth - realStartX) : realDataWidth;
    uint32_t height = (realDataHeight + realStartY) > realGPUHeight ? (realGPUHeight - realStartY) : realDataHeight;

    //3.开始将数据拷贝到显存中
    uint32_t pitch = dataWidth * gpu->bpp / 8;
    for (int i = realStartY; i < realStartY + height; i++) {
        for (int j = realStartX; j < width + pitch; ++j) {
            memcpy(gpu->buf + (i * gpu->pitch + j), data + ((i - realStartY) * pitch + (j - realStartX)), 1);
        }
    }


    return 0;
}

void test_gpu() {
    //初始化显存
    gpuInit(&gpu, 1024, 768, 1);
    //获取字符数据
    uint8_t str[] = {0xD0, 0xCB};//"兴"
    fontInit("ascii0816", "hz1616", 16, 16, 1);
    int ret = fontGetOneGBK(str, ARRAY_SIZE(str));
    if (ret > 0) {
        //将字符数据填充到显存中
        gpuClear(&gpu);
        uint32_t offset = 1;
        gpuFill(&gpu, font.buf, font.width, font.height, 16 * offset, offset);

//        //开始显示单字
//        for (int i = 0; i < font.height; i++) {
//            printf("\n");
//            for (int j = 0; j < font.pitch; j++) {
//                for (int k = 0; k < 8; ++k) {
//                    if (isBitSet(*((uint8_t *) font.buf + (i * font.pitch + j)), 8 - k)) {
//                        printf("*");
//                    } else {
//                        printf(" ");
//                    }
//                }
//            }
//        }

        //将显存中的数据填充到屏幕上
        for (int i = 0; i < gpu.height; i++) {
            printf("\n");
            for (int j = 0; j < gpu.pitch; j++) {
                for (int k = 0; k < 8; ++k) {
                    if (isBitSet(*((uint8_t *) gpu.buf + (i * gpu.pitch + j)), 8 - k)) {
                        printf("*");
                    } else {
                        printf(" ");
                    }
                }
            }
        }
    }
}


