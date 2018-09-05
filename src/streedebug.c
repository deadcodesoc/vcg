#ifdef ANSI_C
void CheckTree(yysyntaxtree x)
#else
void CheckTree(x)
yysyntaxtree x;
#endif
{
        register int j,len;

        if (!x) return(x);
        len = nr_of_sons(x);

        if (tag(x)==T_Co_string) {
                j = get_lnum(x);
                if (j==0) printf("%d has string %d\n",x,j);
        }

        for (j=1; j<=len; j++) {
                CheckTree(son(x,j));
        }
}


