package fish;
 
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
 
public class Fish
{
	private int index;
	private String name;
	private int num;
	private int price;
	private int cost;
	private int exp;
	
	private static int total;
 
	public Fish(int a, String b, int c, int d, int e)
	{
		index = a;
		name = b;
		num = c;
		price = d;
		cost = num * price;
		exp = e;
	}
 
	public void print()
	{
		System.out.print(index + "\t" +  name + "\t");
		System.out.print(num + "\t" + price + "\t");
		System.out.println(cost + "\t" + exp);
	}
 
	public static void sort(Fish[] input, int size)
	{
		for (int i = size - 1; i >= 0; i--)
			for (int j = 0; j < i; j++)
				if (input[j].exp < input[j + 1].exp)
				{
					Fish temp = input[j];
					input[j] = input[j + 1];
					input[j + 1] = temp;
				}
	}
 
	public static void readFromFile(String fileName)
	{
		try
	 	{
			System.out.println("-----------Read From File " + fileName);
			
	 		FileReader fin = new FileReader(fileName);
			String source = "";
			
			while (fin.ready())
				source += (char)fin.read();
			fin.close();
 
			String[] data = source.split("\t\t|\t|\n");

			for(String T : data)
				System.out.println(T);
			
			total = data.length / 5;
 
			Fish[] myFish = new Fish[total];
			
			for (int i = 1; i <= total; i++)
				myFish[i] = new Fish(Integer.valueOf(data[0*i]),data[1*i],
						Integer.valueOf(data[2*i]),Integer.valueOf(data[3*i]),Integer.valueOf(data[4*i]));
			
			Fish.sort(myFish, total);
			
			for (int i = 0; i < total; i++)
				myFish[i].print();
	 	}
		catch (FileNotFoundException e) {
			System.err.println("File Not Found.");
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args)
	{
		for(String fileName : args)
			readFromFile(fileName);
	}
}