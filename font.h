//
// Created by lining on 6/11/24.
//

#ifndef SHOWHZ_FONT_H
#define SHOWHZ_FONT_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    FILE *fileASCII = NULL;//ASCII字体文件
    FILE *fileGBK = NULL;//GBK字体文件
    uint32_t width;//字体宽度
    uint32_t height;//字体高度
    uint32_t bpp;//每个像素位数
    uint32_t pitch;//每行字节数
    uint8_t *buf = NULL;//字体数据
    uint32_t len = 0;
} Font;

extern Font font;

int loadFontFile(const char *path, FILE **file);

int freeFontFile();

int fontInit(const char *pathASCII, const char *pathGBK, uint32_t width, uint32_t height, uint32_t bpp);

int fontFree();

int fontGetOneGBK(uint8_t *str, uint32_t len);

void test_font();

#endif //SHOWHZ_FONT_H
