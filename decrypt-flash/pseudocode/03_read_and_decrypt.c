// func 0x10000354

void decrypt_sector(uint32_t lba, uint8_t sector[0x200])
{
    uint32_t state = 0x9E37A9EAU + lba * 0x38C9CDA0U;

    for (uint32_t block = 0x0; block < 0x200; block += 0x10) {
        for (uint32_t i = 0x0; i < 0x10; ++i) {
            uint32_t value = state + (i - 0x1) * 0x9E3779B1U;
            sector[block + i] ^= value >> 0x18;
        }
        state += 0x41C64E6DU;
    }
}

int read10(uint32_t lba, uint8_t output[0x200])
{
    const uint8_t *encrypted = (uint8_t *)(0x10100000U + lba * 0x200);
    memcpy(output, encrypted, 0x200);
    decrypt_sector(lba, output);
    return 0x200;
}

// initial ida pseudocode

int __fastcall sub_10000354(int a1, unsigned int a2, unsigned int a3, int a4, unsigned int a5)
{
  unsigned int v5; // r4
  int v6; // r11
  int v7; // r5
  unsigned int v8; // r6
  char *v9; // r7
  unsigned int v10; // r3
  unsigned int v11; // r7
  _BYTE v14[0x200]; // [sp+0x8] [bp-0x204] BYREF
  char v15; // [sp+0x208] [bp-0x4] BYREF

  v5 = a3;
  if ( a3 >= 0x200 || a2 >= 0x800 || a3 + (unsigned __int64)a5 > (unsigned __int64)(0x800 - a2) << 0x9 )
    return -0x1;
  if ( a5 != 0x0 )
  {
    v6 = 0x38C9CDA0U * a2 + 0x9E37A9EAU;
    v7 = 0x20 * a2;
    v8 = a5;
    do
    {
      sub_10002E1C(a1: v14, a2: 0x10 * v7 + 0x10100000U, a3: 0x200);
      v9 = v14;
      v10 = v6;
      do
      {
        *((_DWORD *)v9 + 0x1) ^= ((v10 + 0xDAA66D13U) >> 0x18)
                               | ((v10 + 0x78DDE6C4U) >> 0x18 << 0x8)
                               | ((v10 + 0x17156075U) >> 0x18 << 0x10)
                               | ((v10 + 0xB54CDA26U) >> 0x18 << 0x18);
        *((_DWORD *)v9 + 0x2) ^= ((v10 + 0x538453D7U) >> 0x18)
                               | ((v10 + 0xF1BBCD88U) >> 0x18 << 0x8)
                               | ((v10 + 0x8FF34739U) >> 0x18 << 0x10)
                               | ((v10 + 0x2E2AC0EAU) >> 0x18 << 0x18);
        *((_DWORD *)v9 + 0x3) ^= ((v10 + 0xCC623A9BU) >> 0x18)
                               | ((v10 + 0x6A99B44CU) >> 0x18 << 0x8)
                               | ((v10 + 0x08D12DFDU) >> 0x18 << 0x10)
                               | ((v10 + 0xA708A7AEU) >> 0x18 << 0x18);
        *(_DWORD *)v9 ^= ((v10 + 0x3C6EF362U) >> 0x18 << 0x18)
                       | ((v10 + 0x9E3779B1U) >> 0x18 << 0x10)
                       | (HIBYTE(v10) << 0x8)
                       | ((v10 + 0x61C8864FU) >> 0x18);
        v9 += 0x10;
        v10 += 0x41C64E6DU;
      }
      while ( v9 != &v15 );
      v11 = 0x200 - v5;
      if ( 0x200 - v5 > v8 )
        v11 = v8;
      sub_10002E1C(a1: a4, a2: &v14[v5], a3: v11);
      a4 += v11;
      v6 += 0x38C9CDA0U;
      v5 = 0x0;
      v8 -= v11;
      v7 += 0x20;
    }
    while ( v8 != 0x0 );
  }
  return a5;
}
