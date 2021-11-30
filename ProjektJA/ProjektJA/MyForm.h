#pragma once
#include <thread>

#include "Functions.h"

//typedef HRESULT(CALLBACK* LPFNDLLFUNC2)(int,int);

class Mutex {
	CRITICAL_SECTION cs;
public:
	Mutex() {
		InitializeCriticalSection(&this->cs);
	}
	~Mutex() {
		DeleteCriticalSection(&this->cs);
	}
	void lock() {
		EnterCriticalSection(&this->cs);
	}
	void unlock() {
		LeaveCriticalSection(&this->cs);
	}
};
Mutex mut;

HINSTANCE hDLLASM;
HINSTANCE hDLLCPP;
LPFNDLLFUNC count_deltaroot;
LPFNDLLFUNC2 count_p;
LPFNDLLFUNC2 count_q;
LPFNDLLFUNC3 count_delta;
LPFNDLLFUNC3 count_x1;
LPFNDLLFUNC3 count_x2;

std::vector<SquareFunc>Funcs;
int size = 0;

int NumberOfThreads;
bool Calculated;

void SolveFunc(SquareFunc& func)
{
	func.Check_if_Square_and_U();
	func.delta = (double)count_delta(func.a, func.b, func.c);
	func.p = (double)count_p(func.a, func.b);
	func.q = (double)count_q(func.a, func.delta);
	if (func.delta >= 0)
	{
		func.deltaroot = count_deltaroot(func.delta);
		func.x1 = (double)count_x1(func.a, func.b, func.deltaroot);
		func.x2 = (double)count_x2(func.a, func.b, func.deltaroot);
	}
}

void SolveFunctionsThread(std::vector<SquareFunc>& Funcs, int& iterator) {
	mut.lock();
	while (iterator + 100 < size)
	{
		int it = iterator;
		iterator += 100;
		mut.unlock();
		for (int i = it; i < it + 100; i++)
		{
			SolveFunc(Funcs[i]);
		}
		mut.lock();
	}
	while (iterator < size)
	{
		int it = iterator;
		int temp = size - iterator;
		iterator += temp;
		mut.unlock();
		for (int i = it; i < it + temp; i++)
		{
			SolveFunc(Funcs[i]);
		}
		mut.lock();
	}
	mut.unlock();
}

namespace ProjektJA {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Podsumowanie informacji o MyForm
	/// </summary>
	/// 
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			NumberOfThreads = std::thread::hardware_concurrency();
			this->trackBar1->Value = NumberOfThreads;
			this->threadsAmount->Text = NumberOfThreads.ToString();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::Label^ threadsAmount;


	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::CheckBox^ checkASM;

