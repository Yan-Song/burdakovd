package topcoder.srm;
public class CarrotJumping {

	// Begin cut here

	static class Tester {

		public static void main(final String[] args) {
			try {
				eq(0, new CarrotJumping().theJump(125000000), 1);
				eq(1, new CarrotJumping().theJump(281250001), 2);
				eq(2, new CarrotJumping().theJump(18426114), 58);
				eq(3, new CarrotJumping().theJump(4530664), 478);
				eq(4, new CarrotJumping().theJump(705616876), 100000);
				eq(5, new CarrotJumping().theJump(852808441), -1);
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

	public int theJump(final int init) {
		long pos = init;

		long count = 0;
		while (pos != 0 && count < 1000000) {
			pos = (2 * pos + 1) % 1000000007;
			++count;
		}

		if (pos == 0) {
			if (count == 1) {
				return -1;
			} else {
				long ans = 0;
				while (count % 3 != 0) {
					++ans;
					count -= 2;
				}
				ans += count / 3;
				return (int) (ans <= 100000 ? ans : -1);
			}
		} else {
			return -1;
		}

	}
}
