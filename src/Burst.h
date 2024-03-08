/***************************************************************************************************
 * Copyright (C) 2021 Samsung Electronics Co. LTD
 *
 * This software is a property of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed,
 * transmitted, transcribed, stored in a retrieval system, or translated into any human
 * or computer language in any form by any means,electronic, mechanical, manual or otherwise,
 * or disclosed to third parties without the express written permission of Samsung Electronics.
 * (Use of the Software is restricted to non-commercial, personal or academic, research purpose
 * only)
 **************************************************************************************************/

#ifndef __BURST__HPP__
#define __BURST__HPP__

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "FP16.h"
#include "npy.h"

using namespace std;

namespace DRAMSim
{
union BurstType
{
    BurstType()
    {
        for (int i = 0; i < 64; i++)
        {
            fp16Data_[i] = convertF2H(0.0f);
        }
    }
    BurstType(float* x)
    {
        memcpy(u8Data_, x, 128);
    }

    BurstType(fp16* x)
    {
        memcpy(u8Data_, x, 128);
    }

    BurstType(float x0, float x1, float x2, float x3, float x4, float x5, float x6, float x7)
    {
        set(x0, x1, x2, x3, x4, x5, x6, x7);
    }

    BurstType(fp16 x0, fp16 x1, fp16 x2, fp16 x3, fp16 x4, fp16 x5, fp16 x6, fp16 x7, fp16 x8,
              fp16 x9, fp16 x10, fp16 x11, fp16 x12, fp16 x13, fp16 x14, fp16 x15)
    {
        set(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15);
    }

    BurstType(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4, uint32_t x5,
              uint32_t x6, uint32_t x7)
    {
        set(x0, x1, x2, x3, x4, x5, x6, x7);
    }

    BurstType(uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4, uint16_t x5,
              uint16_t x6, uint16_t x7, uint16_t x8, uint16_t x9, uint16_t x10, uint16_t x11,
              uint16_t x12, uint16_t x13, uint16_t x14, uint16_t x15)
    {
        set(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15);
    }

    BurstType(uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4, uint16_t x5,
              uint16_t x6, uint16_t x7, uint16_t x8, uint16_t x9, uint16_t x10, uint16_t x11,
              uint16_t x12, uint16_t x13, uint16_t x14, uint16_t x15, uint16_t x16, uint16_t x17, uint16_t x18, uint16_t x19, uint16_t x20, uint16_t x21,
              uint16_t x22, uint16_t x23, uint16_t x24, uint16_t x25, uint16_t x26, uint16_t x27,
              uint16_t x28, uint16_t x29, uint16_t x30, uint16_t x31, uint16_t x32, uint16_t x33, uint16_t x34, uint16_t x35, uint16_t x36, uint16_t x37,
              uint16_t x38, uint16_t x39, uint16_t x40, uint16_t x41, uint16_t x42, uint16_t x43,
              uint16_t x44, uint16_t x45, uint16_t x46, uint16_t x47, uint16_t x48, uint16_t x49, uint16_t x50, uint16_t x51, uint16_t x52, uint16_t x53,
              uint16_t x54, uint16_t x55, uint16_t x56, uint16_t x57, uint16_t x58, uint16_t x59,
              uint16_t x60, uint16_t x61, uint16_t x62, uint16_t x63)
    {
        set(x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21,
              x22, x23, x24, x25, x26, x27,
              x28, x29, x30, x31, x32, x33, x34, x35, x36, x37,
              x38, x39, x40, x41, x42, x43,
              x44,x45, x46, x47, x48, x49, x50, x51, x52, x53,
              x54, x55, x56, x57, x58, x59,
              x60, x61, x62, x63);
    }

    void set(float x)
    {
        set(x, x, x, x, x, x, x, x);
    }

    void set(fp16 x)
    {
        set(x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x);
    }

    void set(uint32_t x)
    {
        set(x, x, x, x, x, x, x, x);
    }

