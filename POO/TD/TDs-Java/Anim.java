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

	plat = new Plateau(1080, 800) ;
	robots = new Robot[9] ;

	robots[0] = new Robot("Images/mini1.png", 80, 100, plat, Color.blue,0) ; 
	robots[1] = new Robot("Images/mini1.png", 480, 250, plat, Color.blue,1) ; 
	robots[2] = new Robot("Images/mini1.png", 280, 400, plat, Color.blue,2) ; 
	robots[3] = new Cyborg("Images/mini2.png", 100, 300, plat, Color.pink,3);
	robots[4] = new Cyborg("Images/mini2.png", 160, 450, plat, Color.pink, 4, 5);
	robots[5] = new Cyborg("Images/mini2.png", 92, 532, plat, Color.pink,5 ,15);
	robots[6] = new Indestructible("Images/mini3.png", 480, 300, plat, Color.black, 6);
	robots[7] = new Indestructible("Images/mini3.png", 480, 450, plat, Color.red, 7);
	robots[8] = new Indestructible("Images/mini3.png", 80, 250, plat, Color.red, 8);
	//robots[9] = new Indestructible("Images/mini4.png", 1000, 700, plat, Color.yellow, 9);


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
