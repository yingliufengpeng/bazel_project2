//
// Created by peng on 31/8/2025.
//

#include "third_party/gdal/impl/AA.h"

#include <iostream>
#include "gdal_priv.h"
#include "cpl_conv.h" // for CPLMalloc()

int _show_inner(const char* filename) {
    // 注册所有驱动
    GDALAllRegister();

 // 替换为你的文件路径
    GDALDataset* poDataset = (GDALDataset*) GDALOpen(filename, GA_ReadOnly);

    if (poDataset == nullptr) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return 1;
    }

    // 获取栅格大小
    int nRasterXSize = poDataset->GetRasterXSize();
    int nRasterYSize = poDataset->GetRasterYSize();
    int nBands = poDataset->GetRasterCount();

    std::cout << "栅格尺寸: " << nRasterXSize << " x " << nRasterYSize << std::endl;
    std::cout << "波段数量: " << nBands << std::endl;

    // 读取第一个波段
    GDALRasterBand* poBand = poDataset->GetRasterBand(1);
    if (poBand == nullptr) {
        std::cerr << "无法获取波段 1" << std::endl;
        GDALClose(poDataset);
        return 1;
    }

    // 读取全部像素到缓冲区
    float* pafScanline = (float*) CPLMalloc(sizeof(float) * nRasterXSize * nRasterYSize);
    if (poBand->RasterIO(GF_Read, 0, 0, nRasterXSize, nRasterYSize,
                         pafScanline, nRasterXSize, nRasterYSize, GDT_Float32,
                         0, 0) != CE_None) {
        std::cerr << "读取数据失败" << std::endl;
        CPLFree(pafScanline);
        GDALClose(poDataset);
        return 1;
    }

    // 打印前 10 个像素值
    std::cout << "前 10 个像素值: ";
    for (int i = 0; i < 10 && i < nRasterXSize * nRasterYSize; ++i) {
        std::cout << pafScanline[i] << " ";
    }
    std::cout << std::endl;

    CPLFree(pafScanline);
    GDALClose(poDataset);
    return 0;
}



int AA::show_inner(const char* filename) {
    return _show_inner(filename);
}