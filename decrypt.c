/*
 * decrypt.c — DECRYPTION ONLY via tlscsp.dll (no key, no crypto code here).
 *
 * Loads the Microsoft-signed DLL, calls LsCsp_EncryptHwid. RC4 is symmetric,
 * so this "encrypt" call actually decrypts data that was RC4-encrypted with the
 * key baked inside the DLL. 20 bytes per call.
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef LONG (WINAPI *EncryptHwidFn)(const void* in, void* out, ULONG* size);

int main(int argc, char** argv) {
    if (argc < 3) { printf("usage: decrypt.exe <encrypted> <output>\n"); return 1; }

    /* 1. load the signed DLL (key lives inside it) */
    HMODULE h = LoadLibraryA("C:\\Windows\\System32\\tlscsp.dll");
    if (!h) { printf("[-] LoadLibrary failed\n"); return 1; }

    /* 2. resolve the export */
    EncryptHwidFn fn = (EncryptHwidFn)GetProcAddress(h, "LsCsp_EncryptHwid");
    if (!fn) { printf("[-] GetProcAddress failed\n"); return 1; }

    /* 3. read the encrypted file */
    FILE* f = fopen(argv[1], "rb");
    if (!f) { printf("[-] open failed\n"); return 1; }
    fseek(f, 0, SEEK_END); long len = ftell(f); fseek(f, 0, SEEK_SET);
    unsigned char* buf = (unsigned char*)malloc(len);
    fread(buf, 1, len, f); fclose(f);

    /* 4. decrypt, 20 bytes per call (the DLL does RC4 with its embedded key) */
    for (long i = 0; i + 20 <= len; i += 20) {
        unsigned char out[20];
        ULONG sz = 20;
        if (fn(buf + i, out, &sz) != 0) { printf("[-] decrypt failed\n"); return 1; }
        memcpy(buf + i, out, 20);
    }

    /* 5. write decrypted output */
    f = fopen(argv[2], "wb");
    fwrite(buf, 1, len, f); fclose(f);
    printf("[+] decrypted %ld bytes -> %s\n", len, argv[2]);
    free(buf);
    return 0;
}