	private: System::Windows::Forms::CheckBox^ checkCPP;



	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ TimeValue;
	private: System::Windows::Forms::Button^ Load;
	private: System::Windows::Forms::Button^ Save;
	private: System::Windows::Forms::Label^ Loaded;
	private: System::Windows::Forms::Label^ Saved;





	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->threadsAmount = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->checkASM = (gcnew System::Windows::Forms::CheckBox());
			this->checkCPP = (gcnew System::Windows::Forms::CheckBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TimeValue = (gcnew System::Windows::Forms::Label());
			this->Load = (gcnew System::Windows::Forms::Button());
			this->Save = (gcnew System::Windows::Forms::Button());
			this->Loaded = (gcnew System::Windows::Forms::Label());
			this->Saved = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(11, 115);
			this->trackBar1->Margin = System::Windows::Forms::Padding(2);
			this->trackBar1->Maximum = 64;
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(416, 45);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Value = 1;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MyForm::trackBar1_Scroll);
			// 
			// threadsAmount
			// 
			this->threadsAmount->AutoSize = true;
			this->threadsAmount->Location = System::Drawing::Point(98, 97);
			this->threadsAmount->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->threadsAmount->Name = L"threadsAmount";
			this->threadsAmount->Size = System::Drawing::Size(13, 13);
			this->threadsAmount->TabIndex = 2;
			this->threadsAmount->Text = L"1";
			this->threadsAmount->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(333, 87);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Start";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// checkASM
			// 
			this->checkASM->AutoSize = true;
			this->checkASM->Checked = true;
			this->checkASM->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkASM->Location = System::Drawing::Point(184, 87);
			this->checkASM->Name = L"checkASM";
			this->checkASM->Size = System::Drawing::Size(49, 17);
			this->checkASM->TabIndex = 6;
			this->checkASM->Text = L"ASM";
			this->checkASM->UseVisualStyleBackColor = true;
			this->checkASM->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// checkCPP
			// 
			this->checkCPP->AutoSize = true;
			this->checkCPP->Location = System::Drawing::Point(257, 87);
			this->checkCPP->Name = L"checkCPP";
			this->checkCPP->Size = System::Drawing::Size(47, 17);
			this->checkCPP->TabIndex = 7;
			this->checkCPP->Text = L"CPP";
			this->checkCPP->UseVisualStyleBackColor = true;
			this->checkCPP->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 97);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(81, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Liczba w¹tków:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(330, 26);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(87, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Czas wykonania:";
			// 
			// TimeValue
			// 
			this->TimeValue->AutoSize = true;
			this->TimeValue->Location = System::Drawing::Point(330, 51);
			this->TimeValue->Name = L"TimeValue";
			this->TimeValue->Size = System::Drawing::Size(25, 13);
			this->TimeValue->TabIndex = 10;
			this->TimeValue->Text = L"      ";
			// 
			// Load
			// 
			this->Load->Location = System::Drawing::Point(11, 16);
			this->Load->Name = L"Load";
			this->Load->Size = System::Drawing::Size(99, 23);
			this->Load->TabIndex = 11;
			this->Load->Text = L"Wczytaj funkcje";
			this->Load->UseVisualStyleBackColor = true;
			this->Load->Click += gcnew System::EventHandler(this, &MyForm::Load_Click);
			// 
			// Save
			// 
			this->Save->Location = System::Drawing::Point(12, 51);
			this->Save->Name = L"Save";
			this->Save->Size = System::Drawing::Size(99, 23);
			this->Save->TabIndex = 12;
			this->Save->Text = L"Zapisz wyniki";
			this->Save->UseVisualStyleBackColor = true;
			this->Save->Click += gcnew System::EventHandler(this, &MyForm::Save_Click);
			// 
			// Loaded
			// 
			this->Loaded->AutoSize = true;
			this->Loaded->Location = System::Drawing::Point(123, 23);
			this->Loaded->Name = L"Loaded";
			this->Loaded->Size = System::Drawing::Size(0, 13);
			this->Loaded->TabIndex = 13;
			// 
			// Saved
			// 
			this->Saved->AutoSize = true;
			this->Saved->Location = System::Drawing::Point(123, 56);
			this->Saved->Name = L"Saved";
			this->Saved->Size = System::Drawing::Size(0, 13);
			this->Saved->TabIndex = 14;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(429, 160);
			this->Controls->Add(this->Saved);
			this->Controls->Add(this->Loaded);
			this->Controls->Add(this->Save);
			this->Controls->Add(this->Load);
			this->Controls->Add(this->TimeValue);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->checkCPP);
			this->Controls->Add(this->checkASM);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->threadsAmount);
			this->Controls->Add(this->trackBar1);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"MyForm";
			this->Text = L"Function Analyzer";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) 
	{
		NumberOfThreads = this->trackBar1->Value;
		this->threadsAmount->Text = NumberOfThreads.ToString();
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: void PrepareCPP(std::vector<SquareFunc>& Funcs, int threads)
	{
			std::vector<std::thread> threadVector;
			int iterator = 0;

			LPCWSTR libcpp = L"DllCpp";
			hDLLCPP = LoadLibrary(libcpp);
			count_delta = (LPFNDLLFUNC3)GetProcAddress(hDLLCPP, "count_delta");
			count_p = (LPFNDLLFUNC2)GetProcAddress(hDLLCPP, "count_p");
			count_q = (LPFNDLLFUNC2)GetProcAddress(hDLLCPP, "count_q");
			count_deltaroot = (LPFNDLLFUNC)GetProcAddress(hDLLCPP, "count_deltaroot");
			count_x1 = (LPFNDLLFUNC3)GetProcAddress(hDLLCPP, "count_x1");
			count_x2 = (LPFNDLLFUNC3)GetProcAddress(hDLLCPP, "count_x2");

			for (int i = 0; i < threads; i++)
			{
				threadVector.push_back(std::thread(SolveFunctionsThread, std::ref(Funcs), std::ref(iterator)));
			}
			auto t1 = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < threads; i++)
			{
				threadVector[i].join();
			}
			auto t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> duration = t2 - t1;
			this->TimeValue->Text = duration.count().ToString() + " ms";
			Calculated = true;
	}

	private: void PrepareASM(std::vector<SquareFunc>& Funcs, int threads)
	{
		std::vector<std::thread> threadVector;
		int iterator = 0;

		LPCWSTR libasm = L"DllAsm";
		hDLLASM = LoadLibrary(libasm);
		count_delta = (LPFNDLLFUNC3)GetProcAddress(hDLLASM, "count_delta");
		count_p = (LPFNDLLFUNC2)GetProcAddress(hDLLASM, "count_p");
		count_q = (LPFNDLLFUNC2)GetProcAddress(hDLLASM, "count_q");
		count_deltaroot = (LPFNDLLFUNC)GetProcAddress(hDLLASM, "count_deltaroot");
		count_x1 = (LPFNDLLFUNC3)GetProcAddress(hDLLASM, "count_x1");
		count_x2 = (LPFNDLLFUNC3)GetProcAddress(hDLLASM, "count_x2");

		for (int i = 0; i < threads; i++)
		{
			threadVector.push_back(std::thread(SolveFunctionsThread, std::ref(Funcs), std::ref(iterator)));
		}
		auto t1 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < threads; i++)
		{
			threadVector[i].join();
		}
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> duration = t2 - t1;
		this->TimeValue->Text = duration.count().ToString() + " ms";
		Calculated = true;
	}

private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Loaded->Text = "";
	this->Saved->Text = ""; 
	if (checkCPP->Checked == true)
	{
		PrepareCPP(Funcs, NumberOfThreads);
	}
	else if (checkASM->Checked == true)
	{
		PrepareASM(Funcs, NumberOfThreads);
	}
	else
	{
		this->TimeValue->Text = "Wybierz biblioteke";
	}
}
private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	checkASM->Checked = false;
}
private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	checkCPP->Checked = false;
}
private: System::Void Load_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Saved->Text = "";
	Funcs.clear();
	LoadFromFile(Funcs);
	size = Funcs.size();
	Calculated = false;
	this->Loaded->Text = "Wczytano funkcje z pliku";
}
private: System::Void Save_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Loaded->Text = "";
	if (Funcs.size() != 0 && Calculated!=false)
	{
		if (checkASM->Checked == true)
			SaveResultsToFile(false, Funcs);
		else if (checkCPP->Checked == true)
			SaveResultsToFile(true, Funcs);
		this->Saved->Text = "Zapisano wyniki do pliku";
	}
	else if(Calculated==false)
		this->Saved->Text = "Funkcje nie zostaly rozwiazane";
	else
		this->Saved->Text = "Brak funkcji w pamiêci";
}
};
}
