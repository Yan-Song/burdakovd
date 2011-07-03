package codechef._2010.december.algorithm;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.PrintWriter;
import java.io.StreamTokenizer;
import java.util.Arrays;

public final class DELIVERY {

	private static final class Util {

		private static final class Heap {

			private final static int HEAP_SIZE = 16384;

			long[] data = new long[HEAP_SIZE];
			int count = 0;

			public Heap() {
			}

			public void add(final long element) {
				++count;
				replace(count - 1, element);
			}

			void build(final long[] source, final int n) {
				count = n;
				System.arraycopy(source, 0, data, 0, n);
				for (int i = (count >> 1) - 1; i != -1; --i) {
					heapify(i);
				}
			}

			private void heapify(final int node) {
				for (int i = node;;) {
					final int l = (i << 1) + 1;
					final int r = l + 1;

					int largest = i;
					if (l < count && data[l] < data[largest]) {
						largest = l;
					}
					if (r < count && data[r] < data[largest]) {
						largest = r;
					}

					if (largest != i) {
						final long t = data[largest];
						data[largest] = data[i];
						data[i] = t;
						i = largest;
					} else {
						break;
					}
				}
			}

			public boolean isEmpty() {
				return count == 0;
			}

			public long poll() {
				if (count == 0) {
					throw new RuntimeException("Куча пуста");
				}

				final long headElement = data[0];
				--count;
				data[0] = data[count];
				heapify(0);
				return headElement;
			}

			public void replace(final int position, final long value) {
				data[position] = value;
				heapify(position);

				for (int i = position, p = i - 1 >> 1; i > 0
						&& data[p] > data[i]; i = p, p = i - 1 >> 1) {
					final long t = data[p];
					data[p] = data[i];
					data[i] = t;
				}
			}
		};

		private static final class Random {

			private long seed;

			private final static long multiplier = 0x5DEECE66DL;
			private final static long addend = 0xBL;
			private final static long mask = (1L << 48) - 1;
			private final static float nextFloatDenominator = 1.0f / (1 << 24);

			public Random(final long seed) {
				setSeed(seed);
			}

			int next(final int bits) {
				seed = seed * multiplier + addend & mask;
				return (int) (seed >> 48 - bits);
			}

			public float nextFloat() {
				return next(24) * nextFloatDenominator;
			}

			public void setSeed(final long seed_) {
				seed = (seed_ ^ multiplier) & mask;
			}
		};

		private static final class Scanner {

			private static final int readBufferLength = 1 << 16;
			private static final byte char0 = '0';

			private final byte[] readBuffer = new byte[readBufferLength];
			private final int curPos = readBufferLength;
			private final StreamTokenizer in;

			public Scanner(final InputStream stream) {
				in = new StreamTokenizer(new BufferedReader(
						new InputStreamReader(stream)));
			}

			public int nextInt() throws IOException {
				/*
				 * int left = readBufferLength - curPos; if (left < 64) {
				 * System.arraycopy(readBuffer, curPos, readBuffer, 0, left);
				 * int needRead = readBufferLength - left;
				 * 
				 * while (needRead > 0) { final int read = in.read(readBuffer,
				 * left, needRead); left += read; needRead -= read; if (read <
				 * 0) { break; } } curPos = 0; }
				 * 
				 * while (readBuffer[curPos] < char0) { ++curPos; }
				 * 
				 * int ans = 0; for (byte c = readBuffer[curPos]; c >= char0;
				 * ++curPos, c = readBuffer[curPos]) { ans = ans * 10 + c -
				 * char0; }
				 * 
				 * return ans;
				 */
				in.nextToken();
				return (int) in.nval;
			}
		}

	}

	private static final class Shared {
		static boolean file = false;
		static boolean isLocal = false;
		static DELIVERY.Util.Scanner in;
		static PrintWriter out;
		static PrintStream err = System.err;
		private static float KPD = 40;

		private static DELIVERY.Util.Random gen = new DELIVERY.Util.Random(17L);

