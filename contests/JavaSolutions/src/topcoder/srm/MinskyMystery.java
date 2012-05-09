package topcoder.srm;
public class MinskyMystery {

	// Begin cut here

	static class Tester {

		public static void main(final String[] args) {
			try {
				eq(0, new MinskyMystery().computeAnswer(2L), 9);
				eq(1, new MinskyMystery().computeAnswer(3L), 27);
				eq(2, new MinskyMystery().computeAnswer(4L), 16);
				eq(3, new MinskyMystery().computeAnswer(2401L), 59058);
				eq(4, new MinskyMystery().computeAnswer(24L), 86);
				eq(5, new MinskyMystery().computeAnswer(0L), -1);
				eq(5, new MinskyMystery().computeAnswer(1L), -1);
				for (long i = 0; i < 10; ++i) {
					System.out.printf("f(%d) = %d\n", i,
							new MinskyMystery().computeAnswer(i));
					System.out.flush();
				}

				for (long i = 0; i < 10; ++i) {
					System.out.printf("f(%d) = %d\n", i * 100,
							new MinskyMystery().computeAnswer(i * 100));
					System.out.flush();
				}

				for (long i = 0; i < 10; ++i) {
					System.out.printf("f(%d) = %d\n", i * 1000000,
							new MinskyMystery().computeAnswer(i * 1000000));
					System.out.flush();
				}

				for (long i = 0; i < 10; ++i) {
					System.out.printf("f(%d) = %d\n", i * 1000000000,
							new MinskyMystery().computeAnswer(i * 1000000000));
					System.out.flush();
				}

				for (long i = 0; i <= 10; ++i) {
					System.out.printf("f(%d) = %d\n", i * 100000000000L,
							new MinskyMystery()
									.computeAnswer(i * 100000000000L));
					System.out.flush();
				}
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

	public int computeAnswer(final long N) throws Exception {
		if (N < 2) {
			return -1;
		}
		final int ans1 = fast(N);
		final int ans2 = naive(N);
		if (ans1 == ans2) {
			return ans1;
		} else {
			throw new Exception();
		}
	}

	final long MOD = 1000000009;

	private int naive(final long n) {
		long ans = 1;
		long a = n, b = 1, c = 0, d = 0, e = 0;

		while (true) {
			++b;
			ans = (ans + 1) % MOD;
			e = 0;
			while (a > 0) {
				final long q = Math.min(a, b);
				a -= q;
				b -= q;
				c += q;
				d += q;
				++e;
				ans = (ans + 2 * q + 1) % MOD;
				if (a == 0 && b == 0) {
					e += d;
					ans = (ans + d) % MOD;
					d = 0;
					return (int) ans;
				}
				b += d;
				ans = (ans + d) % MOD;
				d = 0;
			}
			a += c;
			ans = (ans + c) % MOD;
			c = 0;
		}
	}

	private int fast(final long n) {
		long ans = 1;
		for (long b = 2;; ++b) {
			final long k = n / b, x = n % b;
			if (x > 0) {
				ans = (ans + 1 + k * (3 * b + 1) + 3 * x + 1 + n) % MOD;
			} else {
				ans = (ans + 1 + k * (3 * b + 1)) % MOD;
				return (int) ans;
			}
		}
	}
}
