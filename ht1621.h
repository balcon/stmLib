
//#define CS_PORT GPIOB           // Chip Select
//#define CS_PIN GPIO_PIN_0
//#define WR_PORT GPIOB           // Write Clock
//#define WR_PIN GPIO_PIN_1
//#define DT_PORT GPIOB           // Data
//#define DT_PIN GPIO_PIN_2

GPIO_TypeDef* CS_PORT;
GPIO_TypeDef* WR_PORT;
GPIO_TypeDef* DT_PORT;
GPIO_Pin_TypeDef CS_PIN;
GPIO_Pin_TypeDef WR_PIN;
GPIO_Pin_TypeDef DT_PIN;

void sendCode(char data, char size){
  char mask=(0x01)<<(size-1);
  for(int i=0;i<size;i++){
    GPIO_WriteLow(WR_PORT,WR_PIN);
    if((data&mask)==0) GPIO_WriteLow(DT_PORT,DT_PIN);
      else GPIO_WriteHigh(DT_PORT,DT_PIN);
    GPIO_WriteHigh(WR_PORT,WR_PIN);
    mask=mask>>1;
  }
}

void lcdInit(GPIO_TypeDef* cs_port, GPIO_Pin_TypeDef cs_pin,
             GPIO_TypeDef* wr_port, GPIO_Pin_TypeDef wr_pin,
             GPIO_TypeDef* dt_port, GPIO_Pin_TypeDef dt_pin){
  CS_PORT=cs_port;
  CS_PIN=cs_pin;
  WR_PORT=wr_port;
  WR_PIN=wr_pin;
  DT_PORT=dt_port;
  DT_PIN=dt_pin;
  GPIO_Init(CS_PORT,CS_PIN,GPIO_MODE_OUT_PP_HIGH_SLOW); 
  GPIO_Init(WR_PORT,WR_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
  GPIO_Init(DT_PORT,DT_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
  
  GPIO_WriteLow(CS_PORT,CS_PIN);
  sendCode(0x04,3); //Code - Command
  sendCode(0x01,8); //Code - SystemEnable
  sendCode(0,1);
  sendCode(0x03,8); //Code - LCD on
  sendCode(0,1);
  sendCode(0x29,8); //Code - Config brightnes, an other shit
  sendCode(0,1);
  GPIO_WriteHigh(CS_PORT,CS_PIN);
}

void sendChar(char ch){
  char charCode;
  switch(ch){
    case '0': charCode=0x7D;
      break;
    case '1': charCode=0x60;
      break;
    case '2': charCode=0x3E;
      break;
    case '3': charCode=0x7A;
      break;
    case '4': charCode=0x63;
      break;
    case '5': charCode=0x5B;
      break;
    case '6': charCode=0x5F;
      break;
    case '7': charCode=0x70;
      break;
    case '8': charCode=0x7F;
      break;
    case '9': charCode=0x7B;
      break;
    case 'a':
    case 'A': charCode=0x77;
      break; 
    case 'b':
    case 'B': charCode=0x4F;
      break;
    case 'c': charCode=0x0E;
      break; 
    case 'C': charCode=0x1D;
      break; 
    case 'd':
    case 'D': charCode=0x6E;
      break;  
    case 'e':
    case 'E': charCode=0x1F;
      break;
    case 'f':
    case 'F': charCode=0x17;
      break; 
    case 'g':
    case 'G': charCode=0x5D;
      break; 
    case 'h': charCode=0x47;
      break; 
    case 'H': charCode=0x67;
      break; 
    case 'i': charCode=0x40;
      break; 
    case 'I': charCode=0x60;
      break; 
    case 'j': charCode=0x68;
      break;
    case 'J': charCode=0x6C;
      break;
    case 'k':
    case 'K': charCode=0x0F;
      break; 
    case 'l': charCode=0x05;
      break;
    case 'L': charCode=0x0D;
      break;
    case 'n':
    case 'N': charCode=0x46;
      break;
    case 'o': charCode=0x4E;
      break; 
    case 'O': charCode=0x7D;
      break; 
    case 'p':
    case 'P': charCode=0x37;
      break;
    case 'q':
    case 'Q': charCode=0x73;
      break; 
    case 'r':
    case 'R': charCode=0x06;
      break;
    case 's':
    case 'S': charCode=0x5B;
      break; 
    case 't':
    case 'T': charCode=0x15;
      break; 
    case 'u': charCode=0x4C;
      break;
    case 'U': charCode=0x6D;
      break;
    case 'y':
    case 'Y': charCode=0x6B;
      break;
    case '-': charCode=0x02;
      break;
    default: charCode=0x00;
  }
  sendCode(charCode,8);
}

void clear(){
    
  GPIO_WriteLow(CS_PORT,CS_PIN);
  sendCode(0x05,3); // Code - Write
  sendCode(0x00,6); // Address
  for(char i=0;i<6;i++)
  {
    sendCode(0x00,8); // Data
  } 
  GPIO_WriteHigh(CS_PORT,CS_PIN);
}
void sendWord(char* str){
  clear();
  GPIO_WriteLow(CS_PORT,CS_PIN);
  sendCode(0x05,3); //Code - Write
  sendCode(0x00,6); // Address
  char len=strlen(str);
  for(char i=0;i<len;i++)
    sendChar(str[len-i-1]); // Data
  GPIO_WriteHigh(CS_PORT,CS_PIN);
}
