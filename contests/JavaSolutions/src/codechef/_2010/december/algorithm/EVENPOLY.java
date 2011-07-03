package codechef._2010.december.algorithm;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Locale;
import java.util.Set;

public final class EVENPOLY {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;
	static boolean isLocal = false;

	private static int nextInt() throws IOException {
		return Integer.parseInt(nextLine());
	}

	private static String nextLine() throws IOException {
		return in.readLine().trim();
	}

	static BufferedReader in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);

			in = new BufferedReader(new InputStreamReader(
					file ? new FileInputStream("c:\\var\\tmp\\in.txt")
							: System.in));

			// in = new StreamTokenizer(new BufferedReader(new
			// InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in)));
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

		final long startTime = System.nanoTime();
		final long t = nextInt();
		for (long i = 0; i < t; ++i) {
			solve(i + 1);
			if (file) {
				err.println(i + 1 + "/" + t);
			}
			if (isLocal && !file) {
				out.flush();
			}
		}
		if (isLocal) {
			err.println(String.format("Completed after %d ms.",
					(System.nanoTime() - startTime) / 1000000));
		}

		out.flush();

	}

	private final static int fieldLength = 8;
	private final static int polynomialModulo = 0x11b;
	private final static int polynomialModuloHighestBit = 1 << fieldLength;
	private final static int generator = 3;
	private final static int fieldElementCount = 1 << fieldLength;
	private static int[] logTable;
	private static int[] expTable;
	static {
		makeLogTables();
	}

	private static final class Polynomial {

		private static final int[] powersOfX = calculatePowerOfX();

		private final Set<String> monomials;

		public Polynomial(final String rowS) {
			monomials = new HashSet<String>();

			for (final String atom : rowS.split("\\+")) {
				if (!atom.equals("0")) {
					final String normalized = sortedString(atom);
					if (monomials.contains(normalized)) {
						monomials.remove(normalized);
					} else {
						monomials.add(normalized);
					}
				}
			}
		}

		private static int[] calculatePowerOfX() {
			final int[] powers = new int[101];
			final int x = 2;

			powers[0] = 1;
			powers[1] = x;

			for (int i = 2; i < powers.length; ++i) {
				powers[i] = multiplyPolynomials(powers[i - 1], x);
			}

			return powers;
		}

		public Set<String> getMonomials() {
			return monomials;
		}

		@Override
		public String toString() {
			return "Polynomial [monomials=" + monomials + "]";
		}

		public int toInt(final boolean[] needed) {
			int ans = 0;
			for (final String monomial : monomials) {
				int power = 0;
				for (final char c : monomial.toCharArray()) {
					if (c != '1' && needed[c - 'a']) {
						++power;
					}
				}
				ans ^= powersOfX[power];
			}
			return ans;
		}
	}

	private static void solve(final long testId) throws IOException {
		final int d = nextInt();

		final Polynomial[][] p_m = new Polynomial[d][];
		for (int i = 0; i < d; ++i) {
			p_m[i] = readMatrixRow();
		}

		final int[][] m = new int[d][d];

		boolean foundOdd = false;
		final int stepCount = 8;
		for (int step = 0; !foundOdd && step < stepCount; ++step) {
			final boolean[] needed = new boolean[26];
			for (int i = 0; i < needed.length; ++i) {
				needed[i] = (randInt() & 32) != 0;
			}

			for (int i = 0; i < d; ++i) {
				for (int j = 0; j < d; ++j) {
					m[i][j] = p_m[i][j].toInt(needed);
				}
			}

			foundOdd |= isInvertible(m);
		}

		out.println(foundOdd ? "Some Odd" : "All Even");
	}

	private static void makeLogTables() {
		logTable = new int[fieldElementCount];
		expTable = new int[fieldElementCount];
		for (int p = 0, a = 1; p < fieldElementCount - 1; ++p, a = multiplyPolynomialsSlow(
				a, generator)) {

			expTable[p] = a;
			logTable[a] = p;
		}
		expTable[fieldElementCount - 1] = 1;
		logTable[0] = 0;
	}

	private static boolean isInvertible(final int[][] m) {
		final int d = m.length;

		for (int base = 0; base < d; ++base) {

			{
				// найти не 0 в столбце, и перенести его в первую строку
				int row = base;
				while (m[row][base] == 0) {
					++row;
					if (row == d) {
						return false;
					}
				}
				if (row != base) {
					final int[] q = m[base];
					m[base] = m[row];
					m[row] = q;
				}
			}

			{
				// сделать так, чтобы m[base][base] содержал 1
				final int inverted = invert(m[base][base]);
				for (int col = base; col < d; ++col) {
					m[base][col] = multiplyPolynomials(m[base][col], inverted);
				}
			}

			{
				// обнулить столбец ниже base
				for (int row = base + 1; row < d; ++row) {
					final int multiplier = m[row][base];
					for (int col = base; col < d; ++col) {
						m[row][col] ^= multiplyPolynomials(m[base][col],
								multiplier);
					}
				}
			}

		}

		return true;
	}

	private static int invert(final int a) {
		return expTable[fieldElementCount - 1 - logTable[a]];
	}

	private static int multiplyPolynomials(final int a, final int b) {
		if (a == 0 || b == 0) {
			return 0;
		}
		final int l = logTable[a] + logTable[b];
		if (l > fieldElementCount - 1) {
			return expTable[l - fieldElementCount + 1];
		} else {
			return expTable[l];
		}
	}

	private static int multiplyPolynomialsSlow(final int originalA,
			final int originalB) {
		int p = 0;
		for (int counter = 0, a = originalA, b = originalB; counter < fieldLength; ++counter) {
			if ((b & 1) == 1) {
				p ^= a;
			}
			a <<= 1;
			if ((a & polynomialModuloHighestBit) != 0) {
				a ^= polynomialModulo;
			}
			b >>= 1;
		}
		return p;
	}

	private static long seed = 1000000007;

	private static long randInt() {
		seed *= 173;
		return seed;
	}

	private static String sortedString(final String atom) {
		final char[] chars = atom.toCharArray();
		Arrays.sort(chars);
		return String.valueOf(chars);
	}

	private static Polynomial[] readMatrixRow() throws IOException {
		final String[] rowS = nextLine().split(" ");
		final int d = rowS.length;

		final Polynomial[] row = new Polynomial[d];
		for (int i = 0; i < d; ++i) {
			row[i] = new Polynomial(rowS[i]);
		}

		return row;
	}
}
