class Cyborg extends Robot {
	public Cyborg (String nomImage, int init_x, int init_y, Plateau pt, java.awt.Color color) {
		super (nomImage, init_x, init_y, pt, color) ;
	    }
	
	public void collision(Robot autre) {
		this.bouge() ;
	    }
}