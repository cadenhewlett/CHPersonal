import java.util.Date;


public class Block {

		public String hash;
		public String hash_last;
		private String data; //for this example, the data will be a simple message
		private long timeStamp; //as number of milliseconds since 1/1/1970
		private int nonce; 
		//constructor
		public Block(String data, String hash_last) {
			this.data = data;
			this.hash_last = hash_last;
			this.timeStamp = new Date().getTime();
			this.hash = calculateHash(); //set after other variables
		}
		
		//method for calculating hash
		public String calculateHash() {
		
			String calculatedhash = StringUtil.applySha256(
					hash_last +
					Long.toString(timeStamp) +
					data
					);

			return calculatedhash;
		}
		public void mineBlock(int difficulty) {
			String target = new String(new char[difficulty]).replace('\0', '0'); //Create a string with difficulty * "0" 
			while(!hash.substring(0, difficulty).equals(target)) {
				nonce ++;
				hash = calculateHash();
				//System.out.println("Time Elapsed : "+ nonce);
			}
			System.out.println("Block Mined!!! : " + hash);
		}
		
}
