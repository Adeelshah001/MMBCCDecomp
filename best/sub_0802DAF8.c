typedef signed int s32;
extern u8 sub_0803FD68(u16 a);
extern u8 sub_0803F920(u16 a);
extern u8 sub_0803FACC(u16 a);
u32 sub_0802DAF8(u16 a, u16 b)
{
  u32 r6 = 0;
  u8 r1 = sub_0803FD68(a);
  s32 sb = b;
  u8 res;
  int new_var;
  if (b == 962)
  {
    goto callacc;
  }
  if (sb > 962)
  {
    goto gt;
  }
  new_var = 960;
  if (sb < new_var)
  {
    goto end;
  }
  res = sub_0803F920(a);
  goto check70;
  gt:
  if (b == 9152)
  {
    goto check56;
  }

  if (sb > 9152)
  {
    goto gt2;
  }
  if (b == 5056)
  {
    goto check50;
  }
  goto end;
  gt2:
  if (b == 17344)
  {
    goto set7check4;
  }

  goto end;
  check50:
  if (r1 == 1)
  {
    goto set6;
  }

  goto check5a;
  check56:
  if (r1 == 2)
  {
    goto set6;
  }

  goto check5a;
  check5a:
  if (r1 == 5)
  {
    goto set6;
  }

  goto set7;
  set7:
  r6 = 7;

  goto end;
  set7check4:
  r6 = 7;

  if (r1 != 4)
  {
    goto end;
  }
  goto set6;
  callacc:
  ;

  check70:
  r6 = 7;

  if (sub_0803FACC(a) == 0)
  {
    goto end;
  }
  goto set6;
  set6:
  r6 = 6;

  goto end;
  end:
  return r6;

}

