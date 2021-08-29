#include "PathHelper.h"
#include <iostream>
#include <filesystem>


std::string PathHelper::GetUserDirectory() {
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	std::string address;
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						std::wstring b = pszFilePath;
						std::string nstring(b.begin(), b.end());
						address = nstring;

						std::replace(address.begin(), address.end(), '\\', '/');


					}

					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return address;
}

std::string PathHelper::GetRootPath()
{
	std::filesystem::path p = std::filesystem::current_path();
	std::string path_string{ p.u8string() };
	std::replace(path_string.begin(), path_string.end(), '\\', '/'); 
	return path_string;
}


