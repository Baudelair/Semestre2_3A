#include "gassp72.h"
#include "etat.h"

type_etat etat;
void timer_callback(void);

int main(void)
{
	
		extern short Son[];
		extern short LongueurSon;
		extern short PeriodeSonMicroSec;
	
		//int freq_voulue = 1/0.000000091;
		int Periode_en_Tck = 72;
		// Dans le fichier son, on poss�de la periode du son en microsecondes. Par exemple, pour bruitverre, la periode est de 91 microsecondes.
		// Il faut transformer �a en nombre de periodes de CPU. Une periode de CPU = 1/72MHz. => Nb_periodes_CPU = 91*72.


		// config TIM3-CH3 en mode PWM
		etat.taille = LongueurSon;
		etat.periode_ticks = Periode_en_Tck*PeriodeSonMicroSec;
		etat.position= 0;
		etat.son=Son;
		etat.resolution = PWM_Init_ff( TIM3, 3,etat.periode_ticks  );
			
		// activation de la PLL qui multiplie la fr�quence du quartz par 9
		CLOCK_Configure();
		// config port PB0 pour �tre utilis� par TIM3-CH3
		GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
		// initialisation du timer 4
		// Periode_en_Tck doit fournir la dur�e entre interruptions,
		// exprim�e en p�riodes Tck de l'horloge principale du STM32 (72 MHz)
		Timer_1234_Init_ff( TIM4, etat.periode_ticks );
		// enregistrement de la fonction de traitement de l'interruption timer
		// ici le 2 est la priorit�, timer_callback est l'adresse de cette fonction, a cr��r en asm,
		// cette fonction doit �tre conforme � l'AAPCS
		Active_IT_Debordement_Timer( TIM4, 2, timer_callback );

		// config port PB1 pour �tre utilis� en sortie
		GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
		
		// lancement du timer
		Run_Timer( TIM4 );

		while(1);
}
