
public class Compte {
	public int num;
	public double solde;
	public static int nbCompte=0;
	
	public Compte(int num, double solde) {
		this.num =num;
		this.solde=solde;
		nbCompte++;
	}
	
	public int getNum() {
		return this.num;
	}
	
	public double getSolde() {
		return this.solde;
	}
	
	public void Retirer (double X) {
		if (X<=solde) {
			solde =solde-X;
		}
	}
	

}


