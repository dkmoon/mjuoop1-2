#pragma warning(disable: 4996)

#include <chrono>
#include <ctime>
#include <iostream>


class Animal {
public:
	virtual const char* getName() = 0;
	virtual bool isHungry(int currentHour) = 0;
	virtual void getFood() = 0;
};


class Dog : public Animal {
private:
	const char* name;

public:
	Dog(const char* name) : name(strdup(name)) {
		// 비어있는 구현
	}

	~Dog() {
		free((void *) name);
	}

	const char* getName() {
		return name;
	}

	bool isHungry(int currentHour) override {
		// 언제나 배가 고프다
		return true;
	}

	void getFood() override {
		// 짖어서 닝겐에게 요청한다.
		std::cout << name << ": 왈왈왈!" << std::endl;
	}
};


class Human : public Animal {
private:
	const char* name;

public:
	Human(const char* name) : name(strdup(name)) {
		// 비어있는 구현
	}

	~Human() {
		free((void *) name);
	}

	const char* getName() {
		return name;
	}

	bool isHungry(int currentHour) override {
		// 밥 때에만 배가 고프다.
		if (currentHour == 9 || currentHour == 12 || currentHour == 18) {
			return true;
		}
		else {
			return false;
		}
	}

	void getFood() override {
		// 배달을 시킨다.
		std::cout << name << ": 배달의 민족 주문~" << std::endl;
	}
};


// 아래 함수는 실제 구현되는 클래스에 대한 정보는 전혀 없이
// 오직 Animal 이라는 클래스의 인터페이스만으로 구현되었다.
void checkIfHungryAndGetFood(Animal* animal, int currentHour) {
	if (animal->isHungry(currentHour)) {
		animal->getFood();
	}
	else {
		std::cout << animal->getName() << ": " << currentHour << "시니까 아직 배가 고프지 않아" << std::endl;
	}
}


int main() {
	// 누렁이
	Animal* yellow = new Dog("Yellow");
	checkIfHungryAndGetFood(yellow, 9);
	checkIfHungryAndGetFood(yellow, 10);

	// 문대경
	Animal* dkmoon = new Human("DK");
	checkIfHungryAndGetFood(dkmoon, 9);
	checkIfHungryAndGetFood(dkmoon, 10);
}