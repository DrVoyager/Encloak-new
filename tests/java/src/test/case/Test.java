package test;

public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int[] num = {1, 2, 3};
		int n = 2;
		int res = foo(num, n);
		System.out.println(res);
	}
	
	public static int foo(int[] num, int n) {
		return num[n];
	}

}
