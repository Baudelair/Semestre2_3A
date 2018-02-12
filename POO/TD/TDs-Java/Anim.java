/** Boucle principale de la simulation */
import java.awt.* ;
public class Anim {

    /** Effectue une pause de la duree indiquee en millisecondes */
    public static void pause(int duree) {
	try {
	    Thread.currentThread().sleep(duree) ;
	} catch (InterruptedException e) {
	} 
    }

    /** Boucle principale */
    public void go() {
	
	Plateau plat ;
	Robot[] robots ;

	plat = new Plateau(800, 600) ;
	robots = new Robot[4] ;

	robots[0] = new Robot("Images/mini1.png", 80, 100, plat, Color.yellow) ; 
	robots[1] = new Robot("Images/mini2.png", 480, 250, plat, Color.blue) ; 
	robots[2] = new Robot("Images/mini3.png", 280, 400, plat, Color.green) ; 
	robots[3] = new Cyborg("Images/mini4.png", 100, 300, plat, Color.pink);


	// On repete la boucle d'animation sans arret
	while (true) {

	    // On fait evoluer chaque robot
	    for (int i = 0 ; i < robots.length ; i++) {
		robots[i].bouge () ;
	    }

	    // Puis on teste les collisions deux a deux
	    for (int i = 0 ; i < robots.length ; i++) {
		for (int j = i+1 ; j < robots.length ; j++) {
		    robots[i].testeCollision(robots[j]) ;
		}
	    }

	    // Petite pause
	    this.pause(12) ;
	    
	}

    }
    

    public static void main(String[] args) {
	Anim an = new Anim() ;
	Images.init () ;
	an.go () ;
    }

}
