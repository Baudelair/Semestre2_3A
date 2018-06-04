// projet sin HD : interpolation

int sin_q24( int a );


int main(void)
{
int vtest[10];

// on vise la seconde valeur de la table (0xc910)
vtest[0] = sin_q24( 1 * (1<<14) );

// on vise entre la premiere et le seconde valeur de la table
// on attend la moitie de 0xc910 soit 0x6488
vtest[1] = sin_q24( (1<<13) );

// on vise entre la 2nde (0xc910) et la 3eme valeur (0x1921d) de la table
vtest[2] = sin_q24( 3 * (1<<13) );

// 30 degres (pi/6) soit (1<<24)/12 = 1398101
vtest[3] = sin_q24( 1398101 );

vtest[4] = sin_q24( -524 * (1<<14) );
vtest[5] = sin_q24( -1012 * (1<<14) );
vtest[6] = sin_q24( -1024 * (1<<14) );
vtest[7] = sin_q24( (1024+159) * (1<<14) );
vtest[8] = sin_q24( (2048+524) * (1<<14) );
vtest[9] = sin_q24( (65536+159) * (1<<14) );

while (1) {}
}
