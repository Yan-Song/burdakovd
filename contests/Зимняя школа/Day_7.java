import java.util.*;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.math.*;


public class Day_7  {
	
	
	static BigInteger binSqrt(BigInteger a){
		BigInteger left = BigInteger.ONE;
		BigInteger right = a;
		
		while( right.subtract(left).compareTo(BigInteger.ONE) == 1 )
		{
			BigInteger m = left.add(right).divide(new BigInteger("2"));
			
			BigInteger q = m.multiply(m);
			
			if(q.compareTo(a) == -1)
			{
				left = m;
			}
			else
				if(q.compareTo(a) == 1)
				{
					right = m;
				}
				else
					return m;
			
		}
		
		return new BigInteger("-1");
	}
	
	static boolean ok(BigInteger a){
		if(a.isProbablePrime(30))
			return true;
		
		BigInteger b = binSqrt(a);
//		out.println(b);
//		out.flush();
		if(
				(!b.equals(new BigInteger("-1")))
						&& (!b.equals(new BigInteger("2")))
						&& (b.isProbablePrime(30) == true))
						
			return true;
		
		
		long ai = Long.parseLong(a.toString());
		
		
		for(int i = 2; i < 1000000; ++i)
			if(ai % i == 0){
				if(i == 2) return false;
				while(ai % i == 0 && ai != 1)
					ai /= i;
				return ai == 1;
			}
		
		return false;
		
	}
	static Scanner in;
	static PrintWriter out;

	public static void main(String[] args) throws Exception {
//		in = new Scanner(System.in);
	//	out = new PrintWriter(System.out);

		in = new Scanner(new FileReader("j.in"));
		out = new PrintWriter(new FileWriter("j.out"));
		int p = in.nextInt();
		int q = in.nextInt();
		
		
		String s = in.next();
		
		BigInteger a = new BigInteger(s, p);
		
		out.println(a.toString(q).toUpperCase());
		out.flush();
		
		
	}

}
