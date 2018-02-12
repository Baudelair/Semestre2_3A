
public class Eleve {
	private String nom;
	private int age;
	
	
	public Eleve(String leNom, int leAge) {
		this.nom= leNom;
		this.age= leAge;
	}
	
	public void sePresenter() {
		System.out.println("Nom :" + this.nom);
		System.out.println("Age :" + this.age);
	}
	
	/*
	private String getNom() {
		return nom;
	}
	public void setNom(String nom) {
		this.nom = nom;
	}
	public int getAge() {
		return age;
	}
	public void setAge(int age) {
		this.age = age;
	}*/

}


