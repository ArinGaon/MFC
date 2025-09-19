// zlib_interface.h
//
// SPx 라이브러리에는 zlib.lib가 포함되어 있는데 헤더 파일은 누락되어 있어서
// 원본 zlib.h에서 압축과 해제에 관련된 선언 부분만 재정의한 것임

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
