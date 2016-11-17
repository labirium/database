/// @file 
/// @brief ���� �������� ���������� ������� ��� ������������ �������� ����� �������.

#pragma once

namespace sqlite
{
/// ������������ ������������ ������� database
namespace enums
{
/// @brief ���� ����� sqlite
///
enum class FieldType : int
{
	/// SQLITE_INTEGER
	Integer = 1,
	/// SQLITE_FLOAT
	Float = 2,
	/// SQLITE_TEXT
	Text = 3,
	/// SQLITE_BLOB
	BLob = 4,
};
}
/// @brief ������������ ��������������� ���� � ������
///
class FieldType
{
public:
	/// @brief �����������
	///
	/// @param[in] type ��� ���� sqlite
	FieldType( const enums::FieldType type );
	/// @brief ����������
	///
	~FieldType();
public:
	/// @brief ���������� ������ ���� ����
	///
	const wchar_t* const ToString( void ) const;
	/// @brief ���������� ������ ���� ����
	///
	operator const wchar_t* () const;
private:
	///< ������ ��� ����
	const enums::FieldType type_;
};

/// @brief ������ �������� ���� � �������
///
class Field
{
public:
	/// @brief �����������
	///
	/// @param[in] name ��� ����
	/// @param[in] type ��� ����
	/// @param[in] primaryKey �������� ���� ������
	Field( const std::wstring& name, const enums::FieldType type, const bool primaryKey = false );
	/// @brief ����������
	///
	~Field();
public:
	/// @brief ���������� ������ ��� ���������� ���� � �������
	///
	std::wstring operator ()() const;
	/// @brief ��������� ��� ����
	///
	enums::FieldType GetFieldType( void ) const;
	/// @brief ���������� ��� ����
	///
	std::wstring GetName(void ) const;
	/// @brief ���������� ������� ����
	///
	bool GetPrimaryKey(void) const;
private:
	///< ��� ����
	const std::wstring name_;
	///< ��� ����
	const enums::FieldType type_;
	///< ������� ���� �������� �������� ������
	const bool primaryKey_;
};

/// @brief ������ �������� ����� ������������������ � �������
///
class FieldDeclarationTable
{
public:
	/// @brief �����������
	///
	FieldDeclarationTable( void );
	/// @brief ����������
	///
	~FieldDeclarationTable();
public:
	/// @brief ��������� ������ � �������
	///
	/// @param[in] field ������ � �������
	/// @return ���������� ������ �� ����
	FieldDeclarationTable& AddField( const sqlite::FieldPtr& field );
	/// @brief ��������� ������ � �������
	///
	/// @param[in] name ��� ����
	/// @param[in] type ��� ����
	/// @param[in] primaryKey �������� ���� ������
	/// @return ���������� ������ �� ����
	FieldDeclarationTable& AddField( const std::wstring& name, const sqlite::enums::FieldType type, const bool primaryKey = false );
public:
	/// @brief ���������� �������� ���� �� ��� �����
	///
	/// @param[in] name ��� ����
	const sqlite::FieldPtr operator()( const std::wstring& name ) const;
	/// @brief ���������� ������ ������������������ �����
	///
	const sqlite::FieldList& operator()( void ) const;
	/// @brief ���������� ������ ���� ������������������ � �������
	///
	StringList GetFieldNameList( void ) const;
private:
	///< ������ �����
	sqlite::FieldList fieldList_;
};

/// @brief ��������� ������ ������
///
/// @param[in] stream �����
/// @param[in] fieldType ������ �� ������
std::wostream& operator<<( std::wostream& stream, const FieldType& fieldType );
/// @brief ��������� ������ ������
///
/// @param[in] stream �����
/// @param[in] field ������ �� ������
std::wostream& operator<<( std::wostream& stream, const Field& field );
/// @brief ��������� ������ ������
///
/// @param[in] stream �����
/// @param[in] fieldList ������ �� ������
std::wostream& operator<<( std::wostream& stream, const sqlite::FieldList& fieldList );

/// @brief ������������ ������ �� ������ �����
///
/// @param[in] stringList ������ �����
std::wstring StrToStringList( const sqlite::StringList& stringList );
}
