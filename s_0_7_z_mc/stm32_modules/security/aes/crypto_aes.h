/**
 * ***********************************************************
 * @copyright (C)2020 DANFINSWE
 * @author DFS Technology Department
 * @version V1.0.0
 * @date 2020-05-21
 * 
 * @brief AES encrypt/decrypt class
 *        depend on B-Con crypto-algorithms aes 
 *        git : https://github.com/B-Con/crypto-algorithms.git
 * 
 * AES introduce : https://github.com/matt-wu/AES.git
 * ***********************************************************
 */

#ifndef _CRYPTO_AES_H_
#define _CRYPTO_AES_H_

#include "thirdparty\crypto-algorithms\aes.hpp"

#define AES128_KEY_EXP_SIZE (176)
#define AES192_KEY_EXP_SIZE (208)
#define AES256_KEY_EXP_SIZE (240)

typedef enum _crypto_aes_key_length_
{
  AES_128 = 128,
  AES_192 = 192,
  AES_256 = 256
}Aes_key_len;

typedef enum _crypto_aes_opration_mode_
{
  AES_MODE_ECB = 1,
  AES_MODE_CBC,
  AES_MODE_CTR,
  AES_MODE_CCM,
}Aes_mode;

class Crypto_aes
{
  public:
    Crypto_aes(const char* key, Aes_key_len _key_len = AES_128, Aes_mode _mode = AES_MODE_ECB, const char* _iv = NULL);
    ~Crypto_aes();
    void set_inital_vector(const char* _iv);
    int encrypt(const char* in_data, int in_data_len, char* out_data);
    int decrypt(const char* in_data, int in_data_len, char* out_data);

  private:
  Aes_key_len key_len;
  Aes_mode mode;
  unsigned int *key_exp;
  char *iv;
  unsigned char proc_buff[AES_BLOCK_SIZE];
};

#endif


