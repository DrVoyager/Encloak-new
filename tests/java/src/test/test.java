package test;

public class test{
	static final int[] K = {2, 3};
	
	public static int t(int x){
		int a = 1;
		if (K[0] > 1) {
			int c = a + x;
			System.out.println("***pass***");
			return c;
		}
		return -1;
	}
	
	public static void main(String[] args){
		int b = 3;
		int c = t(b);
		System.out.println("c=" + c);
	}
	
}