		private static void initializeIO() throws IOException {

			in = new DELIVERY.Util.Scanner(file ? new FileInputStream(
					"c:\\var\\tmp\\in.txt") : System.in);

			// in = new BufferedReader(new InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in));

			// in = new StreamTokenizer(new BufferedReader(new
			// InputStreamReader(
			// file ? new FileInputStream("c:\\var\\tmp\\in.txt")
			// : System.in)));

			out = Shared.file ? new PrintWriter(new FileWriter(
					"c:\\var\\tmp\\jout.txt")) : new PrintWriter(System.out);
		}
	}

	private static final class Constants {
		private static final int ANT_COUNT = 8;
		private static final float MAX_KARMA = 100000.0f;
		private static final int K_LIMIT = 10000;
		private static final int MAXN = 300;
	}

	private static final class Tmp {
		private static final int[][] distancesMatrix = new int[Constants.MAXN][Constants.MAXN];
		private static final long[] dijkstraInit = new long[Constants.MAXN];
		private static final DELIVERY.Util.Heap dijkstraQueue = new DELIVERY.Util.Heap();
		private static final float[] probs = new float[Constants.MAXN];
		private static final int[] distancesFromStart = new int[Constants.MAXN];
		private static final boolean[] dijkstraIsVertexProcessed = new boolean[Constants.MAXN];
		private static final int[][] solutionsByAntOnCurrentIteration = new int[Constants.ANT_COUNT][Constants.K_LIMIT + 4];
		private static final int[] verticesVisitedByAntOnCurrentIteration = new int[Constants.ANT_COUNT];
		private static final int[] numberOfTimesVertexVisitedByCurrentAnt = new int[Constants.MAXN];
		private static final float[] invertedMagicNumberOfTimesVertexVisitedByCurrentAnt = new float[Constants.MAXN];
	}

	private static final class Solver {

		private final static float[][] karmaOfEdgeFromVertexToNeighbours = new float[Constants.MAXN][Constants.MAXN];
		private final static float[][] karma_mul_InvertedMagicDistances = new float[Constants.MAXN][Constants.MAXN];
		private final static int[][] neighboursByVertex = new int[Constants.MAXN][Constants.MAXN];
		private final static int[][] distancesFromVertexToNeighbours = new int[Constants.MAXN][Constants.MAXN];
		private final static float[][] invertedMagicDistancesFromVertexToNeighbours = new float[Constants.MAXN][Constants.MAXN];

		private final static int[] neighboursCounts = new int[Constants.MAXN];
		private final static int[] bestSolutionForNow = new int[Constants.K_LIMIT + 4];
		private final static int[] distanceToNearestNeighbour = new int[Constants.MAXN];
		private final static int[] resultByFirstIterations = new int[10000];
		private final static long[] timeSpentByFirstIterations = new long[10000];

		private static int bestVisited;
		private static int iterations;
		private static int lastEnhance;
		private final static int elitistCount = 4;
		private static int n;
		private static int b;
		private static int possibleToVisitCount;

