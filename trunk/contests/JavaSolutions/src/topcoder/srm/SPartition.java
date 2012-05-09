package topcoder.srm;

import java.util.HashMap;
import java.util.Map;

public class SPartition {

	// Begin cut here

	static class Tester {

		public static void main(final String[] args) {
			try {
				eq(0, new SPartition().getCount("oxox"), 2L);
				eq(1, new SPartition().getCount("oooxxx"), 0L);
				eq(2, new SPartition().getCount("xoxxox"), 4L);
				eq(3, new SPartition().getCount("xo"), 0L);
				eq(4, new SPartition().getCount("ooooxoox"), 8L);
				eq(5, new SPartition().getCount("ooxxoxox"), 8L);
				eq(5,
						new SPartition()
								.getCount("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"),
						42075627300L);
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

	private boolean[] s;
	// static long[][] cache = new long[41][];
	static Map<Integer, Map<Integer, Long>> hcache = new HashMap<Integer, Map<Integer, Long>>();
	static {
		// for (int i = 0; i < 41; ++i) {
		// cache[i] = new long[1 << 2 + Math.max(0, Math.min(i, 40 - i))];
		// System.err.println(1 << 2 + Math.max(0, Math.min(i, 40 - i)));
		// }
	}

	public long getCount(final String s_) {

		s = new boolean[s_.length()];
		for (int i = 0; i < s_.length(); ++i) {
			s[i] = s_.charAt(i) == 'x';
		}

		// for (final long[] q : cache) {
		// Arrays.fill(q, -1);
		// }
		hcache.clear();
		for (int i = 0; i <= s_.length(); ++i) {
			hcache.put(i, new HashMap<Integer, Long>());
		}

		return f(0, 2);
	}

	private long f(final int processed, final int code) {
		final int internal = Integer.highestOneBit(code);
		final int history = code & ~internal & ~(internal >> 1);

		if (processed == s.length && history == 0) {
			return 1;
		}

		// if (code >= cache[processed].length) {
		// return 0;
		// }

		// final long ans = cache[processed][code];
		final Long ans = hcache.get(processed).get(code);
		// if (ans == -1) {
		if (ans == null) {
			final long calculated = f_impl(processed, code);
			hcache.get(processed).put(code, calculated);
			// cache[processed][code] = calculated;
			// System.err.println(calculated);
			return calculated;
		} else {
			return ans;
		}

	}

	private long f_impl(final int processed, final int code) {

		// System.err.printf("p=%d, code=%d\n", processed, code);

		final int internal = Integer.highestOneBit(code);
		final boolean moreRed = (code & internal >> 1) != 0;
		final int history = code & ~internal & ~(internal >> 1);
		final boolean next = (history & internal >> 2) != 0;

		final int willBeLeft = s.length - processed - 1;
		final boolean canMore = 1 << willBeLeft >= internal;

		long ans = 0;
		for (int ii = 0; ii <= 1; ++ii) {
			final boolean tryRed = ii != 0;

			if (internal == 2) {
				ans += f(processed + 1, 4 | (tryRed ? 1 : 0) << 1
						| (s[processed] ? 1 : 0));
			} else {
				if (tryRed == moreRed) {
					if (canMore) {
						ans += f(processed + 1, (code << 1)
								+ (s[processed] ? 1 : 0));
					}
				} else {
					if (next == s[processed]) {
						ans += f(processed + 1, internal >> 1
								| (moreRed ? internal : 0) >> 2 | history
								& ~(internal >> 2));
					}
				}
			}
		}

		return ans;
	}
}
