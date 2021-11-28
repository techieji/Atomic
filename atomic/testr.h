#define P(...) on?printf(__VA_ARGS__):0
#define TESTR_BEGIN P("=== \x1b[1mTestr Start\x1b[0m ===\n");s=f=0
#define TEST(t) P("%sTest %d in file %s, line %d %s (%s).\n",t?"\x1b[92m":"\x1b[91m",t?++s+f:++f+s,__FILE__,__LINE__,t?"succeeded":"failed",t?"omitted":#t)
#define TESTR_END char*c=!f?"\x1b[92m":"\x1b[91m";P("%s=== \x1b[92m%d succeeded, %s%d failed%s ===\x1b[0m\n",c,s,c,f,c);return f
char s=0,f=0,on=1;

int tests() {
	TESTR_BEGIN;
	TEST(1==1);
	TESTR_END;
}
