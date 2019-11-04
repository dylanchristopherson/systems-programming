import java.io.File;
import java.io.*;
import java.util.*;

import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;


class Extended extends Thread {
	ArrayList<Customer> myList;
	int start, end;
	int total = 0;
	
	Extended(ArrayList<Customer> _myList_, int _start_, int _end_) {
		myList = _myList_;
		start = _start_;
		end = _end_;
	}
	
	public int getValue() {
		System.out.println("IN get value");
		return total;
	}
	
	public void run() {
	
	    int count = 0;

	    System.out.println("In run");
	    
        for (int i = start; i < end; i++) {
        	System.out.println("Within loop");
        	
        	System.out.println(myList.get(1).getBalance());
            if (myList.get(i).getBalance() < 1000) {
                ++count;
            }
        }
        System.out.println("Count: " + count);
        
        total = total + count;
	}
}

public class BankDriver {

	public static void main(String[] args) throws FileNotFoundException {
		/*// feel free to create a different file with smaller/larger number of records
		 * // create a file with random records createAccountsFile(4000000);
		 * System.out.println("File Was Created!");
		 */
		ArrayList<Customer> custList = new ArrayList<Customer>();
		// reading the info from the file and storing in the arrayList
		Scanner inFile = new Scanner(new File("accounts.txt")); 
		while (inFile.hasNext()) { // while 2
			String currID = inFile.nextLine();
			double currBalance = inFile.nextDouble();
			if (inFile.hasNextLine())
				inFile.nextLine(); // dummy reading
			custList.add(new Customer(currID, currBalance));
		} // end of while 2

		// Counting the balances that are less than 1000$
		int lowBalances = 0;
		// --Sequential-Run--------------------------------------------------------------
		long startTime = System.currentTimeMillis();
		// lowBalances = sequentialCounting(custList); // sequential run
		long estimatedTime = System.currentTimeMillis() - startTime;
		System.out.println("Number of accounts with lss than 1000$ is: " + lowBalances);
		System.out.println("Sequential run took in miliseconds: " + estimatedTime);
		// --End of Sequential-Run--------------------------------------------------------
		// *******************************************************************************
		// --Parallel Run-----------------------------------------------------------------

		
		
		System.out.println("Start parallel run");
		long parallelStartTime = System.currentTimeMillis();
		
		// 4000000 records were created
		
		// 0
		// 1000000
		// 2000000
		// 3000000
		// 4000000
		
	   	Extended e1 = new Extended(custList, 0, 1000000);
    	Extended e2 = new Extended(custList, 1000000, 2000000);
    	Extended e3 = new Extended(custList, 2000000, 3000000);
    	Extended e4 = new Extended(custList, 3000000, 4000000);
    	
    	// Extended total = new Extended("DB.txt", 0, 1000000);
    	
    	Thread t1 = new Thread(e1);
    	Thread t2 = new Thread(e2);
    	Thread t3 = new Thread(e3);
    	Thread t4 = new Thread(e4);
		
    	int finalTotal = e1.getValue() + e2.getValue() + e3.getValue() + e4.getValue();
    	
		long parallelEstimatedTime = System.currentTimeMillis() - parallelStartTime;
		System.out.println("Number of accounts with lss than 1000$ is: " + finalTotal);
		System.out.println("Sequential run took in miliseconds: " + parallelEstimatedTime);
		
		// --End-of-Parallel-Run----------------------------------------------------------

	}// end of main
	
	static int sequentialCounting(ArrayList<Customer> myList) {
		int count = 0;
		for (int i = 0; i < myList.size(); ++i)
			if (myList.get(i).getBalance() < 1000)
				++count;
		return count;
	};

	static void createAccountsFile(int count) throws FileNotFoundException {
		File accountsFile = new File("accounts.txt");
		PrintStream outFile = new PrintStream(accountsFile);
		Random rand = new Random();
		// needed for making sure that there is no duplication in the IDs
		// ArrayList<String> tmpIDs = new ArrayList<String>();

		// generating random records IDs from XXXX0 to XXXX300000000 (non-repeating) and
		// balances 0 to 1000000
		for (int i = 0; i < count; ++i) { 
			int tempId;
			tempId = rand.nextInt(300000001);
			// try to generate a random ID with 3 random letters and a number from 0 to
			// 300000000
			String currentID = "" + ((char) ('A' + rand.nextInt(25))) + ((char) ('A' + rand.nextInt(25)))
					+ ((char) ('A' + rand.nextInt(25))) + tempId + ((char) ('A' + rand.nextInt(25)))
					+ ((char) ('A' + rand.nextInt(25))) + ((char) ('A' + rand.nextInt(25)));
			// if (tmpIDs.contains(currentID) == false) {
			// tmpIDs.add(currentID); // insert to the array list in location i
			outFile.println(currentID); // send to file
			// }
			outFile.println(rand.nextInt(1000001) / 100.0); // send to file
		}
		outFile.close();
	}

}


