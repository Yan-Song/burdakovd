package topcoder.srm;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

public class KingSort {

	// Begin cut here

	static class Tester {

		public static void main(final String[] args) {
			try {
				eq(0,
						new KingSort().getSortedList(new String[] { "Louis IX",
								"Louis VIII" }), new String[] { "Louis VIII",
								"Louis IX" });
				eq(1,
						new KingSort().getSortedList(new String[] { "Louis IX",
								"Philippe II" }), new String[] { "Louis IX",
								"Philippe II" });
				eq(2,
						new KingSort().getSortedList(new String[] {
								"Richard III", "Richard I", "Richard II" }),
						new String[] { "Richard I", "Richard II", "Richard III" });
				eq(3,
						new KingSort().getSortedList(new String[] { "John X",
								"John I", "John L", "John V" }), new String[] {
								"John I", "John V", "John X", "John L" });
				eq(4,
						new KingSort().getSortedList(new String[] {
								"Philippe VI", "Jean II", "Charles V",
								"Charles VI", "Charles VII", "Louis XI" }),
						new String[] { "Charles V", "Charles VI",
								"Charles VII", "Jean II", "Louis XI",
								"Philippe VI" });
				eq(5,
						new KingSort().getSortedList(new String[] {
								"Philippe II", "Philip II" }), new String[] {
								"Philip II", "Philippe II" });
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

	static Map<String, Integer> reverse = new HashMap<String, Integer>();
	static {
		final String[] ones = { "", "I", "II", "III", "IV", "V", "VI", "VII",
				"VIII", "IX" };
		final String[] decs = { "", "X", "XX", "XXX", "XL", "L" };

		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j <= 5; ++j) {
				reverse.put(decs[j] + ones[i], j * 10 + i);
			}
		}
	}

	public String[] getSortedList(final String[] kings) {
		Arrays.sort(kings, new Comparator<String>() {
			@Override
			public int compare(final String o1, final String o2) {
				final String[] a1 = o1.split(" "), a2 = o2.split(" ");
				if (a1[0].compareTo(a2[0]) < 0) {
					return -1;
				}
				if (a1[0].compareTo(a2[0]) > 0) {
					return 1;
				}

				return reverse.get(a1[1]).compareTo(reverse.get(a2[1]));
			}
		});
		return kings;
	}
}
