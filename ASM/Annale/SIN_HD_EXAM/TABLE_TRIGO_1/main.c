// projet sin HD : utilisation d'une table limitee a pi/2

int sin_pi( int a );


int main(void)
{
int vtest[5];

vtest[0] = sin_pi( 159 );
vtest[1] = sin_pi( 256 );
vtest[2] = sin_pi( 12 );
vtest[3] = sin_pi( 500 ); // 500 = 512-12
vtest[4] = sin_pi( 512 );

while (1) {}
}
