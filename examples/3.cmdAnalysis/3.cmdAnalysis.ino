/*!
 * @file cmdAnalysis.ino
 * @brief 解析串口命令，保存并打印（以UART2为例，将UART2的RX与TX引脚连接到一起）
 * @n 通过串口随机发送一个字符串："ABCDEFASFGHJUAAAEEB"
 * @n 接收该字符串，去掉字符串中的字符'A'，并将消除字符'A'后的字符串打印出来
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
DFRobot_IIC_Serial iicSerial2(Wire, /*subUartChannel =*/SUBUART_CHANNEL_2, /*IA1 = */1,/*IA0 = */1);//构造子串口2

char rx_buffer[256];//定义一个接收缓存存储UART1接收到的数据
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
  iicSerial2.begin(/*baud = */115200);/*子串口2初始化*/
  //iicSerial2.begin(/*baud = */115200, /*format = */IIC_SERIAL_8N1);
  Serial.println("\n+-----------------------------------------------------+");
  Serial.println("|  connected UART2's TX pin to RX pin.                |");
  Serial.println("|  Analysis string and eliminate a char of a string.  |");
  Serial.println("|  Original string: ABCDEFASFGHJUAAAEEB               |");
  Serial.println("|  Eliminate char: A                                  |");
  Serial.println("|  Original string: BCDEFSFGHJUEEB                    |");
  Serial.println("|  Print the parsed string.                           |");
  Serial.println("+-----------------------------------------------------+");
  Serial.println("Please Send to the string by UART2's TX.");
  Serial.println("UART2 send a string: ABCDEFASFGHJUAAAEEB");
  iicSerial2.println("ABCDEFASFGHJUAAAEEB");//子串口2发送字符串"ABCDEFASFGHJUAAAEEB"
}

void loop() {
  int n = iicSerial2.available();//读取子串口2中的字节数
  int i = 0;
  if(n){
      while(iicSerial2.available()){
          if((char)iicSerial2.peek() != 'A'){//使用peek函数读取字符，不会清除缓存中的数据
              rx_buffer[i++] = iicSerial2.read();//使用read函数读取字符，会清除缓存中的数据
              if((i > (sizeof(rx_buffer) - 1)))
                  break;
          }else{
              iicSerial2.read();//read函数放在这里，用于清除缓存里的一个字节数据，这里是清除字符'A'
          }
      }
      Serial.print("Parsed string: ");
      for(int j = 0; j < i; j++){
          Serial.print(rx_buffer[j]);
      }
      Serial.println();
  }
  delay(1000);
}
