#include <jv_properties.h>

#define BUFFER_SIZE 2048

static jv_int_t jv_parser_until(FILE *fp, u_char *buffer, size_t size, u_char *delims);

static jv_int_t jv_parser_until(FILE *fp, u_char *buffer, size_t size, u_char *delims) {
  char c;
  size_t i = 0;
  int string = 0;

  jv_memzero(buffer, size);

  while (i < size) {
    c = getc(fp);
    if (isblank(c) && string == 0) {
      continue;
    } else if (c == '\"') {
      string++;
    } else if (c == EOF) {
      return i;
    } else {
      u_char d;
      u_char *s = delims;

      while ((d = *s++) != '\0') {
        if (c == d && string !=1) {
          buffer[i] = '\0';
          if (d == '=' || d == ':')
            ungetc(c, fp);
          return i;
        }
      }
    }
    buffer[i++] = c;
  }
  buffer[i] = '\0';
  return JV_ERROR;
}


jv_int_t jv_properties_load(FILE *fp, jv_int_t (*callback)(jv_string_t *key, jv_string_t *value)) {
  int c;
  int r;

  u_char key_buf[BUFFER_SIZE];
  u_char value_buf[BUFFER_SIZE];

  jv_string_t key;
  jv_string_t value;

  while ((c = getc(fp)) != EOF) {
    switch (c) {
      case ';':
      case '#': {
        while ((c = getc(fp)) != '\n') {
          if (c == EOF)
            break;
        }
        break;
      }
      case ':':
      case '=': {
        r = jv_parser_until(fp, value_buf, BUFFER_SIZE, (u_char *) "\r\n");
        if (r == JV_ERROR)
          return JV_ERROR;
	      value.data = value_buf;
        value.len = r;
        r = callback( &key, &value);
        if (r == JV_ERROR)
          return JV_ERROR;
        break;
      }
      case '\r':
      case '\n':
      case ' ':
      case '\t':
        break;
      default:
        ungetc(c, fp);
        r = jv_parser_until(fp, key_buf, BUFFER_SIZE, (u_char *) "=:");
        if (r == JV_ERROR)
          return JV_ERROR;
		    key.data = key_buf;
        key.len = r;
        break;
    }
  }
  return JV_OK;
}
