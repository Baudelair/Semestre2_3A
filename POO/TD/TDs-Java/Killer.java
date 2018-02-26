class Killer extends Robot {
	
	protected int x;
	protected int [] coups;
	
	public Killer (String nomImage, int init_x, int init_y, Plateau pt, java.awt.Color color,int num_serie, int nb_robots, int x) {
		super (nomImage, init_x, init_y, pt, color, num_serie) ;
		this.coups = new int [nb_robots];
		this.x=x;
	}
	
	public void collision(Robot autre) {
		this.coups[autre.getserie()]=this.coups[autre.getserie()]+1;
		if((this.coups[autre.getserie()])>=x) {
			autre.explose();
		}
		this.vx = this.randomV() ;
		this.vy = this.randomV() ;
		
	}
}