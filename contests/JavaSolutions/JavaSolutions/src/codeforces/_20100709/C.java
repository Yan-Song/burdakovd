package codeforces._20100709;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Locale;
import java.util.Scanner;

public class C {

    static {
	final Locale us = Locale.US;
	if (!Locale.getDefault().equals(us)) {
	    Locale.setDefault(us);
	}
    }

    static boolean file = false;

    static Scanner in;
    static {
	try {
	    in = new Scanner(file ? new FileInputStream("f:\\var\\tmp\\in.txt")
		    : System.in);
	} catch (final FileNotFoundException e) {
	    e.printStackTrace();
	}
    }

    static PrintWriter out;
    static {
	try {
	    out = file ? new PrintWriter(
		    new FileWriter("f:\\var\\tmp\\out.txt")) : new PrintWriter(
		    System.out);
	} catch (final IOException e) {
	    e.printStackTrace();
	}
    }

    /**
     * @param args
     */
    public static void main(final String[] args) {
	try {
	    final long t = in.nextInt();
	    for (long i = 0; i < t; ++i) {
		solve(i + 1);
		if (file) {
		    System.out.println(i + 1 + "/" + t);
		    System.out.flush();
		}
		if (!file) {
		    out.flush();
		}
	    }
	} finally {
	    in.close();
	    out.close();
	}
    }

    static class Box {
	public Box(final long apples, final long oranges, final int num) {
	    this.oranges = oranges;
	    this.apples = apples;
	    number = num;
	}

	int number;
	long oranges;

	public long getOranges() {
	    return oranges;
	}

	public void setOranges(final long oranges) {
	    this.oranges = oranges;
	}

	public long getApples() {
	    return apples;
	}

	public void setApples(final long apples) {
	    this.apples = apples;
	}

	public boolean isUsed() {
	    return used;
	}

	public void setUsed(final boolean used) {
	    this.used = used;
	}

	long apples;
	boolean used = false;
    }

    private static void solve(final long testId) {
	final int n = in.nextInt();

	final Box[] boxes = new Box[2 * n - 1];

	long totalApples = 0, totalOranges = 0;
	for (int i = 0; i < 2 * n - 1; ++i) {
	    boxes[i] = new Box(in.nextLong(), in.nextLong(), i + 1);
	    totalApples += boxes[i].getApples();
	    totalOranges += boxes[i].getOranges();
	}

	final long ta = totalApples, to = totalOranges;

	Arrays.sort(boxes, new Comparator<Box>() {

	    @Override
	    public int compare(final Box arg0, final Box arg1) {
		return (int) Math.signum(-arg0.getApples() * 1.0
			/ (ta == 0 ? 1.0 : ta) + arg1.getOranges() * 1.0
			/ (to == 0 ? 1.0 : to));
	    }

	});

	final ArrayList<Integer> ans = new ArrayList<Integer>();

	long hasa = 0, haso = 0;
	for (int i = 0; i < n; ++i) {
	    ans.add(boxes[i].number);
	    hasa += boxes[i].getApples();
	    haso += boxes[i].getOranges();
	}

	if (hasa * 2 >= totalApples && haso * 2 >= totalOranges) {
	    out.println("YES");
	    final Integer[] ans_ = ans.toArray(new Integer[ans.size()]);
	    Arrays.sort(ans_);

	    for (final Integer q : ans_) {
		out.print(q);
		out.print(" ");
	    }
	} else {
	    out.println("NO");
	}

	out.println();
    }
}
