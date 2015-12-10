#include <iostream>
#include <cmath>

#define MAX 3

using namespace std;

void ConvertToArray(int value, int* address) {
    address[0] = value / 100;
    address[1] = (value - address[0] * 100) / 10;
    address[2] = (value - address[0] * 100 - address[1] * 10);
    
    // return result;
}

class Resources {
    public: 
        static void ConvertToArray(int value, int* address, int& length) {
            length = 0;
            
            int* reverse = new int();
            reverse[length] = 0;
            
            while(value > 0) {
                reverse[length] = value % 10;
                value /= 10;
                length++;
            }
            
            for(int i = 0; i < length; i++) {
                address[i] = reverse[length - 1 - i];
            }
        }

};

class BigInt {
    private:
        void MultiplyByPowerOfTen (int power) {
            for(int i = 0; i < power; i++) {
                ArrayValue[NumberOfDigits + i] = 0;
            }
            
            NumberOfDigits += power;
        }
    
    public: 
        int* ArrayValue;
        int NumberOfDigits;
    
        BigInt () {
            InitializeBasic();
        }
    
        BigInt (int value) {
            NumberOfDigits = 0;
            ArrayValue = new int();
            Resources :: ConvertToArray (value, ArrayValue, NumberOfDigits);
        }
    
        BigInt (const BigInt &original) {
            NumberOfDigits = original.NumberOfDigits;
            ArrayValue = new int();
            
            for(int i = 0; i < NumberOfDigits; i++) {
                ArrayValue[i] = original.ArrayValue[i];
            }
        }
    
        ~BigInt () {
            delete[] ArrayValue;
        }
    
        void Print () {
            for (int i = 0; i < NumberOfDigits; i++) {
                std :: cout << ArrayValue[i];
            }
            std :: cout << '\n';
        }
    
        void ShiftRight (int amount = 1) {
            for(int i = NumberOfDigits - 1; i > -1; i--) {
                ArrayValue[i + amount] = ArrayValue[i];
            }
            
            for(int i = 0; i < amount; i++) {
                ArrayValue[i] = 0;
            }
            
            NumberOfDigits += amount;
        }
    
        void ShiftLeft (int amount = 1) {
            for (int i = 0; i < NumberOfDigits; i++) {
                ArrayValue[i - amount] = ArrayValue[i];
            }
            
            for(int i = 0; i < amount; i++) {
                ArrayValue[NumberOfDigits - 1 - i] = 0;
            }
            
            NumberOfDigits -= amount;
        }
    
        void print () {
            Print();
        }
    
        int Length () {
            return NumberOfDigits;
        }
    
        static void Multiply (BigInt* rs, BigInt* rd, BigInt *rt) {
            BigInt* operandOne;
            BigInt* operandTwo;
            
            if (rd -> NumberOfDigits > rt -> NumberOfDigits) {
                operandOne = new BigInt(*rd);
                operandTwo = new BigInt(*rt);
            } else {
                operandOne = new BigInt(*rt);
                operandTwo = new BigInt(*rd);
            }
            
            int sum = operandOne -> NumberOfDigits + operandTwo -> NumberOfDigits;
            
            // BigInt* rs = new BigInt();
            rs -> InitializeWithZeros(sum);
            
            BigInt* iterator = new BigInt();
            int valueToMultiply = 0;
            
            for (int i = 0; i < operandTwo -> Length(); i++) {
                delete iterator;
                iterator = new BigInt(*operandOne);
                
                valueToMultiply = operandTwo -> ArrayValue[operandTwo -> Length() - i - 1];
                MultiplyWithOneDigit(iterator, iterator, valueToMultiply);
                
                iterator -> MultiplyByPowerOfTen(i);
                Add(rs, iterator, rs);
            }
            
            int zeroCheckerIterator = 0;
            while(true) {
                if(rs -> ArrayValue[zeroCheckerIterator] == 0) {
                    rs -> ShiftLeft();
                    zeroCheckerIterator++;
                } else {
                    break;
                }
            }
        }
    
        static void MultiplyWithOneDigit (BigInt *rs, BigInt* rd, int rt) {
            
            BigInt* operandOne = new BigInt(*rd);
            operandOne -> ShiftRight();
            
            // BigInt* rs = new BigInt();
            rs -> InitializeWithZeros(operandOne -> Length());
            
            int carry = 0;
            int computedValue = 0;
            for (int i = operandOne -> Length() - 1; i > - 1; i--) {
                computedValue = operandOne -> ArrayValue[i] * rt + carry;
                
                
                if(computedValue >= 10) {
                    carry = computedValue / 10;
                    computedValue = computedValue % 10;
                } else {
                    carry = 0;
                }
                
                rs -> ArrayValue[i] = computedValue;
            }
            
            if(rs -> ArrayValue[0] == 0) {
                rs -> ShiftLeft();
            }
        }
    
        static void Add (BigInt* rs, BigInt* rd, BigInt* rt) {
            BigInt* operandOne;
            BigInt* operandTwo;
            
            if (rd -> NumberOfDigits > rt -> NumberOfDigits) {
                operandOne = new BigInt(*rd);
                operandTwo = new BigInt(*rt);
            } else {
                operandOne = new BigInt(*rt);
                operandTwo = new BigInt(*rd);
            }
            
            // Math Class
            int difference = abs(operandOne -> NumberOfDigits - operandTwo -> NumberOfDigits);
            
            operandOne -> ShiftRight();
            operandTwo -> ShiftRight(difference + 1);
            
            // BigInt* rs = new BigInt();
            rs -> InitializeWithZeros(operandOne -> Length());
            
            int carry = 0;
            int computedValue = 0;
            for (int i = operandOne -> Length() - 1; i > -1; i--) {
                computedValue = operandOne -> ArrayValue[i] + operandTwo -> ArrayValue[i] + carry;
                
                if(computedValue >= 10) {
                    carry = 1;
                    computedValue -= 10;
                } else {
                    carry = 0;
                }
                
                rs -> ArrayValue[i] = computedValue;
            }
            
            if(rs -> ArrayValue[0] == 0)
                rs -> ShiftLeft();
            
            // rs -> Print();
        }
    
        void InitializeWithZeros (int length) {
            NumberOfDigits = length;
            
            if(ArrayValue != NULL)
                delete[] ArrayValue;
            
            ArrayValue = new int();
            
            for(int i = 0; i < length; i++) {
                ArrayValue[i] = 0;
            }
        }
    
        void InitializeBasic () {
            NumberOfDigits = 0;
            if(ArrayValue != NULL)
                delete ArrayValue;
            
            ArrayValue = new int();
        }
    
};


int main(void ) {
    int input;
    cin >> input;
    BigInt* value = new BigInt(input);
    BigInt* value2 = new BigInt(245);
    BigInt* value3 = new BigInt();
    BigInt :: Multiply(value3, value, value2);
    value -> print();
    delete value;
    return 0;
}
