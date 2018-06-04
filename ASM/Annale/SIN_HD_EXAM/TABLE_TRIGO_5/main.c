// projet sin HD : angles en milliemes de degres

int sin_deg( int a );


int main(void)
{
int vtest[10];

vtest[0] = sin_deg( 30000 );    // sin(30deg) = 0.5 --> 0x400000 
vtest[1] = sin_deg( 150000 );
vtest[2] = sin_deg( -30000 );
vtest[3] = sin_deg( 45000 );    // sin(45deg) = 0.7071068 --> 0x5A8278
vtest[4] = sin_deg( -135000 );
vtest[5] = sin_deg( 90000 );
vtest[6] = sin_deg( 180000 );
vtest[7] = sin_deg( -180000 );
vtest[8] = sin_deg( 1 );        // sin(0.001deg) = 1.745e-5 --> 0x92
vtest[9] = sin_deg( 2 );

while (1) {}
}
