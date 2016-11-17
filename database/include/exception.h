/// @file 
/// @brief ���� �������� ���������� ������� ��� ������������ ����������.

#pragma once

namespace sqlite
{
/// @brief ���������� ��������� ������� sqlite
///
class Exception : public std::runtime_error
{
public:
    /// @brief �����������
	///
	/// @param[in] message ��������� �� ������
    explicit Exception(const std::string& message );
	/// @brief ����������
	///
	virtual ~Exception();
};
} 

