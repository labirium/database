/// @file 
/// @brief ���� �������� ���������� ������� ��� ������������� ��������� ������ �� �������.

#pragma once

namespace sqlite
{

/// @brief ����� ������������ ��������� ������ �� �������.
///
class Stmt : boost::noncopyable
{
public:
	/// @brief �����������
	///
	/// @param[in] transaktion ����������� � ������ ������� �������������� ���������
	/// @param[in] fieldDeclarationTable �������� ����� �������
	/// @param[in] query ������ � ��
	Stmt( const Transaction& transaktion, const FieldDeclarationTablePtr& fieldDeclarationTable, const std::wstring& query );
	/// @brief ����������
	///
	~Stmt() throw();
public:
	/// @brief ������������ �������� �� �������
	///
	/// @return ���������� ������ ����.
	sqlite::ValueTablePtr Step( void );
	/// @brief ���������� �������� ����������� � ��
	///
    sqlite::DatabasePtr GetDataBase( void ) const;
private:
	/// @brief ���������� �������� ����������� � ��
	///
	sqlite3* GetSqlite( void ) const;
	/// @brief ���������� ������ �� ����������������� ������ � ��
	///
    sqlite3_stmt* Get( void ) const throw();
private:
	///< �������� ����������� � ��
	const DatabasePtr dataBase_;
	///< �������� ����� �������
    const FieldDeclarationTablePtr fieldDeclarationTable_;
	///< ������ � ��
    sqlite3_stmt* stmt_;
};
} 
