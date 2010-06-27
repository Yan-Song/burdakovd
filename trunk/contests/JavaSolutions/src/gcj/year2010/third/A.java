package gcj.year2010.third;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.Scanner;

public class A {

    static {
	Locale.setDefault(Locale.US);
    }

    static boolean file = true;
    static long[] primes = generatePrimes();

    static Scanner in;
    static {
	try {
	    in = new Scanner(file ? new FileInputStream("f:\\var\\tmp\\in.txt")
		    : System.in);
	} catch (final FileNotFoundException e) {
	    e.printStackTrace();
	}
    }

    static PrintWriter out;
    static {
	try {
	    out = file ? new PrintWriter(
		    new FileWriter("f:\\var\\tmp\\out.txt")) : new PrintWriter(
		    System.out);
	} catch (final IOException e) {
	    e.printStackTrace();
	}
    }

    /**
     * @param args
     */
    public static void main(final String[] args) {
	try {
	    final long t = in.nextInt();
	    for (long i = 0; i < t; ++i) {
		solve(i + 1);
		if (file) {
		    System.out.println(i + 1 + "/" + t);
		    System.out.flush();
		}
		if (!file) {
		    out.flush();
		}
	    }
	} finally {
	    in.close();
	    out.close();
	}
    }

    private static long[] generatePrimes() {
	final int mx = 1000000;
	final boolean[] isPrime = new boolean[mx + 1];
	for (int i = 0; i <= mx; ++i) {
	    isPrime[i] = true;
	}

	isPrime[0] = isPrime[1] = false;
	int count = isPrime.length - 2;

	for (int i = 2; i <= mx; ++i) {
	    if (isPrime[i]) {
		for (int j = i * 2; j <= mx; j += i) {
		    if (isPrime[j]) {
			--count;
			isPrime[j] = false;
		    }
		}
	    }
	}

	final long[] ans_ = new long[count];
	for (int i = 0, p = 0; i < count; ++i, ++p) {
	    while (!isPrime[p]) {
		++p;
	    }
	    ans_[i] = p;
	}
	return ans_;
    }

    private static void solve(final long testId) {
	final Long ans = doSolve();
	out.println("Case #" + testId + ": "
		+ (ans == null ? "I don't know." : String.valueOf(ans)));
    }

    private static Long doSolve() {
	final int d = in.nextInt(), k = in.nextInt();
	final long[] v = new long[k];
	for (int i = 0; i < k; ++i) {
	    v[i] = in.nextInt();
	}
	final long last = v[v.length - 1];
	Long ans = null;
	final long lim = (long) Math.pow(10, d);

	if (v.length > 1) {
	    for (final long p : primes) {
		if (p > lim) {
		    break;
		}

		for (long a = 0; a < p; ++a) {
		    boolean ok = true;

		    final long s = v[0];
		    final long b = (v[1] - a * s % p + p + p) % p;

		    for (int i = 1; i < v.length; ++i) {
			if (v[i] != (a * v[i - 1] + b) % p) {
			    ok = false;
			    break;
			}
		    }

		    if (ok) {
			final long newans = (a * last + b) % p;
			if (ans == null) {
			    ans = Long.valueOf(newans);
			} else {
			    if (ans.intValue() != newans) {
				System.out.flush();
				System.out.println(ans.intValue() + "  or "
					+ newans);
				return null;
			    }
			}
		    }
		}
	    }
	} else {
	    System.out.println("anything");
	}

	return ans;
    }

}
