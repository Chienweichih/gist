void something_magic(const int start) {

  const int end = start + 4;
  
  for(GR_2 = start;GR_2 < end;GR_2++) {
      
    for(GR_1 = 0;GR_1 < 4;GR_1++)//GR_2 singleton + GR_1 nonsingleton + GR_1 singleton
    {
      printf("singleton_row:%d GR_1:%d GR_2:%d\n", singleton_row, GR_1, GR_2);
      
      for(element = 0;element < 15;element++) {
	a[a_row][element+1] += GR[singleton_row][element];
	a[a_row][element+1] += GR[GR_2][element];
	a[a_row][element+1] += GR[GR_1][element];
      }
      a_row++;
    }
    
    for(element = 0;element < 15;element++)//GR_2 singleton + GR_1 singleton + GR_1 singleton
    {
      a[a_row][element+1] += GR[singleton_row][element];
      a[a_row][element+1] += GR[GR_2][element];
      a[a_row][element+1] += GR[singleton_row][element];
    }
    a_row++;
  }
  
}

for(singleton_row = 4; singleton_row < 9; ++singleton_row) {

  if(singleton_row == 4)
    something_magic(22);
  else if(singleton_row == 5)
    something_magic(18);
  else if(singleton_row == 6)
    something_magic(14);
  else if(singleton_row == 7)
    something_magic(26);
    
}