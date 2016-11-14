#include <common/toolkit/HashTk.h>

#include <linux/cryptohash.h>

#define get16bits(d) (*((const uint16_t *) (d)))

#define HashTkDefaultHash HASHTK_HALFMD4
//#define HashTkDefaultHash HASHTK_HSIEHHASH32

#define Hashtk_HALFMD4_IN_BUF_SIZE   8
#define HashTk_HALFMD4_OUT_BUF_SIZE  4
#define HashTk_INT_BYTES             4

#define HashTk_HALFMD4_MAJOR_BUFPOS   1 // as in ext4
#define HashTk_HALFMD4_MINOR_BUFPOS   2


static uint32_t HashTk_HsiehHash32(const char* data, int len);

static void HashTk_string2HashBufSigned(const char *msg, int len, __u32 *buf, int num);

/**
 * Copied from ext4 hash.c (str2hashbuf_signed() )
 */
static void HashTk_string2HashBufSigned(const char *msg, int len, __u32 *buf, int num)
{
   __u32 pad, val;
   int   i;
   const signed char *scp = (const signed char *) msg;

   pad = (__u32)len | ((__u32)len << 8);
   pad |= pad << 16;

   val = pad;
   if (len > num*4)
      len = num * 4;
   for (i = 0; i < len; i++) {
      if ((i % 4) == 0)
         val = pad;
      val = ((int) scp[i]) + (val << 8);
      if ((i % 4) == 3) {
         *buf++ = val;
         val = pad;
         num--;
      }
   }
   if (--num >= 0)
      *buf++ = val;
   while (--num >= 0)
      *buf++ = pad;
}


/**
 * Note: This is the Hsieh hash function, which is available under old BSD-style license.
 * (It performs very well on x86 and PowerPC archs compared to other famous hash functions.)
 *
 * @data the buffer for which you want the hash value to be computed (arbitraty length)
 * @len length of the data buffer
 */
uint32_t HashTk_HsiehHash32(const char* data, int len)
{
   uint32_t hash = len, tmp;
   int rem;

   if(unlikely(len <= 0 || data == NULL) )
      return 0;

   rem = len & 3;
   len >>= 2;

   /* Main loop */
   for(; len > 0; len--)
   {
      hash += get16bits(data);
      tmp = (get16bits(data+2) << 11) ^ hash;
      hash = (hash << 16) ^ tmp;
      data += 2 * sizeof(uint16_t);
      hash += hash >> 11;
   }

   /* Handle end cases */
   switch(rem)
   {
      case 3:
         hash += get16bits(data);
         hash ^= hash << 16;
         hash ^= data[sizeof(uint16_t)] << 18;
         hash += hash >> 11;
         break;
      case 2:
         hash += get16bits(data);
         hash ^= hash << 11;
         hash += hash >> 17;
         break;
      case 1:
         hash += *data;
         hash ^= hash << 10;
         hash += hash >> 1;
   }

   /* Force "avalanching" of final 127 bits */
   hash ^= hash << 3;
   hash += hash >> 5;
   hash ^= hash << 4;
   hash += hash >> 17;
   hash ^= hash << 25;
   hash += hash >> 6;

   return hash;
}

/**
 * Do the halfMD4 hash computation.
 * Note: OutBuf must be an array of size HashTk_HALFMD4_OUT_BUF_SIZE
 */
void HashTk_halfMD4(const char* data, int len, uint32_t* outBuf)
{
   uint32_t inBuf[Hashtk_HALFMD4_IN_BUF_SIZE];
   int maxMD4StrLen = Hashtk_HALFMD4_IN_BUF_SIZE * HashTk_INT_BYTES; // 32
   const char* dataPtr = data;
   int remainingLen = len;

   /* Initialize the default seed for the hash checksum functions, magic numbers taken from
    * ext4fs_dirhash() */
   outBuf[0] = 0x67452301;
   outBuf[1] = 0xefcdab89;
   outBuf[2] = 0x98badcfe;
   outBuf[3] = 0x10325476;

   while (remainingLen > 0) {
      HashTk_string2HashBufSigned(dataPtr, len, inBuf, Hashtk_HALFMD4_IN_BUF_SIZE);
      half_md4_transform(outBuf, inBuf);

      remainingLen -= maxMD4StrLen;
      dataPtr      += maxMD4StrLen;
   }
}


uint32_t HashTk_hash32(HashTkHashTypes hashType, const char* data, int len)
{
   switch (hashType)
   {
      default:
      {
         printk_fhgfs(KERN_INFO, "Unknown hashtype: %d\n", hashType);
         hashType = HashTkDefaultHash;
      } // fall through

      case HASHTK_HSIEHHASH32:
      {
         return HashTk_HsiehHash32(data, len);
      } break;

      case HASHTK_HALFMD4:
      {
         uint32_t buf[HashTk_HALFMD4_OUT_BUF_SIZE];
         uint32_t majHash;

         HashTk_halfMD4(data, len, buf);

         majHash = buf[HashTk_HALFMD4_MAJOR_BUFPOS];

         return majHash;

      } break;

   }
}

/**
 * Note: This generates the 64bit hash by computing two 32bit hashes for the first and second half
 * of the data buf.
 *
 * @data the buffer for which you want the hash value to be computed (arbitraty length)
 * @len length of the data buffer
 */
uint64_t HashTk_hash64(HashTkHashTypes hashType, const char* data, int len)
{
   uint64_t hash64;

   switch (hashType)
   {
      default:
      {
         printk_fhgfs(KERN_INFO, "Unknown hashtype: %d\n", hashType);
         hashType = HashTkDefaultHash;
      } // fall through

      case HASHTK_HSIEHHASH32:
      {
         int len1stHalf = len / 2;
         int len2ndHalf = len - len1stHalf;

         uint64_t high = HashTk_HsiehHash32(data, len1stHalf);
         uint64_t low  = HashTk_HsiehHash32(&data[len1stHalf], len2ndHalf);

         hash64 = (high << 32) | low;
      } break;

      case HASHTK_HALFMD4:
      {
         uint32_t buf[HashTk_HALFMD4_OUT_BUF_SIZE];
         uint32_t majHash;
         uint32_t minHash;

         HashTk_halfMD4(data, len, buf);

         majHash = buf[HashTk_HALFMD4_MAJOR_BUFPOS];
         minHash = buf[HashTk_HALFMD4_MINOR_BUFPOS];

         hash64 = (uint64_t) majHash << 32  | (uint64_t) minHash;

      } break;

   }

   return hash64;
}
