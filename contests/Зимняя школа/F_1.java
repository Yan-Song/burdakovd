import java.util.*;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.math.*;


public class F_1 {
	
	
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
		in = new Scanner(new FileReader("f1.in"));
		out = new PrintWriter(new FileWriter("f1.out"));
		
		BigInteger a = in.nextBigInteger();
		BigInteger orig = a;
		
		if(a.compareTo(new BigInteger("7")) == -1)
		{
			out.print(a.subtract(BigInteger.ONE));
			out.close();
			return;
		}
		
		if(a.mod(new BigInteger("2")).compareTo(new BigInteger("0"))==0){
			a = a.divide(new BigInteger("2"));
		}
		
		if(ok(a))
			out.print(orig.subtract(BigInteger.ONE));
		else
			out.print("1");
		
		out.flush();
		out.close();
		
		
	}

}
