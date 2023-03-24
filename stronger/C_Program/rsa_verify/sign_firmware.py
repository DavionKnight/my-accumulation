#coding=utf-8
from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256
from Crypto.Signature import PKCS1_v1_5
import argparse
import struct

TYPE_SIGN = 1
TYPE_FIRMWARE = 3
TYPE_RESERVED = 2

def write_sign_seg(sign_bytes):
    ret = b""
    sign_bytes_length = len(sign_bytes)
    print (sign_bytes_length)
    print(sign_bytes)
    if sign_bytes_length > 0xffff:
        raise Exception("signature too long")

    ret += struct.pack("<B", TYPE_SIGN)
    ret += struct.pack("<H", sign_bytes_length)
    ret += sign_bytes
    return ret

def write_reserved_seg():
    ret = b""
    re_bytes = b"0000000000000000"
    print( 'length is ', len(re_bytes))
    print(re_bytes)

    ret += struct.pack("<B", TYPE_RESERVED)
    print(ret)
    print(len(ret))
    ret += re_bytes
    print(ret)
    return ret


def write_firmware_seg(firmware_bytes):
    ret = b""
    firmware_bytes_length = len(firmware_bytes)
    if firmware_bytes_length > 0xffffffff:
        raise Exception("firmware too long")
    
    ret += struct.pack("<B", TYPE_FIRMWARE)
    ret += struct.pack("<I", firmware_bytes_length)
    ret += firmware_bytes
    return ret

def sign_firmware(private_key_bytes, private_key_passphrase, input_firmware_bytes):
    #private_key = RSA.importKey(private_key_bytes, passphrase=private_key_passphrase)
    private_key = RSA.importKey(private_key_bytes)
    signer = PKCS1_v1_5.new(private_key)

    digest = SHA256.new()
    digest.update(input_firmware_bytes)
    signature = signer.sign(digest)
    
    return write_sign_seg(signature) + write_reserved_seg() + write_firmware_seg(input_firmware_bytes)

def merge_firmware_seg():
    ret = b""
    with open("Hawk_Station_APP_A.bin", "rb") as f:
        firmware_bytes_a = f.read()
        ret += firmware_bytes_a
        f.close()
    with open("Hawk_Station_APP_B.bin", "rb") as f:
        firmware_bytes_b = f.read()
        ret += firmware_bytes_b
        f.close()
    with open("Hawk_Station_APP_merged.bin", "wb") as f:
        f.write(ret)
        print(len(ret))
        f.close()

def main():
    parser = argparse.ArgumentParser(description="Swift tracker MCU firmware sign tool")
    parser.add_argument("-k", "--key", help="private key file for firmware signing", required=True)
    parser.add_argument("-p", "--password", help="password of the private key")
    parser.add_argument("-i", "--input", help="input MCU firmware for signing", required=True)
    parser.add_argument("-o", "--output", help="output MCU signed firmware, if not specified, use signed_(input_firmware_name) as output filename", required=False)

    args = parser.parse_args()
    print(args)

    with open(args.key, "rb") as f:
        private_key_bytes = f.read()
    with open(args.input, "rb") as f:
        firmware_bytes = f.read()
        print(len(firmware_bytes))
    
    signed_firmware_bytes = sign_firmware(private_key_bytes, args.password, firmware_bytes)

    output_filename = args.output
    if output_filename == None:
        output_filename = "signed_"+args.input
    with open(output_filename, "wb") as f:
        f.write(signed_firmware_bytes)
    
    print("firwmare signed at ", output_filename)

if __name__ == "__main__":
#    merge_firmware_seg()
    main()