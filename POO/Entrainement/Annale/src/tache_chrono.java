/*
import java.io.IOException;
import java.util.Calendar;

public class tache_chrono extends tache {
	
	private int dateEcheance;
	private int date;
	private int dateDebut;
	
	Calendar dt = Calendar.getInstance();

	public tache_chrono(String descriptif, int duree) throws IOException {
		super(descriptif, duree);
		this.dateDebut = dt.get(Calendar.HOUR_OF_DAY);
		this.dateEcheance = dateDebut + duree;
		this.date = dt.get(Calendar.DATE);
	}
	
	public void afficher()
	{
		
	}
}
*/
import java.util.ArrayList;
import java.util.Date;
 
public class tache_chrono extends tache{
     private Date dateEcheance;
     private ArrayList<tache_chrono> tacheDependant;
     
     public tache_chrono(String descriptif, Date dateEcheance) {
          super(descriptif);
          this.dateEcheance=dateEcheance;
     }
 
     @Override
     public void setBonus() {
          if (this.dateRealisation > this.dateEcheance))
          {
          		//tache accompli
          		this.accompli = true;
          		this.bonus ++; 
          }
     }
     
     //...
 }
