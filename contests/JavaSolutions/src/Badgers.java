import java.util.Arrays;

public class Badgers {

    // Begin cut here

    static class Tester {

	public static void main(final String[] args) {
	    try {
		eq(0, new Badgers().feedMost(new int[] { 1, 2, 3 }, new int[] {
			2, 2, 1 }, 7), 2);
		eq(1, new Badgers().feedMost(new int[] { 5, 2, 1, 5 },
			new int[] { 0, 2, 4, 1 }, 19), 3);
		eq(2, new Badgers().feedMost(new int[] { 1, 1, 1, 1, 1 },
			new int[] { 1000, 1000, 1000, 1000, 1000 }, 10), 1);
		eq(3,
			new Badgers().feedMost(new int[] { 1, 2, 3, 4, 5, 6, 7,
				8, 9, 10 }, new int[] { 10, 9, 8, 7, 6, 5, 4,
				3, 2, 1 }, 100), 5);
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

    public int feedMost(final int[] hunger, final int[] greed,
	    final int totalFood) {
	int res = 0;
	final int n = hunger.length;

	for (int i = 1; i <= n; ++i) {
	    final int[] total = new int[n];
	    for (int j = 0; j < n; ++j) {
		total[j] = hunger[j] + (i - 1) * greed[j];
	    }

	    Arrays.sort(total);

	    int sum = 0;
	    for (int j = 0; j < i; ++j) {
		sum += total[j];
	    }

	    if (sum <= totalFood) {
		res = i;
	    } else {
		break;
	    }
	}

	return res;
    }

}
