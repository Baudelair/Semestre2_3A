import java.io.IOException;

public abstract class Node {
	
	public String cheminFichier;  		//"C:\\Users\\Manu\\Documents\\Cours\\Semestre 2\\POO\\TD\\JavaDoc";
	public String nomFichier; 			//"fichier.txt";
	public long tailleFichier;
	
	public Node(String chemin) throws IOException {
		this.cheminFichier = chemin;
		this.tailleFichier = FileInfo.size(chemin);
	}
	
	public abstract void afficher() ;
	
}