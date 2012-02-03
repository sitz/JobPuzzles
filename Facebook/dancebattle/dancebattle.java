import java.util.*;
import java.io.*;

public class dancebattle {
	final int N;
	final int M;
	final boolean[] used;
	
	int edge(int i, int j) {
		return (i < j ? i * N + j : j * N + i);
	}
	
	boolean winnable(int current) {
		for (int next = 0; next < N; next++) {
			int e = edge(current, next);
			if (!used[e]) {
				used[e] = true;
				boolean oppMustLose = !winnable(next);
				used[e] = false;
				if (oppMustLose) {
					return true;
				}
			}
		}
		return false;
	}
	
	dancebattle(Scanner in) {
		N = in.nextInt();
		M = in.nextInt();
		used = new boolean[N * N];
		
		int current = 0;
		for (int i = M; i --> 0;) {
			used[edge(in.nextInt(), current = in.nextInt())] = true;
		}

		boolean p1w = winnable(current) ^ (M % 2 == 1);
		System.out.println(p1w ? "Win" : "Lose");
	}
	
	public static void main(String[] args) throws Exception {
		new dancebattle(new Scanner(new File(args[0])));
	}
}
