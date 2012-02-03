import java.util.*;
import java.math.*;
import java.io.*;

class Exon implements Comparable<Exon> {
  int start, end, weight, overlapsTo, score;

  public Exon(int start) {
    this.start = start;
    this.score = 0;
  }

  public int compareTo (Exon e) {
    if (this == e) return 0;
    if (this.start < e.start) return -1;
    if (this.start > e.start) return 1;
    return 0;
  }
}

public class gattaca {
  public static void main(String args[]) throws IOException {

    // Set up file reader, read how many digits to skip, skip them
    BufferedReader in = new BufferedReader (new FileReader(args[0]));

    // Read number of characters to skip (plus line breaks every 80 chars)
    long skip = Long.parseLong(in.readLine());
    skip += Math.ceil(skip/80);
    in.skip(skip);

    // Set up stream tokenizer *after* skipping the reader forward
    // Unexpected behavior happens when mixing tokenizer and reader calls
    StreamTokenizer st = new StreamTokenizer(in);
    st.parseNumbers();

    // Read number of exon description lines
    List<Exon> exonList = new ArrayList<Exon>();
    while(st.ttype != StreamTokenizer.TT_NUMBER) st.nextToken();
    int count = (int)st.nval;

    // Read exon descriptions, add to ArrayList
    Exon e;
    for (int i = 0; i < count; i++) {
      st.nextToken();
      e = new Exon((int)st.nval);
      st.nextToken();
      e.end = (int)st.nval;
      st.nextToken();
      e.weight = (int)st.nval;
      exonList.add(e);
    }
    in.close();

    // Sort ArrayList by start position
    Collections.sort(exonList);

    // Find each exon's last overlap
    Exon finder = new Exon(0);
    int end, next;
    for (int n = 0; n < count; n++) {
      e = exonList.get(n);
      end = e.end;
      finder.start = end;
      next = Collections.binarySearch(exonList, finder);
      if (next < 0) e.overlapsTo = -(next + 2);
      else {
        while (next < count && end >= exonList.get(next).start) next++;
        e.overlapsTo = next - 1;
      }
    }

    // Find best paths
    int highScore = 0;
    int nonOverlapScore;
    int lastScore = 0;
    int highestOverlap = 0;
    Exon overlap;
    for (int i = 0; i < count; i++) {
      e = exonList.get(i);
      if (e.overlapsTo > highestOverlap) {
        highScore = exonList.get(highestOverlap).score;
        for (int n = highestOverlap + 1; n <= e.overlapsTo; n++) exonList.get(n).score = highScore;
        highestOverlap = e.overlapsTo;
      }
      nonOverlapScore = lastScore + e.weight;
      if (nonOverlapScore > exonList.get(e.overlapsTo).score ) {
        for (int n = e.overlapsTo; n<= highestOverlap; n++) {
          overlap = exonList.get(n);
          if (nonOverlapScore > overlap.score) overlap.score = nonOverlapScore;
        }
      }
      lastScore = e.score;
    }
    System.out.println(lastScore);
  }

}
