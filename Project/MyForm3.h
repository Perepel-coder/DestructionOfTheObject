#include "Main.h"
#pragma once

namespace Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm3
	/// </summary>
	public ref class MyForm3 : public System::Windows::Forms::Form
	{
	public:
		MyForm3(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm3()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBox2;
	protected:
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBox4);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->textBox2);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Location = System::Drawing::Point(14, 167);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(280, 191);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Параметры броска";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(78, 128);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 22);
			this->textBox4->TabIndex = 6;
			this->textBox4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm3::textBox4_KeyPress_1);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(78, 85);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 22);
			this->textBox3->TabIndex = 5;
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm3::textBox3_KeyPress_1);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(78, 22);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 4;
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm3::textBox2_KeyPress_1);
			// 
			// label4
			// 
			this->label4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label4->Location = System::Drawing::Point(7, 127);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(64, 23);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Угол";
			// 
			// label3
			// 
			this->label3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label3->Location = System::Drawing::Point(7, 69);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(64, 38);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Сила \r\nброска";
			// 
			// label2
			// 
			this->label2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label2->Location = System::Drawing::Point(7, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 23);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Высота";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(205, 104);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 33);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Ввод";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm3::button1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox6);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->textBox5);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(14, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(280, 149);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Параметры фигуры";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(77, 115);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 22);
			this->textBox6->TabIndex = 5;
			this->textBox6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm3::textBox6_KeyPress_1);
			// 
			// label6
			// 
			this->label6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label6->Location = System::Drawing::Point(7, 114);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(64, 23);
			this->label6->TabIndex = 4;
			this->label6->Text = L"Высота";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(77, 71);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 22);
			this->textBox5->TabIndex = 3;
			this->textBox5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm3::textBox5_KeyPress_1);
			// 
			// label5
			// 
			this->label5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label5->Location = System::Drawing::Point(7, 70);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(64, 23);
			this->label5->TabIndex = 2;
			this->label5->Text = L"Ширина";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(77, 26);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 22);
			this->textBox1->TabIndex = 1;
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm3::textBox1_KeyPress_1);
			// 
			// label1
			// 
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Location = System::Drawing::Point(7, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(64, 23);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Длина";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->button4);
			this->groupBox3->Controls->Add(this->button3);
			this->groupBox3->Controls->Add(this->button2);
			this->groupBox3->Controls->Add(this->button1);
			this->groupBox3->Location = System::Drawing::Point(14, 364);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(280, 144);
			this->groupBox3->TabIndex = 4;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Материал";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(7, 104);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 34);
			this->button4->TabIndex = 2;
			this->button4->Text = L"Железо";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm3::button4_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(7, 64);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 34);
			this->button3->TabIndex = 1;
			this->button3->Text = L"Дуб";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm3::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(6, 24);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 34);
			this->button2->TabIndex = 0;
			this->button2->Text = L"Мрамор";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm3::button2_Click);
			// 
			// MyForm3
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(308, 521);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->MaximumSize = System::Drawing::Size(326, 568);
			this->MinimumSize = System::Drawing::Size(326, 568);
			this->Name = L"MyForm3";
			this->Text = L"Параметры Куба";
			this->Load += gcnew System::EventHandler(this, &MyForm3::MyForm3_Load_1);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	String^ TorZ; // Точка или запятая
	/*private: System::Void MyForm3_Load_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	}
	private: System::Void textBox5_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	}
	private: System::Void textBox6_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	}
	private: System::Void textBox2_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	}
	private: System::Void textBox3_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	}
	private: System::Void textBox4_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	}*/
	private: System::Void MyForm3_Load_1(System::Object^ sender, System::EventArgs^ e) {
		// Выясняем что установлено в настройках в качестве разделителя
		// точка или запятая
		TorZ = Globalization::NumberFormatInfo::CurrentInfo->NumberDecimalSeparator;
	}
	private: System::Void textBox1_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {	// радиус
		bool TZFound = false; // Разделительный знак найден
		if (Char::IsDigit(e->KeyChar) == true) return;	// если нажатый символ цифра выходим
		if (e->KeyChar == (char)Keys::Back) return;		// если нажата Backspase выходим
		if (textBox1->Text->IndexOf(TorZ) != -1)		// проверка позиции разделителя
			TZFound = true;
		if (TZFound == true) { e->Handled = true; return; }	// проверка раздеоителя
		if (e->KeyChar.ToString() == TorZ) return;
		e->Handled = true;
	}
	private: System::Void textBox2_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {	// высота
		bool TZFound = false; // Разделительный знак найден
		if (Char::IsDigit(e->KeyChar) == true) return;	// если нажатый символ цифра выходим
		if (e->KeyChar == (char)Keys::Back) return;		// если нажата Backspase выходим
		if (textBox2->Text->IndexOf(TorZ) != -1)		// проверка позиции разделителя
			TZFound = true;
		if (TZFound == true) { e->Handled = true; return; }	// проверка раздеоителя
		if (e->KeyChar.ToString() == TorZ) return;
		e->Handled = true;
	}
	private: System::Void textBox3_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {	// сила броска
		bool TZFound = false; // Разделительный знак найден
		if (Char::IsDigit(e->KeyChar) == true) return;	// если нажатый символ цифра выходим
		if (e->KeyChar == (char)Keys::Back) return;		// если нажата Backspase выходим
		if (textBox3->Text->IndexOf(TorZ) != -1)		// проверка позиции разделителя
			TZFound = true;
		if (TZFound == true) { e->Handled = true; return; }	// проверка раздеоителя
		if (e->KeyChar.ToString() == TorZ) return;
		e->Handled = true;
	}
	private: System::Void textBox4_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {	// угол
		bool TZFound = false; // Разделительный знак найден
		if (Char::IsDigit(e->KeyChar) == true) return;	// если нажатый символ цифра выходим
		if (e->KeyChar == (char)Keys::Back) return;		// если нажата Backspase выходим
		if (textBox4->Text->IndexOf(TorZ) != -1)		// проверка позиции разделителя
			TZFound = true;
		if (TZFound == true) { e->Handled = true; return; }	// проверка раздеоителя
		if (e->KeyChar.ToString() == TorZ) return;
		e->Handled = true;
	}
	private: System::Void textBox5_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {	// угол
		bool TZFound = false; // Разделительный знак найден
		if (Char::IsDigit(e->KeyChar) == true) return;	// если нажатый символ цифра выходим
		if (e->KeyChar == (char)Keys::Back) return;		// если нажата Backspase выходим
		if (textBox5->Text->IndexOf(TorZ) != -1)		// проверка позиции разделителя
			TZFound = true;
		if (TZFound == true) { e->Handled = true; return; }	// проверка раздеоителя
		if (e->KeyChar.ToString() == TorZ) return;
		e->Handled = true;
	}
	private: System::Void textBox6_KeyPress_1(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {	// угол
		bool TZFound = false; // Разделительный знак найден
		if (Char::IsDigit(e->KeyChar) == true) return;	// если нажатый символ цифра выходим
		if (e->KeyChar == (char)Keys::Back) return;		// если нажата Backspase выходим
		if (textBox6->Text->IndexOf(TorZ) != -1)		// проверка позиции разделителя
			TZFound = true;
		if (TZFound == true) { e->Handled = true; return; }	// проверка раздеоителя
		if (e->KeyChar.ToString() == TorZ) return;
		e->Handled = true;
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Single l = 0, w = 0, hf = 0, h = 0, v = 0, a = 0;
		Single L = Single::TryParse(textBox1->Text,
			System::Globalization::NumberStyles::Number,
			System::Globalization::NumberFormatInfo::CurrentInfo, l);
		Single W = Single::TryParse(textBox5->Text,
			System::Globalization::NumberStyles::Number,
			System::Globalization::NumberFormatInfo::CurrentInfo, w);
		Single HF = Single::TryParse(textBox6->Text,
			System::Globalization::NumberStyles::Number,
			System::Globalization::NumberFormatInfo::CurrentInfo, hf);
		Single H = Single::TryParse(textBox2->Text,
			System::Globalization::NumberStyles::Number,
			System::Globalization::NumberFormatInfo::CurrentInfo, h);
		Single V = Single::TryParse(textBox3->Text,
			System::Globalization::NumberStyles::Number,
			System::Globalization::NumberFormatInfo::CurrentInfo, v);
		Single A = Single::TryParse(textBox4->Text,
			System::Globalization::NumberStyles::Number,
			System::Globalization::NumberFormatInfo::CurrentInfo, a);
		if (w > 0 && w <= 500 && l > 0 && l <= 500 && hf > 0 && hf <= 500) {
			parameter.Init_qube_or_pyramid(l, w, hf, QUBE);
		}
		else {
			if (w <= 0 || w > 500) {
				w = 100.0f;
			}
			if (l <= 0 || l > 500) {
				l = 100.0f;
			}
			if (hf <= 0 || hf > 500) {
				hf = 100.0f;
			}
			parameter.Init_qube_or_pyramid(l, w, hf, QUBE);
		}
		if (h > 0 && h <= 1500) {
			if (v <= 2 && v >= -2) {
				parameter.Initi(a, h, v);
			}
			else {
				if (v < 0) {
					parameter.Initi(a, h, -2);
				}
				else {
					parameter.Initi(a, h, 2);
				}
			}
		}
		else {
			if (v <= 2 && v >= -2) {
				parameter.Initi(a, 0, v);
			}
			else {
				if (v < 0) {
					parameter.Initi(a, 0, -2);
				}
				else {
					parameter.Initi(a, 0, 2);
				}
			}
		}
		parameter.Initi();	// инициализируем скорость
		ID = QUBE;
		Close();
		///////////////////////////////////
		/////////////////////////////////////////////
		/////////////// Создаю Окно /////////////////
		/////////////////////////////////////
		if (!BEGIN) {
			BEGIN = true;
			Window();
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!BEGIN_TEXTURE) {
			//BEGIN_TEXTURE = true;
			Texture = MARBLE;
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!BEGIN_TEXTURE) {
			//BEGIN_TEXTURE = true;
			Texture = OAK;
		}
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!BEGIN_TEXTURE) {
			//BEGIN_TEXTURE = true;
			Texture = IRON;
		}
	}
};
}
