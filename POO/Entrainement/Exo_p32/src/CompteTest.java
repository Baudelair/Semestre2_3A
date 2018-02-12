
public class CompteTest {

	public static void main(String [] args){ 
	Compte C1 = new Compte(1, 10f); 
	Compte C2 = new Compte(2, 10000f); 
	
	System.out.println("Nombre de compte : "+ Compte.nbCompte); 
	
	C1.Retirer(245f);
	System.out.println("Solde compte :" +C1.solde);
	C2.Retirer(C1.solde);
	System.out.println("Solde compte :" + C2.solde);
	} 
}