    void set(float x0, float x1, float x2, float x3, float x4, float x5, float x6, float x7)
    {
        fp32Data_[0] = x0;
        fp32Data_[1] = x1;
        fp32Data_[2] = x2;
        fp32Data_[3] = x3;
        fp32Data_[4] = x4;
        fp32Data_[5] = x5;
        fp32Data_[6] = x6;
        fp32Data_[7] = x7;
    }

    void set(uint32_t x0, uint32_t x1, uint32_t x2, uint32_t x3, uint32_t x4, uint32_t x5,
             uint32_t x6, uint32_t x7)
    {
        u32Data_[0] = x0;
        u32Data_[1] = x1;
        u32Data_[2] = x2;
        u32Data_[3] = x3;
        u32Data_[4] = x4;
        u32Data_[5] = x5;
        u32Data_[6] = x6;
        u32Data_[7] = x7;
    }

    void set(fp16 x0, fp16 x1, fp16 x2, fp16 x3, fp16 x4, fp16 x5, fp16 x6, fp16 x7, fp16 x8,
             fp16 x9, fp16 x10, fp16 x11, fp16 x12, fp16 x13, fp16 x14, fp16 x15)
    {
        fp16Data_[0] = x0;
        fp16Data_[1] = x1;
        fp16Data_[2] = x2;
        fp16Data_[3] = x3;
        fp16Data_[4] = x4;
        fp16Data_[5] = x5;
        fp16Data_[6] = x6;
        fp16Data_[7] = x7;
        fp16Data_[8] = x8;
        fp16Data_[9] = x9;
        fp16Data_[10] = x10;
        fp16Data_[11] = x11;
        fp16Data_[12] = x12;
        fp16Data_[13] = x13;
        fp16Data_[14] = x14;
        fp16Data_[15] = x15;
    }

    void set(uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4, uint16_t x5,
             uint16_t x6, uint16_t x7, uint16_t x8, uint16_t x9, uint16_t x10, uint16_t x11,
             uint16_t x12, uint16_t x13, uint16_t x14, uint16_t x15)
    {
        u16Data_[0] = x0;
        u16Data_[1] = x1;
        u16Data_[2] = x2;
        u16Data_[3] = x3;
        u16Data_[4] = x4;
        u16Data_[5] = x5;
        u16Data_[6] = x6;
        u16Data_[7] = x7;
        u16Data_[8] = x8;
        u16Data_[9] = x9;
        u16Data_[10] = x10;
        u16Data_[11] = x11;
        u16Data_[12] = x12;
        u16Data_[13] = x13;
        u16Data_[14] = x14;
        u16Data_[15] = x15;
    }

