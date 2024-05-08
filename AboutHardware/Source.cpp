/* STL libraries */
#include <iostream>
#include <string>
#include <intrin.h>
#include <array>
#include <vector>

/* Thrid party libraries */
#include <dxgi.h> /* https://en.wikipedia.org/wiki/DirectX_Graphics_Infrastructure */

/* Include library for DXGI */
#pragma comment(lib, "dxgi.lib")

/* Return description of your GPU */

WCHAR* getGPUDesc() {
    IDXGIFactory1* pFactory;

    /* Create factory and put it in pFactory pointer */
    CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&pFactory));

    IDXGIAdapter1* Adapter;

    /* Take a first GPU and write information about it */
    pFactory->EnumAdapters1(0, &Adapter);

    /* Get descritpion about GPU */
    DXGI_ADAPTER_DESC1 desc;
    Adapter->GetDesc1(&desc);

    return desc.Description;
}

/* Return name of brand your processor */

std::string getCPUBrand() {
    int nExIds;

    std::vector<std::array<int, 4>> data;
    std::array<int, 4> cpui;

    /* Put CPU information in cpui */
    __cpuid(cpui.data(), 0x80000000);

    /* Put in nExIds EAX code */
    nExIds = cpui[0];

    char brand[0x40];

    /* Fill array brand with zeros */
    memset(brand, 0, sizeof(brand));

    for (int i = 0x80000000; i <= nExIds; i++) {
        __cpuidex(cpui.data(), i, 0);
        data.push_back(cpui);
    }

    if (nExIds >= 0x80000004) {
        memcpy(brand, data[2].data(), sizeof(cpui));
        memcpy(brand + 16, data[3].data(), sizeof(cpui));
        memcpy(brand + 32, data[4].data(), sizeof(cpui));
    }

    return brand;
}

/*======================== Main ===========================*/

int main() {
    std::cout << getCPUBrand() << std::endl;
    wprintf(L"%s\n", getGPUDesc());
    return 0;
}