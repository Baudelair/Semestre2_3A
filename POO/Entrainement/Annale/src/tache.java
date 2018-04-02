/*
public abstract class tache {
	
	private int dateDebut;
	private String descriptif;
	private int bonus;
	private int duree;
	
	public tache (String descriptif, int duree) {
		this.descriptif= descriptif;
	}
	
	public abstract void afficher();
}
*/

import java.util.Date;
 
public abstract class tache {
     private String descriptif;
     private int bonus;
     private Date dateDebut;
     private Date dateRealisation;
     
     public tache(String descriptif){
          this.descriptif=descriptif;
          dateDebut=new Date();
     }
     public abstract void setBonus();
     
     
     public void setDateRealisation(Date dr){
          this.dateRealisation=dr;
     }
     
     public String toString(){
          //comme pour le TD sur les robots, il faut retourner les informations d'une tâche
    	 return "Descriptif " + this.descriptif; 
     
     }
     //...
}
