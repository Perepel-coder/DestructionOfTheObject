#include "pch.h"
#include "Main.h"
#include "MyForm2.h"
#include "MyForm3.h"
#include "MyForm4.h"
#pragma once

namespace Project {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^ groupBox1;
	protected:




	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;





	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;

	private: System::Windows::Forms::GroupBox^ groupBox5;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::GroupBox^ groupBox6;

	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label14;



	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::Label^ label26;


	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::Label^ label24;





	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->groupBox6);
			this->groupBox1->Controls->Add(this->groupBox4);
			this->groupBox1->Controls->Add(this->groupBox3);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(414, 341);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Ввод данных";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->label21);
			this->groupBox6->Controls->Add(this->label20);
			this->groupBox6->Controls->Add(this->label19);
			this->groupBox6->Controls->Add(this->label18);
			this->groupBox6->Controls->Add(this->label17);
			this->groupBox6->Controls->Add(this->label12);
			this->groupBox6->Controls->Add(this->label14);
			this->groupBox6->Location = System::Drawing::Point(215, 197);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(193, 138);
			this->groupBox6->TabIndex = 1;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Параметры падения";
			// 
			// label21
			// 
			this->label21->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label21->Location = System::Drawing::Point(75, 95);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(100, 23);
			this->label21->TabIndex = 15;
			// 
			// label20
			// 
			this->label20->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label20->Location = System::Drawing::Point(75, 58);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(100, 23);
			this->label20->TabIndex = 14;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(5, 101);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(38, 17);
			this->label19->TabIndex = 13;
			this->label19->Text = L"Угол";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(5, 58);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(73, 34);
			this->label18->TabIndex = 11;
			this->label18->Text = L"Скорость \r\n(нач)";
			// 
			// label17
			// 
			this->label17->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label17->Location = System::Drawing::Point(75, 22);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(100, 23);
			this->label17->TabIndex = 10;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(5, 23);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(57, 17);
			this->label12->TabIndex = 3;
			this->label12->Text = L"Высота";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(11, 118);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(0, 17);
			this->label14->TabIndex = 2;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->label29);
			this->groupBox4->Controls->Add(this->label28);
			this->groupBox4->Controls->Add(this->label16);
			this->groupBox4->Controls->Add(this->label15);
			this->groupBox4->Controls->Add(this->label13);
			this->groupBox4->Controls->Add(this->label11);
			this->groupBox4->Controls->Add(this->label7);
			this->groupBox4->Controls->Add(this->label6);
			this->groupBox4->Controls->Add(this->label5);
			this->groupBox4->Location = System::Drawing::Point(213, 21);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(195, 170);
			this->groupBox4->TabIndex = 1;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Параметры фигуры";
			// 
			// label29
			// 
			this->label29->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label29->Location = System::Drawing::Point(77, 128);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(100, 23);
			this->label29->TabIndex = 11;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(7, 134);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(55, 17);
			this->label28->TabIndex = 10;
			this->label28->Text = L"Радиус";
			// 
			// label16
			// 
			this->label16->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label16->Location = System::Drawing::Point(77, 92);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(100, 23);
			this->label16->TabIndex = 9;
			// 
			// label15
			// 
			this->label15->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label15->Location = System::Drawing::Point(77, 56);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(100, 23);
			this->label15->TabIndex = 8;
			// 
			// label13
			// 
			this->label13->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label13->Location = System::Drawing::Point(77, 22);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(100, 23);
			this->label13->TabIndex = 7;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(7, 98);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(57, 17);
			this->label11->TabIndex = 3;
			this->label11->Text = L"Высота";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(7, 57);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(59, 17);
			this->label7->TabIndex = 2;
			this->label7->Text = L"Ширина";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(7, 22);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(51, 17);
			this->label6->TabIndex = 1;
			this->label6->Text = L"Длина";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(7, 36);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(0, 17);
			this->label5->TabIndex = 0;
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->groupBox3->Controls->Add(this->button3);
			this->groupBox3->Controls->Add(this->button2);
			this->groupBox3->Controls->Add(this->button1);
			this->groupBox3->Location = System::Drawing::Point(7, 21);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(199, 314);
			this->groupBox3->TabIndex = 0;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Фигура";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(23, 100);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(95, 35);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Пирамида";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(24, 61);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(94, 33);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Куб";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(24, 21);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(94, 33);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Шар";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->groupBox2->Controls->Add(this->button4);
			this->groupBox2->Controls->Add(this->label27);
			this->groupBox2->Controls->Add(this->label26);
			this->groupBox2->Controls->Add(this->label23);
			this->groupBox2->Controls->Add(this->label22);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Location = System::Drawing::Point(12, 359);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(414, 301);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Показатели";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(29, 255);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(159, 29);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Вывести показатели";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label27
			// 
			this->label27->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label27->Location = System::Drawing::Point(223, 208);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(91, 23);
			this->label27->TabIndex = 20;
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(220, 182);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(96, 17);
			this->label26->TabIndex = 19;
			this->label26->Text = L"Макс. высота";
			// 
			// label23
			// 
			this->label23->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label23->Location = System::Drawing::Point(115, 208);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(91, 23);
			this->label23->TabIndex = 16;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(112, 182);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(39, 17);
			this->label22->TabIndex = 6;
			this->label22->Text = L"Путь";
			// 
			// label9
			// 
			this->label9->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label9->Location = System::Drawing::Point(7, 208);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(87, 23);
			this->label9->TabIndex = 5;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 182);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(50, 17);
			this->label8->TabIndex = 4;
			this->label8->Text = L"Время";
			// 
			// label4
			// 
			this->label4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label4->Location = System::Drawing::Point(7, 146);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(383, 23);
			this->label4->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(27, 119);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(132, 17);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Предел прочности";
			// 
			// label2
			// 
			this->label2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label2->Location = System::Drawing::Point(7, 45);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(383, 65);
			this->label2->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(26, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(80, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Уравнение";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->label24);
			this->groupBox5->Controls->Add(this->label10);
			this->groupBox5->Location = System::Drawing::Point(433, 13);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(604, 647);
			this->groupBox5->TabIndex = 2;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Инструкции по управлению";
			// 
			// label24
			// 
			this->label24->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label24->Location = System::Drawing::Point(6, 20);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(592, 624);
			this->label24->TabIndex = 1;
			this->label24->Text = resources->GetString(L"label24.Text");
			// 
			// label10
			// 
			this->label10->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label10->Location = System::Drawing::Point(15, 20);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(450, 503);
			this->label10->TabIndex = 0;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1050, 672);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"END";
			this->groupBox1->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm2 ^newForm = gcnew MyForm2();
		newForm->Show();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm3^ newForm2 = gcnew MyForm3();
		newForm2->Show();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm4^ newForm3 = gcnew MyForm4();
		newForm3->Show();
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		label13->Text = "";
		label15->Text = "";
		label16->Text = "";
		label29->Text = "";
		label17->Text = "";
		label20->Text = "";
		label21->Text = "";
		label2->Text = "";
		label4->Text = "";
		label9->Text = "";
		label23->Text = "";
		label27->Text = "";
		if (BEGIN) {
			switch (ID)
			{
			case QUBE:
				label13->Text = String::Format("{0:F3} м", data.p_qube.length);
				label15->Text = String::Format("{0:F3} м", data.p_qube.width);
				label16->Text = String::Format("{0:F3} м", data.p_qube.height);
				break;
			case PYRAMID:
				label13->Text = String::Format("{0:F3} м", data.p_pyramid.length);
				label15->Text = String::Format("{0:F3} м", data.p_pyramid.width);
				label16->Text = String::Format("{0:F3} м", data.p_pyramid.height);
				break;
			case SPHERE:
				label29->Text = String::Format("{0:F3} м", data.p_sphere.radius);
			}
			/////////////// показатели падения ////////////
			data.p_fall.a = (float)((data.p_fall.a * 180) / PI);
			label17->Text = String::Format("{0:F3} м", data.p_fall.h);
			label20->Text = String::Format("{0:F3} м", data.p_fall.v);
			label21->Text = String::Format("{0:F3} гр", data.p_fall.a);
			//////////// уравнение ///////////////
			float b = tan(data.p_fall.a);
			if (data.p_fall.v != 0 && cos(data.p_fall.a)!=0) {
				float a = (9.8f) / (2 * data.p_fall.v * data.p_fall.v * cos(data.p_fall.a) * cos(data.p_fall.a));
				label2->Text = String::Format("y = {0:F3} * x - {0:F3} * x^2 + {0:F3}", b, a, data.p_fall.h);
			}
			else {
				label2->Text = String::Format("y = - {0:F3} * t^2", 9.8f);
			}
			////////// предел прочности ////////////////
			switch (data.tex)
			{
			case MARBLE:
				label4->Text = String::Format("Предел прочности мрамора не менее: {0:F3}(МПа)", 40);
				break;
			case IRON:
				label4->Text = String::Format("Предел прочности железа: {0:F3}(МПа)", 250);
				break;
			case OAK:
				label4->Text = String::Format("Сжатие вдоль волокон: {0:F3}(МПа)", 8);
				break;
			default:
				label4->Text = String::Format("НЕ УБИВАЕМ!!!!!!!");
				break;
			}
			label9->Text = String::Format("{0:F0} сек", data.p_fall.t * 100000);
			label23->Text = String::Format("{0:F3} м", data.p_fall.s);
			float h = (data.p_fall.v * data.p_fall.v * sin(data.p_fall.a) * sin(data.p_fall.a)) / (2 * 9.8f) + data.p_fall.h;
			label27->Text = String::Format("{0:F3} м", h);
		}
		data.destruct();
	}	
};
}