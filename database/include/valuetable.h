/// @file 
/// @brief ���� �������� �������� ������� ��� ������ �� ���������� ����� ������� ��

#pragma once

///������ � ������ ������
namespace sqlite
{
/// @brief ������������ ������ � ����� ������� ���� ������
class ValueTable
{
	friend std::wostream& operator<<( std::wostream& stream, const sqlite::ValueTable& valueTable );
public:
	/// @brief �����������
	///
	/// @param[in] table �������� �������
	explicit ValueTable( const TablePtr& table  ); 
	/// @brief �����������
	///
	/// @param[in] fieldDeclarationTable �������� ����� �������
	explicit ValueTable( const FieldDeclarationTablePtr& fieldDeclarationTable  ); 
	/// @brief ����������
	///
	virtual ~ValueTable();
public:
	/// @brief ���������� �������� ����� �������
	///
	const FieldDeclarationTable& GetFieldDeclarationTable( void ) const;
private:
	/// @brief ���������� � ��������� ���������� �� ���� �� ��� ����� � ����
	///
	/// @param[in] name ��� ���������� ����
	/// @param[in] type ��� ����
	/// @return ����������� ����������
	ValuePtr GetAndCheckValue( const std::wstring& name, const sqlite::enums::FieldType type ) const;
protected:
	/// @brief ���������� ���������� �� ���� �� ��� �����
	///
	/// @param[in] name ��� ���������� ����
	/// @return ����������� ����������
	ValuePtr GetValue( const std::wstring& name ) const;
	/// @brief ���������� ���������� �� ���� �� ��� �����
	///
	/// @param[in] name ��� ���������� ����
	/// @return ����������� ����������
	ValuePtr operator[]( const std::wstring& name ) const;
public:
	/// @brief ���������� �������������� ���������� �� ���� �� ��� �����
	///
	/// @param[in] name ��� ���������� ����
	/// @return ����������� ��������� ��������
	types::ValueStringPtr GetStringValue( const std::wstring& name ) const;
	/// @brief ���������� �������������� ���������� �� ���� �� ��� �����
	///
	/// @param[in] name ��� ���������� ����
	/// @return ����������� ����� ����
	types::ValueIntegerPtr GetIntegerValue( const std::wstring& name ) const;
	/// @brief ���������� �������������� ���������� �� ���� �� ��� �����
	///
	/// @param[in] name ��� ���������� ����
	/// @return ����������� ����� � ��������� ������
	types::ValueFloatPtr GetFloatValue( const std::wstring& name ) const;
	/// @brief ���������� �������������� ���������� �� ���� �� ��� �����
	///
	/// @param[in] name ��� ���������� ����
	/// @return ����������� BLOB
	types::ValueBlobPtr GetBlobValue( const std::wstring& name ) const;
private:
	///< ������ �������� ���� �������
	ValueList valueList_;
	///< �������� ����� �������
	const FieldDeclarationTablePtr fieldDeclarationTable_;
};
/// @brief ��������� ����� ��� ����� �������
///
/// @param[in] stream �����
/// @param[in] valueTable �������� ����� �������
/// @return ���������� �����
std::wostream& operator<<( std::wostream& stream, const ValueTable& valueTable );
}
