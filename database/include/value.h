/// @file 
/// @brief ���� �������� �������� ������� ��� ��������� � �������������� ������� � ������ ��

#pragma once

namespace sqlite
{
/// @brief ����� ������������ ������������� ����������/�������� ���� ������� ��
///
class Value 
{
protected:
	/// @brief �����������
	///
	/// @param[in] data ��������
	/// @param[in] field �������� ���� � ��
	Value( const boost::any& data, const sqlite::FieldPtr& field );
public:
	/// @brief ����������
	///
	virtual ~Value();
protected:
	/// @brief ���������� ����������
	///
	const boost::any& Get( void ) const throw();
	/// @brief ������ ����������
	///
	void Set( const boost::any& data ) throw();
public:
	/// @brief ������ nil ��� ����
	///
	void SetNull( void ) throw();
	/// @brief ��������� ��������� �� nil
	///
	bool IsNull( void ) const throw();
public:
	/// @brief ���������� �������� ���� 
	///
	const sqlite::FieldPtr& Field( void ) const throw();
private:
	///< ����������
	boost::any data_;
	///< �������� ���� � ��
	const sqlite::FieldPtr field_;
	///< ��������� �� nil
	bool isNull_;
};

/// @brief ���������� ������� ��� ��������� ������ � ����������/�������� ���� ������� ��
template< typename TypeObject>
class ValueType : public Value
{
public:
	/// @brief �����������
	///
	/// @param[in] field �������� ���� � ��
	explicit ValueType( const sqlite::FieldPtr& field ) : Value( TypeObject(), field )
	{
	}
	/// @brief �����������
	///
	/// @param[in] data ��������
	/// @param[in] field �������� ���� � ��
	ValueType( const TypeObject& data, const sqlite::FieldPtr& field )  :  Value( data, field )
	{
	}
	/// @brief ����������
	///
	~ValueType()
	{
	}
public:
	/// @brief ���������� ����������
	///
	TypeObject Get( void ) const
	{
		return boost::any_cast<TypeObject>( Value::Get() );
	}
	/// @brief ���������� ����������
	///
	TypeObject operator()() const
	{
		return Get( void );
	}
	/// @brief ������ �������� � ����������
	void Set( const TypeObject& data )
	{
		Value::Set( data );
	}
};
}