		public static void ctorSolver() throws IOException {

			Shared.gen.setSeed(1000000007L);

			n = Shared.in.nextInt();
			int m = Shared.in.nextInt();
			b = Shared.in.nextInt();

			for (int i = 0; i < n; ++i) {
				Arrays.fill(Tmp.distancesMatrix[i], 0, n, b + 1);
			}

			Arrays.fill(neighboursCounts, 0, n, 0);
			for (int i = m, j = 0; i > 0; --i) {
				final int u = Shared.in.nextInt();
				final int v = Shared.in.nextInt();
				final int d = Shared.in.nextInt();
				if (d <= b) {
					Tmp.distancesMatrix[u][v] = d;
					++neighboursCounts[u];
					++j;
				} else {
					--m;
				}
			}

			// out.println(-1);
			// if (1 == 1) {
			// return;
			// }

			for (int i = 0; i < n; ++i) {
				final int[] row = neighboursByVertex[i];
				final int[] aRow = Tmp.distancesMatrix[i];
				for (int j = 0, k = 0; j < n; ++j) {
					if (aRow[j] <= b) {
						row[k] = j;
						++k;
					}
				}
			}

			System.arraycopy(Tmp.distancesMatrix[0], 0, Tmp.distancesFromStart,
					0, n);
			Tmp.distancesFromStart[0] = 0;
			Arrays.fill(Tmp.dijkstraIsVertexProcessed, 0, n, false);

			final int[] row0 = neighboursByVertex[0];
			final int count0 = neighboursCounts[0];
			for (int i = 0; i < count0; ++i) {
				final int neighbour = row0[i];
				final long distance = Tmp.distancesFromStart[neighbour];
				Tmp.dijkstraInit[i] = distance << 32 | neighbour;
			}

			Tmp.dijkstraQueue.build(Tmp.dijkstraInit, count0);

			while (!Tmp.dijkstraQueue.isEmpty()) {
				final long packed = Tmp.dijkstraQueue.poll();
				final int nearest = (int) packed;

				if (!Tmp.dijkstraIsVertexProcessed[nearest]) {
					Tmp.dijkstraIsVertexProcessed[nearest] = true;
					final int[] neighboursOfNearest = neighboursByVertex[nearest];
					final int[] aRow = Tmp.distancesMatrix[nearest];
					final int maxI = neighboursCounts[nearest];
					final int nDistance = Tmp.distancesFromStart[nearest];

					for (int i = 0; i < maxI; ++i) {
						final int next = neighboursOfNearest[i]; // при сложении
																	// проверяем
																	// на
																	// переполнение
						final int newDistance = Math.min(b + 1, nDistance
								+ aRow[next]);
						final int oldDistance = Tmp.distancesFromStart[next];

						if (newDistance < oldDistance) {
							Tmp.distancesFromStart[next] = newDistance;
							Tmp.dijkstraQueue.add((long) newDistance << 32
									| next);
						}
					}
				}
			}

			// избавиться от недоступных ребер
			for (int u = 0; u < n; ++u) {
				final int[] neighboursOfU = neighboursByVertex[u];
				final int[] distancesFromU = Tmp.distancesMatrix[u];
				final int oldCount = neighboursCounts[u];
				int newCount = 0;
				for (int i = 0; i < oldCount; ++i) {
					final int v = neighboursOfU[i];
					final boolean reachable = Tmp.distancesFromStart[u]
							+ distancesFromU[v] <= b;
					if (reachable) {
						if (i != newCount) {
							neighboursOfU[newCount] = v;
						}
						++newCount;
					}
				}
				neighboursCounts[u] = newCount;
				final int[] newDistances = distancesFromVertexToNeighbours[u];
				distanceToNearestNeighbour[u] = b + 1;
				for (int i = 0; i < newCount; ++i) {
					final int currentDistance = distancesFromU[neighboursOfU[i]];
					distanceToNearestNeighbour[u] = Math.min(
							distanceToNearestNeighbour[u], currentDistance);
					newDistances[i] = currentDistance;
				}
			}

			possibleToVisitCount = 1;
			for (int i = 1; i < n; ++i) {
				if (Tmp.distancesFromStart[i] <= b) {
					++possibleToVisitCount;
				}
			}

			for (int i = 0; i < n; ++i) {
				final int w = neighboursCounts[i];
				final float[] invRow = invertedMagicDistancesFromVertexToNeighbours[i];
				final int[] rRow = distancesFromVertexToNeighbours[i];

				for (int j = 0; j < w; ++j) {
					invRow[j] = 1.0f / (0.1f + rRow[j]);
				}
			}

			bestVisited = 0;

			iterations = 0;
			lastEnhance = -1;
			resetKarma(n, true);

		}

