typedef signed short s16;
typedef signed int s32;
extern u8 *sub_080113F4(u16 cur);
typedef struct 
{
  u8 *f0;
  u8 b4;
  u8 b5;
  u8 b6;
  u8 b7;
  u8 pad[28];
  u8 b35;
} Obj;
s32 sub_08011A78(Obj *p)
{
  register u8 *q = p->f0;
  register u8 *r2 = ((u8 *) p) + 35;
  u8 z = 0;
  u8 new_var;
  u8 e;
  u8 t;
  if (t)
  {
    *r2 = z;
  }
  else
  {
    *r2 = z;
  }
  {
    register u8 eight = 8;
    e = eight;
    new_var = z;
    t = q[10];
    if ((e & t) != 0)
    {
      *r2 = 1;
    }
    if ((*((s16 *) (p->f0 + 30))) > 0)
    {
      u16 v = *((u16 *) (p->f0 + 30));
      u8 *w = sub_080113F4(v);
      if (w != 0)
      {
        p->f0 = w;
        p->b4++;
        goto done;
      }
    }
    p->b4 = eight;
    done:
    p->b5 = new_var;

    p->b6 = new_var;
    p->b7 = z;
    return -1;
  }
}

