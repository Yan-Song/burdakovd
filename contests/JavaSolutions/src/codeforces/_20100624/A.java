package codeforces._20100624;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Locale;
import java.util.Scanner;

public class A {

    static class Team {
	final String name;
	int points = 0;
	int good = 0;
	int bad = 0;

	Team(final String name) {
	    this.name = name;
	}
    }

    static {
	Locale.setDefault(Locale.US);
    }

    static boolean file = true;

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

    private static void solve(final long testId) {
	final HashMap<String, Team> teams = new HashMap<String, Team>();

	final int n = in.nextInt();

	for (int i = 0; i < n; ++i) {
	    // teams[in.]
	}
    }
}
