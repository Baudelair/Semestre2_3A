import java.io.IOException;

public class Main {
	
	private static int i;
	
	public static void main(String[] args) throws IOException {
		personne[] pers;
		
		pers = new personne[3];
		
		pers[0] = new personne(0, "abc", "def");
		pers[1] = new personne(1, "def", "azfd");
		pers[2] = new personne(2, "fnjf", "azfakf");
		
		for(i=0; i < 3; i++) {
			pers[i].afficherActivites();
		}
		
	}
}


//mettre en abstact la classe personne de tel sorte à ce que l'on puisse récupérer l'id de chaque personne 
//les activites et les taches 