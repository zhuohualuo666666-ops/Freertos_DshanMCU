<!-- _FreeRTOS源码概述 -->

·数据类型：
1.TickType_t:
该类型可以是16位，也可以是32位；
在FreeRTOSConfig.h中定义configUSE_16BIT_TICKS时，TickType_t就是uint16_t,否则是uint32_t;
32位架构建议配置为uint32_t

2.BaseType_t:
架构的最高效数据类型，32位中就是uint32_t，64位中就是uint64_t


·变量名前缀：
p:指针
x:BaseType_t
u:unsigned

·函数名前缀：
vTask:返回值类型void,该函数在Task.c中定义
xQueue:返回值类型BaseType_t,该函数在Queue.c中定义
pvTimer:返回值类型pointer to void,该函数在Timer.c中定义

·宏的前缀：
port:在portable.h或portmacro.h中定义
task:在task.h中定义
pd:在projdefs.h中定义
config:在FreeRTOSConfig.h中定义
