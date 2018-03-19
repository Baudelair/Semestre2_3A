class Cyborg extends Robot {
	
	private int nb_collisions;
	private int max_collisions;
	public Cyborg (String nomImage, int init_x, int init_y, Plateau pt, java.awt.Color color, int num_serie) {
		super (nomImage, init_x, init_y, pt, color, num_serie) ;
		this.max_collisions=6;
		int nb_collisions=0;
	    }
	
	public Cyborg (String nomImage, int init_x, int init_y, Plateau pt, java.awt.Color color, int num_serie, int max_col) {
		super (nomImage, init_x, init_y, pt, color, num_serie) ;
		this.max_collisions=max_col;
		int nb_collisions=0;
	    }
	
	public void collision(Robot autre) {
		this.vx = this.randomV() ;
		this.vy = this.randomV() ;
		this.nb_collisions= nb_collisions+1;
		if(this.nb_collisions<this.max_collisions) {
			this.explose(autre);
		}
	}
}