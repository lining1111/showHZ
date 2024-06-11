//
// Created by lining on 6/11/24.
//

#include <stdlib.h>
#include <string.h>
#include "font.h"
#include "utils.h"

Font font;


int loadFontFile(const char *path, FILE **file) {
    *file = fopen(path, "rb");

    if (*file == NULL) {
        return -1;
    }


    return 0;
}

int freeFontFile() {
    if (font.fileASCII != NULL) {
        free(font.fileASCII);
        font.fileASCII = NULL;
    }
    if (font.fileGBK != NULL) {
        free(font.fileGBK);
        font.fileGBK = NULL;
    }


    return 0;
}

int fontInit(const char *pathASCII, const char *pathGBK, uint32_t width, uint32_t height, uint32_t bpp) {
    if (loadFontFile(pathASCII, &font.fileASCII) != 0) {
        return -1;
    }
    if (loadFontFile(pathGBK, &font.fileGBK) != 0) {
        return -1;
    }

    font.width = width;
    font.height = height;
    font.bpp = bpp;
    font.pitch = font.width * font.bpp / 8;
    //buf malloc
    font.len = height * font.pitch;
    font.buf = (uint8_t *) malloc(font.len);

    return 0;
}

int fontFree() {
    freeFontFile();

    return 0;
}


int fontGetOneGBK(uint8_t *str, uint32_t len) {

    //点阵字库的地址偏移
    //ASCII的地址偏移为 c-' ' 再乘以每个ASCII字符的点阵字节数
    //汉字的地址偏移（(H-0xa1)*94 + (L - 0xa1))*每个ASCII字符的点阵字节数
    uint32_t location = 0;
    int ret = 0;
    ret = getGBKOffset(str);
    switch (ret) {
        case 1: {
            //ASCII
            uint8_t val = (uint8_t) *str;
            location = (val - ' ') * font.len / 2;
            //读取单个字的点阵数据
            memset(font.buf, 0, font.len);
            FILE *file = (FILE *) font.fileASCII;
            fseek(file, location, SEEK_SET);
            int index = 0;
            int row = font.height;
            int pitch = font.pitch / 2;
            for (int i = 0; i < row; ++i) {
                fseek(file, location + index, SEEK_SET);
                fread((uint8_t *) font.buf + i * pitch * 2, pitch, 1, file);
                index += pitch;
            }
        }
            break;
        case 2: {
            //汉字
            uint8_t h = (uint8_t) *str;
            uint8_t l = (uint8_t) *(str + 1);
            location = ((h - 0xa1) * 94 + (l - 0xa1)) * font.len;
//location = 0;
            //读取单个字的点阵数据
            memset(font.buf, 0, font.len);
            FILE *file = (FILE *) font.fileGBK;
            fseek(file, location, SEEK_SET);
            int index = 0;
            int row = font.height;
            int pitch = font.pitch;
            for (int i = 0; i < row; ++i) {
                fseek(file, location + index, SEEK_SET);
                fread((uint8_t *) font.buf + i * pitch, pitch, 1, file);
                index += pitch;
            }
        }
            break;
    }


    return ret;
}

/**
 * 显示用* 不显示用空格
 */
void test_font() {
//    uint8_t str[] = {0x31};//"1"
    uint8_t str[] = {0xD0, 0xCB};//"兴"
    fontInit("ascii0816", "hz1616", 16, 16, 1);
    int ret = fontGetOneGBK(str, ARRAY_SIZE(str));
    if (ret > 0) {
        //开始显示
        for (int i = 0; i < font.height; i++) {
            printf("\n");
            for (int j = 0; j < font.pitch; j++) {
                for (int k = 0; k < 8; ++k) {
                    if (isBitSet(*((uint8_t *) font.buf + (i * font.pitch + j)), 8 - k)) {
                        printf("*");
                    } else {
                        printf(" ");
                    }
                }
            }
        }
    }
    fontFree();

}

