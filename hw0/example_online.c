#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
const char *input = "WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW";
const char *output = "12W1B12W3B24W1B14W";
 
typedef void (*YIELDCHAR)(); /* yields via yield_init */
typedef void (*GENCHAR) ();
 
/* #include <macro.h> :-) */
typedef enum{FALSE=0, TRUE=1}BOOL;
 
#ifdef NEED_GOTO
#include <setjmp.h>
/* declare label otherwise it is not visible in sub-scope */
#define LABEL(label) jmp_buf label; if(setjmp(label))goto label;
#define GOTO(label) longjmp(label, TRUE)
#endif
 
/* the following line is the only time I have ever required "auto" */
#define FOR(i,iterator) auto BOOL lambda(i); yield_init = (void *)&lambda; iterator; BOOL lambda(i)
#define DO {
#define     YIELD(x) if(!yield(x))return
#define     BREAK return FALSE
#define     CONTINUE return TRUE
#define OD CONTINUE; }
/* Warning: _Most_ FOR(,){ } loops _must_ have a CONTINUE, BREAK
 * or OD as the terminating statement. Otherwise the lambda will 
 * return random value from stack, and may terminate early */
 
typedef BOOL ITERATOR;
static volatile void *yield_init; /* not thread safe */
#define YIELDS(type) BOOL (*yield)(type) = yield_init
 
ITERATOR gen_char_seq (const char *s){
  YIELDS(char);
  fflush(stdout);
  int upb_s = strlen(s);
  int i; for(i = 0; i <= upb_s; i++) YIELD(s[i]);
}
 
void input_seq (){ YIELDS(char); FOR(char c, gen_char_seq(input))DO yield(c); OD; }
void output_seq (){ YIELDS(char); FOR(char c, gen_char_seq(output))DO yield(c); OD; }
 
ITERATOR gen_encode (GENCHAR gen_char){
  YIELDS(char);
  int count = 0;
  char prev;
  FOR(char c, gen_char())DO
      if(count == 0){
        count = 1;
        prev = c;
      } else if(c != prev){
        char str_count[32]; sprintf(str_count, "%d", count);
        FOR(char c, gen_char_seq(str_count))DO YIELD(c); OD;
        count = 1;
        YIELD(prev); prev = c;
      } else {
        count += 1;
      }
  OD;
  if(count != 0){
    char str_count[32]; sprintf(str_count, "%d", count);
    FOR(char c, gen_char_seq(str_count))DO YIELD(c); OD;
    YIELD(prev);
  }
}
 
const char *zero2nine = "0123456789";
 
ITERATOR gen_decode (GENCHAR gen_char){
  YIELDS(char);
  int repeat = 0;
  FOR(char c, (*gen_char)())DO
    if(strchr(zero2nine, c)){
      repeat = repeat*10 + c - '0';
    } else {
      int i; for(i = 1; i <= repeat; i++ ){ YIELD(c); }
      repeat = 0;
    }
  OD
}
 
int main(){
  /* iterate through input string */
  printf("Encode input: ");
    FOR(char c, gen_encode(input_seq))DO
      putchar(c);
    OD;
  printf("\n");
 
  /* iterate through output string */
  printf("Decode output: ");
    FOR(char c, gen_decode(output_seq))DO
      putchar(c);
    OD;
  printf("\n");
  return 0;
}
