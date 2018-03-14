#ifndef _JV_PROPERTIES_H_INCLUDE_
#define _JV_PROPERTIES_H_INCLUDE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define  JV_OK          0
#define  JV_ERROR      -1

#define jv_memzero(buf, n) (void *) memset(buf, 0, n)

#ifndef intptr_t
#define intptr_t    long
#define uintptr_t   unsigned long
#endif

typedef intptr_t jv_int_t;
typedef uintptr_t jv_uint_t;

typedef unsigned char  u_char;

typedef struct jv_string_s jv_string_t;

struct jv_string_s {
  size_t len;
  u_char *data;
};

jv_int_t jv_properties_load(FILE *fp, jv_int_t (*callback)(jv_string_t *key, jv_string_t *value));

#endif /* _JV_PROPERTIES_H_INCLUDE_ */