		private static int chooseNext(
				final int[] candidates,
				final int candidatesCount,
				final int[] distancesFromCurrent,
				final float[] invertedMagicDistancesFromCurrent,
				final int[] visited,
				final float[] invertedMagicVisited,
				final int ant,
				final int timeLeft,
				final float[] karmaFromCurrent,
				final float[] karmaFromCurrentMulInvertedMagicDistancesFromCurrent) {

			final int n = candidatesCount;
			final boolean takeAttentionOnLengths = ant > 0;
			final float[] magicMultiplier = takeAttentionOnLengths ? karmaFromCurrentMulInvertedMagicDistancesFromCurrent
					: karmaFromCurrent;

			float total = 0.0f;

			for (int i = 0; i < n; ++i) {

				final int distance = distancesFromCurrent[i];
				if (distance <= timeLeft) {
					final int next = candidates[i];
					// if (visited[next] == 0
					// || distance + distanceToNearestNeighbour[next] <=
					// timeLeft) {
					total += magicMultiplier[i] * invertedMagicVisited[next];
					// }
				}

				Tmp.probs[i] = total;
			}

			final float position = Shared.gen.nextFloat() * total;

			if (n < 16) {
				for (int i = 0; i < n; ++i) {
					if (position <= Tmp.probs[i]) {
						return i;
					}
				}
				return n - 1;
			} else {
				int l = 0, r = n - 1;

				while (l < r) {
					final int m = l + r >> 1;

					if (position <= Tmp.probs[m]) {
						r = m;
					} else {
						l = m + 1;
					}

				}

				return l;
			}
		}

		private static float makeMagicVisited(final int timesVisited) {
			return 1.0f / (timesVisited << 8 | 1);
		}

		private static void resetKarma(final int n, final boolean force) {

			if (force) {
				final float initialKarma = Math.max(n / 3.0f, 2.0f);
				for (int i = 0; i < n; ++i) {
					Arrays.fill(karmaOfEdgeFromVertexToNeighbours[i], 0,
							neighboursCounts[i], initialKarma);
				}
			} else {
				for (int i = 0; i < n; ++i) {
					final float[] row = karmaOfEdgeFromVertexToNeighbours[i];
					final int w = neighboursCounts[i];
					for (int j = 0; j < w; ++j) {
						row[j] = (float) Math.sqrt(row[j]);
					}
				}
			}

			for (int u = 0; u < n; ++u) {
				final int w = neighboursCounts[u];
				final float[] row = karma_mul_InvertedMagicDistances[u];
				final float[] karmaRow = karmaOfEdgeFromVertexToNeighbours[u];
				final float[] imdRow = invertedMagicDistancesFromVertexToNeighbours[u];

				for (int j = 0; j < w; ++j) {
					row[j] = karmaRow[j] * imdRow[j];
				}
			}
		}

