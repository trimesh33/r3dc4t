// func 0x10000944

void pass_encoder(uint gpio, uint events)
{
    if (gpio == 27 || gpio == 29) {
        uint8_t current =
            ((SIO_GPIO_IN >> 29) & 1) << 1 |
            ((SIO_GPIO_IN >> 27) & 1);

        int8_t step = transition_table[previous_state * 4 + current];
        previous_state = current;

        if (step != 0)
            encoder_delta += step;
    }

    if (gpio == 28 && (events & GPIO_IRQ_EDGE_FALL))
        button_pressed = true;
}

// initial ida pseudocode

char *__fastcall pass_encoder(char *result, char a2)
{
  int v2; // r3
  int v3; // r2
  int v4; // r2

  if ( ((unsigned int)(result - 27) & 0xFFFFFFFD) != 0 )
  {
    if ( result == (char *)28 && (a2 & 4) != 0 )
      byte_20002ED0 = 1;
  }
  else
  {
    v2 = SIO_GPIO_IN;
    v3 = SIO_GPIO_IN;
    result = &byte_20002ED6;
    LOBYTE(v2) = (2 * ((v2 & 0x20000000) != 0)) | ((v3 & 0x8000000) != 0);
    v4 = byte_100054F0[4 * (unsigned __int8)byte_20002ED6 + (char)v2];
    byte_20002ED6 = v2;
    if ( v4 != 0 )
      byte_20002ED1 += v4;
  }
  return result;
}
