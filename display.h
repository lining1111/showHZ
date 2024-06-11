//
// Created by lining on 6/11/24.
//

#ifndef SHOWHZ_DISPLAY_H
#define SHOWHZ_DISPLAY_H


typedef struct {
    char show = '*';//显用*
    char hide = ' ';//不显用空格
}Display;

extern Display display;


int displayInit();

/**
 * 显示
 * @param x 起始x
 * @param y 起始y
 * @param data  数据
 * @param width 宽度
 * @param height 高度
 * @param bpp 每个像素的位数
 * @return 0 成功 其他失败
 */
int displayShow(int x, int y,  void *data, int width, int height, int bpp);


void test_display();

#endif //SHOWHZ_DISPLAY_H
