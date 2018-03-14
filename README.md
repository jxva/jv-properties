# Parse .properties configuration file using ANSI C

if you need to parse .ini configuration file, you can also see https://github.com/jxva/jv-ini

## Features

- No dynamic memory allocation
- No dependence
- ~100 LOC
- Supports for separating key and value using '=' or ':'
- Supports comments using '#' or ';'
- Supports value is a string
- Uses callbacks

## Getting Started

### test.properties

```ini
# fdsafsa
hello=world  ;fdsas
ni = "hao        #fds  fsa"
; fdsafsa
china= 中国
chinese =中国人

url = http://129fdsa.com:8080/fdsa?fdas=fdasf&fdsa=vcsa&reqwrw#fdsa

# fdsafafdsafsa

fdsa : 32q4

#.ddddddddddddddddddd

;fdsafas

fdsaf : fdsa


fdsafsa = "this is 
a
string"

342=fd"saf"sa

#fdsfa
;fdsafsafsa
```

### jv_properties_main.c

```c
#include <jv_properties.h>

static jv_int_t callback(jv_string_t *key, jv_string_t *value);

static jv_int_t callback( jv_string_t *key, jv_string_t *value) {
  printf("[%s:%lu] = [%s:%lu]\n", key->data, (jv_uint_t)key->len, value->data, (jv_uint_t)value->len);
  return JV_OK;
}

int main(int argc, char *argv[]) {
  FILE *fp;
  char *file = "test.properties";

  fp = fopen(file, "r");
  if (!fp) {
    fprintf(stderr, "Error opening %s\n", file);
    return JV_ERROR;
  }

  jv_properties_load(fp, callback);

  fclose(fp);
  return 0;
}
```

## Build

    $ make

## Run

    $ ./jv_perperties_main

## Out Print

```ini
[hello:5] = [world;fdsas:11]
[ni:2] = ["hao        #fds  fsa":22]
[china:5] = [中国:6]
[chinese:7] = [中国人:9]
[url:3] = [http://129fdsa.com:8080/fdsa?fdas=fdasf&fdsa=vcsa&reqwrw#fdsa:61]
[fdsa:4] = [32q4:4]
[fdsaf:5] = [fdsa:4]
[fdsafsa:7] = ["this is
a
string":19]
[342:3] = [fd"saf"sa:9]
```

## License

This project is under MIT License. See the [LICENSE](LICENSE) file for the full license text.

