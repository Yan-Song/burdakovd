package topcoder.srm;

public class Islands {

	// Begin cut here

	static class Tester {

		public static void main(final String[] args) {
			try {
				eq(0, new Islands().beachLength(new String[] { ".#...#.." }), 4);
				eq(1,
						new Islands().beachLength(new String[] { "..#.##",
								".##.#.", "#.#..." }), 19);
				eq(2,
						new Islands().beachLength(new String[] { "#...#.....",
								"##..#...#." }), 15);
				eq(3,
						new Islands().beachLength(new String[] { "....#.",
								".#....", "..#..#", "####.." }), 24);
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

	public int beachLength(final String[] kingdom) {
		int ans = 0;
		for (int i = 0; i < kingdom.length; ++i) {
			for (int j = 0; j < kingdom[0].length(); ++j) {
				if (j != 0 && kingdom[i].charAt(j) != kingdom[i].charAt(j - 1)) {
					++ans;
				}

				final int[] previdx = { j, (i & 1) == 1 ? j + 1 : j - 1 };
				for (final int k : previdx) {
					if (i > 0 && k >= 0 && k < kingdom[0].length()
							&& kingdom[i].charAt(j) != kingdom[i - 1].charAt(k)) {
						++ans;
					}
				}
			}
		}

		return ans;

	}
}
