package topcoder.srm;

public class TwoRegisters {

    // Begin cut here

    static class Tester {

	public static void main(final String[] args) {
	    try {
		eq(0, new TwoRegisters().minProg(10), "XXYYX");
		eq(1, new TwoRegisters().minProg(3), "XX");
		eq(2, new TwoRegisters().minProg(20), "XYYYYXX");
		eq(3, new TwoRegisters().minProg(34), "XYXYXYX");

		for (int i = 1000000;; --i) {
		    System.out.println("ans for r = " + i + " is "
			    + new TwoRegisters().minProg(i));
		}
	    } catch (final Exception exx) {
		System.err.println(exx);
		exx.printStackTrace(System.err);
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

    public static void main(final String[] args) {
	Tester.main(args);
    }

    // End cut here

    public String minProg(final int r) {
	if (r == 1) {
	    return "";
	}

	String ans = null;
	@SuppressWarnings("unused")
	int ansy = -1;

	for (int ey = 1; ey < r; ++ey) {
	    int x = r, y = ey;

	    final StringBuilder builder = new StringBuilder();

	    while ((x > 1 || y > 1) && x > 0 && y > 0 && builder.length() < 50) {
		if (x > y) {
		    builder.append('X');
		    x -= y;
		} else {
		    builder.append('Y');
		    y -= x;
		}
	    }

	    if (x == 1 && y == 1) {
		final String candidate = builder.reverse().toString();
		//System.out.println("for ey = " + ey + " ; ans = " + candidate);
		if (ans == null || candidate.length() < ans.length()
			|| candidate.length() == ans.length()
			&& candidate.compareTo(ans) < 0) {
		    ans = candidate;
		    ansy = ey;
		}
	    }
	}

	assert ans != null;

	//System.out.println("for r = " + r + " ey is " + ansy);

	return ans;
    }
}
