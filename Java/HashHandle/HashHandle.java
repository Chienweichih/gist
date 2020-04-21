import java.io.File;
import java.io.InputStream;
import java.io.FileInputStream;
import java.io.BufferedInputStream;
import java.nio.file.Paths;
import java.security.DigestInputStream;
import java.security.MessageDigest;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class HashHandle
{
	public static void main(String[] args) throws Exception
	{
		long StartTime = System.currentTimeMillis();
		
		String	home_dir = "TEST";		
		File	homeFolder = new File(new File(home_dir).getAbsolutePath());
		File	hashFolder = new File(homeFolder.getAbsolutePath() + "_HASH");
		File	rootHashFile = new File(home_dir + "_ROOTHASH");

		
		/**initial**************************************************************************/
		if(hashFolder.exists())
			hashFolder.delete();
		
		if(rootHashFile.exists())
			rootHashFile.delete();

		hashFolder.mkdir();
		byte[] rootHash = generateHashDir(homeFolder, hashFolder);
		java.nio.file.Files.write(rootHashFile.toPath(), rootHash);
				
		printHash(hashFolder, rootHashFile);
		/***********************************************************************************/

		/**update a file's hash*************************************************************/
		
		if(!hashFolder.exists())
			throw new Exception();
		
		File newFile = new File(hashFolder.getName() + "/src/summer/ChainHashing/Base64codc.java_HASH");
				
		if(updateHash(newFile, rootHashFile))
			System.out.println("T");
		else
			System.out.println("F");
		
		printHash(hashFolder, rootHashFile);
		/***********************************************************************************/
		
		deleteHash(newFile, rootHashFile);
		printHash(hashFolder, rootHashFile);
		
		long ProcessTime = System.currentTimeMillis() - StartTime;
		System.out.println(ProcessTime);
	}
	
	public static byte[] generateHashDir(final File folder, final File hashFolder) throws Exception
	{
		if(!folder.exists() || !hashFolder.exists())
			throw new Exception();
		
		//sorting to ensure everything is in corrected order
		List<File> files = Arrays.asList(folder.listFiles());
		Collections.sort(files, new Comparator<File>() {  
	        @Override  
	        public int compare(File o1, File o2) {  
	            return o1.getName().compareTo(o2.getName());  
	        }  
	    });
		
		MessageDigest hash = MessageDigest.getInstance("SHA-1", "BC");
		
	    for (final File fileEntry : files) {
	    	byte[] hashValue = null;
	        if (fileEntry.isDirectory()) {
	        	//new folder
	        	File newFolder = new File(hashFolder.getAbsolutePath() + "/" + fileEntry.getName());
	        	newFolder.mkdir();
	        	hashValue = generateHashDir(fileEntry, newFolder);
	        } else {
	    		InputStream			is = new BufferedInputStream(new FileInputStream(fileEntry));
	            DigestInputStream	dIn = new DigestInputStream(is, MessageDigest.getInstance("SHA-1", "BC"));
	            final byte[]		buf = new byte[1000];
	            
	            while (dIn.read(buf) != -1);
	            hashValue = dIn.getMessageDigest().digest();	//notice: getMessageDigest() can only call once
	            dIn.close();
	        }
	        
	        //concatenation
	        hash.update(hashValue);
	        
	        //write to file
	        java.nio.file.Path	hashPath = Paths.get(hashFolder.getAbsolutePath() + "/" + fileEntry.getName() + "_HASH");
	        java.nio.file.Files.write(hashPath, hashValue);
	    }

        return hash.digest();
	}
	
	//caller update hash file first
	public static boolean updateHash(final File dir,final File rootHash) throws Exception
	{		
		if(!dir.exists() || !rootHash.exists())
			return false;
		
		File iterDir = dir.getParentFile();
		File iter = new File(iterDir.getAbsolutePath() + "_HASH");
		
		while(iterDir.exists())
		{
			if(!iter.exists())
				iter = rootHash;
						
			//sorting to ensure everything is in corrected order
			List<File> files = Arrays.asList(iterDir.listFiles());
			Collections.sort(files, new Comparator<File>() {  
		        @Override  
		        public int compare(File o1, File o2) {  
		        	
		        	String o1Name = o1.getName();
		        	String o2Name = o2.getName();
		        	
		        	int o1Last = o1Name.lastIndexOf("_");
		        	int o2Last = o2Name.lastIndexOf("_");
		        	
		        	if(o1Last != -1)
		        		o1Name = o1Name.substring(0, o1Last);
		        	if(o2Last != -1)
		        		o2Name = o2Name.substring(0, o2Last);		        	

		            return o1Name.compareTo(o2Name);
		        }
		    });
			
			MessageDigest hash = MessageDigest.getInstance("SHA-1", "BC");
			
			for (final File fileEntry : files)
			{
				if(fileEntry.isDirectory())
					continue;
				
				hash.update(java.nio.file.Files.readAllBytes(fileEntry.toPath()));
			}
			
			java.nio.file.Files.write(iter.toPath(), hash.digest());
			
			if(iter.equals(rootHash))
				return true;
		  
			iterDir = iter.getParentFile();
			iter = new File(iterDir.getAbsolutePath() + "_HASH");
		}

		return false;
	}
	
	public static boolean deleteHash(final File dir,final File rootHash) throws Exception
	{
		if(!dir.exists())
			return false;
		
		File iterDir = dir.getParentFile();
		
		dir.delete();
		
		File iter = iterDir.listFiles()[0];
		
		return updateHash(iter,rootHash);
	}
		
	public static void printHash(final File folder, final File roothash) throws Exception
	{
		if(!folder.exists() || !roothash.exists())
			System.err.println("ERROR");
		
		List<File> files = Arrays.asList(folder.listFiles());

	    for (final File fileEntry : files) {    	
	    	
	        if (fileEntry.isDirectory())
	        	continue;
	        
	        System.out.println(fileEntry.getName() + " : " + Utils.toHex(java.nio.file.Files.readAllBytes(fileEntry.toPath())));
	    }
	    
	    System.out.println("roothash : " + Utils.toHex(java.nio.file.Files.readAllBytes(roothash.toPath())));
	}
}