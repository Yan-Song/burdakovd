package spoj;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Locale;
import java.util.Map;
import java.util.Scanner;

public final class FIBOBASE {

	static {
		final Locale us = Locale.US;
		if (!Locale.getDefault().equals(us)) {
			Locale.setDefault(us);
		}
	}

	static boolean file = false;

	static Scanner in;
	static {
		try {
			in = new Scanner(file ? new FileInputStream("c:\\var\\tmp\\in.txt")
					: System.in);
			// in = new BufferedReader(new InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in));
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
	 */
	public static void main(final String[] args) {
		try {

			solve();

		} finally {
			out.flush();
		}
	}

	private static void solve() {

		final long n = in.nextLong();
		out.println(solve(n));
		out.flush();
		while (true) {
			;
		}
	}

	private static long solve(final long n) {
		final long partial = partialGroupNumber(n);
		return onesInFirstGroups(partial)
				+ processPartialGroup(partial, n - summaryGroupsWidth(partial));
	}

	private static long summaryGroupsWidth(final long count) {
		long ans = 0;
		for (int i = 0; i < count; ++i) {
			ans += (i + 1) * length(i);
		}
		return ans;
	}

	private static long processPartialGroup(final long partialGroupId,
			final long n) {
		if (n == 0) {
			return 0;
		} else {
			final long width = partialGroupId + 1;
			final long numbers = n / width;
			final long remainder = n % width;

			return onesInFirstRowsOfGroup(numbers)
					+ onesInPartialNumber(summaryGroupsLength(partialGroupId)
							+ numbers + 1, remainder);

		}
	}

	private static long onesInFirstRows(final long rows) {
		if (rows == 0) {
			return 0;
		}

		out.println(String.format("onesInFirstRows(%d)", rows));
		out.flush();

		final long partialId = partialGroupIdByRowCount(rows);

		return onesInFirstGroups(partialId)
				+ onesInFirstRowsOfGroup(rows - summaryGroupsLength(partialId));
	}

	private static long onesInFirstRowsOfGroup(final long rows) {

		long ans = rows;
		if (rows > 0) {
			ans += onesInFirstRows(rows - 1);
		}
		return ans;
	}

	private static long partialGroupIdByRowCount(final long rows) {

		long left = rows, id = 0;
		while (length(id) <= left) {
			left -= length(id);
			++id;
		}
		return id;
	}

	private static long onesInPartialNumber(final long n,
			final long firstDigitsCount) {

		long maxN = 0;
		while (fib(maxN + 1) <= n) {
			++maxN;
		}

		long ans = 0;
		long left = n;
		for (long i = 0; i < firstDigitsCount; ++i) {
			final long candidate = fib(maxN - i);
			if (candidate <= left) {
				++ans;
				left -= candidate;
			}
		}

		return ans;
	}

	private static long summaryGroupsLength(final long groupCount) {
		return fib(groupCount + 1) - 1;
	}

	static final Map<Long, Long> cachedOnesInFirstGroups = new HashMap<Long, Long>();

	private static long onesInFirstGroups(final long groupCount) {
		if (groupCount == 0) {
			return 0;
		} else {
			final Long cached = cachedOnesInFirstGroups.get(groupCount);
			if (cached == null) {
				final long ans = onesInFirstGroups(groupCount - 1)
						+ onesInGroup(groupCount - 1);
				cachedOnesInFirstGroups.put(groupCount, ans);
				return ans;
			} else {
				return cached;
			}
		}
	}

	static final Map<Long, Long> cachedOnesInGroup = new HashMap<Long, Long>();

	private static long onesInGroup(final long groupId) {
		if (groupId < 2) {
			return 1;
		} else {
			final Long cached = cachedOnesInGroup.get(groupId);
			if (cached == null) {
				final long ans = length(groupId)
						+ onesInFirstGroups(groupId - 1);
				cachedOnesInGroup.put(groupId, ans);
				return ans;
			} else {
				return cached;
			}
		}
	}

	private static long length(final long groupId) {
		return fib(groupId);
	}

	static final Map<Long, Long> fibs = new HashMap<Long, Long>();

	/**
	 * 1 1 2 3 5...
	 * <p>
	 * numbered from 0
	 * 
	 * @param n
	 * @return
	 */
	private static long fib(final long n) {
		final Long cached = fibs.get(n);

		if (cached == null) {

			long cur = 1, prev = 0;
			for (int i = 0; i < n; ++i) {
				cur += prev;
				prev = cur - prev;
			}
			fibs.put(n, cur);
			return cur;
		} else {
			return cached;
		}
	}

	private static long partialGroupNumber(final long n) {
		long left = n;
		long id = 0;

		while (left >= length(id) * (id + 1)) {
			left -= length(id) * (id + 1);
			++id;
		}

		return id;
	}
}
