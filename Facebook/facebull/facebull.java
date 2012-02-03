import java.io.*;
import java.util.*;

public class facebull {
	static class Index {
		Map<String, Integer> map;
		List<String> list;
		
		Index() {
			map = new HashMap<String, Integer>();
			list = new ArrayList<String>();
		}
		int indexOf(String s) {
			Integer ii = map.get(s);
			if (ii == null) {
				map.put(s, ii = map.size());
				list.add(s);
			}
			return ii;
		}
		String at(int i) {
			return list.get(i);
		}
	}
	Index compoundsIndex = new Index();
	
	static class Machine {
		int label;
		int c1, c2;
		int w;

		Machine(int label, int c1, int c2, int w) {
			this.label = label;
			this.c1 = c1;
			this.c2 = c2;
			this.w = w;
		}
		public String toString() {
			return label + " " + c1 + " " + c2 + " " + w;
		}
	}
	List<Machine> machinesList = new ArrayList<Machine>();
	
	static Integer[] asArray(BitSet set) {
		Integer[] ret = new Integer[set.cardinality()];
		for (int i = 0, v = set.nextSetBit(0); v >= 0; v = set.nextSetBit(v + 1)) {
			ret[i++] = v;
		}
		return ret;
	}

	String toStringMachines(BitSet machines) {
		BitSet labels = new BitSet();
		for (int i : asArray(machines)) {
			labels.set(machinesList.get(i).label);
		}
		return labels.toString().replaceAll("[^0-9 ]", "");		
	}

	String toStringCompounds(BitSet compounds) {
		String s = "";
		for (int i : asArray(compounds)) {
			s += " " + compoundsIndex.at(i);
		}
		return s.trim();
	}
	
	int NUM_C;
	
	int record = Integer.MAX_VALUE;
	BitSet bestSet = null;
	
	BitSet[] outgoing;
	
	static BitSet copy(BitSet b) {
		BitSet ret = new BitSet();
		ret.or(b);
		return ret;
	}
	static BitSet or(BitSet b1, BitSet b2) {
		BitSet ret = copy(b1);
		ret.or(b2);
		return ret;
	}
	static BitSet set(BitSet b, int index) {
		BitSet ret = copy(b);
		ret.set(index);
		return ret;
	}

	void bruteDFS(int current, BitSet loopable, BitSet reachable, BitSet machines, int totalCost, BitSet path) {
		if (totalCost > record) {
			return;
		}
		for (int mIndex : asArray(outgoing[current])) {
			if (machines.get(mIndex)) {
				continue;
			}
			Machine m = machinesList.get(mIndex);
			int next = m.c2;
			if (loopable.get(next)) {
				bruteAddCycle(or(loopable, path), set(reachable, next), set(machines, mIndex), totalCost + m.w);
			} else if (!reachable.get(next)) {
				bruteDFS(next, loopable, set(reachable, next), set(machines, mIndex), totalCost + m.w, set(path, next));
			}
		}
	}
				
	void bruteAddCycle(BitSet loopable, BitSet reachable, BitSet machines, int totalCost) {
		if (reachable.cardinality() == NUM_C) {
			if (totalCost < record) {
				record = totalCost;
				bestSet = copy(machines);
			}
			return;
		}
		Integer[] cycleStart = asArray(loopable);
		Queue<BitSet> copy = new LinkedList<BitSet>();
		for (int start : cycleStart) {
			bruteDFS(start, loopable, reachable, machines, totalCost, new BitSet());
			copy.add(copy(outgoing[start]));
			outgoing[start].clear();
		}
		for (int start : cycleStart) {
			outgoing[start].or(copy.remove());
		}
	}
	
	void solve(Scanner in) {
		while (in.hasNext()) {
			int label = Integer.parseInt(in.next().substring(1));
			int c1 = compoundsIndex.indexOf(in.next());
			int c2 = compoundsIndex.indexOf(in.next());
			int w = in.nextInt();
			machinesList.add(new Machine(label, c1, c2, w));
		}
		NUM_C = compoundsIndex.map.size();
		BitSet machines = new BitSet();
		machines.set(0, machinesList.size());

		outgoing = new BitSet[NUM_C];
		for (Machine m : machinesList) {
			BitSet out = outgoing[m.c1];
			if (out == null) {
				outgoing[m.c1] = out = new BitSet();
			}
			out.set(machinesList.indexOf(m));
		}

		bruteAddCycle(set(new BitSet(), 0), new BitSet(), new BitSet(), 0);
		
		System.out.println(record);
		System.out.println(toStringMachines(bestSet));
	}

	public static void main(String[] args) throws Exception {
		new facebull().solve(new Scanner(new File(args[0])));
	}
}
