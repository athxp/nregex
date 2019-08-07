#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Fungsi iki gunane, kanggo ngganti inputan regex sing ditulis nganggo aturan
 * tulis biasa(infix) dadi aturan tulis polandia kuwalik(postfix)
 * contone: a(bb)+a dadi abb.+.a.
 *
 * @param regex sing ditulis nganggo aturan biasa(infix)
 * @return regex sing ditulis nganggo aturan polandia kuwalik(postfix)
 */

char *re2post(char *re)
{
	int loop = 0;
	int nalt, natom;
	static char buf[8000];
	char *dst;
	struct {
		int nalt;
		int natom;
	} paren[100], *p;

	p = paren;
	dst = buf;
	nalt = 0;
	natom = 0;
	// kukut nek re ne kedawan
	if (strlen(re) >= sizeof buf / 2)
		return NULL;
	for (; *re; re++) {
		switch (*re) {
		case '(':
			if (natom > 1) {
				--natom;
				*dst++ = '.';
			}
			// iki artine podo karo nek i > p.lenght
			if (p >= paren + 100)
				return NULL;
			p->nalt = nalt;
			p->natom = natom;
			p++;
			nalt = 0;
			natom = 0;
			break;
		case '|':
			if (natom == 0)
				return NULL;
			while (--natom > 0)
				*dst++ = '.';
			nalt++;
			break;
		case ')':
			if (p == paren)
				return NULL;
			if (natom == 0)
				return NULL;
			while (--natom > 0)
				*dst++ = '.';
			for (; nalt > 0; nalt--)
				*dst++ = '|';
			--p;
			nalt = p->nalt;
			natom = p->natom;
			natom++;
			break;
		case '*':
		case '+':
		case '?':
			if (natom == 0)
				return NULL;
			*dst++ = *re;
			break;
		default:
			if (natom > 1) {
				--natom;
				*dst++ = '.';
			}
			*dst++ = *re;
			natom++;
			break;
		}
		loop++;
	}
	if (p != paren)
		return NULL;
	while (--natom > 0)
		*dst++ = '.';
	for (; nalt > 0; nalt--)
		*dst++ = '|';
	*dst = 0;
	return buf;
}

int main()
{
	char regex[] = "a(bb)+a";
	char *ret;
	ret = re2post(regex);
	printf("%s\n", ret);
	return 0;
}
