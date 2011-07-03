package topcoder.srm;

import java.util.Arrays;

public class KiwiJuice {

	// Begin cut here

	static class Tester {

		public static void main(final String[] args) {
			try {
				eq(0, new KiwiJuice().theProfit(10, new int[] { 5, 8 },
						new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10 }), 10);
				eq(1, new KiwiJuice().theProfit(10, new int[] { 5, 8 },
						new int[] { 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10 }),
						20);
				eq(2,
						new KiwiJuice().theProfit(10, new int[] { 4, 5, 3, 7 },
								new int[] { 14, 76, 12, 35, 6, 94, 26, 3, 93,
										90, 420 }), 625);
				eq(3, new KiwiJuice().theProfit(1, new int[] { 0 }, new int[] {
						1000000, 1000000 }), 1000000);
				eq(4, new KiwiJuice().theProfit(49, new int[] { 2, 47, 24, 14,
						0, 32, 9, 12, 31, 46, 39, 12, 16, 22, 29 }, new int[] {
						428668, 995687, 128567, 37241, 496916, 238624, 304781,
						997819, 85856, 417008, 398570, 951499, 750349, 333625,
						927594, 188616, 942498, 259414, 654344, 354809, 25303,
						226854, 98578, 207140, 305527, 358343, 393213, 256248,
						282644, 103327, 667191, 103402, 609183, 619323, 189127,
						518006, 778846, 400460, 128334, 795097, 605203, 669142,
						121825, 934404, 837430, 554265, 610818, 546228, 80784,
						949440 }), 12873962);

				eq(5,
						new KiwiJuice().theProfit(

						49, new int[] { 24 }, new int[] { 771154, 358840,
								216078, 982833, 896069, 971582, 545764, 485499,
								990135, 988115, 674826, 594470, 590282, 88279,
								465526, 858065, 938177, 944893, 7538, 376503,
								244092, 646266, 733290, 237026, 259986, 317213,
								283612, 683817, 818056, 127040, 795071, 902920,
								89294, 498253, 94033, 676967, 857204, 45373,
								547243, 38281, 328932, 910517, 567195, 803682,
								25412, 912810, 191362, 842676, 390405, 240464 }

						), 259986);
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

	static int[][] memo = new int[50][33000];

	static private int[] prices;
	static private int[] bottles;
	static private int c;

	private static int n;

	public int theProfit(final int C, final int[] bottles, final int[] prices) {
		for (final int[] q : memo) {
			Arrays.fill(q, -1);
		}
		final int ppp = prices[0];
		for (int i = 0; i < prices.length; ++i) {
			prices[i] -= ppp;
		}

		c = C;
		KiwiJuice.bottles = bottles;
		KiwiJuice.prices = prices;

		n = bottles.length;

		return ppp * n + f(0, (1 << n) - 1);
	}

	private int f(final int cur, final int mask) {
		if (mask == 0) {
			return prices[cur];
		}

		if (memo[cur][mask] != -1) {
			return memo[cur][mask];
		}

		int ans = cur == 0 ? Integer.MIN_VALUE : prices[cur] + f(0, mask);

		for (int i = 0; i < n; ++i) {
			if ((mask & 1 << i) != 0) {
				final int nc = cur + bottles[i];
				final int t = prices[c] * (nc / c)
						+ f(nc % c, mask & ~(1 << i));
				if (t > ans) {
					ans = t;
				}
			}
		}

		memo[cur][mask] = ans;
		return ans;
	}

}
