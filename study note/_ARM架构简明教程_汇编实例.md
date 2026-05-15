<!-- _ARM架构简明教程_汇编实例 -->

C函数：
int add(volatile int a,volatile int b)
{
    volatile int sum;
    sum=a+b;
    return sum;
}

调用：
void OLED_Test(void)
{
	int cnt = 0;
    OLED_Init();
	// 清屏
	OLED_Clear();
    
	while (1)
	{
		// 在(0, 0)打印'A'
		OLED_PutChar(0, 0, 'A');
		// 在(1, 0)打印'Y'
		OLED_PutChar(1, 0, 'Y');
		// 在第0列第2页打印一个字符串"Hello World!"
		OLED_PrintString(0, 2, "Hello World!");
		OLED_PrintSignedVal(0, 4, cnt);
		
		cnt = add(cnt, 1);
	}
}
反汇编：
·指令：
fromelf  --text  -a  -c  --output==xxx.dis  xxx.axf

xxx替换为生成的文件名和文件保存的根目录：
fromelf  --text  -a -c  --output=test.dis  01_freertos_template\01_freertos_template.axf


·反汇编格式：
地址  机器码  汇编码（3列）

注：烧写的是机器码，给人看的是汇编码，执行到对应指令时，CPU读取地址，得到机器码，执行机器码



·调用反汇编：
    OLED_Test
        0x08002a00:    2400        .$      MOVS     r4,#0
        0x08002a02:    f7ffff01    ....    BL       OLED_Init ; 0x8002808
        0x08002a06:    f7fffeea    ....    BL       OLED_Clear ; 0x80027de
        0x08002a0a:    2100        .!      MOVS     r1,#0
        0x08002a0c:    2241        A"      MOVS     r2,#0x41
        0x08002a0e:    4608        .F      MOV      r0,r1
        0x08002a10:    f7ffff9c    ....    BL       OLED_PutChar ; 0x800294c
        0x08002a14:    2259        Y"      MOVS     r2,#0x59
        0x08002a16:    2100        .!      MOVS     r1,#0
        0x08002a18:    2001        .       MOVS     r0,#1
        0x08002a1a:    f7ffff97    ....    BL       OLED_PutChar ; 0x800294c
        0x08002a1e:    a208        ..      ADR      r2,{pc}+0x22 ; 0x8002a40
        0x08002a20:    2102        .!      MOVS     r1,#2
        0x08002a22:    2000        .       MOVS     r0,#0
        0x08002a24:    f7ffff79    ..y.    BL       OLED_PrintString ; 0x800291a
        0x08002a28:    4622        "F      MOV      r2,r4
        0x08002a2a:    2104        .!      MOVS     r1,#4
        0x08002a2c:    2000        .       MOVS     r0,#0
        0x08002a2e:    f7ffff35    ..5.    BL       OLED_PrintSignedVal ; 0x800289c
        0x08002a32:    2101        .!      MOVS     r1,#1
        0x08002a34:    4620         F      MOV      r0,r4
        0x08002a36:    f000fa7f    ....    BL       add ; 0x8002f38
        0x08002a3a:    4604        .F      MOV      r4,r0
        0x08002a3c:    e7e5        ..      B        0x8002a0a ; OLED_Test + 10


思路：
MOVS指令意思是移动数值，理解为赋值，
令r1=1,r0=r4,这里r4等于变量cnt,
接着调用add函数，
调用完计算出的新值再次保存到r4寄存器中


·C函数反汇编：
add
        0x08002f38:    b503        ..      PUSH     {r0,r1,lr}
        0x08002f3a:    b081        ..      SUB      sp,sp,#4
        0x08002f3c:    e9dd0101    ....    LDRD     r0,r1,[sp,#4]
        0x08002f40:    4408        .D      ADD      r0,r0,r1
        0x08002f42:    9000        ..      STR      r0,[sp,#0]
        0x08002f44:    bd0e        ..      POP      {r1-r3,pc}


思路：
a,b,sum三个局部变量保存在栈里。

PUSH指令属于STR指令的变种，
假设初始栈指针sp指向A这个地址，即sp=A，
PUSH     {r0,r1,lr}这一句执行后，栈指针sp由高地址向低地址移动，
从高到低写入lr,r1,r0,占据12个字节，此时sp=sp-12=A-12，
这里r0=cnt,r1=1,lr是返回地址，值为0x08002a3a,即返回到调用add函数的下面；

SUB      sp,sp,#4这一句是减法，意思是sp=sp-4栈指针再次向低地址移动，开辟4个字节空间,此时sp=A-16；

LDRD     r0,r1,[sp,#4]这一句意思是从sp+4的位置读8个字节，分别存入r0和r1，此时sp=A-16，
即A-12开始的4个字节空间里保存的cnt值存入r0,A-8开始的4个字节空间里保存的1值存入r1；

ADD      r0,r0,r1这一句意思是r0=r0+r1=cnt+1;

STR      r0,[sp,#0]这一句意思是将r0的值保存到sp+0,即A-16,这个值对应C函数的sum变量；

POP      {r1-r3,pc}这一句意思是将开辟出来的栈空间A-16,A-12,A-8,A-4开始的四个字节空间里保存的数值移动到r1,r2,r3,pc寄存器中，目的是将返回地址放入pc寄存器和恢复栈；