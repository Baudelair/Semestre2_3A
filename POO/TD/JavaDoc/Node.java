import java.io.IOException;

public abstract class Node {
	
	public String chemin;  		
	public String nom; 			
	public long taille;
	
	public Node(String chemin, long taille) throws IOException {
		this.chemin = chemin;
		this.taille = taille;
		this.nom=FileInfo.getName(chemin);
	}
	
	public abstract void afficher() ;
	
}