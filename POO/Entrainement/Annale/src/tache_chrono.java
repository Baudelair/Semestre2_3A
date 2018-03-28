import java.io.IOException;
import java.util.Calendar;

public class tache_chrono extends tache {
	
	private int dateEcheance;
	private int date;
	
	Calendar dt = Calendar.getInstance();

	public tache_chrono(String descriptif, int duree) throws IOException {
		super(descriptif);
		this.dateDebut = dt.get(Calendar.HOUR_OF_DAY);
		this.dateEcheance = dateDebut + duree;
		this.date = dt.get(Calendar.DATE);
	}
}