struct Info34B4C
{
  u8 pad00[3];
  u8 unk03;
  u8 unk04;
  u8 unk05;
  u8 pad06[2];
};
struct State34B4C
{
  u8 pad00[0x140];
  struct Info34B4C info0;
  struct Info34B4C info1;
};
void sub_08034B4C(struct State34B4C *state, u8 *arg1, u8 *arg2, u8 *arg3, u8 side)
{
  struct Info34B4C *info;
  u8 new_var;
  if (side == 0)
  {
    info = &state->info0;
  }
  else
  {
    info = &state->info1;
  }
  if (info->unk03 == 1)
  {
    *arg1 = 0;
  }
  else
  {
    *arg1 = 1;
  }
  if (info->unk04 == 3)
  {
    *arg2 = 0;
  }
  else
    if (info->unk04 == 4)
  {
    if ((*arg1) != 0)
    {
      *arg2 = 0;
    }
    else
    {
      *arg2 = 2;
    }
  }
  else
    if (info->unk04 == 5)
  {
    *arg2 = 2;
  }
  switch (info->unk04)
  {
    case 3:
      if (info->unk05 == 6)
    {
      *arg3 = 0;
    }
    else
    {
      *arg3 = 4;
    }
      break;

    case 4:
      new_var = info->unk05;
      if (new_var == 7)
    {
      *arg3 = 0;
    }
    else
    {
      *arg3 = 4;
    }
      break;

    case 5:
      if (new_var == 8)
    {
      *arg3 = 0;
    }
    else
    {
      *arg3 = 4;
    }
      break;

  }

}

