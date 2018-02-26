// programme pour calculer la somme des carres d'une suite d'entiers consécutifs


int subtest (int i, int j);

int main(void)
{
	int i, j;
	j = 0;
	for	( i = 1; i < 5; ++i)
		j = subtest( i, j );
	while (1) {}
}
