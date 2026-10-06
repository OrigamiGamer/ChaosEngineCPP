#pragma once

#include <string>
#include <ostream>

namespace chaos::core {

    /**
     * @brief 基于 `std::string`，引擎定义的字符串类。
     */
    class String {
    private:
        std::string _str;

    public:

        static constexpr size_t npos = std::string::npos;   // 字符串最大长度


        // 构造

        /** @brief 默认构造函数。 */
        String() = default;

        /** @brief 从 C 字符串构造。 */
        String(const char* str);

        /** @brief 从 `std::string` 构造。 */
        String(const std::string& str);

        /** @brief 拷贝构造函数。 */
        String(const String& other) = default;

        /** @brief 移动构造函数。 */
        String(String&& other) noexcept = default;


        // 赋值

        /** @brief 拷贝赋值。 */
        String& operator=(const String& other);

        /** @brief 移动赋值。 */
        String& operator=(String&& other) noexcept;

        /** @brief 从 `std::string` 赋值。 */
        String& operator=(const std::string& str);

        /** @brief 从 C 字符串赋值。 */
        String& operator=(const char* str);


        // 容量

        /** @brief 返回字符串长度。 */
        size_t size() const;

        /** @brief 检查字符串是否为空。 */
        bool empty() const;


        // 访问

        /** @brief 按索引访问字符。 */
        char& operator[](size_t index);

        /** @brief 按索引访问字符（只读）。 */
        const char& operator[](size_t index) const;

        /** @brief 带边界检查的字符访问。 */
        char& at(size_t index);

        /** @brief 带边界检查的字符访问（只读）。 */
        const char& at(size_t index) const;

        /** @brief 返回 C 风格字符串指针。 */
        const char* c_str() const;

        /** @brief 返回底层数据指针。 */
        const char* data() const;


        // 修改

        /** @brief 追加字符串。 */
        String& append(const String& str);

        /** @brief 追加 C 字符串。 */
        String& append(const char* str);

        /** @brief 追加运算符。 */
        String& operator+=(const String& str);

        /** @brief 追加 C 字符串运算符。 */
        String& operator+=(const char* str);

        /** @brief 在指定位置插入子串。 */
        String& insert(size_t pos, const String& str);

        /** @brief 在指定位置删除子串。 */
        String& erase(size_t pos, size_t count = npos);

        /** @brief 替换子串。 */
        String& replace(size_t pos, size_t count, const String& str);

        /** @brief 返回子串。 */
        String substr(size_t pos = 0, size_t count = npos) const;

        /** @brief 清空字符串。 */
        void clear();


        // 搜索

        /** @brief 查找首次出现的位置。 */
        size_t find(const String& str, size_t pos = 0) const;

        /** @brief 查找 C 字符串首次出现的位置。 */
        size_t find(const char* str, size_t pos = 0) const;

        /** @brief 查找最后一次出现的位置。 */
        size_t rfind(const String& str, size_t pos = npos) const;

        /** @brief 检查字符串是否以指定前缀开头。 */
        bool starts_with(const String& str) const;

        /** @brief 检查字符串是否包含子串。 */
        bool contains(const String& str) const;


        // 比较

        /** @brief 与另一个 String 比较。 */
        int compare(const String& str) const;

    };


    // 运算符重载

    /** @brief 字符串拼接。 */
    String operator+(const String& lhs, const String& rhs);

    /** @brief 字符串相等比较。 */
    bool operator==(const String& lhs, const String& rhs);

    /** @brief 字符串不等比较。 */
    bool operator!=(const String& lhs, const String& rhs);

    /** @brief 字符串小于比较。 */
    bool operator<(const String& lhs, const String& rhs);

    /** @brief 流输出。 */
    std::ostream& operator<<(std::ostream& os, const String& str);

}
