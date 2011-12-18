/**
* @file    EratosthenesPrimes.h
* @brief   Eratosthenes筛法查找素数
* @author  Tu Yongce <yongce (at) 126 (dot) com>
* @date    2009-4-21
* @version 0.2
*/

#ifndef ERATOSTHENES_PRIMES_H_INCLUDED
#define ERATOSTHENES_PRIMES_H_INCLUDED

#include <cmath>
#include <cstring>
#include <stdexcept>
#include <cassert>

/**
* @brief 使用Eratosthenes筛法查找[1, M]范围内的所有素数
* @tparam IntType 模板类 EratosthenesPrimes 的模板参数，最好是int或unsigned int（以获得最好的运行效率）
*/

template <typename IntType>
class EratosthenesPrimes
{
public:
    /// 当调用IsPrime成员函数时，可能抛出的异常类
    class Unready: public std::runtime_error
    {
    public:
        /// 构造函数
        Unready(const char *errMsg): std::runtime_error(errMsg) { }
    };
    
public:
    /// 构造函数
    EratosthenesPrimes()
    {
        m_tags = 0;
        m_maxNum = 0;
        m_primesCount = 0;
        m_done = false;
    }

    /// 析构函数
    ~EratosthenesPrimes() 
    {
        delete m_tags;
    }

    /**
    * @brief 查找[1, <em>maxNum</em>]范围内的所有素数
    * @param maxNum 查找范围的上限值，必须不小于1
    * @return 如果maxNum小于1，那么查找操作失败，返回false；否则操作操作成功，返回true
    */
    bool FindPrimes(IntType maxNum); 

    /**
    * @brief 根据FindPrimes的查找结果，判断[1, <em>maxNum</em>]范围内的数，<em>num</em>是否为素数
    * @param num 需要判断素性的数
    * @return 如果<em>num</em>为素数，则返回true；否则返回false
    * @throw Unready 如果调用IsPrime之前没有调用FindPrimes或者<em>num</em>不在[1, <em>maxNum</em>]范围内，
    *                将抛出该类异常。
    */
    bool IsPrime(IntType num) const
    {
        if (!m_done || num < 1 || num > m_maxNum)
            throw Unready("failed");
        if (num == 2)
            return true;
        if (num % 2 == 0)
            return false;
        return GetTag(num);
    }

    /// 返回[1, <em>maxNum</em>]范围内的素数个数
    IntType GetPrimesCount() const
    {
        return m_primesCount;
    }

    /**
    * @brief 输出所有素数
    * @tparam OutIterator 输出迭代器类型
    * @param outIt 输出迭代器
    * @return 返回输出序列的最后一个元素的下一个位置
    */
    template <typename OutIterator>
    OutIterator OutputPrimes(OutIterator outIt) const;

private:
    bool GetTag(IntType num) const
    {
        assert(num % 2 == 1);
        return (m_tags[num / BM_CYCLE] & (BitMap(1) << (num % BM_CYCLE / 2))) != 0;
    }

    void ClearTag(IntType num)
    {
        assert(num % 2 == 1);
        m_tags[num / BM_CYCLE] &= ~(BitMap(1) << (num % BM_CYCLE / 2));
    }
    
private:
    // 禁止拷贝
    EratosthenesPrimes(const EratosthenesPrimes &);
    EratosthenesPrimes& operator = (const EratosthenesPrimes &);

private:
    typedef unsigned int BitMap;
    static const int BM_CYCLE = sizeof(BitMap) * 16;
    
    BitMap *m_tags;
    IntType m_maxNum;
    IntType m_primesCount;
    bool m_done;
};

template <typename IntType>
bool EratosthenesPrimes<IntType>::FindPrimes(IntType maxNum)
{
    if (maxNum < 1)
        return false;

    IntType newNum = maxNum / BM_CYCLE + 1;
    if (!m_tags || (m_maxNum / BM_CYCLE + 1) < newNum) {
        delete m_tags;
        m_tags = new BitMap[static_cast<size_t>(newNum)];
    }
    m_maxNum = maxNum;
    std::memset(m_tags, 0xFF, static_cast<size_t>(newNum) * sizeof(BitMap));
    m_primesCount = (m_maxNum - 1) / 2 + 1;  // 小心溢出

    ClearTag(1);
    //--m_primesCount;      // 1
    //++m_primesCount;      // 2

    IntType root = IntType(std::sqrt(double(m_maxNum)));
    for (IntType i = 3; i <= root; i += 2) {
        if (!GetTag(i)) {
            continue;
        }

        IntType i2 = 2 * i;
        IntType limit = m_maxNum - i2;  // 防止无符号类型的溢出
        IntType k;
        for (k = i * 3; k <= limit; k += i2) {
            if (GetTag(k)) {
                ClearTag(k);
                --m_primesCount;
            }
        }
        if (k <= m_maxNum && GetTag(k)) {
            ClearTag(k);
            --m_primesCount;
        }
    }

    m_done = true;
    return true;
}

template <typename IntType>
template <typename OutIterator>
OutIterator EratosthenesPrimes<IntType>::OutputPrimes(OutIterator outIt) const
{
    if (!m_done)
        return outIt;

    if (m_maxNum >= 2)
        *outIt++ = 2;

    for (IntType i = 3; i <= m_maxNum; i += 2) {
        if (GetTag(i)) {
            *outIt++ = i;
        }
    }
    return outIt;
}

#endif //ERATOSTHENES_PRIMES_H_INCLUDED
