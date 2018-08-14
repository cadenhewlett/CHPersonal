import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;

import java.util.Hashtable;

import java.util.Map;

public class dictionary {
	public static void main(String[] args) throws IOException {
		
		
		Map<String, Integer> dictionary = new HashMap(); //new map with string and integer keys/values
		Map<Integer, String> dictionaryKeys = new HashMap(); //new map with inverted keys/values
		
		//define variables
		int j, temp; 
		//arbitrary values
		int A = 47; 
		int B = 252; 
		int C = 13;
		int D = 57;
		//arbitrary keys
		String A_KEY = "Dogs";
		String B_KEY = "Cats";
		String C_KEY = "Enchiladas";
		String D_KEY = "Pigs";
		
		//add values and keys to both dictionaries
		dictionaryKeys.put(A, A_KEY);
		dictionaryKeys.put(B, B_KEY);
		dictionaryKeys.put(C, C_KEY);
		dictionaryKeys.put(D, D_KEY);
		
		dictionary.put(A_KEY, A);
		dictionary.put(B_KEY, B);
		dictionary.put(C_KEY, C);
		dictionary.put(D_KEY, D);
		
		//new String Array filled with the values of the keys
		String[] b = { dictionaryKeys.get(A), dictionaryKeys.get(B), dictionaryKeys.get(C), dictionaryKeys.get(D) };
		
		//new Integer Array filled with keys of the values
		int[] a = { dictionary.get(b[0]), dictionary.get(b[1]), dictionary.get(b[2]), dictionary.get(b[3]) };

		// System.out.println(String.format("Value = %s", dictionary.get("FIRST"))); //gets the first value

		// System.out.println(Arrays.toString(a)); // prints the array

		// System.out.println(Arrays.toString(b)); // prints the array
		
		//insertion sorting algorithm
		for (int i = 1; i < a.length; i++) // repeats while iteration is less than the length of the array
		{
			j = i - 1; // j is one less than the iteration
			while (j >= 0 && a[j] < a[i])// while j is greater than 0, and the jth term of the array is greater than the
											// ith term of the array
			{
				temp = a[i]; 
				a[i] = a[j]; 
				a[j] = temp;

				// System.out.println(String.format("%s", temp));
				b[i] = b[j];
				b[j] = dictionaryKeys.get(temp);

				i = j;
				j--;

			}
		}
		for (int x = 0; x < a.length; x++) {
			System.out.println(String.format("%s, %s", b[x], a[x]));

		}
	}

}
