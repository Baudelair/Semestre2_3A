#include "gassp72.h"
#include "stdio.h"
#include "etat.h"
int M2(unsigned short * signal, short k); 

extern short LeSignal;
unsigned  short dma_buf[64];
int compt[6] = {0};
int M2TIR = 40000;// seuil deteciton tir
int valk[6] = {17,18,19,20,23,24}; // la moitié de la valeur correspond à la valeur d'un pistolet (*100000)
type_etat etat;
void timer_callback(void);

unsigned int SYSTICK_PER=72000000*0.005 ; //pour 5 ms

int res[64] ;

int score[6] = {0};

void sys_callback(){
		GPIO_Set(GPIOB, 1);// ouvre sortie pour observation a l oscillo
		Start_DMA1(64);
		Wait_On_End_Of_DMA1();
		Stop_DMA1;
	
		//calcul DFT
	


		for (int k=0;k<64;k++){	// FAIRE JUSTE VALEURS INTERESSANTES DE K
				res[k] =M2(dma_buf, k);
		}
		
		
		//mise a jour compteurs selon dft
		for (int i=0;i<6;i++){
				if (res[valk[i]]>M2TIR){
						compt[i]++;
						if (compt[i]==6){
							score[i]++;
							// lancement du son
							etat.position = 0;
						}
				}
				else{
						compt[i]=0;
				}
		}
		
		GPIO_Clear(GPIOB, 1);
}


int main(){
		extern short Son[];
		extern short LongueurSon;
		extern short PeriodeSonMicroSec;
		int Periode_en_Tck = 72;
	
		etat.taille = LongueurSon;
		etat.periode_ticks = Periode_en_Tck*PeriodeSonMicroSec;
		etat.position= 0;
		etat.son=Son;
		etat.resolution = PWM_Init_ff( TIM3, 3,etat.periode_ticks  );
		
		// activation de la PLL qui multiplie la fréquence du quartz par 9
		CLOCK_Configure();
		// PA2 (ADC voie 2) = entrée analog
		GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
		// PB1 = sortie pour profilage à l'oscillo
		GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
		// PB14 = sortie pour LED
		GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);
		// config port PB0 pour être utilisé par TIM3-CH3
		GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
		// activation ADC, sampling time 1us
		Init_TimingADC_ActiveADC_ff( ADC1, 72 );
		Single_Channel_ADC( ADC1, 2 );
		// Déclenchement ADC par timer2, periode (72MHz/320kHz)ticks
		Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
		// Config DMA pour utilisation du buffer dma_buf (a créér)
		Init_ADC1_DMA1( 0, dma_buf );


		// initialisation du timer 4
		// Periode_en_Tck doit fournir la durée entre interruptions,
		// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
		Timer_1234_Init_ff( TIM4, etat.periode_ticks );
		// enregistrement de la fonction de traitement de l'interruption timer
		// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créér en asm,
		// cette fonction doit être conforme à l'AAPCS
		Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
		// config port PB1 pour être utilisé en sortie
		GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
		
		// lancement du timer
		Run_Timer( TIM4 );

		// Config Timer, période exprimée en périodes horloge CPU (72 MHz)
		Systick_Period_ff( SYSTICK_PER );
		// enregistrement de la fonction de traitement de l'interruption timer
		// ici le 3 est la priorité, sys_callback est l'adresse de cette fonction, a créér en C
		Systick_Prio_IT( 3, sys_callback );
		SysTick_On;
		SysTick_Enable_IT;
		
	
	
	



		while(1){
				if(compt[0]>0 ||compt[1]>0 ||compt[2]>0 ||compt[3]>0 ||compt[4]>0 || compt[5]>0){
						 GPIO_Set(GPIOB,14);
				}
				else{
							GPIO_Set(GPIOB,14);
				}
		}
		

}
