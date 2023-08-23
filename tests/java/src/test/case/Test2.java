package test;

public class Test2{
	int[] K = {2, 3};
	
//	public static void t(){
//		if (K[0] > 1) {
//			System.out.println("***pass***");
//		}
//	}
	
	public static void main(String[] args){
//		t();
		Test2 test = new Test2();
		if (test.K[0] > 1){
			System.out.println("****YES****");
		}
		System.out.println("****finish****");
	}
	
}