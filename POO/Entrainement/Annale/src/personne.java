/*
public class personne {
	private int id;
	private String nom;
	private String prenom;
	private static int i;
	
	public personne (int id, String nom, String prenom, int nbActivite) {
		this.id=id;
		this.nom = nom;
		this.prenom = prenom;
		
		activite[] act;
		act = new activite[nbActivite];
		
		
		
		if( nbActivite != 0) {
			for(i=0; i < (nbActivite+1); i++) {
				act[i] = new activite("bonjour", 1);
				act[i].afficher();
			}
		}
	}
	
	
	
	public void afficher () {
		System.out.println("nom " + this.nom + " prenom " + this.prenom);
	}
}*/

import java.util.ArrayList;
 
public class personne {
     private int numIdentite;
     private String nom;
     private String prenom;
     private ArrayList<activite> listeActivites;
     private ArrayList<tache> listeTaches;
     
     public personne(int numIdentite,String nom, String prenom){
          this.numIdentite=numIdentite;
          this.nom=nom;
          this.prenom=prenom;
          this.listeActivites=new ArrayList<activite>();
          this.listeTaches=new ArrayList<tache>();
     }
     
     public void afficherActivites(){
    	 for( activite a : listeActivites)
    	 {
    	 	if (a.accompli)
    	 	{
    		 	System.out.println("	" + activite.toString());
    		 	System.out.println("		" + tache.toString());	
    	 	}
    	 }
          
     }
     
     public void afficherTachesRealisees(){
          //afficher les taches réalisée
     }
     
     public void afficherTachesRetard(){
          //afficher les taches en retard 
     }
     
     public int getBonus(){
          //faire la somme des bonus des différentes taches
          return 0;
     }
     
     //...
     
}

