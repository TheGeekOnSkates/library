#pragma once
#define _WIN32_DCOM

#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <sstream>
#include <cstdint>

using namespace std;

#pragma comment(lib, "wbemuuid.lib")

/**
* Gets low-level system info using WMI
* @param[in] The name of the variable to get
* @param[out] The data (whatever type you put in - there are/will be several overloads)
* @return "Done" on success or an error message on failure
* @remarks This code was modified from this link on MSDN: https://msdn.microsoft.com/en-us/library/aa390423(v=vs.85).aspx
* It gives you a big chunk of code and some minimal explanation, but it has links to pages
* that gives additional details about each step of the process.  If this function runs into
* crazy problems, it should have more than enough info to ix it; it's just a matter of research.
*/
const wchar_t * GetWMIData(const char * query, const wchar_t * info, wstring & OutputVar)
{
	// Declare variables
	wstringstream ss;
	HRESULT hres;

	// Initialize COM
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		ss << "Failed to initialize COM library. Error code = 0x"
			<< hex << hres << endl;
		return ss.str().c_str();
	}

	// Set "general" COM security levels
	hres = CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
	);
	if (FAILED(hres))
	{
		ss << "Failed to initialize security. Error code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return ss.str().c_str();
	}

	// Get a pointer to WMI
	IWbemLocator *pLoc = NULL;
	hres = CoCreateInstance
	(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc
	);
	if (FAILED(hres))
	{
		ss << "Failed to create IWbemLocator object."
			<< " Err code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return ss.str().c_str();
	}

	// Connect to WMI through the IWbemLocator::ConnectServer method
	IWbemServices *pSvc = NULL;

	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (for example, Kerberos)
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
	);
	if (FAILED(hres))
	{
		ss << "Could not connect. Error code = 0x"
			<< hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Set security levels on the proxy
	hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);
	if (FAILED(hres))
	{
		ss << "Could not set proxy blanket. Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Query the OS (interesting, Windows seems to use some kind of SQL DB under the hood)
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(query),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator
	);

	if (FAILED(hres))
	{
		ss << "Query for operating system name failed."
			<< " Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Get the data from the query
	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (uReturn == 0)
			break;
		VARIANT vtProp;

		// And we can finally get the value of the Name property
		hr = pclsObj->Get(info, 0, &vtProp, 0, 0);
		const wchar_t * temp = vtProp.bstrVal;
		OutputVar = temp;
		VariantClear(&vtProp);
		pclsObj->Release();

		// Clean up
		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		CoUninitialize();
		return L"Done";
	}
}
const wchar_t * GetWMIData(const char * query, const wchar_t * info, int & OutputVar)
{
	// Declare variables
	wstringstream ss;
	HRESULT hres;

	// Initialize COM
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		ss << "Failed to initialize COM library. Error code = 0x"
			<< hex << hres << endl;
		return ss.str().c_str();
	}

	// Set "general" COM security levels
	hres = CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
	);
	if (FAILED(hres))
	{
		ss << "Failed to initialize security. Error code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return ss.str().c_str();
	}

	// Get a pointer to WMI
	IWbemLocator *pLoc = NULL;
	hres = CoCreateInstance
	(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc
	);
	if (FAILED(hres))
	{
		ss << "Failed to create IWbemLocator object."
			<< " Err code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return ss.str().c_str();
	}

	// Connect to WMI through the IWbemLocator::ConnectServer method
	IWbemServices *pSvc = NULL;

	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (for example, Kerberos)
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
	);
	if (FAILED(hres))
	{
		ss << "Could not connect. Error code = 0x"
			<< hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Set security levels on the proxy
	hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);
	if (FAILED(hres))
	{
		ss << "Could not set proxy blanket. Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Query the OS (interesting, Windows seems to use some kind of SQL DB under the hood)
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(query),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator
	);

	if (FAILED(hres))
	{
		ss << "Query for operating system name failed."
			<< " Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Get the data from the query
	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (uReturn == 0)
			break;
		VARIANT vtProp;

		// And we can finally get the value of the Name property
		hr = pclsObj->Get(info, 0, &vtProp, 0, 0);
		OutputVar = vtProp.intVal;
		VariantClear(&vtProp);
		pclsObj->Release();

		// Clean up
		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		CoUninitialize();
		return L"Done";
	}
}
const wchar_t * GetWMIData(const char * query, const wchar_t * info, uint64_t & OutputVar)
{
	// Declare variables
	wstringstream ss;
	HRESULT hres;

	// Initialize COM
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		ss << "Failed to initialize COM library. Error code = 0x"
			<< hex << hres << endl;
		return ss.str().c_str();
	}

	// Set "general" COM security levels
	hres = CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
	);
	if (FAILED(hres))
	{
		ss << "Failed to initialize security. Error code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return ss.str().c_str();
	}

	// Get a pointer to WMI
	IWbemLocator *pLoc = NULL;
	hres = CoCreateInstance
	(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc
	);
	if (FAILED(hres))
	{
		ss << "Failed to create IWbemLocator object."
			<< " Err code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return ss.str().c_str();
	}

	// Connect to WMI through the IWbemLocator::ConnectServer method
	IWbemServices *pSvc = NULL;

	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (for example, Kerberos)
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
	);
	if (FAILED(hres))
	{
		ss << "Could not connect. Error code = 0x"
			<< hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Set security levels on the proxy
	hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);
	if (FAILED(hres))
	{
		ss << "Could not set proxy blanket. Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Query the OS (interesting, Windows seems to use some kind of SQL DB under the hood)
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(query),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator
	);

	if (FAILED(hres))
	{
		ss << "Query for operating system name failed."
			<< " Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Get the data from the query
	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (uReturn == 0)
			break;
		VARIANT vtProp;

		// And we can finally get the value of the Name property
		hr = pclsObj->Get(info, 0, &vtProp, 0, 0);
		OutputVar = vtProp.uintVal;
		VariantClear(&vtProp);
		pclsObj->Release();

		// Clean up
		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		CoUninitialize();
		return L"Done";
	}
}
const wchar_t * GetWMIData(const char * query, const wchar_t * info, DATE & OutputVar)
{
	// Declare variables
	wstringstream ss;
	HRESULT hres;

	// Initialize COM
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		ss << "Failed to initialize COM library. Error code = 0x"
			<< hex << hres << endl;
		return ss.str().c_str();
	}

	// Set "general" COM security levels
	hres = CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
	);
	if (FAILED(hres))
	{
		ss << "Failed to initialize security. Error code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return ss.str().c_str();
	}

	// Get a pointer to WMI
	IWbemLocator *pLoc = NULL;
	hres = CoCreateInstance
	(
		CLSID_WbemLocator,
		0,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID *)&pLoc
	);
	if (FAILED(hres))
	{
		ss << "Failed to create IWbemLocator object."
			<< " Err code = 0x"
			<< hex << hres << endl;
		CoUninitialize();
		return ss.str().c_str();
	}

	// Connect to WMI through the IWbemLocator::ConnectServer method
	IWbemServices *pSvc = NULL;

	// Connect to the root\cimv2 namespace with
	// the current user and obtain pointer pSvc
	// to make IWbemServices calls.
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // User name. NULL = current user
		NULL,                    // User password. NULL = current
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority (for example, Kerberos)
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
	);
	if (FAILED(hres))
	{
		ss << "Could not connect. Error code = 0x"
			<< hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Set security levels on the proxy
	hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);
	if (FAILED(hres))
	{
		ss << "Could not set proxy blanket. Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Query the OS (interesting, Windows seems to use some kind of SQL DB under the hood)
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(query),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator
	);

	if (FAILED(hres))
	{
		ss << "Query for operating system name failed."
			<< " Error code = 0x"
			<< hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ss.str().c_str();
	}

	// Get the data from the query
	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (uReturn == 0)
			break;
		VARIANT vtProp;

		// And we can finally get the value of the Name property
		hr = pclsObj->Get(info, 0, &vtProp, 0, 0);
		OutputVar = vtProp.date;
		VariantClear(&vtProp);
		pclsObj->Release();

		// Clean up
		pSvc->Release();
		pLoc->Release();
		pEnumerator->Release();
		CoUninitialize();
		return L"Done";
	}
}

