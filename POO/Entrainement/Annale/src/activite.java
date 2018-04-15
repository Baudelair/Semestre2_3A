import java.util.ArrayList;
public class activite {
     
     private String intitule;
     private static int nombreActivite;
     private ArrayList <tache>listeTaches;
     
     public activite(String intitule){
          this.intitule=intitule;
          listeTaches=new ArrayList<tache>();
          
          nombreActivite++;
     }
     
     public static int getnombreActivite(){
          return nombreActivite;
     }
        
     public void addTache(tache t){
          this.listeTaches.add(t);
     }
     public int getNombreTaches(){
          return this.listeTaches.size();
     }
     
     public String toString(){
//comme pour le TD sur les robots, il faut retourner les   informations d'une activité
    	     return "Intitule " + this.intitule;
     }
     //...
 
}
