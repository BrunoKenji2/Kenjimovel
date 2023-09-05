// --- Liga��es entre PIC e LCD ---
sbit LCD_RS at RE2_bit;   // PINO 2 DO PORTD LIGADO AO RS DO DISPLAY
sbit LCD_EN at RE1_bit;   // PINO 3 DO PORTD LIGADO AO EN DO DISPLAY
sbit LCD_D7 at RD7_bit;  // PINO 7 DO PORTD LIGADO AO D7 DO DISPLAY
sbit LCD_D6 at RD6_bit;  // PINO 6 DO PORTD LIGADO AO D6 DO DISPLAY
sbit LCD_D5 at RD5_bit;  // PINO 5 DO PORTD LIGADO AO D5 DO DISPLAY
sbit LCD_D4 at RD4_bit;  // PINO 4 DO PORTD LIGADO AO D4 DO DISPLAY

// Selecionando dire��o de fluxo de dados dos pinos utilizados para a comunica��o com display LCD
sbit LCD_RS_Direction at TRISE2_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 2 DO PORTD
sbit LCD_EN_Direction at TRISE1_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 3 DO PORTD
sbit LCD_D7_Direction at TRISD7_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 7 DO PORTD
sbit LCD_D6_Direction at TRISD6_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 6 DO PORTD
sbit LCD_D5_Direction at TRISD5_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 5 DO PORTD
sbit LCD_D4_Direction at TRISD4_bit;  // SETA DIRE��O DO FLUXO DE DADOS DO PINO 4 DO PORTD

void main() {

   unsigned int  uiContador;   // Variavel de armazenamento do contador.
   unsigned int  uiValor;      // Variavel auxiliar para exibi??o do contador.
   unsigned char ucStatus_inc; // Variavel de travamento do incremento.
   int last = 0;
   unsigned int  AD;     // Variavel que armazena o valor do A/D.
   //ADCON1 = 0x0E;       // Configura todos canais como Digital.
   UART1_Init(9600);
   TRISB.RB0=1;
   ucStatus_inc = 0;         // Define o pino RB0 do PORTB como entrada.

   PORTA = 255;
   TRISA = 255;                 // Configura PORTA pins como entrada

   ADCON0 = 0b00000001;  // Configura conversor A/D Canal 0, convers�o desligada, A/D ligado.
   ADCON1 = 0b11001110;  // Configura todos canais como Digital menos AN0 e REF Interna.
   ADCON2 = 0b10111110;  // Configura conversor A/D para resultado justificado a direita, clock de 20 TAD, clock de Fosc/64.

   uiContador=0;        // Inicializa a variavel com o valor 0.
   uiValor = 0;

     Lcd_Init();                               //Inicializa m�dulo LCD
     Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
     Lcd_Cmd(_LCD_CLEAR);                      //Limpa display
     


   PWM1_Init(5000);      // Inicializa m�dulo PWM com 5Khz
   PWM1_Start();         // Start PWM

   while(1){
   if((PORTB.RB0==0)&&(ucStatus_inc==0)){       // Incrementa somente uma vez quando a tecla for pressionada.
         uiContador++;
         ucStatus_inc=1;
         }
      if((PORTB.RB0==1)&&(ucStatus_inc==1)){   // Volta a disponibilizar a op??o de incremento quando a tecla for solta.
         ucStatus_inc=0;
      }
      delay_ms(100);
      uiValor = uiContador%2;
     if (uiValor == 0){
        if(last == 1){
                Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
                Lcd_Cmd(_LCD_CLEAR);
        }
        lcd_out(1,3,"KENJIMOVEL");
        lcd_out(2,4,"PARADO");
        last = 0;
        PWM1_Set_Duty(0);


        }else{
        if(last == 0){
                Lcd_Cmd(_LCD_CURSOR_OFF);                 //Apaga cursor
                Lcd_Cmd(_LCD_CLEAR);
        }
        lcd_out(1,3,"KENJIMOVEL");
        lcd_out(2,4,"RODANDO");
        last = 1;
        AD= ADC_Read(0);     // L� Canal AD 0
        AD*=0.24;            // Converte valor para o duty cycle
        PWM1_Set_Duty(AD);   // Envia o valor lido de "uiValorAD" para o m�dulo CCP1 pwm
        Delay_10us;
        }
        


        UART1_Write(uiContador);
   }
}
 