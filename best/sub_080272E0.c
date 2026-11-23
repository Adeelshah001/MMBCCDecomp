typedef struct 
{
  u8 pad0;
  u8 mode;
  u8 f2;
  u8 f3;
  u8 f4;
} S;
extern void sub_08004E44(int a);
extern void sub_0800520C(int a);
extern void sub_08004DFC(int a);
extern void sub_080275B4(void);
extern void sub_08021C2C(void);
extern void sub_08004F18(void);
extern void sub_08004F80(void);
extern void sub_080267B4(u32 *p, int kind);
typedef void (*Fn)(S *s);
void sub_080272E0(S *s)
{
  u8 m = s->mode;
  switch (m)
  {
    case 0:
      s->mode = 1;
      s->f3 = m;
      s->f2 = m;
      sub_08004E44(1);
      sub_0800520C(1);
      sub_08004DFC(2);
      sub_080275B4();
    {
      register u16 *pp = (u16 *) 0x020031E0;
      register unsigned int mask = 0xEDFF;
      *pp &= mask;
    }
      sub_08021C2C();
      s->f4 = 255;
      break;

    case 1:
    {
      sub_08004F18();
      {
        register Fn *tbl = (Fn *) 0x0822D968;
        {
          register u8 idx = s->f2;
          register u32 off = idx << 2;
          Fn fn = *((Fn *) (off + ((u32) tbl)));
          fn(s);
        }
      }
      *((u16 *) 0x020031F4) -= 4;
      sub_08004F80();
      break;
    }

    case 2:
      sub_080267B4((u32 *) 0x020070F0, 4);
      break;

  }

}

