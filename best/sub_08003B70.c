#define MATRIX(sprite) (&D_03002830[((u32)(sprite)->attributes << 26) >> 27])
#define ANGLE(sprite, angle, mask)     ((angleMix = (sprite)->flipY, angleMix ^= (sprite)->flipX),      ((((angleMix * 255) ^ (angle)) + angleMix) & (mask)))
typedef short s16;
typedef struct 
{
  u8 pad0[19];
  u8 attributes;
  u8 pad14[4];
  u8 flipX;
  u8 flipY;
  u8 pad1A;
  u8 angle;
  u16 scaleX;
  u16 scaleY;
} AffineSprite;
typedef struct 
{
  u16 pad0[3];
  s16 pa;
  u16 pad8[3];
  s16 pb;
  u16 pad10[3];
  s16 pc;
  u16 pad18[3];
  s16 pd;
} OamMatrix;
extern OamMatrix D_03002830[];
extern const s16 D_0804E05C[];
extern int sub_0804DD08(int numerator, int denominator);
inline int inline_fn(int arg0, int arg1, int arg2)
{
  return ((arg0 - 1) | arg1) + arg2;
}

void sub_08003B70(AffineSprite *sprite, u8 angle)
{
  OamMatrix *matrix = MATRIX(sprite);
  OamMatrix *slot2;
  OamMatrix *slot3;
  OamMatrix *slot4;
  const s16 *sine = D_0804E05C;
  int angleMix;
  int scaleX;
  int scaleY;
  int firstX;
  int firstY;
  int *new_var;
  int secondX;
  int secondY;
  int sign;
  u8 flip;
  int mask;
  unsigned angleIndex;
  angleMix = sprite->flipY;
  angleMix ^= sprite->flipX;
  angleIndex = ((angleMix * 255) ^ angle) + angleMix;
  mask = 255;
  angleIndex &= mask;
  angleIndex += 64;
  matrix->pa = sine[angleIndex];
  slot2 = MATRIX(sprite);
  flip = mask;
  scaleY = flip;
  slot2->pd = sine[ANGLE(sprite, angle, scaleY) + 64];
  slot3 = MATRIX(sprite);
  slot3->pb = sine[ANGLE(sprite, angle, flip)];
  slot4 = MATRIX(sprite);
  slot4->pc = -sine[ANGLE(sprite, angle, flip)];
  scaleX = sprite->scaleX;
  if (inline_fn(scaleX, scaleX, 1) == (scaleX * 2))
  {
    scaleX++;
  }
  firstX = sub_0804DD08(matrix->pa << 8, scaleX);
  matrix->pa = firstX;
  secondX = sub_0804DD08(matrix->pb << 8, scaleX);
  matrix->pb = secondX;
  flip = sprite->flipX;
  mask = ((int) (((u32) flip) << 31)) >> 31;
  sign = mask;
  firstX ^= sign;
  firstX += flip;
  matrix->pa = firstX;
  secondX ^= sign;
  new_var = &secondX;
  secondX += flip;
  matrix->pb = *new_var;
  scaleY = sprite->scaleY;
  if (inline_fn(scaleY, scaleY, 1) == (scaleY * 2))
  {
    if (1)
    {
      scaleY++;
    }
  }
  firstY = sub_0804DD08(matrix->pc << 8, scaleY);
  matrix->pc = firstY;
  secondY = sub_0804DD08(matrix->pd << 8, scaleY);
  matrix->pd = secondY;
  flip = sprite->flipY;
  sign = ((int) (((u32) flip) << 31)) >> 31;
  firstY ^= sign;
  firstY += flip;
  matrix->pc = firstY;
  secondY ^= sign;
  secondY += flip;
  matrix->pd = secondY;
  sprite->angle = angle;
}

