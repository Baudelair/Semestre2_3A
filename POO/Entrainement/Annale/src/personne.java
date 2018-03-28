
public class personne {
	private int id;
	private String nom;
	private String prenom;
	
	public personne (int id, String nom, String prenom) {
		this.id=id;
		this.nom = nom;
		this.prenom = prenom;
	}
	
	public void afficher () {
		System.out.println("afficher personne");
	}
}
