import java.util.Date;

public class LogLine {
	
	public Date date;
	private String message;
	public Robot emetteur;
	public Robot tiers;


	public LogLine(String message, Robot emetteur, Robot tiers){
		this.date = new Date();
		this.message = message;
		this.emetteur = emetteur;
		this.tiers = tiers;
		System.out.println("Date : " + this.date + this.message);
	}
	
	/**
	public  String  toString() {
    	return "date : " + this.date + ", message : " + this.message + ", emetteur : " + this.emetteur + ", tiers : " + this.tiers; 
    } */
}

