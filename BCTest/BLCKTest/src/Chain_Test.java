

import com.google.gson.*;

import java.util.ArrayList;

public class Chain_Test {

		public static ArrayList<Block> blockchain = new ArrayList<Block>();
		public static int difficulty = 1;
		
		public static Boolean isChainValid() {
			Block currentBlock;
			Block previousBlock;
			String hashTarget = new String(new char[difficulty]).replace('\0', '0');
			
			//loop through the chain and compare hashes:
			for(int i = 1; i < blockchain.size(); i++) {
				currentBlock = blockchain.get(i);
				previousBlock = blockchain.get(i-1);
				//compare registered hash and calculated hash:
				if(!currentBlock.hash.equals(currentBlock.calculateHash())) {
					System.out.println("Current Hashes are not equal:");
					return false;
				}
				//compare previous hash and registered previous hash
				if(!(previousBlock.hash.equals(currentBlock.hash_last))) {
					System.out.println("Previous Hashes are not equal");
					return false;	
				}
				//check if hash is solved
				if(!(currentBlock.hash.substring(0, difficulty).equals(hashTarget))) {
					System.out.println("This block hasn't been mined");
					return false;
				}
			}
			return true;
		}
		
		public static void main(String[] args) {
			
			blockchain.add(new Block("Hi im the first block", "0"));
			System.out.println("Trying to Mine block 1... ");
			blockchain.get(0).mineBlock(difficulty);
			
			blockchain.add(new Block("Yo im the second block",blockchain.get(blockchain.size()-1).hash));
			System.out.println("Trying to Mine block 2... ");
			blockchain.get(1).mineBlock(difficulty);
			
			blockchain.add(new Block("Hey im the third block",blockchain.get(blockchain.size()-1).hash));
			System.out.println("Trying to Mine block 3... ");
			blockchain.get(2).mineBlock(difficulty);	
			
			System.out.println("\nBlockchain is Valid: " + isChainValid());
			
			String blockchainJson = new GsonBuilder().setPrettyPrinting().create().toJson(blockchain);
			System.out.println("\nThe block chain: ");
			System.out.println(blockchainJson);
			
		}
		
		
}
