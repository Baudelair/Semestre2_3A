#include "gassp72.h"
#include "etat.h"

// Variables du son
extern void NextValue(void);
extern void PwmTick(void);
extern u32 LongueurSon;
extern u32 PeriodeSonMicroSec;
extern u16 Son[];
type_etat etat;

// Variables observables
u32 result;

// Variables DFT
unsigned short dma_buf[64] = {0};
int tab_laser[6] = {17, 18, 19, 20, 23, 24};
int tab_occu[6] = {0};

extern u32 DFT(int k); //int tab_freq[], int tab_stock[]);

// Variables jeu
int M2TIR = 1;
void scan_tir();
int SYSTICK_PER = 360000;
int led;
int k;


int main(void)
{
	
	// Nbre de ticks
	u32 Periode_SON_en_Tck = PeriodeSonMicroSec * 72 ;
	u32 Periode_PWM_en_Tck = Periode_SON_en_Tck / 10;
	// Init de etat
	etat.position = 10472;
	etat.taille = LongueurSon;
	etat.son = Son;
	etat.periode_ticks = Periode_SON_en_Tck;
	// config port PB0 pour être utilisé par TIM3-CH3
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	// config TIM3-CH3 en mode PWM
	etat.resolution = PWM_Init_ff( TIM3, 3, Periode_PWM_en_Tck );	
	// config port PB1 pour être utilisé en sortie
	//GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// initialisation du timer 4
	// Periode_en_Tck doit fournir la durée entre interruptions,
	// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
	Timer_1234_Init_ff( TIM4, Periode_SON_en_Tck);
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créer en asm,
	// cette fonction doit être conforme à l'AAPCS
	Active_IT_Debordement_Timer( TIM4, 2, NextValue);
	// init du timer 3 pour le PWM
	Timer_1234_Init_ff( TIM3, Periode_PWM_en_Tck);
	// lancement des timers
	Run_Timer( TIM4 );
	Run_Timer( TIM3 );
	
	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entrée analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage à l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	// Déclenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	// Config DMA pour utilisation du buffer dma_buf (a créér)
	Init_ADC1_DMA1( 0, dma_buf );

	// Config Timer, période exprimée en périodes horloge CPU (72 MHz)
	Systick_Period_ff( SYSTICK_PER );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorité, sys_callback est l'adresse de cette fonction, a créér en C
	Systick_Prio_IT( 3, scan_tir);
	SysTick_On;
	SysTick_Enable_IT;
	
	while(1){}
}

void scan_tir(){
	GPIO_Set(GPIOB, 1);
	// Démarrage DMA pour 64 points
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	// On effectue les 6 DFT
	for (k = 0; k < 6; k++){
		if (DFT(tab_laser[k]) > 10){
			tab_occu[k]++;
		} else {
			tab_occu[k] = 0;
		}
	}
	// On allume/éteint la LED
	led = 0;
	
	for (k = 0; k < 6; k++){
		if (tab_occu[k] > M2TIR && k == 3){
			led++;
		}
	}
	if (led > 0){
		GPIO_Set(GPIOB, 14);
		etat.position = 0;
	} else {
		GPIO_Clear(GPIOB, 14);
	}
	
	GPIO_Clear(GPIOB, 1);
}	
