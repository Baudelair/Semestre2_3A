package exo;

public class testexo {
	private final int Max=99;
	private int tableau[]=new int[Max];
	
	public testexo(int n) {
		for(int i=0;i<n;i++)
			tableau[i]=i;
	}
	
	public int sommeDesNPremiers (int n) {
		int resultat =0;
		for(int i=0; i<n;i++)
			resultat+=tableau[i];
		return resultat;
	}
}
