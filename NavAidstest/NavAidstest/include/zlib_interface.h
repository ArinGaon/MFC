// zlib_interface.h
//
// SPx ���̺귯������ zlib.lib�� ���ԵǾ� �ִµ� ��� ������ �����Ǿ� �־
// ���� zlib.h���� ����� ������ ���õ� ���� �κи� �������� ����

//typedef unsigned char Byte;
//typedef unsigned long uLong;
//
//int compress2(Byte *dest, uLong *destLen, const Byte *source, uLong sourceLen, int level);
//int uncompress (Byte *dest,   uLong *destLen, const Byte *source, uLong sourceLen);
//
//typedef unsigned char Byte;
//typedef unsigned long uLong;


int compress2(U08 *dest, U32 *destLen, const U08 *source, U32 sourceLen, int level);
int uncompress (U08 *dest,   U32 *destLen, const U08 *source, U32 sourceLen);

#define	Z_OK	0
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
