/*=============================================================================*\
  APN: Тестирование работы с параллельнми портами на плате Discovery
c МК STM32F10xRB
  
  Конфигурация [ParP-Regs] - использует технику работы с параллельными
портами путем обращения напрямую к регистрам.

на Discovery - СвДиоды подкл. к выводам PC8(гол) и PC9(зел)
             - кнопка к выводу PA0, при нажатой на PA0 - Лог.1

             
 \*=============================================================================*/

// ---- Директивы #include подключают заголовочные файлы -----------------------
#include <stm32f10x.h>

// ---- Директивы #define - определения констант и макросов 

// ---- Глобальные переменные -----------------------------------------


    // ----- Function definitions --------------------------------------------
void Delay(u32 uiTDel) 
  {
    while (uiTDel--) {} 
  }	

    // ===== Function main() =================================================
int main(void)
{  	//  Разрешение тактирования порта А и порта С 
    // (к (разным)выводам этих портов на платах подключены кнопка User и СвДиоды)
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;        

    //  Включение режима "вывод" для светодиода
  GPIOC->CRH = 0x44444443;  //  Вывод PC8 - для управления USER СД Discovery

  while(1) 
  {
    GPIOC->ODR ^=1<<8;      //  USER СвДиод Discovery (1 - горит)
    Delay(1000000);
    //  Остановка в конце диагр. по нажатию кнопки USER
		while(((GPIOA->IDR)&(1<<0)) ==(1<<0))    
      {             //  USER кнопка Discovery к PA0 (нажата - 1)
        __NOP();    //  см. core_cmInstr.h, строки 321++
      }             // чтобы можно было поставить "точку останова"
  }
//	return 0;
}
