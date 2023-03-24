#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h> 
#include <openssl/crypto.h> 
 
/*
 * 参考https://blog.csdn.net/zjf535214685/article/details/82182241
 */ 
#define PUBLIC_KEY_PATH  ("./public.pem")
#define PRIVATE_KEY_PATH ("./rsa_test.pri")
 
#define isUseSha256    (1)
 
#if isUseSha256
#define SHA_WHICH        NID_sha256
#define WHICH_DIGEST_LENGTH    SHA256_DIGEST_LENGTH
#else
#define SHA_WHICH        NID_sha512
#define WHICH_DIGEST_LENGTH    SHA512_DIGEST_LENGTH
#endif
 
 
void printHex(unsigned char *md, int len)
{
 
    int i = 0;
    for (i = 0; i < len; i++) {
        printf("%02x", md[i]);
    }
 
    printf("\n");
}
 
/*读取私钥*/
RSA* ReadPrivateKey(char* p_KeyPath)
{   
    FILE *fp = NULL; 
    RSA  *priRsa = NULL;
 
    printf("PrivateKeyPath[%s] \n", p_KeyPath);
 
    /*  打开密钥文件 */
    if(NULL == (fp = fopen(p_KeyPath, "r"))) {
        printf( "fopen[%s] failed \n", p_KeyPath);
        return NULL;
    }
    /*  获取私钥 */
    priRsa = PEM_read_RSAPrivateKey(fp, NULL, NULL,NULL);
    if(NULL == priRsa) {
        ERR_print_errors_fp(stdout);
        printf( "PEM_read_RSAPrivateKey\n");
        fclose(fp);
        return NULL;
    }
    fclose(fp);
 
    return priRsa;
}
 
/*读取公匙*/
RSA* ReadPublicKey(char* p_KeyPath)
{   
    FILE *fp = NULL; 
    RSA *pubRsa = NULL;
 
    printf("PublicKeyPath[%s]\n", p_KeyPath);
 
    /*  打开密钥文件 */
    if(NULL == (fp = fopen(p_KeyPath, "r"))) {
        printf( "fopen[%s] \n", p_KeyPath);
        return NULL;
    }
    /*  获取公钥 */
    if(NULL == (pubRsa = PEM_read_RSA_PUBKEY(fp, NULL, NULL,NULL)))
    {
        printf( "PEM_read_RSAPubKey error\n");
        fclose(fp);
        return NULL;
    }
    fclose(fp);
 
    return pubRsa;
}
 
int RSA_sign_verify(unsigned char *sha, int sha_len, unsigned char *data, int *len)
{
    RSA *pubKey = NULL;
    RSA *privKey = NULL;
    int nRet = 0;
 
    printf("sha256:\n");
    //1. 对数据进行sha256算法摘要
    unsigned char md[WHICH_DIGEST_LENGTH];
#if isUseSha256
    SHA256((unsigned char *)data, len, md);
#else
    SHA512((unsigned char *)data, len, md);
#endif
    printHex(md, WHICH_DIGEST_LENGTH);
    printf("sha256:\n");
    printHex(sha, sha_len);
 
 
    // 3. 读取公匙
    pubKey = ReadPublicKey(PUBLIC_KEY_PATH);  
    if(!pubKey) {
        RSA_free(privKey);   
        printf("Error: can't load public key");
        return -1;
    }
 
    // 5. 验签 
    nRet = RSA_verify(SHA_WHICH, md, WHICH_DIGEST_LENGTH, sha, sha_len, pubKey);
    if(nRet != 1) {
        printf("RSA_verify err !!! \n");    
        goto quit;
    }
    printf("RSA_verify Success !!! \n");  
 
quit:
    RSA_free(privKey);
    RSA_free(pubKey);
 
    return 0;
}
 
int binary_parse(char *path, unsigned char *sha, int *sha_len, unsigned char *data, int *data_len)
{
    unsigned char *buf = (unsigned char *)malloc(200*1024);
    int ret = 0;

    memset(buf, 0, 200*1024);
    int fd = open(path, O_RDONLY); 
    ret = read(fd, buf, 200*1024);
    if (ret < 1024) {
        printf("err\n");
    }
    *sha_len = *(unsigned short*)(buf+1);
    printf("sha_len=%d,ret=%d\n", *sha_len,ret);
    if (*sha_len > 256) {
        printf("sha_len=%d err\n", *sha_len);
        free(buf);
        return -1;
    }
    memcpy(sha, buf + 3 , *sha_len);
    *data_len = *(unsigned int*)(buf+1+2+*sha_len+1 + 16 + 1); 
    printf("data_len=%d\n", *data_len);
    memcpy(data, buf + 3 + *sha_len + 1 + 16 + 1 + 4, *data_len);
    printf("1data_len=%d\n", *data_len);

    close(fd);
    free(buf);

    return 0;
}
int save_bin(unsigned char *data, int len)
{
    if (len%2 == 0) {
        FILE *fd = fopen("./fist.bin", "w");
        fwrite(data, 1, len/2, fd);
        fclose(fd);
        FILE *ffd = fopen("./second.bin", "w");
        fwrite(data + len/2, 1, len/2, ffd);
        fclose(ffd);
        printf("save ok\n");
    } else {
        printf("save err len:%d\n", len);
    }
}
 
int main(int argc, char *argv[])
{
    char *p = argv[1];
    unsigned char sha[256] = {0};
    unsigned char *data = NULL;
    int data_len = 0;
    int sha_len = 0;

    data = (unsigned char *)malloc(200*1024);
    binary_parse(p, sha, &sha_len, data, &data_len);
    printf("before verify=%d\n", data_len);
    save_bin(data, data_len);

    RSA_sign_verify(sha, sha_len, data, data_len);
    return 0;
}
