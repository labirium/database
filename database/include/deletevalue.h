/// @file 
/// @brief ���� �������� ���������� ������� ��� ������� ����� � �������

#pragma once

namespace sqlite
{
/// @brief �������� ������ ��� �������� ������ � �������
///
class DeleteValue
{
public:
	/// @brief �����������
	///
	/// @param[in] table �������� �������
	explicit DeleteValue(const sqlite::TablePtr& table);
	/// @brief �����������
	///
	/// @param[in] table �������� �������
	explicit DeleteValue(const sqlite::Table& table);
	/// @brief ����������
	///
	~DeleteValue();
public:
	/// @brief ����������� ������ �� ���������� � �������
	/// 
	/// @param[in] data ������ �������
	void Add( const sqlite::ValueTable& data );
	/// @brief ������������ ������ ������ � �������
	///
	/// @param[in] transaction �������� ���������� � ������ ������� �������������� �������
	void Exec( const sqlite::Transaction& transaction ) const;
protected:
	/// @brief ��������� ������� ��� ������� � �������
	///
	std::wstring operator()( void ) const;
private:
	///< ������ �������� �� �������
	ValueTableList valueTableList_;
	///< ��� �������
	const std::wstring tableName_;
};
}
