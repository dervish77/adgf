public class test {
    public static void main(String args[]) {

	System.out.println("Begin test");

	final int SIZE = 3; // size of arrays
	int [] A = new int[SIZE];
	int [] B = new int[SIZE];
	int i;

	// set array A[i] = i + 1
	for (i = 0; i < A.length; i++) {
	    A[i] = i + 1;
	}
	// Set the values of B to be the same as A.
	// actually causes an alias problem
	B = A;
	// make B[i] = 2 * (i + 1) - 2 times current value
	for (i = 0; i < B.length; i++) {
	    B[i] = 2 * B[i];
	}
	// print results
	for (i = 0; i < A.length - 1; i++) {
	    System.out.print("A[" + i + "] = " + A[i] + ", ");
	}
	System.out.println("A[" + i + "] = " + A[i]);
	for (i = 0; i < B.length - 1; i++) {
	    System.out.print("B[" + i + "] = " + B[i] + ", ");
	}
	System.out.println("B[" + i + "] = " + B[i]);

	System.out.println("Ending test");
    }
}
