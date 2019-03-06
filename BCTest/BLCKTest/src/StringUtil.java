

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class StringUtil {
	// sha256 is a security hash algorithm algorithm - it encrypts stuff
	// applies Sha256 to a string and returns the result

	public static String applySha256(String inputString) {
		MessageDigest digest;
		try {
			digest = MessageDigest.getInstance("SHA-256");
			byte[] hash = digest.digest(inputString.getBytes("UTF-8"));
			StringBuffer hexString = new StringBuffer(); // this lets us contain the hash as a hexadecimal
			for (int i = 0; i < hash.length; i++) { // repeats for hash length iterations
				String hex = Integer.toHexString(0xff & hash[i]);
				if (hex.length() == 1) {
					hexString.append('0');
				}
				hexString.append(hex);
			}
			return hexString.toString();
		} catch (NoSuchAlgorithmException e) {
			return e.getMessage();

		} // gets SHA-256 as our instance
		catch (UnsupportedEncodingException e) {
			return e.getMessage();
		}

	}
}
