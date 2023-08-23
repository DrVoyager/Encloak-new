package test;

public class test{
	static final int[] K = {2, 3};
	
	public static void t(){
		if (K[0] > 1) {
			System.out.println("***pass***");
		}
	}
	
	public static void main(String[] args){
		t();
		System.out.println("****finish****");
	}
	
}