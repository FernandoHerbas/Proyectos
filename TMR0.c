//practicas con el sensor de ultrasonido, aun no terminado
//falta lograr un comunicacion serial o mostrar la distancia en pantalla
//          ALGORITMO
//1.Configurar el pin de comunicación en el microcontrolador como salida.
//2.Escribir un "0" lógico al pin de comunicación.
//3.Esperar un tiempo corto para estabilizar la línea de comunicación (5 µs).
//4.Escribir un "1" lógico al pin de comunicación. (Inicio de pulso de disparo).
//5.Retardo de tiempo (10-15 µs) para lograr el ancho de pulso de disparo del sensor.
//6.Terminar el pulso de disparo escribiendo un "0" lógico al pin de comunicación.
//7.Configurar el pin de comunicación como entrada.
//8.Esperar hasta recibir un "1" lógico en el pin de comunicación. (Inicio del pulso de eco de salida del sensor).
//9.Activar el temporizador del PIC
//10.Esperara hasta recibir un "0" lógico en el pin de comunicación. (Fin del pulso de eco de salida del sensor).
//11.Desactivar el temporizador del PIC.
//12.Leer conteo efectivo en el temporizador en µs.
//13.Calcular la distancia en función a la duración del pulso de eco de salida del sensor.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <18f14k50.h>
#fuses XT,NOPUT,PROTECT,NOBROWNOUT,NOLVP,NOWDT             
#use delay(clock=4M)
#include <LCD1.C>
#include <math.h>
#use standard_io(A)
#use standard_io(B)
#use standard_io(C)

#define PING         PIN_C0
//VARIABLES//////////////////////////
int16 data_sonido;
float distancia;
////////////////////////////////////

void main()
{
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8);  // PREESCALER DE 1:8
  // enable_interrupts(INT_TIMER0);
  // enable_interrupts(GLOBAL);
  lcd_init();                       //inicia el lcd                  
  lcd_gotoxy(1,1);
  printf(LCD_PUTC, "ULTRASONIDO");
   while(true)
   {
   OUTPUT_HIGH(PING);        //el PIN C0 se configura como salida para enviar
   delay_us(10);              //un pulso de 10uS 
   output_low(PING);         //y despues a nivel bajo
   while(!input(PING))          //el PIN C0 se configura como entrada y espera el flanco de subida
    {}
      SET_TIMER0(0);          //inicio el TIMER 0
      while(input(PING));  
      {}
      data_sonido=get_timer0();  //Recibo el valor del TIMER 0 y lo guardo en la variable
      delay_ms(5);               //espero 5 ms para una nueva medida              
      distancia=((data_sonido*10)/58.0); //calculo de la distancia con respecto al tiempo 
      lcd_gotoxy(1,2);
      printf(LCD_PUTC,"\f Distancia = %f",distancia);  //Muestro el valor en el LCD
      delay_ms(500);
      
     
   }
}
