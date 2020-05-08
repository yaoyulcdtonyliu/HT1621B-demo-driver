#define CS   13  //Pin 2 as chip selection output
#define WR   12  //Pin 3 as read clock output
#define DATA 7  //Pin 4 as Serial data output
 
#define CS1    digitalWrite(CS, HIGH) 
#define CS0    digitalWrite(CS, LOW)
#define WR1    digitalWrite(WR, HIGH) 
#define WR0    digitalWrite(WR, LOW)
#define DATA1  digitalWrite(DATA, HIGH) 
#define DATA0  digitalWrite(DATA, LOW)
 
#define sbi(x, y)  (x |= (1 << y))  
#define cbi(x, y)  (x &= ~(1 <<y ))      
#define uchar   unsigned char 
#define uint   unsigned int 
 
#define  ComMode    0x52  
#define  RCosc      0x30  
#define  LCD_on     0x06 
#define  LCD_off    0x04 
#define  Sys_en     0x02 
#define  CTRl_cmd   0x80
#define  Data_cmd   0xa0   

int i;
int j;
int b;
int stemp;

int analogPin1 = A3;
int analogPin2 = A2;
int vala = 0;  // variable to store the value read
int valb = 0;  // variable to store the value read



//                    0    1    2    3    4    5    6    7    8    9  DEL  
const char numbers[]={0X7E,0X30,0X6D,0X79,0X33,0X5B,0X5F,0X70,0X7F,0X7B,0X00,};

//                    D4   D5   D6   D7   D8   D9  D10  D11  D12
const char addreses[]={0x00,0x02,0x04,0x06,0x08,0x0A,0x0C,0x0E,0x10};

 
void SendBit_1621(uchar sdata,uchar cnt){
  uchar i;
  for(i=0;i<cnt;i++)
  {
    WR0;
    if(sdata&0x80) DATA1;
    else DATA0;
    WR1;
    sdata<<=1;
  }
}
void SendCmd_1621(uchar command){
  CS0;
  SendBit_1621(0x80,4);
  SendBit_1621(command,8);
  CS1;
}
void Write_1621(uchar addr,uchar sdata){
  addr<<=2;
  CS0;
  SendBit_1621(0xa0,3);
  SendBit_1621(addr,6);
  SendBit_1621(sdata,8);
  CS1;
}
void HT1621_all_off(uchar num){
  uchar i;
  uchar addr=0;
  for(i=0;i<num;i++)
  {
    Write_1621(addr,0x00);
    addr+=2;
  }
}
void HT1621_all_on(uchar num){
  uchar i;
  uchar addr=0;
  for(i=0;i<num;i++)
  {
    Write_1621(addr,0xff);
    addr+=2;
  }
}
void Init_1621(void){
  SendCmd_1621(Sys_en);
  SendCmd_1621(RCosc);
  SendCmd_1621(ComMode);
  SendCmd_1621(LCD_on);
}

 
 
void setup() {
  pinMode(CS, OUTPUT); // 
  pinMode(WR, OUTPUT); // 
  pinMode(DATA, OUTPUT); //
  CS1;
  DATA1;
  WR1;
  delay(50);
  Init_1621();
  HT1621_all_on(16);
  delay(1000);
  HT1621_all_off(16);
  delay(1000);
  
}
 
void loop() {



vala = analogRead(analogPin1);  // read the input pin
tset(vala); 
delay(200); 


valb = analogRead(analogPin2);  // read the input pin
tmeas(valb); 
delay(200); 
  
}




void tset(int stemp){

                            int hunds = (stemp%100);
                                hunds = (stemp-hunds)/100;
                            int oness=stemp-(hunds*100);
                                oness=(oness%10);
                            int tenns=(stemp%10);
                                tenns=(stemp-tenns)/10;
                                tenns=tenns%10;

                            Write_1621(addreses[8], numbers[10]);  //0
                            Write_1621(addreses[8], numbers[oness]);  //0
                            Write_1621(addreses[7], numbers[10]);  //0
                            Write_1621(addreses[7], numbers[tenns]);  //0
                            Write_1621(addreses[6], numbers[10]);  //0
                            Write_1621(addreses[6], numbers[hunds]);  //0
                      }


 void tmeas(int stemp){

                            int hunds = (stemp%100);
                                hunds = (stemp-hunds)/100;
                            int oness=stemp-(hunds*100);
                                oness=(oness%10);
                            int tenns=(stemp%10);
                                tenns=(stemp-tenns)/10;
                                tenns=tenns%10;

                            Write_1621(addreses[3], numbers[10]);  //0
                            Write_1621(addreses[3], numbers[oness]);  //0
                            Write_1621(addreses[2], numbers[10]);  //0
                            Write_1621(addreses[2], numbers[tenns]);  //0
                            Write_1621(addreses[1], numbers[10]);  //0
                            Write_1621(addreses[1], numbers[hunds]);  //0
                      }
