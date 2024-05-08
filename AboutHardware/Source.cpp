/* STL libraries */
#include <iostream>
#include <string>
#include <intrin.h>
#include <bitset>
#include <array>
#include <vector>
#include <bitset>

/* Thrid party libraries */
#include <dxgi.h> /* https://en.wikipedia.org/wiki/DirectX_Graphics_Infrastructure */

/* Include library for DXGI */
#pragma comment (lib, "dxgi.lib")

/* Return description of your GPU */

WCHAR* getGPU() {
    IDXGIFactory1* pFactory;
    HRESULT res = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&pFactory));

    IDXGIAdapter1* Adapter;

    pFactory->EnumAdapters1(0, &Adapter);

    DXGI_ADAPTER_DESC1 desk;
    Adapter->GetDesc1(&desk);

    return desk.Description;
}

/* Return name of brand your processor */

std::string getCPUBrand() {
    int nExIds;

    std::vector<std::array<int, 4>> data;
    std::array<int, 4> cpui;

    std::bitset<32> f_81_ECX;
    std::bitset<32> f_81_EDX;

    __cpuid(cpui.data(), 0x80000000);
    nExIds = cpui[0];

    char brand[0x40];
    memset(brand, 0, sizeof(brand));

    for (int i = 0x80000000; i <= nExIds; i++) {
        __cpuidex(cpui.data(), i, 0);
        data.push_back(cpui);
    }

    if (nExIds >= 0x80000001) {
        f_81_ECX = data[1][2];
        f_81_EDX = data[1][3];
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
    wprintf(L"%s\n", getGPU());
    return 0;
}
