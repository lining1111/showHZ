# 点阵字库显示例程

## 1. 简介

    本例程实现了点阵字库的显示功能，通过该例程，可以实现点阵字库的显示。
    font 字库相关操作，主要涉及字体大小的设置、字体的读取、字体的写入等操作。
    gpu 与屏幕大小相当的显示缓冲区，主要涉及显示缓冲区的读取、显示缓冲区的写入等操作。
    display 将显存区的内容显示到屏幕上。

## 2.GBK编码小知识

    一、区位码
    1.
    整个GB2312字符集分成94个区，每区有94个位，每个区位上只有一个字符，即每区含有94个汉字或符号，用所在的区和位来对字符进行编码(实际上就是字符编号、码点编号)，因此称为区位码(或许叫“区位号”更为恰当)。
    换言之，GB2312将包括汉字在内的所有字符编入一个94 * 94的二维表，行就是“区”、列就是“位”，每个字符由区、位唯一定位，其对应的区、位编号合并就是区位码。比如“万”字在45区82位，所以“万”字的区位码是：45 82（注意，GB类汉字编码为双字节编码，因此，45相当于高位字节，82相当于低位字节）。
    2.
    GB2312字符集中：
    1）01~09区(682个)：特殊符号、数字、英文字符、制表符等，包括拉丁字母、希腊字母、日文平假名及片假名字母、俄语西里尔字母等在内的682个全角字符；
    2）10~15区：空区，留待扩展；
    3）16~55区(3755个)：常用汉字(也称一级汉字)，按拼音排序；
    4）56~87区(3008个)：非常用汉字(也称二级汉字)，按部首/笔画排序；
    5）88~94区：空区，留待扩展。
    二、国标码(交换码)
    1.
    为了避开ASCII字符中的不可显示字符0000 0000 ~ 0001 1111(十六进制为0 ~ 1F，十进制为0 ~ 31)及空格字符0010 0000(十六进制为20，十进制为32)（至于为什么要避开、又为什么只避开ASCII中0~32的不可显示字符和空格字符，后文有解释），国标码(又称为交换码)规定表示汉字的范围为(0010 0001，0010 0001) ~ (0111 1110，0111 1110)，十六进制为(21，21) ~ (7E，7E)，十进制为(33，33) ~ (126，126)（注意，GB类汉字编码为双字节编码）。
    因此，必须将“区码”和“位码”分别加上32(十六进制为20H，后缀H表示十六进制)，作为国标码。也就是说，国标码相当于将区位码向后偏移了32，以避免与ASCII字符中0~32的不可显示字符和空格字符相冲突。
    2.
    注意，国标码中是分别将区位码中的“区”和“位”各自加上32(20H)的，因为GB2312是DBCS双字节字符集，国标码属于双字节码，“区”和“位”各作为一个单独的字节。
    这样我们可以算出“万”字的国标码十进制为：(45+32，82+32) = (77，114)，十六进制为：(4D，72H)，二进制为：(0100 1101，0111 0010)。
    三、内码(机内码)
    1.
    不过国标码还不能直接在计算机上使用，因为这样还是会和早已通用的ASCII码冲突(导致乱码)。
    比如，“万”字国标码中的高位字节77与ASCII的“M”冲突，低位字节114与ASCII的“r”冲突。因此，为避免与ASCII码冲突，规定国标码中的每个字节的最高位都从0换成1，即相当于每个字节都再加上128(十六进制为80，即80H；二进制为1000 0000)，从而得到国标码的“机内码”表示，简称“内码”。
    2.
    由于ASCII码只用了一个字节中的低7位，所以，这个首位(最高位)上的“1”就可以作为识别汉字编码的标志，计算机在处理到首位是“1”的编码时就把它理解为汉字，在处理到首位是“0”的编码时就把它理解为ASCII字符。
    比如：
    77 + 128 = 205(二进制为1100 1101，十六进制为CD)
    114+ 128 = 242(二进制为1111 0010，十六进制为F2)
    总结一下：
    从区位码(国家标准定义) ---> 区码和位码分别+32(即+20H)得到国标码 ---> 再分+128(即+80H)得到机内码(与ACSII码不再冲突)。
    因此，区位码的区和位分别+160(即+A0H，32+128=160)可直接得到内码。用十六进制表示就是：
    区位码(区码,位码) + (20H,20H) + (80H,80H) =区位码(区码,位码) + (A0H,A0H) = 内码(高字节,低字节)。

## 3.字体数据与显存关系

    字体数据就是bitmap，而显存的呢，正常来讲应该是字节的整数倍对应一个像素点。
    但在单片机中，由于内存大小的原因，显存的位置往往是1bit对应1个像素点，这样在静态显示的时候，因为字体bitmap在宽度上是字节的整数倍，
    所以要实现左右的移动，如果按像素来就涉及到很多移位操作，如果按字体的bitmap宽度来，又显得不够细腻。
    所以要在单片机这种频率低的cpu上实现字体移动效果或者其他的动态效果，加大内存是必须的