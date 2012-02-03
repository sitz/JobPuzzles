import java.io.*;
import java.util.*;

public class swarm {
	static final int MAX_T = 1000;
	static final int MAX_Z = 1000;

	int[] W = new int[MAX_T];
	int[] maxV = new int[MAX_Z + 1];

	int[][] pred = new int[MAX_T][MAX_Z + 1];
	static final int NONE = -1;

	String trace(int r, int c) {
		if (r < 0) {
			return "";
		} else {
			int t = pred[r][c];
			return (t == NONE) ?
				trace(r - 1, c) :
				trace(r - 1, c - W[t]) + " " + t + " " + W[t];
		}
	}

	void solve(Scanner in) {		
		for (int P = in.nextInt(); P --> 0;) {
			int T = in.nextInt();
			int Z = in.nextInt();
			for (int t = 0; t < T; t++) {
				int s = in.nextInt();
				int m = in.nextInt();
				W[t] = s * 3;
				Arrays.fill(pred[t], NONE);
				for (int w = Z; w - W[t] >= 0; w--) {
					int vt = maxV[w - W[t]] + m;
					if (vt > maxV[w]) {
						maxV[w] = vt;
						pred[t][w] = t;
					}
				}
			}

			while (Z > 0 && maxV[Z] == maxV[Z - 1]) {
				Z--;
			}
			System.out.println(Z + " " + maxV[Z]);
			System.out.println(trace(T - 1, Z).trim());

			Arrays.fill(maxV, 0);
		}
	}

	public static void main(String[] args) throws Exception {
		new swarm().solve(new Scanner(new File(args[0])));
	}
}
