import java.awt.Color ;
import java.util.Stack;

public class Robot {

    /* 
     *  Les attributs de chaque Robot. 
     */

    /** Position du robot */
    protected int x, y ;

    /** Vitesse du robot */
    protected int vx, vy ;

    /** Etat du robot */
    private boolean vivant ;

    /** Sprite (==image) representant le robot */
    private Sprite image ;
    
    /** Plateau sur lequel le robot evolue */
    private Plateau plat ;

    /** Ce robot est-il arrete' ? */
    private boolean arrete ;

    private java.awt.Color col;
    
    private int count ;
    
    private int num_serie;
    
    private static int nbexplose = 0;
    private static final int maxExplosions = 3 ;	
    
    private static int nbRobots = 1;
    
    public static Logs logsCollision = new Logs();
    public static Logs logsExplosion = new Logs();
   

    /* 
     *  Constructeur de Robot. 
     */

    /** Cree un nouveau robot avec l'image indiquee, a la position indiquee sur le plateau
     *  La vitesse de depart est aleatoire
     */
    public Robot (String nomImage, int init_x, int init_y, Plateau pt, java.awt.Color color, int num_ser) {
		this.x = init_x ;
		this.y = init_y ;
		this.vivant = true ;
		this.vx = this.randomV() ;
		this.vy = this.randomV() ;
		this.plat = pt ;
		this.image = pt.addSprite (nomImage, this.x, this.y) ;
		this.arrete = false ;
		this.col= color;
		this.count=0;
		this.num_serie= nbRobots;
		nbRobots++;
		
    }

    /*
     *  MÃ©thodes
     */


    /** Renvoie une valeur de vitesse aleatoire */
    public int randomV() { return (int)(Math.random() * 6) - 3 ; }

    /** Recupere la largeur de l'image du robot */
    public int getLarg() { return this.image.getLarg() ; }

    /** Recupere la hauteur de l'image du robot */
    public int getHaut() { return this.image.getHaut() ; }


    /** Effectue un deplacement elementaire du robot */
    public void bouge() {

	if (this.vivant) {
		
		this.count= this.count +1;
		plat.setColor(this.col);
		
		if (this.count==5) {
			plat.drawCircle(this.x, this.y, 3);
			this.count=0;
		}
		
	    this.x += this.vx ;
	    this.y += this.vy ;
	    	    
	    // Si le robot rejoint un bord de la fenetre, il rebondit et change de direction
	    int futurX = this.x + this.vx ;
	    int futurY = this.y + this.vy ;
	    
	    // Collision avec le bord gauche
	    if (futurX < 0) {
		this.vx = Math.abs(this.vx) ;
		this.vy = this.randomV() ;
	    }

	    // Collision avec le bord droit
	    if (futurX + this.getLarg() > this.plat.getLarg()) {
		this.vx = -Math.abs(this.vx) ;
		this.vy = this.randomV() ;
	    }

	    // Collision avec le bord haut 
	    if (futurY < 0) {
		this.vy = Math.abs(this.vy) ;
		this.vx = this.randomV() ;
	    }

	    // Collision avec le bord bas
	    if (futurY + this.getHaut() > this.plat.getHaut()) {
		this.vy = -Math.abs(this.vy) ;
		this.vx = this.randomV() ;
	    }
	}

	// Redessine le robot au nouvel endroit
	// Force a redessiner, meme si le robot n'a pas bouge.
	this.image.moveTo(this.x, this.y) ;

    }

    
    /** Teste si ce robot est en collision avec le robot 'autre' */
    public void testeCollision(Robot autre) {

	// Pour etre en collision, il faut une intersection sur les X ET sur les Y
	boolean enCollision = ((this.x + this.getLarg() >= autre.x) && (this.x < autre.x + autre.getLarg()) &&
			       (this.y + this.getHaut() >= autre.y) && (this.y < autre.y + autre.getHaut())) ;

	// Si on est en collision avec un robot different de soi-meme, on reagit et l'autre aussi.
	if (this.vivant && autre.vivant && (autre != this) && enCollision) {

	    // Si les deux robots sont deja arretes, on ne fait rien.
	    if (this.arrete && autre.arrete) {}
	    else {
		this.collision(autre) ;
		autre.collision(this) ;
	    }
	}
    }

    /** ArrÃªter ce robot. */
    public void arreterRobot() {
	this.vx = 0 ;
	this.vy = 0 ;
	this.arrete = true ;
    }

    /** Fait exploser ce robot */
    public void explose(Robot autre) {
    	nbexplose++;
    	this.image.playSequence(Images.explosion, false) ;
    	this.vivant = false ;
       	Robot.logsExplosion.add(" Explosion entre " + this.num_serie + " et " +autre.num_serie, this, autre);
    }

    /** Reaction a une collision : on s'arrete */
    /** Affiche le String à la place des this et autre */
    public void collision(Robot autre) {
    	this.direBonjour(autre);
    	Robot.logsCollision.add(" Collisions entre " + this.num_serie + " et " +autre.num_serie, this, autre);
    	System.out.println("Collision entre : " + this + " et "+ autre);
    	this.arreterRobot() ;
    	
    }
    
    public  String  toString() {
    	return "ROBOT x : " + this.x + ", y : " + this.y; 
    }
    
    public int getserie () {
    	return(this.num_serie);
    }
    
    public void direBonjour(Robot autre) {
    	LogLine l = logsCollision.trouveLigne(this, autre);
    	if(l != null) {
    		System.out.println("Rebonjour, on s'est déjà croisé le " + l.date);
    	}
    	else {
    		System.out.println("Bonjour, on ne se connaît pas!");
    	}
    }
    
    Stack<Robot> pileRobot = new Stack<Robot> () ;
}
