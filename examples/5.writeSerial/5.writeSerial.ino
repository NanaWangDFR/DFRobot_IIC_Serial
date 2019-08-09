/*!
 * @file writeSerial.ino
 * @brief 向子串口中写数据(以UART2为例)
 * @n 实验现象：每隔2s从子串口2(UART2)发送一次数据
 * @n 要使用此demo你需要一个USB转串口模块连接到UART2的TX引脚，以此通过串口监视器查看打印信息
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Arya](xue.peng@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-28
 * @get from https://www.dfrobot.com
 * @url https://github.com/DFRobot/DFRobot_IIC_Serial
 */
#include <DFRobot_IIC_Serial.h>
/*DFRobot_IIC_Serial构造函数
 *参数&wire 可填TwoWire对象Wire
 *参数subUartChannel 子串口通道号，用于确定操作的是串口UART1还是UART2
 *@n 如下参数可用：
     SUBUART_CHANNEL_1  SUBUART_CHANNEL_2
           UART1             UART2
 *参数IA1  对应模块上的拨码开关IA1的电平（0或1），用于配置IIC地址第6位的值，默认为1
 *参数IA0  对应模块上的拨码开关IA0的电平（0或1），用于配置IIC地址第5位的值，默认为1
 *IIC地址配置如下所示：
 * 7   6   5   4   3   2   1   0
 * 0  IA1 IA0  1   0  C1  C0  0/1
 *@n IIC地址是7位地址，而一个字节有8位，多出的一位一般用0处理
 *@n 第6位值对应拨码开关的IA1，可手动配置
 *@n 第5位值对应拨码开关的IA0，可手动配置
 *@n 第4/3位为固定值，分别为1/0
 *@n 第2/1位的值为子串口通道，00表示子串口1，01表示子串口2，由
 *@n 第0位表示操作对象是寄存器还是FIFO缓存，0表示寄存器，1表示FIFO缓存
 */
DFRobot_IIC_Serial iicSerial2(Wire, /*subUartChannel =*/SUBUART_CHANNEL_2, /*IA1 = */1,/*IA0 = */1 );//构造串口UART2

void setup() {
  Serial.begin(115200);
  /*begin 初始化函数,设置波特率,该波特率需要根据选择的晶振频率设置
  begin(long unsigned baud)调用该函数，可设置子串口波特率，默认配置->波特率：baud，数据格式：IIC_SERIAL_8N1，8位数据，无校验模式，1位停止位
  begin(long unsigned baud, uint8_t format)调用该函数可设置波特率和数据格式,
  参数baud支持：2400、4800、57600、7200、9600、14400、19200、28800、38400、
                76800、115200、153600、230400、460800、307200、921600
  参数format可填：
  IIC_SERIAL_8N1  IIC_SERIAL_8N2  IIC_SERIAL_8Z1  IIC_SERIAL_8Z2  IIC_SERIAL_8O1
  IIC_SERIAL_8O2  IIC_SERIAL_8E1  IIC_SERIAL_8E2  IIC_SERIAL_8F1  IIC_SERIAL_8F2
  8代表数据位数，N代表无校验，Z代表0校验，O表示奇校验，E表示偶校验， F代表1校验，1或2代表停止位个数，
  默认为IIC_SERIAL_8N1 8为数据，1为停止位，无校验数据格式
  */
  while(iicSerial2.begin(/*baud = */115200) !=0){//UART2初始化
    Serial.println("串口初始化失败，检查模块是否正确连接!");
    delay(10);
  }
  //iicSerial2.begin(/*baud = */115200, /*format = */IIC_SERIAL_8N1);
  Serial.println("\n+--------------------------------------------------------------+");
  Serial.println("|  Write data to UART2.                                        |");
  Serial.println("|  Connected UART2's TX pin to a UART module!                  |");//将UART2的TX引脚连接到一个USB转串口模块的RX引脚
  Serial.println("|  UART2 send a string: \"hello, world!\"                        |");
  Serial.println("|  UART2 send a char: 'A'                                      |");
  Serial.println("+--------------------------------------------------------------+");
  Serial.println("Start to send data to serial.");
}

void loop() {
  iicSerial2.println("hello, world!");//子串口2发送字符串"hello, wrold!"
  iicSerial2.write('A');
  delay(2000);
}
