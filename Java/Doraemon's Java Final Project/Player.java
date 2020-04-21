import java.util.Scanner;

public class Player
{
	private String name;
	private int experience,life,mana,speed,attack;

	public Player()
	{
		name = new Scanner(System.in).next();
		experience = 0;
	    life = (int)(Math.random()*251+350);
	    mana = (int)(Math.random()*21+100);
	    speed = (int)(Math.random()*16+35);
	    attack = (int)(Math.random()*21+40);
	}
	
	public int getLife()
	{
		return life;
	}
	
	public int getSpeed()
	{
		return speed;
	}
	
	public int getAttack()
	{
		System.out.print(name + "攻擊，");
		return attack;
	}
	
	public void injure(int attack)
	{
		life -= attack;
		System.out.println("造成" + name + "失血 " + attack + " 點。\n");
	}
	
	public void heal()
	{
		if(mana>=20)
        {
            mana-=20;
            life+=100;
            System.out.println("你扣了20點mana換取100生命值\n");
            System.out.println("現在血量"+life+"\n");
        }
        else System.out.println("mana值不夠!!!\n");
	}
	
	public void died()
	{
		System.out.println("\n" + name + "你掛了");
	}
	
	public void killedMonster(Monster m)
	{
		int experience = m.died();
		System.out.println(name + "獲得經驗值" + experience + "\n\n");
	}
	
	public void printData()
	{
		String data = name + "\n";
		data += "體力 " + life + " ,";
		data += "速度 " + speed + " ,";
		data += "攻擊力 " + attack + " ,";
		data += "經驗值 " + experience;
	    System.out.println(data);
	}
}