import java.util.Scanner;

class Substring {
	public static void main(String[] args) {
		Scanner subScan = new Scanner(System.in);
		
		System.out.println("String one: ");
		String bigString = subScan.nextLine();

		System.out.println("String two: ");
		String subString = subScan.nextLine();

		if (bigString.contains(subString)) {
		       	System.out.println("FOUND");
	 	}
		else {
			System.out.println("NOT FOUND");
		}
	}
}
