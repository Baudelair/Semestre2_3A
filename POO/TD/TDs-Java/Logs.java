import java.util.Stack;

public class Logs {
	
	Stack<LogLine> pileLog = new Stack<LogLine> () ;
	
	public void add(String message, Robot emetteur, Robot tiers) {
		pileLog.push(new LogLine(message, emetteur, tiers));
	}
	
	public void affiche() {
		for (LogLine ligne : pileLog) {
			System.out.println(ligne);
		}
	}
	
	public LogLine trouveLigne(Robot emetteur, Robot tiers) {
		for (LogLine ligne : pileLog) {
			if(ligne.emetteur == emetteur && ligne.tiers == tiers) {
				return (ligne);
			}
		}
		return(null);
	}
}