    void set(uint16_t x0, uint16_t x1, uint16_t x2, uint16_t x3, uint16_t x4, uint16_t x5,
              uint16_t x6, uint16_t x7, uint16_t x8, uint16_t x9, uint16_t x10, uint16_t x11,
              uint16_t x12, uint16_t x13, uint16_t x14, uint16_t x15, uint16_t x16, uint16_t x17, uint16_t x18, uint16_t x19, uint16_t x20, uint16_t x21,
              uint16_t x22, uint16_t x23, uint16_t x24, uint16_t x25, uint16_t x26, uint16_t x27,
              uint16_t x28, uint16_t x29, uint16_t x30, uint16_t x31, uint16_t x32, uint16_t x33, uint16_t x34, uint16_t x35, uint16_t x36, uint16_t x37,
              uint16_t x38, uint16_t x39, uint16_t x40, uint16_t x41, uint16_t x42, uint16_t x43,
              uint16_t x44, uint16_t x45, uint16_t x46, uint16_t x47, uint16_t x48, uint16_t x49, uint16_t x50, uint16_t x51, uint16_t x52, uint16_t x53,
              uint16_t x54, uint16_t x55, uint16_t x56, uint16_t x57, uint16_t x58, uint16_t x59,
              uint16_t x60, uint16_t x61, uint16_t x62, uint16_t x63)
    {
        u16Data_[0] = x0;
        u16Data_[1] = x1;
        u16Data_[2] = x2;
        u16Data_[3] = x3;
        u16Data_[4] = x4;
        u16Data_[5] = x5;
        u16Data_[6] = x6;
        u16Data_[7] = x7;
        u16Data_[8] = x8;
        u16Data_[9] = x9;
        u16Data_[10] = x10;
        u16Data_[11] = x11;
        u16Data_[12] = x12;
        u16Data_[13] = x13;
        u16Data_[14] = x14;
        u16Data_[15] = x15;
        u16Data_[16] = x16;
        u16Data_[17] = x17;
        u16Data_[18] = x18;
        u16Data_[19] = x19;
        u16Data_[20] = x20;
        u16Data_[21] = x21;
        u16Data_[22] = x22;
        u16Data_[23] = x23;
        u16Data_[24] = x24;
        u16Data_[25] = x25;
        u16Data_[26] = x26;
        u16Data_[27] = x27;
        u16Data_[28] = x28;
        u16Data_[29] = x29;
        u16Data_[30] = x30;
        u16Data_[31] = x31;
        u16Data_[32] = x32;
        u16Data_[33] = x33;
        u16Data_[34] = x34;
        u16Data_[35] = x35;
        u16Data_[36] = x36;
        u16Data_[37] = x37;
        u16Data_[38] = x38;
        u16Data_[39] = x39;
        u16Data_[40] = x40;
        u16Data_[41] = x41;
        u16Data_[42] = x42;
        u16Data_[43] = x43;
        u16Data_[44] = x44;
        u16Data_[45] = x45;
        u16Data_[46] = x46;
        u16Data_[47] = x47;
        u16Data_[48] = x48;
        u16Data_[49] = x49;
        u16Data_[50] = x50;
        u16Data_[51] = x51;
        u16Data_[52] = x52;
        u16Data_[53] = x53;
        u16Data_[54] = x54;
        u16Data_[55] = x55;
        u16Data_[56] = x56;
        u16Data_[57] = x57;
        u16Data_[58] = x58;
        u16Data_[59] = x59;
        u16Data_[60] = x60;
        u16Data_[61] = x61;
        u16Data_[62] = x62;
        u16Data_[63] = x63;
    }
    
    void set(BurstType& b)
    {
        memcpy(u8Data_, b.u8Data_, 128);
    }

    void setRandom()
    {
        std::random_device rd;   // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<float> dis(-10.0, 10.0);
        for (int i = 0; i < 16; i++)
        {
            fp16Data_[i] = (fp16)dis(gen);
        }
    }

    string binToStr() const
    {
        stringstream ss;
        ss << "[";
        for (int i = 0; i < 16; i++)
        {
            ss << bitset<16>(u16Data_[i]);
        }
        ss << "]";
        return ss.str();
    }

    string hexToStr() const
    {
        stringstream ss;
        for (int i = 0; i < 16; i++)
        {
            ss << setfill('0') << setw(4) << hex << u16Data_[i];
        }
        return ss.str();
    }

    string hexToStrU8() const
    {
        stringstream ss;
        for (int i = 0; i < 32; i++)
        {
            ss << setfill('0') << setw(2) << hex << (int)u8Data_[i];
        }
        return ss.str();
    }

    string hexToStr2() const
    {
        stringstream ss;
        for (int i = 15; i >= 0; i--)
        {
            ss << setfill('0') << setw(4) << hex << u16Data_[i];
        }
        return ss.str();
    }

    string hexToStrReverse(int start, int end) const
    {
        stringstream ss;
        for (int i = start; i <= end; i++)
        {
            ss << setfill('0') << setw(4) << hex << u16Data_[i];
        }
        return ss.str();
    }

    string hexToStrReverseU8(int start, int end) const
    {
        stringstream ss;
        for (int i = start; i <= end; i++)
        {
            ss << setfill('0') << setw(2) << hex << (int)u8Data_[i];
        }
        return ss.str();
    }