		public static void solve(final long testId, final long deadline,
				final long t) throws IOException {

			// final long loopStart = System.nanoTime();
			// final long guaranteedTime = 5 * 1000000;

			for (boolean hasBestSolution = false; // iterations < 100
			; ++iterations) {

				resultByFirstIterations[iterations] = bestVisited;
				// final long now = System.nanoTime();
				// timeSpentByFirstIterations[iterations] = now;

				if (hasBestSolution) {

					// if (now > deadline) {
					if (testId == t - 1) {
						// break;
					}
					// }

					/*
					 * final float currentKPD = Math .max(
					 * 
					 * (bestVisited - resultByFirstIterations[iterations * 2 /
					 * 3]) 1.0f / (now - timeSpentByFirstIterations[iterations *
					 * 2 / 3]),
					 * 
					 * (bestVisited - resultByFirstIterations[Math
					 * .max(iterations - 100, 0)]) 1.0f / (now -
					 * timeSpentByFirstIterations[Math .max(iterations - 100,
					 * 0)])
					 * 
					 * );
					 */

					// if (currentKPD < 0) {
					// throw new RuntimeException();
					// }

					final boolean shouldContinue = iterations < 100
					// currentKPD > Shared.KPD * 1e-9
					;
					// || System.nanoTime() - loopStart < guaranteedTime
					// || bestVisited * 1000000000L
					// / (System.nanoTime() - loopStart) > KPD;
					// && delta != 0
					// && iterations - 1 <= Math.max(lastEnhance * 1.5f,
					// 100.0);
					// && (iterations <= 100.0f || iterations <= lastEnhance
					// *
					// 1.5f)
					// &&
					// (iterations <= lastEnhance * 1.5f || iterations <=
					// lastEnhance +
					// 100);
					;

					if (!shouldContinue) {
						break;
					}

				}

				int solutionsFound = 0;
				for (int ant = 0; ant < Constants.ANT_COUNT; ++ant) {
					final int start = 0;
					int current = start;
					int left = b;
					final int[] currentSolution = Tmp.solutionsByAntOnCurrentIteration[solutionsFound];
					currentSolution[0] = 0;

					Arrays.fill(Tmp.numberOfTimesVertexVisitedByCurrentAnt, 0,
							n, 0);
					Arrays.fill(
							Tmp.invertedMagicNumberOfTimesVertexVisitedByCurrentAnt,
							0, n, makeMagicVisited(0));

					++Tmp.numberOfTimesVertexVisitedByCurrentAnt[current];
					Tmp.invertedMagicNumberOfTimesVertexVisitedByCurrentAnt[current] = makeMagicVisited(Tmp.numberOfTimesVertexVisitedByCurrentAnt[current]);

					int visitedCount = 1;

					for (int k = 0; k < Constants.K_LIMIT; ++k) {

						final int[] candidates = neighboursByVertex[current];
						final int candidatesCount = neighboursCounts[current];
						final int[] distancesFromCurrent = distancesFromVertexToNeighbours[current];
						if (candidatesCount == 0) {
							break; // провал
						}

						final int iNext = chooseNext(
								candidates,
								candidatesCount,
								distancesFromCurrent,
								invertedMagicDistancesFromVertexToNeighbours[current],
								Tmp.numberOfTimesVertexVisitedByCurrentAnt,
								Tmp.invertedMagicNumberOfTimesVertexVisitedByCurrentAnt,
								ant, left,
								karmaOfEdgeFromVertexToNeighbours[current],
								karma_mul_InvertedMagicDistances[current]);

						left -= distancesFromCurrent[iNext];

						if (left >= 0) {
							current = candidates[iNext];
							if (Tmp.numberOfTimesVertexVisitedByCurrentAnt[current] == 0) {
								++visitedCount;
							}
							++Tmp.numberOfTimesVertexVisitedByCurrentAnt[current];
							Tmp.invertedMagicNumberOfTimesVertexVisitedByCurrentAnt[current] = makeMagicVisited(Tmp.numberOfTimesVertexVisitedByCurrentAnt[current]);
							currentSolution[++currentSolution[0]] = iNext;
							if (visitedCount == possibleToVisitCount) {
								break;
							}
						} else {
							break;
						}
					}

					if (Shared.isLocal) {
						// Shared.err.println("Found solution "
						// + Arrays.toString(Arrays.copyOfRange(
						// currentSolution, 1,
						// currentSolution[0] + 1))
						// + " with visited = " + visitedCount);
					}

					Tmp.verticesVisitedByAntOnCurrentIteration[solutionsFound] = visitedCount;
					++solutionsFound;

					if (visitedCount == possibleToVisitCount) {
						break;
					}
				}

				for (int ant = 0; ant < solutionsFound; ++ant) {

					final int[] currentSolution = Tmp.solutionsByAntOnCurrentIteration[ant];
					final int currentlyVisited = Tmp.verticesVisitedByAntOnCurrentIteration[ant];
					final int deltaKarma = currentlyVisited;

					updateKarma(currentSolution, deltaKarma, b);

					if (bestVisited < currentlyVisited) {
						System.arraycopy(currentSolution, 0,
								bestSolutionForNow, 0, currentSolution[0] + 1);
						hasBestSolution = true;
						bestVisited = currentlyVisited;
						lastEnhance = iterations;
						if (Shared.isLocal) {
							// Shared.err.println("On " + iterations
							// + " iterations, answer is " + bestVisited);
						}
						if (bestVisited == possibleToVisitCount) {
							break;
						}
					}
				}

				if (bestVisited == possibleToVisitCount) {
					break;
				}

				if (iterations > Math.max(lastEnhance * 1.5f,
						lastEnhance + 100.0f)
				// && testId != t // todo: при финальной сдаче расскоментировать
				// эту
				// строку
				) {
					// break;
					/*
					 * iterations = 0; lastEnhance = -1; resetKarma(n, false);
					 * --elitistCount;
					 */
				}

				updateKarma(bestSolutionForNow, elitistCount * bestVisited, b);

				final float removalCoefficient = 0.95f;

				for (int u = 0; u < n; ++u) {
					final int w = neighboursCounts[u];
					final float[] karmaRow = karmaOfEdgeFromVertexToNeighbours[u];
					final float[] kmimdRow = karma_mul_InvertedMagicDistances[u];

					for (int j = 0; j < w; ++j) {
						karmaRow[j] *= removalCoefficient;
						kmimdRow[j] *= removalCoefficient;
					}
				}

			}

			if (Shared.isLocal) {
				Shared.err.println("Ran " + iterations + " iterations");
			}

			int current = 0;
			final int bestSolutionLength = bestSolutionForNow[0];
			for (int i = 1; i <= bestSolutionLength; ++i) {
				final int movement = bestSolutionForNow[i];
				current = neighboursByVertex[current][movement];
				Shared.out.print(current + " ");
			}

			Shared.out.println(-1);
		}

