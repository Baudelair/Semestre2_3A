import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

public class Dossier extends Node {
	
	private ArrayList<Node> listeNode = new ArrayList<>();
	private String cheminsuiv;
	

	public Dossier(String chemin) throws IOException {
		super(chemin, 0);
		
		if (FileInfo.isDirectory(chemin)) {
			this.afficher();
			for(Iterator<String> iteration = FileInfo.getElements(chemin); iteration.hasNext();) //Pour chaque element du dossier
			{
				this.cheminsuiv = iteration.next();
				
				if(FileInfo.isFile(cheminsuiv)) 
				{
					Fichier fic = new Fichier(cheminsuiv);
					fic.afficher();
				}
				
				else
				{
					Dossier dos = new Dossier(cheminsuiv);
					dos.afficher();
				}
			}
		}
	}

	@Override
	public void afficher() {
		System.out.println("nom Dossier : " + this.nom + ", taille : " + this.taille);
		
	}
	
	
}