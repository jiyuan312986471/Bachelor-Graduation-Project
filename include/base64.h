#ifndef __BASE64_H__
#define __BASE64_H__

unsigned char base64_char (char c);
unsigned int base64_decode (char *dest, char *src);
unsigned int base64_ndecode (char *dest, char *src, unsigned int srclen);
unsigned int base64_encode (char *dest, const char *src, unsigned int srclen);

#endif /* __BASE64_H__ */
