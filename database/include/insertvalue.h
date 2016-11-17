/// @file 
/// @brief ���� �������� ���������� ������� ��� ������� ����� � �������

#pragma once

namespace sqlite
{
/// @brief �������� ������ ��� ������� ������ � �������
///
class InsertValue
{
public:
	/// @brief �����������
	///
	/// @param[in] table �������� �������
	explicit InsertValue( const sqlite::TablePtr& table );
	/// @brief �����������
	///
	/// @param[in] table �������� �������
	explicit InsertValue( const sqlite::Table& table );
	/// @brief ����������
	///
	~InsertValue();
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
