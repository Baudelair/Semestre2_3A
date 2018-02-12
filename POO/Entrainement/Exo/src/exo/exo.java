package exo;

public class exo {
	public static void main(String [] args) {
		testexo cm = new testexo(10);
		int n=500;
		int resultat;
		
		resultat =cm.sommeDesNPremiers(n);
		System.out.println("La somme des "+n+" premiers nombres est : "+resultat);
	}
}
