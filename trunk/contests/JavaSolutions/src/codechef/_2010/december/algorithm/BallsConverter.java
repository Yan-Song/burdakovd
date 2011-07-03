package codechef._2010.december.algorithm;

public final class BallsConverter {

	// Begin cut here

	static class Tester {

		public static void main(final String[] args) {
			try {
				eq(0,
						new BallsConverter()
								.theGood(new String[] { "AB", "BA" }), "Good");
				eq(1,
						new BallsConverter()
								.theGood(new String[] { "BA", "AA" }), "Bad");
				eq(2,
						new BallsConverter().theGood(new String[] { "ACB",
								"CBA", "BAC" }), "Bad");
				eq(3,
						new BallsConverter().theGood(new String[] { "AAAA",
								"ABBB", "ABCC", "ABCD" }), "Good");
				eq(4,
						new BallsConverter().theGood(new String[] {
								"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
								"ABCDEFGHIJKLMNOPQRSTUVWXYZabcd",
								"ACEGIKMOQSUWYacACEGIKMOQSUWYac",
								"ADGJMPSVYbADGJMPSVYbADGJMPSVYb",
								"AEIMQUYcCGKOSWaAEIMQUYcCGKOSWa",
								"AFKPUZAFKPUZAFKPUZAFKPUZAFKPUZ",
								"AGMSYAGMSYAGMSYAGMSYAGMSYAGMSY",
								"AHOVcFMTaDKRYBIPWdGNUbELSZCJQX",
								"AIQYCKSaEMUcGOWAIQYCKSaEMUcGOW",
								"AJSbGPYDMVAJSbGPYDMVAJSbGPYDMV",
								"AKUAKUAKUAKUAKUAKUAKUAKUAKUAKU",
								"ALWDOZGRcJUBMXEPaHSdKVCNYFQbIT",
								"AMYGSAMYGSAMYGSAMYGSAMYGSAMYGS",
								"ANaJWFSBObKXGTCPcLYHUDQdMZIVER",
								"AOcMaKYIWGUESCQAOcMaKYIWGUESCQ",
								"APAPAPAPAPAPAPAPAPAPAPAPAPAPAP",
								"AQCSEUGWIYKaMcOAQCSEUGWIYKaMcO",
								"AREVIZMdQDUHYLcPCTGXKbOBSFWJaN",
								"ASGYMASGYMASGYMASGYMASGYMASGYM",
								"ATIbQFYNCVKdSHaPEXMBUJcRGZODWL",
								"AUKAUKAUKAUKAUKAUKAUKAUKAUKAUK",
								"AVMDYPGbSJAVMDYPGbSJAVMDYPGbSJ",
								"AWOGcUMEaSKCYQIAWOGcUMEaSKCYQI",
								"AXQJCZSLEbUNGdWPIBYRKDaTMFcVOH",
								"AYSMGAYSMGAYSMGAYSMGAYSMGAYSMG",
								"AZUPKFAZUPKFAZUPKFAZUPKFAZUPKF",
								"AaWSOKGCcYUQMIEAaWSOKGCcYUQMIE",
								"AbYVSPMJGDAbYVSPMJGDAbYVSPMJGD",
								"AcaYWUSQOMKIGECAcaYWUSQOMKIGEC",
								"AdcbaZYXWVUTSRQPONMLKJIHGFEDCB" }), "Good");
				eq(5,
						new BallsConverter()
								.theGood(new String[] {
										"AAAAAFAAAAAAAAAAAAAAAAAXAAAAcAAAAAAAAAAnAAAAAAAvAA",
										"ABBBBFBBBBBLBBBBQBBBBBBXYBBBcBBBBBBBBBBnBBBBBBBvwB",
										"ABCCCFCCCCCLMCOCQRCCCCCXYCCCcCCCCCCCCCCnCCCCsCCvwC",
										"ABCDEFGHDDDLMDODQRSDUVWXYDDbcdDfghDDklDnopDrsDDvwx",
										"ABCEEFEEEEELMEOEQRSEUVWXYEEbcEEfEhEEklEnEpEEsEEvwE",
										"FFFFFFFFFFFFFFFFFFFFFFFXFFFFcFFFFFFFFFFFFFFFFFFvFF",
										"ABCGEFGGGGGLMGOGQRSGUVWXYGGbcGGfGhGGklGnGpGGsGGvwG",
										"ABCHEFGHHHHLMHOHQRSHUVWXYHHbcdHfHhHHklHnHpHHsHHvwH",
										"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwx",
										"ABCDEFGHJJJLMJOJQRSJUVWXYJJbcdJfghJJklJnopJrsJJvwx",
										"ABCDEFGHKJKLMNOPQRSTUVWXYZKbcdefghijklmnopqrsKKvwx",
										"ALLLLFLLLLLLLLLLLLLLLLLXLLLLcLLLLLLLLLLnLLLLLLLvwL",
										"ABMMMFMMMMMLMMOMQMMMMMMXYMMMcMMMMMMMMMMnMMMMMMMvwM",
										"ABCDEFGHNJNLMNOPQRSTUVWXYZNbcdefghijklmnopqrsNNvwx",
										"ABOOOFOOOOOLOOOOQOOOOOOXYOOOcOOOOOOOOOOnOOOOOOOvwO",
										"ABCDEFGHPJPLMPOPQRSTUVWXYZPbcdPfghiPklmnopPrsPPvwx",
										"AQQQQFQQQQQLQQQQQQQQQQQXQQQQcQQQQQQQQQQnQQQQQQQvwQ",
										"ABRRRFRRRRRLMRORQRRRRRRXYRRRcRRRRRRRRRRnRRRRRRRvwR",
										"ABCSSFSSSSSLMSOSQRSSSSSXYSSScSSSSSSSSSSnSSSSsSSvwS",
										"ABCDEFGHTJTLMTOTQRSTUVWXYTTbcdTfghiTklTnopTrsTTvwx",
										"ABCUUFUUUUULMUOUQRSUUUWXYUUUcUUUUhUUklUnUUUUsUUvwU",
										"ABCVVFVVVVVLMVOVQRSVUVWXYVVbcVVfVhVVklVnVVVVsVVvwV",
										"ABCWWFWWWWWLMWOWQRSWWWWXYWWWcWWWWhWWkWWnWWWWsWWvwW",
										"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXvXX",
										"AYYYYFYYYYYLYYYYQYYYYYYXYYYYcYYYYYYYYYYnYYYYYYYvwY",
										"ABCDEFGHZJZLMZOZQRSTUVWXYZZbcdZfghiZklZnopZrsZZvwx",
										"ABCDEFGHaJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwx",
										"ABCbbFbbbbbLMbObQRSbUbWXYbbbcbbfbhbbklbnbbbbsbbvwb",
										"cccccccccccccccccccccccXcccccccccccccccccccccccvcc",
										"ABCdEFGddddLMdOdQRSdUVWXYddbcddfdhddkldndpddsddvwd",
										"ABCDEFGHeJeLMeOPQRSTUVWXYZebcdefghijklmnoperseevwx",
										"ABCffFfffffLMfOfQRSfUfWXYfffcffffhffklfnffffsffvwf",
										"ABCgEFGHgggLMgOgQRSgUVWXYggbcdgfghggklgngpggsggvwg",
										"ABChhFhhhhhLMhOhQRShhhhXYhhhchhhhhhhkhhnhhhhshhvwh",
										"ABCDEFGHiJiLMiOiQRSiUVWXYiibcdifghiiklinopirsiivwx",
										"ABCDEFGHjJjLMjOPQRSTUVWXYZjbcdjfghijklmnopjrsjjvwx",
										"ABCkkFkkkkkLMkOkQRSkkkkXYkkkckkkkkkkkkknkkkkskkvwk",
										"ABCllFlllllLMlOlQRSlllWXYlllcllllhllkllnllllsllvwl",
										"ABCDEFGHmJmLMmOmQRSTUVWXYZmbcdmfghimklmnopmrsmmvwx",
										"nnnnnFnnnnnnnnnnnnnnnnnXnnnncnnnnnnnnnnnnnnnnnnvnn",
										"ABCoEFGHoooLMoOoQRSoUVWXYoobcdofghooklonoporsoovwx",
										"ABCppFpppppLMpOpQRSpUVWXYppbcppfphppklpnpppSsppvwp",
										"ABCDEFGHqJqLMqOPQRSTUVWXYZqbcdefghijklmnopqrsqqvwx",
										"ABCrEFGHrrrLMrOrQRSrUVWXYrrbcdrfghrrklrnrSrrsrrvwx",
										"ABsssFsssssLMsOsQRsssssXYssscssssssssssnsssssssvws",
										"ABCDEFGHtJKLMNOPQRSTUVWXYZtbcdefghijklmnopqrsttvwx",
										"ABCDEFGHuJKLMNOPQRSTUVWXYZubcdefghijklmnopqrstuvwx",
										"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv",
										"AwwwwFwwwwwwwwwwwwwwwwwXwwwwcwwwwwwwwwwnwwwwwwwvww",
										"ABCxEFGHxxxLMxOxQRSxUVWXYxxbcdxfghxxklxnxpxxsxxvwx" }),
						"Bad");
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

	public static int stoi(final char c) {
		if (c >= 'A' && c <= 'Z') {
			return c - 'A';
		} else {
			return c - 'a' + 26;
		}
	}

	public String theGood(final String[] convert) {
		final String res;
		return "";
	}

}
