#pragma once
class VectorProcess
{
	vector<float> data_;

public:
	VectorProcess();
	VectorProcess(const vector<float> data);

	// геттер для вывода вектора
    const vector<float>& getData();

	// сеттер для вывода вектора
    void setData(vector<float>& value);

	// генрация вектора заданного размера, с заданным жиапазоном значений
	static vector<float> initialize(int n, float lo = -50.f, float hi = 50.f);

    // очистка вектора
    void clearVector();

    #pragma region Обработки по заданию

	// 1) Количество отрицательных элементов вектора
    int numberNegatives();

    // 2) Количество элементов вектора, не попадающих в интервал [a, b], введенный с клавиатуры
    int numberNotInRange(float a, float b);

    // 3) Сумма элементов вектора, расположенных перед первым минимальным элементом
    float sumToMin();

    // 4) Сумма элементов вектора, расположенных между первым минимальным и первым максимальным элементами
    float sumInDiaposone();

    // 5) Bыборка в другой вектор отрицательных элементов
    vector<float> findByNegative();
    
    // 6) Выбрка в другой вектор элементов, не попадающих в интервал [a, b]
    vector<float> findByDiaposone(float first, float second);

    // 7) Упорядочить элементы вектора по убыванию
    void sortItem();

    // 8) Упорядочить вектор по возрастанию модулей элементов
    void sortByModel();

    // 9) Упорядочить вектор по правилу – элементы, не попадающие в интервал значений [a, b] в конец вектора
    void sortByDiaposone(float first, float second);
};

