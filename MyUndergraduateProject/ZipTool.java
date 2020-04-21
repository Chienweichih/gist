import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

public class ZipTool
{	
	public static void main(String[] args)
	{
		ZipTool z = new ZipTool();
		String in = null;
		try
		{
			FileInputStream fis = new FileInputStream(new File("testZip.txt"));
			BufferedReader br = new BufferedReader(new InputStreamReader(fis));
					
			StringBuilder sb = new StringBuilder();
			while((in = br.readLine()) != null)	
				sb.append( in.concat("\n") );
			
			in = sb.toString();
			in = in.substring(0, in.length() - 1);
			
			byte[] out = z.compress(in);
			FileOutputStream bos = new FileOutputStream("ZipTest.txt");
			bos.write(out);

			String test = z.decompress(out);
			System.out.println((test.equals(in))?"SAME":"NOT SAME");
			
			System.out.println("壓縮前大小 : " + in.getBytes().length);
			System.out.println("壓縮後大小 : " + out.length);
			
			br.close();
			bos.close();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public byte[] compress(String input)
	{
		if(input == null || input.length() == 0)
			return null;
		
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		try
		{
			GZIPOutputStream gzip = new GZIPOutputStream(out);
			gzip.write(input.getBytes());
			
			gzip.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		
		return out.toByteArray();
	}
	
	public String decompress(byte[] input)
	{
		if(input == null || input.length == 0)
			return null;
		
		String out = null;
		try
		{
			GZIPInputStream gzip = new GZIPInputStream(new ByteArrayInputStream(input));
			BufferedReader in = new BufferedReader(new InputStreamReader(gzip));
	
			StringBuilder sb = new StringBuilder();
			while ((out = in.readLine()) != null)
				sb.append( out.concat("\n") );
			
			out = sb.toString();
			out = out.substring(0, out.length() - 1);
			
			in.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
		
		return out;
	}
}