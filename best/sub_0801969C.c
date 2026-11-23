typedef short s16;
typedef int s32;
typedef struct 
{
  u8 pad0[10];
  u8 flags;
  u8 padB[2];
  u8 phase;
  u8 padE[21];
  u8 variant;
  u8 pad24[8];
  void *owner;
  u8 pad30[40];
  s32 x;
  s32 y;
  s32 dx;
  s32 dy;
} Object1969C;
extern void sub_0800DD4C(Object1969C *, s32, s32);
extern void sub_0800DD08(s32 *, Object1969C *);
extern void sub_080178A8(int, int, s16, s16, void *);
extern u8 sub_08017494(void *, int);
extern u8 sub_08017474(void *);
inline u8 *inline_fn(Object1969C *arg0)
{
  return &arg0->flags;
}

u8 sub_0801969C(Object1969C *obj)
{
  s32 xy[2];
  u8 flags;
  u8 variant;
  int mask;
  register s32 y;
  register s32 x;
  s32 new_var;
  Object1969C *new_var2;
  sub_0800DD4C(obj, obj->x, obj->y);
  obj->x += obj->dx;
  obj->y += obj->dy;
  sub_0800DD08(xy, obj);
  x = xy[0];
  y = xy[1];
  switch (obj->phase)
  {
    new_var = x;
    case 0:
      if (new_var > 12800)
    {
      variant = obj->variant;
      sub_080178A8(82, (((u32) variant) << 28) >> 28, 15360, (s16) y, obj->owner);
      if (sub_08017494(obj->owner, 0))
      {
        obj->phase = 1;
      }
      else
      {
        mask = 253;
        flags = mask & (*((volatile u8 *) inline_fn(obj)));
        flags &= 254;
        obj->flags = flags;
        goto advance;
      }
    }
      break;

    new_var2 = obj;
    case 1:
      if (x > 30720)
    {
      advance:
      new_var2->phase = 2;

    }
      break;

    case 2:
      if (sub_08017474(obj->owner) > 5)
    {
      return 1;
    }
      break;

  }

  return 0;
}

