package templates;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.Scanner;

public class Template {

    static {
	final Locale us = Locale.US;
	if (!Locale.getDefault().equals(us)) {
	    Locale.setDefault(us);
	}
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

    }
}