		private static void updateKarma(final int[] currentSolution,
				final int deltaKarma, final int b) {

			int current = 0;
			final int movementsCount = currentSolution[0];

			for (int i = 1; i <= movementsCount; ++i) {
				final int movement = currentSolution[i];
				final float result = Math.min(
						karmaOfEdgeFromVertexToNeighbours[current][movement]
								+ deltaKarma, Constants.MAX_KARMA);
				karmaOfEdgeFromVertexToNeighbours[current][movement] = result;
				karma_mul_InvertedMagicDistances[current][movement] = result
						* invertedMagicDistancesFromVertexToNeighbours[current][movement];
				current = neighboursByVertex[current][movement];
			}

		}

	}

	public static void main(final String[] args) throws IOException {
		Shared.initializeIO();
		Shared.isLocal |= args.length > 0 && args[0].equals("local");

		if (Shared.isLocal) {
			Shared.err.println("Local run");
		}

		try {

			// final long startTime = System.nanoTime();
			// final long globalDeadline = startTime + 9000000000L;

			final int t = Shared.in.nextInt();

			// final double plannedTimePerCase = (globalDeadline - startTime)
			// / (t + 1);

			final double timeBonusOverdrive = 1.5;

			for (int i = 0; i < t; ++i) {

				final long now = System.nanoTime();

				// времени до глобального дэдлайна
				// final long timeLeft = globalDeadline - now;

				// осталось кейсов после текущего
				final double casesLeft = t - i;

				// время, которое этот кейс должен получить гарантированно
				// (если делить оставшееся время по-братски)
				// учитывает возможное отставание или опережение графика
				// это время будет выдано, несмотря на ограничения ниже
				// final double guaranteedTime = timeLeft / casesLeft;

				// времени зарезервировано на последующие кейсы (по плану)
				// сейчас можно увеличить время на этот кейс, но нельзя забирать
				// у остальных то, что им положено по плану
				// final double reservedTimeForOthers = (casesLeft - 1)
				// * plannedTimePerCase;

				// излишки времени, сэкономленные предыдущими тесткейсами
				// может быть отрицательным, если были задержки
				// в пределах этих излишков можно выделить текущему тест-кейсу
				// дополнительное время
				// final double freeTimeForThis = timeLeft -
				// reservedTimeForOthers;

				// final long canSpendNow = (long) Math.max(
				// guaranteedTime,
				// Math.min(freeTimeForThis, timeBonusOverdrive
				// * guaranteedTime));

				// final boolean beforePlan = System.nanoTime() - startTime <
				// (globalDeadline - startTime)
				// * i / t;

				// if (beforePlan) {
				// Shared.KPD = Math.max(Shared.KPD - 0.3f, 1.0f);
				// } else {
				// Shared.KPD += 0.3f;
				// }

				Solver.ctorSolver();
				Solver.solve(i + 1,
				// now + canSpendNow
						0, t);

				if (Shared.file) {
					Shared.err.println(i + 1 + "/" + t);
				}
				if (Shared.isLocal && !Shared.file) {
					Shared.out.flush();
				}
			}

			if (Shared.isLocal) {
				// Shared.err.println(String.format("Completed after %d ms.",
				// (System.nanoTime() - startTime) / 1000000));
			}

		} finally {
			Shared.out.flush();
		}
	}

}
