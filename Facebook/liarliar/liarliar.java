import java.io.*;
import java.util.*;

public class liarliar {	
	
	static class Node {
		Node rep;
		Node opp;
		int size;

		static Node NULL = new Node(0);
		static {
			NULL.opp = NULL;
		}
		
		Node(int sz) {
			rep = this;
			opp = NULL;
			size = sz;
		}
			
		Node rep() {
			return (rep == this ? this : (rep = rep.rep()));
		}
		
		static void oppose(Node n1, Node n2) {
			if (n1.opp != n2) {
				n1.size += n2.opp.size;
				n2.size += n1.opp.size;
				n1.opp = n1.opp.rep = n2;
				n2.opp = n2.opp.rep = n1;
			}
		}
	}
	
	Map<String, Node> map = new HashMap<String, Node>();

	Node get(String k) {
		Node n = map.get(k);
		if (n == null) {
			map.put(k, n = new Node(1));
		}
		return n.rep();
	}
	
	void solve(Scanner in) {
		Node accuser = Node.NULL;
		for (int n = in.nextInt(); n --> 0;) {
			accuser = get(in.next());
			for (int m = in.nextInt(); m --> 0;) {
				Node.oppose(accuser, get(in.next()));
			}
		}		
		int c1 = accuser.size;
		int c2 = accuser.opp.size;
		System.out.println(Math.max(c1, c2) + " " + Math.min(c1, c2));
	}

	public static void main(String[] args) throws Exception {
		new liarliar().solve(new Scanner(new File(args[0])));
	}
}
