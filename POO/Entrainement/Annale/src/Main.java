import java.io.IOException;

public class Main {
	
	public static void main(String[] args) throws IOException {
		String chemin = args[0];
		
		Dossier dos = new Dossier(chemin);
		dos.afficher();
	}
}
