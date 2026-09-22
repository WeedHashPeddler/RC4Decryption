tlscsp.dll — Ghosted Microsoft RC4 LOLBin (BYOK encrypt/decrypt primitive)

A Microsoft-signed, never-loaded DLL that ships a hardcoded RC4 key.
Call LsCsp_EncryptHwid -> get RC4 encrypt/decrypt running inside trusted
Windows code, with zero crypto in your own binary.

# tlscsp.dll — Ghosted Microsoft RC4 LOLBin

`tlscsp.dll` ("Microsoft Remote Desktop Services Cryptographic Utility") is a
Microsoft-signed DLL in System32 that is **unloaded by default**. Its export
`LsCsp_EncryptHwid` performs **RC4 with a 16-byte key hardcoded in `.rdata`.


## Tested on

Windows 11 latest build (25H2). Older Windows builds ship a slightly different
`tlscsp.dll`, so the key offset may need a small tweak — not covered here.

NOTE- The embedded key is public, so anyone can decrypt. Use BYOK (Bring Your Own Key) — patch the 16 bytes at base + 0x141D0 in memory with your own key before calling the export. Now the DLL encrypts/decrypts with your secret, and your loader still carries no key and no crypto.
