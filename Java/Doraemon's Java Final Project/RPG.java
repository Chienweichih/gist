import java.util.Scanner;

public class RPG {
	
	private Player player;
	private Monster[] monsters;
	private static final int monsterTotal = 3;
	private static Scanner scanner = new Scanner(System.in);
	
	public RPG()
	{
		System.out.print("請輸入角色名稱： ");
		player = new Player();
		
		monsters = new Monster[monsterTotal];
		for(int i = 0; i < monsterTotal; i++)
			monsters[i] = new Monster();
		
		System.out.println("遊戲規則：\n(A)ttack\n(H)eal\n(F)lee\n");
		
		for(int i = 0;i < monsterTotal;i++)
		{
			player.printData();
			System.out.println("\n碰到一隻"+monsters[i].getType());
			monsters[i].printData();

			while(player.getLife() > 0 && monsters[i].getLife() > 0)
			{
				System.out.println("你要幹嘛呢?");
				switch(scanner.next().charAt(0))
			    {
			       case 'A':case 'a':
			    	   battle(player,monsters[i]);
			    	   break;
			       case 'H':case 'h':
			    	   player.heal();
			    	   break;
			       case 'F':case 'f':
			       {
			    	   int a = (int)(Math.random()*101);
			    	   int v = ((player.getSpeed())-(monsters[i].getSpeed()))/10;
			    	   
			    	   
			    	   if(v == -6 || v == -5)
			    	   {
			    		   System.out.println("逃跑機率0%,準備跟"+monsters[i].getType()+"戰鬥吧\n");
			    		   battle(player,monsters[i]);
			    	   }
			    	   else if(v == 5 || v == 60)
			    		   System.out.println("逃跑成功!!\n");			    	   
			    	   else if(a < 51 + v*10)
			    		   System.out.println("逃跑成功!!\n");
			    	   else
			    	   {
			    		   System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");
			    		   battle(player,monsters[i]);
			    	   }   
			    	   
			    	   /*
			           switch(((player.speed)-(monsters[i].speed))/10)
			           {
			              case -6:case -5:{System.out.println("逃跑機率0%,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}break;
			              case -4:{if(a<11)System.out.println("逃跑成功!!\n");else {System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}}break;
			              case -3:{if(a<21)System.out.println("逃跑成功!!\n");else {System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}}break; 
			              case -2:{if(a<31)System.out.println("逃跑成功!!\n");else {System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}}break; 
			              case -1:{if(a<41)System.out.println("逃跑成功!!\n");else {System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}}break; 
			              case 0:{if(a<51)System.out.println("逃跑成功!!\n");else {System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}}break; 
			              case 1:{if(a<61)System.out.println("逃跑成功!!\n");else {System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}}break; 
			              case 2:{if(a<71)System.out.println("逃跑成功!!\n");else {System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}}break; 
			              case 3:{if(a<81)System.out.println("逃跑成功!!\n");else {System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}}break; 
			              case 4:{if(a<91)System.out.println("逃跑成功!!\n");else {System.out.println("逃不掉了,準備跟"+monsters[i].getType()+"戰鬥吧\n");battle(player,monsters[i]);}}break; 
			              case 5:case 60:System.out.println("逃跑成功!!\n");break;
			              default:System.out.println("遊戲錯誤ORZ...請不要逃跑好嗎= =\n");
			           }*/
			       }
						break;
			       default:
			    	   System.out.println("別亂輸入!!\n");
			      }
			}
			
			if(isDied(player,monsters[i]))
				break;
		}		
	}
	
	private void battle(Player p,Monster m)
	{
		int e = (p.getSpeed() * Math.random() > m.getSpeed() * Math.random()) ? 0 : 1;
		
	    if(e % 2 == 0)
	    {
	    	int attack = p.getAttack();
	    	m.injure(attack);
		}
		else
		{
			int attack = m.getAttack();
	    	p.injure(attack);
		}
	}
	
	private boolean isDied(Player p,Monster m)
	{
		if(p.getLife() <= 0)
		{
			p.died();
			return true;
		}
		
		p.killedMonster(m);
		return false;
	}
}