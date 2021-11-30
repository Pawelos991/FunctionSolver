#include "Functions.h"

void LoadFromFile(std::vector<SquareFunc>& Funcs)
{
    std::ifstream file;
    file.open("Functions.txt");
    if (file.good() == false)
    {
        file.close();
        return;
    }
    float a, b, c;
    while (true)
    {
        if (file.good());
        else
            break;
        file >> a;
        file >> b;
        file >> c;
        Funcs.push_back(SquareFunc(a, b, c));
    }
    file.close();
}

void SaveResultsToFile(bool cpp, std::vector<SquareFunc>& Funcs)
{
    std::ofstream file;
    if(cpp)
        file.open("Functions_Result_CPP.txt");
    else
        file.open("Functions_Result_ASM.txt");
    int counter = Funcs.size();
    for (int i = 0; i < counter; i++)
    {
        SquareFunc func = Funcs[i];
        file << "Funkcja ";
        file << func.a;
        file << "x^2 + ";
        file << func.b;
        file << "x + ";
        file << func.c;
        if (func.isSquare)
        {
            file << " jest funkcja kwadratowa. Funkcja ma ksztalt ";
            if (func.isU)
            {
                file << "litery U. Funkcja maleje w przedziale (inf; ";
                file << func.p;
                file << "> i rosnie w przedziale <";
                file << func.p;
                file << "; inf). Najmniejsza wartosc funkcji to ";
                file << func.q;
            }
            else
            {
                file << "odwroconej litery U. Funkcja rosnie w przedziale (inf; ";
                file << func.p;
                file << "> i maleje w przedziale <";
                file << func.p;
                file << "; inf). Najwieksza wartosc funkcji to ";
                file << func.q;
            }
            file << ". Delta jest ";
            if (func.delta > 0)
            {
                file << "dodatnia, wiec funkcja ma 2 miejsca zerowe: x1= ";
                file << func.x1;
                file << " oraz x2= ";
                file << func.x2;
            }
            else if (func.delta == 0)
            {
                file << "rowna 0, wiec funkcja ma 1 miejsce zerowe: x= ";
                file << func.x1;
            }
            else
            {
                file << "ujemna, wiec funkcja nie ma miejsca zerowego";
            }

        }    
        else
        {
            file << " nie jest funkcja kwadratowa. Funkcja ";
            if (func.b == 0)
                file << "jest stala i nie ma miejsca zerowego.";
            else if (func.b > 0)
            {
                file << "jest rosnaca w calym przedziale i ma miejsce zerowe x=";
                file << func.x1;
            }
        }
        file << " .";
        file << std::endl;
    }
    file.close();
}