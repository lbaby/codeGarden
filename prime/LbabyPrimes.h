/**
* @file    LbabyPrimes.h
* @brief   Lbaby筛法查找素数
* @details  Lbaby筛：http://blog.csdn.net/lbaby/archive/2009/04/22/4101835.aspx
*                    http://bbs3.chinaunix.net/thread-1433650-1-1.html
* @author  Tu Yongce <yongce (at) 126 (dot) com>
* @date    2009-4-23  
* @version 0.1
*/

#ifndef LBABY_PRIME_H_INCLUDED
#define LBABY_PRIME_H_INCLUDED

#include <cmath>
#include <cstring>
#include <stdexcept>
#include <cassert>

template <typename IntType>
class LbabyPrimes
{
public:
    class Unready: public std::runtime_error
    {
    public:
        Unready(const char *errMsg): std::runtime_error(errMsg) { }
    };
    
public:
    LbabyPrimes()
    {
        m_tags = 0;
        m_maxNum = 0;
        m_primesCount = 0;
        m_done = false;
    }

    ~LbabyPrimes() 
    {
        delete m_tags;
    }

    // 查找[1, maxNum]范围内的素数
    void FindPrimes(IntType maxNum); 

    // 根据FindPrimes的查找结果，判断[1, maxNum]范围内的数num是否为素数
    bool IsPrime(IntType num) const
    {
        if (!m_done || num < 1 || num > m_maxNum)
            throw Unready("failed");
            
        if (num == 2 || num == 5)
            return true;
        if (num == 1)
            return false;
            
        IntType r = num % 10;
        if (r == 5 || r % 2 == 0)
            return false;
            
        return GetTag(num);
    }

    IntType GetPrimesCount() const
    {
        return m_primesCount;
    }

    template <typename OutIterator>
    OutIterator OutputPrimes(OutIterator outIt) const;

private:
    bool GetTag(IntType num) const
    {
        num -= 3; // 起始数为3，以BM_CYCLE为周期
        int bitIndex = sm_bitIndexMapping[num % BM_CYCLE];
        assert(bitIndex != -1);
        return (m_tags[num / BM_CYCLE] & (BitMap(1) << bitIndex)) != 0;
    }

    void ClearTag(IntType num)
    {
        num -= 3; // 起始数为3，以BM_CYCLE为周期
        int bitIndex = sm_bitIndexMapping[num % BM_CYCLE];
        assert(bitIndex != -1);
        m_tags[num / BM_CYCLE] &= ~(BitMap(1) << bitIndex);
    }
    
private:
    // 禁止拷贝
    LbabyPrimes(const LbabyPrimes &);
    LbabyPrimes& operator = (const LbabyPrimes &);

private:
    typedef unsigned int BitMap;
    static const int BM_CYCLE = sizeof(BitMap) * 20;
    static const int sm_bitIndexMapping[BM_CYCLE];

    BitMap *m_tags;    // 保存3, 7, 9, 11, 13, 17, 19, 21, ...的素数标记
    IntType m_maxNum;
    IntType m_primesCount;
    bool m_done;
};

template <typename IntType>
const int LbabyPrimes<IntType>::sm_bitIndexMapping[BM_CYCLE] = {
     0, -1, -1, -1,  1, -1,  2, -1,  3, -1,  4, -1, -1, -1,  5, -1,  6, -1,  7, -1, // 0~19  --> 0~7
     8, -1, -1, -1,  9, -1, 10, -1, 11, -1, 12, -1, -1, -1, 13, -1, 14, -1, 15, -1, // 20~39 --> 8~15
    16, -1, -1, -1, 17, -1, 18, -1, 19, -1, 20, -1, -1, -1, 21, -1, 22, -1, 23, -1, // 40~59 --> 16~23
    24, -1, -1, -1, 25, -1, 26, -1, 27, -1, 28, -1, -1, -1, 29, -1, 30, -1, 31, -1, // 60~79 --> 24~31
};

template <typename IntType>
void LbabyPrimes<IntType>::FindPrimes(IntType maxNum)
{
    IntType newNum = maxNum / BM_CYCLE + 1;
    if (!m_tags || (m_maxNum / BM_CYCLE + 1) < newNum) {
        delete m_tags;
        m_tags = new BitMap[static_cast<size_t>(newNum)];
    }
    m_maxNum = maxNum;
    std::memset(m_tags, 0xFF, static_cast<size_t>(newNum) * sizeof(BitMap));

    static const int mapping[10] = {0, 1, 1, 2, 2, 2, 2, 3, 3, 4};
    m_primesCount = m_maxNum / 10 * 4 + mapping[m_maxNum % 10];
    if (m_maxNum >= 2)
        ++m_primesCount;  // 2
    if (m_maxNum >= 5) 
        ++m_primesCount;  // 5
    --m_primesCount;      // 1

    IntType root = IntType(std::sqrt(double(m_maxNum)));
    for (IntType i = 3; i <= root; i += 2) {
        if (i % 10 == 5 || !GetTag(i))
            continue;

        IntType limit = m_maxNum / i;  // 防止无符号类型的溢出
        IntType k;
        for (k = i; k <= limit; k += 2) {
            if (k % 10 == 5)
                continue;

            IntType m = i * k;
            if (GetTag(m)) {
                ClearTag(m);
                --m_primesCount;
            }
        }
    }

    m_done = true;
}

template <typename IntType>
template <typename OutIterator>
OutIterator LbabyPrimes<IntType>::OutputPrimes(OutIterator outIt) const
{
    if (!m_done)
        return outIt;

    if (m_maxNum >= 2)
        *outIt++ = 2;
    if (m_maxNum >= 3)
        *outIt++ = 3;
    if (m_maxNum >= 5)
        *outIt++ = 5;

    for (IntType i = 7; i <= m_maxNum; i += 2) {
        if (i % 10 == 5 || !GetTag(i))
            continue;
        *outIt++ = i;
    }

    return outIt;
}

#endif //LBABY_PRIME_H_INCLUDED
