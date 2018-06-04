// projet sin HD

int sin_2pi( int a );


int main(void)
{
int vtest[8];

vtest[0] = sin_2pi( 159 );
vtest[1] = sin_2pi( 256 );
vtest[2] = sin_2pi( 12 );
vtest[3] = sin_2pi( 500 );  // 500  = 512-12
vtest[4] = sin_2pi( 512 );
vtest[5] = sin_2pi( 524 );  // 524  = 512+12
vtest[6] = sin_2pi( 1012 ); // 1012 = 1024-12
vtest[7] = sin_2pi( 1024 );

while (1) {}
}
