#include "CreateScenePck.h"
#include "PckCommon.h"
#include "Compression.h"
#include <string>
#include <vector>

void decrypt_1(byte* debuf, size_t desize, PBYTE PrivateKey)
{
	size_t key_idx = 0;
	size_t xor_idx = 0;

	for (xor_idx = 0; xor_idx<desize; xor_idx++, key_idx++, key_idx = key_idx & 0x8000000F)
	{
		debuf[xor_idx] ^= PrivateKey[key_idx];
	}
}

void decrypt_2(byte* debuf, size_t desize)
{
	size_t key_idx = 0;
	size_t xor_idx = 0;

	static byte key[] =
	{
		0x70, 0xF8, 0xA6, 0xB0, 0xA1, 0xA5, 0x28, 0x4F, 0xB5, 0x2F, 0x48, 0xFA, 0xE1, 0xE9, 0x4B, 0xDE,
		0xB7, 0x4F, 0x62, 0x95, 0x8B, 0xE0, 0x03, 0x80, 0xE7, 0xCF, 0x0F, 0x6B, 0x92, 0x01, 0xEB, 0xF8,
		0xA2, 0x88, 0xCE, 0x63, 0x04, 0x38, 0xD2, 0x6D, 0x8C, 0xD2, 0x88, 0x76, 0xA7, 0x92, 0x71, 0x8F,
		0x4E, 0xB6, 0x8D, 0x01, 0x79, 0x88, 0x83, 0x0A, 0xF9, 0xE9, 0x2C, 0xDB, 0x67, 0xDB, 0x91, 0x14,
		0xD5, 0x9A, 0x4E, 0x79, 0x17, 0x23, 0x08, 0x96, 0x0E, 0x1D, 0x15, 0xF9, 0xA5, 0xA0, 0x6F, 0x58,
		0x17, 0xC8, 0xA9, 0x46, 0xDA, 0x22, 0xFF, 0xFD, 0x87, 0x12, 0x42, 0xFB, 0xA9, 0xB8, 0x67, 0x6C,
		0x91, 0x67, 0x64, 0xF9, 0xD1, 0x1E, 0xE4, 0x50, 0x64, 0x6F, 0xF2, 0x0B, 0xDE, 0x40, 0xE7, 0x47,
		0xF1, 0x03, 0xCC, 0x2A, 0xAD, 0x7F, 0x34, 0x21, 0xA0, 0x64, 0x26, 0x98, 0x6C, 0xED, 0x69, 0xF4,
		0xB5, 0x23, 0x08, 0x6E, 0x7D, 0x92, 0xF6, 0xEB, 0x93, 0xF0, 0x7A, 0x89, 0x5E, 0xF9, 0xF8, 0x7A,
		0xAF, 0xE8, 0xA9, 0x48, 0xC2, 0xAC, 0x11, 0x6B, 0x2B, 0x33, 0xA7, 0x40, 0x0D, 0xDC, 0x7D, 0xA7,
		0x5B, 0xCF, 0xC8, 0x31, 0xD1, 0x77, 0x52, 0x8D, 0x82, 0xAC, 0x41, 0xB8, 0x73, 0xA5, 0x4F, 0x26,
		0x7C, 0x0F, 0x39, 0xDA, 0x5B, 0x37, 0x4A, 0xDE, 0xA4, 0x49, 0x0B, 0x7C, 0x17, 0xA3, 0x43, 0xAE,
		0x77, 0x06, 0x64, 0x73, 0xC0, 0x43, 0xA3, 0x18, 0x5A, 0x0F, 0x9F, 0x02, 0x4C, 0x7E, 0x8B, 0x01,
		0x9F, 0x2D, 0xAE, 0x72, 0x54, 0x13, 0xFF, 0x96, 0xAE, 0x0B, 0x34, 0x58, 0xCF, 0xE3, 0x00, 0x78,
		0xBE, 0xE3, 0xF5, 0x61, 0xE4, 0x87, 0x7C, 0xFC, 0x80, 0xAF, 0xC4, 0x8D, 0x46, 0x3A, 0x5D, 0xD0,
		0x36, 0xBC, 0xE5, 0x60, 0x77, 0x68, 0x08, 0x4F, 0xBB, 0xAB, 0xE2, 0x78, 0x07, 0xE8, 0x73, 0xBF,
		0xD8, 0x29, 0xB9, 0x16, 0x3D, 0x1A, 0x76, 0xD0, 0x87, 0x9B, 0x2D, 0x0C, 0x7B, 0xD1, 0xA9, 0x19,
		0x22, 0x9F, 0x91, 0x73, 0x6A, 0x35, 0xB1, 0x7E, 0xD1, 0xB5, 0xE7, 0xE6, 0xD5, 0xF5, 0x06, 0xD6,
		0xBA, 0xBF, 0xF3, 0x45, 0x3F, 0xF1, 0x61, 0xDD, 0x4C, 0x67, 0x6A, 0x6F, 0x74, 0xEC, 0x7A, 0x6F,
		0x26, 0x74, 0x0E, 0xDB, 0x27, 0x4C, 0xA5, 0xF1, 0x0E, 0x2D, 0x70, 0xC4, 0x40, 0x5D, 0x4F, 0xDA
	};
	for (xor_idx = 0; xor_idx<desize; xor_idx++, key_idx++, key_idx = key_idx & 0x800000FF)
	{
		debuf[xor_idx] ^= key[key_idx];
	}
}