    string fp32ToStr() const
    {
        stringstream ss;
        ss << "[ ";
        for (int i = 0; i < 8; i++)
        {
            ss << fp32Data_[i] << " ";
        }
        ss << "]";
        return ss.str();
    }

    string fp16ToStr() const
    {
        stringstream ss;
        ss << "[ ";
        for (int i = 0; i < 16; i++)
        {
            ss << convertH2F(fp16Data_[i]) << " ";
        }
        ss << "]";
        return ss.str();
    }

    bool fp16Similar(const BurstType& rhs, float epsilon)
    {
        for (int i = 0; i < 16; i++)
        {
            if ((convertH2F(fp16Data_[i]) - convertH2F(rhs.fp16Data_[i])) /
                    convertH2F(fp16Data_[i]) >
                epsilon)
            {
                return false;
            }
        }
        return true;
    }

    fp16 fp16ReduceSum()
    {
        fp16 sum(0.0f);
        for (int i = 0; i < 64; i++)
        {
            sum += fp16Data_[i];
        }
        return sum;
    }

    fp16 fp16AdderTree()
    {
        fp16 sum[16];
        int numData = 16;

        for (int i = 0; i < numData; i++)
        {
            sum[i] = fp16Data_[i];
        }
        for (int i = 0; i < 4; i++)
        {
            numData = numData / 2;
            for (int j = 0; j < numData; j++)
            {
                sum[j] = sum[j * 2] + sum[j * 2 + 1];
            }
        }

        return sum[0];
    }

    float fp32ReduceSum()
    {
        float sum = 0.0;
        for (int i = 0; i < 8; i++)
        {
            sum += fp32Data_[i];
        }
        return sum;
    }

    bool operator==(const BurstType& rhs) const
    {
        return !(memcmp(this, &rhs, 128));
    }

    bool operator!=(const BurstType& rhs) const
    {
        return (memcmp(this, &rhs, 128));
    }

    BurstType operator+(const BurstType& rhs) const
    {
        BurstType ret;
        for (int i = 0; i < 64; i++)
        {
            ret.fp16Data_[i] = fp16Data_[i] + rhs.fp16Data_[i];
        }
        return ret;
    }
    BurstType operator*(const BurstType& rhs) const
    {
        BurstType ret;
        for (int i = 0; i < 64; i++)
        {
            ret.fp16Data_[i] = fp16Data_[i] * rhs.fp16Data_[i];
        }
        return ret;
    }

    fp16 fp16Data_[64];
    uint8_t u8Data_[128];
    float fp32Data_[32];
    uint32_t u32Data_[32];
    uint16_t u16Data_[64];
};

struct NumpyBurstType
{
    vector<unsigned long> shape;
    vector<float> data;
    vector<uint16_t> u16Data;
    vector<unsigned long> bShape;
    vector<BurstType> bData;
    enum precision
    {
        FP32,
        FP16
    };

    BurstType& getBurst(int x, int y)
    {
        return bData[y * bShape[1] + x];
    }
    BurstType& getBurst(int x)
    {
        return bData[x];
    }

    void loadTobShape(double divisor)
    {
        for (int i = 0; i < shape.size(); i++)
        {
            if (i == shape.size() - 1)
                bShape.push_back(ceil(shape[i] / divisor));
            else
                bShape.push_back(shape[i]);
        }
    }

    void loadFp32(string filename)
    {
        npy::LoadArrayFromNumpy(filename, shape, data);
        loadTobShape((double)8);
        for (int i = 0; i < data.size(); i += 8)
        {
            BurstType burst(data[i], data[i + 1], data[i + 2], data[i + 3], data[i + 4],
                            data[i + 5], data[i + 6], data[i + 7]);
            bData.push_back(burst);
        }
    }

