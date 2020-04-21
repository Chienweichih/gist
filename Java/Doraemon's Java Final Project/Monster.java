public class Monster
{
	private String type;
	private int life,speed,attack,provideExp;
	
	public Monster()
	{
	     type = "紳士史萊姆";
	     life = (int)(Math.random()*21+150);
	     speed = (int)(Math.random()*16+35);
	     attack = (int)(Math.random()*11+20);
	     provideExp = (int)(Math.random()*1000+1000);
	}
	
	public String getType()
	{
		return type;
	}
	
	public int getSpeed()
	{
		return speed;
	}
	
	public int getLife()
	{
		return life;
	}
	
	public int getAttack()
	{
		System.out.print(type + "攻擊，");
		return attack;
	}
	
	public void injure(int attack)
	{
		life -= attack;
		System.out.println("造成" + type + "失血 " + attack + " 點。\n");
	}
	
	public int died()
	{
		System.out.print("\n" + type + "終於掛了\n");
		return provideExp;
	}
	
	public void printData()
	{
		String data = type + "\n";
		data += "體力 " + life + " ,";
		data += "速度 " + speed + " ,";
		data += "攻擊力 " + attack + " ,";
		data += "經驗值 " + provideExp;
	    System.out.println(data);
	}
}