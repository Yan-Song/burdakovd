package codechef._2010.december.algorithm;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Locale;
import java.util.TreeSet;

public final class BYTEISLE {

	private static final class Tree {

		private final int[] counts;

		public Tree(final int n, final List<Integer> positions) {
			int z = 1;
			while (2 * n > z) {
				z <<= 1;
			}
			counts = new int[z];

			Arrays.fill(counts, 0);

			for (final int position : positions) {
				add(position);
			}
		}

		private void add(final int position) {
			for (int i = position + counts.length / 2; i >= 1; i >>= 1) {
				++counts[i];
			}
		}

		private int partial(final int finish) {
			final int first = finish + counts.length / 2;
			int ans = counts[first];

			for (int i = first; i >= 1; i >>= 1) {
				if (counts[i] == 0) {
					ans = 0;
				}

				if (i > 1 && (i & 1) == 1) {
					ans += counts[i ^ 1];
				}
			}

			return ans;
		}

		public int sum(final int start, final int finish) {
			if (start == 0) {
				return partial(finish);
			} else {
				return partial(finish) - partial(start - 1);
			}
		}

		public void nullify(final int start, final int finish) {
			nullify(1, start, finish, 0, counts.length / 2 - 1);
		}

		private void nullify(final int cell, final int start, final int finish,
				final int mystart, final int myfinish) {

			if (myfinish < start || mystart > finish) {
				return;
			}

			if (mystart >= start && myfinish <= finish) {
				counts[cell] = 0;
			} else {
				final int leftfinish = (mystart + myfinish) / 2;
				nullify(cell * 2, start, finish, mystart, leftfinish);
				nullify(cell * 2 + 1, start, finish, leftfinish + 1, myfinish);
				counts[cell] = counts[cell * 2] + counts[cell * 2 + 1];
			}
		}
	}

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;
	static boolean isLocal = false;

	private static int nextInt() throws IOException {

		in.nextToken();
		if (in.ttype == StreamTokenizer.TT_NUMBER) {
			return (int) in.nval;
		} else {
			throw new IOException();
		}

		// return in.nextInt();
	}

	static StreamTokenizer in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);

			// in = new BufferedReader(new InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in));

			in = new StreamTokenizer(new BufferedReader(new InputStreamReader(
					file ? new FileInputStream("c:\\var\\tmp\\in.txt")
							: System.in)));
		} catch (final FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	static PrintWriter out;
	static {
		try {
			out = file ? new PrintWriter(
					new FileWriter("c:\\var\\tmp\\out.txt")) : new PrintWriter(
					System.out);
		} catch (final IOException e) {
			e.printStackTrace();
		}
	}

	static PrintStream err;
	static {
		err = System.err;
	}

	/**
	 * @param args
	 * @throws IOException
	 */
	public static void main(final String[] args) throws IOException {
		try {
			final long startTime = System.nanoTime();
			final long t = nextInt();
			for (long i = 0; i < t; ++i) {
				solve(i + 1);
				if (file) {
					err.println(i + 1 + "/" + t);
				}
				if (!file) {
					out.flush();
				}
			}
			if (isLocal) {
				err.println(String.format("Completed after %d ms.",
						(System.nanoTime() - startTime) / 1000000));
			}
		} finally {
			out.flush();
		}
	}

	private static void solve(final long testId) throws IOException {

		final int n = nextInt();
		final int[] a = new int[n];
		final int[] b = new int[n];
		for (int i = 0; i < n; ++i) {
			a[i] = nextInt();
			b[i] = nextInt();
		}

		// consonantCount[i] - число субъектов, согласных с тем, что рыцарей i
		final int[] consonantCounts = countConsonant(n, a, b);

		final List<Integer> variants = new ArrayList<Integer>();

		for (int count = 0; count <= n; ++count) {
			if (consonantCounts[count] == count) {
				variants.add(count);
			}
		}

		out.println(variants.size());

		// final Tree tree = new Tree(n + 2, variants);
		final TreeSet<Integer> tree = new TreeSet<Integer>(variants);

		final char[] ans = new char[n];
		for (int i = 0; i < n; ++i) {

			/*
			 * if (tree.sum(a[i], b[i]) != tree.sum(0, n)) { tree.nullify(a[i],
			 * b[i]); ans[i] = '0'; } else { ans[i] = '1'; }
			 */

			if (tree.lower(a[i]) != null || tree.higher(b[i]) != null) {
				while (true) {
					final Integer q = tree.ceiling(a[i]);
					if (q == null || q > b[i]) {
						break;
					}
					tree.remove(q);
				}
				ans[i] = '0';
			} else {
				ans[i] = '1';
			}

		}

		out.println(ans);
	}

	private static int[] countConsonant(final int n, final int[] a,
			final int[] b) {

		final int[] deltas = new int[n + 2];
		Arrays.fill(deltas, 0);

		for (int i = 0; i < n; ++i) {
			++deltas[a[i]];
			--deltas[b[i] + 1];
		}

		final int[] counts = new int[n + 1];
		counts[0] = deltas[0];
		for (int i = 1; i <= n; ++i) {
			counts[i] = counts[i - 1] + deltas[i];
		}

		return counts;
	}
}
