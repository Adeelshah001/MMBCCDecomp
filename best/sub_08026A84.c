extern void sub_08004E44(void);
extern void sub_08004F18(void);
extern s8 sub_0804DEE8(u8 a, int b);
extern void sub_08006A54(u32 *p, int a, int b, int c, int d);
extern void sub_080267B4(u8 *p, int a);
extern void sub_08004F80(void);
void sub_08026A84(u8 *s)
{
  u8 t = s[1];
  if (t == 0)
  {
    goto case0;
  }
  if (t == 1)
  {
    goto aa2;
  }
  goto end;
  case0:
  s[6] = 0;

  sub_08004E44();
  s[1]++;
  aa2:
  sub_08004F18();

  if (sub_0804DEE8(s[6], 20) != 0)
  {
    u32 *p = (u32 *) 0x082350d0;
    sub_08006A54(*p, 1, 1, 8, 0);
  }
  if ((++s[6]) > 60)
  {
    goto docall;
  }
  {
    register u8 *base = (u8 *) 0x02002f50;
    register u32 mask = 1;
    ;
    if ((mask & (*((u16 *) (base + 4)))) == 0)
    {
      goto skipcall;
    }
  }
  docall:
  sub_080267B4((u8 *) 0x020070f0, 3);

  skipcall:
  sub_08004F80();

  end:
  ;

  ;
}

