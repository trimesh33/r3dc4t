// func inside 0x10000AB0

static const uint8_t right_code[4] = { 9, 4, 5, 0 };

void password(void)
{
    uint8_t entered[4] = { 0 };
    uint position = 0;
    uint8_t digit = 0;

    // A, B, button
    configure_encoder_irq(27, 29, 28, pass_encoder);
    set_rgb(BLUE);

    for (;;) {
        if (encoder_delta != 0) {
            digit = wrap_0_to_9(digit + take_encoder_delta());
            show_digit(digit);
        }

        if (!take_button_press())
            continue;

        entered[position++] = digit;
        show_filled_positions(position);

        if (position < 4)
            continue;

        if (memcmp(entered, right_code, 4) == 0) {
            set_rgb(GREEN);
            unlocked = true;
            JMP usb_decode;
        }

        blink_rgb(RED, 3, 200ms);
        clear(entered);
        position = 0;
        digit = 0;
        set_rgb(BLUE);
    }
}

// initial ida pseudocode

int long_func()
{
  return sub_10000ABA();
}

void __fastcall sub_10000ABA(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
  _BYTE *v9; // r4
  int v10; // r5
  _BYTE *v11; // r5
  int v12; // r7
  int v13; // r0
  int v14; // r0
  __int64 v15; // r0
  __int64 v16; // r4
  unsigned int v17; // r6
  int v18; // r7
  unsigned int v19; // r7
  int v20; // r4
  int v21; // r4
  int v22; // r0
  __int64 v23; // r0
  __int64 v24; // r2
  __int64 v25; // r0
  int v26; // r3
  int v27; // r3
  bool v28; // cf
  int v29; // r3
  int v30; // [sp+4h] [bp-38h]
  int v31; // [sp+8h] [bp-34h]
  int v32; // [sp+Ch] [bp-30h]
  __int64 v33; // [sp+10h] [bp-2Ch]
  __int64 v34; // [sp+18h] [bp-24h]
  int v35; // [sp+20h] [bp-1Ch]
  int v36; // [sp+24h] [bp-18h]
  char v37; // [sp+33h] [bp-9h]
  _DWORD v38[2]; // [sp+34h] [bp-8h]

  sub_100016B8(a1: 29);
  SIO_GPIO_OE_CLR = 0x20000000;
  sub_10001568(a1: 29, a2: 1, a3: 0);
  sub_100016B8(a1: 27);
  SIO_GPIO_OE_CLR = 0x8000000;
  sub_10001568(a1: 27, a2: 1, a3: 0);
  sub_100016B8(a1: 28);
  SIO_GPIO_OE_CLR = 0x10000000;
  sub_10001568(a1: 28, a2: 1, a3: 0);
  v9 = byte_10005508;
  do
  {
    v10 = (unsigned __int8)*v9++;
    sub_100016B8(a1: v10);
    SIO_GPIO_OE_SET = 1 << v10;
    SIO_GPIO_OUT_CLR = 1 << v10;
  }
  while ( &byte_10005508[10] != v9 );
  v11 = byte_10005504;
  do
  {
    v12 = (unsigned __int8)*v11++;
    v13 = sub_100016B8(a1: v12);
    SIO_GPIO_OE_SET = 1 << v12;
    SIO_GPIO_OUT_CLR = 1 << v12;
  }
  while ( v11 != byte_10005508 );
  sub_10001204(a1: v13);
  byte_20002ED1 = 0;
  byte_20002ED0 = 0;
  dword_20001EB0 = 0;
  sub_100015E8(a1: 29, a2: 12, a3: 1, a4: pass_encoder);
  sub_10001590(a1: 27, a2: 12, a3: 1);
  sub_10001590(a1: 28, a2: 4, a3: 1);
  v38[0] = 0;
  SIO_GPIO_OUT_CLR = 128;
  SIO_GPIO_OUT_CLR = 64;
  SIO_GPIO_OUT_CLR = 32;
  SIO_GPIO_OUT_CLR = 16;
  SIO_GPIO_OUT_CLR = 8;
  SIO_GPIO_OUT_CLR = 4;
  SIO_GPIO_OUT_CLR = 2;
  SIO_GPIO_OUT_CLR = 1;
  SIO_GPIO_OUT_CLR = 512;
  SIO_GPIO_OUT_CLR = 256;
  SIO_GPIO_OUT_SET = 128;
  v14 = sub_10001218(a1: 0, a2: 0, a3: 32);
  v15 = sub_100025C8(a1: v14);
  v16 = v15 + 300000;
  if ( (((unsigned __int64)(v15 + 300000) >> 32) & 0x80000000) != 0LL )
    v16 = 0x7FFFFFFFFFFFFFFFLL;
  v36 = 0;
  v34 = 0;
  v31 = 0;
  v33 = 0;
  v30 = 0;
  v32 = 0;
  v35 = 0;
  v17 = 0;
  v18 = byte_20002ED1;
  if ( byte_20002ED1 != 0 )
    goto LABEL_8;
LABEL_28:
  if ( v30 != 0 )
  {
    v15 = sub_100025C8(a1: v15);
    if ( v33 - v15 > 0 )
      goto LABEL_30;
    if ( v32 <= 0 )
    {
      if ( v32 != 0 )
      {
        v36 = -1;
        v30 = 0;
        goto LABEL_30;
      }
    }
    else
    {
      v36 = 1;
    }
  }
  v30 = 0;
LABEL_30:
  v19 = v17;
  if ( v31 == 0 )
    goto LABEL_15;
LABEL_13:
  v15 = sub_100025C8(a1: v15);
  v19 = v17;
  if ( v34 - v15 > 0 )
  {
    v31 = 1;
    goto LABEL_15;
  }
  v31 = 0;
  if ( v36 != 0 )
  {
    v27 = *((unsigned __int8 *)v38 + v17);
    if ( v36 == -1 )
      goto LABEL_85;
LABEL_80:
    v28 = v27 != 0;
    v29 = v27 - 1;
    if ( !v28 )
    {
      v36 = 1;
      v29 = 9;
      goto LABEL_82;
    }
    v36 = 1;
LABEL_86:
    while ( v29 > 9 )
      v29 -= 10;
LABEL_82:
    *((_BYTE *)v38 + v17) = v29;
    SIO_GPIO_OUT_CLR = 128;
    SIO_GPIO_OUT_CLR = 64;
    SIO_GPIO_OUT_CLR = 32;
    SIO_GPIO_OUT_CLR = 16;
    SIO_GPIO_OUT_CLR = 8;
    SIO_GPIO_OUT_CLR = 4;
    SIO_GPIO_OUT_CLR = 2;
    SIO_GPIO_OUT_CLR = 1;
    SIO_GPIO_OUT_CLR = 512;
    SIO_GPIO_OUT_CLR = 256;
    LODWORD(v15) = byte_10005508;
    SIO_GPIO_OUT_SET = 1 << byte_10005508[v29];
    v31 = 0;
  }
  while ( 1 )
  {
LABEL_15:
    if ( byte_20002ED0 == 0 )
      goto LABEL_26;
    byte_20002ED0 = 0;
    if ( v17 > 2 )
      break;
    *((_BYTE *)&dword_20001EB0 + v17) = 1;
    v17 = (unsigned __int8)(v17 + 1);
    HIDWORD(v15) = *((unsigned __int8 *)v38 + v17);
    SIO_GPIO_OUT_CLR = 128;
    SIO_GPIO_OUT_CLR = 64;
    SIO_GPIO_OUT_CLR = 32;
    SIO_GPIO_OUT_CLR = 16;
    SIO_GPIO_OUT_CLR = 8;
    SIO_GPIO_OUT_CLR = 4;
    SIO_GPIO_OUT_CLR = 2;
    SIO_GPIO_OUT_CLR = 1;
    SIO_GPIO_OUT_CLR = 512;
    LODWORD(v15) = 256;
    v19 = v17;
    SIO_GPIO_OUT_CLR = 256;
    if ( HIDWORD(v15) > 9 )
      goto LABEL_26;
    SIO_GPIO_OUT_SET = 1 << byte_10005508[HIDWORD(v15)];
    v23 = sub_100025C8(a1: byte_10005508);
    v24 = v16 - v23;
    if ( (int)((unsigned __int64)(v16 - v23) >> 32) <= 0 )
    {
LABEL_37:
      if ( HIDWORD(v24) != 0 || (_DWORD)v24 == 0 )
      {
        v16 = sub_100025C8(a1: v23) + 300000;
        if ( v16 < 0 )
          v16 = 0x7FFFFFFFFFFFFFFFLL;
        v35 ^= 1u;
        SIO_GPIO_OUT_CLR = 0x2000;
        SIO_GPIO_OUT_CLR = 4096;
        SIO_GPIO_OUT_CLR = 2048;
        SIO_GPIO_OUT_CLR = 1024;
        if ( (_BYTE)dword_20001EB0 != 0 )
          SIO_GPIO_OUT_SET = 0x2000;
        if ( BYTE1(dword_20001EB0) != 0 )
          SIO_GPIO_OUT_SET = 4096;
        if ( BYTE2(dword_20001EB0) != 0 )
          SIO_GPIO_OUT_SET = 2048;
        if ( HIBYTE(dword_20001EB0) != 0 )
          SIO_GPIO_OUT_SET = 1024;
        if ( *((_BYTE *)&dword_20001EB0 + v19) == 0 )
        {
          if ( v35 != 0 )
            SIO_GPIO_OUT_SET = 1 << byte_10005504[v19];
          else
            SIO_GPIO_OUT_CLR = 1 << byte_10005504[v19];
        }
      }
    }
LABEL_27:
    LODWORD(v15) = sub_1000239C(a1: 2);
    v18 = byte_20002ED1;
    if ( byte_20002ED1 == 0 )
      goto LABEL_28;
LABEL_8:
    byte_20002ED1 = 0;
    if ( v31 == 0 )
    {
      v15 = sub_100025C8(a1: v15);
      v34 = v15 + 80000;
      if ( (((unsigned __int64)(v15 + 80000) >> 32) & 0x80000000) != 0LL )
        v34 = 0x7FFFFFFFFFFFFFFFLL;
      v36 = 0;
    }
    if ( v30 != 0 )
    {
      v32 += v18;
      v15 = sub_100025C8(a1: v15);
      if ( v33 - v15 > 0 )
        goto LABEL_13;
      v26 = v32;
      if ( v32 <= 0 )
      {
        if ( v32 == 0 )
        {
LABEL_57:
          v30 = v26;
          goto LABEL_13;
        }
        v15 = sub_100025C8(a1: v15);
        v19 = v17;
        if ( v34 - v15 <= 0 )
        {
          v27 = *((unsigned __int8 *)v38 + v17);
          v30 = 0;
LABEL_85:
          v29 = v27 + 1;
          v36 = -1;
          goto LABEL_86;
        }
        v31 = v30;
        v36 = -1;
        v30 = 0;
      }
      else
      {
        v15 = sub_100025C8(a1: v15);
        v19 = v17;
        if ( v34 - v15 <= 0 )
        {
          v27 = *((unsigned __int8 *)v38 + v17);
          v30 = 0;
          goto LABEL_80;
        }
        v31 = v30;
        v36 = 1;
        v30 = 0;
      }
    }
    else
    {
      v25 = sub_100025C8(a1: v15);
      v33 = v25 + 30000;
      if ( (((unsigned __int64)(v25 + 30000) >> 32) & 0x80000000) != 0LL )
        v33 = 0x7FFFFFFFFFFFFFFFLL;
      v32 = v18;
      v15 = sub_100025C8(a1: v25);
      if ( v33 - v15 > 0 )
      {
        v26 = 1;
        goto LABEL_57;
      }
      if ( v18 <= 0 )
      {
        v15 = sub_100025C8(a1: v15);
        v19 = v17;
        if ( v34 - v15 <= 0 )
        {
          v27 = *((unsigned __int8 *)v38 + v17);
          goto LABEL_85;
        }
        v36 = -1;
        v31 = 1;
      }
      else
      {
        v15 = sub_100025C8(a1: v15);
        v19 = v17;
        if ( v34 - v15 <= 0 )
        {
          v27 = *((unsigned __int8 *)v38 + v17);
          goto LABEL_80;
        }
        v36 = 1;
        v31 = 1;
      }
    }
  }
  v20 = 1;
  *((_BYTE *)&dword_20001EB0 + v17) = 1;
  while ( *(&v37 + v20) == *(_BYTE *)(v20 + 268457215) )
  {
    ++v20;
    sub_1000239C(a1: 50);
    if ( v20 == 5 )
    {
      sub_10001218(a1: 0, a2: 32, a3: 0);
      SIO_GPIO_OUT_SET = 0x2000;
      SIO_GPIO_OUT_SET = 4096;
      SIO_GPIO_OUT_SET = 2048;
      SIO_GPIO_OUT_SET = 1024;
      byte_20002ED2 = 1;
      __asm { POP     {R4-R7,PC} }
    }
  }
  SIO_GPIO_OUT_SET = 0x2000;
  SIO_GPIO_OUT_SET = 4096;
  SIO_GPIO_OUT_SET = 2048;
  v21 = 3;
  SIO_GPIO_OUT_SET = 1024;
  do
  {
    sub_10001218(a1: 32, a2: 0, a3: 0);
    sub_1000239C(a1: 200);
    sub_10001218(a1: 0, a2: 0, a3: 0);
    --v21;
    sub_1000239C(a1: 200);
  }
  while ( v21 != 0 );
  dword_20001EB0 = 0;
  SIO_GPIO_OUT_CLR = 0x2000;
  SIO_GPIO_OUT_CLR = 4096;
  SIO_GPIO_OUT_CLR = 2048;
  SIO_GPIO_OUT_CLR = 1024;
  v38[0] = 0;
  SIO_GPIO_OUT_CLR = 128;
  SIO_GPIO_OUT_CLR = 64;
  SIO_GPIO_OUT_CLR = 32;
  SIO_GPIO_OUT_CLR = 16;
  SIO_GPIO_OUT_CLR = 8;
  SIO_GPIO_OUT_CLR = 4;
  SIO_GPIO_OUT_CLR = 2;
  SIO_GPIO_OUT_CLR = 1;
  SIO_GPIO_OUT_CLR = 512;
  SIO_GPIO_OUT_CLR = 256;
  SIO_GPIO_OUT_SET = 128;
  v22 = sub_10001218(a1: 0, a2: 0, a3: 32);
  v15 = sub_100025C8(a1: v22);
  v16 = v15 + 300000;
  if ( (((unsigned __int64)(v15 + 300000) >> 32) & 0x80000000) != 0LL )
    v16 = 0x7FFFFFFFFFFFFFFFLL;
  v19 = 0;
  v17 = 0;
  v35 = 0;
LABEL_26:
  v23 = sub_100025C8(a1: v15);
  v24 = v16 - v23;
  if ( (int)((unsigned __int64)(v16 - v23) >> 32) <= 0 )
    goto LABEL_37;
  goto LABEL_27;
}
