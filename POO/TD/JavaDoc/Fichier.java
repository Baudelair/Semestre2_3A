import java.io.IOException;

public class Fichier extends Node {
	
	
	public Fichier(String chemin) throws IOException {
		super(chemin);
		// TODO Auto-generated constructor stub
	}
	
	public void afficher() {
		System.out.println("nom : " + this.nomFichier + ", taille : " + this.tailleFichier);
	}
	
}