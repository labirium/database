/// @file 
/// @brief ���� �������� ���������� ������� ��� ������������� �������� ��� �������� ���� ������.

#pragma once

namespace sqlite
{
/// @brief �������� �������� ��� �������� � ��
///
class Table
{
public:
	/// @brief �����������
	///
	/// @param[in] name ��� �������
	/// @param[in] fieldDeclarationTable �������� ����� �������
	Table( const std::wstring& name, const sqlite::FieldDeclarationTable& fieldDeclarationTable  );
	/// @brief ����������
	///
	virtual ~Table();
public:
	/// @brief �������� ������� �� �������� �����
	///
	/// @param[in] transaktion �������� ����������
	void Create( const Transaction& transaktion ) const;
	/// @brief �������� �������
	///
	/// @param[in] transaktion �������� ����������
	void Drop( const Transaction& transaktion ) const;
	/// @brief ������������ ������� ����� ������
	///
	/// @param[in] transaktion �������� ����������
	/// @param[in] valueTable �������� ����������
	void Insert( const sqlite::Transaction& transaktion, const sqlite::ValueTable& valueTable ) const;
	/// @brief ������������ �������� ������
	///
	/// @param[in] transaktion �������� ����������
	/// @param[in] valueTable �������� ����������
	void Delete(const sqlite::Transaction& transaktion, const sqlite::ValueTable& valueTable) const;
	/// @brief ���������� ������ ��� ������� �� �������
	///
	Query GetQueryWhereRecordSet( void ) const;
public:
	/// @brief ���������� ��� �������
	///
	const std::wstring& GetName( void ) const; 
	///@brief ��������� �������� �����
	///
	const FieldDeclarationTable& GetFieldDeclarationTable( void ) const;
	///@brief ��������� ��������� �� �������� ����� �������
	///
	const FieldDeclarationTablePtr GetFieldDeclarationTablePtr( void ) const;
private:
	///< �������� ����� �������
	const sqlite::FieldDeclarationTablePtr fieldDeclarationTable_;	
	///< ��� �������
	const std::wstring name_;
};
}