NTSTATUS FASTCALL CreateScenePck(HWND hParent, PBYTE PrivateKey, LPCWSTR Path, LPCWSTR OutputFileName, BOOL NeedExtraKey)
{
	WCHAR FullPath[MAX_PATH];
	BOOL HasSeparator = FALSE;
	ULONG_PTR Length = lstrlenW(Path);
	if (Path[Length - 1] == L'\\' || Path[Length - 1] == L'/')
		HasSeparator = TRUE;


	FILE* f = _wfopen(L"Scene.pck", L"rb");
	if (!f)
	{
		MessageBoxW(hParent, L"Couldn't open original pck file!", L"SiglusExtract", MB_OK | MB_ICONERROR);
		return STATUS_NO_SUCH_FILE;
	}
	fseek(f, 0, SEEK_END);
	unsigned int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	auto buf = (unsigned char*)malloc(size);
	fread(buf, size, 1, f);
	fclose(f);

	WCHAR ScriptFileName[MAX_PATH];
	WCHAR OutScriptFileName[MAX_PATH];

	SCENEHEADER* header = (SCENEHEADER*)buf;
	HEADERPAIR* SceneNameLength = (HEADERPAIR*)&buf[header->SceneNameIndex.offset];
	wchar_t* SceneNameString = (wchar_t*)&buf[header->SceneName.offset];
	HEADERPAIR* SceneDataInfo = (HEADERPAIR*)&buf[header->SceneInfo.offset];
	byte* SceneData = (byte*)&buf[header->SceneData.offset];
	std::vector<BYTE> disk_buffer;
	unsigned int disk_offset = 0;
	for (DWORD i = 0; i<header->SceneNameIndex.count; i++)
	{
		RtlZeroMemory(ScriptFileName, sizeof(ScriptFileName));
		RtlZeroMemory(OutScriptFileName, sizeof(OutScriptFileName));
		wcsncpy(ScriptFileName, &SceneNameString[SceneNameLength[i].offset], SceneNameLength[i].count);
		wsprintfW(OutScriptFileName, L"%d.%s.ss", i, ScriptFileName);

		if (HasSeparator)
			wsprintfW(FullPath, L"%s%s", Path, OutScriptFileName);
		else
			wsprintfW(FullPath, L"%s\\%s", Path, OutScriptFileName);

		FILE* pf = _wfopen(FullPath, L"rb");
		if (!pf)
		{
			MessageBoxW(hParent, (L"Couldn't open ss script file[" + std::wstring(OutScriptFileName) + L"]!").c_str(), L"SiglusExtract", MB_OK | MB_ICONERROR);
			return STATUS_NO_SUCH_FILE;
		}
		fseek(pf, 0, SEEK_END);
		size_t length_of_ss = ftell(pf);
		fseek(pf, 0, SEEK_SET);
		byte* tmpbuf = new byte[length_of_ss];
		fread(tmpbuf, length_of_ss, 1, pf);
		fclose(pf);

		int complen = 0;
		//has header
		PBYTE outbuffer = CompressData(tmpbuf, length_of_ss, &complen, 17);

		SceneDataInfo[i].offset = disk_offset;
		SceneDataInfo[i].count = complen;

		decrypt_2(outbuffer, complen);

		if (NeedExtraKey)
			decrypt_1(outbuffer, complen, PrivateKey);

		for (ULONG i = 0; i < complen + sizeof(compress_file_header_t); i++)
		{
			disk_buffer.push_back(outbuffer[i]);
		}
		disk_offset += complen + sizeof(compress_file_header_t);

		delete tmpbuf;
		free(outbuffer);
	}

	FILE* newf = _wfopen(OutputFileName, L"wb");
	if (!newf)
	{
		MessageBoxW(hParent, (L"Couldn't create file [" + std::wstring(OutputFileName) + L"]").c_str(), L"SiglusExtract", MB_OK | MB_ICONERROR);
		return STATUS_UNSUCCESSFUL;
	}
	fwrite(header, 1, header->SceneData.offset, newf);
	fwrite(&disk_buffer[0], 1, disk_buffer.size(), newf);
	fclose(newf);

	free(buf);
	return STATUS_SUCCESS;
}

