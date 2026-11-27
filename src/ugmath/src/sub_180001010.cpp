





extern "C" unsigned short word_1800E1AF8;
extern "C" unsigned short word_1800E1AFC;
unsigned short word_1800E1AF8 = 0xA8A0;
unsigned short word_1800E1AFC = 0x011C;

extern "C" unsigned short sub_180001010() {
  word_1800E1AFC = word_1800E1AF8;
  return word_1800E1AF8;
}
