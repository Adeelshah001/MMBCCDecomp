void sub_080267B4(u8 *p, u8 kind);
extern u8 gUnknown_02002F50[];
extern u8 gUnknown_020070F0[];
void sub_08028244(u8 *s)
{
  u8 v = s[1];
  int new_var2;
  u16 *new_var;
  if (v == 0)
  {
    goto zero;
  }
  if (v == 1)
  {
    goto one;
  }
  return;
  zero:
  s[6] = 0;

  s[1]++;
  one:
  s[6]++;

  if (s[6] > 180)
  {
    goto call;
  }
  {
    struct 
    {
      u8 pad[4];
      u16 flg;
    } *st = (void *) gUnknown_02002F50;
    new_var = &st->flg;
    new_var2 = 1;
    if (((*new_var) & new_var2) == 0)
    {
      goto end;
    }
  }
  call:
  sub_080267B4(gUnknown_020070F0, 9);

  end:
  ;

  ;
}

