// projet sin HD

int sin_q10( int a );


int main(void)
{
int vtest[10];

// angles negatifs
vtest[0] = sin_q10( -159 );
vtest[1] = sin_q10( -256 );
vtest[2] = sin_q10( -500 );
vtest[3] = sin_q10( -512 );
vtest[4] = sin_q10( -524 );
vtest[5] = sin_q10( -1012 );
vtest[6] = sin_q10( -1024 );
// angles > 2pi
vtest[7] = sin_q10( 1024+159 );
vtest[8] = sin_q10( 2048+524 );
vtest[9] = sin_q10( 65536+159 );

while (1) {}
}