    void loadFp16(string filename)
    {
        npy::LoadArrayFromNumpy(filename, shape, u16Data);
        loadTobShape((double)64);
        for (int i = 0; i < u16Data.size(); i += 64)
        {
            BurstType burst((u16Data[i]), (u16Data[i + 1]), (u16Data[i + 2]), (u16Data[i + 3]),
                            (u16Data[i + 4]), (u16Data[i + 5]), (u16Data[i + 6]), (u16Data[i + 7]),
                            (u16Data[i + 8]), (u16Data[i + 9]), (u16Data[i + 10]),
                            (u16Data[i + 11]), (u16Data[i + 12]), (u16Data[i + 13]),
                            (u16Data[i + 14]), (u16Data[i + 15]), (u16Data[i + 16]), (u16Data[i + 17]), (u16Data[i + 18]), (u16Data[i + 19]),
                            (u16Data[i + 20]), (u16Data[i + 21]), (u16Data[i + 22]), (u16Data[i + 23]),
                            (u16Data[i + 24]), (u16Data[i + 25]), (u16Data[i + 26]),
                            (u16Data[i + 27]), (u16Data[i + 28]), (u16Data[i + 29]),
                            (u16Data[i + 30]), (u16Data[i + 31]), (u16Data[i + 32]), (u16Data[i + 33]), (u16Data[i + 34]), (u16Data[i + 35]),
                            (u16Data[i + 36]), (u16Data[i + 37]), (u16Data[i + 38]), (u16Data[i + 39]),
                            (u16Data[i + 40]), (u16Data[i + 41]), (u16Data[i + 42]),
                            (u16Data[i + 43]), (u16Data[i + 44]), (u16Data[i + 45]),
                            (u16Data[i + 46]), (u16Data[i + 47]), (u16Data[i + 48]), (u16Data[i + 49]), (u16Data[i + 50]), (u16Data[i + 51]),
                            (u16Data[i + 52]), (u16Data[i + 53]), (u16Data[i + 54]), (u16Data[i + 55]),
                            (u16Data[i + 56]), (u16Data[i + 57]), (u16Data[i + 58]),
                            (u16Data[i + 59]), (u16Data[i + 60]), (u16Data[i + 61]),
                            (u16Data[i + 62]), (u16Data[i + 63]));
            bData.push_back(burst);
        }
    }

    void loadFp16FromFp32(string filename)
    {
        npy::LoadArrayFromNumpy(filename, shape, data);
        loadTobShape((double)16);
        for (int i = 0; i < data.size(); i += 16)
        {
            fp16 dataF2H[16];
            for (int j = 0; j < 16; j++)
            {
                dataF2H[j] = convertF2H(data[i + j]);
            }
            BurstType burst(dataF2H[0], dataF2H[1], dataF2H[2], dataF2H[3], dataF2H[4], dataF2H[5],
                            dataF2H[6], dataF2H[7], dataF2H[8], dataF2H[9], dataF2H[10],
                            dataF2H[11], dataF2H[12], dataF2H[13], dataF2H[14], dataF2H[15]);
            bData.push_back(burst);
        }
    }

    void dumpFp16(string filename)
    {
        ofstream file(filename.c_str());
        if (file.is_open())
        {
            for (int i = 0; i < bData.size(); i++)
            {
                for (int j = 0; j < 16; j++)
                {
                    file << bData[i].u16Data_[j] << " ";
                }
            }
        }
        file.close();
    }

    void dumpInt8(string filename)
    {
        ofstream file(filename.c_str());
        if (file.is_open())
        {
            for (int i = 0; i < bData.size(); i++)
            {
                for (int j = 0; j < 32; j++)
                {
                    file << bData[i].u8Data_[j];
                }
            }
        }
        file.close();
    }

    void copyBurst(BurstType* b, unsigned long size)
    {
        bShape.push_back(size);

        for (int i = 0; i < size; i++)
        {
            BurstType burst;
            burst.set(b[i]);
            bData.push_back(burst);
        }
    }

    unsigned long getTotalDim()
    {
        unsigned long dim = 1;
        for (int i = 0; i < bShape.size(); i++)
        {
            dim *= bShape[i];
        }
        return dim;
    }
};

}  // namespace DRAMSim
#endif
