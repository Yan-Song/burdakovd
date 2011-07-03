package spoj;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Deque;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Locale;
import java.util.Set;

public class SETSTACK {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;

	static BufferedReader in;
	static {
		try {
			// in = new Scanner(file ? new
			// FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in);
			in = new BufferedReader(new InputStreamReader(
					file ? new FileInputStream("c:\\var\\tmp\\in.txt")
							: System.in));
		} catch (final FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	static PrintWriter out;
	static {
		try {
			out = file ? new PrintWriter(
					new FileWriter("c:\\var\\tmp\\out.txt")) : new PrintWriter(
					System.out);
		} catch (final IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * @param args
	 * @throws IOException
	 * @throws NumberFormatException
	 */
	public static void main(final String[] args) throws NumberFormatException,
			IOException {
		try {
			final long t = Integer.parseInt(in.readLine());
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
			out.flush();
		}
	}

	private static final class SSet {
		private boolean hasHash = false;
		private int hash;
		private final Set<SSet> data;

		@Override
		public int hashCode() {
			if (hasHash) {
				return hash;
			} else {
				hasHash = true;

				final int prime = 319117;
				int result = 1;
				for (final SSet e : data) {
					result = prime * result
							+ (e == null ? 0 : e.hashCode() * 112987);
				}
				hash = result;
				return result;
			}
		}

		@Override
		public boolean equals(final Object obj) {
			if (this == obj) {
				return true;
			}
			if (obj == null) {
				return false;
			}
			if (getClass() != obj.getClass()) {
				return false;
			}
			final SSet other = (SSet) obj;

			return hashCode() == other.hashCode() ? true : data
					.equals(other.data);
		}

		public SSet(final Set<SSet> data) {
			this.data = data;
		}
	}

	private static void solve(final long testId) throws NumberFormatException,
			IOException {
		final int n = Integer.parseInt(in.readLine());
		final Deque<SSet> stack = new LinkedList<SETSTACK.SSet>();

		for (int i = 0; i < n; ++i) {
			final String line = in.readLine();
			if ("PUSH".equals(line)) {
				stack.push(new SSet(new HashSet<SETSTACK.SSet>()));
			} else if ("DUP".equals(line)) {
				stack.push(new SSet(new HashSet<SSet>(stack.peek().data)));
			} else if ("UNION".equals(line)) {
				final SSet ans = new SSet(new HashSet<SSet>(stack.pop().data));
				ans.data.addAll(stack.pop().data);
				stack.push(ans);
			} else if ("INTERSECT".equals(line)) {
				final SSet ans = new SSet(new HashSet<SSet>(stack.pop().data)), second = stack
						.pop();
				ans.data.retainAll(second.data);
				stack.push(ans);
			} else if ("ADD".equals(line)) {
				final SSet first = stack.pop(), ans = new SSet(
						new HashSet<SETSTACK.SSet>(stack.pop().data));
				ans.data.add(new SSet(new HashSet<SETSTACK.SSet>(first.data)));
				stack.push(ans);
			} else {
				throw new IllegalArgumentException(line);
			}
			out.println(stack.peek().data.size());
		}

		out.println("***");
	}
}
