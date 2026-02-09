#// Файл: Task4/Object.h
#// Действие: объявляем объект предметной области для Task4
#pragma once
#include "pch.h"

// ������� ����� ��� ����������� ������ 
// ���� ����������� ������� 
class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	// ��� ������� ������ ����� ������� ���� ��������� �������������
	virtual string toString() const = 0;  // �������� const

	// ������� �������� - ��������� ��������
	// virtual bool equals(Object &other) = 0;
};