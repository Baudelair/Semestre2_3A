#include "gassp72.h"
#include "etat.h"

type_etat etat;
	extern short Son[];
	extern short LongueurSon;
void timer_callback(void);
int main(void)
{
	
	


	
	
		int freq_voulue = 1/0.000000091;
		int Periode_en_Tck = 36000000/freq_voulue;
	//36000 donne une ms

// config TIM3-CH3 en mode PWM
etat.taille = LongueurSon;

etat.periode_ticks = 2*Periode_en_Tck;
etat.position= 0;
etat.son=Son;
etat.resolution = PWM_Init_ff( TIM3, 3,etat.periode_ticks  );
	
// activation de la PLL qui multiplie la fréquence du quartz par 9
CLOCK_Configure();
// config port PB1 pour être utilisé en sortie
GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
// initialisation du timer 4
// Periode_en_Tck doit fournir la durée entre interruptions,
// exprimée en périodes Tck de l'horloge principale du STM32 (72 MHz)
Timer_1234_Init_ff( TIM4, Periode_en_Tck );
// enregistrement de la fonction de traitement de l'interruption timer
// ici le 2 est la priorité, timer_callback est l'adresse de cette fonction, a créér en asm,
// cette fonction doit être conforme à l'AAPCS
Active_IT_Debordement_Timer( TIM4, 2, timer_callback );

 // config port PB0 pour être utilisé par TIM3-CH3
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

// lancement du timer
Run_Timer( TIM4 );





while(1){
	if (etat.position == etat.taille*2){
		etat.position = 0;
	}
}
	
}
