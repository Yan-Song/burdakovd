package topcoder.srm;

import java.util.AbstractMap.SimpleEntry;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;

public class TheCoffeeTimeDivOne {

	// Begin cut here

	static class Tester {

		public static void main(final String[] args) {
			try {
				eq(0, new TheCoffeeTimeDivOne().find(2, new int[] { 1 }), 108L);
				eq(1, new TheCoffeeTimeDivOne().find(2, new int[] { 2, 1 }),
						59L);
				eq(2,
						new TheCoffeeTimeDivOne().find(15, new int[] { 1, 2, 3,
								4, 5, 6, 7 }), 261L);
				eq(3,
						new TheCoffeeTimeDivOne().find(47, new int[] { 1, 10,
								6, 2, 4 }), 891L);
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

	public long find(final int n, final int[] tea) {

		final List<SimpleEntry<Integer, Integer>> teaGroups = makeGroups(tea,
				false, n);

		final List<SimpleEntry<Integer, Integer>> coffeeGroups = makeGroups(
				tea, true, n);

		return solve(teaGroups) + solve(coffeeGroups) + 4 * n;
	}

	private long solve(final List<SimpleEntry<Integer, Integer>> groups) {

		final int n = groups.size();

		if (groups.isEmpty()) {
			return 0;
		} else {

			final long dp[][] = new long[n + 1][7];

			for (int i = 0; i < 7; ++i) {
				dp[n][i] = groups.get(n - 1).getValue();
			}

			for (int processed = n - 1; processed >= 0; --processed) {
				for (int has = 0; has < 7; ++has) {

					final int currentPosition = processed == 0 ? 0 : groups
							.get(processed - 1).getValue();

					final int firstTime = groups.get(processed).getKey()
							- currentPosition;

					if (has >= len(groups.get(processed))) {

						final int left = has - len(groups.get(processed));

						dp[processed][has] = firstTime
								+ len(groups.get(processed)) - 1
								+ dp[processed + 1][left];
					} else {
						int ans;
						int start = groups.get(processed).getKey();
						final int end = groups.get(processed).getValue();

						if (has == 0) {
							ans = currentPosition;
						} else {
							ans = firstTime + (has - 1) * 2 - start;
							start += has;
						}

						final long count = (end - start + 1) / 7;
						ans += 12 * count + 2 * count * start + 7 * count
								* (count - 1);

						final long left = (end - start + 1) % 7;

						if (left == 0) {
							ans -= end;
							dp[processed][has] = ans;
						} else {
							start = (int) (start + 7 * count);

							dp[processed][has] = Long.MAX_VALUE;
							for (long k = left; k <= 7; ++k) {
								dp[processed][has] = Math
										.min(dp[processed][has],
												ans
														+ start
														+ 47
														+ end
														+ dp[processed + 1][(int) (k - left)]);
							}

						}
					}
				}
			}

			return dp[0][0];
		}
	}

	private int len(final SimpleEntry<Integer, Integer> group) {
		return group.getValue() - group.getKey() + 1;
	}

	private List<SimpleEntry<Integer, Integer>> makeGroups(final int[] tea,
			final boolean inverse, final int n) {

		final TreeSet<Integer> teas = new TreeSet<Integer>();

		for (final int tean : tea) {
			teas.add(tean);
		}

		if (inverse) {
			final List<SimpleEntry<Integer, Integer>> ans = new ArrayList<SimpleEntry<Integer, Integer>>();

			int currentStart = 1;

			while (!teas.isEmpty()) {
				final int currentEnd = teas.pollFirst() - 1;

				if (currentStart <= currentEnd) {
					ans.add(new SimpleEntry<Integer, Integer>(currentStart,
							currentEnd));
				}

				currentStart = currentEnd + 2;
			}

			if (currentStart <= n) {
				ans.add(new SimpleEntry<Integer, Integer>(currentStart, n));
			}

			return ans;

		} else {
			final List<SimpleEntry<Integer, Integer>> ans = new ArrayList<SimpleEntry<Integer, Integer>>();

			while (!teas.isEmpty()) {

				final int currentStart = teas.pollFirst();
				int currentEnd = currentStart;

				while (!teas.isEmpty() && teas.first() == currentEnd + 1) {
					currentEnd = teas.pollFirst();
				}

				ans.add(new SimpleEntry<Integer, Integer>(currentStart,
						currentEnd));
			}

			return ans;
		}
	}
}
