asm(".long 0x1badb002, 0, (-(0x1badb002 + 0))");

unsigned short *video_buffer = (unsigned short *)0xb8000;

char *message = "Hello, world!";

void kernel_main(void)
{
  for (int i = 0; i < 80 * 25; i++)
  {
    video_buffer[i] = (video_buffer[i] & 0xff00) | ' ';
  }

  for (int i = 0; message[i] != '\0'; i++)
  {
    video_buffer[i] = (video_buffer[i] & 0xff00) | message[i];
  }

  while (1)
    ;
}
