/*
 * Definitions etc. for regexp(3) routines.
 *
 * Caveat:  this is V8 regexp(3) [actually, a reimplementation thereof],
 * not the System V one.
 */

#ifndef REGEXP_H
#define REGEXP_H


/*
http://www.opensource.apple.com/darwinsource/10.3/expect-1/expect/expect.h ,
which contains a version of this library, says:

 *
 * NSUBEXP must be at least 10, and no greater than 117 or the parser
 * will not work properly.
 *

However, it looks rather like this library is limited to 10.  If you think
otherwise, let us know.
*/

#define NSUBEXP  10
typedef struct regexp {
	char *startp[NSUBEXP];
	char *endp[NSUBEXP];
	char regstart;		/* Internal use only. */
	char reganch;		/* Internal use only. */
	char *regmust;		/* Internal use only. */
	int regmlen;		/* Internal use only. */
	char program[1];	/* Unwarranted chumminess with compiler. */
} regexp;

static regexp * regcomp(char *exp, int *patternsize);
static int regexec(regexp *prog, char *string);
static void regerror(char *s);

#define MAGIC   0234

#endif
