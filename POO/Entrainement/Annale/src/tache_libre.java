/*
import java.io.IOException;
import java.util.Calendar;

public class tache_libre extends tache {
	
	private int dateRealisation;
	private int dureeMoy;
	private int dateDebut;
	
	Calendar dt = Calendar.getInstance();

	public tache_libre(String descriptif, int duree) throws IOException {
		super(descriptif,duree );
		this.dateDebut = dt.get(Calendar.HOUR_OF_DAY);
		this.dateRealisation = duree;
		this.dureeMoy = dureeMoy;
	}
	
	public void afficher()
	{
		
	}
}
*/

public class tache_libre extends tache{
     private int duree;
     
     public tache_libre(String descriptif,int duree) {
          super(descriptif);
          this.duree=duree;
     }
 
     @Override
     public void setBonus() {
          // Implémentation de la méthode
          
     }
     
//...
}


