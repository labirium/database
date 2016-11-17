/// @file 
/// @brief ���� �������� ���������� ��������� ��� ������ �� ��������

#pragma once

///��������������� ������/�������
namespace tools
{
/// @brief ������� ���������� �������� ������ ������ ��� ����� ������� ���������.
///
class FirstString
{
public:
	/// @brief ����������
	/// 
	/// @param[in] data ������ ��� ��������
	explicit FirstString( const std::wstring& data = L" ");
	/// @brief ����������
	///
	~FirstString();
public:
	/// @brief �������
	///
	std::wstring operator()( void ) const throw();
private:
	///< ������ ��� ��������
	std::wstring data_;
	///< ���� ������ ��������
	mutable bool bFirst_;
};
}
