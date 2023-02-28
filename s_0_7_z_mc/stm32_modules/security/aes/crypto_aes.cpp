#include "crypto_aes.h"
#include "string.h"

Crypto_aes::Crypto_aes(const char *key, Aes_key_len _key_len, Aes_mode _mode, const char *_iv)
{
  key_len = _key_len;
  mode = _mode;
  iv = NULL;

  int exp_key_size = 0;
  switch (key_len)
  {
  case AES_128:
    exp_key_size = AES128_KEY_EXP_SIZE;
    break;
  case AES_192:
    exp_key_size = AES128_KEY_EXP_SIZE;
    break;
  case AES_256:
    exp_key_size = AES128_KEY_EXP_SIZE;
    break;
  default:
    exp_key_size = AES128_KEY_EXP_SIZE;
    break;
  }

  key_exp = new unsigned int[exp_key_size];
  if (key_exp != NULL)
  {
    memset(key_exp, 0, exp_key_size);
  }
  aes_key_setup((const unsigned char *)key, key_exp, key_len);
}

Crypto_aes::~Crypto_aes()
{
  if (key_exp != NULL)
  {
    delete key_exp;
    key_exp = NULL;
  }

  if (iv != NULL)
  {
    delete iv;
    iv = NULL;
  }
}

void Crypto_aes::set_inital_vector(const char *_iv)
{
  if (iv == NULL)
  {
    iv = new char[AES_BLOCK_SIZE];
    if (iv != NULL)
    {
      memset(iv, 0, AES_BLOCK_SIZE);
    }
  }

  memcpy(iv, _iv, AES_BLOCK_SIZE);
}

int Crypto_aes::encrypt(const char *in_data, int in_data_len, char *out_data)
{
  if ((in_data == NULL) || (in_data_len == 0) || (out_data == NULL))
  {
    return 0;
  }

  int block_cnt = in_data_len / AES_BLOCK_SIZE;
  int rest_data_cnt = in_data_len % AES_BLOCK_SIZE;
  if (rest_data_cnt != 0)
  {
    block_cnt += 1;
  }

  memset(proc_buff, 0, sizeof(proc_buff));

  switch (mode)
  {
  case AES_MODE_ECB:
    for (int i = 0; i < block_cnt; i++)
    {
      if ((rest_data_cnt > 0) && (i == (block_cnt - 1)))
      {
        memcpy(proc_buff, in_data, rest_data_cnt);
        aes_encrypt(proc_buff, (BYTE *)out_data, key_exp, key_len);
      }
      else
      {
        aes_encrypt((const unsigned char *)in_data, (BYTE *)out_data, key_exp, key_len);
      }
      in_data += AES_BLOCK_SIZE;
      out_data += AES_BLOCK_SIZE;
    }

    break;
  case AES_MODE_CBC:
    // aes_encrypt_cbc(in_data, in_data_len out_data, )
    break;
  case AES_MODE_CTR:
    break;
  case AES_MODE_CCM:
    break;
  default:
    break;
  }

  return block_cnt * AES_BLOCK_SIZE;
}

int Crypto_aes::decrypt(const char *in_data, int in_data_len, char *out_data)
{
  int ret = 0;

  if ((in_data == NULL) || (in_data_len % AES_BLOCK_SIZE != 0) || (out_data == NULL))
  {
    return 0;
  }

  int block_cnt = in_data_len / AES_BLOCK_SIZE;

  memset(proc_buff, 0, sizeof(proc_buff));

  switch (mode)
  {
  case AES_MODE_ECB:
    for (int i = 0; i < block_cnt; i++)
    {
      ret += aes_decrypt((const unsigned char *)in_data, (BYTE *)out_data, key_exp, key_len);
      in_data += AES_BLOCK_SIZE;
      out_data += AES_BLOCK_SIZE;
    }

    break;
  case AES_MODE_CBC:
    // aes_encrypt_cbc(in_data, in_data_len out_data, )
    break;
  case AES_MODE_CTR:
    break;
  case AES_MODE_CCM:
    break;
  default:
    break;
  }

  return ret;
}
