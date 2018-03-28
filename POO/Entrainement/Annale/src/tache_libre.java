import java.io.IOException;
import java.util.Calendar;

public class tache_libre extends tache {
	
	private int dateRealisation;
	private int dureeMoy;

	public tache_libre(String descriptif, int dateReal) throws IOException {
		super(descriptif);
		tache.dateDebut = dt.get(Calendar.DATE);
		this.dateRealisation = dateReal;
		this.dureeMoy = dureeMoy;
	}
}

