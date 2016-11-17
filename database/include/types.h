/// @file 
/// @brief ���� �������� �������� ����� ������ database

#pragma once

namespace sqlite
{

class Database;
/// ��������� �� ����������� � ��
typedef std::shared_ptr<Database> DatabasePtr;

class TransactionImp;
/// ��������� �� ���������� ����������
typedef std::shared_ptr<TransactionImp> TransactionImpPtr;

class Field;
/// ��������� �� ����
typedef std::shared_ptr<Field> FieldPtr;

class FieldDeclarationTable;
/// ��������� �� �������� ����� �������
typedef std::shared_ptr<FieldDeclarationTable> FieldDeclarationTablePtr;

/// C����� �������� ����
typedef std::vector<const FieldPtr> FieldList;
/// ������ �����
typedef std::vector<std::wstring> StringList;

class Value;
/// ��������� �� ����������
typedef std::shared_ptr<Value> ValuePtr;

class ValueTable;
/// ��������� �� ���������� �������
typedef std::shared_ptr<ValueTable> ValueTablePtr;
/// /// �������� ������ ����������
typedef std::vector<ValueTable> ValueTableList;
/// �������� ������ ���������� ������������ ����� ����
typedef std::map<std::wstring, ValuePtr > ValueList;

class Table;
/// ��������� �� ������� ���� ������
typedef std::shared_ptr<Table> TablePtr;

class Stmt;
/// ��������� �� ������� ������
typedef std::shared_ptr<Stmt> StmtPtr;

template< typename TypeObject> class ValueType;

///���� ������ ���� ������
namespace types
{
///�������� ������ ��
typedef std::wstring				SQLITE_TYPE_STRING;
///�������� �������� ����� ��
typedef sqlite_int64				SQLITE_TYPE_INTEGER;
///�������� ����� � ��������� ������ ��
typedef double						SQLITE_TYPE_FLOAT;
///�������� BLOB ��
typedef std::vector<unsigned char>	SQLITE_TYPE_BLOB;

/// ��������� �� ������ ��
typedef std::shared_ptr<ValueType<SQLITE_TYPE_STRING>> ValueStringPtr;
/// ��������� �� ����� ����� ��
typedef std::shared_ptr<ValueType<SQLITE_TYPE_INTEGER>> ValueIntegerPtr;
/// ��������� �� ����� � ��������� ������ ��
typedef std::shared_ptr<ValueType<SQLITE_TYPE_FLOAT>> ValueFloatPtr;
/// ��������� �� BLOB ��
typedef std::shared_ptr<ValueType<SQLITE_TYPE_BLOB>> ValueBlobPtr;
}

}
