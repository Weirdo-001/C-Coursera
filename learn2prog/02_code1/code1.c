int max (int num1, int num2) {
  //check if num1 is greater than num2
    //if so, your answer is num1
    //otherwise, your answer is num2
//eturn (a > b) ? a : b;}
    return (num1 > num2) ? num1 : num2;
}
int main(void) {
  printf("max(42, -69) is %d\n", max(42, -69));
  printf("max(33, 0) is %d\n", max(33, 0));
  printf("max(0x123456, 123456) is %d\n", max(0x123456, 123456));
  //compute the max of 0x451215AF and 0x913591AF and print it out as a decimal number
  int hex1 = 0x451215AF;
    int hex2 = 0x913591AF;
    printf("max(0x%X, 0x%X) is %d\n", hex1, hex2, max(hex1, hex2));
  return 0;
}


