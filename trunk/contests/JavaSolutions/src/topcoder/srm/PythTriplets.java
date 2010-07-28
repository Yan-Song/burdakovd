package topcoder.srm;
import java.util.Arrays;
import java.util.LinkedList;

public class PythTriplets {

	// Begin cut here

	static class Tester {

		public static void main(final String[] args) {
			try {
				eq(0,
						new PythTriplets()
								.findMax(new String[] { "3 4 4 3 11 5 12 9 4" }),
						3);
				eq(1,
						new PythTriplets()
								.findMax(new String[] { "20 21 3021 220" }), 2);
				eq(2,
						new PythTriplets().findMax(new String[] { "28 19",
								"5 1035 21412 37995" }), 2);
			} catch (final Exception exx) {
				System.err.println(exx);
				exx.printStackTrace(System.err);
			}
		}

		private static void eq(final int n, final double a, final double b) {
			if (Math.abs(a - b) < 1e-9) {
				System.err.println("Case " + n + " passed.");
			} else {
				System.err.println("Case " + n + " failed: expected " + b
						+ ", received " + a + ".");
			}
		}

		private static void eq(final int n, final int a, final int b) {
			if (a == b) {
				System.err.println("Case " + n + " passed.");
			} else {
				System.err.println("Case " + n + " failed: expected " + b
						+ ", received " + a + ".");
			}
		}

		private static void eq(final int n, final char a, final char b) {
			if (a == b) {
				System.err.println("Case " + n + " passed.");
			} else {
				System.err.println("Case " + n + " failed: expected '" + b
						+ "', received '" + a + "'.");
			}
		}

		private static void eq(final int n, final long a, final long b) {
			if (a == b) {
				System.err.println("Case " + n + " passed.");
			} else {
				System.err.println("Case " + n + " failed: expected \"" + b
						+ "L, received " + a + "L.");
			}
		}

		private static void eq(final int n, final boolean a, final boolean b) {
			if (a == b) {
				System.err.println("Case " + n + " passed.");
			} else {
				System.err.println("Case " + n + " failed: expected " + b
						+ ", received " + a + ".");
			}
		}

		private static void eq(final int n, final String a, final String b) {
			if (a != null && a.equals(b)) {
				System.err.println("Case " + n + " passed.");
			} else {
				System.err.println("Case " + n + " failed: expected \"" + b
						+ "\", received \"" + a + "\".");
			}
		}

		private static void eq(final int n, final int[] a, final int[] b) {
			if (a.length != b.length) {
				System.err.println("Case " + n + " failed: returned "
						+ a.length + " elements; expected " + b.length
						+ " elements.");
				return;
			}
			for (int i = 0; i < a.length; i++) {
				if (a[i] != b[i]) {
					System.err
							.println("Case "
									+ n
									+ " failed. Expected and returned array differ in position "
									+ i);
					print(b);
					print(a);
					return;
				}
			}
			System.err.println("Case " + n + " passed.");
		}

		private static void eq(final int n, final long[] a, final long[] b) {
			if (a.length != b.length) {
				System.err.println("Case " + n + " failed: returned "
						+ a.length + " elements; expected " + b.length
						+ " elements.");
				return;
			}
			for (int i = 0; i < a.length; i++) {
				if (a[i] != b[i]) {
					System.err
							.println("Case "
									+ n
									+ " failed. Expected and returned array differ in position "
									+ i);
					print(b);
					print(a);
					return;
				}
			}
			System.err.println("Case " + n + " passed.");
		}

		private static void eq(final int n, final String[] a, final String[] b) {
			if (a.length != b.length) {
				System.err.println("Case " + n + " failed: returned "
						+ a.length + " elements; expected " + b.length
						+ " elements.");
				return;
			}
			for (int i = 0; i < a.length; i++) {
				if (!a[i].equals(b[i])) {
					System.err
							.println("Case "
									+ n
									+ " failed. Expected and returned array differ in position "
									+ i);
					print(b);
					print(a);
					return;
				}
			}
			System.err.println("Case " + n + " passed.");
		}

		private static void print(final int a) {
			System.err.print(a + " ");
		}

		private static void print(final long a) {
			System.err.print(a + "L ");
		}

		private static void print(final String s) {
			System.err.print("\"" + s + "\" ");
		}

		private static void print(final int[] rs) {
			if (rs == null) {
				return;
			}
			System.err.print('{');
			for (int i = 0; i < rs.length; i++) {
				System.err.print(rs[i]);
				if (i != rs.length - 1) {
					System.err.print(", ");
				}
			}
			System.err.println('}');
		}

		private static void print(final long[] rs) {
			if (rs == null) {
				return;
			}
			System.err.print('{');
			for (int i = 0; i < rs.length; i++) {
				System.err.print(rs[i]);
				if (i != rs.length - 1) {
					System.err.print(", ");
				}
			}
			System.err.println('}');
		}

		private static void print(final String[] rs) {
			if (rs == null) {
				return;
			}
			System.err.print('{');
			for (int i = 0; i < rs.length; i++) {
				System.err.print("\"" + rs[i] + "\"");
				if (i != rs.length - 1) {
					System.err.print(", ");
				}
			}
			System.err.println('}');
		}

		private static void nl() {
			System.err.println();
		}
	}

	// End cut here

	public int findMax(final String[] stick) {
		final StringBuilder builder = new StringBuilder();
		for (final String s : stick) {
			builder.append(s);
		}
		final String data = builder.toString();

		final String[] snumbers = data.split(" ");

		final LinkedList<Long> numbers = new LinkedList<Long>();

		for (int i = 0; i < snumbers.length; ++i) {
			numbers.add(Long.parseLong(snumbers[i]));
		}

		final long[] squares = new long[1500000];

		for (long i = 0; i < 1500000; ++i) {
			squares[(int) i] = i * i;
		}

		int ans = 0;

		while (!numbers.isEmpty()) {
			final Long a = numbers.removeFirst();

			for (final Long b : numbers) {
				if (!b.equals(a) && gcd(a, b) == 1) {
					final long c2 = a * a + b * b;
					if (Arrays.binarySearch(squares, c2) >= 0) {
						++ans;
						numbers.remove(b);
						break;
					}
				}
			}
		}

		return ans;

	}

	private long gcd(final long a, final long b) {
		return b == 0 ? a : gcd(b, a % b);
	}
}
